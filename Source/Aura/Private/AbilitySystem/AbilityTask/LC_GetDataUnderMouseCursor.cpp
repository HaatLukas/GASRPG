// Copyright Curyło Łukasz


#include "AbilitySystem/AbilityTask/LC_GetDataUnderMouseCursor.h"

#include "AbilitySystemComponent.h"
#include "Player/LC_PlayerController.h"

ULC_GetDataUnderMouseCursor* ULC_GetDataUnderMouseCursor::GetDataUnderMouseCursor(UGameplayAbility* OwningAbility)
{
	ULC_GetDataUnderMouseCursor* MyObj = NewAbilityTask<ULC_GetDataUnderMouseCursor>(OwningAbility);
	return MyObj;
}

void ULC_GetDataUnderMouseCursor::Activate()
{
	const bool bIsLocallyControlled = AbilitySystemComponent->AbilityActorInfo->IsLocallyControlled();

	if(bIsLocallyControlled)
	{
		SendDataToServer();
	}
	else
	{
		AbilitySystemComponent.Get()->AbilityTargetDataSetDelegate(GetAbilitySpecHandle(),GetActivationPredictionKey()).AddUObject(this,&ULC_GetDataUnderMouseCursor::MouseCursorDataDelegate);
		const bool bSetReplicatedData = AbilitySystemComponent.Get()->CallReplicatedTargetDataDelegatesIfSet(GetAbilitySpecHandle(),GetActivationPredictionKey());

		if(!bSetReplicatedData)
		{
			SetWaitingOnRemotePlayerData();
		}
	}
	

}

void ULC_GetDataUnderMouseCursor::SendDataToServer()
{
	ALC_PlayerController* PC = Cast<ALC_PlayerController>(Ability->GetCurrentActorInfo()->PlayerController.Get());
	FHitResult HitResult;
	PC->GetHitResultUnderCursor(ECC_Visibility,false,HitResult);

	//To get Target Data, use proper FGameplayAbilityTargetData
	
	FGameplayAbilityTargetData_SingleTargetHit* Data = new FGameplayAbilityTargetData_SingleTargetHit();
	Data->HitResult=HitResult;
	FGameplayAbilityTargetDataHandle DataHandle;
	DataHandle.Add(Data);

	// Then to send it to server use ServerSetReplicatedTargetData

	AbilitySystemComponent->ServerSetReplicatedTargetData(GetAbilitySpecHandle(),
		GetActivationPredictionKey(),
		DataHandle,
		FGameplayTag(),
		AbilitySystemComponent->ScopedPredictionKey);

	// After that, check if we should Broadcast Delegates in case of we don't need it anymore

	if(ShouldBroadcastAbilityTaskDelegates())
	{
		MouseData.Broadcast(DataHandle);
	}
}

void ULC_GetDataUnderMouseCursor::MouseCursorDataDelegate(const FGameplayAbilityTargetDataHandle& DataHandle,
	FGameplayTag StartTag)
{
	//Tell the client to clean the cached data about an AbilityTask
	AbilitySystemComponent->ConsumeAllReplicatedData(GetAbilitySpecHandle(),GetActivationPredictionKey());

	//BroadcastInfo
	if(ShouldBroadcastAbilityTaskDelegates())
	{
		MouseData.Broadcast(DataHandle);
	}
}
