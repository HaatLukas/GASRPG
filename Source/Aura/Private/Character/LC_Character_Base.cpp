// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/LC_Character_Base.h"
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


