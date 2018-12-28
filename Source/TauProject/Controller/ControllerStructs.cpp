// Fill out your copyright notice in the Description page of Project Settings.

#include "ControllerStructs.h"


UControllerStructs::UControllerStructs() {

}

AUnits* UControllerStructs::GetUnitForUIPopup(TEnumAsByte<EUnitList::All> unitType) {

	AUnits* unit = Cast<AUnits>(UnitStructs::GetUnitClass(unitType));

	unit->BuildCost = UnitStructs::GetInitialBuildCostArray(unitType);
	unit->Description = UnitStructs::GetUnitDescription(unitType);
	unit->DisplayName = UnitStructs::GetUnitDisplayName(unitType);
	

	return unit;
}

