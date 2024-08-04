// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleShooterAIController.h"

#include "SimpleShooterCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void ASimpleShooterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

bool ASimpleShooterAIController::IsDead() const
{
	ASimpleShooterCharacter* ControlledCharacter = Cast<ASimpleShooterCharacter>(GetPawn());
	// checks if AI character is dead, if one is found
	if (ControlledCharacter != nullptr)
	{
		return ControlledCharacter->IsDead();
	}
	// returns true if no possessed pawn is found since it technically means that they did die
	return true;
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
