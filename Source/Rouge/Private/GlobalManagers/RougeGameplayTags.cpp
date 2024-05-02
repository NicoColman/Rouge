// Rouge


#include "GlobalManagers/RougeGameplayTags.h"
#include "GameplayTagsManager.h"
#include "AbilitySystemComponent.h"

FRougeGameplayTags FRougeGameplayTags::GameplayTags;

void FRougeGameplayTags::InitializeNativeGameplayTags() {
	GameplayTags.Attribute_Vital_Health = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Vital.Health"),
		FString("Set Base Health")
		);
	GameplayTags.Attribute_Vital_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Vital.MaxHealth"),
		FString("Set Max Health")
		);

	/**
	 * Input Tags
	 */
	GameplayTags.InputTag_Weapon_Attack = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.LMB"),
		FString("Input tag for Left Mouse Button")
		);
	GameplayTags.InputTag_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.RMB"),
		FString("Input tag for Right Mouse Button")
		);
	GameplayTags.InputTag_Jump = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.Jump"),
		FString("Input tag for Jump")
		);
	GameplayTags.InputTag_Sprint = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.Sprint"),
		FString("Input tag for Sprint")
		);
	GameplayTags.InputTag_Dash = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.Dash"),
		FString("Input tag for Dash")
		);
	GameplayTags.InputTag_Equip = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.Equip"),
		FString("Input tag for Equip")
		);
	GameplayTags.InputTag_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.1"),
		FString("Input tag for 1")
		);
	GameplayTags.InputTag_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.2"),
		FString("Input tag for 2")
		);
	GameplayTags.InputTag_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.3"),
		FString("Input tag for 3")
		);
	GameplayTags.InputTag_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.4"),
		FString("Input tag for 4")
		);

	/** Begin Input Block Tags */
	GameplayTags.Player_Block_InputPressed = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Player.Block.InputPressed"),
		FString("Player Block Input Pressed")
		);
	GameplayTags.Player_Block_InputReleased = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Player.Block.InputReleased"),
		FString("Player Block Input Released")
		);
	GameplayTags.Player_Block_InputHeld = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Player.Block.InputHeld"),
		FString("Player Block Input Held")
		);
	/** End Input Block Tags */
	
	/**
	 * Player State Tags
	 */
	GameplayTags.StateTag_Player_Jumping = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("StateTag.Player.Jumping"),
		FString("State tag for Jumping")
		);
	GameplayTags.StateTag_Player_Sprinting = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("StateTag.Player.Sprinting"),
		FString("State tag for Sprinting")
		);
	GameplayTags.StateTag_Player_AbleEquip = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("StateTag.Player.AbleEquip"),
		FString("State tag for Able Equip")
		);

	/** Begin WeaponType Tags*/
	GameplayTags.WeaponType = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("WeaponType"),
	FString("Weapon Type")
	);
	GameplayTags.WeaponType_Proxy = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("WeaponType.Proxy"),
	FString("Weapon Type Proxy")
	);

	// Staff Weapons
	GameplayTags.WeaponType_Staff = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("WeaponType.Staff"),
		FString("Weapon Type Staff")
		);
	GameplayTags.WeaponType_Staff_Blue = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("WeaponType.Staff.Blue"),
		FString("Weapon Type Staff Blue")
		);
	GameplayTags.WeaponType_Staff_Red = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("WeaponType.Staff.Red"),
		FString("Weapon Type Staff Red")
		);
	GameplayTags.WeaponType_Staff_Green = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("WeaponType.Staff.Green"),
		FString("Weapon Type Staff Green")
		);
	GameplayTags.WeaponType_Staff_Yellow = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("WeaponType.Staff.Yellow"),
		FString("Weapon Type Staff Yellow")
		);
	GameplayTags.WeaponType_Staff_Purple = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("WeaponType.Staff.Purple"),
		FString("Weapon Type Staff Purple")
		);
	GameplayTags.WeaponType_Staff_White = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("WeaponType.Staff.White"),
		FString("Weapon Type Staff White")
		);
	GameplayTags.WeaponType_Staff_Combined = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("WeaponType.Staff.Combined"),
		FString("Weapon Type Staff Combined")
		);

	// Melee Weapons
	GameplayTags.WeaponType_Melee = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("WeaponType.Melee"),
		FString("Weapon Type Melee")
		);
	/** End WeaponType Tags*/
	
	/** Begin Montages Tags */
	GameplayTags.MontageTag_Melee_Attack = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("MontageTag.Melee.Attack"),
		FString("Montage Tag Melee Attack")
		);
	GameplayTags.MontageTag_Melee_AttackEnd = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("MontageTag.Melee.AttackEnd"),
		FString("Montage Tag Melee Attack End")
		);
	/** End Montages Tags */

	/** Begin Damage Tags */
	GameplayTags.Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage"),
		FString("Damage")
		);
	/** End Damage Tags */

	/** Begin Effect Tags */
	GameplayTags.Effect_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Effect.HitReact"),
		FString("Effect Hit React")
		);
	/** End Effect Tags */

	/** Begin GameplayCue Tags */
	// Player GameplayCue Tags
	GameplayTags.GameplayCue_Ability_Spell_Cast = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("GameplayCue.Ability.Spell.Cast"),
		FString("Gameplay Cue for Spell Cast Ability")
		);
	/** End GameplayCue Tags */

	/** Begin Event Tags */
	// Static Tags
	GameplayTags.GameplayEvent_Ability_Spell_Cast = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("GameplayEvent.Ability.Spell.Cast"),
		FString("Gameplay Event for Spell Cast Ability")
		);
	GameplayTags.GameplayCue_Ability_Pickup = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("GameplayCue.Ability.Pickup"),
		FString("Gameplay Cue for Ability Pickup")
		);

	// Loop Tags
	GameplayTags.GameplayCue_Ability_Pickup_Loop = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("GameplayCue.Ability.Pickup.Loop"),
		FString("Gameplay Cue for Ability Pickup Loop")
		);
	// Enemy Event Tags
	GameplayTags.Event_Enemy_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Event.Enemy.HitReact"),
		FString("Event Enemy Hit React")
		);
	/** End Event Tags */
}

FGameplayTag FRougeGameplayTags::GetMatchTagFromASC(UAbilitySystemComponent* ASC, const FName& RequestedTag)
{
	FGameplayTagContainer TagContainer;
	ASC->GetOwnedGameplayTags(TagContainer);
	
	for (const FGameplayTag& Tag : TagContainer)
	{
		if (Tag.MatchesTag(FGameplayTag::RequestGameplayTag(RequestedTag)))
		{
			return Tag;
		}
	}
	
	return FGameplayTag();
}
