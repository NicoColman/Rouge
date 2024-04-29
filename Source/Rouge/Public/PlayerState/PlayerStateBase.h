// Rouge

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "PlayerStateBase.generated.h"

/**
 * 
 */
UCLASS()
class ROUGE_API APlayerStateBase : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	APlayerStateBase();

	/** Begin AbilitySystemInterface */
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }
	/** End AbilitySystemInterface */

private:
	TObjectPtr<class UAbilitySystemComponent> AbilitySystemComponent;
	TObjectPtr<class UAttributeSet> AttributeSet;
};
