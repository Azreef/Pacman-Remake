// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "E_MazeEnum.h"
#include "F_MazeStruct.generated.h"

/**
 * 
 */

USTRUCT()
struct F_GridData
{
	GENERATED_BODY()

	E_TileType tileType;
	bool isWalkable = false;
	

};

