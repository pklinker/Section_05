// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Section_05GameMode.h"
#include "InfiniteTerrainGameMode.generated.h"

class UActorPool;
/**
 * 
 */
UCLASS()
class SECTION_05_API AInfiniteTerrainGameMode : public ASection_05GameMode
{
	GENERATED_BODY()
	
public:
	AInfiniteTerrainGameMode();

	UFUNCTION(BlueprintCallable, Category = "Bounds Pool")
	void PopulateVolumeBoundsPool();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bounds Pool")
		UActorPool *NavMeshVolumeActorPool;

protected:
	void AddToPool(class AVolume *NavMeshBV);
	TArray<class AVolume*> NavMeshBoundsVolumes;
};
