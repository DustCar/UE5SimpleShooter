// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SimpleShooterInputConfigData.generated.h"

class UInputAction;

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API USimpleShooterInputConfigData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputMove;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputLook;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputControllerLook;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputJump;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputFire;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputSwitchWeapons;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputSwitchWeaponOne;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputSwitchWeaponTwo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* ReloadWeapon;
};
