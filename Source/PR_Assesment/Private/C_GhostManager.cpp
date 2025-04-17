// Fill out your copyright notice in the Description page of Project Settings.


#include "C_GhostManager.h"
#include "C_Ghost.h"

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

	if (CheckIfAnyGhostInHouse())
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Green, FString("Ghost Release Timer: ") + FString::SanitizeFloat(_CurrentGhostHouseTime));

		if (_CurrentGhostHouseTime >= _MaxGhostHouseTime)
		{
			ReleaseGhost();
			GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Green, "RELEASING GHOST");
		}
		else
		{
			_CurrentGhostHouseTime += DeltaTime;
		}
	}
	else
	{
		_CurrentGhostHouseTime = 0;
	}

}

void AC_GhostManager::StartPhase()
{
	float timeToSet = 0;

	if (_CurrentGlobalGhostState == E_GhostState::Scatter) //Switch Mode to Chase
	{
		_CurrentGlobalGhostState = E_GhostState::Chase;
		timeToSet = _PhaseDurationList[_CurrentPhaseLevel].chaseDuration;
		UpdateAllGhostState(E_GhostState::Chase, false);

	}
	else if (_CurrentGlobalGhostState == E_GhostState::Chase) //Switch Mode to Scatter
	{
		_CurrentGlobalGhostState = E_GhostState::Scatter;
		timeToSet = _PhaseDurationList[_CurrentPhaseLevel].scatterDuration;
		UpdateAllGhostState(E_GhostState::Scatter, false);

		_CurrentPhaseLevel++;
	}

	GetWorldTimerManager().SetTimer(_GhostTimerHandle, this, &AC_GhostManager::StartPhase, timeToSet, true);

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "CHANGING MODE TO " + UEnum::GetValueAsString(_CurrentGlobalGhostState));

	_IsTimerInitialized = true;		

}

void AC_GhostManager::UpdateAllGhostState(E_GhostState newGhostState, bool isIncludingGhostAtHome)
{
	for (AC_Ghost* currentGhost : _GhostList)
	{
		if (isIncludingGhostAtHome) //Update all ghost Including one at Home
		{
			currentGhost->SetState(newGhostState, true);
		}
		else //Set only outside Home
		{
			if (!((*currentGhost)._CurrentState == E_GhostState::AtHome))
			{
				currentGhost->SetState(newGhostState, true);
			}
		}
		
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

bool AC_GhostManager::CheckIfAnyGhostInHouse()
{
	bool IsGhostInsideHouse = false;

	for (AC_Ghost* currentGhost : _GhostList)
	{
		if ((*currentGhost)._CurrentState == E_GhostState::AtHome)
		{
			IsGhostInsideHouse = true;
		}
	}

	return IsGhostInsideHouse;
}

void AC_GhostManager::ReleaseGhost()
{
	//Release based on priority (Pinky -> Inky -> Clyde)
	for (AC_Ghost* currentGhost : _GhostList)
	{
		if ((*currentGhost)._CurrentState == E_GhostState::AtHome)
		{
			if ((*currentGhost)._GhostType == E_GhostType::Blinky)
			{
				(*currentGhost).SetState(E_GhostState::ExitingHome, false);
				break;
			}
			else if ((*currentGhost)._GhostType == E_GhostType::Pinky)
			{
				(*currentGhost).SetState(E_GhostState::ExitingHome, false);
				break;
			}
			else if ((*currentGhost)._GhostType == E_GhostType::Inky)
			{
				(*currentGhost).SetState(E_GhostState::ExitingHome, false);
				break;
			}
			else if ((*currentGhost)._GhostType == E_GhostType::Clyde)
			{
				(*currentGhost).SetState(E_GhostState::ExitingHome, false);
				break;
			}
		}
	}

	_CurrentGhostHouseTime = 0;
}

