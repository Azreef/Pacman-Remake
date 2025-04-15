// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "C_MoveableCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "C_PacManCharacter.generated.h"

UCLASS()
class PR_ASSESMENT_API AC_PacManCharacter : public AC_MoveableCharacter
{
	GENERATED_BODY()
	
protected:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(EditAnywhere)
	UInputAction* _MoveInputAction;

	UPROPERTY(EditAnywhere)
	UInputMappingContext* _MappingContext;

	void Move(const FInputActionValue& Value);

};
