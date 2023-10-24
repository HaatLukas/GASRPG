// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Interface/LC_CombatInterface.h"
#include "LC_Character_Base.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;
class UGameplayEffect;

UCLASS(ABSTRACT)
class AURA_API ALC_Character_Base : public ACharacter, public IAbilitySystemInterface, public ILC_CombatInterface
{
	GENERATED_BODY()

public:
	ALC_Character_Base();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }

protected:
	virtual void BeginPlay() override;
	virtual void InitAbiltyActorInfo();
	void InitVitalAttributes() const;
	void InitSecondaryAttributes() const;
	void InitAttributes() const;

	UPROPERTY(EditAnywhere, Category="Weapon")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
	TSubclassOf<UGameplayEffect> VitalAttributesClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
	TSubclassOf<UGameplayEffect> SecondaryAttributesClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
	TSubclassOf<UGameplayEffect> InitAttributesClass;


	

};
