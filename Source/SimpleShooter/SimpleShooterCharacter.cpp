// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleShooterCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInput/Public/EnhancedInputComponent.h"
#include "SimpleShooterInputConfigData.h"
#include "InputActionValue.h"
#include "SimpleShooterGun.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ASimpleShooterCharacter::ASimpleShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArm->SetupAttachment(RootComponent);

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCameraComp"));
	PlayerCamera->SetupAttachment(SpringArm);
	
}

// Called when the game starts or when spawned
void ASimpleShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	MainGun = GetWorld()->SpawnActor<ASimpleShooterGun>(GunClass);
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	MainGun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	MainGun->SetOwner(this);
	
}

// Called every frame
void ASimpleShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

// Called to bind functionality to input
void ASimpleShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	APlayerController* PC = Cast<APlayerController>(GetController());
	if (PC == nullptr)
	{
		return;
	}

	// get local subsystem from local player and clear mappings to add custom IMC
	if (UEnhancedInputLocalPlayerSubsystem* LocalSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
	{
		LocalSubsystem->ClearAllMappings();
		LocalSubsystem->AddMappingContext(InputMapping, 0);
	}
	

	UEnhancedInputComponent* PEI = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	PEI->BindAction(InputActions->InputMove, ETriggerEvent::Triggered, this, &ASimpleShooterCharacter::Move);
	PEI->BindAction(InputActions->InputLook, ETriggerEvent::Triggered, this, &ASimpleShooterCharacter::Look);
	PEI->BindAction(InputActions->InputControllerLook, ETriggerEvent::Triggered, this, &ASimpleShooterCharacter::ControllerLook);
	PEI->BindAction(InputActions->InputJump, ETriggerEvent::Triggered, this, &ACharacter::Jump);
	PEI->BindAction(InputActions->InputFire, ETriggerEvent::Triggered, this, &ASimpleShooterCharacter::Fire);
}

void ASimpleShooterCharacter::Move(const struct FInputActionValue& InVal)
{
	if (Controller != nullptr)
	{
		const FVector2D MoveValue = InVal.Get<FVector2D>();

		if (MoveValue.Y != 0.f)
		{
			AddMovementInput(GetActorForwardVector() * MoveValue.Y);
		}

		if (MoveValue.X != 0.f)
		{
			AddMovementInput(GetActorRightVector() * MoveValue.X);
		}
	}
}

void ASimpleShooterCharacter::Look(const FInputActionValue& InVal)
{
	if (Controller != nullptr)
	{
		const FVector2D LookValue = InVal.Get<FVector2D>();

		if (LookValue.X != 0)
		{
			AddControllerYawInput(LookValue.X * LookSensitivity * GetWorld()->GetDeltaSeconds());
		}

		if (LookValue.Y != 0)
		{
			AddControllerPitchInput(-LookValue.Y * LookSensitivity * GetWorld()->GetDeltaSeconds());
		}
	}
}

void ASimpleShooterCharacter::ControllerLook(const FInputActionValue& InVal)
{
	if (Controller != nullptr)
	{
		const FVector2D LookValue = InVal.Get<FVector2D>();

		if (LookValue.X != 0)
		{
			AddControllerYawInput(LookValue.X * (ControllerSensitivity * ControllerSenMlt) * GetWorld()->GetDeltaSeconds());
		}

		if (LookValue.Y != 0)
		{
			AddControllerPitchInput(LookValue.Y * (ControllerSensitivity * ControllerSenMlt) * GetWorld()->GetDeltaSeconds());
		}
	}
}

void ASimpleShooterCharacter::Fire()
{
	MainGun->PullTrigger();
}

