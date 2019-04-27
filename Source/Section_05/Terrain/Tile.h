// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "Tile.generated.h"

USTRUCT(BlueprintType)
struct FSpawnPosition
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY(BlueprintReadWrite, Category = "Spawn Position")
		FVector Location; // make these uproperties to be available in blueprint
	UPROPERTY(BlueprintReadWrite, Category = "Spawn Position")
		float YawRotation;
	UPROPERTY(BlueprintReadWrite, Category = "Spawn Position")
		float Scale;
};

USTRUCT(BlueprintType)
struct FSpawnRandomizers
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Spawn Randomizer")
		int MinSpawnedActors; 
	UPROPERTY(BlueprintReadWrite, Category = "Spawn Randomizer")
		int MaxSpawnedActors;
	UPROPERTY(BlueprintReadWrite, Category = "Spawn Randomizer")
		float Radius;
	UPROPERTY(BlueprintReadWrite, Category = "Spawn Randomizer")
		float MinimumScale = 1.0;
	UPROPERTY(BlueprintReadWrite, Category = "Spawn Randomizer")
		float MaximumScale = 1.0;
};

class UActorPool;
UCLASS()
class SECTION_05_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();
	UFUNCTION(BlueprintCallable, Category="Setup")
		void  PlaceActors(TSubclassOf<AActor> ToSpawn, FSpawnRandomizers SpawnRandomizers);
	UFUNCTION(BlueprintCallable, Category = "Setup")
		void  PlaceAIPawns(TSubclassOf<APawn> ToSpawn, FSpawnRandomizers SpawnRandomizers);
	UFUNCTION(BlueprintCallable, Category = "Setup")
		void PlaceGrass(int NumberOfGrassTextures, bool RandomQuantity);
	UFUNCTION(BlueprintCallable, Category = "Setup")
		void SetNavVolumeActorPool(UActorPool *InPool);
	//UFUNCTION(BlueprintCallable, Category = "Setup")
		TArray<FSpawnPosition> SpawnRandomPositions(FSpawnRandomizers SpawnRandomizers);
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
	void PlaceActor(TSubclassOf<AActor> ToSpawn, FSpawnPosition SpawnPosition);
	void PlaceActor(TSubclassOf<APawn> ToSpawn, FSpawnPosition SpawnPosition);
	void SpawnGrass(FTransform initialTransform, uint32 actorId);
	template <class T>
	void RandomlyPlaceActors(TSubclassOf<T> ToSpawn, FSpawnRandomizers SpawnRandomizers);

	TMap<uint32, uint32> IdToInstanceMapping;
	UActorPool *NavMeshVolumeActorPool;
	AActor *NavMeshVolumeActor;
};


