// Rouge

#pragma once

#include "CoreMinimal.h"
#include "GASManager/GameplayAbilities/RougeDamageBaseAbility.h"
#include "GlobalManagers/RougeGameplayTags.h"
#include "PlayerFireBallAbility.generated.h"

/**
 * 
 */
UCLASS()
class ROUGE_API UPlayerFireBallAbility : public URougeDamageBaseAbility
{
	GENERATED_BODY()

public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	
private:
	void GetWeaponAssets();
	void ApplyDamageEffect(class AFireBallProjectile* SpawningProjectile) const;
	
	UFUNCTION()
	void OnTargetData(const FGameplayAbilityTargetDataHandle& TargetDataHandle);
	const FRougeGameplayTags& GameplayTags = FRougeGameplayTags::Get();
	
	FGameplayTag WeaponTag;
	TObjectPtr<class UPaperFlipbookComponent> WeaponFlipbook;
	TSubclassOf<class AFireBallProjectile> ProjectileClass;
};
