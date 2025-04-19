


#include "C_MoveableCharacter.h"
#include "C_GameManager.h"

// Sets default values
AC_MoveableCharacter::AC_MoveableCharacter()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AC_MoveableCharacter::BeginPlay()
{
	Super::BeginPlay();

	SetGameManager();//set game manager

	//initialise position
	_TargetGridPosition = ConvertWorldToGrid(GetActorLocation());
	_CurrentGridPosition = ConvertWorldToGrid(GetActorLocation());
	

}

// Called every frame
void AC_MoveableCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateMovement(DeltaTime);
}

void AC_MoveableCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}


// Called to bind functionality to input
void AC_MoveableCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void AC_MoveableCharacter::UpdateMovement(float deltaTime)
{
	
	FVector currentPosition = GetActorLocation();
	_CurrentGridPosition = ConvertWorldToGrid(currentPosition);

	//TELEPORT PLAYER 
	if (!GetActorLocation().Equals(ConvertGridToWorld(_TargetGridPosition), 1))
	{
		if (_CurrentGridPosition.X < 1) //Teleport 
		{
			_CurrentGridPosition.X = _MazeWidth - 2;
			SetActorLocation(ConvertGridToWorld(_CurrentGridPosition));

		}
		else if (_CurrentGridPosition.X >= _MazeWidth - 1) //Teleport 
		{
			_CurrentGridPosition.X = 2;
			SetActorLocation(ConvertGridToWorld(_CurrentGridPosition));

		}
		else
		{
			FHitResult HitResult;
			FVector newPosition = FMath::VInterpConstantTo(currentPosition, ConvertGridToWorld(_TargetGridPosition), deltaTime, _MoveSpeed);
			SetActorLocation(newPosition,true, &HitResult);

			if (HitResult.IsValidBlockingHit())
			{

				if (GEngine)
					GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("HIT"));
				OnOverlapBegin(HitResult.GetComponent(), HitResult.GetActor(), HitResult.GetComponent(), 0, true, HitResult);
			}
		}

	}

	
	FVector2D nextGrid = _CurrentGridPosition + _MovingDirection;
	bool isAtTileCenter = GetActorLocation().Equals(ConvertGridToWorld(_CurrentGridPosition), _CornerMargin); //To stop corner cutting

	if (!_MovingDirection.IsZero())
	{
		if (CheckWalkableGrid(nextGrid))
		{
			
			if (isAtTileCenter  || ((_MovingDirection == -_PreviousMoveDirection)))
			{
				_TargetGridPosition = nextGrid;
				_PreviousMoveDirection = _MovingDirection;

				if (_CharacterRotateEnabled)
				{
					RotateCharacter(_MovingDirection);
				}
			}
		}
		else
		{
			MoveTowards(_PreviousMoveDirection);

			nextGrid = _CurrentGridPosition + _MovingDirection;
			if (CheckWalkableGrid(nextGrid))
			{

				_TargetGridPosition = nextGrid;
			}

		}
	}

}

void AC_MoveableCharacter::MoveTowards(FVector2D direction) //Changes Direction
{
	_MovingDirection = direction;
}

void AC_MoveableCharacter::SetTileSize(float tileSize)
{
	_TileSize = tileSize;
}

void AC_MoveableCharacter::SetMazeGrid(TArray <TArray<F_GridData>>* mazeGrid)
{
	if (!mazeGrid->IsEmpty())
	{
		_MazeGrid = mazeGrid;

		_MazeWidth = _MazeGrid->Num();
		//DEBUG

		/*for (int32 Y = 0; Y < _MazeGrid->Num(); Y++)
		{
			FString RowString;

			for (int32 X = 0; X < (*_MazeGrid)[Y].Num(); X++)
			{
				RowString += (*_MazeGrid)[Y][X].isWalkable ? TEXT("1 ") : TEXT("0 ");
			}

			UE_LOG(LogTemp, Warning, TEXT("%s"), *RowString);
		}*/
	}
	else
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("_MazeGrid is EMPTY!"));
	}
	

}

void AC_MoveableCharacter::SetGameManager()
{
	_GameManager = Cast<AC_GameManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AC_GameManager::StaticClass()));
}

bool AC_MoveableCharacter::CheckWalkableGrid(FVector2D gridLocation)
{

	if (!_MazeGrid->IsEmpty())
	{
		int indexX = gridLocation.X;
		int indexY = gridLocation.Y;

		return (*_MazeGrid)[indexX][indexY].isWalkable;
	}
	else
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("_MazeGrid is EMPTY!"));

		return false;
	}

}

void AC_MoveableCharacter::RotateCharacter(FVector2D direction)
{
	FVector convertedDirection = FVector(direction.X, direction.Y, 0);
	FRotator lookRotation = convertedDirection.Rotation();
	SetActorRotation(lookRotation);
}

FVector2D AC_MoveableCharacter::ConvertWorldToGrid(FVector worldLocation) //Used to Convert World Position to Grid Position, FVector2D to FVector
{
	FVector2D gridPosition = FVector2D(FMath::RoundToInt(worldLocation.X / _TileSize), FMath::RoundToInt(worldLocation.Y / _TileSize));

	return gridPosition;
}

FVector AC_MoveableCharacter::ConvertGridToWorld(FVector2D gridLocation) //Used to Convert Grid Position to World Position, FVector to FVector2D
{
	return FVector(gridLocation.X * _TileSize, gridLocation.Y * _TileSize, 0);
}
