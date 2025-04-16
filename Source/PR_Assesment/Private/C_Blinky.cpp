

#include "C_Blinky.h"

FVector2D AC_Blinky::GetTargetTile(TArray<FVector2D>& availableDirection)
{       
    return GetDirectTileTo(_PacManPointer->_CurrentGridPosition, availableDirection);
}