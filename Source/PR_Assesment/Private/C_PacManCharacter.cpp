


#include "C_PacManCharacter.h"
#include "C_GameManager.h"
#include "Components/CapsuleComponent.h"


AC_PacManCharacter::AC_PacManCharacter()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Trigger Capsule"));
	TriggerCapsule->InitCapsuleSize(55.f, 96.0f);;
	TriggerCapsule->SetCollisionProfileName(TEXT("Trigger"));
	RootComponent = TriggerCapsule;
	TriggerCapsule->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	TriggerCapsule->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	TriggerCapsule->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	TriggerCapsule->SetGenerateOverlapEvents(true);
	
}


void AC_PacManCharacter::BeginPlay()
{
	Super::BeginPlay();

	TriggerCapsule->OnComponentBeginOverlap.AddDynamic(this, &AC_PacManCharacter::OnOverlapBegin);
}


void AC_PacManCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (_IntendedDirectionTimer <= _IntendedDirectionDuration)
	{
		MoveTowards(_IntendedDirection);
		_IntendedDirectionTimer = _IntendedDirectionTimer + DeltaTime;
	}
	else if ((_IntendedDirectionTimer > _IntendedDirectionDuration))
	{
		_IntendedDirection = _PreviousMoveDirection;
		MoveTowards(_IntendedDirection);

	}

}


void AC_PacManCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//Set up Mapping Context
	APlayerController* playerController = Cast<APlayerController>(GetController());
	if (playerController)
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer());

		if (Subsystem && _MappingContext)
		{
			Subsystem->AddMappingContext(_MappingContext, 0);
		}
	}
	

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(_MoveInputAction, ETriggerEvent::Triggered, this, &AC_PacManCharacter::MoveInput);
		EnhancedInputComponent->BindAction(_ToggleDebugInputAction, ETriggerEvent::Triggered, this, &AC_PacManCharacter::ToggleDebug);
	}
	
}


void AC_PacManCharacter::ToggleDebug(const FInputActionValue& movementValue)
{
	_GameManager->_IsDebugModeEnabled = !_GameManager->_IsDebugModeEnabled;
}

void AC_PacManCharacter::MoveInput(const FInputActionValue& movementValue)
{
	
	FVector2D moveDirection = movementValue.Get<FVector2D>();

	if (moveDirection.X > 0.5f)
	{
		_IntendedDirection = FVector2D(1, 0);
		// Move Right
		
	}
	else if (moveDirection.X < -0.5f)
	{
		// Move Left
		_IntendedDirection = FVector2D(-1, 0);
		
	}
	else if (moveDirection.Y > 0.5f)
	{
		// Move Up
		_IntendedDirection = FVector2D(0, -1);
		
	}
	else if (moveDirection.Y < -0.5f)
	{
		// Move Down
		_IntendedDirection = FVector2D(0, 1);
		
	}

	_IntendedDirectionTimer = 0;

}

void AC_PacManCharacter::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this))
	{
		UE_LOG(LogTemp, Warning, TEXT("Overlapped: %s"), *OtherActor->GetName());
	}
}


void AC_PacManCharacter::NotifyActorBeginOverlap(AActor* otherActor)
{
	Super::NotifyActorBeginOverlap(otherActor);

	if (otherActor && otherActor != this)
	{
		
		I_Collectable* collectAble = Cast<I_Collectable>(otherActor);
		if (collectAble)
		{
			collectAble->OnCollected();
		}
	}
}