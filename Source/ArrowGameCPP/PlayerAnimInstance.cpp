// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "MyPlayer.h"

void UPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

}

void UPlayerAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	auto Pawn = TryGetPawnOwner();

	if (IsValid(Pawn))
	{
		MyPlayer = Cast<AMyPlayer>(Pawn);

		if (IsValid(MyPlayer))
		{
			CharacterMovement = MyPlayer->GetCharacterMovement();
		}
	}
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (IsValid(MyPlayer))
	{
		Velocity = CharacterMovement->Velocity;
		FRotator Rotation = MyPlayer->GetActorRotation();
		FVector UnRotateVector = Rotation.UnrotateVector(Velocity);
		UnRotateVector.Normalize();

		Vertical = UnRotateVector.X;
		Horizontal = UnRotateVector.Y;
		Speed = Velocity.Size2D();

		auto Acceleration = CharacterMovement->GetCurrentAcceleration();
		ShouldMove = Speed > 3.f && Acceleration != FVector::Zero();
		IsFalling = CharacterMovement->IsFalling();

		AimRotation = MyPlayer->GetBaseAimRotation();
		FRotator VelocityRotation = UKismetMathLibrary::MakeRotFromX(Velocity);

		FRotator DeltaRotation = VelocityRotation - AimRotation;
		DeltaRotation.Normalize();

		YawOffset = DeltaRotation.Yaw;

		if (ShouldMove || IsFalling)
		{
			RotateYaw = FMath::FInterpTo(RotateYaw, 0.f, DeltaSeconds, 20.f);
			PrevRotation = MovingRotation;
			MovingRotation = MyPlayer->GetActorRotation();

		}
		else
		{

			PrevRotation = MovingRotation;
			MovingRotation = MyPlayer->GetActorRotation();
			FRotator Delta = MovingRotation - PrevRotation;
			Delta.Normalize();
			RotateYaw -= Delta.Yaw;

			PrevDistanceCurve = DistanceCurve;
			DistanceCurve = GetCurveValue(TEXT("DistanceCurve"));
			DeltaDistanceCurve = DistanceCurve - PrevDistanceCurve;

			float TurnValue = GetCurveValue(TEXT("Turn"));

			if (TurnValue > 0.f)
			{
				if (RotateYaw > 0.f)
				{
					RotateYaw -= DeltaDistanceCurve;
				}
				else
				{
					RotateYaw += DeltaDistanceCurve;
				}

				float AbsRotateYawOffset = FMath::Abs(RotateYaw);
				if (AbsRotateYawOffset > 0.f)
				{
					float YawExcess = AbsRotateYawOffset - 90.f;
					if (RotateYaw > 0.f)
					{
						RotateYaw -= YawExcess;
					}
					else
					{
						RotateYaw += YawExcess;
					}
				}
			}
		}
	}
}

UPlayerAnimInstance::UPlayerAnimInstance()
{
	ConstructorHelpers::FObjectFinder<UAnimMontage> AM(TEXT("/Script/Engine.AnimMontage'/Game/ParagonSparrow/Characters/Heroes/Sparrow/Animations/Primary_Fire_Med_Montage.Primary_Fire_Med_Montage'"));
	if (AM.Succeeded())
	{
		AttackMontage = AM.Object;
	}
}
