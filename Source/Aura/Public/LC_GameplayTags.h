// Copyright Curyło Łukasz

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * Singleton containing native Gameplay Tags
 */

struct FLC_GameplayTags
{
public:
	static const FLC_GameplayTags& Get() { return GameplayTags; }
	static void InitializeNativeGameplayTags();
	static FLC_GameplayTags GameplayTags;

	FGameplayTag Attributes_Main_Strength;
	FGameplayTag Attributes_Main_Intelligence;
	FGameplayTag Attributes_Main_Persistence;
	FGameplayTag Attributes_Main_Vitality;

	FGameplayTag Attributes_Secondary_Armor;
	FGameplayTag Attributes_Secondary_CriticalHitChance;
	FGameplayTag Attributes_Secondary_CriticalHitResistance;
	FGameplayTag Attributes_Secondary_HealthRegeneration;
	FGameplayTag Attributes_Secondary_ManaRegeneration;
	FGameplayTag Attributes_Secondary_MaxHealth;
	FGameplayTag Attributes_Secondary_MaxMana;

	FGameplayTag InputTag_LMB;
	FGameplayTag InputTag_RMB;
	FGameplayTag InputTag_1;
	FGameplayTag InputTag_2;
	FGameplayTag InputTag_3;
	FGameplayTag InputTag_4;

private:
	
};