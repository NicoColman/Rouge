// Rouge

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Interfaces/GameModeInterfaces/RougeGameModeInterface.h"
#include "RougeGameModeBase.generated.h"

class UGameplayEffect;
class AEffectActorBase;
class ACharacterEnemy;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnNewRoundDelegate, int32 /* StatValue */);

/**
 * 
 */
UCLASS()
class ROUGE_API ARougeGameModeBase : public AGameModeBase, public IRougeGameModeInterface
{
	GENERATED_BODY()

public:
	ARougeGameModeBase();

	/** Begin IRougeGameModeInterface */
	virtual AActor* GetWeaponFromPool(const FGameplayTag& WeaponTag) override;
	virtual void ReturnWeaponToPool(AActor* Weapon) override;
	virtual void RequestRespawn(APlayerController* PlayerController) override;
	virtual void EnemyKilled() override;
	virtual void SetCrazyMode(const bool bIsCrazy) override;
	virtual bool IsCrazyMode() const override { return bIsCrazyMode; }
	/** End IRougeGameModeInterface */

	FOnNewRoundDelegate OnNewRound;
	FOnNewRoundDelegate OnNewEnemies;
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ACharacterEnemy> EnemyClass;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AEffectActorBase>> PotionActors;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameplayEffect> DefaultAttributes;
	
private:
	int32 EnemiesToKill;
	int32 EnemiesKilled;
	int32 CurrentRound;
	TArray<int32> RandomPotionSpawn;
	float A;
	float B;
	float C;
	float D;

	bool bIsCrazyMode;
	bool bStartCrazyMode;

	UPROPERTY()
	TArray<AActor*> EnemySpawnPoints;
	
	UPROPERTY()
	class UWeaponPoolObject* WeaponPoolObject;

	void StartNewRound();

	void CrazyMode();
	void SpawnEnemy(const int32 EnemyLevel);
	
	TArray<FVector> GetClosestSpawnerLocations();
	void SpawnRandomPotion();

};
