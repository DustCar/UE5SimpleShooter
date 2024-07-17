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
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCameraComponent* PlayerCamera;
	
	void Move(const struct FInputActionValue& InVal);

	void Look(const FInputActionValue& InVal);

	void ControllerLook(const FInputActionValue& InVal);

	// sensitivity for mouse
	UPROPERTY(EditAnywhere, Category = "Enanced Input", meta=(UImin = 1, UIMax = 100))
	float LookSensitivity = 1;

	// sensitivity for controller
	UPROPERTY(EditAnywhere, Category = "Enanced Input", meta=(UImin = 1, UIMax = 100))
	float ControllerSensitivity = 1;

	UPROPERTY(EditAnywhere, Category = "Enanced Input")
	float ControllerSenMlt = 1;
};
