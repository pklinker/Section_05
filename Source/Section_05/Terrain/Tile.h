// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

UCLASS()
class SECTION_05_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();
	UFUNCTION(BlueprintCallable, Category="Setup")
		void  PlaceActors(TSubclassOf<AActor> ToSpawn, int MinSpawnedActors, int MaxSpawnedActors, float Radius, float MinimumScale = 1.0, float MaximumScale = 1.0);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
		int MAX_TRIES = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
		FVector BackLeftVector = FVector(0, -2000, 0);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
		FVector FarRightVector = FVector(4000, 2000, 0);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	bool CastSphere(FVector Location, float Radius);
	bool GetEmptySpawnPoint(FVector &SpawnPoint, float Radius);
	void PlaceActor(TSubclassOf<AActor> ToSpawn, FVector SpawnPoint, float YawRotation, float Scale);


};
