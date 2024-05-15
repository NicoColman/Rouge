// Rouge


#include "UIManager/WidgetControllers/RougeWidgetController.h"

void URougeWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& InWidgetControllerParams)
{
	PlayerController = InWidgetControllerParams.PlayerController;
	PlayerState = InWidgetControllerParams.PlayerState;
	AbilitySystemComponent = InWidgetControllerParams.AbilitySystemComponent;
	AttributeSet = InWidgetControllerParams.AttributeSet;
}

void URougeWidgetController::BroadcastInitialValues()
{
}

void URougeWidgetController::BindCallbacksToDependencies()
{
}

void URougeWidgetController::OnInitializeStartupAbilities(UASCBase* ASC)
{
	//if (!ASC->bStartupAbilitiesGiven) return;

	
}
