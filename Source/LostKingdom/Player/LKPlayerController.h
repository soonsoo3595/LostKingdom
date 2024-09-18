// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "LKPlayerController.generated.h"

/**
 * 
 */

class UNiagaraSystem;

UCLASS()
class LOSTKINGDOM_API ALKPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ALKPlayerController();

	/** FX Class that we will spawn when clicking */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UNiagaraSystem* FXCursor;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Click Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SetDestinationClickAction;

	/** Zoom Action **/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ZoomAction;

	/** Attack Action**/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* AttackAction;

protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	/** Input handlers for SetDestination action. */
	void OnInputStarted();
	void OnSetDestinationTriggered();
	void OnSetDestinationReleased();

	/* Zoom */
	void OnZoomTriggered(const FInputActionValue& Value);
	void OnZoomIn();
	void OnZoomOut();

	/* Attack */
	void OnAttackTriggered();
	void OnAttackCompleted();

// HUD
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = HUD)
	TSubclassOf<class ULKMainHUD> MainHUDClass;

	UPROPERTY()
	TObjectPtr<class ULKMainHUD> MainHUD;

protected:
	UPROPERTY()
	TObjectPtr<class ALKPlayerCharacter> PlayerCharacter;

private:
	FVector Destination;
	/* Is Zoom in? */
	uint8 bZooming : 1;
};
