// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "E_GhostStateEnum.generated.h"

/**
 * 
 */

UENUM()
enum class E_GhostStateEnum : uint8
{
	Chase,
	Scatter,
};
