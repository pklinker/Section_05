// Fill out your copyright notice in the Description page of Project Settings.

#include "PatrolRouteComponent.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UPatrolRouteComponent::UPatrolRouteComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPatrolRouteComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPatrolRouteComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

TArray<AActor*> UPatrolRouteComponent::GetPatrolPoints()
{
	return Waypoints;
}

void UPatrolRouteComponent::SetPatrolPoints(TArray<AActor*> WaypointArray)
{
	Waypoints = WaypointArray;
}

