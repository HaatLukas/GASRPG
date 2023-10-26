// Copyright Curyło Łukasz


#include "HUD/WidgetController/LC_AttributeMenuWidgetController.h"
#include "AbilitySystem/LC_AttributeSet.h"
#include "AbilitySystem/Data/LC_GameplayTagsDataAsset.h"
#include "LC_GameplayTags.h"
void ULC_AttributeMenuWidgetController::BroadcastInitialValues()
{

}

void ULC_AttributeMenuWidgetController::BindCallbacksToDependecies()
{	
	ULC_AttributeSet* AS = CastChecked<ULC_AttributeSet>(AttributeSet);

	check(AttributeInfoDataAsset);
	FLC_AttributeInfo Info = AttributeInfoDataAsset->FindAttributeInfoForTag(FLC_GameplayTags::Get().Attributes_Main_Intelligence);
	Info.AttributeValue = AS->GetIntelligence();
	AttributeInfoDelegate.Broadcast(Info);

}

