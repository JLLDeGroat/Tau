// Fill out your copyright notice in the Description page of Project Settings.

#include "UnitInventory.h"
#include "PlayerResource/EResource.h"



bool UUnitInventory::CanAddResourcetoCount(TEnumAsByte<EResources::All> resource, float amount) {
	return IsRightResourceType(resource) && CanFitInInventory(amount);
}

bool UUnitInventory::IsRightResourceType(TEnumAsByte<EResources::All> resource) {
	if (GetCurrentResourceType() == resource || GetCurrentResourceType() == EResources::All::R_None) {
		return true;
	}
	return false;
}

bool UUnitInventory::CanFitInInventory(float amount) {
	return GetCurrentResourceCount() < GetMaxResourceCount();
}

void UUnitInventory::AddToResourceCount(float count, TEnumAsByte<EResources::All> resource) {
	if (GetCurrentResourceType() == EResources::All::R_None)
		SetCurrentResourceType(resource);

	ResourceCount += count;
}

bool UUnitInventory::IsInventoryFull() {
	return ResourceCount >= MaxResourceCount;
}


#pragma region Getters

float UUnitInventory::GetCurrentResourceCount() {
	return this->ResourceCount;
}

TEnumAsByte<EResources::All> UUnitInventory::GetCurrentResourceType() {
	return this->ResourceType;
}

float UUnitInventory::GetMaxResourceCount() {
	return this->MaxResourceCount;
}

#pragma endregion

#pragma region Setter

void UUnitInventory::SetCurrentResourceType(TEnumAsByte<EResources::All> resource) {
	ResourceType = resource;
}

#pragma endregion

void UUnitInventory::EmptyInventory() {
	this->ResourceCount = 0;
	this->ResourceType = EResources::R_None;
}