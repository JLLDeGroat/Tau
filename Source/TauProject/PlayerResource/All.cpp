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

void UAll::AffectResouceListOnCounter(TArray<UResourceCost*> list, bool isAdd) {
	for (int32 i = 0; i < list.Num(); i++) {
		AffectResourceCounter(list[i]->res, list[i]->Amount, isAdd);
	}
}