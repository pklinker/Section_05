// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "ActorPool.h"
#include "AI/NavigationSystemBase.h"
#include "EngineUtils.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	NavigationBoundsOffset = FVector(2000, 0, 0);
}

void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, FSpawnRandomizers SpawnRandomizers)
{
	RandomlyPlaceActors(ToSpawn, SpawnRandomizers);
}

void ATile::PlaceAIPawns(TSubclassOf<APawn> ToSpawn, FSpawnRandomizers SpawnRandomizers)
{
	RandomlyPlaceActors(ToSpawn, SpawnRandomizers);
}

template<class T>
void ATile::RandomlyPlaceActors(TSubclassOf<T> ToSpawn, FSpawnRandomizers SpawnRandomizers)
{
	// set a minimum of 1 to prevent weirdness
	if (SpawnRandomizers.MinSpawnedActors < 0)
	{
		SpawnRandomizers.MinSpawnedActors = 0;
	}
	// verify max is greater than min. If not, set max to min+1
	if (SpawnRandomizers.MaxSpawnedActors <= SpawnRandomizers.MinSpawnedActors)
	{
		SpawnRandomizers.MaxSpawnedActors = SpawnRandomizers.MinSpawnedActors + 1;
	}
	int NumActorsToSpawn = FMath::RandRange(SpawnRandomizers.MinSpawnedActors, SpawnRandomizers.MaxSpawnedActors);
	//UE_LOG(LogTemp, Warning, TEXT("=======================Spawning %i actors =======================================."), NumActorsToSpawn);
	for (size_t i = 0; i < NumActorsToSpawn; i++) {
		FSpawnPosition SpawnPosition;
		SpawnPosition.Scale = FMath::RandRange(SpawnRandomizers.MinimumScale, SpawnRandomizers.MaximumScale);
		bool SpawnPointFound = GetEmptySpawnPoint(SpawnPosition.Location, SpawnRandomizers.Radius*SpawnPosition.Scale);
		if (SpawnPointFound)
		{
			SpawnPosition.YawRotation = FMath::RandRange(-180.f, 180.f);
			PlaceActor(ToSpawn, SpawnPosition);
		}

	}
}
void ATile::PlaceActor(TSubclassOf<APawn> ToSpawn, FSpawnPosition SpawnPosition)
{
	APawn* SpawnedPawn = GetWorld()->SpawnActor<APawn>(ToSpawn);
	if (SpawnedPawn == nullptr)
	{
		return;
	}
	SpawnedPawn->SetActorRelativeLocation(SpawnPosition.Location);
	SpawnedPawn->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	SpawnedPawn->SetActorRotation(FRotator(0, SpawnPosition.YawRotation, 0));
	SpawnedPawn->SpawnDefaultController(); // automatically creates AIController and attaches it to ensure Pawn in controlled.
	SpawnedPawn->Tags.Add(FName("Enemy"));

}

void ATile::PlaceActor(TSubclassOf<AActor> ToSpawn, FSpawnPosition SpawnPosition)
{
	//		const FRotator SpawnRotation = GetActorRotation();
			//Set Spawn Collision Handling Override
	//		FActorSpawnParameters ActorSpawnParams;
	//		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	//		AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(*ToSpawn, SpawnPoint, SpawnRotation,ActorSpawnParams);
	AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ToSpawn);
	//UE_LOG(LogTemp, Warning, TEXT("Random point: %s spawned actor %s."), *SpawnPoint.ToString(), *SpawnedActor->GetFName().ToString());
	if (SpawnedActor == nullptr)
	{
		return;
	}
	SpawnedActor->SetActorRelativeLocation(SpawnPosition.Location);
	SpawnedActor->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	SpawnedActor->SetActorRotation(FRotator(0, SpawnPosition.YawRotation, 0));
	SpawnedActor->SetActorScale3D(FVector(SpawnPosition.Scale, SpawnPosition.Scale, SpawnPosition.Scale));
}


/**
* If RandomQuantity is true then it will use the NumberOfGrassTextures as a maximum in a random number generator
NOT USED YET
*/
void ATile::PlaceGrass(int NumberOfGrassTextures, bool RandomQuantity)
{
	int NumGrassToSpawn = NumberOfGrassTextures;
	if (RandomQuantity)
	{
		NumGrassToSpawn = FMath::RandRange(1, NumberOfGrassTextures);
	}
//	UHierarchicalInstancedStaticMeshComponent HISMC_GrassTexture = UHierarchicalInstancedStaticMeshComponent();

	UE_LOG(LogTemp, Warning, TEXT("=======================Spawning %i grass textures =======================================."), NumGrassToSpawn);
	for (size_t i = 0; i < NumGrassToSpawn; i++) {
		FVector SpawnPoint;
	
		bool SpawnPointFound = GetEmptySpawnPoint(SpawnPoint, 100);
		if (SpawnPointFound)
		{
			float RandomYawRotation = FMath::RandRange(-180.f, 180.f);
			FRotator Rotation = FRotator(0, RandomYawRotation, 0);
			FTransform grassTransform;
			grassTransform.SetLocation(SpawnPoint);
			//FRotator CachedRotator = foundSocket->RelativeRotation.GetNormalized();
			grassTransform.SetRotation(Rotation.Quaternion());
			//grassTransform.SetScale3D(1.0f);
			SpawnGrass(grassTransform, i);
		//	PlaceActor(ToSpawn, SpawnPoint, RandomYawRotation, Scale);
		}
	}
}

