

#include "C_Blinky.h"

AC_Blinky::AC_Blinky()
{
    E_GhostType _GhostType = E_GhostType::Blinky;
}

FVector2D AC_Blinky::CalculateChaseTargetGrid()
{       
   
    return _PacManPointer->_CurrentGridPosition;;
}


                