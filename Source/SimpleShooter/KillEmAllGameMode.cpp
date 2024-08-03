// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"

void AKillEmAllGameMode::PawnKilled(APawn* InPawn)
{
	Super::PawnKilled(InPawn);

	UE_LOG(LogTemp, Warning, TEXT("Pawn killed"));
	// Note that since it is casting an APlayerController*, if an AI Character dies, PlayerController would be nullptr
	// since GetController() for an AI would return an AAIController* rather than an APlayerController*
	APlayerController* PlayerController = Cast<APlayerController>(InPawn->GetController());
	if (PlayerController != nullptr)
	{
		PlayerController->GameHasEnded(nullptr, false);
	}
}
