// Rouge


#include "GASManager/RougeAbilitySystemGlobals.h"

#include "CoreUtilites/RougeAbilityTypes.h"

FGameplayEffectContext* URougeAbilitySystemGlobals::AllocGameplayEffectContext() const
{
	return new FRougeGameplayEffectContext();
}
