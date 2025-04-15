// Fill out your copyright notice in the Description page of Project Settings.


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

        //GetWorldTimerManager().SetTimer(_MoveTimer, this, &AGhostAI::MoveToNextTile, _MoveInterval, true);

    }
}

void AC_Ghost::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (_PacManPointer)
    {
        
       UpdateDirection();
       
    }
}


void AC_Ghost::UpdateDirection()
{
    TArray<FVector2D> availableDirection;

   
    if (CheckAvailableIntersection(true, availableDirection) && _LatestIntersectionGrid != _CurrentGridPosition)
    {

        //GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("HAS INTERSECTION"));
        //if (GEngine)
        //    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, _CurrentGridPosition.ToString()); 
        ////Ghost is at Intersection
        if (_MovingDirection != GetTargetTile(availableDirection))
        {
            MoveTowards(GetTargetTile(availableDirection));
            GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "CHANGE DIRECTION: " + _MovingDirection.ToString());
            _LatestIntersectionGrid = _CurrentGridPosition;
        }
        
        
    }

}


FVector2D AC_Ghost::GetTargetTile(TArray<FVector2D>& availableDirection)
{
    return FVector2D();
}

bool AC_Ghost::CheckAvailableIntersection(bool isIgnoringOppositeDirection, TArray<FVector2D>& availableDirection)
{
    availableDirection.Empty();

   /* FVector2D currentGridPosition = _CurrentGridPosition;
    FVector2D currentMovingPosition = _MovingDirection;*/

    bool isAtIntersection = false;


   /* GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "=========================================");
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "GRID: " + currentGridPosition.ToString());
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Direction: " + currentMovingPosition.ToString());*/

    //UE_LOG(LogTemp, Warning, TEXT("========================================"));
    //UE_LOG(LogTemp, Warning,  currentGridPosition.ToString());

    for (const FVector2D& currentDirection : _Directions)
    {

        //FIntPoint NewIndex = CurrentIndex + Dir;
        FVector2D nextGrid = _CurrentGridPosition + currentDirection;

        if (CheckWalkableGrid(nextGrid))
        {
            // Ignore reverse direction
            if (currentDirection.Equals(-_MovingDirection, 0.01f) && isIgnoringOppositeDirection)
            {
                /*if (GEngine)
                    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "ignore" + currentDirection.ToString());*/
                continue;
            }
            else
            {
                availableDirection.Add(currentDirection);
                //GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Added: " + currentDirection.ToString());
            }
        }
    }
    //GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "=========================================" );
    /*if (GEngine)
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "IS AT INTERSECTION: " + FString::Printf(TEXT("%d"), availableDirection.Num()));*/

    if (availableDirection.Num() >= 1)
    {
        isAtIntersection = true;
        //GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "IS AT INTERSECTION: " + FString::Printf(TEXT("%d"), availableDirection.Num()));
       
    }
    return isAtIntersection;
}


AC_MoveableCharacter* AC_Ghost::GetPacManPointer()
{
    AActor* foundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AC_PacManCharacter::StaticClass());
    return Cast<AC_MoveableCharacter>(foundActor);

}

