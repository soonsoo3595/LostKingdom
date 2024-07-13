// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/LKCharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/DamageEvents.h"
#include "CharacterStat/LKCharacterStatComponent.h"
#include "UI/LKWidgetComponent.h"
#include "UI/LKHUDWidget.h"

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

	WeaponComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("WeaponCollision"));
	WeaponComponent->SetupAttachment(GetMesh(), TEXT("WeaponSocket"));
	WeaponComponent->SetCollisionProfileName(TEXT("NoCollision"));

	// Stat
	Stat = CreateDefaultSubobject<ULKCharacterStatComponent>(TEXT("Stat"));

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
}

void ALKCharacterBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	AnimInstance = GetMesh()->GetAnimInstance();

	WeaponComponent->OnComponentBeginOverlap.AddDynamic(this, &ALKCharacterBase::OnAttack);

	Stat->OnHPZero.AddUObject(this, &ALKCharacterBase::SetDead);
}

/// <summary>
/// 플레이어 컨트롤러에서 공격 입력이 들어오면 호출되는 함수
/// </summary>
void ALKCharacterBase::ProcessCombo()
{
	if (CurrentCombo == 0)
	{
		ComboAttackBegin();
		return;
	}

	HasNextComboInput = true;
}

void ALKCharacterBase::OnAttack(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// The more you attack in a row, the more damage you get
	const float AttackDamage = Stat->GetAttack() * CurrentCombo;
	UE_LOG(LogTemp, Warning, TEXT("Attack Damage: %f"), AttackDamage);

	if (OtherActor)
	{
		ALKCharacterBase* Enemy = Cast<ALKCharacterBase>(OtherActor);
		if (Enemy)
		{
			FDamageEvent DamageEvent;
			Enemy->TakeDamage(AttackDamage, DamageEvent, GetController(), this);
		}
	}
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

float ALKCharacterBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	Stat->ApplyDamage(DamageAmount);

	return DamageAmount;
}

void ALKCharacterBase::SetDead()
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	PlayDeadAnimation();
	SetActorEnableCollision(false);
	HUD->SetHiddenInGame(true);
}

void ALKCharacterBase::PlayDeadAnimation()
{
	AnimInstance->StopAllMontages(0.0f);
	AnimInstance->Montage_Play(DeadMontage);
}

void ALKCharacterBase::SetupCharacterWidget(ULKUserWidget* InUserWidget)
{
	ULKHUDWidget *HUDWidget = Cast<ULKHUDWidget>(InUserWidget);
	if (HUDWidget)
	{
		HUDWidget->SetMaxHP(Stat->GetFinalStat().MaxHP);
		HUDWidget->UpdateHPBar(Stat->GetCurrentHp());
		HUDWidget->SetCharacterName(Stat->GetCharacterName());

		Stat->OnHPChanged.AddUObject(HUDWidget, &ULKHUDWidget::UpdateHPBar);
	}
}
