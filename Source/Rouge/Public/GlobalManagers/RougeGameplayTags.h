// Zombies

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * 
 */

struct FRougeGameplayTags
{
public:
    static const FRougeGameplayTags& Get() {
        return GameplayTags;
    }

    static void InitializeNativeGameplayTags();
	static FGameplayTag GetMatchTagFromASC(class UAbilitySystemComponent* ASC, const FName& RequestedTag);

	/**
	 *	Input Related Tags
	 */
	
	/** Begin Input Tags */
	FGameplayTag InputTag_Weapon_Attack;
	FGameplayTag InputTag_RMB;
	FGameplayTag InputTag_Jump;
	FGameplayTag InputTag_Sprint;
	FGameplayTag InputTag_Dash;
	FGameplayTag InputTag_Equip;
	FGameplayTag InputTag_1;
	FGameplayTag InputTag_2;
	FGameplayTag InputTag_3;
	FGameplayTag InputTag_4;
	/** End Input Tags */

	/** Begin Input Block Tags */
	FGameplayTag Player_Block_InputPressed;
	FGameplayTag Player_Block_InputReleased;
	FGameplayTag Player_Block_InputHeld;
	/** End Input Block Tags */

	
	/**
	 *	Player Related Tags
	 */
	
	/** Begin State Tags */
	// Character State Tags
	FGameplayTag StateTag_Character_Shocked;
	// Player State Tags
	FGameplayTag StateTag_Player_Jumping;
	FGameplayTag StateTag_Player_Sprinting;
	FGameplayTag StateTag_Player_AbleEquip;
	FGameplayTag StateTag_Player_Dashing;
	FGameplayTag StateTag_Player_Healing;
	/** End State Tags */

	
	/**
	 *	GAS Related Tags
	 */
	
	/** Begin Attribute Tags */
	FGameplayTag Attribute_Primary_Strength;
	FGameplayTag Attribute_Primary_Intelligence;
	FGameplayTag Attribute_Primary_Resilience;
	FGameplayTag Attribute_Primary_Vigor;
	// Secondary Attributes Tags
	FGameplayTag Attribute_Secondary_Armor;
	FGameplayTag Attribute_Secondary_ArmorPenetration;
	FGameplayTag Attribute_Secondary_BlockChance;
	FGameplayTag Attribute_Secondary_CriticalHitChance;
	FGameplayTag Attribute_Secondary_CriticalHitDamage;
	FGameplayTag Attribute_Secondary_CriticalHitResistance;
	FGameplayTag Attribute_Secondary_HealthRegeneration;
	FGameplayTag Attribute_Secondary_ManaRegeneration;
	FGameplayTag Attribute_Secondary_MaxMana;
	FGameplayTag Attribute_Secondary_MaxHealth;
	// Vital Attributes Tags
    FGameplayTag Attribute_Vital_Health;
	FGameplayTag Attribute_Vital_Mana;
	FGameplayTag Attribute_Vital_Speed;
	FGameplayTag Attribute_Vital_JumpHeight;
	// Resistances Tags
	FGameplayTag Attribute_Resistance_Fire;
	FGameplayTag Attribute_Resistance_Lightning;

	//Meta
	FGameplayTag Attribute_Meta_IncomingXP;
	/** End Attribute Tags */
	
	/** Begin Effect Tags */
	FGameplayTag EffectTag_JumpBoost;
	FGameplayTag EffectTag_VelocityBoost;
	FGameplayTag EffectTag_Regeneration;
	/** End Effect Tags */
	
	/** Begin Abilities Tags*/
	FGameplayTag Abilities_Fire_Fireball;
	FGameplayTag Abilities_Dash;
	FGameplayTag Abilities_Pickup;
	FGameplayTag Abilities_Shockwave;
	/** End Abilities Tags */

	/** Begin Cooldown Tags */
	FGameplayTag CooldownTag_Dash;
	FGameplayTag CooldownTag_Fireball;
	FGameplayTag CooldownTag_Shockwave;
	FGameplayTag CooldownTag_Heal;
	/** End Cooldown Tags */

	/** Begin GameplayCue Tags */
	// Static Tags
	FGameplayTag GameplayCue_Ability_Spell_Cast;
	FGameplayTag GameplayCue_Ability_Base;
	FGameplayTag GameplayCue_Effect_Health;
	FGameplayTag GameplayCue_Effect_Mana;
	// Loop Tags
	FGameplayTag GameplayCue_Ability_PickupLoop;
	FGameplayTag GameplayCue_Ability_RegenerationLoop;
	FGameplayTag GameplayCue_Ability_ShockedLoop;
	FGameplayTag GameplayCue_Ability_HealLoop;
	/** End GameplayCue Tags */

	/** Begin Event Tags */
	// Enemy Event Tags
	FGameplayTag GameplayEvent_Ability_Spell_Cast;
	FGameplayTag Event_Enemy_HitReact;
	/** End Event Tags */

	/** SetByCaller Tags */
	FGameplayTag SetByCaller_Ability_HealAmount;
	FGameplayTag SetByCaller_Attribute_IncomingXP;
	/** End SetByCaller Tags */

	/** Begin Damage Tags */
	FGameplayTag Damage;
	FGameplayTag Damage_Fire;
	FGameplayTag Damage_Lightning;
	TMap<FGameplayTag, FGameplayTag> DamageTypesToResistances;
	/** End Damage Tags */

	/** Begin Buff Tags */
	FGameplayTag Buff;
	FGameplayTag Buff_Heal;
	/** End Buff Tags */
	
	/** Begin Debuff Tags */
	FGameplayTag Debuff;
	FGameplayTag Debuff_Burn;
	FGameplayTag Debuff_Stun;

	FGameplayTag Debuff_Chance;
	FGameplayTag Debuff_Damage;
	FGameplayTag Debuff_Duration;
	FGameplayTag Debuff_Frequency;
	
	TMap<FGameplayTag, FGameplayTag> DamageTypesToDebuffs;
	/** End Debuff Tags */

	
	/**
	 *	Weapon Related Tags
	 */

    /** Begin WeaponType Tags*/
	FGameplayTag WeaponType;
	FGameplayTag WeaponType_Proxy;

	// Staffs
	FGameplayTag WeaponType_Staff;
	FGameplayTag WeaponType_Staff_Blue;
	FGameplayTag WeaponType_Staff_Red;
	FGameplayTag WeaponType_Staff_Green;
	FGameplayTag WeaponType_Staff_Yellow;
	FGameplayTag WeaponType_Staff_Purple;
	FGameplayTag WeaponType_Staff_White;
	FGameplayTag WeaponType_Staff_Combined;
	
	// Melee Weapons
	FGameplayTag WeaponType_Melee;
	/** End WeaponType Tags*/
	
private:
    static FRougeGameplayTags GameplayTags;
};
