// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/LKPlayerWeapon.h"
#include "Components/CapsuleComponent.h"

void ALKPlayerWeapon::Attack()
{
	WeaponComponent->SetCollisionProfileName(TEXT("LKPlayerAttack"));
}
