// Fill out your copyright notice in the Description page of Project Settings.


#include "C_PacManCharacter.h"


void AC_PacManCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//Set up Mapping Context
	APlayerController* playerController = Cast<APlayerController>(GetController());
	if (playerController)
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer());

		if (Subsystem && _MappingContext)
		{
			Subsystem->AddMappingContext(_MappingContext, 0);
		}
	}
	

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(_MoveInputAction, ETriggerEvent::Triggered, this, &AC_PacManCharacter::MoveInput);
	}
	
}

void AC_PacManCharacter::MoveInput(const FInputActionValue& movementValue)
{
	
	FVector2D moveDirection = movementValue.Get<FVector2D>();

	if (moveDirection.X > 0.5f)
	{
		// Move Right
		MoveRight();
	}
	else if (moveDirection.X < -0.5f)
	{
		// Move Left
		MoveLeft();
	}
	else if (moveDirection.Y > 0.5f)
	{
		// Move Up
		MoveUp();
	}
	else if (moveDirection.Y < -0.5f)
	{
		// Move Down
		MoveDown();
	}

}
