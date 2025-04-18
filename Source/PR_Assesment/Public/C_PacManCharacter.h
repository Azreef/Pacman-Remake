

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
	virtual void Tick(float DeltaTime);
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* _MoveInputAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* _ToggleDebugInputAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* _MappingContext;

	void MoveInput(const FInputActionValue& Value);
	void ToggleDebug(const FInputActionValue& movementValue);
	FVector2D _IntendedDirection;


	UPROPERTY(EditAnywhere, Category = "Movement", meta = (ToolTip = "Used to Simulate Cornering (moving the joystick in the direction one wishes to go well before reaching the center of a turn)"))
	float _IntendedDirectionDuration = 0.2;

	float _IntendedDirectionTimer = 0;
};
