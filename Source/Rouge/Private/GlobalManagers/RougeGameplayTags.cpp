// Rouge


#include "GlobalManagers/RougeGameplayTags.h"
#include "GameplayTagsManager.h"
#include "AbilitySystemComponent.h"

FRougeGameplayTags FRougeGameplayTags::GameplayTags;

void FRougeGameplayTags::InitializeNativeGameplayTags(){

	/**
	 *	Input Related Tags
	 */
	
	/** Begin Input Tags*/
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
	/** End Input Tags */

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
	 *	Player Related Tags
	 */
	
	/** Begin State Tags */
	// Character State Tags
	GameplayTags.StateTag_Character_Shocked = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("StateTag.Character.Shocked"),
		FString("State tag for Shocked")
		);
	// Player State Tags
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
	GameplayTags.StateTag_Player_Dashing = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("StateTag.Player.Dashing"),
		FString("State tag for Dashing")
		);
	GameplayTags.StateTag_Player_Healing = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("StateTag.Player.Healing"),
		FString("State tag for Healing")
		);
	/** End State Tags */

	
	/**
	 *	GAS Related Tags
	 */
	
	/** Begin Attribute Tags */
	// Primary Attributes Tags
	GameplayTags.Attribute_Primary_Strength = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Strength"),
		FString("Set Base Strength")
		);
	GameplayTags.Attribute_Primary_Intelligence = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Intelligence"),
		FString("Set Base Intelligence")
		);
	GameplayTags.Attribute_Primary_Resilience = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Resilience"),
		FString("Set Base Resilience")
		);
	GameplayTags.Attribute_Primary_Vigor = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Vigor"),
		FString("Set Base Vigor")
		);
	// Secondary Attributes Tags
	GameplayTags.Attribute_Secondary_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Armor"),
		FString("Set Base Armor")
		);
	GameplayTags.Attribute_Secondary_ArmorPenetration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.ArmorPenetration"),
		FString("Set Base Armor Penetration")
		);
	GameplayTags.Attribute_Secondary_BlockChance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.BlockChance"),
		FString("Set Base Block Chance")
		);
	GameplayTags.Attribute_Secondary_CriticalHitChance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.CriticalHitChance"),
		FString("Set Base Critical Hit Chance")
		);
	GameplayTags.Attribute_Secondary_CriticalHitDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.CriticalHitDamage"),
		FString("Set Base Critical Hit Damage")
		);
	GameplayTags.Attribute_Secondary_CriticalHitResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.CriticalHitResistance"),
		FString("Set Base Critical Hit Resistance")
		);
	GameplayTags.Attribute_Secondary_HealthRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.HealthRegeneration"),
		FString("Set Base Health Regeneration")
		);
	GameplayTags.Attribute_Secondary_ManaRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.ManaRegeneration"),
		FString("Set Base Mana Regeneration")
		);
	GameplayTags.Attribute_Secondary_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.MaxMana"),
		FString("Set Base Max Mana")
		);
	GameplayTags.Attribute_Secondary_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.MaxHealth"),
		FString("Set Base Max Health")
		);
	// Vital Attributes Tags
	GameplayTags.Attribute_Vital_Health = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attributes.Vital.Health"),
	FString("Set Base Health")
	);
	GameplayTags.Attribute_Vital_Mana = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Vital.Mana"),
		FString("Set Base Mana")
		);
	GameplayTags.Attribute_Vital_Speed = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Vital.Speed"),
		FString("Set Base Speed")
		);
	GameplayTags.Attribute_Vital_JumpHeight = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Vital.JumpHeight"),
		FString("Set Base Jump Height")
		);
	// Resistances Tags
	GameplayTags.Attribute_Resistance_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Resistance.Fire"),
		FString("Set Fire Resistance")
		);
	GameplayTags.Attribute_Resistance_Lightning = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Resistance.Lightning"),
		FString("Set Lightning Resistance")
		);
	// Meta
	GameplayTags.Attribute_Meta_IncomingXP = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Meta.IncomingXP"),
		FString("Set Incoming XP")
		);
	/** End Attribute Tags */

	/** Begin Effect Tags */
	GameplayTags.EffectTag_JumpBoost = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("EffectTag.JumpBoost"),
		FString("Effect tag for Jump Boost")
		);
	GameplayTags.EffectTag_VelocityBoost = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("EffectTag.VelocityBoost"),
		FString("Effect tag for Velocity Boost")
		);
	GameplayTags.EffectTag_Regeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("EffectTag.Regeneration"),
		FString("Effect tag for Regeneration")
		);
	/** End Effect Tags */

	/** Begin Abilities Tags*/
	GameplayTags.Abilities_Fire_Fireball = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Fire.Fireball"),
		FString("Abilities Fireball")
		);
	GameplayTags.Abilities_Dash = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Dash"),
		FString("Abilities Dash")
		);
	GameplayTags.Abilities_Pickup = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Pickup"),
		FString("Abilities Pickup")
		);
	GameplayTags.Abilities_Shockwave = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Shockwave"),
		FString("Abilities Shockwave")
		);
	/** End Abilities Tags */

	/** Begin Cooldown Tags */
	GameplayTags.CooldownTag_Dash = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("CooldownTag.Dash"),
		FString("Cooldown Dash")
		);
	GameplayTags.CooldownTag_Fireball = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("CooldownTag.Fireball"),
		FString("Cooldown Fireball")
		);
	GameplayTags.CooldownTag_Shockwave = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("CooldownTag.Shockwave"),
		FString("Cooldown Shockwave")
		);
	GameplayTags.CooldownTag_Heal = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("CooldownTag.Heal"),
		FString("Cooldown Heal")
		);
	/** End Cooldown Tags */

	/** Begin GameplayCue Tags */
	// Static Tags
	GameplayTags.GameplayCue_Ability_Spell_Cast = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("GameplayCue.Ability.Spell.Cast"),
		FString("Gameplay Cue for Spell Cast Ability")
		);
	GameplayTags.GameplayCue_Ability_Base = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("GameplayCue.Ability.Base"),
	FString("Gameplay Cue for Ability Base")
	);
	GameplayTags.GameplayCue_Effect_Health = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("GameplayCue.Effect.Health"),
		FString("Gameplay Cue for Health Effect")
		);
	GameplayTags.GameplayCue_Effect_Mana = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("GameplayCue.Effect.Mana"),
		FString("Gameplay Cue for Mana Effect")
		);
	// Loop Tags
	GameplayTags.GameplayCue_Ability_PickupLoop = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("GameplayCue.Ability.PickupLoop"),
		FString("Gameplay Cue for Ability Pickup Loop")
		);
	GameplayTags.GameplayCue_Ability_RegenerationLoop = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("GameplayCue.Ability.RegenerationLoop"),
		FString("Gameplay Cue for Ability Regeneration Loop")
		);
	GameplayTags.GameplayCue_Ability_ShockedLoop = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("GameplayCue.Ability.ShockedLoop"),
		FString("Gameplay Cue for Ability Shocked Loop")
		);
	GameplayTags.GameplayCue_Ability_HealLoop = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("GameplayCue.Ability.HealLoop"),
		FString("Gameplay Cue for Ability Heal Loop")
		);
	/** End GameplayCue Tags */

	/** Begin Event Tags */
	GameplayTags.GameplayEvent_Ability_Spell_Cast = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("GameplayEvent.Ability.Spell.Cast"),
		FString("Gameplay Event for Spell Cast Ability")
		);
	
	// Enemy Event Tags
	GameplayTags.Event_Enemy_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Event.Enemy.HitReact"),
		FString("Event Enemy Hit React")
		);
	/** End Event Tags */

	/** SetByCaller Tags */
	GameplayTags.SetByCaller_Ability_HealAmount = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("SetByCaller.Ability.HealAmount"),
		FString("Set By Caller Ability Heal Amount")
		);
	GameplayTags.SetByCaller_Attribute_IncomingXP = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("SetByCaller.Attribute.IncomingXP"),
		FString("Set By Caller Attribute Incoming XP")
		);
	/** End SetByCaller Tags */

	/** Begin Damage Tags */
	GameplayTags.Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage"),
		FString("Damage")
		);
	GameplayTags.Damage_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Fire"),
		FString("Damage Fire")
		);
	GameplayTags.Damage_Lightning = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Lightning"),
		FString("Damage Lightning")
		);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Fire, GameplayTags.Attribute_Resistance_Fire);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Lightning, GameplayTags.Attribute_Resistance_Lightning);
	/** End Damage Tags */

	/** Begin Buff Tags */
	GameplayTags.Buff = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Buff"),
		FString("Buff")
		);
	GameplayTags.Buff_Heal = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Buff.Heal"),
		FString("Buff Heal")
		);
	/** End Buff Tags */
	
	/** Begin Debuff Tags */
	GameplayTags.Debuff = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Debuff"),
		FString("Debuff")
		);
	GameplayTags.Debuff_Chance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Debuff.Chance"),
		FString("Debuff Chance")
		);
	GameplayTags.Debuff_Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Debuff.Damage"),
		FString("Debuff Damage")
		);
	GameplayTags.Debuff_Duration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Debuff.Duration"),
		FString("Debuff Duration")
		);
	GameplayTags.Debuff_Frequency = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Debuff.Frequency"),
		FString("Debuff Frequency")
		);
	
	// Debuff Types
	GameplayTags.Debuff_Burn = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Debuff.Burn"),
		FString("Debuff Burn")
		);
	GameplayTags.Debuff_Stun = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Debuff.Stun"),
		FString("Debuff Stun")
		);
	GameplayTags.DamageTypesToDebuffs.Add(GameplayTags.Damage_Fire,GameplayTags.Debuff_Burn);
	GameplayTags.DamageTypesToDebuffs.Add(GameplayTags.Damage_Lightning,GameplayTags.Debuff_Stun);
	/** End Debuff Tags */

	/**
	 *	Weapon Related Tags
	 */
	
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
