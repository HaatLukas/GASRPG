// Copyright Curyło Łukasz


#include "AbilitySystem/LC_AbilitySystemComponent.h"
#include "AbilitySystemComponent.h"

void ULC_AbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &ULC_AbilitySystemComponent::EffectApllied);
}

void ULC_AbilitySystemComponent::EffectApllied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& GameplayEffectSpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle)
{
	FGameplayTagContainer TagContainer;
	GameplayEffectSpec.GetAllAssetTags(TagContainer);

	EffectAssetTagsDelegate.Broadcast(TagContainer);
}
