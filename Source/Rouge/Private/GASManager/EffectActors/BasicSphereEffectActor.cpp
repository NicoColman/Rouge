// Rouge


#include "GASManager/EffectActors/BasicSphereEffectActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Components/SphereComponent.h"


// Sets default values
ABasicSphereEffectActor::ABasicSphereEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SetRootComponent(SphereComponent);
}

void ABasicSphereEffectActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABasicSphereEffectActor::BeginPlay()
{
	Super::BeginPlay();
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ABasicSphereEffectActor::OnSphereOverlap);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &ABasicSphereEffectActor::OnSphereEndOverlap);
}

void ABasicSphereEffectActor::Destroyed()
{
	for (const auto& ActiveEffect : ActiveEffectsMap)
	{
		ActiveEffect.Value->RemoveActiveGameplayEffect(ActiveEffect.Key, -1);
	}
	Super::Destroyed();
}

void ABasicSphereEffectActor::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                              UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor);

	if (TargetASC && EffectSpecToApply.IsValid())
	{
		const FActiveGameplayEffectHandle EffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecToApply.Data.Get());
		ActiveEffectsMap.Add(EffectHandle, TargetASC);
	}
}

void ABasicSphereEffectActor::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor))
	{
		TArray<FActiveGameplayEffectHandle> ActiveEffectsToRemove;
		for (auto& ActiveEffect : ActiveEffectsMap)
		{
			if (ActiveEffect.Value == TargetASC)
			{
				TargetASC->RemoveActiveGameplayEffect(ActiveEffect.Key, -1);
				ActiveEffectsToRemove.Add(ActiveEffect.Key);
			}
		}
		for (auto& ActiveEffect : ActiveEffectsToRemove)
		{
			ActiveEffectsMap.FindAndRemoveChecked(ActiveEffect);
		}
	}
}
