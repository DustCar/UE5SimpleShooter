// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleShooterGun.h"

#include "Kismet/GameplayStatics.h"

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
	if (bGunEmpty)
	{
		UGameplayStatics::SpawnSoundAttached(EmptyGunSound, GunMesh, TEXT("MuzzleFlashSocket"));
		return;
	}
	
	// Spawns muzzle flash particles at socket on GunMesh
	UGameplayStatics::SpawnEmitterAttached(MuzzleParticles, GunMesh, TEXT("MuzzleFlashSocket"));
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, GunMesh, TEXT("MuzzleFlashSocket"));
	CurrentAmmoInMag--;

	if (CurrentReserveAmmo == 0 && CurrentAmmoInMag == 0)
	{
		bGunEmpty = true;
	}
}

void ASimpleShooterGun::RefreshMags()
{
	if (bGunEmpty)
	{
		return;
	}

	// Use rest  of reserve ammo as ammo count rather than max
	if (CurrentReserveAmmo < MaxAmmoPerMag)
	{
		CurrentAmmoInMag = CurrentReserveAmmo;
		CurrentReserveAmmo = 0;
	}
	// Refills mag based on how much is still in the mag
	else
	{
		CurrentReserveAmmo = CurrentReserveAmmo - (MaxAmmoPerMag - CurrentAmmoInMag);
		CurrentAmmoInMag = MaxAmmoPerMag;
	}
}

uint32 ASimpleShooterGun::GetCurrentAmmoCount() const
{
	return CurrentAmmoInMag;
}

uint32 ASimpleShooterGun::GetCurrentReserveAmmoCount() const
{
	return CurrentReserveAmmo;
}

void ASimpleShooterGun::BeginPlay()
{
	Super::BeginPlay();

	MaxReserveAmmo = MaxAmmoPerMag * MagCount;
	
	CurrentReserveAmmo = MaxReserveAmmo;
	CurrentAmmoInMag = MaxAmmoPerMag;
}

AController* ASimpleShooterGun::GetOwnerController() const
{
	// Get owner pawn to use for GetController
	APawn *OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr)
	{
		return nullptr;
	}
	
	// Get controller for to get player viewpoint
	return OwnerPawn->GetController();
}

bool ASimpleShooterGun::GunTrace(FHitResult& OutHit) const
{
	AController* OwnerController = GetOwnerController();
	if (OwnerController == nullptr)
	{
		return false;
	}
	
	// Grab location and rotation of player's view and store in vars
	FVector OVPLocation;
	FRotator OVPRotation;
	OwnerController->GetPlayerViewPoint(OVPLocation, OVPRotation);

	/* Calculate end location of view point by adding viewpoint's current location to unit vector of direction multiplied
	 * by a custom initialized range (units in UE is set in cm, so 1000.f is 1000cm)
	*/
	FVector EndLocation = OVPLocation + OVPRotation.Vector() * GunRange;

	// Get a hit using Trace Channels so that bullet can hit anything that can stop it
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());
	
	return GetWorld()->LineTraceSingleByChannel(OutHit, OVPLocation, EndLocation, ECollisionChannel::ECC_GameTraceChannel1, Params);
}

void ASimpleShooterGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}




