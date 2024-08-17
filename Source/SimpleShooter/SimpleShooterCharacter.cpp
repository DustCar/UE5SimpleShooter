// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleShooterCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInput/Public/EnhancedInputComponent.h"
#include "SimpleShooterInputConfigData.h"
#include "InputActionValue.h"
#include "SimpleShooterGameModeBase.h"
#include "SimpleShooterGun.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
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

	CurrHealth = MaxHealth;
	
	/* code for a single gun
	MainGun = GetWorld()->SpawnActor<ASimpleShooterGun>(RifleClass);
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_Term);
	MainGun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	MainGun->SetOwner(this);
	*/

	Guns[0] = GetWorld()->SpawnActor<ASimpleShooterGun>(RifleClass);
	Guns[1] = GetWorld()->SpawnActor<ASimpleShooterGun>(LauncherClass);
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_Term);
	Guns[GunsIndex]->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Guns[GunsIndex]->SetOwner(this);
}

// Called every frame
void ASimpleShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TimeUntilSwap--;
	if (TimeUntilSwap <= 0.f)
	{
		bJustSwapped = false;
	}
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
	PEI->BindAction(InputActions->InputSwitchWeapons, ETriggerEvent::Triggered, this, &ASimpleShooterCharacter::SwitchWeapons);
	PEI->BindAction(InputActions->InputSwitchWeaponOne, ETriggerEvent::Triggered, this, &ASimpleShooterCharacter::SwitchWeaponNumbered, 0);
	PEI->BindAction(InputActions->InputSwitchWeaponTwo, ETriggerEvent::Triggered, this, &ASimpleShooterCharacter::SwitchWeaponNumbered, 1);
	PEI->BindAction(InputActions->ReloadWeapon, ETriggerEvent::Triggered, this, &ASimpleShooterCharacter::Reload);
}

float ASimpleShooterCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float DamageTaken = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if (DamageTaken > 0)
	{
		// Take the min of DamageTaken and CurrHealth in case actor takes more damage than health
		DamageTaken = FMath::Min(DamageTaken, CurrHealth);
		CurrHealth -= DamageTaken;
		UE_LOG(LogTemp, Warning, TEXT("Actor: %s Damage: %f"), *GetName(), DamageTaken)
	}

	if (IsDead() && GetCapsuleComponent()->IsCollisionEnabled())
	{
		ASimpleShooterGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ASimpleShooterGameModeBase>();
		if (GameMode != nullptr)
		{
			GameMode->PawnKilled(this);
		}
		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	return DamageTaken;
}

bool ASimpleShooterCharacter::IsDead() const
{
	return CurrHealth <= 0;
}

float ASimpleShooterCharacter::GetHealthPercent() const
{
	return CurrHealth/MaxHealth;
}

void ASimpleShooterCharacter::Move(const struct FInputActionValue& InVal)
{
	APlayerController* PC = GetLocalViewingPlayerController();
	if (PC != nullptr)
	{
		const FVector2D MoveValue = InVal.Get<FVector2D>();

		if (MoveValue.Y != 0.f)
		{
			// cancels movement for Keyboard players if opposite keys are pressed
			if (PC->IsInputKeyDown(EKeys::W) && PC->IsInputKeyDown(EKeys::S))
			{
				return;
			}
			AddMovementInput(GetActorForwardVector() * MoveValue.Y);
		}

		if (MoveValue.X != 0.f)
		{
			if (PC->IsInputKeyDown(EKeys::A) && PC->IsInputKeyDown(EKeys::D))
			{
				return;
			}
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

void ASimpleShooterCharacter::SwitchWeapons()
{
	if (bJustSwapped == true || TimeUntilSwap >= 0.f)
	{
		return;
	}

	bJustSwapped = true;
	TimeUntilSwap = 15.f;
		
	Guns[GunsIndex]->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
	GunsIndex = (GunsIndex + 1) % 2;
	Guns[GunsIndex]->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Guns[GunsIndex]->SetOwner(this);
}

ASimpleShooterGun* ASimpleShooterCharacter::GetEquippedGun() const
{
	return Guns[GunsIndex];
}

void ASimpleShooterCharacter::SwitchWeaponNumbered(int32 WeaponIndex)
{
	if (bJustSwapped == true || TimeUntilSwap >= 0.f || WeaponIndex == GunsIndex)
	{
		return;
	}

	bJustSwapped = true;
	TimeUntilSwap = 15.f;

	Guns[GunsIndex]->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
	GunsIndex = WeaponIndex;
	Guns[GunsIndex]->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Guns[GunsIndex]->SetOwner(this);
}

void ASimpleShooterCharacter::GetWeaponsAmmoCount(int32& AmmoCount, int32& ReserveAmmoCount) const
{
	AmmoCount = Guns[GunsIndex]->GetCurrentAmmoCount();
	ReserveAmmoCount = Guns[GunsIndex]->GetCurrentReserveAmmoCount();
}

void ASimpleShooterCharacter::Fire()
{
	if (Guns[GunsIndex]->GetCurrentAmmoCount() == 0 && Guns[GunsIndex]->GetCurrentReserveAmmoCount() != 0)
	{
		Reload();
		return;
	}
	Guns[GunsIndex]->PullTrigger();
}

void ASimpleShooterCharacter::Reload()
{
	Guns[GunsIndex]->RefreshMags();
}

