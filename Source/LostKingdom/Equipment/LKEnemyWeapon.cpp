// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/LKEnemyWeapon.h"
#include "Components/CapsuleComponent.h"

void ALKEnemyWeapon::Attack()
{
	WeaponComponent->SetCollisionProfileName(TEXT("LKEnemyAttack"));
}
