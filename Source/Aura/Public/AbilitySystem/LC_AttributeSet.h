// Copyright Curyło Łukasz

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "LC_GameplayTags.h"
#include "LC_AttributeSet.generated.h"

/**
 * 
 */

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


class FLC_GameplayTag;

template<class T>
using TStaticFunctionPtr = typename TBaseStaticDelegateInstance<T, FDefaultDelegateUserPolicy>::FFuncPtr;


USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()

	FEffectProperties() {}

	FGameplayEffectContextHandle EffectContextHandle;

	UPROPERTY()
	UAbilitySystemComponent* SourceASC = nullptr;

	UPROPERTY()
	AActor* SourceAvatarActor = nullptr;

	UPROPERTY()
	AController* SourceController = nullptr;

	UPROPERTY()
	ACharacter* SourceCharacter = nullptr;

	UPROPERTY()
	UAbilitySystemComponent* TargetASC = nullptr;

	UPROPERTY()
	AActor* TargetAvatarActor = nullptr;

	UPROPERTY()
	AController* TargetController = nullptr;

	UPROPERTY()
	ACharacter* TargetCharacter = nullptr;
};




UCLASS()
class AURA_API ULC_AttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	ULC_AttributeSet();
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;


	TMap<FGameplayTag, TStaticFunctionPtr<FGameplayAttribute()>> TagsToAttributes;

	//
	// Main Attributes
	//

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Strength, Category = "Main Attributes")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(ULC_AttributeSet, Strength);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Intelligence, Category = "Main Attributes")
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(ULC_AttributeSet, Intelligence);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Persistence, Category = "Main Attributes")
	FGameplayAttributeData Persistence;
	ATTRIBUTE_ACCESSORS(ULC_AttributeSet, Persistence);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Vitality, Category = "Main Attributes")
	FGameplayAttributeData Vitality;
	ATTRIBUTE_ACCESSORS(ULC_AttributeSet, Vitality);


	//
	// Main Attributes End
	//

	// Secondary Attributes Start

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MPRegen, Category = "Secondary Attributes")
	FGameplayAttributeData MPRegen;
	ATTRIBUTE_ACCESSORS(ULC_AttributeSet, MPRegen);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HPRegen, Category = "Secondary Attributes")
	FGameplayAttributeData HPRegen;
	ATTRIBUTE_ACCESSORS(ULC_AttributeSet, HPRegen);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CritChance, Category = "Secondary Attributes")
	FGameplayAttributeData CritChance;
	ATTRIBUTE_ACCESSORS(ULC_AttributeSet, CritChance);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Armor, Category = "Secondary Attributes")
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(ULC_AttributeSet, Armor);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CritResistance, Category = "Secondary Attributes")
	FGameplayAttributeData CritResistance;
	ATTRIBUTE_ACCESSORS(ULC_AttributeSet, CritResistance);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "HP/MP")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(ULC_AttributeSet, Health);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "HP/MP")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(ULC_AttributeSet, MaxHealth);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "HP/MP")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(ULC_AttributeSet, Mana);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "HP/MP")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(ULC_AttributeSet, MaxMana);


	// Secondary Attributes End

	UFUNCTION()
	void OnRep_Health(FGameplayAttributeData& OldHealth) const;
	UFUNCTION()
	void OnRep_MaxHealth(FGameplayAttributeData& OldMaxHealth) const;
	UFUNCTION()
	void OnRep_Mana(FGameplayAttributeData& OldMana) const;
	UFUNCTION()
	void OnRep_MaxMana(FGameplayAttributeData& OldMaxMana) const;
	UFUNCTION()
	void OnRep_Strength(FGameplayAttributeData& OldStrength) const;
	UFUNCTION()
	void OnRep_Intelligence(FGameplayAttributeData& OldIntelligence) const;
	UFUNCTION()
	void OnRep_Persistence(FGameplayAttributeData& OldPersistence) const;
	UFUNCTION()
	void OnRep_Vitality(FGameplayAttributeData& OldVitality) const;
	UFUNCTION()
	void OnRep_MPRegen(FGameplayAttributeData& OldMPRegen) const;
	UFUNCTION()
	void OnRep_HPRegen(FGameplayAttributeData& OldHPRegen) const;
	UFUNCTION()
	void OnRep_CritChance(FGameplayAttributeData& OldCritChance) const;
	UFUNCTION()
	void OnRep_Armor(FGameplayAttributeData& OldArmor) const;
	UFUNCTION()
	void OnRep_CritResistance(FGameplayAttributeData& OldCritResistance) const;




private:

	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const;
};
