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

	void UpdateDirection();

	virtual FVector2D GetTargetTile(TArray<FVector2D>& availableDirection);
	bool CheckAvailableIntersection(bool isIgnoringDirection, TArray<FVector2D>& availableDirection);
	AC_MoveableCharacter* GetPacManPointer();
	
	
	AC_MoveableCharacter* _PacManPointer;

};
