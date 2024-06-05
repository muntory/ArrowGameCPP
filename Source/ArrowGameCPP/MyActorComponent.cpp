// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActorComponent.h"
#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UMyActorComponent::UMyActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
	Level = 1;
}


// Called when the game starts
void UMyActorComponent::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Log, TEXT("ActorComponent"));

}

void UMyActorComponent::InitializeComponent()
{
	Super::InitializeComponent();
	SetLevel(Level);
}

void UMyActorComponent::SetHp(int32 InHp)
{
	Hp = InHp;
	if (Hp < 0)
	{
		Hp = 0;
	}

	OnHpChanged.Broadcast();
}

void UMyActorComponent::SetLevel(int32 InLevel)
{
	auto MyGameInstace = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (MyGameInstace)
	{
		auto PlayerData = MyGameInstace->GetPlayerData(InLevel);
		if (PlayerData)
		{
			Level = PlayerData->Level;
			MaxHp = PlayerData->MaxHp;
			Hp = MaxHp;
		}
	}


}

void UMyActorComponent::OnDamaged(float Damage)
{
	SetHp(Hp - Damage);
	
}

float UMyActorComponent::GetHpRatio() const
{
	if (MaxHp == 0)
		return 0.f;
	return (float)Hp / (float)MaxHp;
}


// Called every frame
void UMyActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

