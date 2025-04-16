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
};

UENUM()
enum class E_ScatterZone : uint8
{
	TopLeft,
	TopRight,
	BottomLeft,
	BottomRight,
};