// Fill out your copyright notice in the Description page of Project Settings.

#include "InfiniteTerrainGameMode.h"
#include "GameFramework/Volume.h"
#include "ActorPool.h"
#include "Public/EngineUtils.h"


AInfiniteTerrainGameMode::AInfiniteTerrainGameMode()
{
	NavMeshVolumeActorPool = CreateDefaultSubobject<UActorPool>(FName("Nav Mesh Volume Actor Pool"));
}


// Put the nav mesh volumes to the actor pool. This sends all volumes to add to pool 
void AInfiniteTerrainGameMode::PopulateVolumeBoundsPool()
{
	UE_LOG(LogTemp, Warning, TEXT("PopulateVolumeBoundsPool called."));
	auto VolumeIterator = TActorIterator<AVolume>(GetWorld());

	while (VolumeIterator)
	{
		AddToPool(*VolumeIterator);
		// moves to the next instance of type ANavMeshBoundsVolume
		++VolumeIterator;
	}

}

// Adds a Nav mesh volume to the ActorPool
void AInfiniteTerrainGameMode::AddToPool(AVolume *NavMeshBV)
{
	if (NavMeshBV != nullptr)
	{
		//		UE_LOG(LogTemp, Warning, TEXT("Determing whether to add to pool %s."), *NavMeshBV->GetName());
		FString VolumeName = *NavMeshBV->GetName();
		if (VolumeName.Contains(FString("NavMesh"), ESearchCase::CaseSensitive, ESearchDir::FromStart))
		{
			UE_LOG(LogTemp, Warning, TEXT("Adding to pool %s."), *NavMeshBV->GetName());
			
			NavMeshVolumeActorPool->Add(NavMeshBV);
		}
	}

}