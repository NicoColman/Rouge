// Rouge


#include "GASManager/GameplayCues/GameplayCuesAbilities/GameplayCue_Pickup.h"

#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

bool UGameplayCue_Pickup::OnExecute_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) const
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(MyTarget->GetWorld(), PickupParticles, Parameters.Location, FRotator::ZeroRotator, FVector::OneVector * Parameters.AbilityLevel, true, true, ENCPoolMethod::None, true);
	UGameplayStatics::PlaySoundAtLocation(MyTarget, PickupSound, Parameters.Location, 1.f);
	return Super::OnExecute_Implementation(MyTarget, Parameters);
}
