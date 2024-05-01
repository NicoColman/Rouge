// Rouge


#include "CoreUtilites/RougeLibrary.h"
#include "GlobalManagers/RougeAssetManager.h"

URougeLibrary::URougeLibrary()
{
}

UObject* URougeLibrary::GetPrimaryObjectFromTag(const FGameplayTag& Tag, const ANSICHAR* InName)
{
	FPrimaryAssetId PrimaryAssetId = GetPrimaryAssetIdFromTag(Tag, InName);
	if (PrimaryAssetId.IsValid())
	{
		URougeAssetManager& AssetManager = URougeAssetManager::Get();
		UObject* LoadedAsset = AssetManager.GetPrimaryAssetObject(PrimaryAssetId);
		if (!LoadedAsset)
		{
			TSharedPtr<FStreamableHandle> Handle = AssetManager.LoadPrimaryAsset(PrimaryAssetId);
			if (Handle.IsValid() && Handle->HasLoadCompleted())
			{
				LoadedAsset = Handle->GetLoadedAsset();
			}
		}
		if (LoadedAsset)
		{
			return LoadedAsset;
		}
	}
	return nullptr;
}

FPrimaryAssetId URougeLibrary::GetPrimaryAssetIdFromTag(const FGameplayTag& Tag, const ANSICHAR* InName)
{
	const FString AssetName = Tag.GetTagName().ToString();
	return FPrimaryAssetId(FPrimaryAssetType(InName), FName(*AssetName));
}
