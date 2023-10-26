// Copyright Curyło Łukasz

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LC_AbilitySystemBlueprintLibrary.generated.h"

class ULC_OverlayWidgetController;
class ULC_AttributeMenuWidgetController;
/**
 * 
 */
UCLASS()
class AURA_API ULC_AbilitySystemBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	ULC_OverlayWidgetController* OverlayWidgetController;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "LC_AbilitySystemBlueprintLibrary")
	static ULC_OverlayWidgetController* GetOverlayWidgetController(const UObject* WorldContextObject);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "LC_AbilitySystemBlueprintLibrary")
	static ULC_AttributeMenuWidgetController* GetAttributeMenuWidgetController(const UObject* WorldContextObject);
	
};
