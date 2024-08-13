// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleShooterProjectile.h"

#include "SimpleShooterGunProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASimpleShooterProjectile::ASimpleShooterProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMeshComponent"));
	RootComponent = ProjectileMeshComp;

	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComp->InitialSpeed = ProjectileInitSpeed;
	ProjectileMovementComp->MaxSpeed = ProjectileMaxSpeed;
	
}

// Called when the game starts or when spawned
void ASimpleShooterProjectile::BeginPlay()
{
	Super::BeginPlay();

	ProjectileMeshComp->OnComponentHit.AddDynamic(this, &ASimpleShooterProjectile::OnHit);
}

// Called every frame
void ASimpleShooterProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASimpleShooterProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	AActor* MyOwner = GetOwner();
	if (MyOwner == nullptr)
	{
		return;
	}
	
	TArray<AActor*> IgnoredActors;
	IgnoredActors.Add(MyOwner);
	IgnoredActors.Add(MyOwner->GetOwner());
	IgnoredActors.Add(this);
	
	if (OtherActor != this && OtherActor != MyOwner)
	{
		UGameplayStatics::ApplyRadialDamageWithFalloff(
			GetWorld(),
			MaxDamage,
			MinDamage,
			GetActorLocation(),
			InnerRadius,
			FullRadius,
			1.f,
			nullptr,
			IgnoredActors,
			this);
	}

	ASimpleShooterGunProjectile* MyOwnerAsGun = Cast<ASimpleShooterGunProjectile>(MyOwner);
	if (MyOwnerAsGun == nullptr)
	{
		return;
	}

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), MyOwnerAsGun->GetHitParticles(), GetActorLocation());
	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), MyOwnerAsGun->GetHitSound(), GetActorLocation());
	
	Destroy();
}

