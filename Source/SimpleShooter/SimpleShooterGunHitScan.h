// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SimpleShooterGun.h"
#include "SimpleShooterGunHitScan.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API ASimpleShooterGunHitScan : public ASimpleShooterGun
{
	GENERATED_BODY()

public:
	virtual void PullTrigger() override;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

};
