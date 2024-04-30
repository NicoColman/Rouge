// Rouge


#include "SpawnManager/WeaponSpawners/WeaponPoolObject.h"
#include "SpawnManager/ObjectPoolingDataAssets/WeaponPoolingDataAsset.h"
#include "SpawnManager/WeaponSpawners/WeaponFactory.h"
#include "WeaponManager/WeaponDataAssets/WeaponBaseDataAsset.h"

UWeaponPoolObject::UWeaponPoolObject()
{
	static ConstructorHelpers::FObjectFinder<UWeaponPoolingDataAsset> DataAssetFinder(TEXT("/Game/Blueprints/SpawnManager/ObjectPoolDataAssets/DA_W_Pool"));
	if (DataAssetFinder.Succeeded())
	{
		WeaponPoolingDataAsset = DataAssetFinder.Object;
	}
}

void UWeaponPoolObject::WeaponPoolManager(UObject* WorldContextObject)
{
	if (!WeaponPoolingDataAsset) return;
	for (const auto& WeaponPair : WeaponPoolingDataAsset->WeaponPool)
	{
		FGameplayTag WeaponTag = WeaponPair.Key;
		EWeaponTypes WeaponType = WeaponPair.Value.WeaponType;
		UWeaponBaseDataAsset* WeaponData = Cast<UWeaponBaseDataAsset>(WeaponPair.Value.WeaponDataAsset);

		AActor* SpawnedWeapon = UWeaponFactory::CreateWeapon(WeaponType,  WorldContextObject->GetWorld(), WeaponData);
		if (SpawnedWeapon)
		{
			WeaponPool.Add(WeaponTag, SpawnedWeapon);
			//SetActive(SpawnedWeapon, false);
		}
	}
}

AActor* UWeaponPoolObject::GetWeaponFromPool(const FGameplayTag& WeaponTag)
{
	for (auto& WeaponPair : WeaponPool)
	{
		if (WeaponPair.Key.MatchesTagExact(WeaponTag) && WeaponPair.Value->GetActorLocation() == FVector::ZeroVector)
		{
			AActor* Weapon = WeaponPair.Value;
			SetActive(Weapon, true);
			return Weapon;
		}
	}
	return nullptr;
}

void UWeaponPoolObject::ReturnWeaponToPool(AActor* Weapon)
{
	SetActive(Weapon, false);
}

void UWeaponPoolObject::SetActive(AActor* Weapon, bool bActive)
{
	if (!Weapon) return;
	//Weapon->SetActorHiddenInGame(!bActive);
	Weapon->SetActorEnableCollision(bActive);
	Weapon->SetActorTickEnabled(bActive);
	if (!bActive)
	{
		Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		Weapon->SetActorLocation(FVector::ZeroVector);
	}
}
