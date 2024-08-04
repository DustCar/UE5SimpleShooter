// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"

#include "EngineUtils.h"
#include "SimpleShooterAIController.h"

void AKillEmAllGameMode::PawnKilled(APawn* InPawn)
{
	Super::PawnKilled(InPawn);

	UE_LOG(LogTemp, Warning, TEXT("Pawn killed"));
	// Note that since it is casting an APlayerController*, if an AI Character dies, PlayerController would be nullptr
	// since GetController() for an AI would return an AAIController* rather than an APlayerController*
	APlayerController* PlayerController = Cast<APlayerController>(InPawn->GetController());
	if (PlayerController != nullptr)
	{
		EndGame(false);
	}

	// for loop that checks if any of the ShooterAI controllers are alive, if so then early return
	for (ASimpleShooterAIController* AIController : TActorRange<ASimpleShooterAIController>(GetWorld()))
	{
		if (!AIController->IsDead())
		{
			return;
		}
	}
	
	// If for loop successfully passes then game ends and player wins
	EndGame(true);
}

// Function that tells all Controllers that the game is over and if they are winners
void AKillEmAllGameMode::EndGame(bool bIsPlayerWinner) const
{
	for (AController* Controller : TActorRange<AController>(GetWorld()))
	{
		/* Final iteration for determining GameHasEnded state
		 * evaluates Winner in one line, true if same value, false if differing values
		 * True if PlayerControlled (true) & PlayerWinner (true)
		 * True if NotPlayerController (false) & PlayerNotWinner (false)
		*/
		bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
		Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
		
		/* Second iteration for determining state of GameHasEnded for each Controller
		 *
		// bool to help differentiate between PlayerController and other Controllers
		bool bIsPlayerControlled = Controller->IsPlayerController();
		// when player wins, GameHasEnded returns true for the player while false for AI (bIsPlayerControlled becomes false);
		if (bIsPlayerWinner)
		{
			Controller->GameHasEnded(nullptr, bIsPlayerControlled);
		}
		// opposite for when player loses
		else
		{
			Controller->GameHasEnded(nullptr, !bIsPlayerControlled);
		}
		*/
	}
}
