// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"

#include "AIController.h"
#include "SimpleShooterCharacter.h"

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (OwnerComp.GetAIOwner() == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	
	ASimpleShooterCharacter* AIPawn = Cast<ASimpleShooterCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (AIPawn == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	AIPawn->Fire();
	
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}

UBTTask_Shoot::UBTTask_Shoot()
{
	NodeName = TEXT("Shoot");
}
