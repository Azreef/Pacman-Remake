// Fill out your copyright notice in the Description page of Project Settings.


#include "C_LevelLoader.h"
#include "C_MoveableCharacter.h"
#include "C_GhostManager.h"
#include "C_Ghost.h"
#include "IImageWrapper.h"
#include "IImageWrapperModule.h"
#include "Modules/ModuleManager.h"
#include "Misc/FileHelper.h"
#include "HAL/PlatformFilemanager.h"
#include "Engine/Texture2D.h"
#include "ImageUtils.h"

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
	FString ImagePath = FPaths::ProjectUserDir() + "Content/Resources/Level1.png";
	_MazeTexture = LoadTextureFromDisk(ImagePath);

	//Getting Pixel Data
	if (!_MazeTexture)
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("_MazeTexture is EMPTY!"));

		return;
	}
	_MazeTexture->UpdateResource();
	FTexture2DMipMap& mipMap = _MazeTexture->GetPlatformData()->Mips[0];
	FByteBulkData* rawImageData = &mipMap.BulkData;
	FColor* allPixel = reinterpret_cast<FColor*>(rawImageData->Lock(LOCK_READ_ONLY));
	
	int32 mazeWidth = mipMap.SizeX;
	int32 mazeHeight = mipMap.SizeY;

	bool isPacManExist = false;
	FVector pacManSpawnLocation;


	TArray <F_SpawnGhostData> ghostToSpawnList;

	AC_GhostManager* ghostManager = Cast<AC_GhostManager>(_GhostManager);


	//Initialise _MazeGrid 2D Array
	_MazeGrid.SetNum(mazeWidth);
	for (TArray<F_GridData>& currentRow : _MazeGrid)
	{
		currentRow.SetNum(mazeHeight);
	}

	for (int32 Y = 0; Y < mazeHeight; Y++)
	{
		for (int32 X = 0; X < mazeWidth; X++)
		{
			int32 currentIndex = Y * mazeWidth + X;
			FColor currentPixel = allPixel[currentIndex];

			FVector spawnLocation = GetActorLocation() + FVector(X * _TileSize, Y * _TileSize, 0);

			bool isWalkable = true;
			E_TileType tileType = E_TileType::Empty;

			if (currentPixel == FColor::Black )//Spawn Wall
			{
				GetWorld()->SpawnActor<AActor>(_Wall, spawnLocation, FRotator::ZeroRotator);

				isWalkable = false;
				tileType = E_TileType::Wall;
			}
			else if (currentPixel == FColor::Green)//Spawn Door
			{
				GetWorld()->SpawnActor<AActor>(_Door, spawnLocation, FRotator::ZeroRotator);

				isWalkable = false;
				tileType = E_TileType::Door;
			}
			else if(currentPixel == FColor::Yellow && _IsSpawningDots)//Spawn Dots
			{
				GetWorld()->SpawnActor<AActor>(_Dots, spawnLocation, FRotator::ZeroRotator);

			}
			else if (currentPixel == FColor(255, 0, 255))//Spawn Teleporter
			{
				GetWorld()->SpawnActor<AActor>(_TeleporterFacade, FVector(spawnLocation.X, spawnLocation.Y, spawnLocation.Z + 100), FRotator::ZeroRotator);
				isWalkable = true;
				tileType = E_TileType::Teleporter;
			}
			else if (currentPixel == FColor::Blue)//Spawn Player
			{
				isPacManExist = true;
				pacManSpawnLocation = spawnLocation;
			}
			else if (currentPixel == FColor(255, 0, 0))//Spawn Blinky
			{
				ghostToSpawnList.Add({ E_GhostType::Blinky, spawnLocation });
			}
			else if (currentPixel == FColor(255, 192, 203))//Spawn Pinky
			{
				ghostToSpawnList.Add({ E_GhostType::Pinky, spawnLocation });
			}
			else if (currentPixel == FColor(0, 255, 255))//Spawn Inky
			{
				ghostToSpawnList.Add({ E_GhostType::Inky, spawnLocation });
			}
			else if (currentPixel == FColor(255, 128, 0))//Spawn Clyde
			{
				ghostToSpawnList.Add({ E_GhostType::Clyde, spawnLocation });
			}

			_MazeGrid[X][Y].isWalkable = isWalkable;
			_MazeGrid[X][Y].tileType = tileType;
		}
	}

	//Spawn Characters
	if (isPacManExist) //Pacman
	{
		
		AActor* pacMan = GetWorld()->SpawnActor<AActor>(_PacMan, pacManSpawnLocation, FRotator::ZeroRotator);

		AC_MoveableCharacter* moveAbleCharacter = Cast<AC_MoveableCharacter>(pacMan);

		moveAbleCharacter->SetMazeGrid(&_MazeGrid);
		moveAbleCharacter->SetTileSize(_TileSize);
	}
	 
	if (_IsSpawningGhost)
	{
		for (const F_SpawnGhostData& currentGhostData : ghostToSpawnList) //Ghosts
		{
			TSubclassOf<AActor> spawnedGhostType;

			switch (currentGhostData.ghostSpawnType)
			{
			case E_GhostType::Blinky:
				spawnedGhostType = _Blinky;
				break;

			case E_GhostType::Pinky:
				spawnedGhostType = _Pinky;
				break;

			case E_GhostType::Inky:
				spawnedGhostType = _Inky;
				break;

			case E_GhostType::Clyde:
				spawnedGhostType = _Clyde;
				break;

			}

			AActor* spawnedGhostActor = GetWorld()->SpawnActor<AActor>(spawnedGhostType, currentGhostData.ghostSpawnLocation, FRotator::ZeroRotator);

			AC_MoveableCharacter* moveAbleCharacter = Cast<AC_MoveableCharacter>(spawnedGhostActor);

			moveAbleCharacter->SetMazeGrid(&_MazeGrid);
			moveAbleCharacter->SetTileSize(_TileSize);

			AC_Ghost* spawnedGhost = Cast<AC_Ghost>(spawnedGhostActor);

			spawnedGhost->SetGhostManager(ghostManager);
			
			ghostManager->AddToGhostList(spawnedGhost);

		}
	}
	
	ghostManager->StartPhase();//Starts Game Timer

	rawImageData->Unlock();

	FVector2D middlePosition = FVector2D((mazeWidth * _TileSize) / 2, (mazeHeight * _TileSize) / 2);
	SpawnCamera(middlePosition, 30 * _TileSize);
}

