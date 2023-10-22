// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/LC_Character_Base.h"
#include "AbilitySystemComponent.h"
#include "Components/SkeletalMeshComponent.h"

ALC_Character_Base::ALC_Character_Base()
{
	PrimaryActorTick.bCanEverTick = true;
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), "WeaponSocket");
}

UAbilitySystemComponent* ALC_Character_Base::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}


void ALC_Character_Base::BeginPlay()
{
	Super::BeginPlay();
}

void ALC_Character_Base::InitAbiltyActorInfo()
{

}

void ALC_Character_Base::InitVitalAttributes() const
{
		check(GetAbilitySystemComponent());
		check(IsValid(VitalAttributesClass));
		const FGameplayEffectContextHandle GameplayContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
		const FGameplayEffectSpecHandle EffectSpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(VitalAttributesClass, 1.f, GameplayContextHandle);
		GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*EffectSpecHandle.Data.Get(), GetAbilitySystemComponent());
}

void ALC_Character_Base::InitSecondaryAttributes() const
{
	check(GetAbilitySystemComponent());
	check(IsValid(SecondaryAttributesClass));
	const FGameplayEffectContextHandle GameplayContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	const FGameplayEffectSpecHandle EffectSpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(SecondaryAttributesClass, 1.f, GameplayContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*EffectSpecHandle.Data.Get(), GetAbilitySystemComponent());
}


