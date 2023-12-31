// Copyright Curyło Łukasz


#include "HUD/WidgetController/LC_WidgetController.h"

void ULC_WidgetController::SetWidgetControllerParams(const FWidgetControllerParameters& Params)
{
	PlayerController = Params.PlayerController;
	AbilitySystemComponent = Params.AbilitySystemComponent;
	AttributeSet = Params.AttributeSet;
	PlayerState = Params.PlayerState;
}

void ULC_WidgetController::BroadcastInitialValues()
{

}

void ULC_WidgetController::BindCallbacksToDependecies()
{

}
