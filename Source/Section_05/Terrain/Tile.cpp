// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "DrawDebugHelpers.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}
void ATile::PlaceActor(TSubclassOf<AActor> ToSpawn, FVector SpawnPoint)
{
	//		const FRotator SpawnRotation = GetActorRotation();
			//Set Spawn Collision Handling Override
	//		FActorSpawnParameters ActorSpawnParams;
	//		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	//		AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(*ToSpawn, SpawnPoint, SpawnRotation,ActorSpawnParams);
	AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ToSpawn);
	UE_LOG(LogTemp, Warning, TEXT("Random point: %s spawned actor %s."), *SpawnPoint.ToString(), *SpawnedActor->GetFName().ToString());
	SpawnedActor->SetActorRelativeLocation(SpawnPoint);
	SpawnedActor->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
}

void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, int MinSpawnedActors, int MaxSpawnedActors, float Radius)
{
	// set a minimum of 1 to prevent weirdness
	if (MinSpawnedActors < 0)
	{
		MinSpawnedActors = 0; 
	}
	// verify max is greater than min. If not, set max to min+1
	if (MaxSpawnedActors <= MinSpawnedActors)
	{
		MaxSpawnedActors = MinSpawnedActors + 1;
	}
	int NumActorsToSpawn = FMath::RandRange(MinSpawnedActors, MaxSpawnedActors);
	UE_LOG(LogTemp, Warning, TEXT("=======================Spawning %i actors =======================================."), NumActorsToSpawn);
	for (size_t i = 0; i < NumActorsToSpawn; i++) {
		FVector SpawnPoint;
		bool SpawnPointFound = GetEmptySpawnPoint(SpawnPoint, Radius);
		if (SpawnPointFound)
		{
			PlaceActor(ToSpawn, SpawnPoint);
		}
	}
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
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
	DrawDebugSphere(GetWorld(), GlobalLocation, Radius, 32, ResultColor, true, 300);
	UE_LOG(LogTemp, Warning, TEXT("Drawing debug capsule at %s."), *Location.ToString());

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

