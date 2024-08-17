// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SimpleShooterCharacter.generated.h"

UCLASS()
class SIMPLESHOOTER_API ASimpleShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASimpleShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UInputMappingContext* InputMapping;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class USimpleShooterInputConfigData* InputActions;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintPure)
	bool IsDead() const;

	UFUNCTION(BlueprintPure)
	float GetHealthPercent() const;

	void Fire();

	void Reload();
	
	void SwitchWeapons();

	class ASimpleShooterGun* GetEquippedGun() const;

	UFUNCTION(BlueprintPure)
	void GetWeaponsAmmoCount(int32& AmmoCount, int32& ReserveAmmoCount) const;

private:
	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* PlayerCamera;
	
	void Move(const struct FInputActionValue& InVal);

	void Look(const FInputActionValue& InVal);

	void ControllerLook(const FInputActionValue& InVal);

	void SwitchWeaponNumbered(int32 WeaponIndex);

	UPROPERTY(EditDefaultsOnly, Category= "Health")
	float MaxHealth = 100.f;

	UPROPERTY(EditDefaultsOnly, Category= "Health")
	float CurrHealth;

	// sensitivity for mouse
	UPROPERTY(EditAnywhere, Category = "Enhanced Input", meta=(UImin = 1, UIMax = 100))
	float LookSensitivity = 1;

	// sensitivity for controller
	UPROPERTY(EditAnywhere, Category = "Enhanced Input", meta=(UImin = 1, UIMax = 100))
	float ControllerSensitivity = 1;

	UPROPERTY(EditAnywhere, Category = "Enhanced Input")
	float ControllerSenMlt = 1;

	// Timers for Switching Weapons
	UPROPERTY(EditAnywhere, Category = "Enhanced Input")
	float TimeUntilSwap = 0.f;

	bool bJustSwapped = false;

	// start: Code for a single gun
	UPROPERTY()
	class ASimpleShooterGun* MainGun;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<ASimpleShooterGun> RifleClass;
	// end

	// start: Code for an array of guns; For weapon swap functionality
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TArray<TSubclassOf<ASimpleShooterGun>> GunClasses;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<ASimpleShooterGun> LauncherClass;

	TStaticArray<ASimpleShooterGun*, 2> Guns;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	int32 GunsIndex = 0;
	
};
