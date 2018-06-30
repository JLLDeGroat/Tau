// Fill out your copyright notice in the Description page of Project Settings.

#include "ResourceCost.h"



UResourceCost::UResourceCost() {

}


UResourceCost* UResourceCost::Setup(TEnumAsByte<EResources::All> r, float a) {
	this->res = r;
	this->Amount = a;
	return this;
}


float UResourceCost::GetAmount() {
	return Amount;
}

FString UResourceCost::GetResourceType() {
	switch (this->res) 
	{
		case EResources::E_CopperSword:
			return "Copper Sword";
		case EResources::E_IronSword:
			return "Iron Sword";
		case EResources::E_SteelSword:
			return "Steel Sword";
		case EResources::R_Alcohol:
			return "Alcohol";
		case EResources::R_Bread:
			return "Bread";
		case EResources::R_Coal:
			return "Coal";
		case EResources::R_Copper:
			return "Copper";
		case EResources::R_CopperOre:
			return "Copper Ore";
		case EResources::R_Food:
			return "Food";
		case EResources::R_Iron:
			return "Iron";
		case EResources::R_IronOre:
			return "Iron Ore";
		case EResources::R_Lumber:
			return "Lumber";
		case EResources::R_Peatanium:
			return "Peatanium";
		case EResources::R_Planks:
			return "Planks";
		case EResources::R_Steel:
			return "Steel";
		case EResources::R_Stone:
			return "Stone";
		case EResources::R_Water:
			return "Water";
		case EResources::R_Wheat:
			return "What";
		case EResources::R_None:
			return "None";
			

		default:
			return "Resource";
	}
}