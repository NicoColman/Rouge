// Rouge

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CharacterBaseInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCharacterBaseInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ROUGE_API ICharacterBaseInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual int32 GetCharacterLevel() const = 0;
	virtual void SetPlayerWeapon(class AActor* Weapon) = 0;
	virtual class UCharacterBaseDataAsset* GetCharacterDataAsset() const = 0;
};
