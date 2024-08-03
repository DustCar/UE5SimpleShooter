// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleShooterAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void ASimpleShooterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ASimpleShooterAIController::BeginPlay()
{
	Super::BeginPlay();

	// BehaviorTree code block
	if (AIBehaviorTree != nullptr)
	{
		RunBehaviorTree(AIBehaviorTree);

		GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
	}
}
