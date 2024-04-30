// Rouge

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "RougeAbilitySystemInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class URougeAbilitySystemInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ROUGE_API IRougeAbilitySystemInterface
{
	GENERATED_BODY()

public:
	virtual void AbilityActorInfoSet() = 0;
	virtual void AddCharacterAbilities(const TArray<TSubclassOf<class UGameplayAbility>>& Abilities) = 0;
	virtual void AbilityInputTagHeld(const struct FGameplayTag InputTag) = 0;
	virtual void AbilityInputTagPressed(const FGameplayTag InputTag) = 0;
	virtual void AbilityInputTagReleased(const FGameplayTag InputTag) = 0;
};
