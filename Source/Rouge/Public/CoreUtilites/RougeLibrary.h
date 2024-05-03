// Rouge

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RougeLibrary.generated.h"

UENUM(BlueprintType)
enum class EFlipbookRotation : uint8
{
	EFR_None UMETA(DisplayName = "None"),
	EFR_North UMETA(DisplayName = "North"),
	EFR_South UMETA(DisplayName = "South"),
	EFR_East UMETA(DisplayName = "East"),
	EFR_West UMETA(DisplayName = "West"),
};

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

	static FRotator GetFlipbookRotation(EFlipbookRotation FlipbookRotation);


private:
	static FPrimaryAssetId GetPrimaryAssetIdFromTag(const FGameplayTag& Tag, const ANSICHAR* InName);
};
