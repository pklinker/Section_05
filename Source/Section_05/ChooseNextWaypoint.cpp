// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "GameFramework/Actor.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Public/PatrolRouteComponent.h"
EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	
	// get the patrol points
	AAIController* AIControl = OwnerComp.GetAIOwner();
	if (!AIControl) {
		return EBTNodeResult::Aborted;
	}
	auto ControlledPawn = AIControl->GetPawn();
	if (!ControlledPawn)
	{
		return EBTNodeResult::Failed;
	}
	//TODO remove coupling
	UPatrolRouteComponent *PatrolRtComp = ControlledPawn->FindComponentByClass<UPatrolRouteComponent>();
	if (!PatrolRtComp)
	{
		return EBTNodeResult::Failed;
	}
	PatrolPoints = PatrolRtComp->GetPatrolPoints();
	BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComp)
	{
		return EBTNodeResult::Failed;
	}

//	auto Index = BlackboardComp->GetValueAsInt(FName("NextWaypointIndex"));
	int32 Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	int32 CurrentIndex = SetNextWayPoint(Index);
	CycleWaypointIndex(CurrentIndex);
	//UE_LOG(LogTemp, Warning, TEXT("Waypoint index: %i."), Index);

	return EBTNodeResult::Succeeded;
}

void UChooseNextWaypoint::SetPatrolPoints(TArray<AActor*> PatrolPts)
{
	PatrolPoints = PatrolPts;
}

int32 UChooseNextWaypoint::SetNextWayPoint(int32 Index)
{

	// the FName works also
//	BlackboardComp->SetValueAsObject(FName("NextWaypoint"), PatrolPoints[Index]);
	BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[Index]);
	return Index;
}

void UChooseNextWaypoint::CycleWaypointIndex(int32 CurrentIndex)
{
	int32 NextIndex = (CurrentIndex + 1) % PatrolPoints.Num();
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);
}

