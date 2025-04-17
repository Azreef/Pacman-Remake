
#pragma once

#include "CoreMinimal.h"
#include "C_Ghost.h"
#include "C_Blinky.generated.h"

UCLASS()
class PR_ASSESMENT_API AC_Blinky : public AC_Ghost
{
	GENERATED_BODY()
	
protected:
	FVector2D CalculateChaseTargetGrid();

public:
	AC_Blinky();
};
