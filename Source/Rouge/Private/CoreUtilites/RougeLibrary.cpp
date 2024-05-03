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

FRotator URougeLibrary::GetFlipbookRotation(EFlipbookRotation FlipbookRotation)
{
	switch (FlipbookRotation)
	{
	case EFlipbookRotation::EFR_North:
		return FRotator(0, 0, 0);
	case EFlipbookRotation::EFR_South:
		return FRotator(0, 180, 0);
	case EFlipbookRotation::EFR_East:
		return FRotator(0, 90, 0);
	case EFlipbookRotation::EFR_West:
		return FRotator(0, -90, 0);
	default:
		return FRotator::ZeroRotator;
	}
}
