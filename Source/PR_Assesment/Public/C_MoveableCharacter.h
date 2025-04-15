// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "C_MoveableCharacter.generated.h"

UCLASS()
class PR_ASSESMENT_API AC_MoveableCharacter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AC_MoveableCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
	void MoveTowards(FVector2D direction);

	//void UpdateMovement(float deltaTime);
	virtual void UpdateMovement(float deltaTime);

	FVector2D ConvertWorldToGrid(FVector worldLocation);
	FVector ConvertGridToWorld(FVector2D gridLocation);
	void SetMazeGrid(TArray<TArray<bool>>& mazeGrid);
	bool CheckWalkableGrid(FVector2D gridLocation);
	void RotateCharacter(FVector2D direction);

	FVector2D _CurrentGridPosition;
	FVector2D _TargetGridPosition;
	FVector2D _MovingDirection = FVector2D(1, 0);
	float _TileSize = 100;
	float _MoveSpeed = 500;
	FVector2D _PreviousMoveDirection;

	//SAVE DIRECTION VALUE, TEMP  DONT FORGET TO CHANGE TO ENUM LATER
	const TArray<FVector2D> _Directions = {
	   FVector2D(0, -1), // Up is -1 because how Y increases downward
	   FVector2D(0, 1),  // Down
	   FVector2D(-1, 0), // Left
	   FVector2D(1, 0)   // Right
	};

	TArray <TArray<bool>> _MazeGrid; //Stores Generated Grid [true - can walk | false - cannot walk (has walls)]


};
