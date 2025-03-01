// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "MyCharacter.h"

void UMyAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

}

void UMyAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	auto Pawn = TryGetPawnOwner();

	if (IsValid(Pawn))
	{
		MyCharacter = Cast<AMyCharacter>(Pawn);
		
		if (IsValid(MyCharacter))
		{
			CharacterMovement = MyCharacter->GetCharacterMovement();
		}
	}
}

void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (IsValid(MyCharacter))
	{
		Velocity = CharacterMovement->Velocity;
		FRotator Rotation = MyCharacter->GetActorRotation();
		FVector UnRotateVector = Rotation.UnrotateVector(Velocity);
		UnRotateVector.Normalize();

		Vertical = UnRotateVector.X;
		Horizontal = UnRotateVector.Y;
		Speed = Velocity.Size2D();

		auto Acceleration = CharacterMovement->GetCurrentAcceleration();
		ShouldMove = Speed > 3.f && Acceleration != FVector::Zero();
		IsFalling = CharacterMovement->IsFalling();

		AimRotation = MyCharacter->GetBaseAimRotation();
		FRotator VelocityRotation = UKismetMathLibrary::MakeRotFromX(Velocity);

		FRotator DeltaRotation = VelocityRotation - AimRotation;
		DeltaRotation.Normalize();

		YawOffset = DeltaRotation.Yaw;

		if (ShouldMove || IsFalling)
		{
			RotateYaw = FMath::FInterpTo(RotateYaw, 0.f, DeltaSeconds, 20.f);
			PrevRotation = MovingRotation;
			MovingRotation = MyCharacter->GetActorRotation();

		}
		else
		{

			PrevRotation = MovingRotation;
			MovingRotation = MyCharacter->GetActorRotation();
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

UMyAnimInstance::UMyAnimInstance()
{
	ConstructorHelpers::FObjectFinder<UAnimMontage> AnimMontage(TEXT("/Script/Engine.AnimMontage'/Game/ParagonSparrow/Characters/Heroes/Sparrow/Animations/Primary_Fire_Med_Montage.Primary_Fire_Med_Montage'"));

	if (AnimMontage.Succeeded())
	{
		FireMontage = AnimMontage.Object;
	}
}



void UMyAnimInstance::PlayFireMontage()
{
	if (IsValid(FireMontage))
	{
		if (!Montage_IsPlaying(FireMontage))
		{
			Montage_Play(FireMontage);
		}
	}
}
