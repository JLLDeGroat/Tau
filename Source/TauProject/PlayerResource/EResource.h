// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EResource.generated.h"

/**
 * 
 */
UCLASS()
class TAUPROJECT_API UEResource : public UObject
{
	GENERATED_BODY()
	
	
	
	
};


UENUM(BlueprintType)
namespace EResources
{
	enum All
	{
		R_None						UMETA(DisplayName = "None"),

		R_Lumber					UMETA(DisplayName = "Lumber"),
		R_Stone						UMETA(DisplayName = "Stone"),
		R_IronOre					UMETA(DisplayName = "IronOre"),
		R_Wheat						UMETA(DisplayName = "Wheat"),
		R_CopperOre					UMETA(DisplayName = "CopperOre"),
		R_Coal						UMETA(DisplayName = "Coal"),
		R_Water						UMETA(DisplayName = "Water"),
		R_Food						UMETA(DisplayName = "Food"),



		R_Copper					UMETA(DisplayName = "Copper"),
		R_Iron						UMETA(DisplayName = "Iron"),
		R_Bread						UMETA(DisplayName = "Bread"),
		R_Alcohol					UMETA(DisplayName = "Alcohol"),
		R_Steel						UMETA(DisplayName = "Steel"),
		R_Planks					UMETA(DisplayName = "Planks"),



		R_Peatanium					UMETA(DisplayName = "Peatanium"),



		E_IronSword					UMETA(DisplayName = "IronSword"),
		E_SteelSword				UMETA(DisplayName = "SteelSword"),
		E_CopperSword				UMETA(DisplayName = "CopperSword")
	};
}

UENUM(BlueprintType)
namespace EResourceTier
{
	enum Tier {
		T_1							UMETA(DisplayName = "Tier1"),
		T_2							UMETA(DisplayName = "Tier2"),
		T_3							UMETA(DisplayName = "Tier3"),
		T_4							UMETA(DisplayName = "Tier4"),
		T_5							UMETA(DisplayName = "Tier5")
	};
}