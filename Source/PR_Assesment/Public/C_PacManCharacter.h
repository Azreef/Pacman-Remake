

#pragma once

#include "CoreMinimal.h"
#include "C_MoveableCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "I_Collectable.h"
#include "C_PacManCharacter.generated.h"

class UCapsuleComponent;

UCLASS()
class PR_ASSESMENT_API AC_PacManCharacter : public AC_MoveableCharacter
{
	GENERATED_BODY()
	
protected:
	
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
	virtual void BeginPlay() override;

public:
	
	AC_PacManCharacter();
	virtual void Tick(float DeltaTime);
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* _MoveInputAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* _ToggleDebugInputAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* _MappingContext;

	void MoveInput(const FInputActionValue& Value);
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)override;
	void NotifyActorBeginOverlap(AActor* OtherActor);
	void ToggleDebug(const FInputActionValue& movementValue);
	FVector2D _IntendedDirection;


	UPROPERTY(EditAnywhere, Category = "Movement", meta = (ToolTip = "How long does the input stays (Used to Simulate Cornering)"))
	float _IntendedDirectionDuration = 0.5;

	float _IntendedDirectionTimer = 0;

	UPROPERTY(VisibleAnywhere, Category = "Collision")
	UCapsuleComponent* TriggerCapsule;
};
