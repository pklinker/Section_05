// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "Tile.generated.h"

class UActorPool;
UCLASS()
class SECTION_05_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();
	UFUNCTION(BlueprintCallable, Category="Setup")
		void  PlaceActors(TSubclassOf<AActor> ToSpawn, int MinSpawnedActors, int MaxSpawnedActors, float Radius, float MinimumScale = 1.0, float MaximumScale = 1.0);
	UFUNCTION(BlueprintCallable, Category = "Setup")
		void PlaceGrass(int NumberOfGrassTextures, bool RandomQuantity);
	UFUNCTION(BlueprintCallable, Category = "Setup")
		void SetNavVolumeActorPool(UActorPool *InPool);

	void PositionNavMeshBoundsVolume();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
		int MAX_TRIES = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
		FVector BackLeftVector = FVector(0, -2000, 0);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
		FVector FarRightVector = FVector(4000, 2000, 0);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
		UHierarchicalInstancedStaticMeshComponent* MeshPool;
	UPROPERTY(EditDefaultsOnly, Category = "Navigation")
		FVector NavigationBoundsOffset;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	bool CastSphere(FVector Location, float Radius);
	bool GetEmptySpawnPoint(FVector &SpawnPoint, float Radius);
	void PlaceActor(TSubclassOf<AActor> ToSpawn, FVector SpawnPoint, float YawRotation, float Scale);
	void SpawnGrass(FTransform initialTransform, uint32 actorId);
	TMap<uint32, uint32> IdToInstanceMapping;
	UActorPool *NavMeshVolumeActorPool;
	AActor *NavMeshVolumeActor;
};
