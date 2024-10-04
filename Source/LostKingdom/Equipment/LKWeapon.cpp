// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/LKWeapon.h"
#include "Components/CapsuleComponent.h"
#include "Interface/LKDamageInterface.h"
#include "Character/LKCharacterBase.h"
#include "CharacterStat/LKCharacterStatComponent.h"

ALKWeapon::ALKWeapon()
{
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	RootComponent = WeaponMesh;

	WeaponComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("WeaponCollision"));
	WeaponComponent->SetCollisionProfileName(TEXT("NoCollision"));
	WeaponComponent->SetupAttachment(RootComponent);
}

void ALKWeapon::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	WeaponComponent->OnComponentBeginOverlap.AddDynamic(this, &ALKWeapon::OnAttack);
}

void ALKWeapon::OnAttack(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && WeaponOwner)
	{
		float Damage = WeaponOwner->Stat->GetAttack();

		ILKDamageInterface* DamagedActor = Cast<ILKDamageInterface>(OtherActor);
		if (DamagedActor && DamagedActor->OnDamaged(WeaponOwner, Damage))
		{
			WeaponOwner->AttackSuccess();
		}
	}
}

void ALKWeapon::Attack()
{
	
}

void ALKWeapon::StopAttack()
{
	WeaponComponent->SetCollisionProfileName(TEXT("NoCollision"));
}


