// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleShooterPickup_Ammo.h"

#include "SimpleShooterCharacter.h"
#include "SimpleShooterGun.h"
#include "Components/SphereComponent.h"

void ASimpleShooterPickup_Ammo::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                          UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	if (OtherActor == nullptr || OtherActor == this || OverlappedComponent == nullptr)
	{
		return;
	}
	
	ASimpleShooterCharacter* OtherCharacter = Cast<ASimpleShooterCharacter>(OtherActor);
	if (OtherCharacter == nullptr)
	{
		return;
	}

	ASimpleShooterGun* OtherCharacterGun = OtherCharacter->GetEquippedGun();
	if (OtherCharacterGun == nullptr)
	{
		return;
	}

	OtherCharacterGun->ReplenishAmmo(AmmoReplenishAmt);
	OtherCharacterGun->SetGunEmpty(false);

	BaseMesh->SetHiddenInGame(true);
	SphereComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BaseMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
