// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "I_Collectable.h" 
#include "C_Pellet.generated.h"

class USphereComponent;

UCLASS()
class PR_ASSESMENT_API AC_Pellet : public AActor, public I_Collectable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_Pellet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, Category = "Collision")
	USphereComponent* _CollisionSphere;

	UFUNCTION()
	
	virtual void OnCollected() override;
};
