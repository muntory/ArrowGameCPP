// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack.h"
#include "MyAIController.h"
#include "MyEnemy.h"

UBTTask_Attack::UBTTask_Attack()
{
	bNotifyTick = true;


	NodeName = TEXT("Attack");
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);
	
	
	if (MyEnemy == nullptr)
	{
		MyEnemy = Cast<AMyEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	}

	if (MyEnemy == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	if (!MyEnemy->GetIsAttacking())
	{
		MyEnemy->Attack();
		return EBTNodeResult::InProgress;
		UE_LOG(LogTemp, Log, TEXT("Attack"));
	}

	return Result;
}

void UBTTask_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (MyEnemy == nullptr)
	{
		MyEnemy = Cast<AMyEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	}

	if (MyEnemy == nullptr)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}

	if (!MyEnemy->GetIsAttacking())
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
	
	
}
