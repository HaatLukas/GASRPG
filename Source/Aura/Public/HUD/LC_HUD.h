// Copyright Curyło Łukasz

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "LC_HUD.generated.h"

class ULC_UserWidget;
struct FWidgetControllerParameters;
class ULC_OverlayWidgetController;
class ULC_AttributeMenuWidgetController;


/**
 * 
 */
UCLASS()
class AURA_API ALC_HUD : public AHUD
{
	GENERATED_BODY()

public:
	ULC_OverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParameters& WCParams);
	ULC_AttributeMenuWidgetController* GetAttributeMenuWidgetController(const FWidgetControllerParameters& WCParams);

	UFUNCTION()
	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

private:
	UPROPERTY()
	TObjectPtr<ULC_UserWidget> OverlayWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ULC_UserWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<ULC_OverlayWidgetController> OverlayWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ULC_OverlayWidgetController> OverlayControllerClass;

	UPROPERTY()
	TObjectPtr<ULC_AttributeMenuWidgetController> AttributeMenuWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ULC_AttributeMenuWidgetController> AttributeMenuWidgetControllerClass;
	
};
