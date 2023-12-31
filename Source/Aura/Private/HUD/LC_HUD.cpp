// Copyright Curyło Łukasz


#include "HUD/LC_HUD.h"
#include "HUD/WidgetController/LC_OverlayWidgetController.h"	
#include "HUD/Widget/LC_UserWidget.h"

ULC_OverlayWidgetController* ALC_HUD::GetOverlayWidgetController(const FWidgetControllerParameters& WCParams)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<ULC_OverlayWidgetController>(this, OverlayControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
		OverlayWidgetController->BindCallbacksToDependecies();

		return OverlayWidgetController;
	}
	else
		return OverlayWidgetController;
}

void ALC_HUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class unitilizaed, please fill out BP_GASHUD"));
	checkf(OverlayControllerClass, TEXT("Overlay Controller Class unitilizaed, please fill out BP_GASHUD"));


	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<ULC_UserWidget>(Widget);

	const FWidgetControllerParameters WidgetControllerParams(PC, PS, ASC, AS);
	ULC_OverlayWidgetController* OverlayWidgetCont = GetOverlayWidgetController(WidgetControllerParams);
	

	OverlayWidget->SetWidgetController(OverlayWidgetCont);
	OverlayWidgetCont->BroadcastInitialValues();

	Widget->AddToViewport();
}

