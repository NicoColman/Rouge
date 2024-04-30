// Rouge

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "RougeAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class ROUGE_API URougeAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	static URougeAssetManager& Get();

protected:
	virtual void StartInitialLoading() override;
};
