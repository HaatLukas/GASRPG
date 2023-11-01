// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"
#include "LC_PlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class IHoverInterface;
class ULC_InputDataAsset;
class ULC_AbilitySystemComponent;
class USplineComponent;
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

	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<ULC_InputDataAsset> InputDataAsset;

	UPROPERTY()
	TObjectPtr<ULC_AbilitySystemComponent> LC_AbilitySystemComponent;

	ULC_AbilitySystemComponent* GetASC();

private:
	FVector CachedDestination = FVector::ZeroVector;
	bool bAutoRunning = false;
	bool bTargeting = false;
	float ShortClickThreshold = 0.5f;
	float RunningTime = 0.f;
	UPROPERTY(EditDefaultsOnly)
	float AutoRunAcceptanceRadius = 50.f;
	TObjectPtr<USplineComponent> Spline;
	FHitResult CursorHit;

	void AutoRun();

};
