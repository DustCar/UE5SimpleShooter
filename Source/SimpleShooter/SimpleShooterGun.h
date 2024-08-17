// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SimpleShooterGun.generated.h"

UCLASS()
class SIMPLESHOOTER_API ASimpleShooterGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASimpleShooterGun();

	virtual void PullTrigger();

	void RefreshMags();

	int32 GetCurrentAmmoCount() const;

	int32 GetCurrentReserveAmmoCount() const;

	void ReplenishAmmo(int32 AddedAmmo);

	void SetGunEmpty(bool Value);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	AController* GetOwnerController() const; 
	
	virtual bool GunTrace(FHitResult& OutHit) const;
	
	UPROPERTY(VisibleAnywhere)
	USceneComponent* RootComp;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* GunMesh;

	UPROPERTY(EditAnywhere, Category = "GunFX")
	UParticleSystem* MuzzleParticles;

	UPROPERTY(EditAnywhere, Category = "GunFX")
	USoundBase* MuzzleSound;

	UPROPERTY(EditAnywhere, Category = "GunFX")
	UParticleSystem* HitParticles;

	UPROPERTY(EditAnywhere, Category = "GunFX")
	USoundBase* HitSound;

	UPROPERTY(EditAnywhere, Category = "GunFX")
	USoundBase* EmptyGunSound;

	UPROPERTY(EditAnywhere, Category = "GunStats")
	float GunRange = 1500.f;

	UPROPERTY(EditAnywhere, Category = "GunStats")
	float GunDamage = 10.f;

	UPROPERTY(EditAnywhere, Category = "GunStats")
	int32 MaxReserveAmmo = 0;

	UPROPERTY(EditAnywhere, Category = "GunStats")
	int32 CurrentReserveAmmo = 0;

	UPROPERTY(EditAnywhere, Category = "GunStats")
	int32 MaxAmmoPerMag = 0;

	UPROPERTY(EditAnywhere, Category = "GunStats")
	int32 CurrentAmmoInMag = 0;

	UPROPERTY(EditAnywhere, Category = "GunStats")
	int32 MagCount = 0;

	UPROPERTY()
	bool bGunEmpty = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
};
