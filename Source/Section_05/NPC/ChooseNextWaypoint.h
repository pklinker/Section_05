// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "ChooseNextWaypoint.generated.h"

/**
 * 
 */
UCLASS()
class SECTION_05_API UChooseNextWaypoint : public UBTTaskNode
{
	GENERATED_BODY()

public:
	/** starts this task, should return Succeeded, Failed or InProgress
		*  (use FinishLatentTask() when returning InProgress)
		* this function should be considered as const (don't modify state of object) if node is not instanced! */
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	/** Sets the array of patrol or way points. */
	void SetPatrolPoints(TArray<AActor *> PatrolPts);
	/** Sets the index of the next waypoint or patrol point to navigate to. */
	int32 SetNextWayPoint(int32 Index);
	/** increment the index of the next waypoint */
	void CycleWaypointIndex(int32 CurrentIndex);

protected:

	UPROPERTY(EditAnywhere, Category = "Blackboard")
		struct FBlackboardKeySelector IndexKey;
	UPROPERTY(EditAnywhere, Category = "Blackboard")
		struct FBlackboardKeySelector WaypointKey;
	TArray<AActor *> PatrolPoints;

private:
	UBlackboardComponent *BlackboardComp;
};
