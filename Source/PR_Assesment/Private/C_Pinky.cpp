

#include "C_Pinky.h"

AC_Pinky::AC_Pinky()
{
    E_GhostType _GhostType = E_GhostType::Pinky;
}
FVector2D AC_Pinky::CalculateChaseTargetGrid()
{
    FVector2D targetGridPosition = _PacManPointer->_CurrentGridPosition + (_PacManPointer->_MovingDirection * 4);

    return targetGridPosition;


}
