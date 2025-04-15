// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "E_GhostStateEnum.h"
#include "C_GhostManager.generated.h"

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

	E_GhostStateEnum _CurrentGhostState;

};
