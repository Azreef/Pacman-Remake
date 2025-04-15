// Fill out your copyright notice in the Description page of Project Settings.


#include "C_Blinky.h"

FVector2D AC_Blinky::GetTargetTile(TArray<FVector2D>& availableDirection)
{
    float shortestDistance = 100;
    FVector2D bestDirection = _MovingDirection;


    for (FVector2D& currentDirection : availableDirection)
    {
        float currentDistance = FVector2D::Distance(currentDirection + _CurrentGridPosition, _PacManPointer->_CurrentGridPosition);

       
        if (currentDistance < shortestDistance)
        {
            bestDirection = currentDirection;
            shortestDistance = currentDistance;
        }

    }

    return bestDirection;
}