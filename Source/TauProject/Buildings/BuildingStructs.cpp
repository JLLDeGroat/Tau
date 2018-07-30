// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingStructs.h"
#include "PlayerResource/ResourceCost.h"
#include "Utils/ResearchLibrary.h"



UBuildingStructs::UBuildingStructs() {

}



FString UBuildingStructs::SetBuildingName(TEnumAsByte<EAvailableBuildings::EAvailableBuildings> buildingType) {
	switch (buildingType) {
	case EAvailableBuildings::B_Barracks:
		return "Barracks";

	case EAvailableBuildings::B_CopperForge:
		return "Copper Forge";

	case EAvailableBuildings::B_Farm:
		return "Windmill";

	case EAvailableBuildings::B_FarmLand:
		return "Farm Land";

	case EAvailableBuildings::B_IronForge:
		return "Iron Forge";

	case EAvailableBuildings::B_MarketPlace:
		return "MarketPlace";

	case EAvailableBuildings::B_OreRefinery:
		return "Ore Refinery";

	case EAvailableBuildings::B_PhylosopherCave:
		return "Think Tank";

	case EAvailableBuildings::B_SawMill:
		return "Saw Mill";

	case EAvailableBuildings::B_SteelForge:
		return "Steel Forge";

	case EAvailableBuildings::B_Storage:
		return "Storage";

	case EAvailableBuildings::B_TownCenter:
		return "Town Center";

	default:
		return "Undefined Building";
	}
}

FString UBuildingStructs::SetBuildingDescription(TEnumAsByte<EAvailableBuildings::EAvailableBuildings> buildingType) {
	switch (buildingType) {
	case EAvailableBuildings::B_Barracks:
		return "Basic millitary units can be trained (to minimal skill) units can come in a variety of arms and can not be equipped with advanced millitary gear created in the armory.";
	case EAvailableBuildings::B_CopperForge:
		return "Manipulate heat to forge copper ingots from ore.";
	case EAvailableBuildings::B_SteelForge:
		return "Manipulate heat to forge Steel ingots from iron ore & coal.";
	case EAvailableBuildings::B_MarketPlace:
		return "Peas will trade there arm n legs here for resources and arms and legs.";
	case EAvailableBuildings::B_IronForge:
		return "The heat is intense, many a pea could not stand the heat in this particular kitchen.";
	case EAvailableBuildings::B_OreRefinery:
		return "Research more effecient ways of craking, smelting and reducing slag from ores you get around the world.";
	case EAvailableBuildings::B_PhylosopherCave:
		return "The peas come together, and think through the needs and wants that will bring the peas into the future.";
	case EAvailableBuildings::B_SawMill:
		return "Cut Sturdy wood into sturdier wood because it looks better.";
	case EAvailableBuildings::B_Farm:
		return "The humble wind powered mill, is the source of your farmlands and can be used in the same was as a storage building but more costly.";
	case EAvailableBuildings::B_FarmLand:
		return "Create farms to harvest wheat, the only resource peas know (for some reason) and use it to create food";
	case EAvailableBuildings::B_Storage:
		return "Harvesting units can drop resources off at this location and will add to your vegville, pro tip: put near resources...";
	case EAvailableBuildings::B_TownCenter:
		return "the town :D";

	default:
		return "non descript";
	}
}

float UBuildingStructs::SetBuildingHealth(TEnumAsByte<EAvailableBuildings::EAvailableBuildings> buildingType) {
	switch (buildingType) {
	case EAvailableBuildings::B_Barracks:
	case EAvailableBuildings::B_CopperForge:
	case EAvailableBuildings::B_SteelForge:
	case EAvailableBuildings::B_MarketPlace:
	case EAvailableBuildings::B_IronForge:
	case EAvailableBuildings::B_OreRefinery:
	case EAvailableBuildings::B_PhylosopherCave:
	case EAvailableBuildings::B_SawMill:
		return 500;
		

	case EAvailableBuildings::B_Farm:
	case EAvailableBuildings::B_FarmLand:
	case EAvailableBuildings::B_Storage :
		return 350;	
	

	case EAvailableBuildings::B_TownCenter:
		return 1200;


	default:
		return 500;
	}
}

