// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/LC_Character_Base_Enemy.h"
#include "AbilitySystem/LC_AbilitySystemComponent.h"
#include "AbilitySystem/LC_AttributeSet.h"

void ALC_Character_Base_Enemy::BeginPlay()
{
	Super::BeginPlay();

	InitAbiltyActorInfo();
}

ALC_Character_Base_Enemy::ALC_Character_Base_Enemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECR_Block);

	AbilitySystemComponent = CreateDefaultSubobject<ULC_AbilitySystemComponent>("Ability System Component");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<ULC_AttributeSet>("Attribute Set");
}

void ALC_Character_Base_Enemy::HighlightActor()
{
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(250.f);
	Weapon->SetRenderCustomDepth(true);
	Weapon->SetCustomDepthStencilValue(true);
}

void ALC_Character_Base_Enemy::UnHighlightActor()
{
	bHighlighted = false;
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
}

void ALC_Character_Base_Enemy::InitAbiltyActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<ULC_AbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
	InitVitalAttributes();
	InitSecondaryAttributes();
	InitAttributes();
}

int32 ALC_Character_Base_Enemy::GetPlayerLevel()
{
	return PlayerLevel;
}
