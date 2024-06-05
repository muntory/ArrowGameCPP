// Fill out your copyright notice in the Description page of Project Settings.


#include "MyEnemy.h"
#include "Components/CapsuleComponent.h"
#include "MyAIController.h"
#include "EnemyAnimInstance.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMyEnemy::AMyEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Goblin/Mesh/Goblin_Base/SK_Goblin.SK_Goblin'"));

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Character"));

	if (SkeletalMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SkeletalMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -69.f), FRotator(0.f, -90.f, 0.f));
		GetCapsuleComponent()->SetCapsuleHalfHeight(68.f);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> AI(TEXT("/Script/Engine.AnimBlueprint'/Game/Animation/Enemy/ABP_Goblin.ABP_Goblin_C'"));
	if (AI.Succeeded())
	{
		GetMesh()->SetAnimClass(AI.Class);
	}

	AIControllerClass = AMyAIController::StaticClass();



}

void AMyEnemy::Attack()
{
	Super::Attack();
}

void AMyEnemy::OnAttack()
{
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);

	float AttackRange = 100.f;
	float AttackRadius = 50.f;

	bool Result = GetWorld()->SweepSingleByChannel
	(
		OUT HitResult,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * AttackRange,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(AttackRadius),
		Params
	);

	FVector Center = GetActorLocation();
	FVector Forward = GetActorLocation() + GetActorForwardVector() * AttackRange;

	float HalfHeight = AttackRange * 0.5f + AttackRange;
	FQuat Rotation = FRotationMatrix::MakeFromZ(Forward).ToQuat();
	FColor DrawColor;


	if (Result && HitResult.GetActor())
	{
		DrawColor = FColor::Green;

		AActor* HitActor = HitResult.GetActor();
		UGameplayStatics::ApplyDamage(HitActor, 10.f, GetController(), nullptr, NULL);
	}
	else
	{
		DrawColor = FColor::Red;
	}
	DrawDebugCapsule(GetWorld(), Center, HalfHeight, AttackRadius, Rotation, DrawColor, false, 0.2f);
}


// Called when the game starts or when spawned
void AMyEnemy::BeginPlay()
{
	Super::BeginPlay();

	CreatureAnimInstance = Cast<UEnemyAnimInstance>(GetMesh()->GetAnimInstance());
	CreatureAnimInstance->OnMontageEnded.AddUniqueDynamic(this, &AMyEnemy::OnAttackMontageEnded);
	CreatureAnimInstance->OnAttack.AddUObject(this, &AMyEnemy::OnAttack);
	
}

// Called every frame
void AMyEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

