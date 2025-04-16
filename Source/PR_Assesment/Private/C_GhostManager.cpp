// Fill out your copyright notice in the Description page of Project Settings.


#include "C_GhostManager.h"

// Sets default values
AC_GhostManager::AC_GhostManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AC_GhostManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_GhostManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC_GhostManager::UpdateAllGhostState(E_GhostState)
{
	for (AC_Ghost* currentGhost : _GhostList)
	{
		currentGhost->SetState(_CurrentGhostState);
	}

}

void AC_GhostManager::AddToGhostList(AC_Ghost* newGhost)
{
	
	if (!_GhostList.Contains(newGhost))
	{
		_GhostList.Add(newGhost);
	}
	else
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Ghost Already Exit is GhostList!");
	}
}

