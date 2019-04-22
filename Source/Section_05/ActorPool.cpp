// Fill out your copyright notice in the Description page of Project Settings.

#include "ActorPool.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties

UActorPool::UActorPool()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


AActor * UActorPool::CheckoutActor()
{
	AActor *TheActor = nullptr;
	if (FreeActors.Num() > 0)
	{
		TheActor = FreeActors.Pop(true);
		UE_LOG(LogTemp, Warning, TEXT("Actor %s checked out."), *TheActor->GetName());
	} 
	return TheActor;
}

void UActorPool::CheckinActor(AActor * ActorToReturn)
{
	Add(ActorToReturn);
}

void UActorPool::Add(AActor * ActorToAdd)
{
	if (ActorToAdd)
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor %s checked in."), *ActorToAdd->GetName());
		FreeActors.Push(ActorToAdd);
	}
}

// Called when the game starts
void UActorPool::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UActorPool::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

