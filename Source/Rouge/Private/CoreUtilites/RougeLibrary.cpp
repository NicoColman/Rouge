// Rouge


#include "CoreUtilites/RougeLibrary.h"

#include "CoreUtilites/RougeAbilityTypes.h"
#include "GlobalManagers/RougeAssetManager.h"
#include "Interfaces/CharacterInterfaces/CharacterBaseInterface.h"

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

UCharacterBaseDataAsset* URougeLibrary::GetCharacterBaseDataAsset(AActor* Actor)
{
	if (const ICharacterBaseInterface* CharacterInterface = Cast<ICharacterBaseInterface>(Actor))
	{
		return CharacterInterface->GetCharacterDataAsset();
	}
	return nullptr;
}

bool URougeLibrary::IsBlockedHit(const FGameplayEffectContextHandle& EffectContext)
{
	if (const FRougeGameplayEffectContext* RougeEffectContext = static_cast<const FRougeGameplayEffectContext*>(EffectContext.Get()))
	{
		return RougeEffectContext->IsBlockedHit();
	}
	return false;
}

bool URougeLibrary::IsCriticalHit(const FGameplayEffectContextHandle& EffectContext)
{
	if (const FRougeGameplayEffectContext* RougeEffectContext = static_cast<const FRougeGameplayEffectContext*>(EffectContext.Get()))
	{
		return RougeEffectContext->IsCriticalHit();
	}
	return false;
}

void URougeLibrary::SetBlockedHit(FGameplayEffectContextHandle& EffectContext, bool bBlockedHit)
{
	if (FRougeGameplayEffectContext* RougeEffectContext = static_cast<FRougeGameplayEffectContext*>(EffectContext.Get()))
	{
		RougeEffectContext->SetIsBlockedHit(bBlockedHit);
	}
}

void URougeLibrary::SetCriticalHit(FGameplayEffectContextHandle& EffectContext, bool bCriticalHit)
{
	if (FRougeGameplayEffectContext* RougeEffectContext = static_cast<FRougeGameplayEffectContext*>(EffectContext.Get()))
	{
		RougeEffectContext->SetIsCriticalHit(bCriticalHit);
	}
}
