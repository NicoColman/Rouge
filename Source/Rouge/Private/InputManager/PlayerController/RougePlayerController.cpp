// Rouge


#include "InputManager/PlayerController/RougePlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputManager/EnhancedInputComponents/RougeEnhancedInputComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Characters/CharacterBase.h"
#include "GlobalManagers/RougeGameplayTags.h"
#include "Interfaces/GASInterfaces/RougeAbilitySystemInterface.h"

ARougePlayerController::ARougePlayerController()
{
	AbilityInterface = nullptr;
	CachedCharacter = nullptr;
}

void ARougePlayerController::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;

	if (!ensure(PlayerBaseContext))
	{
		UE_LOG(LogTemp, Error, TEXT(" PlayerBaseContext is null."));
		return;
	}
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (!Subsystem)
	{
		return;
	}
	Subsystem->AddMappingContext(PlayerBaseContext, 0);
	FInputModeGameAndUI InputModeData;
}

void ARougePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	URougeEnhancedInputComponent* EnhancedInputComponentBase = CastChecked<URougeEnhancedInputComponent>(InputComponent);

	// Basic
	EnhancedInputComponentBase->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ARougePlayerController::Move);
	EnhancedInputComponentBase->BindAction(LookAction, ETriggerEvent::Triggered, this, &ARougePlayerController::Look);

	/** Data Asset*/
	EnhancedInputComponentBase->BindAbilityActions(InputConfigDataAsset, this,
		&ARougePlayerController::AbilityInputTagPressed, &ARougePlayerController::AbilityInputTagReleased,
		&ARougePlayerController::AbilityInputTagHeld);
}

void ARougePlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	if ((GetASC() && GetASC()->HasMatchingGameplayTag(
		FRougeGameplayTags::Get().Player_Block_InputPressed)) || !GetAbilityInterface()) return;
	
	GetAbilityInterface()->AbilityInputTagPressed(InputTag);
}

void ARougePlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if ((GetASC() && GetASC()->HasMatchingGameplayTag(
		FRougeGameplayTags::Get().Player_Block_InputReleased)) || !GetAbilityInterface()) return;
	
	GetAbilityInterface()->AbilityInputTagReleased(InputTag);
}

void ARougePlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if ((GetASC() && GetASC()->HasMatchingGameplayTag(
		FRougeGameplayTags::Get().Player_Block_InputHeld)) || !GetAbilityInterface()) return;

	GetAbilityInterface()->AbilityInputTagHeld(InputTag);
}

void ARougePlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
	
	FVector2D SpriteDirection = FVector2D::ZeroVector;
	if (!FMath::IsNearlyZero(InputAxisVector.X) || !FMath::IsNearlyZero(InputAxisVector.Y))
	{
		const FVector MovementDirection = ForwardDirection * InputAxisVector.Y + RightDirection * InputAxisVector.X;
		const FVector CameraForwardVector = FVector::ForwardVector.RotateAngleAxis(Rotation.Yaw, FVector::UpVector);
		const float DotProduct = FVector::DotProduct(MovementDirection, CameraForwardVector);
		const float CrossProduct = FVector::CrossProduct(CameraForwardVector, MovementDirection).Z;

		if (FMath::Abs(DotProduct) > FMath::Abs(CrossProduct))
		{
			SpriteDirection = FVector2D(FMath::Sign(DotProduct), 0.f);
		}
		else
		{
			SpriteDirection = FVector2D(0.f, FMath::Sign(CrossProduct));
		}
	}
	
	GetCharacter()->SetDirectionality(SpriteDirection);
}

void ARougePlayerController::Look(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	GetPawn()->AddControllerYawInput(InputAxisVector.X);
	GetPawn()->AddControllerPitchInput(InputAxisVector.Y);
}

ACharacterBase* ARougePlayerController::GetCharacter()
{
	if (CachedCharacter) return CachedCharacter;
	return CachedCharacter = Cast<ACharacterBase>(GetPawn<APawn>());
}

UAbilitySystemComponent* ARougePlayerController::GetASC()
{
	if (PawnASC) return PawnASC;
	return PawnASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>());
}

IRougeAbilitySystemInterface* ARougePlayerController::GetAbilityInterface()
{
	if (AbilityInterface) return AbilityInterface;
	return AbilityInterface = Cast<IRougeAbilitySystemInterface>(GetASC());
}
