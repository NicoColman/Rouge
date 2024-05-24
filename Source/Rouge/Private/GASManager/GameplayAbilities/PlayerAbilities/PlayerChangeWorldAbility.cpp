// Rouge


#include "GASManager/GameplayAbilities/PlayerAbilities/PlayerChangeWorldAbility.h"

#include "AbilitySystemComponent.h"
#include "GlobalManagers/RougeGameplayTags.h"
#include "Interfaces/CharacterInterfaces/CharacterPlayerInterface.h"

void UPlayerChangeWorldAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                                const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                                const FGameplayEventData* TriggerEventData)
{
	const FRougeGameplayTags& GameplayTags = FRougeGameplayTags::Get();
	ApplyCooldown(Handle, ActorInfo, ActivationInfo);
	AActor* Actor = GetAvatarActorFromActorInfo();
	ICharacterPlayerInterface* Player = Cast<ICharacterPlayerInterface>(Actor);

	if (CurrentWorld.IsValid())
	{
		Player->SetChangeWorldLastLocation(CurrentWorld, Actor->GetActorLocation());
		const FGameplayTag NextWorldTag = CurrentWorld == GameplayTags.World_First ? GameplayTags.World_Second : GameplayTags.World_First;
		CurrentWorld = NextWorldTag;
		FVector NewLocation = Player->GetChangeWorldLastLocation(NextWorldTag);
		if (NewLocation == FVector::ZeroVector)
		{
			NewLocation = WorldStartSecondPosition;
		}
		Actor->SetActorLocation(NewLocation);
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
	}
	UE_LOG(LogTemp, Warning, TEXT("CurrentWorld: %s"), *CurrentWorld.ToString());
}
