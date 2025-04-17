
#pragma once

#include "CoreMinimal.h"
#include "C_Ghost.h"
#include "C_Clyde.generated.h"

UCLASS()
class PR_ASSESMENT_API AC_Clyde : public AC_Ghost
{
	GENERATED_BODY()
	
protected:
	FVector2D CalculateChaseTargetGrid();
};
