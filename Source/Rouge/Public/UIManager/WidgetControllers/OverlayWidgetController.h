// Rouge

#pragma once

#include "CoreMinimal.h"
#include "RougeWidgetController.h"
#include "OverlayWidgetController.generated.h"

struct FOnAttributeChangeData;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangedSignature, float, NewHealth);

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class ROUGE_API UOverlayWidgetController : public URougeWidgetController
{
	GENERATED_BODY()

public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeChangedSignature OnHealthChanged;
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeChangedSignature OnMaxHealthChanged;
	UPROPERTY(BlueprintAssignable, Category = "GAS|XP")
	FOnAttributeChangedSignature OnXPChanged;

protected:
	void HealthChanged(const FOnAttributeChangeData& Data) const;
	void MaxHealthChanged(const FOnAttributeChangeData& Data) const;

	void XPChanged(const int32 NewXP) const;
};
