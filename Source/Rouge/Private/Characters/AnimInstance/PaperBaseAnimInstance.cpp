// Rouge


#include "Characters/AnimInstance/PaperBaseAnimInstance.h"
#include "PaperZDCharacter.h"
#include "InputManager/PlayerController/RougePlayerController.h"

void UPaperBaseAnimInstance::OnInit_Implementation()
{
	Super::OnInit_Implementation();

	CachedCharacter = Cast<APaperZDCharacter>(GetOwningActor());
}

FVector2D UPaperBaseAnimInstance::GetDirection() const
{
	if (!CachedCharacter) return FVector2D::ZeroVector;
	
	if (const ARougePlayerController* PlayerController = Cast<ARougePlayerController>(CachedCharacter->GetController()))
	{
		return PlayerController->Directionality;
	}
	return FVector2D::ZeroVector;
}
