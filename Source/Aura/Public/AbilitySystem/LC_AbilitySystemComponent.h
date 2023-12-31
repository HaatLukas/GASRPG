// Copyright Curyło Łukasz

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "LC_AbilitySystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags, const FGameplayTagContainer&);

/**
 * 
 */
UCLASS()
class AURA_API ULC_AbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	void AbilityActorInfoSet();
	FEffectAssetTags EffectAssetTagsDelegate;

protected:
	void EffectApllied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& GameplayEffectSpec,
		FActiveGameplayEffectHandle ActiveGameplayEffectHandle);

};
