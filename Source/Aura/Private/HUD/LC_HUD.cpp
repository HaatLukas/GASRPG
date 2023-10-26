// Copyright Curyło Łukasz


#include "HUD/LC_HUD.h"
#include "HUD/WidgetController/LC_OverlayWidgetController.h"	
#include "HUD/WidgetController/LC_AttributeMenuWidgetController.h"
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

ULC_AttributeMenuWidgetController* ALC_HUD::GetAttributeMenuWidgetController(const FWidgetControllerParameters& WCParams)
{
	if (AttributeMenuWidgetController == nullptr)
	{
		AttributeMenuWidgetController = NewObject<ULC_AttributeMenuWidgetController>(this, AttributeMenuWidgetControllerClass);
		AttributeMenuWidgetController->SetWidgetControllerParams(WCParams);
		AttributeMenuWidgetController->BindCallbacksToDependecies();

	}
	UE_LOG(LogTemp, Warning, TEXT("Hello"));
	return AttributeMenuWidgetController;

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

	//AttributeMenuWidgetController->BroadcastInitialValues();

	Widget->AddToViewport();
}

