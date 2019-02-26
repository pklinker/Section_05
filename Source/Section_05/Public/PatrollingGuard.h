// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "PatrollingGuard.generated.h"

class UBehaviorTreeComponent;
/**
 * 
 */
UCLASS()
class SECTION_05_API APatrollingGuard : public ATP_ThirdPersonCharacter
{
	GENERATED_BODY()

public:
	//UPROPERTY()
	TArray<AActor *> GetNextWaypoint();

protected:
	UPROPERTY(EditAnywhere, Category = "Patrol Route")
	TArray<AActor *> Waypoints;
	
};
