// Rouge


#include "PlayerState/PlayerStateBase.h"

#include "GASManager/AbilitySystem/ASCBase.h"
#include "GASManager/AttributeSet/AttributeSetBase.h"

APlayerStateBase::APlayerStateBase()
{
	AbilitySystemComponent = CreateDefaultSubobject<UASCBase>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UAttributeSetBase>(TEXT("AttributeSet"));
}
