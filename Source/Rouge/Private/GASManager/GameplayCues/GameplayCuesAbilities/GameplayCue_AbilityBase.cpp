// Rouge


#include "GASManager/GameplayCues/GameplayCuesAbilities/GameplayCue_AbilityBase.h"

#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

bool UGameplayCue_AbilityBase::OnExecute_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) const
{
	FAbilityBaseCues CurrentAbility;
	const FGameplayTag Tag = Parameters.AggregatedSourceTags.First();
	CurrentAbility.CastParticles = AbilityEffects.FindRef(Tag).CastParticles;
	CurrentAbility.CastSound = AbilityEffects.FindRef(Tag).CastSound;
	
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(MyTarget->GetWorld(), CurrentAbility.CastParticles, MyTarget->GetActorLocation(), FRotator::ZeroRotator, FVector::OneVector * Parameters.AbilityLevel, true, true, ENCPoolMethod::None, true);
	UGameplayStatics::PlaySoundAtLocation(MyTarget, CurrentAbility.CastSound, MyTarget->GetActorLocation(), 1.f);
	return Super::OnExecute_Implementation(MyTarget, Parameters);
}
