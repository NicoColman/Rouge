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
	 * Attribute Tags
	 */
    FGameplayTag Attribute_Vital_Health;
    FGameplayTag Attribute_Vital_MaxHealth;

	/**
	 * Input Tags
	 */
    FGameplayTag InputTag_Weapon_Attack;
    FGameplayTag InputTag_RMB;
    FGameplayTag InputTag_Jump;
    FGameplayTag InputTag_Sprint;
	FGameplayTag InputTag_Equip;
	FGameplayTag InputTag_1;
	FGameplayTag InputTag_2;
    FGameplayTag InputTag_3;
    FGameplayTag InputTag_4;

	/** Begin Input Block Tags */
	FGameplayTag Player_Block_InputPressed;
	FGameplayTag Player_Block_InputReleased;
	FGameplayTag Player_Block_InputHeld;
	/** End Input Block Tags */
	
	/**
	 * Player State Tags 
	 */
    FGameplayTag StateTag_Player_Jumping;
    FGameplayTag StateTag_Player_Sprinting;
    FGameplayTag StateTag_Player_AbleEquip;

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

	/** Begin Montages Tags */
	FGameplayTag MontageTag_Melee_Attack;
	FGameplayTag MontageTag_Melee_AttackEnd;
	/** End Montages Tags */

	/** Begin Damage Tags */
	FGameplayTag Damage;
	/** End Damage Tags */

	/** Begin Effect Tags */
	FGameplayTag Effect_HitReact;
	/** End Effect Tags */

	// Enemy GameplayCue Tags
	FGameplayTag GameplayCue_Ability_Spell_Cast;
	/** End GameplayCue Tags */

	/** Begin Event Tags */
	// Player Event Tags
	
	// Enemy Event Tags
	FGameplayTag GameplayEvent_Ability_Spell_Cast;
	FGameplayTag Event_Enemy_HitReact;
	/** End Event Tags */
	
private:
    static FRougeGameplayTags GameplayTags;
};
