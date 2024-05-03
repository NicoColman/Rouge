// Rouge


#include "GASManager/GameplayCues/GameplayCuesEffectStatic/GameplayCue_EffectBase.h"

#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

bool UGameplayCue_EffectBase::OnExecute_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) const
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(
		MyTarget->GetWorld(),
		EffectParticles,
		MyTarget->GetActorLocation(),
		MyTarget->GetActorRotation(),
		FVector::OneVector * Parameters.AbilityLevel,
		true,
		true,
		ENCPoolMethod::None
		);

	UGameplayStatics::PlaySoundAtLocation(
		MyTarget->GetWorld(),
		EffectSound,
		MyTarget->GetActorLocation(),
		0.5f
		);
	
	return Super::OnExecute_Implementation(MyTarget, Parameters);
}
