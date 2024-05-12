// Rouge


#include "UIManager/WidgetControllers/OverlayWidgetController.h"

#include "GASManager/AttributeSet/AttributeSetBase.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UAttributeSetBase* AttributeSetBase = CastChecked<UAttributeSetBase>(AttributeSet);
	
	OnHealthChanged.Broadcast(AttributeSetBase->GetHealth());
	OnMaxHealthChanged.Broadcast(AttributeSetBase->GetMaxHealth());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UAttributeSetBase* AttributeSetBase = CastChecked<UAttributeSetBase>(AttributeSet);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AttributeSetBase->GetHealthAttribute()).AddUObject(this, &UOverlayWidgetController::HealthChanged);
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AttributeSetBase->GetMaxHealthAttribute()).AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);
}

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);

}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}
