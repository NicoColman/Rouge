// Rouge


#include "GASManager/GameplayCues/GameplayCuesAbilities/GameplayCue_Fireball.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

UGameplayCue_SpellCast::UGameplayCue_SpellCast()
{
}

bool UGameplayCue_SpellCast::OnExecute_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) const
{
	const FGameplayTag Tag = Parameters.AggregatedSourceTags.First();
	FCastEffect CurrentWeaponCast;
	CurrentWeaponCast.CastParticles = CastEffects.FindRef(Tag).CastParticles;
	CurrentWeaponCast.CastSound = CastEffects.FindRef(Tag).CastSound;

	USceneComponent* TargetComponent = Parameters.TargetAttachComponent.Get();
	UNiagaraFunctionLibrary::SpawnSystemAttached(
		CurrentWeaponCast.CastParticles,
		TargetComponent, FName("SOCKET_Tip"),
		FVector::ZeroVector,
		FRotator::ZeroRotator,
		FVector::OneVector,
		EAttachLocation::SnapToTarget,
		true,
		ENCPoolMethod::None,
		true
		);
	
	UGameplayStatics::PlaySoundAtLocation(MyTarget, CurrentWeaponCast.CastSound, Parameters.Location, 1.f);

	return Super::OnExecute_Implementation(MyTarget, Parameters);
}
