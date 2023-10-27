// Copyright Curyło Łukasz


#include "HUD/WidgetController/LC_AttributeMenuWidgetController.h"
#include "AbilitySystem/LC_AttributeSet.h"
#include "AbilitySystem/Data/LC_GameplayTagsDataAsset.h"
#include "AbilitySystemComponent.h"
#include "LC_GameplayTags.h"
void ULC_AttributeMenuWidgetController::BroadcastInitialValues()
{
	ULC_AttributeSet* AS = CastChecked<ULC_AttributeSet>(AttributeSet);
	check(AttributeInfoDataAsset);

	for (auto& Pair : AS->TagsToAttributes)
	{
		FLC_AttributeInfo Info = AttributeInfoDataAsset->FindAttributeInfoForTag(Pair.Key);
		Info.AttributeValue = Pair.Value().GetNumericValue(AS);
		AttributeInfoDelegate.Broadcast(Info);
	}
}

void ULC_AttributeMenuWidgetController::BindCallbacksToDependecies()
{	
	ULC_AttributeSet* AS = CastChecked<ULC_AttributeSet>(AttributeSet);
	check(AttributeInfoDataAsset);

	for (auto& Pair : AS->TagsToAttributes)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda(
			[this,AS,Pair](const FOnAttributeChangeData& Data)
			{
				FLC_AttributeInfo Info = AttributeInfoDataAsset->FindAttributeInfoForTag(Pair.Key);
				Info.AttributeValue = Pair.Value().GetNumericValue(AS);
				AttributeInfoDelegate.Broadcast(Info);
			}
		);
	}

}

