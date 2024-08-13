// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleShooterGunHitScan.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/DamageEvents.h"


void ASimpleShooterGunHitScan::PullTrigger()
{
	Super::PullTrigger();

	if (bGunEmpty)
	{
		return;
	}
	
	FHitResult Hit;

	// If hit found, spawn particles at location and deal damage to actor, if the hit is an actor
	if (GunTrace(Hit))
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticles, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), HitSound, Hit.ImpactPoint);
		if (AActor* DamagedActor = Hit.GetActor())
		{
			FPointDamageEvent GunDamageEvent(GunDamage, Hit, Hit.ImpactNormal, nullptr);
			AController* OwnerController = GetOwnerController();
			DamagedActor->TakeDamage(GunDamage, GunDamageEvent, OwnerController, this);
		}
	}
}

// Called when the game starts or when spawned
void ASimpleShooterGunHitScan::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ASimpleShooterGunHitScan::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

