

#include "C_Clyde.h"

FVector2D AC_Clyde::GetTargetTile(TArray<FVector2D>& availableDirection)
{     
    float currentDistance = FVector2D::Distance(_CurrentGridPosition, _PacManPointer->_CurrentGridPosition);

    if (currentDistance > 8)
    {
        return GetDirectTileTo(_PacManPointer->_CurrentGridPosition, availableDirection);
    }
    else
    {
        return GetDirectTileTo(_ScatterGridCoordinate, availableDirection);
    }
   
}