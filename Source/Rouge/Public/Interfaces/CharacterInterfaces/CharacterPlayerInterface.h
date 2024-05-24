// Rouge

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CharacterPlayerInterface.generated.h"

struct FGameplayTag;
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCharacterPlayerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ROUGE_API ICharacterPlayerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void AddToXP(const int32 InXP) = 0;
	virtual void AddToPlayerLevel(const int32 InLevel) = 0;
	virtual void AddToAttributesPoints(const int32 InPoints) = 0;
	virtual void AddToSpellPoints(const int32 InPoints) = 0;
	virtual void LevelUp() = 0;
	virtual int32 GetXP() const = 0;
	virtual int32 FindLevelForXP(const int32 InXP) const = 0;
	virtual int32 GetAttributesPointsRewards(const int32 Level) const = 0;
	virtual int32 GetSpellPointsRewards(const int32 Level) const = 0;
	virtual void SetChangeWorldLastLocation(const FGameplayTag& WorldTag, const FVector& Location) = 0;
	virtual FVector GetChangeWorldLastLocation(const FGameplayTag& WorldTag) const = 0;	
};
