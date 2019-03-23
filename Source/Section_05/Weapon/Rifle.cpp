// Fill out your copyright notice in the Description page of Project Settings.

#include "Rifle.h"
#include "Kismet/GameplayStatics.h"
#include "Weapon/FirstPersonProjectile.h"
#include "Animation/AnimInstance.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
ARifle::ARifle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Create a gun mesh component
	RifleComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	RifleComponent->bCastDynamicShadow = false;
	RifleComponent->CastShadow = false;
	// RifleComponent->SetupAttachment(Mesh1P, TEXT("GripPoint"));
//	RifleComponent->SetupAttachment(RootComponent);

	MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	MuzzleLocation->SetupAttachment(RifleComponent);
//	MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));
	MuzzleLocation->SetRelativeLocation(FVector(0.2f, 0.0f, 0.0f));
}

FVector ARifle::GetMuzzleLocation()
{
	if (!ensure(MuzzleLocation))
	{
		UE_LOG(LogTemp, Warning, TEXT("Rifle muzzle is missing."));
		return FVector();
	}
	return MuzzleLocation->GetComponentLocation();
}

FRotator ARifle::GetMuzzleRotation()
{
	if (!ensure(MuzzleLocation)) {
		UE_LOG(LogTemp, Warning, TEXT("Rifle muzzle is missing."));
		return FRotator();
	}

	FRotator MuzzleRotator = MuzzleLocation->GetComponentRotation();
	return MuzzleRotator;
}

// Called when the game starts or when spawned
void ARifle::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ARifle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARifle::Fire()
{
 // RifleBlueprint is firing.

	// try and fire a projectile
	if (ProjectileBlueprint != NULL)
	{
		

		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			//const FRotator SpawnRotation = GetActorRotation();
			const FRotator SpawnRotation = MuzzleLocation->GetComponentRotation();
			// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
			const FVector SpawnLocation =  MuzzleLocation->GetComponentLocation();

			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			// spawn the projectile at the muzzle
			World->SpawnActor<AFirstPersonProjectile>(ProjectileBlueprint, SpawnLocation, SpawnRotation, ActorSpawnParams);
		}
	}

	// try and play the sound if specified
	if (FireSound != NULL)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}

	// try and play a firing animation if specified
	if (FireAnimation != NULL)
	{
		
		if (AnimInstance != NULL)
		{
		//	UE_LOG(LogTemp, Warning, TEXT("RifleBlueprint AnimInstance not null."));
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}
}
