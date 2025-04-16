

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
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* _MoveInputAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* _MappingContext;

	void MoveInput(const FInputActionValue& Value);

};
