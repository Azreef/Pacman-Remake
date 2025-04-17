

#include "C_Pinky.h"


FVector2D AC_Pinky::CalculateChaseTargetGrid()
{
    FVector2D targetGridPosition = _PacManPointer->_CurrentGridPosition + (_PacManPointer->_MovingDirection * 4);

    return targetGridPosition;

}
