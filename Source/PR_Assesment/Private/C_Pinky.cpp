

#include "C_Pinky.h"


FVector2D AC_Pinky::GetChaseGridStep(TArray<FVector2D>& availableDirection)
{
    FVector2D targetGridPosition = _PacManPointer->_CurrentGridPosition + (_PacManPointer->_MovingDirection * 4);


    if (_IsDebugModeEnabled)
    {
        DrawDebug(targetGridPosition, FColor::Red);
    }
    
    
    return GetNextGridStep(targetGridPosition, availableDirection);


}

FVector2D AC_Pinky::GetScatterGridStep(TArray<FVector2D>& availableDirection)
{
    return FVector2D();
}
