// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Engine/DataTable.h"

UMyGameInstance::UMyGameInstance()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DT(TEXT("/Script/Engine.DataTable'/Game/Data/DT_PlayerInfo.DT_PlayerInfo'"));

	if (DT.Succeeded())
	{
		PlayerDataTable = DT.Object;
	}
}

void UMyGameInstance::Init()
{
	Super::Init();
	GetPlayerData(1);
}



FMyPlayerData* UMyGameInstance::GetPlayerData(int32 InLevel)
{
	FName RowName = FName(*FString::Printf(TEXT("Lv%d"), InLevel));

	return PlayerDataTable->FindRow<FMyPlayerData>(RowName, TEXT(""));
}
