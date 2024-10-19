// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/LKAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

ULKAnimInstance::ULKAnimInstance()
{
	IdleTime = 0.f;
	MovingThreshold = 3.f;
}

void ULKAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Owner = Cast<ACharacter>(GetOwningActor());
	if (Owner)
	{
		Movement = Owner->GetCharacterMovement();
	}
}

void ULKAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Movement)
	{
		Velocity = Owner->GetVelocity();
		GroundSpeed = Velocity.Size2D();
		bIsIdle = GroundSpeed < MovingThreshold;

		if (bIsIdle)
		{
			IdleTime += DeltaSeconds;
			if (IdleTime > 5.f)
			{
				bIsResting = true;
			}
		}
		else
		{
			IdleTime = 0.f;
			bIsResting = false;
		}
	}
}
