
#pragma once

#include "CoreMinimal.h"
#include "C_Ghost.h"
#include "C_Blinky.generated.h"

UCLASS()
class PR_ASSESMENT_API AC_Blinky : public AC_Ghost
{
	GENERATED_BODY()
	
protected:
	FVector2D GetTargetTile(TArray<FVector2D>& availableDirection); //Set Target to Player Directly
};
