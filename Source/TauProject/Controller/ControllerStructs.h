// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ControllerStructs.generated.h"

/**
 * 
 */
UCLASS()
class TAUPROJECT_API UControllerStructs : public UObject
{
	GENERATED_BODY()
};

UENUM(BlueprintType)
namespace EWidgets
{
	enum EWidgetToShow
	{
		W_Selection					UMETA(DisplayName = "Selection"),
		W_Barracks					UMETA(DisplayName = "Barracks"),
		W_Details					UMETA(DisplayName = "Details"),
		W_None						UMETA(DisplayName = "None")
	};
}