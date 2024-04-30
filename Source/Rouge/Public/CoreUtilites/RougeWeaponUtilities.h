// Rouge

#pragma once

#include "CoreMinimal.h"
#include "RougeWeaponUtilities.generated.h"

UENUM()
enum class EWeaponTypes : uint8
{
	EWT_Proxy UMETA(DisplayName = "Proxy"),
	EWT_Base UMETA(DisplayName = "Base"),
	EWT_MAX UMETA(DisplayName = "DefaultMAX")
};