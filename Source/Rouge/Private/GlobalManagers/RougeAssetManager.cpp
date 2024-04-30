// Rouge


#include "GlobalManagers/RougeAssetManager.h"
#include "AbilitySystemGlobals.h"
#include "GlobalManagers/RougeGameplayTags.h"

URougeAssetManager& URougeAssetManager::Get()
{
	URougeAssetManager* AssetManager = Cast<URougeAssetManager>(GEngine->AssetManager);
	return *AssetManager;
}

void URougeAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	FRougeGameplayTags::InitializeNativeGameplayTags();
	UAbilitySystemGlobals::Get().InitGlobalData();
}