TArray<UResourceCost*> UBuildingStructs::SetBuildingResourceCost(TEnumAsByte<EAvailableBuildings::EAvailableBuildings> buildingType) {
	TArray<UResourceCost*> costList;

	switch (buildingType) {
	case EAvailableBuildings::B_Barracks:
		costList.Add(NewObject<UResourceCost>()->Setup(EResources::R_Stone, 10));
		costList.Add(NewObject<UResourceCost>()->Setup(EResources::R_Iron, 5));
		costList.Add(NewObject<UResourceCost>()->Setup(EResources::R_Copper, 5));
		break;

	case EAvailableBuildings::B_CopperForge:
		costList.Add(NewObject<UResourceCost>()->Setup(EResources::R_Planks, 10));
		costList.Add(NewObject<UResourceCost>()->Setup(EResources::R_CopperOre, 5));
		break;

	case EAvailableBuildings::B_Farm:
		costList.Add(NewObject<UResourceCost>()->Setup(EResources::R_Lumber, 4));
		costList.Add(NewObject<UResourceCost>()->Setup(EResources::R_Stone, 2));
		break;

	case EAvailableBuildings::B_FarmLand:
		costList.Add(NewObject<UResourceCost>()->Setup(EResources::R_Lumber, 5));
		break;

	case EAvailableBuildings::B_IronForge:
		costList.Add(NewObject<UResourceCost>()->Setup(EResources::R_Planks, 10));
		costList.Add(NewObject<UResourceCost>()->Setup(EResources::R_Copper, 5));
		costList.Add(NewObject<UResourceCost>()->Setup(EResources::R_IronOre, 5));
		break;

	case EAvailableBuildings::B_MarketPlace:
		costList.Add(NewObject<UResourceCost>()->Setup(EResources::R_Planks, 15));
		costList.Add(NewObject<UResourceCost>()->Setup(EResources::R_Stone, 15));
		break;

	case EAvailableBuildings::B_OreRefinery:
		break;

	case EAvailableBuildings::B_PhylosopherCave:
		costList.Add(NewObject<UResourceCost>()->Setup(EResources::R_Stone, 10));
		costList.Add(NewObject<UResourceCost>()->Setup(EResources::R_Planks, 15));
		break;

	case EAvailableBuildings::B_SawMill:
		costList.Add(NewObject<UResourceCost>()->Setup(EResources::R_Lumber, 15));
		break;

	case EAvailableBuildings::B_SteelForge:
		break;

	case EAvailableBuildings::B_Storage:
		costList.Add(NewObject<UResourceCost>()->Setup(EResources::R_Lumber, 4));
		costList.Add(NewObject<UResourceCost>()->Setup(EResources::R_Stone, 2));
		break;

	case EAvailableBuildings::B_TownCenter:
		break;

	default:
		costList.Add(NewObject<UResourceCost>()->Setup(EResources::All::R_Planks, 10));
		costList.Add(NewObject<UResourceCost>()->Setup(EResources::All::R_Stone, 10));
	}

	return costList;
}

TArray<UResearcher*> UBuildingStructs::SetBuildingResearchCost(TEnumAsByte<EAvailableBuildings::EAvailableBuildings> buildingType) {
	TArray<UResearcher*> resList;

	TArray<UResearcher*> allResearch = UResearchLibrary::ResearchList();

	switch (buildingType) {

	case EAvailableBuildings::B_CopperForge:	
		resList.Add(UResearchLibrary::GetResearch(EResearchList::R_CopperForge));
		break;

			
	case EAvailableBuildings::B_IronForge:	
		resList.Add(UResearchLibrary::GetResearch(EResearchList::R_IronForge));
		break;

	
	case EAvailableBuildings::B_OreRefinery:
		resList.Add(UResearchLibrary::GetResearch(EResearchList::R_OreRefinery));
		break;
		

	case EAvailableBuildings::B_SteelForge:
		break;


	case EAvailableBuildings::B_TownCenter:
		break;
		
	default:
		break;
	}
	return resList;
}

TArray<UResearcher*> UBuildingStructs::SetBuildingsResearchableItems(TEnumAsByte<EAvailableBuildings::EAvailableBuildings> buildingType) {
	TArray<UResearcher*> resList;
	resList = UResearchLibrary::ResearchList();

	switch (buildingType) {

	case EAvailableBuildings::B_PhylosopherCave:
		resList.Add(UResearchLibrary::GetResearch(EResearchList::R_Harveting));
		resList.Add(UResearchLibrary::GetResearch(EResearchList::R_IronForge));
		resList.Add(UResearchLibrary::GetResearch(EResearchList::R_CopperForge));
		break;

	case EAvailableBuildings::B_OreRefinery:
		resList.Add(UResearchLibrary::GetResearch(EResearchList::R_Harveting));
		break;

	default:
		break;
	}

	return resList;
}

