// Rouge


#include "SpawnManager/WeaponSpawners/WeaponFactory.h"
#include "WeaponManager/WeaponTypes/WeaponBase.h"

AActor* UWeaponFactory::CreateWeapon(EWeaponTypes WeaponType, UObject* WorldContextObject,
	UPrimaryDataAsset* WeaponDataAsset)
{
	switch (WeaponType)
	{//case EWeaponTypes::EWT_Proxy:
			//return CreateWeaponProxy(WorldContextObject, WeaponDataAsset);
	case EWeaponTypes::EWT_Base:
		return CreateWeaponBase(WorldContextObject, WeaponDataAsset);
	default:
		return nullptr;
	}
}

AWeaponBase* UWeaponFactory::CreateWeaponBase(UObject* WorldContextObject,
	UPrimaryDataAsset* WeaponDataAsset)
{
	if (AWeaponBase* Weapon = WorldContextObject->GetWorld()->SpawnActor<AWeaponBase>(AWeaponBase::StaticClass(), FVector::ZeroVector,
		FRotator::ZeroRotator))
	{
		Weapon->SetDataAsset(WeaponDataAsset);
		return Weapon;	
	}
	return nullptr;
}
