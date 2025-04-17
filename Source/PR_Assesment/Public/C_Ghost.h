

#pragma once

#include "CoreMinimal.h"
#include "C_MoveableCharacter.h"
#include "E_GhostEnum.h"
#include "DrawDebugHelpers.h"
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

	FVector2D CalculateNextGridStep(FVector2D targetGridCoordinate, TArray<FVector2D>& availableDirection);//Get Next grid needed to reach target
	virtual FVector2D CalculateChaseTargetGrid(); //Calculate Target Grid (Is Different for Each Ghost Type) 

	bool CalculatePossiblePath(bool isIgnoringOppositeDirection, TArray<FVector2D>& availableDirection); // Get any available Direction Path & add all valid direction into 'availableDirection' | Return false if found none

	void DrawDebug(FVector2D targetGridCoordinate, FColor debugColour);

	FVector2D _LatestIntersectionGrid; // Used to make sure that intersection check (and turning) is only triggered once
	AC_MoveableCharacter* _PacManPointer;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetGhostManager(class AC_GhostManager* newGhostManager);
	AC_MoveableCharacter* GetPacManPointer();//Get PacMan Data for targeting purposes
	void SetState(E_GhostState newState, bool shouldChangeDirection);
	bool CheckWalkableGrid(FVector2D gridLocation);
	
	UPROPERTY(EditAnywhere, Category = "Character|Ghost")
	E_GhostState _CurrentState;

	UPROPERTY(EditAnywhere, Category = "Character|Ghost", meta = (ToolTip = "Where The Ghost will Go When in Scatter Mode"))
	FVector2D _ScatterGridCoordinate;

	UPROPERTY(EditAnywhere, Category = "Character|Ghost", meta = (ToolTip = "Where The Ghost will Go When Exiting House"))
	FVector2D _HouseExitGridCoordinate = FVector2D(12,11);

	UPROPERTY(EditAnywhere, Category = "Character|Ghost|Debug")
	bool _IsDebugModeEnabled = true;

	UPROPERTY(EditAnywhere, Category = "Character|Ghost|Debug")
	FColor _DebugColor = FColor::White;

	FVector2D _CurrentTargetGridPosition;
	TArray<FVector2D> _AvailableDirection;

	UPROPERTY(EditAnywhere, Category = "Character|Ghost|Debug", meta = (ToolTip = "How long the ghost will be delayed before making a turn (In Seconds)"))
	float _GhostTurnWaitTime = 0.15f;

	float _CurrentTurnWaitTime = 0;
	
	E_GhostType _GhostType;

	AC_GhostManager* _GhostManager;
	

};
