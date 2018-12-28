// Fill out your copyright notice in the Description page of Project Settings.

#include "UnitStructs.h"
#include "PlayerResource/ResourceCost.h"

#include "Units/Organic/Corn.h"
#include "Units/Organic/Pea.h"
#include "Units/Organic/Sprout.h"
#include "Units/Organic/MusketPea.h"

#include "Buildings/Organic/Barracks.h"
#include "Buildings/Organic/Storage.h"
#include "Buildings/Organic/SawMill.h"
#include "Buildings/Organic/Farm.h"
#include "Buildings/Organic/IronForge.h"
#include "Buildings/Organic/CopperForge.h"
#include "Buildings/Organic/OreRefinery.h"
#include "Buildings/Organic/MarketPlace.h"
#include "Buildings/Organic/Depletable/FarmField.h"
#include "Buildings/Organic/PhylosopherCave.h"
#include "Buildings/Organic/TownCenter.h"

#include "Buildings/Organic/Depletable/FarmField.h"

#include "Engine.h"

UnitStructs::UnitStructs() {

}

#pragma region Statistics

float UnitStructs::GetInitialWalkingSpeed(TEnumAsByte<EUnitList::All> unit)
{
	switch (unit) {
	case EUnitList::UL_Sprout:
	case EUnitList::UL_Pea:
	case EUnitList::UL_Corn:
	case EUnitList::UL_MusketPea:
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

	case EUnitList::UL_MusketPea:
		return 150;


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
	case EUnitList::UL_MusketPea:
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
	case EUnitList::UL_MusketPea:
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
	case EUnitList::UL_MusketPea:
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

	case EUnitList::UL_MusketPea:
		return 650;

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

	case EUnitList::UL_MusketPea:
		return 750;

	default:
		return 220;
	}
}

bool UnitStructs::SetIsUnitRanged(TEnumAsByte<EUnitList::All> unit) {
	switch (unit) {
	case EUnitList::UL_MusketPea:
		return true;

	default:
		return false;
	}
}

bool UnitStructs::GetIsArmedUnit(TEnumAsByte<EUnitList::All> unit) {
	switch (unit) {
	case EUnitList::UL_Pea:
	case EUnitList::UL_MusketPea:
		return true;

	
	default: 
		return false;
	}
}

FString UnitStructs::GetUnitDescription(TEnumAsByte<EUnitList::All> unit) {
	switch (unit) {
	case EUnitList::UL_Corn:
		return "Children of this particular corn are horrors not to unsuspected movie goers, but to the environment. These master destroyers will rip the earths innards out, display them, live in them and war with them";

	case EUnitList::UL_Pea:
		return "This expelling euthamism will blindly follow orders, unless its kids are taken from the pod, and will lay his life on the line to further the cause of peadom.";

	case EUnitList::UL_MusketPea:
		return "The musket pea stands his ground... until someone gets close, then proceeds to walk away";

	case EUnitList::UL_Sprout:
		return "Builder unit";

	default:
		return "unit Description";
	}
}

FString UnitStructs::GetUnitDisplayName(TEnumAsByte<EUnitList::All> unit) {
	switch (unit) {
	case EUnitList::UL_Corn:
		return "Corn";

	case EUnitList::UL_Pea:
	case EUnitList::UL_MusketPea:
		return "Pea";

	case EUnitList::UL_Sprout:
		return "Sprout";

	default:
		return "unit";
	}
}

#pragma endregion

AActor* UnitStructs::GetUnitClass(TEnumAsByte<EUnitList::All> unit) {
	switch (unit) {

	case EUnitList::UL_None:
		return nullptr;


	case EUnitList::UL_Corn:
		return NewObject<ACorn>();


	case EUnitList::UL_Pea:
		return NewObject<APea>();


	case EUnitList::UL_Sprout:
		return NewObject<ASprout>();

	case EUnitList::UL_MusketPea:
		return NewObject<AMusketPea>();


	default:
		return nullptr;
	}
}




TArray<AActor*> UnitStructs::SetUnitsBuildableBuildings(TEnumAsByte<EUnitList::All> unit) {
	TArray<AActor*> list;
	switch (unit) {
		case EUnitList::UL_Sprout:
			list.Add(NewObject<ABarracks>());
			list.Add(NewObject<AMarketPlace>());
			list.Add(NewObject<ASawMill>());
			list.Add(NewObject<APhylosopherCave>());
			list.Add(NewObject<ACopperForge>());
			list.Add(NewObject<AStorage>());
			break;

		case EUnitList::UL_Pea:
			list.Add(NewObject<ABarracks>());
			break;

	default:
		break;
	}
	return list;
}

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

	case EUnitList::UL_MusketPea:
		returnCosts.Add(NewObject<UResourceCost>()->Setup(EResources::R_Bread, 1));
		returnCosts.Add(NewObject<UResourceCost>()->Setup(EResources::R_Iron, 1));
		return returnCosts;

	default:
		return returnCosts;
	}

}

#pragma endregion



void UnitStructs::Debug(FString message) {
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, "UnitStructs.h: " + message);
}
