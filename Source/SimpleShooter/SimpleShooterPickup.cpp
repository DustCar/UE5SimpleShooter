// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleShooterPickup.h"

#include "Components/SphereComponent.h"

// Sets default values
ASimpleShooterPickup::ASimpleShooterPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	RootComponent = SphereComp;
	
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMeshComp"));
	BaseMesh->SetupAttachment(SphereComp);
}

// Called when the game starts or when spawned
void ASimpleShooterPickup::BeginPlay()
{
	Super::BeginPlay();

	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ASimpleShooterPickup::OnOverlap);
}

void ASimpleShooterPickup::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}

// Called every frame
void ASimpleShooterPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

