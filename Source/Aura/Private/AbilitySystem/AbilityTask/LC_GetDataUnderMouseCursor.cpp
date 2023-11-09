// Copyright Curyło Łukasz


#include "AbilitySystem/AbilityTask/LC_GetDataUnderMouseCursor.h"

#include "GameFramework/GameSession.h"
#include "Player/LC_PlayerController.h"

ULC_GetDataUnderMouseCursor* ULC_GetDataUnderMouseCursor::GetDataUnderMouseCursor(UGameplayAbility* OwningAbility)
{
	ULC_GetDataUnderMouseCursor* MyObj = NewAbilityTask<ULC_GetDataUnderMouseCursor>(OwningAbility);
	return MyObj;
}

void ULC_GetDataUnderMouseCursor::Activate()
{
	ALC_PlayerController* PC = Cast<ALC_PlayerController>(Ability->GetCurrentActorInfo()->PlayerController.Get());
	FHitResult HitResult;
	PC->GetHitResultUnderCursor(ECC_Visibility,false,HitResult);
	MouseData.Broadcast(HitResult.Location);
}
