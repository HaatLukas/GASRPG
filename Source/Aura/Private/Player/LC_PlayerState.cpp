// Copyright Curyło Łukasz


#include "Player/LC_PlayerState.h"
#include "AbilitySystem/LC_AbilitySystemComponent.h"
#include "AbilitySystem/LC_AttributeSet.h"
#include "Net/UnrealNetwork.h"

ALC_PlayerState::ALC_PlayerState()
{
	NetUpdateFrequency = 100.f;

	AbilitySystemComponent = CreateDefaultSubobject<ULC_AbilitySystemComponent>("Ability System Component");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<ULC_AttributeSet>("Attribute Set");
}

void ALC_PlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ALC_PlayerState, PlayerLevel);
}

UAbilitySystemComponent* ALC_PlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ALC_PlayerState::OnRep_PlayerLevel(int32 OldPlayerLevel)
{
}
