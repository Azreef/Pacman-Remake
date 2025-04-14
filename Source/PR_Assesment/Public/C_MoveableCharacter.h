// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
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

	void UpdateMovement(float deltaTime);
	FVector2D ConvertWorldToGrid(FVector worldLocation);
	FVector ConvertGridToWorld(FVector2D gridLocation);

	FVector2D _CurrentGridPosition;
	FVector2D _TargetGridPosition;
	FVector2D _MovingDirection;
	float _TileSize = 100;
	float _MoveSpeed = 500;


};
