// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include "EResource.h"
#include "ResourceCost.h"
#include "UObject/NoExportTypes.h"
#include "All.generated.h"

/**
 * 
 */

UCLASS()
class TAUPROJECT_API UAll : public UObject
{
	GENERATED_BODY()
	

public:

	#pragma region Basic

	UPROPERTY()
		float Lumber;

	UPROPERTY()
		float Stone;
	UPROPERTY()
		float IronOre;
	UPROPERTY()
		float CopperOre;	
	UPROPERTY()
		float Wheat;
	UPROPERTY()
		float Coal;
	UPROPERTY()
		float Water;

	#pragma endregion
	
	#pragma region Advanced

	UPROPERTY()
		float Copper;
	UPROPERTY()
		float Iron;
	UPROPERTY()
		float Bread;
	UPROPERTY()
		float Alcohol;
	UPROPERTY()
		float Steel;
	UPROPERTY()
		float Planks;
	
	#pragma endregion

	#pragma region Elite

	UPROPERTY()
		float Peatanium;
	#pragma endregion

	#pragma region Equipment
	UPROPERTY()
		float IronSword;
	UPROPERTY()
		float SteelSword;
	UPROPERTY()
		float CopperSword;
	#pragma endregion

	
	float GetResourceCount(TEnumAsByte<EResources::All> resource);	

	void AffectResourceCounter(TEnumAsByte<EResources::All> resource, float amount, bool Add);

	bool CanAffordResourceList(TArray<UResourceCost*> list);
	bool CanAffordResourceItem(UResourceCost* cost);
	void AffectResouceListOnCounter(TArray<UResourceCost*> list, bool isAdd);

	TArray<FString> GetAllResourceNamesAsString();
	TEnumAsByte<EResources::All> GetResourceFromString(FString name);

	TEnumAsByte<EResourceTier::Tier> GetResourceTier(TEnumAsByte<EResources::All> resource, FString name = "");

};


