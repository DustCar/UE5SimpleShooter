// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleShooterAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void ASimpleShooterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (PlayerPawn != nullptr)
	{
		if (LineOfSightTo(PlayerPawn))
		{
			// Set "PlayerLocation" and "LastKnownPlayerLocation" keys to player's pawn location when in LOS
			GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
			GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownPlayerLocation"), PlayerPawn->GetActorLocation());
		}
		else
		{
			// Clears "PlayerLocation" key when player is no longer in sight
			GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
		}
	}
}

void ASimpleShooterAIController::BeginPlay()
{
	Super::BeginPlay();

	// BehaviorTree code block
	if (AIBehaviorTree != nullptr)
	{
		RunBehaviorTree(AIBehaviorTree);

		/*APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		if (PlayerPawn != nullptr)
		{
			// Sets Blackboard Key "PlayerLocation", holds the Player's Pawn location
			GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
		}*/
		// Sets Blackboard Key "StartLocation", holds the AI's Pawn's starting location
		GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
	}
}
