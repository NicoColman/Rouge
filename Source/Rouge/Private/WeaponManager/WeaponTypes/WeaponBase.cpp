// Rouge


#include "WeaponManager/WeaponTypes/WeaponBase.h"

#include "PaperFlipbookComponent.h"
#include "GlobalManagers/RougeAssetManager.h"
#include "WeaponManager/WeaponDataAssets/WeaponBaseDataAsset.h"
#include "PaperFlipbook.h"
#include "Net/UnrealNetwork.h"

AWeaponBase::AWeaponBase()
{
	PrimaryActorTick.bCanEverTick = false;

	bReplicates = true;
	
	WeaponFlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("WeaponFlipbookComponent"));
	RootComponent = WeaponFlipbookComponent;
	WeaponFlipbookComponent->SetIsReplicated(true);
	WeaponFlipbookComponent->SetRelativeScale3D(FVector(4.f, 4.f, 4.f));

	WeaponFlipbookComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AWeaponBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SetReplicateMovement(true);
}

void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
}

void AWeaponBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AWeaponBase, WeaponDataAsset);
}

void AWeaponBase::SetDataAsset(UPrimaryDataAsset* DataAsset)
{
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this, DataAsset]()
	{
		WeaponDataAsset = Cast<UWeaponBaseDataAsset>(DataAsset);
		StartAsyncLoadDataAsset();
	}, 0.1f, false);
}

void AWeaponBase::StartAsyncLoadDataAsset()
{
	GetAssetsToLoad();
	RequestAsyncLoadDataAsset();
}

void AWeaponBase::GetAssetsToLoad()
{
	AssetToLoad.Add(WeaponDataAsset->WeaponFlipbook.ToSoftObjectPath());
}

void AWeaponBase::RequestAsyncLoadDataAsset()
{
	URougeAssetManager& AssetManager = URougeAssetManager::Get();
	const FStreamableDelegate LoadDelegate = FStreamableDelegate::CreateUObject(this, &AWeaponBase::OnAssetsLoaded);
	AssetManager.GetStreamableManager().RequestAsyncLoad(AssetToLoad, LoadDelegate);
}

void AWeaponBase::OnAssetsLoaded()
{
	WeaponFlipbookComponent->SetFlipbook(WeaponDataAsset->WeaponFlipbook.Get());
	UE_LOG(LogTemp, Warning, TEXT("WeaponFlipbookComponent->SetFlipbook(WeaponDataAsset->WeaponFlipbook.Get());"));
}
