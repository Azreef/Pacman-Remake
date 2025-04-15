// Fill out your copyright notice in the Description page of Project Settings.


#include "C_Blinky.h"

FVector2D AC_Blinky::GetTargetTile(TArray<FVector2D>& availableDirection)
{
    float shortestDistance = 100;
    FVector2D bestDirection = _MovingDirection;

    //FVector2D bestDirection;

    for (FVector2D& currentDirection : availableDirection)
    {
        float currentDistance = FVector2D::Distance(currentDirection + _CurrentGridPosition, _PacManPointer->_CurrentGridPosition);

       /* if (GEngine)
            GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, currentDirection.ToString());*/

        /* if (GEngine)
             GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("%f"), currentDistance));*/

        if (currentDistance < shortestDistance)
        {
            bestDirection = currentDirection;
            shortestDistance = currentDistance;
            /*if (GEngine)
                GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "NOT SHORTEST ");*/

        }

    }

   /* if (GEngine)
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "BEST DIR: " + bestDirection.ToString());
    if (GEngine)
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "==============================================");*/

    return bestDirection;
}