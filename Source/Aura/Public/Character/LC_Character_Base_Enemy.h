// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/LC_Character_Base.h"
#include "Interface/HoverInterface.h"
#include "LC_Character_Base_Enemy.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API ALC_Character_Base_Enemy : public ALC_Character_Base, public IHoverInterface
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly)
	bool bHighlighted = false;
	virtual void BeginPlay() override;

	ALC_Character_Base_Enemy();
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;

protected:
	virtual void InitAbiltyActorInfo() override;
	

	

};
