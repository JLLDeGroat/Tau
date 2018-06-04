// Fill out your copyright notice in the Description page of Project Settings.

#include "UnitInventory.h"




bool UUnitInventory::CanAddResourcetoCount(TEnumAsByte<EUnitInventory::Resource> resource, float amount) {
	return IsRightResourceType(resource) && CanFitInInventory(amount);
}

bool UUnitInventory::IsRightResourceType(TEnumAsByte<EUnitInventory::Resource> resource) {
	if (GetCurrentResourceType() == resource || GetCurrentResourceType() == EUnitInventory::Resource::UR_None) {
		return true;
	}
	return false;
}

bool UUnitInventory::CanFitInInventory(float amount) {
	return GetCurrentResourceCount() < GetMaxResourceCount();
}

void UUnitInventory::AddToResourceCount(float count, TEnumAsByte<EUnitInventory::Resource> resource) {
	if (GetCurrentResourceType() == EUnitInventory::Resource::UR_None)
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

TEnumAsByte<EUnitInventory::Resource> UUnitInventory::GetCurrentResourceType() {
	return this->ResourceType;
}

float UUnitInventory::GetMaxResourceCount() {
	return this->MaxResourceCount;
}

#pragma endregion

#pragma region Setter

void UUnitInventory::SetCurrentResourceType(TEnumAsByte<EUnitInventory::Resource> resource) {
	ResourceType = resource;
}

#pragma endregion