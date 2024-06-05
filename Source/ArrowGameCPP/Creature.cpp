// Fill out your copyright notice in the Description page of Project Settings.


#include "Creature.h"
#include "MyActorComponent.h"
#include "CreatureAnimInstance.h"
#include "Components/WidgetComponent.h"
#include "MyUserWidget.h"




void ACreature::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	IsAttacking = false;

}

// Sets default values
ACreature::ACreature()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

	MyActorComponent = CreateDefaultSubobject<UMyActorComponent>(TEXT("MyActorComponent"));

	HpBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HpBar"));
	HpBar->SetupAttachment(GetMesh());
	HpBar->SetWidgetSpace(EWidgetSpace::Screen);
	static ConstructorHelpers::FClassFinder<UMyUserWidget> MyUW(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/WBP_HpBar.WBP_HpBar_C'"));

	if (MyUW.Succeeded())
	{
		HpBar->SetWidgetClass(MyUW.Class);
		HpBar->SetDrawSize(FVector2D(200.f, 20.f));
		HpBar->SetRelativeLocation(FVector(0.f, 0.f, 200.f));
	}
}

void ACreature::Attack()
{
	if (!IsAttacking)
	{
		if (IsValid(CreatureAnimInstance))
		{

			CreatureAnimInstance->PlayAttackMontage();

		}
	}
}

void ACreature::OnAttack()
{
	UE_LOG(LogTemp, Log, TEXT("On Attack"));
}

float ACreature::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	MyActorComponent->OnDamaged(DamageAmount);
	return DamageAmount;
}

// Called when the game starts or when spawned
void ACreature::BeginPlay()
{
	Super::BeginPlay();
	CreatureAnimInstance = Cast<UCreatureAnimInstance>(GetMesh()->GetAnimInstance());
	if (CreatureAnimInstance)
	{
		CreatureAnimInstance->OnMontageEnded.AddUniqueDynamic(this, &ACreature::OnAttackMontageEnded);
		CreatureAnimInstance->OnAttack.AddUObject(this, &ACreature::OnAttack);
	}
	
	auto HpWidget = Cast<UMyUserWidget>(HpBar->GetUserWidgetObject());
	if (HpWidget)
	{
		HpWidget->BindHp(MyActorComponent);
	}
}

// Called every frame
void ACreature::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACreature::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

