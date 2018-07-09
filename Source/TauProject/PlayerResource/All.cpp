// Fill out your copyright notice in the Description page of Project Settings.

#include "All.h"
#include "EResource.h"
#include "ResourceCost.h"



float UAll::GetResourceCount(TEnumAsByte<EResources::All> resource) {
	switch (resource) {

	case EResources::R_IronOre:
		return IronOre;

	case EResources::R_CopperOre:
		return CopperOre;

	case EResources::R_Stone:
		return Stone;

	case EResources::R_Lumber:
		return Lumber;

	case EResources::R_Wheat:
		return Wheat;

	case EResources::R_Coal:
		return Coal;

	case EResources::R_Water:
		return Water;

		//advance

	case EResources::R_Copper:
		return Copper;

	case EResources::R_Iron:
		return Iron;

	case EResources::R_Alcohol:
		return Alcohol;

	case EResources::R_Bread:
		return Bread;

	case EResources::R_Steel:
		return Steel;

	case EResources::R_Planks:
		return Planks;

	//elite

	case EResources::R_Peatanium:
		return Peatanium;

	//equip

	case EResources::E_IronSword:
		return IronSword;

	case EResources::E_CopperSword:
		return CopperSword;

	case EResources::E_SteelSword:
		return SteelSword;
	}
	return -1;
}

void UAll::AffectResourceCounter(TEnumAsByte<EResources::All> resource, float amount, bool Add)
{
	switch (resource) {

	case EResources::R_IronOre:
		if (Add) IronOre += amount;
		else IronOre -= amount;

		break;
	case EResources::R_CopperOre:
		if (Add) CopperOre += amount;
		else CopperOre -= amount;
		break;

	case EResources::R_Stone:
		if (Add) Stone += amount;
		else Stone -= amount;
		break;

	case EResources::R_Lumber:
		if (Add) Lumber += amount;
		else Lumber -= amount;
		break;

	case EResources::R_Wheat:
		if (Add) Wheat += amount;
		else Wheat -= amount;
		break;

	case EResources::R_Coal:
		if (Add) Coal += amount;
		else Coal -= amount;
		break;

	case EResources::R_Water:
		if (Add) Water += amount;
		else Water -= amount;
		break;

		//advance

	case EResources::R_Copper:
		if (Add) Copper += amount;
		else Copper -= amount;
		break;

	case EResources::R_Iron:
		if (Add) Iron += amount;
		else Iron -= amount;
		break;
		
	case EResources::R_Alcohol:
		if (Add) Alcohol += amount;
		else Alcohol -= amount;
		break;

	case EResources::R_Bread:
		if (Add) Bread += amount;
		else Bread -= amount;
		break;

	case EResources::R_Steel:
		if (Add) Steel += amount;
		else Steel -= amount;
		break;

	case EResources::R_Planks:
		if (Add) Planks += amount;
		else Planks -= amount;
		return;

		//elite

	case EResources::R_Peatanium:
		if (Add) Peatanium += amount;
		else Peatanium -= amount;
		break;

		//equip

	case EResources::E_IronSword:
		if (Add) IronSword += amount;
		else IronSword -= amount;
		break;

	case EResources::E_CopperSword:
		if (Add) CopperSword += amount;
		else CopperSword -= amount;
		break;

	case EResources::E_SteelSword:
		if (Add) SteelSword += amount;
		else SteelSword -= amount;
		break;

	}
}

bool UAll::CanAffordResourceList(TArray<UResourceCost*> list) {
	for (int32 i = 0; i < list.Num(); i++) {
		float res = GetResourceCount(list[i]->res);
		if (GetResourceCount(list[i]->res) < list[i]->Amount) {
			return false;
		}
	}
	return true;
}

bool UAll::CanAffordResourceItem(UResourceCost* cost) {
	return GetResourceCount(cost->res) >= cost->Amount;
}

void UAll::AffectResouceListOnCounter(TArray<UResourceCost*> list, bool isAdd) {
	for (int32 i = 0; i < list.Num(); i++) {
		AffectResourceCounter(list[i]->res, list[i]->Amount, isAdd);
	}
}

TArray<FString> UAll::GetAllResourceNamesAsString() {
	TArray<FString> resourceList;
	resourceList.Add("Lumber");
	resourceList.Add("Stone");
	resourceList.Add("IronOre");
	resourceList.Add("CopperOre");
	resourceList.Add("Coal");
	resourceList.Add("Planks");
	resourceList.Add("Water");
	resourceList.Add("Bread");
	resourceList.Add("Food");
	resourceList.Add("Iron");
	resourceList.Add("Copper");
	resourceList.Add("Steel");	
	resourceList.Add("Peatanium");
	resourceList.Add("Alcohol");
	resourceList.Sort();
	return resourceList;
}

TEnumAsByte<EResources::All> UAll::GetResourceFromString(FString name) {
	
	if (name == "Lumber") return EResources::R_Lumber;
	else if (name == "Stone") return EResources::R_Stone;
	else if (name == "IronOre") return EResources::R_IronOre;
	else if (name == "CopperOre") return EResources::R_CopperOre;
	else if (name == "Coal") return EResources::R_Coal;
	else if (name == "Planks") return EResources::R_Planks;
	else if (name == "Water") return EResources::R_Water;
	else if (name == "Wheat") return EResources::R_Wheat;
	else if (name == "Bread") return EResources::R_Bread;
	else if (name == "Food") return EResources::R_Food;
	else if (name == "Iron") return EResources::R_Iron;
	else if (name == "Copper") return EResources::R_Copper;
	else if (name == "Steel") return EResources::R_Steel;
	else if (name == "Peatanium") return EResources::R_Peatanium;
	else if (name == "Alcohol") return EResources::R_Alcohol;
	

	else return EResources::R_None;


}

TEnumAsByte<EResourceTier::Tier> UAll::GetResourceTier(TEnumAsByte<EResources::All> resource, FString name) {
	if (name != "") {
		resource = GetResourceFromString(name);
	}


	switch (resource) {
	case EResources::R_IronOre:
		return EResourceTier::T_1;
	
	case EResources::R_CopperOre:
		return EResourceTier::T_1;

	case EResources::R_Stone:
		return EResourceTier::T_1;

	case EResources::R_Lumber:
		return EResourceTier::T_1;

	case EResources::R_Wheat:
		return EResourceTier::T_1;

	case EResources::R_Coal:
		return EResourceTier::T_1;

	case EResources::R_Water:
		return EResourceTier::T_1;

		
		//advance

	case EResources::R_Copper:
		return EResourceTier::T_2;

	case EResources::R_Iron:
		return EResourceTier::T_2;

	case EResources::R_Alcohol:
		return EResourceTier::T_2;

	case EResources::R_Bread:
		return EResourceTier::T_2;

	case EResources::R_Steel:
		return EResourceTier::T_2;

	case EResources::R_Planks:
		return EResourceTier::T_2;

		//elite

	case EResources::R_Peatanium:
		return EResourceTier::T_5;

		//equip

	case EResources::E_IronSword:
		return EResourceTier::T_4;

	case EResources::E_CopperSword:
		return EResourceTier::T_4;

	case EResources::E_SteelSword:
		return EResourceTier::T_4;


	default:
		return EResourceTier::T_1;
	}


}