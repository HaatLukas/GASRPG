// Copyright Curyło Łukasz


#include "LC_GameplayTags.h"
#include "GameplayTagsManager.h"

FLC_GameplayTags FLC_GameplayTags::GameplayTags;


void FLC_GameplayTags::InitializeNativeGameplayTags()
{
	// Main Attributes

	GameplayTags.Attributes_Main_Vitality = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Main.Vitality"), FString("Increases character health potions and regeneration"));
	GameplayTags.Attributes_Main_Persistence = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Main.Persistance"), FString("Increases the toughness of the character"));
	GameplayTags.Attributes_Main_Intelligence = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Main.Intelligence"), FString("Increases the maximum mana and magic damage"));
	GameplayTags.Attributes_Main_Strength = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Main.Strength"), FString("Increases physical damage"));
	

	//Secondary Atttributes
	GameplayTags.Attributes_Secondary_CriticalHitChance =  UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CritChance"),FString("Percantge chance to deal double physical damage"));
	GameplayTags.Attributes_Secondary_CriticalHitResistance = UGameplayTagsManager::Get(). AddNativeGameplayTag(FName("Attributes.Secondary.CritResistance"),FString("Percantge chance to avoid critical damage"));
	GameplayTags.Attributes_Secondary_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Armor"),FString("Shows the toughness of the character against physical attacks"));
	GameplayTags.Attributes_Secondary_HealthRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.HPRegen"),FString("Amount of HP that is recovered per second"));
	GameplayTags.Attributes_Secondary_ManaRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MPRegen"),FString("Amount of MP that is recovered per second"));
	GameplayTags.Attributes_Secondary_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxHealth"),FString("Indicates how many health a character can have during game"));
	GameplayTags.Attributes_Secondary_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxMana"),FString("Indicates how many mana a character can have during game"));
}
