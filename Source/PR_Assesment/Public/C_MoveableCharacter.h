

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "F_MazeStruct.h"
#include "C_MoveableCharacter.generated.h"

UCLASS()
class PR_ASSESMENT_API AC_MoveableCharacter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AC_MoveableCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Moving Functions (Change Direction, Not Position)
	void MoveTowards(FVector2D direction);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void UpdateMovement(float deltaTime); //Update The Current Position

	// Grid = 1 | World = Grid * TileSize
	FVector2D ConvertWorldToGrid(FVector worldLocation);
	FVector ConvertGridToWorld(FVector2D gridLocation);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void SetTileSize(float tileSize); //Set The Tile Size for Movement Purposes
	void SetMazeGrid(TArray <TArray<F_GridData>>* mazeGrid); //Get MazeGrid (From LevelLoader)
	void SetGameManager();
	virtual bool CheckWalkableGrid(FVector2D gridLocation);
	void RotateCharacter(FVector2D direction);
	FVector2D _CurrentGridPosition;
	FVector2D _TargetGridPosition;

	UPROPERTY(EditAnywhere, Category = "Character|Debugging", meta = (ToolTip = "Current Moving Direction"))
	FVector2D _MovingDirection = FVector2D::ZeroVector;

	UPROPERTY(EditAnywhere, Category = "Character|Debugging", meta = (ToolTip = "Previous Moving Direction"))
	FVector2D _PreviousMoveDirection;

	float _TileSize = 100;

	UPROPERTY(EditAnywhere, Category = "Character", meta = (ToolTip = "Speed of The Character"))
	float _MoveSpeed = 300;
	
	UPROPERTY(EditAnywhere, Category = "Character", meta = (ToolTip = "How quick the character can turn around the corner (Min - 1)"))
	float _CornerMargin = 1;

	UPROPERTY(EditAnywhere, Category = "Character", meta = (ToolTip = "Will character rotate when changing direction"))
	bool _CharacterRotateEnabled = true;
	//SAVE DIRECTION VALUE, TEMP  DONT FORGET TO CHANGE TO ENUM LATER
	//BASED ON PRIORITY up > left > down.
	const TArray<FVector2D> _Directions = {
		FVector2D(0, -1), // Up is -1 because how Y increases downward
		FVector2D(-1, 0), // Left 
		FVector2D(0, 1),  // Down
		FVector2D(1, 0),  // Right
	};

	TArray <TArray<F_GridData>>* _MazeGrid;

	int _MazeWidth = 31;

	class AC_GameManager* _GameManager;
};
