// Copyright Curyło Łukasz


#include "Player/LC_PlayerState.h"
#include "AbilitySystem/LC_AbilitySystemComponent.h"
#include "AbilitySystem/LC_AttributeSet.h"

ALC_PlayerState::ALC_PlayerState()
{
	NetUpdateFrequency = 100.f;

	AbilitySystemComponent = CreateDefaultSubobject<ULC_AbilitySystemComponent>("Ability System Component");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<ULC_AttributeSet>("Attribute Set");
}

UAbilitySystemComponent* ALC_PlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
