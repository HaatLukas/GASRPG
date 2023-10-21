// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/LC_Character_Base.h"
#include "AbilitySystemComponent.h"
#include "LC_Character_Player.generated.h"

class UGameplayEffect;
/**
 * 
 */
UCLASS()
class AURA_API ALC_Character_Player : public ALC_Character_Base
{
	GENERATED_BODY()

public:
	ALC_Character_Player();

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	virtual void InitAbiltyActorInfo() override;

protected:



};
