// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MyActorComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHpChanged)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARROWGAMECPP_API UMyActorComponent : public UActorComponent
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere, Category = "Info", meta = (AllowPrivateAccess = true))
	int32 Level = 1;
	UPROPERTY(EditAnywhere, Category = "Info", meta = (AllowPrivateAccess = true))
	int32 MaxHp = 100;
	UPROPERTY(EditAnywhere, Category = "Info", meta = (AllowPrivateAccess = true))
	int32 Hp = 50;

public:	
	// Sets default values for this component's properties
	UMyActorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;
public:
	FOnHpChanged OnHpChanged;
public:
	void SetHp(int32 InHp);
	void SetLevel(int32 InLevel);
	void OnDamaged(float Damage);
	int32 GetLevel() const { return Level; }
	int32 GetHp() const { return Hp; }
	int32 GetMaxHp() const { return MaxHp; }
	float GetHpRatio() const;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
