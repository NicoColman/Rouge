// Rouge


#include "WeaponManager/WeaponDataAssets/WeaponBaseDataAsset.h"

FPrimaryAssetId UWeaponBaseDataAsset::GetPrimaryAssetId() const
{
	if (WeaponTag.IsValid())
	{
		const FString WeaponNameTag = WeaponTag.GetTagName().ToString();
		const FPrimaryAssetId AssetId = FPrimaryAssetId(FPrimaryAssetType("Weapon"), FName(*WeaponNameTag));
		return AssetId;
	}
	return FPrimaryAssetId();
}
