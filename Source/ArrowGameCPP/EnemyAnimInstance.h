// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CreatureAnimInstance.h"
#include "EnemyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class ARROWGAMECPP_API UEnemyAnimInstance : public UCreatureAnimInstance
{
	GENERATED_BODY()
private:
	UPROPERTY(Category = "Animation", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	float GroundSpeed;
	UPROPERTY(Category = "Animation", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	bool ShouldMove;
	UPROPERTY(Category = "Animation", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	bool IsFalling;
	UPROPERTY(Category = "Animation", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	FVector Velocity;
private:
	UPROPERTY(VisibleAnywhere)
	class AMyEnemy* MyEnemy;
	UPROPERTY(VisibleAnywhere)
	class UCharacterMovementComponent* CharacterMovement;



public:
	UEnemyAnimInstance();
public:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

};
