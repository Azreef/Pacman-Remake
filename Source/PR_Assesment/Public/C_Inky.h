
#pragma once

#include "CoreMinimal.h"
#include "C_Ghost.h"
#include "C_Blinky.h"
#include "C_Inky.generated.h"

UCLASS()
class PR_ASSESMENT_API AC_Inky : public AC_Ghost
{
	GENERATED_BODY()
	
protected:
	FVector2D GetTargetTile(TArray<FVector2D>& availableDirection); //Set Target to Player Directly

	float _CurrentBlinkySearchTime = 0;
	AC_Blinky* _BlinkyPointer;

public:
	virtual void Tick(float DeltaTime) override;

	void GetBlinkyPointer();

	UPROPERTY(EditAnywhere, Category = "Inky", meta = (ToolTip = "How long before timeout in searching Blinky (in Seconds)"))
	float _BlinkySearchTimeoutTime = 60;

	

};
