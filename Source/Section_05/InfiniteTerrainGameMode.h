// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Section_05GameMode.h"
#include "InfiniteTerrainGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SECTION_05_API AInfiniteTerrainGameMode : public ASection_05GameMode
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Bounds Pool")
	void PopulateVolumeBoundsPool();

protected:
	void AddToPool(class AVolume *NavMeshBV);
	TArray<class AVolume*> NavMeshBoundsVolumes;
};
