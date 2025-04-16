

#pragma once

#include "CoreMinimal.h"
#include "C_MoveableCharacter.h"
#include "E_GhostEnum.h"
#include "C_Ghost.generated.h"

/**
 * 
 */
UCLASS()
class PR_ASSESMENT_API AC_Ghost : public AC_MoveableCharacter
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void UpdateDirection(); //Update Current Moving Direction (Not Position)
	virtual FVector2D GetTargetTile(TArray<FVector2D>& availableDirection);//Get Next Target Tile (Is Different for Each Ghost Type) 

	FVector2D GetDirectTileTo(FVector2D targetCoordinate, TArray<FVector2D>& availableDirection);//Get Next Direct Tile to Get to the Target Coordinate (Find Closest path To the Tile), Usually used for Scatter
	bool GetPossiblePath(bool isIgnoringOppositeDirection, TArray<FVector2D>& availableDirection); // Get any available Direction Path & add all valid direction into 'availableDirection' | Return false if found none

	FVector2D _LatestIntersectionGrid; // Used to make sure that intersection check (and turning) is only triggered once
	AC_MoveableCharacter* _PacManPointer;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	AC_MoveableCharacter* GetPacManPointer();//Get PacMan Data for targeting purposes
	void SetState(E_GhostState newState, bool shouldChangeDirection);
	
	UPROPERTY(EditAnywhere, Category = "Character|Ghost")
	E_GhostState _CurrentState;

	UPROPERTY(EditAnywhere, Category = "Character|Ghost", meta = (ToolTip = "Where The Ghost will Go When in Scatter Mode"))
	FVector2D _ScatterGridCoordinate;

};
