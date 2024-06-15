// Rouge


#include "GameMode/RougeGameModeBase.h"

#include "AbilitySystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SpawnManager/WeaponSpawners/WeaponPoolObject.h"
#include "GameFramework/PlayerStart.h"
#include "GameFramework/Character.h"
#include "Characters/CharacterEnemy.h"
#include "GASManager/EffectActors/EffectActorBase.h"

ARougeGameModeBase::ARougeGameModeBase()
{
	WeaponPoolObject = nullptr;

	A = 4.0f;
	B = 2.0f;
	C = 1.0f;
	D = 5.0f;

	EnemiesKilled = 0;
	CurrentRound = 0;
	EnemiesToKill = 1;
	bIsCrazyMode = false;
	bStartCrazyMode = false;
}

void ARougeGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
	WeaponPoolObject = NewObject<UWeaponPoolObject>(this, UWeaponPoolObject::StaticClass());
	WeaponPoolObject->WeaponPoolManager(this);

	StartNewRound();
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

void ARougeGameModeBase::StartNewRound()
{
	CurrentRound++;
	EnemiesKilled = 0;
	EnemiesToKill = FMath::RoundToInt(A * FMath::LogX(B, CurrentRound + C)) + D;
	
	const int32 NumberOfRandomPotionsToSpawn = CurrentRound / 5 + 1;
	

	for (int32 i = 0; i < NumberOfRandomPotionsToSpawn; ++i)
	{
		int32 RandomIndex = FMath::RandRange(0, EnemiesToKill - 1);
		while (RandomPotionSpawn.Contains(RandomIndex))
		{
			RandomIndex = FMath::RandRange(0, EnemiesToKill - 1);
		}
		RandomPotionSpawn.Add(RandomIndex);
	}
	
	const TArray<FVector> ClosestSpawnerLocations = GetClosestSpawnerLocations();
	for (int i = 0; i < EnemiesToKill; ++i)
	{
		SpawnEnemy(CurrentRound);
	}

	OnNewRound.Broadcast(CurrentRound);
	OnNewEnemies.Broadcast(EnemiesToKill);
}

void ARougeGameModeBase::SetCrazyMode(const bool bIsCrazy)
{
	bIsCrazyMode = bIsCrazy;
	if (bIsCrazyMode)
	{
		constexpr int32 EnemiesLeft = 999;
		OnNewEnemies.Broadcast(EnemiesLeft);
		CrazyMode();
	}
	else
	{
		const int32 EnemiesLeft = EnemiesToKill - EnemiesKilled;
		OnNewEnemies.Broadcast(EnemiesLeft);
	}
}

void ARougeGameModeBase::CrazyMode()
{
	if (bStartCrazyMode)
	{
		SpawnEnemy(1000);
	}
	else
	{
		bStartCrazyMode = true;
		for (int i = 0; i < 20; ++i)
		{
			SpawnEnemy(1000);
		}
	}
}

void ARougeGameModeBase::EnemyKilled()
{
	if (bIsCrazyMode)
	{
		SpawnEnemy(1000);
		const int32 RandomIndex = FMath::RandRange(0, 1);
		if (RandomIndex == 0)
		{
			SpawnRandomPotion();
		}
	}
	else
	{
		EnemiesKilled++;
		const int32 EnemiesLeft = EnemiesToKill - EnemiesKilled;
		OnNewEnemies.Broadcast(EnemiesLeft);

		for (const int32 RandomPotionIndex : RandomPotionSpawn)
		{
			if (EnemiesKilled == RandomPotionIndex)
			{
				SpawnRandomPotion();
				RandomPotionSpawn.Remove(RandomPotionIndex);
				break;
			}
		}
	
		if (EnemiesKilled >= EnemiesToKill)
		{
			StartNewRound();
		}
	}
}

void ARougeGameModeBase::SpawnEnemy(const int32 EnemyLevel)
{
	const TArray<FVector> ClosestSpawnerLocations = GetClosestSpawnerLocations();
	
	const FVector SpawnerLocation = ClosestSpawnerLocations[FMath::RandRange(0, ClosestSpawnerLocations.Num() - 1)];
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	if (ACharacterEnemy* Enemy = GetWorld()->SpawnActor<ACharacterEnemy>(EnemyClass, SpawnerLocation, FRotator::ZeroRotator, SpawnParams))
	{
		if (UAbilitySystemComponent* ASC = Enemy->GetAbilitySystemComponent())
		{
			const FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(DefaultAttributes, EnemyLevel, ASC->MakeEffectContext());
			ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		}
		Enemy->SetLevel(EnemyLevel);
	}
}

void ARougeGameModeBase::SpawnRandomPotion()
{
	const TSubclassOf<AEffectActorBase> PotionClass = PotionActors[FMath::RandRange(0, PotionActors.Num() - 1)];
	const TArray<FVector> PotionSpawnPoints = GetClosestSpawnerLocations();
		
	if (PotionSpawnPoints.Num() > 0)
	{
		const FVector SpawnerLocation = PotionSpawnPoints[FMath::RandRange(0, PotionSpawnPoints.Num() - 1)];
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		AEffectActorBase* Potion = GetWorld()->SpawnActor<AEffectActorBase>(PotionClass, SpawnerLocation, FRotator::ZeroRotator, SpawnParams);

		const int32 PotionLevel = FMath::RandRange(1, 4);
		Potion->SetActorLevel(PotionLevel);
	}
}

TArray<FVector> ARougeGameModeBase::GetClosestSpawnerLocations()
{
	TArray<FVector> ClosestSpawnerLocations;

	if (EnemySpawnPoints.Num() == 0)
	{
		UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName(TEXT("EnemySpawnerPoint")), EnemySpawnPoints);
	}
	if (EnemySpawnPoints.Num() > 0)
	{
		const ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		if (!PlayerCharacter) return ClosestSpawnerLocations;
		
		const FVector PlayerLocation = PlayerCharacter->GetActorLocation();

		TArray<TPair<float, AActor*>> SpawnerQueue;

		for (AActor* Spawner : EnemySpawnPoints)
		{
			float Distance = FVector::Distance(PlayerLocation, Spawner->GetActorLocation());
			SpawnerQueue.HeapPush(TPair<float, AActor*>(Distance, Spawner));
		}

		for (int32 i = 0; i < 6 && SpawnerQueue.Num() > 0; ++i)
		{
			TPair<float, AActor*> ClosestSpawnerPair;
			SpawnerQueue.HeapPop(ClosestSpawnerPair);
			const AActor* ClosestSpawner = ClosestSpawnerPair.Value;
			ClosestSpawnerLocations.Add(ClosestSpawner->GetActorLocation());
		}
	}

	return ClosestSpawnerLocations;
}
