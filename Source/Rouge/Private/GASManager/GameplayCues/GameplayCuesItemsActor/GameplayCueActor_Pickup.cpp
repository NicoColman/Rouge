// Rouge


#include "GASManager/GameplayCues/GameplayCuesItemsActor/GameplayCueActor_Pickup.h"

#include "NiagaraFunctionLibrary.h"
#include "PaperZDCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "PaperFlipbookComponent.h"

bool AGameplayCueActor_Pickup::OnActive_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters)
{
	const APaperZDCharacter* Character = Cast<APaperZDCharacter>(MyTarget);
	UNiagaraFunctionLibrary::SpawnSystemAttached(
		PickupParticles,
		Character->GetSprite(),
		FName("SOCKET_Tip"),
		FVector::ZeroVector,
		FRotator::ZeroRotator,
		FVector::OneVector * Parameters.AbilityLevel,
		EAttachLocation::SnapToTarget,
		true,
		ENCPoolMethod::None,
		true
		);	UGameplayStatics::PlaySoundAtLocation(MyTarget, PickupSound, MyTarget->GetActorLocation(), 1.f);
	return Super::OnActive_Implementation(MyTarget, Parameters);
}
