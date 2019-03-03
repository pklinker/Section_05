// Fill out your copyright notice in the Description page of Project Settings.

#include "PatrolUe4ASP_Character.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
APatrolUe4ASP_Character::APatrolUe4ASP_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Create a mesh component that will be used 
	USkeletalMeshComponent *CharacterMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	if (!CharacterMesh)
	{
		return;
	}
	CharacterMesh->SetOnlyOwnerSee(false);
	CharacterMesh->bCastDynamicShadow = true;
	CharacterMesh->CastShadow = true;

	// Create a gun mesh component
	USkeletalMeshComponent *Patrol_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Patrol_Gun"));
	if (!Patrol_Gun)
	{
		return;
	}
	Patrol_Gun->SetOnlyOwnerSee(false);			// Anyone can see this mesh
	Patrol_Gun->bCastDynamicShadow = false;
	Patrol_Gun->CastShadow = false;
	Patrol_Gun->RelativeRotation = FRotator(-2.808f, 23.718f, 0.0f);
	Patrol_Gun->RelativeLocation = FVector(0.0f, 0.0f, -100.0f);
	Patrol_Gun->SetupAttachment(RootComponent);
}


// Called when the game starts or when spawned
void APatrolUe4ASP_Character::BeginPlay()
{
	Super::BeginPlay();
	//Attach gun mesh component to Skeleton, doing it here because the skeleton is not yet created in the constructor
	//Patrol_Gun->AttachToComponent(CharacterMesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));

}

// Called every frame
void APatrolUe4ASP_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APatrolUe4ASP_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

