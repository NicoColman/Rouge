// Rouge


#include "GameMode/RougeGameModeBase.h"

#include "Kismet/GameplayStatics.h"
#include "SpawnManager/WeaponSpawners/WeaponPoolObject.h"
#include "GameFramework/PlayerStart.h"

ARougeGameModeBase::ARougeGameModeBase()
{
	WeaponPoolObject = nullptr;
}

void ARougeGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
	WeaponPoolObject = NewObject<UWeaponPoolObject>(this, UWeaponPoolObject::StaticClass());
	WeaponPoolObject->WeaponPoolManager(this);
}

AActor* ARougeGameModeBase::GetWeaponFromPool(const FGameplayTag& WeaponTag)
{
	if (WeaponPoolObject)
	{
		return WeaponPoolObject->GetWeaponFromPool(WeaponTag);
	}
	return nullptr;
}

void ARougeGameModeBase::ReturnWeaponToPool(AActor* Weapon)
{
	if (WeaponPoolObject)
	{
		WeaponPoolObject->ReturnWeaponToPool(Weapon);
	}
}

void ARougeGameModeBase::RequestRespawn(APlayerController* PlayerController)
{
	TArray<AActor*> AllPlayerStarts;
	UGameplayStatics::GetAllActorsOfClass(this, APlayerStart::StaticClass(), AllPlayerStarts);

	for (AActor* PlayerStart : AllPlayerStarts)
	{
		RestartPlayerAtPlayerStart(PlayerController, PlayerStart);
		break;
	}
	
}
