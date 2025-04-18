


#include "C_PacManCharacter.h"
#include "C_GameManager.h"


void AC_PacManCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (_IntendedDirectionTimer <= _IntendedDirectionDuration)
	{
		MoveTowards(_IntendedDirection);
		_IntendedDirectionTimer = _IntendedDirectionTimer + DeltaTime;
	}
	else if ((_IntendedDirectionTimer > _IntendedDirectionDuration))
	{
		_IntendedDirection = _PreviousMoveDirection;
		MoveTowards(_IntendedDirection);

	}
}


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
		EnhancedInputComponent->BindAction(_ToggleDebugInputAction, ETriggerEvent::Triggered, this, &AC_PacManCharacter::ToggleDebug);
	}
	
}

void AC_PacManCharacter::ToggleDebug(const FInputActionValue& movementValue)
{
	_GameManager->_IsDebugModeEnabled = !_GameManager->_IsDebugModeEnabled;
}

void AC_PacManCharacter::MoveInput(const FInputActionValue& movementValue)
{
	
	FVector2D moveDirection = movementValue.Get<FVector2D>();

	if (moveDirection.X > 0.5f)
	{
		_IntendedDirection = FVector2D(1, 0);
		// Move Right
		
	}
	else if (moveDirection.X < -0.5f)
	{
		// Move Left
		_IntendedDirection = FVector2D(-1, 0);
		
	}
	else if (moveDirection.Y > 0.5f)
	{
		// Move Up
		_IntendedDirection = FVector2D(0, -1);
		
	}
	else if (moveDirection.Y < -0.5f)
	{
		// Move Down
		_IntendedDirection = FVector2D(0, 1);
		
	}

	_IntendedDirectionTimer = 0;

}
