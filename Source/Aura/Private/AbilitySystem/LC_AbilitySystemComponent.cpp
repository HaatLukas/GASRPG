// Copyright Curyło Łukasz


#include "AbilitySystem/LC_AbilitySystemComponent.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/Ability/LC_BaseGameplayAbility.h"
#include "LC_GameplayTags.h"

void ULC_AbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &ULC_AbilitySystemComponent::ClientEffectApllied);
}

void ULC_AbilitySystemComponent::AddCharacterAbilities(TArray<TSubclassOf<UGameplayAbility>>& GameplayAbilites)
{
	for (const TSubclassOf<UGameplayAbility> AbilityClass : GameplayAbilites)
	{
		
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass);
		if (const ULC_BaseGameplayAbility* Ability = Cast< ULC_BaseGameplayAbility>(AbilitySpec.Ability))
		{
			AbilitySpec.DynamicAbilityTags.AddTag(Ability->StartupInputTag);
			GiveAbility(AbilitySpec);
		}
	
	}
}

void ULC_AbilitySystemComponent::AbilityInputTagHeld(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;

	for (auto GameplaySpec : GetActivatableAbilities())
	{

		if (GameplaySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpecInputPressed(GameplaySpec);
			if (!GameplaySpec.IsActive())
			{
				TryActivateAbility(GameplaySpec.Handle);
			}
			
		}
	}
}

void ULC_AbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;

	for (auto GameplaySpec : GetActivatableAbilities())
	{
		if (GameplaySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpecInputReleased(GameplaySpec);
		}
	}
}

void ULC_AbilitySystemComponent::ClientEffectApllied_Implementation(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& GameplayEffectSpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle)
{
	FGameplayTagContainer TagContainer;
	GameplayEffectSpec.GetAllAssetTags(TagContainer);
	EffectAssetTagsDelegate.Broadcast(TagContainer);
}
