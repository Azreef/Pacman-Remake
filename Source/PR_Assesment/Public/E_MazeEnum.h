// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "E_MazeEnum.generated.h"

/**
 * 
 */

UENUM()
enum class E_TileType : uint8
{
	Empty,
	Door,
	Wall,
	Teleporter,

};

