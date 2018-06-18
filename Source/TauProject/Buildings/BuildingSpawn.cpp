// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingSpawn.h"
#include "Units/Units.h"


void UBuildingSpawn::SetupSpawnitem(AUnits* unitClass, float SpawnTime, AController* controller) {
	SetUnit(unitClass);
	SetSpawnCompleteDeltaTime(SpawnTime);
	SetCurrentSpawnDeltaTime(0);
	SetUnitController(controller);
}

bool UBuildingSpawn::IsSpawncomplete() {
	return currentSpawnDeltaTime >= SpawnCompleteDeltaTime;
}

void UBuildingSpawn::UpdateSpawnList(float DeltaTime) {
	currentSpawnDeltaTime += DeltaTime;
}

#pragma region Setters 
void UBuildingSpawn::SetUnit(AUnits* un) {
	unit = un;
}
void UBuildingSpawn::SetCurrentSpawnDeltaTime(float t) {
	currentSpawnDeltaTime = t;
}
void UBuildingSpawn::SetSpawnCompleteDeltaTime(float t) {
	SpawnCompleteDeltaTime = t;
}
void UBuildingSpawn::SetUnitController(AController* controller) {
	UnitController = controller;
}
#pragma endregion

#pragma region Getters

AUnits* UBuildingSpawn::GetUnit() {
	return unit;
}
float UBuildingSpawn::GetCurrentSpawnDeltaTime() {
	return currentSpawnDeltaTime;
}
float UBuildingSpawn::GetSpawnCompleteDeltaTime() {
	return SpawnCompleteDeltaTime;
}
AController* UBuildingSpawn::GetUnitController() {
	return UnitController;
}

#pragma endregion