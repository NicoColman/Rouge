// Rouge


#include "GASManager/GameplayAbilities/PlayerAbilities/PlayerChangeWorldAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GlobalManagers/RougeGameplayTags.h"
#include "Interfaces/CharacterInterfaces/CharacterPlayerInterface.h"
#include "Kismet/GameplayStatics.h"

void UPlayerChangeWorldAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                                const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                                const FGameplayEventData* TriggerEventData)
{
	const FRougeGameplayTags& GameplayTags = FRougeGameplayTags::Get();
	ApplyCooldown(Handle, ActorInfo, ActivationInfo);
	AActor* Actor = GetAvatarActorFromActorInfo();
	ICharacterPlayerInterface* Player = Cast<ICharacterPlayerInterface>(Actor);

	if (HitActors.Num() > 0)
	{
		for (auto& Pair : HitActors)
		{
			if (UAbilitySystemComponent* const TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Pair.Value))
			{
				TargetASC->RemoveActiveGameplayEffect(Pair.Key);
			}
		}
		HitActors.Empty();
	}

	TArray<AActor*> HitPlayerActorsArray;
	UGameplayStatics::GetAllActorsWithTag(this, "Player", HitPlayerActorsArray);
	
	AActor* AvatarActor = GetAvatarActorFromActorInfo();
	FVector StartLocation = AvatarActor->GetActorLocation();
	
	TArray<FHitResult> HitResults;
	GetWorld()->SweepMultiByProfile(
		HitResults,
		StartLocation,
		StartLocation + FVector(0, 0, -1000),
		FQuat::Identity,
		FName(),	
		FCollisionShape::MakeSphere(1000.f),
		FCollisionQueryParams()
		);
	
	for (FHitResult HitResult : HitResults)
	{
		AActor* HitActor = HitResult.GetActor();
		if (HitActor == AvatarActor || HitPlayerActorsArray.Contains(HitActor)) continue;
		
		if (UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(HitActor))
		{
			FGameplayEffectSpecHandle EffectSpec = GetAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(SlowEnemiesEffect, GetAbilityLevel(), GetAbilitySystemComponentFromActorInfo()->MakeEffectContext());
			FActiveGameplayEffectHandle AppliedEffect = TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpec.Data);
			HitActors.Add(AppliedEffect, HitActor);
		}
	}
	
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
		for (AActor* PlayerActor : HitPlayerActorsArray)
		{
			PlayerActor->SetActorLocation(NewLocation);
		}
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
	}
}
