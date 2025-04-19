// Fill out your copyright notice in the Description page of Project Settings.


#include "C_Pellet.h"
#include "Components/SphereComponent.h"

// Sets default values
AC_Pellet::AC_Pellet()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    _CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
    _CollisionSphere->InitSphereRadius(30.f);
    _CollisionSphere->SetupAttachment(RootComponent);

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

//void AC_Pellet::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
//{
//    if (OtherActor && OtherActor != this)
//    {
//        AC_MoveableCharacter* pacman = Cast<AC_PacManCharacter>(OtherActor);
//        if (pacman)
//        {
//            OnCollected();
//        }
//    }
//}

void AC_Pellet::OnCollected()
{
    Destroy();

}



