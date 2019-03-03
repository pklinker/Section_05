// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PatrolUe4ASP_Character.generated.h"

UCLASS(config = Game)
class SECTION_05_API APatrolUe4ASP_Character : public ACharacter
{
	GENERATED_BODY()

	/** Gun mesh */
//	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
//	class USkeletalMeshComponent* Patrol_Gun;
	/** body mesh */
//	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
//		USkeletalMeshComponent *CharacterMesh;

public:
	// Sets default values for this character's properties
	APatrolUe4ASP_Character();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
