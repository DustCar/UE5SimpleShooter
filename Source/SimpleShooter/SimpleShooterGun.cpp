// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleShooterGun.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/DamageEvents.h"

// Sets default values
ASimpleShooterGun::ASimpleShooterGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	RootComponent = RootComp;

	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunMesh"));
	GunMesh->SetupAttachment(RootComp);

}

void ASimpleShooterGun::PullTrigger()
{
	// Spawns muzzle flash particles at socket on GunMesh
	UGameplayStatics::SpawnEmitterAttached(MuzzleParticles, GunMesh, TEXT("MuzzleFlashSocket"));

	// Get owner pawn to use for GetController
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr)
	{
		return;
	}

	// Get controller for to get player viewpoint
	AController* OwnerController = OwnerPawn->GetController();
	if (OwnerController == nullptr)
	{
		return;
	}

	// Grab location and rotation of player's view and store in vars
	FVector OVPLocation;
	FRotator OVPRotation;
	OwnerController->GetPlayerViewPoint(OVPLocation, OVPRotation);

	/* Calculate end location of view point by adding viewpoint's current location to unit vector of direction multiplied
	 * by a custom initialized range (units in UE is set in cm, so 1000.f is 1000cm)
	*/
	FVector EndLocation = OVPLocation + OVPRotation.Vector() * GunRange;

	// Get a hit using Trace Channels so that bullet can hit anything that can stop it
	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());
	bool bSuccessHit = GetWorld()->LineTraceSingleByChannel(Hit, OVPLocation, EndLocation, ECollisionChannel::ECC_GameTraceChannel1, Params);

	// If hit found, spawn particles at location and deal damage to actor, if the hit is an actor
	if (bSuccessHit)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticles, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
		if (AActor* DamagedActor = Hit.GetActor())
		{
			FPointDamageEvent GunDamageEvent(GunDamage, Hit, Hit.ImpactNormal, nullptr);
			DamagedActor->TakeDamage(GunDamage, GunDamageEvent, OwnerController, this);
		}
	}
}

// Called when the game starts or when spawned
void ASimpleShooterGun::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ASimpleShooterGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

