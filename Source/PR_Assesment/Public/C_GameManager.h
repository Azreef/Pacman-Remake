// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_GameManager.generated.h"

UCLASS()
class PR_ASSESMENT_API AC_GameManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_GameManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Debugging", meta = (ToolTip = "Enable Debugging Mode"))
	bool _IsDebugModeEnabled = false;


	int _PlayerScore = 0;

};
