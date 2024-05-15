// Rouge


#include "PlayerState/PlayerStateBase.h"

#include "GASManager/AbilitySystem/ASCBase.h"
#include "GASManager/AttributeSet/AttributeSetBase.h"
#include "Net/UnrealNetwork.h"

APlayerStateBase::APlayerStateBase()
{
	NetUpdateFrequency = 100.f;
	
	AbilitySystemComponent = CreateDefaultSubobject<UASCBase>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UAttributeSetBase>(TEXT("AttributeSet"));
	Level = 1;
	XP = 1;
	AttributePoints = 0;
	AbilityPoints = 1;
}

void APlayerStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APlayerStateBase, Level);
	DOREPLIFETIME(APlayerStateBase, XP);
	DOREPLIFETIME(APlayerStateBase, AttributePoints);
	DOREPLIFETIME(APlayerStateBase, AbilityPoints);
}

void APlayerStateBase::AddToXP(const int32 AddedXP)
{
	XP += AddedXP;
	OnXPChangedDelegate.Broadcast(XP);
}

void APlayerStateBase::SetXP(const int32 NewXP)
{
	XP = NewXP;
	OnXPChangedDelegate.Broadcast(XP);
}

void APlayerStateBase::OnRep_XP(int32 OldXP) const
{
	OnXPChangedDelegate.Broadcast(XP);
}

void APlayerStateBase::OnRep_AttributePoints(int32 OldAttributePoints) const
{
	OnAttributePointsChangedDelegate.Broadcast(AttributePoints);
}

void APlayerStateBase::OnRep_AbilityPoints(int32 OldAbilityPoints) const
{
	OnAbilityPointsChangedDelegate.Broadcast(AbilityPoints);
}

void APlayerStateBase::AddToLevel(const int32 AddedLevel)
{
	Level += AddedLevel;
	OnLevelChangedDelegate.Broadcast(Level);
}

void APlayerStateBase::SetLevel(const int32 NewLevel)
{
	Level = NewLevel;
	OnLevelChangedDelegate.Broadcast(Level);
}

void APlayerStateBase::AddAttributePoints(const int32 AddedAttributePoints)
{
	AttributePoints += AddedAttributePoints;
	OnAttributePointsChangedDelegate.Broadcast(AttributePoints);
}

void APlayerStateBase::AddAbilityPoints(const int32 AddedAbilityPoints)
{
	AbilityPoints += AddedAbilityPoints;
	OnAbilityPointsChangedDelegate.Broadcast(AbilityPoints);
}

void APlayerStateBase::OnRep_Level(int32 OldLevel) const
{
	OnLevelChangedDelegate.Broadcast(Level);
}
