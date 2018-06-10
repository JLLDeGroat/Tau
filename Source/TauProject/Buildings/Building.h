// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Buildings/BuildingStructs.h"
#include "PlayerResource/ResourceCost.h"
#include "Units/Units.h"
#include "Units/UnitStructs.h" 
#include "Building.generated.h"
UCLASS()
class TAUPROJECT_API ABuilding : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABuilding();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	UPROPERTY(EditAnywhere, category = BuildingGlobal)
		TEnumAsByte<EAvailableBuildings::EAvailableBuildings> BuildingType;

	UPROPERTY(EditAnywhere, category = BuildingGlobal)
		FString BuildingName;

	UPROPERTY(EditAnywhere, category = BuildingGlobal)
		float Health;

	UPROPERTY(EditAnywhere, category = BuildingGlobal)
		float MaxHealth;
		
	UPROPERTY(EditAnywhere, category = BuildingGlobal)
		bool CanStore;

	#pragma region Costing
	UPROPERTY()
		TArray<UResourceCost*> BuildCost;

	TArray<UResourceCost*> GetBuildCost();
	#pragma endregion

	#pragma region Spawning
	UPROPERTY()
		bool IsPlaced;

	UPROPERTY()
		bool IsConstructed;

	UPROPERTY()
		bool CanPlace;

	UPROPERTY()
		TArray<UPrimitiveComponent*> OverlappingComponents;

	void SetBuildingAsPlaced();
	void CheckIsValidPlacement();
	bool GetIsValidPlacement();
	void SetIsValidPlacement(bool valid);

	void PlaceBuilding();
	#pragma endregion

	#pragma region Health Changes

	void AddToHealth(float amount);
	void SubtractFromHealth(float amount);
	void SetHealthToMax();

	void ChangeStateOnHealthChange();

	#pragma endregion

	#pragma region Onwership
	UPROPERTY()
		TEnumAsByte<EBuildingOwnerships::EBuildingOwnership> BuildingOwner;

	void SetBuildingOwner(TEnumAsByte<EBuildingOwnerships::EBuildingOwnership> owner);
	TEnumAsByte<EBuildingOwnerships::EBuildingOwnership> GetBuildingOwnership();

	#pragma endregion

	#pragma region States

	UPROPERTY()
		TEnumAsByte<EBuildStates::EBuildingStates> CurrentBuildingState;

	void SetBuildingState(TEnumAsByte<EBuildStates::EBuildingStates> state);
	TEnumAsByte<EBuildStates::EBuildingStates> GetCurrentState();

	TEnumAsByte<EAvailableBuildings::EAvailableBuildings> GetBuildingType();

	#pragma endregion
	
	#pragma region Creating And Spawning Units

	UPROPERTY()
		TArray<UObject*> SpawnList;

	void AddUnitToSpawnList(TEnumAsByte<EUnitList::All> unitType, AController* control);
	

	void SpawnUnitTick(float DeltaTime);
	#pragma endregion


	void Debug(FString error);
};
