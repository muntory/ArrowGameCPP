// Fill out your copyright notice in the Description page of Project Settings.


#include "MyUserWidget.h"
#include "MyActorComponent.h"
#include "Components/ProgressBar.h"

void UMyUserWidget::BindHp(UMyActorComponent* InMyActorComponent)
{
	MyActorComponent = InMyActorComponent;
	MyActorComponent->OnHpChanged.AddUObject(this, &UMyUserWidget::UpdateHp);
	UpdateHp();
}

void UMyUserWidget::UpdateHp()
{
	PB_HpBar->SetPercent(MyActorComponent->GetHpRatio());
}