TArray<FString> UBuildingStructs::SetBuildingsBuildingNeededList(TEnumAsByte<EAvailableBuildings::EAvailableBuildings> buildingType) {
	TArray<FString> buildingNameArray;
	switch (buildingType) {

	
	case EAvailableBuildings::B_FarmLand:
		buildingNameArray.Add(SetBuildingName(EAvailableBuildings::B_Farm));
		break;

	
	case EAvailableBuildings::B_PhylosopherCave:
		buildingNameArray.Add(SetBuildingName(EAvailableBuildings::B_Barracks));
		buildingNameArray.Add(SetBuildingName(EAvailableBuildings::B_MarketPlace));
		break;


	default:
		break;

	
	}
	return buildingNameArray;
}

UConverter* UBuildingStructs::SetConversionIfConverterBuilding(TEnumAsByte<EAvailableBuildings::EAvailableBuildings> buildingType) {
	UConverter* conversionObject = NewObject<UConverter>();
	TArray<UResourceCost*> conversionCost;
	TArray<UResourceCost*> conversionReward;

	switch (buildingType) {

	case EAvailableBuildings::B_CopperForge:
		conversionCost.Add(NewObject<UResourceCost>()->Setup(EResources::R_CopperOre, 1));
		conversionReward.Add(NewObject<UResourceCost>()->Setup(EResources::R_Copper, 1));
		conversionObject->SetConverterFromItem(conversionCost);
		conversionObject->SetConverterToItem(conversionReward);
		conversionObject->SetConversionRate(20);
		break;


	case EAvailableBuildings::B_IronForge:
		conversionCost.Add(NewObject<UResourceCost>()->Setup(EResources::R_IronOre, 1));
		conversionReward.Add(NewObject<UResourceCost>()->Setup(EResources::R_Iron, 1));
		conversionObject->SetConverterFromItem(conversionCost);
		conversionObject->SetConverterToItem(conversionReward);
		conversionObject->SetConversionRate(30);
		break;

	
	case EAvailableBuildings::B_SawMill:
		conversionCost.Add(NewObject<UResourceCost>()->Setup(EResources::R_Lumber, 1));
		conversionReward.Add(NewObject<UResourceCost>()->Setup(EResources::R_Planks, 1));		
		conversionObject->SetConverterFromItem(conversionCost);
		conversionObject->SetConverterToItem(conversionReward);
		conversionObject->SetConversionRate(20);
		break;	


	case EAvailableBuildings::B_SteelForge:
		conversionCost.Add(NewObject<UResourceCost>()->Setup(EResources::R_Coal, 2));
		conversionCost.Add(NewObject<UResourceCost>()->Setup(EResources::R_Iron, 1));
		conversionReward.Add(NewObject<UResourceCost>()->Setup(EResources::R_Steel, 1));
		conversionObject->SetConverterFromItem(conversionCost);
		conversionObject->SetConverterToItem(conversionReward);
		conversionObject->SetConversionRate(40);
		break;


	
	default:
		return nullptr;
	}

	return conversionObject;
}

bool UBuildingStructs::SetIsConverterBuilding(TEnumAsByte<EAvailableBuildings::EAvailableBuildings> buildingType) {
	switch (buildingType) {

	case EAvailableBuildings::B_SawMill:
	case EAvailableBuildings::B_CopperForge:
	case EAvailableBuildings::B_IronForge:
	case EAvailableBuildings::B_SteelForge:
		return true;

	default:
		return false;
	}
}

bool UBuildingStructs::SetIsResearcherBuilding(TEnumAsByte<EAvailableBuildings::EAvailableBuildings> buildingType) {
	switch (buildingType) {

	case EAvailableBuildings::B_OreRefinery:
	case EAvailableBuildings::B_PhylosopherCave:
		return true;


	default:
		return false;
	}
}

bool UBuildingStructs::SetBuildingCanStore(TEnumAsByte<EAvailableBuildings::EAvailableBuildings> buildingType) {
	switch (buildingType) {

	case EAvailableBuildings::B_Storage:
	case EAvailableBuildings::B_Farm:
	case EAvailableBuildings::B_TownCenter:
		return true;



	default:
		return false;
	}
}