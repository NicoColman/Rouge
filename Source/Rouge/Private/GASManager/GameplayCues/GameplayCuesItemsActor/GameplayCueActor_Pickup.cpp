// Rouge


#include "GASManager/GameplayCues/GameplayCuesItemsActor/GameplayCueActor_Pickup.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "PaperZDCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "PaperFlipbookComponent.h"
#include "Components/AudioComponent.h"

bool AGameplayCueActor_Pickup::OnActive_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters)
{
	const APaperZDCharacter* Character = Cast<APaperZDCharacter>(MyTarget);
	SpawnedParticles = UNiagaraFunctionLibrary::SpawnSystemAttached(
		PickupParticles,
		Character->GetSprite(),
		FName(),
		FVector::ZeroVector,
		FRotator::ZeroRotator,
		FVector::OneVector * Parameters.AbilityLevel,
		EAttachLocation::SnapToTarget,
		true,
		ENCPoolMethod::None,
		true
		);
	
	SpawnedSound = UGameplayStatics::SpawnSoundAttached(
		PickupSound,
		Character->GetSprite(),
		FName(),
		FVector::ZeroVector,
		EAttachLocation::SnapToTarget,
		true,
		0.5f,
		1.0f,
		0.0f,
		nullptr,
		nullptr,
		true
		);
	
	return Super::OnActive_Implementation(MyTarget, Parameters);
}

bool AGameplayCueActor_Pickup::OnRemove_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters)
{
	if (SpawnedParticles && SpawnedSound)
	{
		SpawnedParticles->DestroyComponent();
		SpawnedSound->DestroyComponent();
	}
	return Super::OnRemove_Implementation(MyTarget, Parameters);
}
