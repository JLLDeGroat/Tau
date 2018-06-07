// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Units/Units.h"
#include "Buildings/Building.h"
#include "Buildings/BuildingStructs.h"
#include "ControllerStructs.h"
#include "PlayerResource/All.h"
#include "PlayerResource/EResource.h"
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
	UAll* resources;

	UFUNCTION(BlueprintCallable)
	float GetResourceCount(TEnumAsByte<EResources::All> resource);

	void AffectResourceCount(TEnumAsByte<EResources::All> resource, float amount, bool IsAdd);
	
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
