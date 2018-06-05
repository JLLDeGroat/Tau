// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Units/Units.h"
#include "Buildings/Building.h"
#include "Buildings/BuildingStructs.h"
#include "ControllerStructs.h"
#include "PController.generated.h"


UCLASS()
class TAUPROJECT_API APController : public APlayerController
{
	GENERATED_BODY()
	APController();


protected:
	virtual void BeginPlay() override;

public:

	UPROPERTY()
	class APHUD* Hudptr;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupInputComponent() override;

	void LeftMouseClick();
	void LeftMouseClickRelease();

	void RightMouseClick();
	void RightMouseClickRelease();

	UPROPERTY()
	TArray<AUnits*> SelectedUnits;
	
	#pragma region Widgets	
	UPROPERTY(EditAnywhere)
    TEnumAsByte<EWidgets::EWidgetToShow> WidgetToShow;

	void SetWidgetToShow();
	UFUNCTION(BlueprintCallable)
	TEnumAsByte<EWidgets::EWidgetToShow> GetWidgetToShow();
	#pragma endregion

	#pragma region Resources

	UPROPERTY()
		float CurrentMinerals;

	UPROPERTY()
		float CurrentLumber;

	UPROPERTY()
		float CurrentCopper;

	UPROPERTY()
		float CurrentIron;

	UPROPERTY()
		float CurrentSteel;

	UPROPERTY()
		float CurrentFood;

	UFUNCTION(BlueprintCallable)
		float GetCurrentMinerals();

	UFUNCTION(BlueprintCallable)
		float GetCurrentLumber();

	UFUNCTION(BlueprintCallable)
		float GetCurrentCopper();

	UFUNCTION(BlueprintCallable)
		float GetCurrentIron();

	UFUNCTION(BlueprintCallable)
		float GetCurrentSteel();

	UFUNCTION(BlueprintCallable)
		float GetCurrentFood();

	UFUNCTION(BlueprintCallable)
		void AddToCurrentMinerals(float minerals);

	UFUNCTION(BlueprintCallable)
		void SubtractFromCurrentMinerals(float minerals);

	UFUNCTION(BlueprintCallable)
		void AddToCurrentLumber(float lumber);

	UFUNCTION(BlueprintCallable)
		void SubtractFromCurrentLumber(float lumber);

	UFUNCTION(BlueprintCallable)
		void AddToCurrentCopper(float copper);

	UFUNCTION(BlueprintCallable)
		void SubtractFromCurrentCopper(float copper);

	UFUNCTION(BlueprintCallable)
		void AddToCurrentIron(float iron);

	UFUNCTION(BlueprintCallable)
		void SubtractFromCurrentIron(float iron);

	UFUNCTION(BlueprintCallable)
		void AddToCurrentSteel(float steel);

	UFUNCTION(BlueprintCallable)
		void SubtractFromCurrentSteel(float steel);

	UFUNCTION(BlueprintCallable)
		void AddToCurrentFood(float food);

	UFUNCTION(BlueprintCallable)
		void SubractFromCurrentFood(float food);
	

	#pragma endregion

	#pragma region Building Buildings

	UPROPERTY()
		TArray<AActor*> OwnedBuildings;

	UPROPERTY()
		bool IsPlacingBuilding;

	ABuilding* BuildingToPlace;

	UFUNCTION(BlueprintCallable)
	void BeginPlaceBuilding(TEnumAsByte<EAvailableBuildings::EAvailableBuildings> EBuilding);

	ABuilding* FindOrSpawnBuilding(TEnumAsByte<EAvailableBuildings::EAvailableBuildings> EBuilding, bool Find);	

	bool CanBuyBuilding(ABuilding* building);

	void KeepBuildingAtMouse();

	void PlaceBuilding();

	void AddToOwnedBuildings(AActor* actor);
	void RemoveFromOwnedBuildings(AActor* actor);

	#pragma endregion


	void Debug(FString string);
};
