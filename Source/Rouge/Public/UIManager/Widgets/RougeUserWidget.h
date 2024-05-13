// Rouge

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RougeUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class ROUGE_API URougeUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();
};
