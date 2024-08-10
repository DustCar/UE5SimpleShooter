// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SimpleShooterProjectile.generated.h"

UCLASS()
class SIMPLESHOOTER_API ASimpleShooterProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASimpleShooterProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleDefaultsOnly, Category = "Projectile")
	UStaticMeshComponent* ProjectileMeshComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Projectile")
	class UProjectileMovementComponent* ProjectileMovementComp;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	UPROPERTY(EditAnywhere, Category = "Projectile")
	float ProjectileInitSpeed = 2000.f;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	float ProjectileMaxSpeed = 2200.f;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	float MaxDamage = 40.f;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	float MinDamage = 10.f;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	float FullRadius = 40.f;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	float InnerRadius = 20.f;
};
