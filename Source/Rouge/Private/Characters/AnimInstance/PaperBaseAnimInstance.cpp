// Rouge


#include "Characters/AnimInstance/PaperBaseAnimInstance.h"
#include "PaperZDCharacter.h"
#include "InputManager/PlayerController/RougePlayerController.h"

void UPaperBaseAnimInstance::OnInit_Implementation()
{
	Super::OnInit_Implementation();

	CachedCharacter = Cast<APaperZDCharacter>(GetOwningActor());
}
