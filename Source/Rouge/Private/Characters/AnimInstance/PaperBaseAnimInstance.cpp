// Rouge


#include "Characters/AnimInstance/PaperBaseAnimInstance.h"
#include "Characters/CharacterBase.h"
#include "InputManager/PlayerController/RougePlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"

void UPaperBaseAnimInstance::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CachedCharacter = !CachedCharacter ? Cast<ACharacterBase>(GetOwningActor()) : CachedCharacter;
	if (!CachedCharacter) return;
	bIsFalling = CachedCharacter->GetCharacterMovement()->IsFalling();
	bHasVelocity = CachedCharacter->GetCharacterMovement()->Velocity.Size() > 0.f;
	Velocity = CachedCharacter->GetCharacterMovement()->Velocity;
	Directionality = CachedCharacter->GetDirectionality();
}
