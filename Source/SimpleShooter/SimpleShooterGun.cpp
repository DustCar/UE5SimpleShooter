// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleShooterGun.h"
#include "Kismet/GameplayStatics.h"

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

void ASimpleShooterGun::PullTrigger()
{
	UE_LOG(LogTemp, Warning, TEXT("Shoot"));
	UGameplayStatics::SpawnEmitterAttached(MuzzleParticles, GunMesh, TEXT("MuzzleFlashSocket"));

	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr)
	{
		return;
	}

	AController* OwnerController = OwnerPawn->GetController();
	if (OwnerController == nullptr)
	{
		return;
	}

	FVector OVPLocation;
	FRotator OVPRotation;
	OwnerController->GetPlayerViewPoint(OVPLocation, OVPRotation);

	DrawDebugCamera(GetWorld(), OVPLocation, OVPRotation, 90, 1, FColor::Red, true);
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

