// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Equipment/LKEquipment.h"
#include "LKWeapon.generated.h"

UCLASS()
class LOSTKINGDOM_API ALKWeapon : public ALKEquipment
{
	GENERATED_BODY()
	
public:	
	ALKWeapon();

protected:
	virtual void PostInitializeComponents() override;

	UFUNCTION()
	virtual void OnAttack(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	virtual void Attack();
	virtual void StopAttack();
	FORCEINLINE void SetWeaponOwner(class ALKCharacterBase* InOwner) { WeaponOwner = InOwner; }
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	TObjectPtr<class UStaticMeshComponent> WeaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
	TObjectPtr<class UCapsuleComponent> WeaponComponent;

	UPROPERTY()
	TObjectPtr<class ALKCharacterBase> WeaponOwner;
};
