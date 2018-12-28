// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Researcher.h"
#include "PlayerResource/ResourceCost.h"
#include "Units/Units.h"
#include "Converter.h"
#include "Engine.h"
#include "BuildingStructs.generated.h"
/**
 * 
 */

UENUM(BlueprintType)
namespace EBuildingOwnerships
{
	enum EBuildingOwnership
	{
		BO_Player					UMETA(DisplayName = "Player"),
		BO_Neutral					UMETA(DisplayName = "Neutral"),
		BO_Enemy					UMETA(DisplayName = "Enemy")
	};
}

UENUM(BlueprintType)
namespace EBuildStates
{
	enum EBuildingStates
	{
		BS_Spawning					UMETA(DisplayName = "Spawning"),
		BS_Placed					UMETA(DisplayName = "Placed"),
		BS_Constructing1			UMETA(DisplayName = "Constructing1"),
		BS_Constructing2			UMETA(DisplayName = "Constructing2"),
		BS_Constructing3			UMETA(DisplayName = "Constructing3"),
		BS_Complete					UMETA(DisplayName = "Complete"),
		BS_Damaged1					UMETA(DisplayName = "Damaged1"),
		BS_Damaged2					UMETA(DisplayName = "Damaged2"),
		BS_Damaged3					UMETA(DisplayName = "Damaged3"),
		BS_Destroyed				UMETA(DisplayName = "Destroyed"),
		BS_Depleted					UMETA(DisplayName = "Depleted")
	};
}

UENUM(BlueprintType)
namespace EAvailableBuildings
{
	enum  EAvailableBuildings
	{
		B_None						UMETA(DisplayName = "None"),
		B_Barracks					UMETA(DisplayName = "Barracks"),
		B_Storage					UMETA(DisplayName = "Storage"),
		B_SawMill					UMETA(DisplayName = "SawMill"),
		B_OreRefinery				UMETA(DisplayName = "OreRefinery"),
		B_SteelForge				UMETA(DisplayName = "SteelForge"),
		B_TownCenter				UMETA(DisplayName = "TownCenter"),
		B_CopperForge				UMETA(DisplayName = "CopperForge"),
		B_IronForge					UMETA(DisplayName = "IronForge"),
		B_MarketPlace				UMETA(DisplayName = "MarketPlace"),

		B_PhylosopherCave			UMETA(DisplayName = "PhylosophersCave"),

		B_FarmLand					UMETA(DisplayName = "FarmLand"),
		B_Farm						UMETA(DisplayName = "Farm")
	};
}

UCLASS()
class TAUPROJECT_API UBuildingStructs : public UObject
{
	GENERATED_BODY()
		UBuildingStructs();

public:

	static AActor* FindOrSpawnBuilding(TEnumAsByte<EAvailableBuildings::EAvailableBuildings> building, bool Find, UWorld* world);

	static FString SetBuildingName(TEnumAsByte<EAvailableBuildings::EAvailableBuildings> buildingType);

	static FString SetBuildingDescription(TEnumAsByte<EAvailableBuildings::EAvailableBuildings> buildingType);

	static float SetBuildingHealth(TEnumAsByte<EAvailableBuildings::EAvailableBuildings> buildingType);

	static TArray<UResourceCost*> SetBuildingResourceCost(TEnumAsByte<EAvailableBuildings::EAvailableBuildings> buildingType);

	static TArray<UResearcher*> SetBuildingResearchCost(TEnumAsByte<EAvailableBuildings::EAvailableBuildings> buildingType);

	UFUNCTION(BlueprintCallable, Category = "Building Helpers")
	static TArray<UResearcher*> SetBuildingsResearchableItems(TEnumAsByte<EAvailableBuildings::EAvailableBuildings> buildingType);

	UFUNCTION(BlueprintCallable, Category = "Building Helpers")
	static TArray<AUnits*> SetBuildingsSpawnableUnits(TEnumAsByte<EAvailableBuildings::EAvailableBuildings> buildingType);

	UFUNCTION(BlueprintCallable, Category = "Building Helpers")
	static TArray<AActor*> SetBuildingsBuildableBuildings(TEnumAsByte<EAvailableBuildings::EAvailableBuildings> buildingType);

	static TArray<FString> SetBuildingsBuildingNeededList(TEnumAsByte<EAvailableBuildings::EAvailableBuildings> buildingType);

	static UConverter* SetConversionIfConverterBuilding(TEnumAsByte<EAvailableBuildings::EAvailableBuildings> buildingType);

	static bool SetIsConverterBuilding(TEnumAsByte<EAvailableBuildings::EAvailableBuildings> buildingType);

	static bool SetIsResearcherBuilding(TEnumAsByte<EAvailableBuildings::EAvailableBuildings> buildingType);

	static bool SetBuildingCanStore(TEnumAsByte<EAvailableBuildings::EAvailableBuildings> buildingType);


	static void Debug(FString message);
};
