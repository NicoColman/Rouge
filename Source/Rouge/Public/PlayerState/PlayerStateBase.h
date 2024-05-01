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
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	/** Begin AbilitySystemInterface */
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }
	/** End AbilitySystemInterface */

private:
	TObjectPtr<class UAbilitySystemComponent> AbilitySystemComponent;
	TObjectPtr<class UAttributeSet> AttributeSet;

	UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_Level)
	int32 Level;

	UFUNCTION()
	void OnRep_Level(int32 OldLevel);

public:
	int32 GetCharacterLevel() const { return Level; }
};
