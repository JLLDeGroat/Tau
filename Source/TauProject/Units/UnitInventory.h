// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Units/UnitStructs.h"
#include "PlayerResource/EResource.h"
#include "UObject/NoExportTypes.h"
#include "UnitInventory.generated.h"

/**
 * 
 */
UCLASS()
class TAUPROJECT_API UUnitInventory : public UObject
{
	GENERATED_BODY()
	
public:


	UPROPERTY()
		float ResourceCount;

	UPROPERTY()
		float MaxResourceCount;

	UPROPERTY()
		TEnumAsByte<EResources::All> ResourceType;

	UPROPERTY()
		TEnumAsByte<EUnitRightArm::Armaments> RightArm;
	UPROPERTY()
		TEnumAsByte<EUnitLeftArm::Armaments> LeftArm;
	UPROPERTY()
		TEnumAsByte<EUnitTwoHanded::Armaments> TwoHanded;
	

	bool CanAddResourcetoCount(TEnumAsByte<EResources::All> resource, float amount);
	void AddToResourceCount(float count, TEnumAsByte<EResources::All> resource);

	bool IsRightResourceType(TEnumAsByte<EResources::All> resource);
	bool CanFitInInventory(float amount);

	bool IsInventoryFull();
	
	#pragma region Getters & Setters

	void SetCurrentResourceType(TEnumAsByte<EResources::All> resource);

	float GetCurrentResourceCount();
	float GetMaxResourceCount();
	TEnumAsByte<EResources::All> GetCurrentResourceType();
	#pragma endregion

	void EmptyInventory();
};
