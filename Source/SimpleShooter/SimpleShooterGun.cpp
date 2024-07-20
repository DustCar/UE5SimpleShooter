// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleShooterGun.h"

// Sets default values
ASimpleShooterGun::ASimpleShooterGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	RootComponent = RootComp;

	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunMesh"));
	GunMesh->SetupAttachment(RootComp);
}

// Called when the game starts or when spawned
void ASimpleShooterGun::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ASimpleShooterGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

