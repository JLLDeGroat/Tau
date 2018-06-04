// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Units\UnitStructs.h"
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
		TEnumAsByte<EUnitInventory::Resource> ResourceType;
	

	bool CanAddResourcetoCount(TEnumAsByte<EUnitInventory::Resource> resource, float amount);
	void AddToResourceCount(float count, TEnumAsByte<EUnitInventory::Resource> resource);

	bool IsRightResourceType(TEnumAsByte<EUnitInventory::Resource> resource);
	bool CanFitInInventory(float amount);

	bool IsInventoryFull();

	
	#pragma region Getters & Setters

	void SetCurrentResourceType(TEnumAsByte<EUnitInventory::Resource> resource);

	float GetCurrentResourceCount();
	float GetMaxResourceCount();
	TEnumAsByte<EUnitInventory::Resource> GetCurrentResourceType();
	#pragma endregion
};
