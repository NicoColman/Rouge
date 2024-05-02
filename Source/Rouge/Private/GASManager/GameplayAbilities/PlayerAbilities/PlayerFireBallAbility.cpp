// Rouge


#include "GASManager/GameplayAbilities/PlayerAbilities/PlayerFireBallAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "CoreUtilites/RougeLibrary.h"
#include "WeaponManager/WeaponDataAssets/WeaponBaseDataAsset.h"
#include "PaperFlipbookComponent.h"
#include "GASManager/AbilityTasks/AbilityTask_TargetDataUnderMouse.h"
#include "WeaponManager/Projectiles/FireBallProjectile.h"

void UPlayerFireBallAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                             const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                             const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	GetWeaponAssets();

	UAbilityTask_TargetDataUnderMouse* TargetDataUnderMouse = UAbilityTask_TargetDataUnderMouse::CreateTargetDataUnderMouse(this);
	TargetDataUnderMouse->OnTargetData.AddDynamic(this, &UPlayerFireBallAbility::OnTargetData);
	TargetDataUnderMouse->ReadyForActivation();
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

void UPlayerFireBallAbility::OnTargetData(const FGameplayAbilityTargetDataHandle& TargetDataHandle)
{
	const FHitResult& HitData = UAbilitySystemBlueprintLibrary::GetHitResultFromTargetData(TargetDataHandle, 0);
	
	const FVector HitLocation = HitData.Location;
	const FVector Socket = WeaponFlipbook->GetSocketLocation("SOCKET_Tip");

	FRotator Rotation = (HitLocation - Socket).Rotation();
	Rotation.Pitch = 0.f;
	
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(Socket);
	SpawnTransform.SetRotation(Rotation.Quaternion());

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
	GetCurrentActorInfo()->AbilitySystemComponent->ExecuteGameplayCue(GameplayTags.GameplayCue_Ability_Spell_Cast, CueParams);

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this, Projectile, Rotation, Socket]()
	{
		FTransform FinishSpawnTransform;
		FinishSpawnTransform.SetLocation(Socket);
		FinishSpawnTransform.SetRotation(Rotation.Quaternion());
		Projectile->FinishSpawning(FinishSpawnTransform);
		EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), false, false);
	}, 0.6f, false);
}
