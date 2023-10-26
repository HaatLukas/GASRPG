// Copyright Curyło Łukasz


#include "AbilitySystem/LC_AbilitySystemBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Player/LC_PlayerState.h"
#include "HUD/WidgetController/LC_WidgetController.h"
#include "HUD/LC_HUD.h"

ULC_OverlayWidgetController* ULC_AbilitySystemBlueprintLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (ALC_HUD* GameHUD = Cast<ALC_HUD>(PC->GetHUD()))
		{
			ALC_PlayerState* PS = PC->GetPlayerState<ALC_PlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			const FWidgetControllerParameters WidgetControllerParams(PC, PS, ASC, AS);
			return GameHUD->GetOverlayWidgetController(WidgetControllerParams);
		}
	}

	return nullptr;
}

ULC_AttributeMenuWidgetController* ULC_AbilitySystemBlueprintLibrary::GetAttributeMenuWidgetController(const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (ALC_HUD* GAME_HUD = Cast<ALC_HUD>(PC->GetHUD()))
		{
			ALC_PlayerState* PS = PC->GetPlayerState<ALC_PlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			const FWidgetControllerParameters WidgetControllerParams(PC, PS, ASC, AS);
			return GAME_HUD->GetAttributeMenuWidgetController(WidgetControllerParams);
		}
	}
	return nullptr;
}
