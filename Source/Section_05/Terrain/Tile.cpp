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

void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, int MinSpawnedActors, int MaxSpawnedActors)
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
	FVector BackLeftVector = FVector(0, -2000, 0);
	FVector FarRightVector = FVector(4000, 2000, 0);
	for (size_t i = 0; i < NumActorsToSpawn; i++) {
		FVector SpawnPoint = FMath::RandPointInBox(FBox(BackLeftVector, FarRightVector));
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
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	CastSphere(GetActorLocation(), 300.0f);
	CastSphere(GetActorLocation() + FVector(800, 0, 0), 300.0f);
	
	
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
	// channel is where each object makes a decision of how it reacts to the channel. Make sure trigger volumes ignore SpawnTraceChannel
	bool HitOccurred = GetWorld()->SweepSingleByChannel(
		HitResult,
		Location, /// we are placing an item in the world so the start and end locations are the same becuase we are looking for collisions with existing objects.
		Location,
		FQuat::Identity, /// Zero rotation, we don't want a rotation. So no effect.
		ECollisionChannel::ECC_GameTraceChannel2, // this is tied to the custom SpawnTraceChannel found in config\DefaultEngine.ini
		FCollisionShape::MakeSphere(Radius)
		);

	FColor ResultColor = HitOccurred ? FColor::Red : FColor::Green;
	//DrawDebugSphere(GetWorld(), Location, Radius, 32, ResultColor, true, 100);
	DrawDebugCapsule(GetWorld(), Location, 0, Radius, FQuat::Identity, ResultColor, true, 100);
	return HitOccurred;
}

