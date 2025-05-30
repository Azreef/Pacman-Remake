// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "E_GhostEnum.generated.h"

/**
 * 
 */

UENUM()
enum class E_GhostState : uint8
{
	Chase,
	Scatter,
	AtHome,
	ExitingHome,
};

UENUM()
enum class E_GhostType : uint8
{
	Blinky,
	Pinky,
	Inky,
	Clyde,
};

UENUM()
enum class E_ScatterZone : uint8
{
	TopLeft,
	TopRight,
	BottomLeft,
	BottomRight,
};