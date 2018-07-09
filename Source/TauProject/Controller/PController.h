#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Units/Units.h"
#include "Buildings/Building.h"
#include "Buildings/BuildingStructs.h"
#include "ControllerStructs.h"
#include "PlayerResource/All.h"
#include "PlayerResource/EResource.h"
#include "Selection/PlayerSelection.h"
#include "Resources/Resource.h"
#include "Utils/DetailsStringLibrary.h"
#include "Buildings/Researcher.h"
#include "ControllerHudMessages.h"
#include "MarketHistory.h"
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

	void DebugFunctionOne();

	UPROPERTY()
		TArray<AUnits*> SelectedUnits;

	UPROPERTY()
		TArray<ABuilding*> SelectedBuildings;

	UPROPERTY()
		TArray<AResource*> SelectedResources;
	
	#pragma region Widgets	
	UPROPERTY(EditAnywhere)
    TEnumAsByte<EWidgets::EWidgetToShow> WidgetToShow;

	void SetWidgetToShow();
	UFUNCTION(BlueprintCallable)
	TEnumAsByte<EWidgets::EWidgetToShow> GetWidgetToShow();
	#pragma endregion

	#pragma region Widget Messages

	UPROPERTY()
		UControllerHudMessages* HudMessage;

	void ShowHudMessage(FString message);

	UFUNCTION(BlueprintCallable)
		bool GetShowHudMessage();

	UFUNCTION(BlueprintCallable)
		void SetShowHudMessage(bool val);

	UFUNCTION(BlueprintCallable)
		bool GetCurrentlyShowingHudMessage();

	UFUNCTION(BlueprintCallable)
		FString GetShowHudMessageText();

	UFUNCTION(BlueprintCallable)
		TArray<FString> GetAllResourceNamesAsString();

	UFUNCTION(BlueprintCallable)
		TEnumAsByte<EResources::All> GetResourceFromString(FString name);



	#pragma endregion

	#pragma region Resources

	UPROPERTY()
		UAll* resources;

	UFUNCTION(BlueprintCallable)
	float GetResourceCount(TEnumAsByte<EResources::All> resource);
	UFUNCTION(BlueprintCallable)
	float GetResourceCountCombine2(TEnumAsByte<EResources::All> resource, TEnumAsByte<EResources::All> resource2);
	UFUNCTION(BlueprintCallable)
	float GetResourceCountCombine3(TEnumAsByte<EResources::All> resource, TEnumAsByte<EResources::All> resource2, TEnumAsByte<EResources::All> resource3);
	UFUNCTION(BlueprintCallable)
	float GetResourceCountCombine4(TEnumAsByte<EResources::All> resource, TEnumAsByte<EResources::All> resource2, TEnumAsByte<EResources::All> resource3, TEnumAsByte<EResources::All> resource4);
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

	//ABuilding* FindOrSpawnBuilding(TEnumAsByte<EAvailableBuildings::EAvailableBuildings> EBuilding, bool Find);	

	bool CanBuyBuilding(ABuilding* building);

	bool HasResearchForBuilding(ABuilding* building);

	bool HasBuildingsForThisBuilding(ABuilding* building);

	void KeepBuildingAtMouse();

	

	void PlaceBuilding();

	void AddToOwnedBuildings(ABuilding* actor);
	void RemoveFromOwnedBuildings(ABuilding* actor);

	#pragma endregion

	#pragma region Building Spawn Management

	UFUNCTION(BlueprintCallable)
	void AddUnitToBuildingSpawnList(TEnumAsByte<EUnitList::All> unit);

	#pragma endregion

	#pragma region Hud Management

	UPROPERTY()
		UPlayerSelection* SelectionDetails;

	void DetermineSelectedUnit();
	void UpdateSelectedUnit();

	UFUNCTION(BlueprintCallable)
	UPlayerSelection* GetSelectionDetails();

	UPROPERTY()
		bool HasSelectedEntity;

	UFUNCTION(BlueprintCallable)
		bool GetHasSelectedEntity();

	void SetHasSelectedEntity(bool val);

	UDetailsStringLibrary* ActivityLibrary;

	#pragma endregion
	
	#pragma region Research

	UPROPERTY()
		TArray<UResearcher*> ResearchedList;

	UFUNCTION(BlueprintCallable)
		TArray<UResearcher*> GetResearchedList();

	UFUNCTION(BlueprintCallable)
		void AddToResearchList(UResearcher* research);

	UFUNCTION(BlueprintCallable)
		void AddListToResearchList(TArray<UResearcher*> researchList);

	#pragma endregion

	#pragma region Market Managing

	UPROPERTY()
		bool bIsMarketGenerated;
	
	UPROPERTY()
		UMarketHistory* marketHistory;


	UPROPERTY()
		float MarketUpdateCountDown;

	UFUNCTION(BlueprintCallable)
		UMarketHistory* GetMarketHistoryObject();

	UFUNCTION(BlueprintCallable)
		void TestMarketThread();

	

	void GenerateMarket();
	void UpdateMarket(float DeltaTime);





	UFUNCTION(BlueprintCallable)
		float GetResourceFromAmountFromSlider(float sliderVal, FString resourceFromName);
	UFUNCTION(BlueprintCallable)
		float GetResourceToAmountFromConversionRate(float resourceFromAmount, float conversionRate);


	UFUNCTION(BlueprintCallable)
		UObject* GetMarketItem(FString resFrom, FString resTo);

	UFUNCTION(BlueprintCallable)
		void TradeExecuted(FString resFrom, FString resTo, float conversionRate, float amount);

	UFUNCTION(BlueprintCallable)
		float GetMarketAmountToTrade(float newVal, FString resourceFromName);

	UFUNCTION(BlueprintCallable)
		float GetMarketAmountToGet(float newVal, FString resourceFromName, float conversionRate);

	#pragma endregion

	void Debug(FString string);
};
