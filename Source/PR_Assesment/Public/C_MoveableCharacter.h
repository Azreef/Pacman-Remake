

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"
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
	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
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

	void SetTileSize(float tileSize); //Set The Tile Size for Movement Purposes
	void SetMazeGrid(TArray<TArray<bool>>& mazeGrid); //Get MazeGrid (From LevelLoader)
	bool CheckWalkableGrid(FVector2D gridLocation); //True - Walkable | False - Unwalkable
	void RotateCharacter(FVector2D direction);

	FVector2D _CurrentGridPosition;
	FVector2D _TargetGridPosition;
	FVector2D _MovingDirection = FVector2D(0, -1);
	FVector2D _PreviousMoveDirection;

	float _TileSize = 100;

	UPROPERTY(EditAnywhere, Category = "Character", meta = (ToolTip = "Speed of The Character"))
	float _MoveSpeed = 500;
	
	//SAVE DIRECTION VALUE, TEMP  DONT FORGET TO CHANGE TO ENUM LATER
	//BASED ON PRIORITY up > left > down.
	const TArray<FVector2D> _Directions = {
		FVector2D(0, -1), // Up is -1 because how Y increases downward
		FVector2D(-1, 0), // Left 
		FVector2D(0, 1),  // Down
		FVector2D(1, 0),  // Right
	};

	TArray <TArray<bool>> _MazeGrid; //Stores Generated Grid [true - can walk | false - cannot walk (has walls)]

};
