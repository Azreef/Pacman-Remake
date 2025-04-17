

#include "C_Clyde.h"

FVector2D AC_Clyde::CalculateChaseTargetGrid()
{     
    float currentDistance = FVector2D::Distance(_CurrentGridPosition, _PacManPointer->_CurrentGridPosition);

    if (currentDistance > 8)
    {
        return _PacManPointer->_CurrentGridPosition;
    }
    else
    {
        return _ScatterGridCoordinate;
    }
   
}