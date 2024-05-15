// Rouge

#pragma once

#include "CoreMinimal.h"
#include "UIManager/WidgetControllers/RougeWidgetController.h"
#include "SpellMenuWidgetController.generated.h"

/**
 * 
 */
UCLASS()
class ROUGE_API USpellMenuWidgetController : public URougeWidgetController
{
	GENERATED_BODY()

public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;
};
