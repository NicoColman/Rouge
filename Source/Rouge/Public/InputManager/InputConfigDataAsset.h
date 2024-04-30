// Rouge

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "InputConfigDataAsset.generated.h"


USTRUCT(BlueprintType)
struct FInputActionBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	const class UInputAction* InputAction = nullptr;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag = FGameplayTag();
	
};

/**
 * 
 */
UCLASS()
class ROUGE_API UInputConfigDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	const UInputAction* GetInputAction(const struct FGameplayTag& InputTag, bool bLogNotFound = false) const;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FInputActionBase> InputActions;
};
