// Fill out your copyright notice in the Description page of Project Settings.


#include "CreatureAnimInstance.h"

UCreatureAnimInstance::UCreatureAnimInstance()
{
}

void UCreatureAnimInstance::PlayAttackMontage()
{
	if (IsValid(AttackMontage))
	{
		if (!Montage_IsPlaying(AttackMontage))
		{
			Montage_Play(AttackMontage);
		}
	}
}

void UCreatureAnimInstance::AnimNotify_Attack()
{
	OnAttack.Broadcast();
}


