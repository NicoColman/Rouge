// Rouge


#include "InputManager/PlayerController/RougePlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputManager/EnhancedInputComponents/RougeEnhancedInputComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Characters/CharacterBase.h"
#include "Characters/CharacterPlayer.h"
#include "GameFramework/SpringArmComponent.h"
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
	
	SetSpriteDirection(InputAxisVector);
}

void ARougePlayerController::SetSpriteDirection(const FVector2D& InputAxisVector)
{
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	
	FVector2D SpriteDirection = FVector2D::ZeroVector;
	if (!FMath::IsNearlyZero(InputAxisVector.X) || !FMath::IsNearlyZero(InputAxisVector.Y))
	{
		const FVector MovementDirection = ForwardDirection * InputAxisVector.Y + RightDirection * InputAxisVector.X;
		const FVector CameraForwardVector = FVector::ForwardVector.RotateAngleAxis(Rotation.Yaw, FVector::UpVector);
		const float DotProduct = FVector::DotProduct(MovementDirection, CameraForwardVector);
		const float CrossProduct = FVector::CrossProduct(CameraForwardVector, MovementDirection).Z;

		if (FMath::Abs(DotProduct) > FMath::Abs(CrossProduct))
		{
			SpriteDirection.X = FMath::Sign(DotProduct);
		}
		else
		{
			SpriteDirection.Y = FMath::Sign(CrossProduct);
		}

		// Handle diagonal movement
		if (!FMath::IsNearlyZero(InputAxisVector.X) && !FMath::IsNearlyZero(InputAxisVector.Y))
		{
			SpriteDirection.X = FMath::Sign(InputAxisVector.X);
			SpriteDirection.Y = FMath::Sign(InputAxisVector.Y);

			// Fix inverted diagonal directions
			if (SpriteDirection.X == -1 && SpriteDirection.Y == 1) // Top-left
			{
				SpriteDirection.X = 1;
				SpriteDirection.Y = -1;
			}
			else if (SpriteDirection.X == 1 && SpriteDirection.Y == -1) // Bottom-right
			{
				SpriteDirection.X = -1;
				SpriteDirection.Y = 1;
			}
		}
	}
	
	GetCharacter()->SetDirectionality(SpriteDirection);
}

void ARougePlayerController::Look(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
    
	GetPawn()->AddControllerYawInput(InputAxisVector.X);

	constexpr float PitchSensitivity = 2.2f;
	CameraPitch = FMath::Clamp(CameraPitch + InputAxisVector.Y * PitchSensitivity, -52.0f, 52.0f);
	
	USpringArmComponent* CameraBoom = GetCharacter()->GetCameraBoom();
	FRotator CameraRotation = CameraBoom->GetComponentRotation();
	CameraRotation.Pitch = CameraPitch * -1.f;
	CameraBoom->SetWorldRotation(CameraRotation);
}

ACharacterPlayer* ARougePlayerController::GetCharacter()
{
	if (CachedCharacter) return CachedCharacter;
	return CachedCharacter = Cast<ACharacterPlayer>(GetPawn<APawn>());
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
