// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/LKEnemyCharacter.h"
#include "Components/CapsuleComponent.h"

ALKEnemyCharacter::ALKEnemyCharacter()
{
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("LKEnemy"));
}
