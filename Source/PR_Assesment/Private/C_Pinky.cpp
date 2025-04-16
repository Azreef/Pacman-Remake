

#include "C_Pinky.h"

FVector2D AC_Pinky::GetTargetTile(TArray<FVector2D>& availableDirection)
{       
    return GetDirectTileTo(_PacManPointer->_CurrentGridPosition + (_PacManPointer->_MovingDirection * 4), availableDirection);
}