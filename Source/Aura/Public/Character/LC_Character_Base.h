// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "LC_Character_Base.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;

UCLASS(ABSTRACT)
class AURA_API ALC_Character_Base : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ALC_Character_Base();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }

protected:
	virtual void BeginPlay() override;
	virtual void InitAbiltyActorInfo();

	UPROPERTY(EditAnywhere, Category="Weapon")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;



};
