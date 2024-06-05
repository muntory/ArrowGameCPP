// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Creature.h"
#include "MyEnemy.generated.h"

UCLASS()
class ARROWGAMECPP_API AMyEnemy : public ACreature
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyEnemy();
public:
	virtual void Attack() override;
	virtual void OnAttack() override;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
