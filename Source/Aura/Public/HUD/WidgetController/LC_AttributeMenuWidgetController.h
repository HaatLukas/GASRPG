// Copyright Curyło Łukasz

#pragma once

#include "CoreMinimal.h"
#include "HUD/WidgetController/LC_WidgetController.h"
#include "AbilitySystem/Data/LC_GameplayTagsDataAsset.h"
#include "LC_AttributeMenuWidgetController.generated.h"

struct FLC_AttributeInfo;
class ULC_AttributeInfo;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeInfSignature, const FLC_AttributeInfo&, Info);
/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class AURA_API ULC_AttributeMenuWidgetController : public ULC_WidgetController
{
	GENERATED_BODY()
public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependecies() override;
	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FAttributeInfSignature AttributeInfoDelegate;
protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<ULC_GameplayTagsDataAsset> AttributeInfoDataAsset;
};
