// Rouge

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RougeLibrary.generated.h"

/**
 * 
 */
UCLASS()
class ROUGE_API URougeLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	URougeLibrary();

	static UObject* GetPrimaryObjectFromTag(const FGameplayTag& Tag, const ANSICHAR* InName);

private:
	static FPrimaryAssetId GetPrimaryAssetIdFromTag(const FGameplayTag& Tag, const ANSICHAR* InName);
};
