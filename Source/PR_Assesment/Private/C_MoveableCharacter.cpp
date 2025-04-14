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

void AC_MoveableCharacter::MoveUp()
{
	_MovingDirection = FVector2D(0, 1);
}

void AC_MoveableCharacter::MoveDown()
{
	_MovingDirection = FVector2D(0, -1);
}

void AC_MoveableCharacter::MoveRight()
{
	_MovingDirection = FVector2D(1, 0);
}

void AC_MoveableCharacter::MoveLeft()
{
	_MovingDirection = FVector2D(-1, 0);
}


void AC_MoveableCharacter::UpdateMovement(float deltaTime)
{
	FVector currentPosition = GetActorLocation();
	_CurrentGridPosition = ConvertWorldToGrid(currentPosition);


	/*GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "ACTOR LOC:" + GetActorLocation().ToString());
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "TARGET LOC:" + ConvertGridToWorld(_TargetGridPosition).ToString());*/

	if (!GetActorLocation().Equals(ConvertGridToWorld(_TargetGridPosition), 1))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "MOVING");
		
		FVector newPosition = FMath::VInterpConstantTo(currentPosition, ConvertGridToWorld(_TargetGridPosition), deltaTime, _MoveSpeed);
		
		SetActorLocation(newPosition);
	}
	
	if (!_MovingDirection.IsZero())
	{
		 _TargetGridPosition = _CurrentGridPosition + _MovingDirection;

		//_MovingDirection = FVector2D::ZeroVector;
	}

}

FVector2D AC_MoveableCharacter::ConvertWorldToGrid(FVector worldLocation) //Used to Convert World Position to Grid Position, FVector2D to FVector
{
	FVector2D gridPosition = FVector2D(FMath::RoundToInt(worldLocation.X / _TileSize), FMath::RoundToInt(worldLocation.Y/ _TileSize));
	
	return gridPosition;
}

FVector AC_MoveableCharacter::ConvertGridToWorld(FVector2D gridLocation) //Used to Convert Grid Position to World Position, FVector to FVector2D
{
	return FVector(gridLocation.X * _TileSize, gridLocation.Y * _TileSize, 0);
}

