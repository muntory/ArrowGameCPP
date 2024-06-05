// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "MyEnemy.h"

UEnemyAnimInstance::UEnemyAnimInstance()
{
	ConstructorHelpers::FObjectFinder<UAnimMontage> AM(TEXT("/Script/Engine.AnimMontage'/Game/Animation/Enemy/AM_Goblin_body_attack_slash1_Montage.AM_Goblin_body_attack_slash1_Montage'"));

	if (AM.Succeeded())
	{
		AttackMontage = AM.Object;
	}



}

void UEnemyAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	auto Pawn = TryGetPawnOwner();

	if (IsValid(Pawn))
	{
		MyEnemy = Cast<AMyEnemy>(Pawn);

		if (IsValid(MyEnemy))
		{
			CharacterMovement = MyEnemy->GetCharacterMovement();
		}

	}
}

void UEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (IsValid(MyEnemy))
	{
		Velocity = CharacterMovement->Velocity;
		GroundSpeed = CharacterMovement->Velocity.Size2D();

		//auto Acceleration = CharacterMovement->GetCurrentAcceleration();
		ShouldMove = GroundSpeed > 3.f;
		IsFalling = CharacterMovement->IsFalling();

		
	}
}


