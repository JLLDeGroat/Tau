// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PlayerResource/ResourceCost.h"
#include "UnitStructs.generated.h"

UENUM(BlueprintType)
namespace EUnitOwnerships
{
	enum EUnitOwnerShip
	{
		UO_Player					UMETA(DisplayName = "Player"),
		UO_Neutral					UMETA(DisplayName = "Neutral"),
		UO_Enemy					UMETA(DisplayName = "Enemy")
	};
}

UENUM(BlueprintType)		//"BlueprintType" is essential to include
namespace EUnitStates
{
	enum EUnitState
	{
		US_Idle 					UMETA(DisplayName = "Idle"),
		US_Moving 					UMETA(DisplayName = "Moving"),
		US_Attacking				UMETA(DisplayName = "Attacking"),
		US_Building					UMETA(DisplayName = "Building"),
		US_Gathering				UMETA(DisplayName = "Gathering"),
		US_CMoving					UMETA(DisplayName = "CMoving"),
		US_CBuilding				UMETA(DisplayName = "CBuilding"),
		US_CAttacking				UMETA(DisplayName = "CAttacking"),
		US_CGathering				UMETA(DisplayName = "CGathering"),
		US_Fighting					UMETA(DisplayName = "Fighting")
	};
}

UENUM(BlueprintType)
namespace EUnitInstructions
{
	enum EUnitInstruction
	{
		UI_None						UMETA(DisplayName = "None"),
		UI_Construct				UMETA(DisplayName = "Constructing"),
		UI_Attack					UMETA(DisplayName = "Attack"),
		UI_Gather					UMETA(DisplayName = "Gather"),	
		UI_GatherBuilding			UMETA(DisplayName = "GatherBuilding"),
		UI_DropOff					UMETA(DisplayName = "DropOff"),
		UI_Multiple					UMETA(DisplayName = "Multiple"),
		UI_Move						UMETA(DisplayName = "Move")

	};
}

UENUM(BlueprintType)
namespace EUnitList
{
	enum All {
		UL_None						UMETA(DisplayName = "None"),
		UL_Corn						UMETA(DisplayName = "Corn"),
		UL_Pea						UMETA(DisplayName = "Pea"),
		UL_MusketPea				UMETA(DisplayName = "MusketPea"),
		UL_Sprout					UMETA(DisplayName = "Sprout")
	};
}

UENUM(BlueprintType)
namespace EUnitCombatType
{
	enum ArmamentType {
		AT_OneHanded				UMETA(DisplayName = "One Handed"),
		AT_Ranged					UMETA(DisplayName = "Ranged"),
		AT_TwoHanded				UMETA(DisplayName = "Two Handed"),
		AT_Civilian					UMETA(DisplayName = "Civilian")
	};
}


UENUM(BlueprintType)
namespace EUnitRightArm
{
	enum Armaments {
		RA_BasicSword				UMETA(DisplayName = "BasicSword"),
		RA_None						UMETA(DisplayName = "None")
	};
}

UENUM(BlueprintType)
namespace EUnitLeftArm
{
	enum Armaments {
		LA_Sheild					UMETA(DisplayName = "Shield"),
		LA_None						UMETA(DisplayName = "None")
	};
}

UENUM(BlueprintType)
namespace EUnitTwoHanded
{
	enum Armaments {
		TH_Polearm					UMETA(DisplayName = "Polearm"),
		TH_None						UMETA(DisplayName = "None")
	};
}


/**
*
*/
UCLASS()
class TAUPROJECT_API UnitStructs : public UObject
{
	GENERATED_BODY()
	UnitStructs();
public:


	static float GetInitialWalkingSpeed(TEnumAsByte<EUnitList::All> unit);

	static float GetInitialHitPoints(TEnumAsByte<EUnitList::All> unit);

	static float GetInitialAttack(TEnumAsByte<EUnitList::All> unit);

	static float GetInitialCritChange(TEnumAsByte<EUnitList::All> unit);

	static float GetInitialCritMultiplier(TEnumAsByte<EUnitList::All> unit);

	static float GetInitialSpawnTime(TEnumAsByte<EUnitList::All> unit);

	static float GetInitialAttackRange(TEnumAsByte<EUnitList::All> unit);

	static float GetInitialLineOfSight(TEnumAsByte<EUnitList::All> unit);

	static bool SetIsUnitRanged(TEnumAsByte<EUnitList::All> unit);

	static bool GetIsArmedUnit(TEnumAsByte<EUnitList::All> unit);

	static TArray<UResourceCost*> GetInitialBuildCostArray(TEnumAsByte<EUnitList::All> unit);

	static FString GetUnitDescription(TEnumAsByte<EUnitList::All> unit);

	static FString GetUnitDisplayName(TEnumAsByte<EUnitList::All> unit);

	static AActor* GetUnitClass(TEnumAsByte<EUnitList::All> unit);

	UFUNCTION(BlueprintCallable, category = "Hud Buttons")
		static TArray<AActor*> SetUnitsBuildableBuildings(TEnumAsByte<EUnitList::All> unit);

	static void Debug(FString message);

};
