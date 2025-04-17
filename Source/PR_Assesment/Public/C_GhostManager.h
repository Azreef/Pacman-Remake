// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "E_GhostEnum.h"
#include "C_GhostManager.generated.h"

USTRUCT()
struct F_PhaseDuration
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float scatterDuration;
	
	UPROPERTY(EditAnywhere)
	float chaseDuration;
	
};

UCLASS()
class PR_ASSESMENT_API AC_GhostManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_GhostManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimerHandle _GhostTimerHandle;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void StartPhase(); //Start the Scatter -> Chase Sequences & Timer
	void UpdateAllGhostState(E_GhostState newGhostState, bool isIncludingGhostAtHome);
	void AddToGhostList(class AC_Ghost* newGhost);
	bool CheckIfAnyGhostInHouse();
	class AC_Ghost* GetGhostByType(E_GhostType ghostType);
	void ReleaseGhost(); //Release Ghost From their house
	void SetGameManager();

	TArray<AC_Ghost*> _GhostList;

	int _CurrentPhaseLevel = 0;

	float _CurrentGhostHouseTime = 0;
	UPROPERTY(EditAnywhere, Category = "Properties", meta = (ToolTip = "How long the ghost will stay at house (in seconds)"))
	float _MaxGhostHouseTime = 5;

	int _GhostLeavesCounter = 1;

	bool _IsTimerInitialized = false;

	UPROPERTY(EditAnywhere, Category = "Properties", meta = (ToolTip = "How long does each mode last each phase (in seconds)"))
	TArray<F_PhaseDuration> _PhaseDurationList = { { 7, 20 }, { 7,20 }, { 5,20 }, { 5,-1 } } ; //-1 is infinite

	UPROPERTY(EditAnywhere, Category = "Properties")
	E_GhostState _CurrentGlobalGhostState = E_GhostState::Chase;

	class AC_GameManager* _GameManager;
};