void ATile::SetNavVolumeActorPool(UActorPool * InPool)
{
	if (!InPool)
	{
		UE_LOG(LogTemp, Error, TEXT("ATile InPool parameter is null."));
		return;
	}
	NavMeshVolumeActorPool = InPool;
	PositionNavMeshBoundsVolume();
}

TArray<FSpawnPosition> ATile::SpawnRandomPositions(FSpawnRandomizers SpawnRandomizers)
{
	TArray<FSpawnPosition> SpawnPositionArray;
	// set a minimum of 1 to prevent weirdness
	if (SpawnRandomizers.MinSpawnedActors < 0)
	{
		SpawnRandomizers.MinSpawnedActors = 0;
	}
	// verify max is greater than min. If not, set max to min+1
	if (SpawnRandomizers.MaxSpawnedActors <= SpawnRandomizers.MinSpawnedActors)
	{
		SpawnRandomizers.MaxSpawnedActors = SpawnRandomizers.MinSpawnedActors + 1;
	}
	int NumActorsToSpawn = FMath::RandRange(SpawnRandomizers.MinSpawnedActors, SpawnRandomizers.MaxSpawnedActors);
	//UE_LOG(LogTemp, Warning, TEXT("=======================Spawning %i actors =======================================."), NumActorsToSpawn);
	for (size_t i = 0; i < NumActorsToSpawn; i++) {
		FSpawnPosition SpawnPosition;
		SpawnPosition.Scale = FMath::RandRange(SpawnRandomizers.MinimumScale, SpawnRandomizers.MaximumScale);
		bool SpawnPointFound = GetEmptySpawnPoint(SpawnPosition.Location, SpawnRandomizers.Radius*SpawnPosition.Scale);
		if (SpawnPointFound)
		{
			SpawnPosition.YawRotation = FMath::RandRange(-180.f, 180.f);		
			SpawnPositionArray.Push(SpawnPosition);
		}

	}
	return SpawnPositionArray;
}

// Set the location of the nav mesh to the location of the tile it will be covering.
void ATile::PositionNavMeshBoundsVolume()
{
	if (NavMeshVolumeActorPool == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("NavMeshVolumeActorPool is null in the Tile."));
		return;
	}
	NavMeshVolumeActor = NavMeshVolumeActorPool->CheckoutActor();
	if (NavMeshVolumeActor == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("NavMeshBoundsVolume is null in the Tile."));
		return;
	}
	NavMeshVolumeActor->SetActorLocation(GetActorLocation()+ NavigationBoundsOffset);
	FNavigationSystem::Build(*GetWorld());
}

void ATile::SpawnGrass(FTransform initialTransform, uint32 actorId) {
	if (MeshPool == nullptr)
	{
		return;
	}
	int32 index = MeshPool->AddInstanceWorldSpace(initialTransform);
	IdToInstanceMapping.Add(actorId, index);
}
// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
}

void ATile::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	if (!NavMeshVolumeActorPool)
	{
		UE_LOG(LogTemp, Error, TEXT("NavMeshVolumeActorPool is null in the Tile EndPlay."));
		return;
	}
	else if (!NavMeshVolumeActor)
	{
		UE_LOG(LogTemp, Error, TEXT("NavMeshVolumeActor is null in the Tile EndPlay."));
		return;

	}
	UE_LOG(LogTemp, Warning, TEXT("[%s] EndPlay, checking in: %s"), *GetName(), *NavMeshVolumeActor->GetName());
	NavMeshVolumeActorPool->CheckinActor(NavMeshVolumeActor);
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/**
True if it hits anything using sphere casting.
*/
bool ATile::CastSphere(FVector Location, float Radius)
{
	FHitResult  HitResult; // not used
	FVector GlobalLocation = ActorToWorld().TransformPosition(Location);
	// channel is where each object makes a decision of how it reacts to the channel. Make sure trigger volumes ignore SpawnTraceChannel
	bool HitOccurred = GetWorld()->SweepSingleByChannel(
		HitResult,
		GlobalLocation, /// we are placing an item in the world so the start and end locations are the same becuase we are looking for collisions with existing objects.
		GlobalLocation,
		FQuat::Identity, /// Zero rotation, we don't want a rotation. So no effect.
		ECollisionChannel::ECC_GameTraceChannel2, // this is tied to the custom SpawnTraceChannel found in config\DefaultEngine.ini
		FCollisionShape::MakeSphere(Radius)
		);

	FColor ResultColor = HitOccurred ? FColor::Red : FColor::Green;
	//DrawDebugSphere(GetWorld(), GlobalLocation, Radius, 32, ResultColor, true, 300);
	//UE_LOG(LogTemp, Warning, TEXT("Drawing debug capsule at %s."), *Location.ToString());

//	DrawDebugCapsule(GetWorld(), Location, 0, Radius, FQuat::Identity, ResultColor, true, 100);
	return HitOccurred;
}

bool ATile::GetEmptySpawnPoint(FVector &SpawnPoint, float Radius)
{
	bool keeptrying = true;
	int i = 0;
	while (keeptrying)
	{
		SpawnPoint = FMath::RandPointInBox(FBox(BackLeftVector, FarRightVector));

		if (!CastSphere(SpawnPoint, Radius))
		{
			return true;
		}
		if (i >= MAX_TRIES) {
			keeptrying = false;
		}
		i = i++;
	}
	return false;
}

