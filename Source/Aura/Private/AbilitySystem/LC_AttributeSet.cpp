// Copyright Curyło Łukasz


#include "AbilitySystem/LC_AttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameFramework/Character.h"
#include "GameplayEffectExtension.h"
#include "LC_GameplayTags.h"

ULC_AttributeSet::ULC_AttributeSet()
{
	const FLC_GameplayTags GameplayTags = FLC_GameplayTags::Get();

	/* Main Attributes */

	TagsToAttributes.Add(GameplayTags.Attributes_Main_Strength, GetStrengthAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Main_Intelligence, GetIntelligenceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Main_Persistence, GetPersistenceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Main_Vitality, GetVitalityAttribute);

	/* end Main Attributes */


	/* Secondary Attributes */

	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_Armor, GetArmorAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_CriticalHitChance, GetCritChanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_CriticalHitResistance, GetCritResistanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_HealthRegeneration, GetHPRegenAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_ManaRegeneration, GetMPRegenAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_MaxHealth, GetMaxHealthAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_MaxMana, GetMaxManaAttribute);

	/* end Secondary Attributes */
}

void ULC_AttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());

	}
	if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
	}
}

void ULC_AttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	// HP/MP
	DOREPLIFETIME_CONDITION_NOTIFY(ULC_AttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULC_AttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULC_AttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULC_AttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);

	//Main
	DOREPLIFETIME_CONDITION_NOTIFY(ULC_AttributeSet, Strength, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULC_AttributeSet, Intelligence, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULC_AttributeSet, Persistence, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULC_AttributeSet, Vitality, COND_None, REPNOTIFY_Always);

	//Secondary
	DOREPLIFETIME_CONDITION_NOTIFY(ULC_AttributeSet, HPRegen, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULC_AttributeSet, MPRegen, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULC_AttributeSet, CritChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULC_AttributeSet, Armor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULC_AttributeSet, CritResistance, COND_None, REPNOTIFY_Always);
}

void ULC_AttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FEffectProperties Props;
	SetEffectProperties(Data, Props);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
		UE_LOG(LogTemp, Warning, TEXT("Changed Health on %s, Health: %f"), *GetActorInfo()->AvatarActor->GetName(), GetHealth());

	}

	if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(), 0.f, GetMaxMana()));
	}
}

void ULC_AttributeSet::OnRep_Health(FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULC_AttributeSet, Health, OldHealth);
}

void ULC_AttributeSet::OnRep_MaxHealth(FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULC_AttributeSet, MaxHealth, OldMaxHealth);
}

void ULC_AttributeSet::OnRep_Mana(FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULC_AttributeSet, Mana, OldMana);
}

void ULC_AttributeSet::OnRep_MaxMana(FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULC_AttributeSet, MaxMana, OldMaxMana);
}

void ULC_AttributeSet::OnRep_Strength(FGameplayAttributeData& OldStrength) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULC_AttributeSet, Strength, OldStrength);
}

void ULC_AttributeSet::OnRep_Intelligence(FGameplayAttributeData& OldIntelligence) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULC_AttributeSet, Intelligence, OldIntelligence);
}

void ULC_AttributeSet::OnRep_Persistence(FGameplayAttributeData& OldPersistence) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULC_AttributeSet, Persistence, OldPersistence);
}

void ULC_AttributeSet::OnRep_MPRegen(FGameplayAttributeData& OldMPRegen) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULC_AttributeSet, MPRegen, OldMPRegen);
}

void ULC_AttributeSet::OnRep_HPRegen(FGameplayAttributeData& OldHPRegen) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULC_AttributeSet, HPRegen, OldHPRegen);
}

void ULC_AttributeSet::OnRep_CritChance(FGameplayAttributeData& OldCritChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULC_AttributeSet, CritChance, OldCritChance);
}

void ULC_AttributeSet::OnRep_Armor(FGameplayAttributeData& OldArmor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULC_AttributeSet, Armor, OldArmor);
}

void ULC_AttributeSet::OnRep_CritResistance(FGameplayAttributeData& OldCritResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULC_AttributeSet, CritResistance, OldCritResistance);
}

void ULC_AttributeSet::OnRep_Vitality(FGameplayAttributeData& OldVitality) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULC_AttributeSet, Vitality, OldVitality);
}

void ULC_AttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const
{
	Props.EffectContextHandle = Data.EffectSpec.GetContext();
	Props.SourceASC = Props.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();

	if (IsValid(Props.SourceASC) && Props.SourceASC->AbilityActorInfo.IsValid() && Props.SourceASC->AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.SourceAvatarActor = Props.SourceASC->AbilityActorInfo->AvatarActor.Get();
		Props.SourceController = Props.SourceASC->AbilityActorInfo->PlayerController.Get();
		if (Props.SourceController == nullptr && Props.SourceAvatarActor != nullptr)
		{
			if (const APawn* Pawn = Cast<APawn>(Props.SourceAvatarActor))
			{
				Props.SourceController = Pawn->GetController();
			}
		}
		if (Props.SourceController)
		{
			ACharacter* SourceCharacter = Cast<ACharacter>(Props.SourceController->GetPawn());
		}
	}

	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		Props.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		Props.TargetCharacter = Cast<ACharacter>(Props.TargetAvatarActor);
		Props.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Props.TargetAvatarActor);
	}
}
