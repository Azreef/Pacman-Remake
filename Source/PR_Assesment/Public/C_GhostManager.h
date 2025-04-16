// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "E_GhostEnum.h"
#include "C_Ghost.h"
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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void StartPhase();
	void UpdateAllGhostState(E_GhostState);
	void AddToGhostList(AC_Ghost* newGhost);

	E_GhostState _CurrentGlobalGhostState = E_GhostState::Chase;

	TArray<AC_Ghost*> _GhostList;

	

	FTimerHandle _GhostTimerHandle;

	int _CurrentPhaseLevel = 0;

	bool _IsTimerInitialized = false;


	UPROPERTY(EditAnywhere)
	TArray<F_PhaseDuration> _PhaseDurationList = { { 7, 20 }, { 7,20 }, { 5,20 }, { 5,-1 } } ; //-1 is infinite

};
