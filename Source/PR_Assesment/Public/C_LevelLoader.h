// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"
#include "E_GhostEnum.h"
#include "F_MazeStruct.h"
#include "C_LevelLoader.generated.h"

USTRUCT()
struct F_SpawnGhostData
{
	GENERATED_BODY();

	E_GhostType ghostSpawnType;
	FVector ghostSpawnLocation;
};

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

	void GenerateMaze();
	void SpawnCamera(FVector2D cameraPosition, float zoom);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	UPROPERTY(EditAnywhere, Category = "Maze|Properties", meta = (ToolTip = "Texture used for generating the maze"))
	UTexture2D* _MazeTexture;

	UPROPERTY(EditAnywhere, Category = "Maze|Properties", meta = (ToolTip = "How big is the tile for each grid"))
	float _TileSize = 100;

	UPROPERTY(EditAnywhere, Category = "Maze|Properties")
	AActor* _GhostManager;

	UPROPERTY(EditAnywhere, Category = "Maze|Debugging")
	bool _IsSpawningDots = true;

	UPROPERTY(EditAnywhere, Category = "Maze|Debugging")
	bool _IsSpawningGhost = false;

	UPROPERTY(EditAnywhere, Category = "Maze|Blueprint")
	TSubclassOf<AActor> _Wall;

	UPROPERTY(EditAnywhere, Category = "Maze|Blueprint")
	TSubclassOf<AActor> _TeleporterFacade;

	UPROPERTY(EditAnywhere, Category = "Maze|Blueprint")
	TSubclassOf<AActor> _Door;

	UPROPERTY(EditAnywhere, Category = "Maze|Blueprint")
	TSubclassOf<AActor> _Dots;

	UPROPERTY(EditAnywhere, Category = "Maze|Blueprint|Character")
	TSubclassOf<AActor> _PacMan;

	UPROPERTY(EditAnywhere, Category = "Maze|Blueprint|Character")
	TSubclassOf<AActor> _Blinky;

	UPROPERTY(EditAnywhere, Category = "Maze|Blueprint|Character")
	TSubclassOf<AActor> _Pinky;

	UPROPERTY(EditAnywhere, Category = "Maze|Blueprint|Character")
	TSubclassOf<AActor> _Inky;

	UPROPERTY(EditAnywhere, Category = "Maze|Blueprint|Character")
	TSubclassOf<AActor> _Clyde;

	//TArray <TArray<bool>> _MazeGrid; //Stores Generated Grid [true - can walk | false - cannot walk (has walls)]
	TArray <TArray<F_GridData>> _MazeGrid;

};
