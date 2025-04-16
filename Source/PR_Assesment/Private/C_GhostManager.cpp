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

	if (_GhostTimerHandle.IsValid() && GetWorldTimerManager().TimerExists(_GhostTimerHandle) && GetWorldTimerManager().IsTimerActive(_GhostTimerHandle) && _IsTimerInitialized)
	{
		if (GEngine)
		{
			FString timeDebugString = UEnum::GetValueAsString(_CurrentGlobalGhostState)+ ": " + FString::SanitizeFloat(GetWorldTimerManager().GetTimerRemaining(_GhostTimerHandle));
			GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Green, timeDebugString);
		}
	}
}

void AC_GhostManager::StartPhase()
{
	float timeToSet = 0;

	if (_CurrentGlobalGhostState == E_GhostState::Scatter) //Switch Mode to Chase
	{
		_CurrentGlobalGhostState = E_GhostState::Chase;
		timeToSet = _PhaseDurationList[_CurrentPhaseLevel].chaseDuration;
		UpdateAllGhostState(E_GhostState::Chase);

	}
	else if (_CurrentGlobalGhostState == E_GhostState::Chase) //Switch Mode to Scatter
	{
		_CurrentGlobalGhostState = E_GhostState::Scatter;
		timeToSet = _PhaseDurationList[_CurrentPhaseLevel].scatterDuration;
		UpdateAllGhostState(E_GhostState::Scatter);

		_CurrentPhaseLevel++;
	}

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::SanitizeFloat(timeToSet));

	GetWorldTimerManager().SetTimer(_GhostTimerHandle, this, &AC_GhostManager::StartPhase, timeToSet, true);

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "CHANGING MODE TO " + UEnum::GetValueAsString(_CurrentGlobalGhostState));

	_IsTimerInitialized = true;		

}

void AC_GhostManager::UpdateAllGhostState(E_GhostState)
{
	for (AC_Ghost* currentGhost : _GhostList)
	{
		currentGhost->SetState(_CurrentGlobalGhostState,true);
	}

}

void AC_GhostManager::AddToGhostList(AC_Ghost* newGhost)
{
	if (newGhost)
	{		
		if (!_GhostList.Contains(newGhost))
		{
			_GhostList.Add(newGhost);
		}
		else
		{
			if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "GHOST MANAGER: Ghost Already Exist is GhostList!");
		}
	}
	else
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "GHOST MANAGER: NEW GHOST POINTER IS NULL");
	}
	
}

