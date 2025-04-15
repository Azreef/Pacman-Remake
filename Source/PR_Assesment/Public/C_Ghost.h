// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "C_MoveableCharacter.h"
#include "C_Ghost.generated.h"

/**
 * 
 */
UCLASS()
class PR_ASSESMENT_API AC_Ghost : public AC_MoveableCharacter
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FVector2D GetTargetTile();

	bool CheckAvailableIntersection(bool isIgnoringDirection, TArray<FVector2D>& availableDirection);


	FVector2D GetClosestPathTile(TArray<FVector2D>& availableDirection); //Is Blinky Behaviour

	AC_MoveableCharacter* GetPacManPointer();
	
	void UpdateDirection();

	AC_MoveableCharacter* _PacManPointer;


	float _MoveInterval = 0.5f;

	FTimerHandle _MoveTimer;
};
