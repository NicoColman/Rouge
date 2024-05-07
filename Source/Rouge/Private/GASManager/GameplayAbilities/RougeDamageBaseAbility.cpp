// Rouge


#include "GASManager/GameplayAbilities/RougeDamageBaseAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

FGameplayEffectSpecHandle URougeDamageBaseAbility::AssignDamageTypes(const UAbilitySystemComponent* ASC ,const FGameplayEffectContextHandle& ContextHandle) const
{
	const FGameplayEffectSpecHandle DamageEffectSpecHandle = ASC->MakeOutgoingSpec(DamageEffectClass, GetAbilityLevel(), ContextHandle);
	for (auto& Pair : DamageTypes)
	{
		const float ScaledDamage = Pair.Value.GetValueAtLevel(GetAbilityLevel());
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(DamageEffectSpecHandle, Pair.Key, ScaledDamage);
	}
	return DamageEffectSpecHandle;
}