void AC_LevelLoader::SpawnCamera(FVector2D cameraPosition, float zoom)
{
	ACameraActor* mainCamera = GetWorld()->SpawnActor<ACameraActor>();

	FTransform cameraTransform(FRotator{ -90.0, 0, 270 }, FVector{ cameraPosition.X, cameraPosition.Y, zoom }, FVector{ 1.0f, 1.0f, 1.0f });

	mainCamera->SetActorTransform(cameraTransform);

	APlayerController* playerController = UGameplayStatics::GetPlayerController(this, 0);
	
	playerController->SetViewTargetWithBlend(mainCamera);

}

UTexture2D* AC_LevelLoader::LoadTextureFromDisk(const FString& FullFilePath)
{
	// Load image file into binary array
	TArray<uint8> RawFileData;
	if (!FFileHelper::LoadFileToArray(RawFileData, *FullFilePath)) {
		UE_LOG(LogTemp, Error, TEXT("Failed to load file from path: %s"), *FullFilePath);
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Failed to decode image: %s"));

		return nullptr;
	}

	// Get the image wrapper module for decoding
	IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));
	TSharedPtr<IImageWrapper> ImageWrapper = ImageWrapperModule.CreateImageWrapper(EImageFormat::PNG); // or JPEG

	if (ImageWrapper.IsValid() && ImageWrapper->SetCompressed(RawFileData.GetData(), RawFileData.Num())) {
		TArray64<uint8> UncompressedBGRA;

		if (ImageWrapper.Get()->GetRaw(ERGBFormat::BGRA, 8, UncompressedBGRA)) {
			
			// Create UTexture2D		
			UTexture2D* NewTexture = UTexture2D::CreateTransient(
				ImageWrapper->GetWidth(),
				ImageWrapper->GetHeight(),
				PF_B8G8R8A8
			);

			if (!NewTexture) return nullptr;

			void* TextureData = NewTexture->GetPlatformData()->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
			FMemory::Memcpy(TextureData, UncompressedBGRA.GetData(), UncompressedBGRA.Num());
			NewTexture-> GetPlatformData()->Mips[0].BulkData.Unlock();

			NewTexture->UpdateResource();
			return NewTexture;
		}
	}

	UE_LOG(LogTemp, Error, TEXT("Failed to decode image: %s"), *FullFilePath);
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Failed to decode image: %s"));
	return nullptr;
}