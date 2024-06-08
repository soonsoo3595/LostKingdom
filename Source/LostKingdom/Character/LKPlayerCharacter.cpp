// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/LKPlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

ALKPlayerCharacter::ALKPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; 

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	bZoomIn = false;
	bIsDebouncing = false;
}

void ALKPlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	AnimInstance = GetMesh()->GetAnimInstance();
}

void ALKPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bZoomIn)
	{
		CameraBoom->TargetArmLength = FMath::FInterpTo(CameraBoom->TargetArmLength, ZoomInArmLength, DeltaTime, 5.f);
		CameraBoom->SetRelativeRotation(FMath::RInterpTo(CameraBoom->GetRelativeRotation(), ZoomInRotation, DeltaTime, 5.f));
	}
	else
	{
		CameraBoom->TargetArmLength = FMath::FInterpTo(CameraBoom->TargetArmLength, ZoomOutArmLength, DeltaTime, 5.f);
		CameraBoom->SetRelativeRotation(FMath::RInterpTo(CameraBoom->GetRelativeRotation(), ZoomOutRotation, DeltaTime, 5.f));
	}
}

void ALKPlayerCharacter::Roll()
{
	AnimInstance->Montage_Play(RollMontage);
}

/// <summary>
/// 플레이어 컨트롤러에서 공격 입력이 들어오면 호출되는 함수
/// </summary>
void ALKPlayerCharacter::ProcessCombo()
{
	// 디바운스 처리를 해서 마우스를 짧게 눌러도 한번만 입력되도록 함
	if (bIsDebouncing)	return;

	bIsDebouncing = true;

	GetWorldTimerManager().SetTimer(DebounceTimerHandle, this, &ALKPlayerCharacter::ResetDebounce, 0.2f, false);

	if(CurrentCombo == 0)
	{
		ComboAttackBegin();
		return;
	}

	HasNextComboInput = true;
}

/// <summary>
/// 몽타주에서 노티파이 이벤트가 발생하면 ComboCheck를 호출 
/// </summary>
void ALKPlayerCharacter::NotifyCombo()
{
	ComboCheck();
}

void ALKPlayerCharacter::ComboAttackBegin()
{
	LookAt();
	CurrentCombo = 1;

	// 애니메이션 세팅
	const float AttackSpeed = 1.0f;		// 속도 특성 있을 경우 변경
	AnimInstance->Montage_Play(ComboAttackMontage, AttackSpeed);

	// 몽타주가 종료되면 ComboAttackEnd 함수 호출
	// 구조체 선언하고 함수 바인딩
	FOnMontageEnded EndDelegate;
	EndDelegate.BindUObject(this, &ALKPlayerCharacter::ComboAttackEnd);
	AnimInstance->Montage_SetEndDelegate(EndDelegate, ComboAttackMontage);
}

/// <summary>
/// 콤보	공격이 끝나면 호출되는 함수(몽타주 종료 시 호출)
/// </summary>
void ALKPlayerCharacter::ComboAttackEnd(UAnimMontage* TargetMontage, bool IsProperlyEnded)
{
	ensure(CurrentCombo != 0);
	CurrentCombo = 0;
}

/// <summary>
/// 콤보 체크할 때 이전에 입력이 들어왔다면 다음 콤보를 실행
/// </summary>
void ALKPlayerCharacter::ComboCheck()
{
	if (HasNextComboInput)
	{
		LookAt();
		CurrentCombo = FMath::Clamp(CurrentCombo + 1, 1, MaxCombo);

		FName NextSection = *FString::Printf(TEXT("ComboAttack%d"), CurrentCombo);
		AnimInstance->Montage_JumpToSection(NextSection, ComboAttackMontage);
		HasNextComboInput = false;
	}
}

/// <summary>
/// 캐릭터가 마우스를 클릭한 곳으로 보게 함. Yaw 회전만 변경
/// </summary>
void ALKPlayerCharacter::LookAt()
{
	APlayerController* PlayerController = CastChecked<APlayerController>(GetController());
	
	FHitResult Hit;
	bool bHitSuccessful = PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);

	if (bHitSuccessful)
	{
		FVector Cursor = Hit.Location;
		FVector CharacterLocation = GetActorLocation();

		FVector Direction = (Cursor - CharacterLocation).GetSafeNormal();
		FRotator NewRotation = Direction.Rotation();

		FRotator CurrentRotation = GetActorRotation();
		CurrentRotation.Yaw = NewRotation.Yaw;

		SetActorRotation(CurrentRotation);
	}
}
