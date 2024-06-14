// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/LKCharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/DamageEvents.h"

// Sets default values
ALKCharacterBase::ALKCharacterBase()
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 640.0f, 0.0f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/Mannequins/Meshes/SKM_Quinn.SKM_Quinn'"));
	if (CharacterMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(CharacterMeshRef.Object);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> CharacterAnimRef(TEXT("/Game/LostKingdom/Animation/ABP_LKCharacter.ABP_LKCharacter_C"));
	if (CharacterAnimRef.Class)
	{
		GetMesh()->SetAnimInstanceClass(CharacterAnimRef.Class);
	}

	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));

	WeaponComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("WeaponCollision"));
	WeaponComponent->SetupAttachment(GetMesh(), TEXT("WeaponSocket"));
	WeaponComponent->SetCollisionProfileName(TEXT("NoCollision"));

	bIsDebouncing = false;
}

void ALKCharacterBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	AnimInstance = GetMesh()->GetAnimInstance();

	WeaponComponent->OnComponentBeginOverlap.AddDynamic(this, &ALKCharacterBase::OnAttack);
}

/// <summary>
/// 플레이어 컨트롤러에서 공격 입력이 들어오면 호출되는 함수
/// </summary>
void ALKCharacterBase::ProcessCombo()
{
	// 디바운스 처리를 해서 마우스를 짧게 눌러도 한번만 입력되도록 함
	if (bIsDebouncing)	return;

	bIsDebouncing = true;

	GetWorldTimerManager().SetTimer(DebounceTimerHandle, this, &ALKCharacterBase::ResetDebounce, 0.2f, false);


	if (CurrentCombo == 0)
	{
		ComboAttackBegin();
		return;
	}

	HasNextComboInput = true;
}

void ALKCharacterBase::AttackStart()
{
}

void ALKCharacterBase::AttackEnd()
{
	WeaponComponent->SetCollisionProfileName(TEXT("NoCollision"));
}

/// <summary>
/// 몽타주에서 노티파이 이벤트가 발생하면 ComboCheck를 호출 
/// </summary>
void ALKCharacterBase::ComboAttackCheck()
{
	ComboCheck();
}

void ALKCharacterBase::OnAttack(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("OtherActor : %s %d"), *OtherActor->GetName(), CurrentCombo);

	if (OtherActor)
	{
		ALKCharacterBase* Enemy = Cast<ALKCharacterBase>(OtherActor);
		if (Enemy)
		{
			FDamageEvent DamageEvent;
			Enemy->TakeDamage(10.0f, DamageEvent, GetController(), this);
		}
	}
}

void ALKCharacterBase::ComboAttackBegin()
{
	LookAt();
	CurrentCombo = 1;

	// 애니메이션 세팅
	const float AttackSpeed = 1.0f;		// 속도 특성 있을 경우 변경
	AnimInstance->Montage_Play(AttackMontage, AttackSpeed);

	// 몽타주가 종료되면 ComboAttackEnd 함수 호출
	// 구조체 선언하고 함수 바인딩
	FOnMontageEnded EndDelegate;
	EndDelegate.BindUObject(this, &ALKCharacterBase::ComboAttackEnd);
	AnimInstance->Montage_SetEndDelegate(EndDelegate, AttackMontage);
}

/// <summary>
/// 콤보	공격이 끝나면 호출되는 함수(몽타주 종료 시 호출)
/// </summary>
void ALKCharacterBase::ComboAttackEnd(UAnimMontage* TargetMontage, bool IsProperlyEnded)
{
	CurrentCombo = 0;
}

/// <summary>
/// 콤보 체크할 때 이전에 입력이 들어왔다면 다음 콤보를 실행
/// </summary>
void ALKCharacterBase::ComboCheck()
{
	if (HasNextComboInput)
	{
		LookAt();
		CurrentCombo = FMath::Clamp(CurrentCombo + 1, 1, MaxCombo);

		FName NextSection = *FString::Printf(TEXT("ComboAttack%d"), CurrentCombo);
		AnimInstance->Montage_JumpToSection(NextSection, AttackMontage);
		HasNextComboInput = false;
	}
}

/// <summary>
/// 캐릭터가 마우스를 클릭한 곳으로 보게 함. Yaw 회전만 변경
/// </summary>
void ALKCharacterBase::LookAt()
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

float ALKCharacterBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	SetDead();

	return DamageAmount;
}

void ALKCharacterBase::SetDead()
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	PlayDeadAnimation();
	SetActorEnableCollision(false);
}

void ALKCharacterBase::PlayDeadAnimation()
{
	AnimInstance->StopAllMontages(0.0f);
	AnimInstance->Montage_Play(DeadMontage);
}
