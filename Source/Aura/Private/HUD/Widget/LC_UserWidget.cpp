

#include "HUD/Widget/LC_UserWidget.h"

void ULC_UserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
