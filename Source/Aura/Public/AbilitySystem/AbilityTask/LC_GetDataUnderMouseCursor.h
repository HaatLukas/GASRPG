// Copyright Curyło Łukasz

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "LC_GetDataUnderMouseCursor.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDataUnderMouseCursorSignature,const FGameplayAbilityTargetDataHandle&,DataHandle);


UCLASS()

class AURA_API ULC_GetDataUnderMouseCursor : public UAbilityTask
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable,Category="Ability|Tasks", meta=(HidePin = "OwningAbility", DefaultToSelf="OwningAbility",BlueprintInternalUseOnly="true"),DisplayName="GetDataUnderMouseCursor")
	static ULC_GetDataUnderMouseCursor* GetDataUnderMouseCursor(UGameplayAbility* OwningAbility);

	UPROPERTY(BlueprintAssignable)
	FDataUnderMouseCursorSignature MouseData;

private:
	virtual void Activate() override;
	void SendDataToServer();
	void MouseCursorDataDelegate(const FGameplayAbilityTargetDataHandle& DataHandle, FGameplayTag StartTag);
	
};
