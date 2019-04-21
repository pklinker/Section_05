// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActorPool.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SECTION_05_API UActorPool : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UActorPool();
	// Call CheckoutActor when you want to get exclusive access to an actor from the pool 
	AActor* CheckoutActor();
	void ReturnActor(AActor *ActorToReturn);
	void Add(AActor *ActorToAdd);


protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	TArray<class AActor*> FreeActors;
	TArray<class AActor*> CheckedOutActors;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
