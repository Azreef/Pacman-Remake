// Fill out your copyright notice in the Description page of Project Settings.


#include "C_LevelLoader.h"

// Sets default values
AC_LevelLoader::AC_LevelLoader()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AC_LevelLoader::BeginPlay()
{
	Super::BeginPlay();
	GenerateMaze();
}

// Called every frame
void AC_LevelLoader::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC_LevelLoader::GenerateMaze()
{
	//Getting Pixel Data
	FTexture2DMipMap& mipMap = _MazeTexture->GetPlatformData()->Mips[0];
	FByteBulkData* rawImageData = &mipMap.BulkData;
	FColor* allPixel = static_cast<FColor*>(rawImageData->Lock(LOCK_READ_ONLY));
	
	int32 mazeWidth = mipMap.SizeX;
	int32 mazeHeight = mipMap.SizeY;

	for (int32 Y = 0; Y < mazeHeight; Y++)
	{
		for (int32 X = 0; X < mazeWidth; X++)
		{
			int32 currentIndex = Y * mazeWidth + X;
			FColor currentPixel = allPixel[currentIndex];

			FVector spawnLocation = GetActorLocation() + FVector(X * _TileSize, Y * _TileSize, 0);

			
			if (currentPixel == FColor::Black )//Spawn Wall
			{
				GetWorld()->SpawnActor<AActor>(_Wall, spawnLocation, FRotator::ZeroRotator);
			}
			else if(currentPixel == FColor::Yellow && _IsSpawningDots)//Spawn Dots
			{
				GetWorld()->SpawnActor<AActor>(_Dots, spawnLocation, FRotator::ZeroRotator);
			}
			else if (currentPixel == FColor::Blue)//Spawn Player
			{
				if (GEngine)
					GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("SPAWN PACMAN"));
				GetWorld()->SpawnActor<AActor>(_PacMan, spawnLocation, FRotator::ZeroRotator);
			}
		}
	}

	rawImageData->Unlock();



}

