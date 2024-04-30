// Rouge

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

UCLASS()
class ROUGE_API AWeaponBase : public AActor
{
	GENERATED_BODY()

public:
	AWeaponBase();
	virtual void PostInitializeComponents() override;
	virtual void Tick(float DeltaTime) override;

	void SetDataAsset(UPrimaryDataAsset* DataAsset);

protected:
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	TObjectPtr<class UPaperFlipbookComponent> WeaponFlipbookComponent;
	TArray<FSoftObjectPath> AssetToLoad;
	
	void StartAsyncLoadDataAsset();
	virtual void GetAssetsToLoad();
	virtual void RequestAsyncLoadDataAsset();
	virtual void OnAssetsLoaded();

private:
	UPROPERTY(Replicated)
	TObjectPtr<class UWeaponBaseDataAsset> WeaponDataAsset;
};