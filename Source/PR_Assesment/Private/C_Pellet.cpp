// Fill out your copyright notice in the Description page of Project Settings.


#include "C_Pellet.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AC_Pellet::AC_Pellet()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

	TriggerCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Trigger Capsule"));
	TriggerCapsule->InitCapsuleSize(55.f, 96.0f);;
	TriggerCapsule->SetCollisionProfileName(TEXT("Trigger"));
	TriggerCapsule->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	TriggerCapsule->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	TriggerCapsule->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	RootComponent = TriggerCapsule;

	TriggerCapsule->SetGenerateOverlapEvents(true);

}

// Called when the game starts or when spawned
void AC_Pellet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_Pellet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AC_Pellet::OnCollected()
{
    Destroy();

}



