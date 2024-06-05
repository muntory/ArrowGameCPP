// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindDestination.h"
#include "MyAIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FindDestination::UBTTask_FindDestination()
{
	NodeName = TEXT("FindPatrolDestination");
}

EBTNodeResult::Type UBTTask_FindDestination::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	
	auto CurrentPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (CurrentPawn != nullptr)
	{
		auto NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
		if (NavSystem != nullptr)
		{
			FNavLocation RandomLoction;
			if (NavSystem->GetRandomPointInNavigableRadius(CurrentPawn->GetActorLocation(), 500.f, RandomLoction))
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("Destination"), RandomLoction.Location);
				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
}
