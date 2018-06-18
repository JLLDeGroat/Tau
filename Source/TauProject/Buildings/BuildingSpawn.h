// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Units/Units.h"

#include "BuildingSpawn.generated.h"

/**
 * 
 */
UCLASS()
class TAUPROJECT_API UBuildingSpawn : public UObject
{
	GENERATED_BODY()

public:
		UPROPERTY()
		AUnits* unit;
	
		UPROPERTY()
			float currentSpawnDeltaTime;

		UPROPERTY()
			float SpawnCompleteDeltaTime;

		UPROPERTY()
			bool SpawnComplete;

		UPROPERTY()
			AController* UnitController;


		bool IsSpawncomplete();

		void UpdateSpawnList(float DeltaTime);

		void SetupSpawnitem(AUnits* unit, float Spawntime, AController* controller);

	#pragma region getters & setters

		AUnits* GetUnit();
		float GetCurrentSpawnDeltaTime();
		float GetSpawnCompleteDeltaTime();
		AController* GetUnitController();

		void SetUnit(AUnits* unit);
		void SetCurrentSpawnDeltaTime(float t);
		void SetSpawnCompleteDeltaTime(float t);
		void SetUnitController(AController* controller);

	#pragma endregion
	
};
