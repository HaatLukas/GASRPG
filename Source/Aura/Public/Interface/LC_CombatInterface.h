// Copyright Curyło Łukasz

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "LC_CombatInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI,BlueprintType)
class ULC_CombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class AURA_API ILC_CombatInterface
{
	GENERATED_BODY()
public:
	virtual int32 GetPlayerLevel();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void UpdateMotionWarping(const FVector& EnemyLocation);
	//UFUNCTION(BlueprintCallable)
	virtual FVector GetWeaponTipLocation();

};
