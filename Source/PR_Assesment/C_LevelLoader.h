// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"
#include "C_LevelLoader.generated.h"

UCLASS()
class PR_ASSESMENT_API AC_LevelLoader : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_LevelLoader();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void GenerateMaze();
	void SpawnCamera(FVector2D cameraPosition, float zoom);

	UPROPERTY(EditAnywhere)
	UTexture2D* _MazeTexture;

	UPROPERTY(EditAnywhere)
	float _TileSize = 100;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> _Wall;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> _Dots;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> _PacMan;

	UPROPERTY(EditAnywhere)
	bool _IsSpawningDots = true;
};
