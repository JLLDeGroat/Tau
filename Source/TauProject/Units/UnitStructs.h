// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UnitStructs.generated.h"

/**
 * 
 */
UCLASS()
class TAUPROJECT_API UnitStructs : public UObject
{
	GENERATED_BODY()
public:



};	

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
		UL_Sprout					UMETA(DisplayName = "Sprout")
	};
}