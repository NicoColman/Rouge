// Rouge


#include "UIManager/HUD/RougeHUD.h"

#include "Blueprint/UserWidget.h"
#include "UIManager/Widgets/RougeUserWidget.h"
#include "UIManager/WidgetControllers/OverlayWidgetController.h"


UOverlayWidgetController* ARougeHUD::GetOverlayWidgetController(const FWidgetControllerParams& InWidgetControllerParams)
{
	if (OverlayWidgetController) return OverlayWidgetController;
	OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
	OverlayWidgetController->SetWidgetControllerParams(InWidgetControllerParams);
	return OverlayWidgetController;
}

void ARougeHUD::InitOverlay(APlayerController* InPlayerController, APlayerState* InPlayerState,
	UAbilitySystemComponent* InAbilitySystemComponent, UAttributeSet* InAttributeSet)
{
	checkf(OverlayWidgetClass, TEXT("OverlayWidgetClass is not set!"));
	checkf(OverlayWidgetControllerClass, TEXT("OverlayWidgetControllerClass is not set!"));
	
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<URougeUserWidget>(Widget);

	const FWidgetControllerParams  WidgetControllerParams(InPlayerController, InPlayerState, InAbilitySystemComponent, InAttributeSet);
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);

	OverlayWidget->SetWidgetController(WidgetController);
	Widget->AddToViewport();
}
