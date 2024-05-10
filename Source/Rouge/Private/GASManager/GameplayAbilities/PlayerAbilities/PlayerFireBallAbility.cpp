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
	ApplyCooldown(Handle, ActorInfo, ActivationInfo);
	
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
		DamageEffectClass = WeaponDataAsset->DamageEffectClass;
		DamageType = WeaponDataAsset->DamageType;
		Damage = WeaponDataAsset->Damage;
	}
}

void UPlayerFireBallAbility::OnTargetData(const FGameplayAbilityTargetDataHandle& TargetDataHandle)
{
	const FHitResult& HitData = UAbilitySystemBlueprintLibrary::GetHitResultFromTargetData(TargetDataHandle, 0);
	
	const FVector HitLocation = HitData.Location;
	const FVector Socket = WeaponFlipbook->GetSocketLocation("SOCKET_Tip");
	
	//const FTransform SpawnTransform;

	AFireBallProjectile* Projectile = GetWorld()->SpawnActorDeferred<AFireBallProjectile>(
		ProjectileClass,
		FTransform(),
		GetOwningActorFromActorInfo(),
		Cast<APawn>(GetOwningActorFromActorInfo()),
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn
		);
	
	Projectile->DamageEffectParams = MakeDamageEffectParamsFromClassDefaults();
	
	ExecuteCastGameplayCue(Socket);
	
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this, Projectile, HitLocation]()
	{
		FTransform FinishSpawnTransform;
		const FVector FinishedSocket = WeaponFlipbook->GetSocketLocation("SOCKET_Tip");
		const FRotator FinishedRotation = (HitLocation - FinishedSocket).Rotation();
		const FRotator FinishedModifyPitch = FinishedRotation + FRotator(1.5f, 0.f, 0.f);

		//FinishedRotation.Pitch = 0.f;
		
		FinishSpawnTransform.SetLocation(FinishedSocket);
		FinishSpawnTransform.SetRotation(FinishedModifyPitch.Quaternion());
		//FinishSpawnTransform.SetScale3D(FVector(5.f, 5.f, 5.f));
		Projectile->FinishSpawning(FinishSpawnTransform);
		EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true, false);
	}, 0.6f, false);
}

void UPlayerFireBallAbility::ExecuteCastGameplayCue(const FVector& Socket) const
{
	FGameplayCueParameters CueParams;
	CueParams.Location = Socket;
	CueParams.TargetAttachComponent = WeaponFlipbook;
	CueParams.AggregatedSourceTags.AddTag(WeaponTag);
	CueParams.AbilityLevel = 1.f;
	GetCurrentActorInfo()->AbilitySystemComponent->ExecuteGameplayCue(GameplayTags.GameplayCue_Ability_Spell_Cast, CueParams);

}