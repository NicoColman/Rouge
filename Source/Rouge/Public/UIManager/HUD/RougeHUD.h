// Rouge

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RougeHUD.generated.h"

struct FWidgetControllerParams;
/**
 * 
 */
UCLASS()
class ROUGE_API ARougeHUD : public AHUD
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TObjectPtr<class URougeUserWidget> OverlayWidget;

	class UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& InWidgetControllerParams);

	void InitOverlay(APlayerController* InPlayerController, APlayerState* InPlayerState, class UAbilitySystemComponent* InAbilitySystemComponent, class UAttributeSet* InAttributeSet);

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<URougeUserWidget> OverlayWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;
	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;
};
