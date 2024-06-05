// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
USTRUCT()
struct FMyPlayerData : public FTableRowBase
{
	GENERATED_BODY() 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Level;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxHp;
};

UCLASS()
class ARROWGAMECPP_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	class UDataTable* PlayerDataTable;
public:
	UMyGameInstance();
public:
	virtual void Init() override;
public:
	FMyPlayerData* GetPlayerData(int32 Level);
};










