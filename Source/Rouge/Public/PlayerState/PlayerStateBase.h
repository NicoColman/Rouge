// Rouge

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "PlayerStateBase.generated.h"

class ULevelUpInfoDataAsset;
DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerStatChanged, int32 /* StatValue */);

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

	FOnPlayerStatChanged OnXPChangedDelegate;
	FOnPlayerStatChanged OnLevelChangedDelegate;
	FOnPlayerStatChanged OnAttributePointsChangedDelegate;
	FOnPlayerStatChanged OnAbilityPointsChangedDelegate;

	void AddToXP(const int32 AddedXP);
	void AddToLevel(const int32 AddedLevel);
	void SetXP(const int32 NewXP);
	void SetLevel(const int32 NewLevel);
	void AddAttributePoints(const int32 AddedAttributePoints);
	void AddAbilityPoints(const int32 AddedAbilityPoints);

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<ULevelUpInfoDataAsset> LevelUpInfo;

private:
	UPROPERTY()
	TObjectPtr<class UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<class UAttributeSet> AttributeSet;

	UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_Level)
	int32 Level;

	UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_XP)
	int32 XP;

	UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_AttributePoints)
	int32 AttributePoints;

	UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_AbilityPoints)
	int32 AbilityPoints;

	UFUNCTION()
	void OnRep_Level(int32 OldLevel) const;

	UFUNCTION()
	void OnRep_XP(int32 OldXP) const;

	UFUNCTION()
	void OnRep_AttributePoints(int32 OldAttributePoints) const;

	UFUNCTION()
	void OnRep_AbilityPoints(int32 OldAbilityPoints) const;

public:
	FORCEINLINE UAttributeSet* GetAttributeSet() const { return AttributeSet; }
	FORCEINLINE int32 GetCharacterLevel() const { return Level; }
	FORCEINLINE int32 GetXP() const { return XP; }
	FORCEINLINE int32 GetAttributePoints() const { return AttributePoints; }
	FORCEINLINE int32 GetAbilityPoints() const { return AbilityPoints; }
};
