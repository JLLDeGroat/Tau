// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Units/Units.h"
#include "Units/UnitStructs.h"
#include "UObject/NoExportTypes.h"
#include "ControllerStructs.generated.h"

/**
 * 
 */
UCLASS()
class TAUPROJECT_API UControllerStructs : public UObject
{
	GENERATED_BODY()
		UControllerStructs();
public:

	UFUNCTION(BlueprintCallable)
		static AUnits* GetUnitForUIPopup(TEnumAsByte<EUnitList::All> unitType);



};

