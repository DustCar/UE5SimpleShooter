// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleShooterGunProjectile.h"

#include "SimpleShooterProjectile.h"

ASimpleShooterGunProjectile::ASimpleShooterGunProjectile()
{
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPoint"));
	ProjectileSpawnPoint->SetupAttachment(GunMesh);
}

void ASimpleShooterGunProjectile::PullTrigger()
{
	Super::PullTrigger();

	FHitResult Hit;
	bool bHit = GunTrace(Hit);
	if (bHit)
	{
		FVector Location = ProjectileSpawnPoint->GetComponentLocation();
		// Calculate the line of the trace to get its rotation
		FVector TraceLine = Hit.ImpactPoint - Hit.TraceStart;
		FRotator Rotation = TraceLine.Rotation();

		ASimpleShooterProjectile* Projectile = GetWorld()->SpawnActor<ASimpleShooterProjectile>(ProjectileClass, Location, Rotation);
		if (Projectile)
		{
			Projectile->SetOwner(this);
		}
	}
	
	
}

void ASimpleShooterGunProjectile::BeginPlay()
{
	Super::BeginPlay();
}

