// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/LKEnemyCharacter.h"
#include "Components/CapsuleComponent.h"
#include "CharacterStat/LKEnemyStatComponent.h"

ALKEnemyCharacter::ALKEnemyCharacter()
{
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("LKEnemy"));
}

void ALKEnemyCharacter::AttackStart()
{
	Super::AttackStart();
	WeaponComponent->SetCollisionProfileName(TEXT("LKEnemyAttack"));
}
