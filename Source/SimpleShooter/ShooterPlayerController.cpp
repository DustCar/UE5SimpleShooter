// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"

void AShooterPlayerController::BeginPlay()
{
	Super::BeginPlay();

	HUD = CreateWidget(this, HUDWidgetClass);

	if (HUD != nullptr)
	{
		HUD->AddToViewport();
	}
}

void AShooterPlayerController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	HUD->RemoveFromParent();
	
	if (bIsWinner)
	{
		UUserWidget* WinScreen = CreateWidget(this, WinScreenWidgetClass);

		if (WinScreen != nullptr)
		{
			WinScreen->AddToViewport();
		}
	}
	else
	{
		UUserWidget* LoseScreen = CreateWidget(this, LoseScreenWidgetClass);

		if (LoseScreen != nullptr)
		{
			LoseScreen->AddToViewport();
		}
	}

	// Timer to reset level
	GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
}
