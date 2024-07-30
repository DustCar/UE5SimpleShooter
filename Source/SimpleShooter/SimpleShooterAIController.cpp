// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleShooterAIController.h"

#include "Kismet/GameplayStatics.h"

void ASimpleShooterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	// if (PlayerPawn != nullptr)
	// {
	// 	if (LineOfSightTo(PlayerPawn))
	// 	{
	// 		SetFocus(PlayerPawn);
	// 		MoveToActor(PlayerPawn, AcceptanceRadius);
	// 	}
	// 	else
	// 	{
	// 		ClearFocus(EAIFocusPriority::Gameplay);
	// 		StopMovement();
	// 	}
	// }
}

void ASimpleShooterAIController::BeginPlay()
{
	Super::BeginPlay();

	if (AIBehaviorTree != nullptr)
	{
		RunBehaviorTree(AIBehaviorTree);
	}
}
