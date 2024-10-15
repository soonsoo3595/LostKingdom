// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/LKCharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CharacterStat/LKCharacterStatComponent.h"
#include "UI/LKWidgetComponent.h"
#include "UI/LKHUDWidget.h"
#include "Skill/LKBaseSkill.h"	
#include "Skill/LKSkillData.h"
#include "Buff/LKBaseBuff.h"
#include "Equipment/LKWeapon.h"

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

	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));

	// Stat
	Stat = CreateDefaultSubobject<ULKCharacterStatComponent>(TEXT("Stat"));
	bIsDead = false;

	// Widget
	HUD = CreateDefaultSubobject<ULKWidgetComponent>(TEXT("HUD"));
	HUD->SetupAttachment(GetMesh(), TEXT("HealthBar"));
	HUD->SetRelativeLocation(FVector(0.0f, 0.0f, 80.0f));
	static ConstructorHelpers::FClassFinder<UUserWidget> HUDWidgetRef(TEXT("/Game/LostKingdom/UI/WBP_HUD.WBP_HUD_C"));
	if (HUDWidgetRef.Class)
	{
		HUD->SetWidgetClass(HUDWidgetRef.Class);
		HUD->SetWidgetSpace(EWidgetSpace::Screen);
		HUD->SetDrawSize(FVector2D(150.0f, 50.0f));
		HUD->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	bUseSkill = false;
}

void ALKCharacterBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	AnimInstance = GetMesh()->GetAnimInstance();

	if (Stat)
	{
		Stat->OnHPZero.AddUObject(this, &ALKCharacterBase::SetDead);
	}
}

void ALKCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	EquipWeapon();
}

void ALKCharacterBase::EquipWeapon()
{
	if (WeaponClass)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();

		Weapon = GetWorld()->SpawnActor<ALKWeapon>(WeaponClass, SpawnParams);
		if (Weapon)
		{
			FName WeaponSocket(TEXT("WeaponSocket"));
			Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, WeaponSocket);
			Weapon->SetWeaponOwner(this);
		}
	}
}

/// <summary>
/// 플레이어 컨트롤러에서 공격 입력이 들어오면 호출되는 함수
/// </summary>
void ALKCharacterBase::ProcessCombo()
{
	if (bUseSkill) return;

	if (CurrentCombo == 0)
	{
		ComboAttackBegin();
		return;
	}

	HasNextComboInput = true;
}

void ALKCharacterBase::AttackStart()
{
	if (Weapon)
	{
		Weapon->Attack();
	}
}

void ALKCharacterBase::AttackEnd()
{
	if (Weapon)
	{
		Weapon->StopAttack();
	}
}


bool ALKCharacterBase::OnDamaged(AActor* DamageCauser, float Damage)
{
	if (DamageCauser)
	{
		float ActualDamage = Stat->ApplyDamage(Damage);
		UE_LOG(LogTemp, Log, TEXT("Actual Damage: %f"), ActualDamage);

		if (bIsDead)
		{
			ALKCharacterBase* Causer = Cast<ALKCharacterBase>(DamageCauser);
			if (Causer)
			{
				Causer->Stat->AddExp(Stat->GetBaseStat().Exp);
			}
		}

		return true;
	}

	return false;
}

void ALKCharacterBase::AttackSuccess()
{
}

void ALKCharacterBase::ComboAttackBegin()
{
	LookAt();
	CurrentCombo = 1;

	// 애니메이션 세팅
	const float AttackSpeed = Stat->GetSpeed();
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

bool ALKCharacterBase::UseSkill(ULKBaseSkill* Skill)
{
	if (Skill)
	{
		// If you are using the skill, you will return false, but if the skill can be canceled, proceed as it is
		if (bUseSkill && Skill->Data->bCanCancel == false)
		{
			return false;
		}

		GetController()->StopMovement();
		LookAt();
		bUseSkill = true;
		CurrentSkill = Skill;
		Skill->Use(this);
	}

	return true;
}

void ALKCharacterBase::OnSkillEnd(UAnimMontage* TargetMontage, bool IsProperlyEnded)
{
	CurrentSkill = nullptr;
	bUseSkill = false;
}

void ALKCharacterBase::SkillAttack()
{
	if (CurrentSkill)
	{
		CurrentSkill->Attack(this);
	}
}

void ALKCharacterBase::AddBuff(ULKBaseBuff* Buff)
{
	if (Buff)
	{
		if (ActiveBuffs.Contains(Buff) == false)
		{
			ActiveBuffs.Add(Buff);
			Buff->OnBuffStart(this);
		}
		else
		{
			Buff->OnBuffReset();
		}

		OnBuffAdded.Broadcast(Buff);
	}
}

void ALKCharacterBase::RemoveBuff(ULKBaseBuff* Buff)
{
	if (Buff)
	{
		if (ActiveBuffs.Contains(Buff))
		{
			ActiveBuffs.Remove(Buff);
			OnBuffRemoved.Broadcast(Buff);
		}
	}
}

void ALKCharacterBase::SetDead()
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	PlayDeadAnimation();
	SetActorEnableCollision(false);
	HUD->SetHiddenInGame(true);

	bIsDead = true;
}

void ALKCharacterBase::PlayDeadAnimation()
{
	AnimInstance->StopAllMontages(0.0f);
	AnimInstance->Montage_Play(DeadMontage);
}

void ALKCharacterBase::SetupCharacterWidget(ULKUserWidget* InUserWidget)
{
	ULKHUDWidget* HUDWidget = Cast<ULKHUDWidget>(InUserWidget);
	if (HUDWidget)
	{
		HUDWidget->SetMaxHP(Stat->GetFinalStat().MaxHP);
		HUDWidget->UpdateHPBar(Stat->GetCurrentHp());
		HUDWidget->SetCharacterName(Stat->GetCharacterName());

		Stat->OnHPChanged.AddUObject(HUDWidget, &ULKHUDWidget::UpdateHPBar);
	}
}

