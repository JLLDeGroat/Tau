// Fill out your copyright notice in the Description page of Project Settings.

#include "UnitStructs.h"
#include "PlayerResource/ResourceCost.h"


UnitStructs::UnitStructs() {

}

#pragma region Statistics

float UnitStructs::GetInitialWalkingSpeed(TEnumAsByte<EUnitList::All> unit)
{
	switch (unit) {
	case EUnitList::UL_Sprout:
	case EUnitList::UL_Pea:
	case EUnitList::UL_Corn:
		return 200;

	default:
		return 200;
	}
}

float UnitStructs::GetInitialHitPoints(TEnumAsByte<EUnitList::All> unit) {
	switch (unit) {
	case EUnitList::UL_Sprout:
	case EUnitList::UL_Corn:
		return 80;

	case EUnitList::UL_Pea:
		return 150;


	default:
		return 120;
	}
}

float UnitStructs::GetInitialAttack(TEnumAsByte<EUnitList::All> unit) {
	switch (unit) {
	case EUnitList::UL_Sprout:
	case EUnitList::UL_Corn:
		return 3;

	case EUnitList::UL_Pea:
		return 7;


	default:
		return 3;
	}
}

float UnitStructs::GetInitialCritChange(TEnumAsByte<EUnitList::All> unit) {
	switch (unit) {
	case EUnitList::UL_Sprout:
	case EUnitList::UL_Corn:
		return 1;

	case EUnitList::UL_Pea:
		return 1;


	default:
		return 1;
	}
}

float UnitStructs::GetInitialCritMultiplier(TEnumAsByte<EUnitList::All> unit) {
	switch (unit) {
	case EUnitList::UL_Sprout:
	case EUnitList::UL_Corn:
		return 1;

	case EUnitList::UL_Pea:
		return 1.2;


	default:
		return 1;
	}
}

float UnitStructs::GetInitialSpawnTime(TEnumAsByte<EUnitList::All> unit) {
	switch (unit) {
	case EUnitList::UL_Sprout:
	case EUnitList::UL_Corn:
		return 5;

	case EUnitList::UL_Pea:
		return 7;


	default:
		return 10;
	}
}

float UnitStructs::GetInitialAttackRange(TEnumAsByte<EUnitList::All> unit) {
	switch (unit) {
	case EUnitList::UL_Sprout:
	case EUnitList::UL_Corn:
	case EUnitList::UL_Pea:
		return 240;


	default:
		return 140;
	}
}

float UnitStructs::GetInitialLineOfSight(TEnumAsByte<EUnitList::All> unit) {
	switch (unit) {
	case EUnitList::UL_Sprout:
	case EUnitList::UL_Corn:
	case EUnitList::UL_Pea:
		return 300;
	default:
		return 220;
	}
}

bool UnitStructs::GetIsArmedUnit(TEnumAsByte<EUnitList::All> unit) {
	switch (unit) {
	case EUnitList::UL_Pea:
		return true;

	default: 
		return false;
	}
}

#pragma endregion

#pragma region BuildCosts

TArray<UResourceCost*> UnitStructs::GetInitialBuildCostArray(TEnumAsByte<EUnitList::All> unit) {
	TArray<UResourceCost*> returnCosts;

	switch (unit) {
	case EUnitList::UL_Sprout:
		return returnCosts;
	case EUnitList::UL_Corn:
		return returnCosts;
	case EUnitList::UL_Pea:
		returnCosts.Add(NewObject<UResourceCost>()->Setup(EResources::R_Bread, 1));
		returnCosts.Add(NewObject<UResourceCost>()->Setup(EResources::R_Iron, 1));
		return returnCosts;

	default:
		return returnCosts;
	}

}

#pragma endregion