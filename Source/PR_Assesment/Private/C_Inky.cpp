

#include "C_Inky.h"
#include "C_Blinky.h"

void AC_Inky::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!_BlinkyPointer && _CurrentBlinkySearchTime < _BlinkySearchTimeoutTime)
    {
        _CurrentBlinkySearchTime += DeltaTime;

      
        GetBlinkyPointer();
    }
    else if (_CurrentBlinkySearchTime >= _BlinkySearchTimeoutTime)
    {
        if (GEngine)
            GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, "INKY: CANNOT FIND BLINKY");
    }
}

AC_Inky::AC_Inky()
{
    E_GhostType _GhostType = E_GhostType::Inky;
}


FVector2D AC_Inky::CalculateChaseTargetGrid()
{       
    if (_BlinkyPointer)
    {
        FVector2D inkyTarget = _PacManPointer->_CurrentGridPosition + (_PacManPointer->_MovingDirection * 2); //Get 2 Grid ahead of Packman

        inkyTarget = inkyTarget - _BlinkyPointer->_CurrentGridPosition ; //Get Vector from Previous target to Blinky

        inkyTarget = _BlinkyPointer->_CurrentGridPosition + (inkyTarget * 2); //Double Previous Vector

        return inkyTarget;
    }
    else
    {
        return FVector2D::ZeroVector;
    }

}


void AC_Inky::GetBlinkyPointer()
{
    AActor* foundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AC_Blinky::StaticClass());
    _BlinkyPointer = Cast<AC_Blinky>(foundActor);

}
