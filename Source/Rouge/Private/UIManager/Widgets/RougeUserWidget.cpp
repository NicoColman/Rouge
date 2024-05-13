// Rouge


#include "UIManager/Widgets/RougeUserWidget.h"

void URougeUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
