// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
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
	};
}

UENUM(BlueprintType)
namespace EAvailableBuildings
{
	enum  EAvailableBuildings
	{
		B_None						UMETA(DisplayName = "None"),
		B_Barracks					UMETA(DisplayName = "Barracks")
	};
}

UCLASS()
class TAUPROJECT_API UBuildingStructs : public UObject
{
	GENERATED_BODY()

public:


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameState)
		TEnumAsByte<EBuildStates::EBuildingStates> BuildingStates;

};
