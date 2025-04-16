


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

	//initialise position
	_TargetGridPosition = ConvertWorldToGrid(GetActorLocation());
	_CurrentGridPosition = ConvertWorldToGrid(GetActorLocation());
	

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


void AC_MoveableCharacter::UpdateMovement(float deltaTime)
{
	FVector currentPosition = GetActorLocation();
	_CurrentGridPosition = ConvertWorldToGrid(currentPosition);

	if (!GetActorLocation().Equals(ConvertGridToWorld(_TargetGridPosition), 1))
	{
		FVector newPosition = FMath::VInterpConstantTo(currentPosition, ConvertGridToWorld(_TargetGridPosition), deltaTime, 300);
		SetActorLocation(newPosition);
	}
	
	FVector2D nextGrid = _CurrentGridPosition + _MovingDirection;
	if (!_MovingDirection.IsZero())
	{
		if (CheckWalkableGrid(nextGrid))
		{
			_TargetGridPosition = nextGrid;
			_PreviousMoveDirection = _MovingDirection;
			RotateCharacter(_MovingDirection);
		}
		else
		{
			
			_MovingDirection = _PreviousMoveDirection;
		}
	}

}

void AC_MoveableCharacter::MoveUp()
{
	_MovingDirection = FVector2D(0, -1);
}

void AC_MoveableCharacter::MoveDown()
{
	_MovingDirection = FVector2D(0, 1);
}

void AC_MoveableCharacter::MoveRight()
{
	_MovingDirection = FVector2D(1, 0);
}

void AC_MoveableCharacter::MoveTowards(FVector2D direction)
{
	_MovingDirection = direction;
}

void AC_MoveableCharacter::MoveLeft()
{
	_MovingDirection = FVector2D(-1, 0);
}


void AC_MoveableCharacter::SetTileSize(float tileSize)
{
	_TileSize = tileSize;
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

void AC_MoveableCharacter::RotateCharacter(FVector2D direction)
{
	FVector convertedDirection = FVector(direction.X, direction.Y, 0);
	FRotator lookRotation = convertedDirection.Rotation();
	SetActorRotation(lookRotation);
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
