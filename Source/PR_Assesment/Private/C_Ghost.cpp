


#include "C_Ghost.h"
#include "C_PacManCharacter.h"

void AC_Ghost::BeginPlay()
{
    Super::BeginPlay();
    _PacManPointer = GetPacManPointer();

    if (!_PacManPointer)
    {
        if (GEngine)
            GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("ERROR: CANNOT FIND PACMAN"));

    }
}

void AC_Ghost::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (_PacManPointer)
    {
        if (_IsDebugModeEnabled)
        {
            DrawDebug(_CurrentTargetGridPosition, _DebugColor);

            //DEBUG HERE
        }
        
          

        if (CalculatePossiblePath(true, _AvailableDirection) && _LatestIntersectionGrid != _CurrentGridPosition)
        {
            if (_CurrentFrameCount >= _GhostTurnWaitFrame)
            {
                UpdateDirection();
                _CurrentFrameCount = 0;
            }
            else
            {
                _CurrentFrameCount++;
            }
             
        }
        else if (!CalculatePossiblePath(true, _AvailableDirection))
        {
            if (GEngine)
                GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "No Path Found!");
        }

    }
}

void AC_Ghost::UpdateDirection()
{
        FVector2D nextDirection = FVector2D::ZeroVector;
        
        if (_CurrentState == E_GhostState::Chase)//Chase Mode
        {
            _CurrentTargetGridPosition = CalculateChaseTargetGrid();

            nextDirection = CalculateNextGridStep(_CurrentTargetGridPosition, _AvailableDirection);
        }
        else if (_CurrentState == E_GhostState::Scatter)//Scatter Mode
        {
           
            _CurrentTargetGridPosition = _ScatterGridCoordinate;
                       
            nextDirection = CalculateNextGridStep(_CurrentTargetGridPosition, _AvailableDirection);
        }

        MoveTowards(nextDirection);
        _LatestIntersectionGrid = _CurrentGridPosition;

    
    
}

FVector2D AC_Ghost::CalculateChaseTargetGrid()
{
    return FVector2D();
}

FVector2D AC_Ghost::CalculateNextGridStep(FVector2D targetGridCoordinate, TArray<FVector2D>& availableDirection)
{
    float shortestDistance = 100;
    FVector2D bestDirection = _MovingDirection;


    for (FVector2D& currentDirection : availableDirection)
    {
        float currentDistance = FVector2D::Distance(currentDirection + _CurrentGridPosition, targetGridCoordinate);


        if (currentDistance < shortestDistance)
        {
            bestDirection = currentDirection;
            shortestDistance = currentDistance;
        }

    }

    return bestDirection;
}


bool AC_Ghost::CalculatePossiblePath(bool isIgnoringOppositeDirection, TArray<FVector2D>& availableDirection)
{
    availableDirection.Empty();

    bool isPossiblePathExist = false;

    for (const FVector2D& currentDirection : _Directions)
    {

        //FIntPoint NewIndex = CurrentIndex + Dir;
        FVector2D nextGrid = _CurrentGridPosition + currentDirection;

        if (CheckWalkableGrid(nextGrid))
        {
            // Ignore reverse direction
            if (currentDirection.Equals(-_MovingDirection, 0.01f) && isIgnoringOppositeDirection)
            {
                
                continue;
            }
            else
            {
                availableDirection.Add(currentDirection);
               
            }
        }
    }
   

    if (availableDirection.Num() >= 1)
    {
        isPossiblePathExist = true;
   
    }
    return isPossiblePathExist;
}

void AC_Ghost::DrawDebug(FVector2D targetCoordinate, FColor debugColour)        
{

    DrawDebugSphere(GetWorld(), ConvertGridToWorld(targetCoordinate), 30, 10, debugColour, false, 0, 0, 10);
    DrawDebugLine(GetWorld(), GetActorLocation(), ConvertGridToWorld(targetCoordinate), debugColour, false, 0, -1, 10);
}
        

AC_MoveableCharacter* AC_Ghost::GetPacManPointer()
{
    AActor* foundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AC_PacManCharacter::StaticClass());
    return Cast<AC_MoveableCharacter>(foundActor);

}

void AC_Ghost::SetState(E_GhostState newState, bool shouldChangeDirection)
{
    _CurrentState = newState;

    if (shouldChangeDirection)//Also Reverse Moving Direction
    {
        _MovingDirection = -_MovingDirection; 
    }
    
    
}

