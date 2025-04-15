// Fill out your copyright notice in the Description page of Project Settings.


#include "C_MoveableCharacter.h"


// Sets default values
AC_MoveableCharacter::AC_MoveableCharacter()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AC_MoveableCharacter::BeginPlay()
{
	Super::BeginPlay();

	_TargetGridPosition = ConvertWorldToGrid(GetActorLocation());
	_CurrentGridPosition = ConvertWorldToGrid(GetActorLocation());
	
	//GetWorld()->GetTimerManager().SetTimer(_MoveTimer, this, &AC_MoveableCharacter::UpdateMovement, _MoveInterval, true);

}

// Called every frame
void AC_MoveableCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateMovement(DeltaTime);
}

// Called to bind functionality to input
void AC_MoveableCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

//void AC_MoveableCharacter::UpdateMovement(float deltaTime)

void AC_MoveableCharacter::UpdateMovement(float deltaTime)
{
	FVector currentPosition = GetActorLocation();
	_CurrentGridPosition = ConvertWorldToGrid(currentPosition);

	/*if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("%f"), currentDistance));*/

	
	if (!GetActorLocation().Equals(ConvertGridToWorld(_TargetGridPosition), 1))
	{
		FVector newPosition = FMath::VInterpConstantTo(currentPosition, ConvertGridToWorld(_TargetGridPosition), deltaTime, 300);
		SetActorLocation(newPosition);
		//SetActorLocation(ConvertGridToWorld(_TargetGridPosition));
		//_CurrentGridPosition = _TargetGridPosition;
		//_CurrentGridPosition = _TargetGridPosition;
	}
	
	FVector2D nextGrid = _CurrentGridPosition + _MovingDirection;
	if (!_MovingDirection.IsZero())
	{
		if (CheckWalkableGrid(nextGrid))
		{
			_TargetGridPosition = nextGrid;
			_PreviousMoveDirection = _MovingDirection;
		}
		else
		{
			//_TargetGridPosition = _CurrentGridPosition;
			_MovingDirection = _PreviousMoveDirection;
		}
	}

	if (GEngine)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "CURRENT: " + _CurrentGridPosition.ToString());
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, "TARGET: " + _TargetGridPosition.ToString());
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, "PrevMove: " + _PreviousMoveDirection.ToString());
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "CURRENT: " + _MovingDirection.ToString());
	}




}



void AC_MoveableCharacter::MoveUp()
{
	//_PreviousMoveDirection = _MovingDirection;
	_MovingDirection = FVector2D(0, -1);
}

void AC_MoveableCharacter::MoveDown()
{
	//_PreviousMoveDirection = _MovingDirection;
	_MovingDirection = FVector2D(0, 1);
}

void AC_MoveableCharacter::MoveRight()
{
	//_PreviousMoveDirection = _MovingDirection;
	_MovingDirection = FVector2D(1, 0);
}

void AC_MoveableCharacter::MoveTo(FVector2D direction)
{
	//_PreviousMoveDirection = _MovingDirection;
	_MovingDirection = direction;
}

void AC_MoveableCharacter::MoveLeft()
{
	//_PreviousMoveDirection = _MovingDirection;
	_MovingDirection = FVector2D(-1, 0);
}


void AC_MoveableCharacter::SetMazeGrid(TArray<TArray<bool>>& mazeGrid)
{
	_MazeGrid = mazeGrid;

	//DEBUG
	for (int32 Y = 0; Y < _MazeGrid.Num(); Y++)
	{
		FString RowString;

		for (int32 X = 0; X < _MazeGrid[Y].Num(); X++)
		{
			RowString += _MazeGrid[Y][X] ? TEXT("1 ") : TEXT("0 ");
		}

		UE_LOG(LogTemp, Warning, TEXT("%s"), *RowString);
	}

}

bool AC_MoveableCharacter::CheckWalkableGrid(FVector2D gridLocation)
{
	return _MazeGrid[gridLocation.X][gridLocation.Y];
}

FVector2D AC_MoveableCharacter::ConvertWorldToGrid(FVector worldLocation) //Used to Convert World Position to Grid Position, FVector2D to FVector
{
	FVector2D gridPosition = FVector2D(FMath::RoundToInt(worldLocation.X / _TileSize), FMath::RoundToInt(worldLocation.Y / _TileSize));

	return gridPosition;
}

FVector AC_MoveableCharacter::ConvertGridToWorld(FVector2D gridLocation) //Used to Convert Grid Position to World Position, FVector to FVector2D
{
	return FVector(gridLocation.X * _TileSize, gridLocation.Y * _TileSize, 0);
}
