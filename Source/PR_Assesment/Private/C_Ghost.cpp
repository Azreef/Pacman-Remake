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

    if (CheckAvailableIntersection(false, availableDirection))
    {

        //GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("HAS INTERSECTION"));
        //if (GEngine)
        //    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, _CurrentGridPosition.ToString()); 
        ////Ghost is at Intersection

        MoveTo(GetTargetTile(availableDirection));


    }

}


FVector2D AC_Ghost::GetTargetTile(TArray<FVector2D>& availableDirection)
{
    return FVector2D();
}

bool AC_Ghost::CheckAvailableIntersection(bool isIgnoringDirection, TArray<FVector2D>& availableDirection)
{
    availableDirection.Empty();

    bool isAtIntersection = false;

    for (const FVector2D& currentDirection : _Directions)
    {
        // Ignore reverse direction
        if (currentDirection == -_MovingDirection && !isIgnoringDirection)
        {
            continue;
        }

        //FIntPoint NewIndex = CurrentIndex + Dir;
        FVector2D nextGrid = _CurrentGridPosition + currentDirection;

        if (CheckWalkableGrid(nextGrid))
        {
            
            availableDirection.Add(currentDirection);
        }
    }

    /*if (GEngine)
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "IS AT INTERSECTION: " + FString::Printf(TEXT("%d"), availableDirection.Num()));*/

    if (availableDirection.Num() >= 1)
    {
        isAtIntersection = true;
    }

    return isAtIntersection;
}


AC_MoveableCharacter* AC_Ghost::GetPacManPointer()
{
    AActor* foundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AC_PacManCharacter::StaticClass());
    return Cast<AC_MoveableCharacter>(foundActor);

}

