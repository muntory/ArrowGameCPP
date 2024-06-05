// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CreatureAnimInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttack);

UCLASS()
class ARROWGAMECPP_API UCreatureAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere)
	UAnimMontage* AttackMontage;
public:
	UCreatureAnimInstance();
public:
	FOnAttack OnAttack;
public:
	void PlayAttackMontage();
	UFUNCTION()
	void AnimNotify_Attack();
	
};
