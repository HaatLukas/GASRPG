// Copyright Curyło Łukasz

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Ability/LC_BaseGameplayAbility.h"
#include "LC_FireSpellProjectile.generated.h"

class ALC_BaseProjectile;
/**
 * 
 */
UCLASS()
class AURA_API ULC_FireSpellProjectile : public ULC_BaseGameplayAbility
{
	GENERATED_BODY()

public:

protected:

	UFUNCTION(BlueprintCallable)
	void SpawnProjectile();
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	UPROPERTY(EditAnywhere)
	TSubclassOf<ALC_BaseProjectile> ProjectileClass;
	
private:
	
};
