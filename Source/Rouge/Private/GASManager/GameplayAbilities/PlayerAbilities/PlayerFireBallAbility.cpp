// Rouge


#include "GASManager/GameplayAbilities/PlayerAbilities/PlayerFireBallAbility.h"

#include "AbilitySystemComponent.h"
#include "CoreUtilites/RougeLibrary.h"
#include "WeaponManager/WeaponDataAssets/WeaponBaseDataAsset.h"
#include "PaperFlipbookComponent.h"
#include "WeaponManager/Projectiles/FireBallProjectile.h"

void UPlayerFireBallAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                             const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                             const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	//GetWeaponAssets();
	const FGameplayTag NewWeaponTag = GameplayTags.GetMatchTagFromASC(GetAbilitySystemComponentFromActorInfo(), "WeaponType.Staff.Red");

	if (const UWeaponBaseDataAsset* WeaponDataAsset = Cast<UWeaponBaseDataAsset>(URougeLibrary::GetPrimaryObjectFromTag(NewWeaponTag, "Weapon")))
	{
		WeaponTag = NewWeaponTag;
		WeaponFlipbook = WeaponDataAsset->WeaponFlipbookComponent;
		ProjectileClass = WeaponDataAsset->Projectile.Get();
	}

	FTransform SpawnTransform;
	const FVector Socket = WeaponFlipbook->GetSocketLocation("SOCKET_Tip");
	SpawnTransform.SetLocation(Socket);

	AFireBallProjectile* Projectile = GetWorld()->SpawnActorDeferred<AFireBallProjectile>(
		ProjectileClass,
		SpawnTransform,
		GetOwningActorFromActorInfo(),
		Cast<APawn>(GetOwningActorFromActorInfo()),
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn
		);

	FGameplayCueParameters CueParams;
	CueParams.Location = Socket;
	CueParams.TargetAttachComponent = WeaponFlipbook;
	FGameplayTagContainer SourceTags;
	SourceTags.AddTag(WeaponTag);
	CueParams.AggregatedSourceTags = SourceTags;
	ActorInfo->AbilitySystemComponent->ExecuteGameplayCue(GameplayTags.GameplayCue_Ability_Spell_Cast, CueParams);

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this, Projectile, SpawnTransform, Handle, ActorInfo, ActivationInfo]()
	{
		FTransform FinishSpawnTransform;
		const FVector Socket = WeaponFlipbook->GetSocketLocation("SOCKET_Tip");
		FinishSpawnTransform.SetLocation(Socket);
		Projectile->FinishSpawning(FinishSpawnTransform);
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
	}, 0.6f, false);
	
}

void UPlayerFireBallAbility::GetWeaponAssets()
{
	const FGameplayTag NewWeaponTag = GameplayTags.GetMatchTagFromASC(GetAbilitySystemComponentFromActorInfo(), "WeaponType.Staff.Red");
	

	if (const UWeaponBaseDataAsset* WeaponDataAsset = Cast<UWeaponBaseDataAsset>(URougeLibrary::GetPrimaryObjectFromTag(NewWeaponTag, "Weapon")))
	{
		WeaponTag = NewWeaponTag;
		WeaponFlipbook = WeaponDataAsset->WeaponFlipbookComponent;
		ProjectileClass = WeaponDataAsset->Projectile.Get();
	}
}
