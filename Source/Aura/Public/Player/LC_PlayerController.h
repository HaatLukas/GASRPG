// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LC_PlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class IHoverInterface;

/**
 * 
 */
UCLASS()
class AURA_API ALC_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ALC_PlayerController();
	virtual void PlayerTick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
private:
	UPROPERTY (EditAnywhere,Category="Input")
	TObjectPtr<UInputMappingContext> PlayerInputContext;
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	void Move(const struct FInputActionValue& InputActionValue);
	void CursorTrace();

	IHoverInterface* LastActor;
	IHoverInterface* CurrentActor;

};
