// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Creature.generated.h"

UCLASS()
class ARROWGAMECPP_API ACreature : public ACharacter
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere)
	bool IsAttacking = false;
	UPROPERTY(VisibleAnywhere)
	class UCreatureAnimInstance* CreatureAnimInstance;
	UPROPERTY(VisibleAnywhere)
	class UMyActorComponent* MyActorComponent;
	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent* HpBar;



public:
	// Sets default values for this character's properties
	ACreature();
	bool GetIsAttacking() const { return IsAttacking; }
	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	UFUNCTION()
	virtual void Attack();
	UFUNCTION()
	virtual void OnAttack(); 
public:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
