

#include "C_Blinky.h"

FVector2D AC_Blinky::GetChaseGridStep(TArray<FVector2D>& availableDirection)
{       
    _CurrentTargetGridPosition = _PacManPointer->_CurrentGridPosition;

    return GetNextGridStep(_CurrentTargetGridPosition, availableDirection);
}


                