// Fill out your copyright notice in the Description page of Project Settings.

#include "InfiniteTerrainGameMode.h"
#include "GameFramework/Volume.h"
#include "Public/EngineUtils.h"


void AInfiniteTerrainGameMode::AddToPool(AVolume *NavMeshBV) 
{
	if (NavMeshBV)
	{
//		UE_LOG(LogTemp, Warning, TEXT("Determing whether to add to pool %s."), *NavMeshBV->GetName());
		FString VolumeName = *NavMeshBV->GetName();
		if (VolumeName.Contains(FString("NavMesh"), ESearchCase::CaseSensitive, ESearchDir::FromStart))
		{
			UE_LOG(LogTemp, Warning, TEXT("Adding to pool %s."), *NavMeshBV->GetName());
			NavMeshBoundsVolumes.Add(NavMeshBV);
		}
	}

}

void AInfiniteTerrainGameMode::PopulateVolumeBoundsPool()
{
	UE_LOG(LogTemp, Warning, TEXT("PopulateVolumeBoundsPool."));
	auto VolumeIterator = TActorIterator<AVolume>(GetWorld());
	while (VolumeIterator)
	{
		AddToPool(*VolumeIterator);
		// moves to the next instance of type ANavMeshBoundsVolume
		++VolumeIterator;
	}

}
