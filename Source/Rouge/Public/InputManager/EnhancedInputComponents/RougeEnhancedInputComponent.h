// Rouge

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "InputManager/InputConfigDataAsset.h"
#include "RougeEnhancedInputComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ROUGE_API URougeEnhancedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	URougeEnhancedInputComponent();

	template<class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
	void BindAbilityActions(const UInputConfigDataAsset* InputConfigDataAsset, UserClass* Object,
		PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc);
protected:
	virtual void BeginPlay() override;
	

};

template <class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
void URougeEnhancedInputComponent::BindAbilityActions(const UInputConfigDataAsset* InputConfigDataAsset,
	UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc)
{
	check(InputConfigDataAsset);

	for (const FInputActionBase& Action : InputConfigDataAsset->InputActions)
	{
		if (Action.InputTag.IsValid())
		{
			if (PressedFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Started, Object, PressedFunc, Action.InputTag);
			}
			if (ReleasedFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Completed, Object, ReleasedFunc, Action.InputTag);
			}
			if (HeldFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Triggered, Object, HeldFunc, Action.InputTag);
			}
		}
	}
}
