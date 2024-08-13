// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SimpleShooterGun.h"
#include "SimpleShooterGunProjectile.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API ASimpleShooterGunProjectile : public ASimpleShooterGun
{
	GENERATED_BODY()

public:
	ASimpleShooterGunProjectile();

	virtual void PullTrigger() override;

	UParticleSystem* GetHitParticles() const;

	USoundBase* GetHitSound() const;
	
protected:
	virtual void BeginPlay() override;

	
private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditDefaultsOnly, Category = "GunStats")
	TSubclassOf<class ASimpleShooterProjectile> ProjectileClass;

};
