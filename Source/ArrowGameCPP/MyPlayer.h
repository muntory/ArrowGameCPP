// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Creature.h"
#include "MyPlayer.generated.h"

/**
 * 
 */
UCLASS()
class ARROWGAMECPP_API AMyPlayer : public ACreature
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* Camera;

public:
	AMyPlayer();
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
public:
	void KeyUpDown(float value);
	void KeyLeftRight(float value);
	void MouseLookUpDown(float value);
	void MouseLookLeftRight(float value);
public:
	virtual void Attack() override;
	virtual void OnAttack() override;

};
