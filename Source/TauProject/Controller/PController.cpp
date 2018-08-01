// Fill out your copyright notice in the Description page of Project Settings.

#include "PController.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Actor.h"
#include "AIController.h"
#include "AI/Navigation/NavigationSystem.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Viewport.h"

#include "HUD/PHUD.h"
#include "ControllerStructs.h"
#include "ControllerHudMessages.h"
#include "MarketHistory.h"
#include "MarketPlace/MarketItem.h"

#include "Buildings/Building.h"
#include "Buildings/Organic/Barracks.h"
#include "Buildings/Organic/Storage.h"
#include "Buildings/Organic/SawMill.h"

#include "Units/Units.h"
#include "Units/UnitStructs.h"
#include "Units/Organic/Pea.h"
#include "Units/Organic/Sprout.h"

#include "Engine/Engine.h"
#include "EngineUtils.h"
#include "Blueprint/UserWidget.h"

#include "Resources/Resource.h"
#include "PlayerResource/EResource.h" 
#include "PlayerResource/All.h"
#include "PlayerResource/ResourceCost.h"

#include "Selection/PlayerSelection.h"

#include "Utils/DetailsStringLibrary.h"

#include "Utils/MarketTask.h"

#pragma region Basic

APController::APController() {
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
	//basic	
}

// GET HUD
void APController::BeginPlay() {
	Super::BeginPlay();
	Hudptr = Cast<APHUD>(GetHUD()); // Hud ptr
	HudMessage = NewObject<UControllerHudMessages>();
	resources = NewObject<UAll>();
	marketHistory = NewObject<UMarketHistory>();

	resources->AffectResourceCounter(EResources::R_Lumber, 100, true);
	resources->AffectResourceCounter(EResources::R_Stone, 100, true);
	resources->AffectResourceCounter(EResources::R_Bread, 100, true);
	resources->AffectResourceCounter(EResources::R_Iron, 100, true);
	resources->AffectResourceCounter(EResources::R_Copper, 100, true);
	resources->AffectResourceCounter(EResources::R_Planks, 100, true);
	resources->AffectResourceCounter(EResources::R_CopperOre, 100, true);
	resources->AffectResourceCounter(EResources::R_IronOre, 100, true);
	resources->AffectResourceCounter(EResources::R_Planks, 100, true);

	//grab initial units and assign them this controller
	for (TActorIterator<AUnits> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		
		// Same as with the Object Iterator, access the subclass instance with the * or -> operators.
		AUnits* unit = *ActorItr;
		if (unit->GetUnitOwner() == EUnitOwnerships::UO_Player) unit->SetController(this);
	}
	ActivityLibrary = NewObject<UDetailsStringLibrary>();
}


void APController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (IsPlacingBuilding) KeepBuildingAtMouse();

	DetermineSelectedUnit();

	UpdateMarket(DeltaTime);

	HighlightHoveredUnit();
}

#pragma endregion

#pragma region Input Component Binding

void APController::SetupInputComponent() {
	Super::SetupInputComponent();
	InputComponent->BindAction("LeftClick", IE_Pressed, this, &APController::LeftMouseClick);
	InputComponent->BindAction("LeftClick", IE_Released, this, &APController::LeftMouseClickRelease);
	InputComponent->BindAction("RightClick", IE_Pressed, this, &APController::RightMouseClick);
	InputComponent->BindAction("RightClick", IE_Released, this, &APController::RightMouseClickRelease);

	InputComponent->BindAction("DebugOne", IE_Pressed, this, &APController::DebugFunctionOne);
}

#pragma endregion

#pragma region Bind Axis

void APController::LeftMouseClick() {
	Hudptr->InitialPoint = Hudptr->GetMousePosition2D();
	Hudptr->bIsSelecting = true;

	for (int32 i = 0; i < SelectedUnits.Num(); i++) {
		SelectedUnits[i]->HideDecals();
		Debug(FString::SanitizeFloat(SelectedUnits.Num()) + " units to hide");
	}

	if (IsPlacingBuilding) {
		PlaceBuilding();
	}		

}

void APController::LeftMouseClickRelease() {
	Hudptr->bIsSelecting = false;
	SelectedUnits = Hudptr->SelectedUnits;
	SelectedBuildings = Hudptr->SelectedBuildings;
	SelectedResources = Hudptr->SelectedResources;
	//SetWidgetToShow();
	for (int32 i = 0; i < SelectedUnits.Num(); i++) {
		SelectedUnits[i]->ShowDecals();
	}

}

void APController::RightMouseClick() {
	SelectedUnits = Hudptr->SelectedUnits;
}

void APController::RightMouseClickRelease() {
	if (SelectedUnits.Num() > 0) {

		// get hit result of Click
		FHitResult Hit;
		GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, Hit);
		FVector MovePosition = Hit.Location;

		//check if actor was was of type
		for (int32 i = 0; i < SelectedUnits.Num(); i++) {
			int32 UnitNumberInCount = i;
			int32 TotalUnitsInCount = SelectedUnits.Num();
			SelectedUnits[i]->MoveUnit(Hit.GetActor(), MovePosition, UnitNumberInCount, TotalUnitsInCount);
		}
	}
}

void APController::DebugFunctionOne() {

	for (int32 i = 0; i < ResearchedList.Num(); i++)
		Debug(ResearchedList[i]->GetResearchName());

	if (ResearchedList.Num() == 0) Debug("No research completed");
}

#pragma endregion

#pragma region Resource Management

float APController::GetResourceCount(TEnumAsByte<EResources::All> resource, bool IsUI) {
	return resources->GetResourceCount(resource, IsUI);
}
float APController::GetResourceCountCombine2(TEnumAsByte<EResources::All> resource, TEnumAsByte<EResources::All> resource2) {
	return (resources->GetResourceCount(resource) + resources->GetResourceCount(resource2));
}
float APController::GetResourceCountCombine3(TEnumAsByte<EResources::All> resource, TEnumAsByte<EResources::All> resource2, TEnumAsByte<EResources::All> resource3) {
	return (resources->GetResourceCount(resource) + resources->GetResourceCount(resource2) + resources->GetResourceCount(resource3));
}
float APController::GetResourceCountCombine4(TEnumAsByte<EResources::All> resource, TEnumAsByte<EResources::All> resource2, TEnumAsByte<EResources::All> resource3, TEnumAsByte<EResources::All> resource4) {
	return (resources->GetResourceCount(resource) + resources->GetResourceCount(resource2) + resources->GetResourceCount(resource3) + resources->GetResourceCount(resource4));
}

void APController::AffectResourceCount(TEnumAsByte<EResources::All> resource, float amount, bool IsAdd) {
	resources->AffectResourceCounter(resource, amount, IsAdd);
}

TArray<FString> APController::GetAllResourceNamesAsString() {
	return resources->GetAllResourceNamesAsString();
}

TEnumAsByte<EResources::All> APController::GetResourceFromString(FString name) {
	return resources->GetResourceFromString(name);
}

#pragma endregion 

#pragma region Building Management

void APController::BeginPlaceBuilding(TEnumAsByte<EAvailableBuildings::EAvailableBuildings> EBuilding) {

	if (BuildingToPlace != nullptr) {
		BuildingToPlace->Destroy();
		BuildingToPlace = nullptr;
	}

	BuildingToPlace = NewObject<ABuilding>()->FindOrSpawnBuilding(EBuilding, true, this->GetWorld()); // FindOrSpawnBuilding(EBuilding, true); // find
	if (BuildingToPlace == nullptr) {
		Debug("Building returned Null");
		return;
	}

	BuildingToPlace->SetPlayerController(this);

	if (!CanBuyBuilding(BuildingToPlace) || !BuildingToPlace->SpecialSpawnConditionsMet()
		|| !HasResearchForBuilding(BuildingToPlace) || !HasBuildingsForThisBuilding(BuildingToPlace)
		) return; // found no building or can not afford or adheres to special rules

	BuildingToPlace = BuildingToPlace->FindOrSpawnBuilding(EBuilding, false, GetWorld()); // spawn
	BuildingToPlace->SetPlayerController(this);
	IsPlacingBuilding = true;

	Debug("IsPlacingBuilding");
}

bool APController::CanBuyBuilding(ABuilding* building) {
	if (resources->CanAffordResourceList(building->GetBuildCost())) {
		Debug("Can afford");
		return true;
	}
	else {
		Debug("Cannot Afford To build " + building->BuildingName);
		ShowHudMessage("Cannot Afford To build " + building->BuildingName);
		return false;
	}
}

bool APController::HasResearchForBuilding(ABuilding* building) {
	Debug(FString::SanitizeFloat(building->ResearchCost.Num()));

	if (building->ResearchCost.Num() == 0) return true;

	for (int32 i = 0; i < building->ResearchCost.Num(); i++) {
		bool hasThisResearch = false;

		for (int32 x = 0; x < ResearchedList.Num(); x++) {
			if (ResearchedList[x]->GetResearchName() == building->ResearchCost[i]->GetResearchName()) {
				hasThisResearch = true;
			}
		}

		if (!hasThisResearch) {
			ShowHudMessage("Can not build " + building->BuildingName + " as you dont have the research " + building->ResearchCost[i]->GetResearchName());
			return false;
		}
	}
	return true;
}

bool APController::HasBuildingsForThisBuilding(ABuilding* building) {
	Debug("Going to look for it");


	if (building->GetNeededBuildingList().Num() == 0) return true;

	for (int32 i = 0; i < building->GetNeededBuildingList().Num(); i++) {
		Debug(building->GetNeededBuildingList()[i]);
		bool hasBuilding = false;

		for (int32 x = 0; x < OwnedBuildings.Num(); x++) {
			ABuilding* thisBuilding = Cast<ABuilding>(OwnedBuildings[x]);
			if (thisBuilding->BuildingName == building->GetNeededBuildingList()[i]) {
				hasBuilding = true;
			}
		}

		if (!hasBuilding) {
			ShowHudMessage("Can not build this building, you do not have " + building->GetNeededBuildingList()[i]);
			return false;
		}
	}

	return true;
}

void APController::KeepBuildingAtMouse() {

	UGameViewportClient* GameViewPort = GEngine->GameViewport;
	FVector2D MousePosition;
	FVector2D ViewPortSize;

	GameViewPort->GetViewportSize(ViewPortSize);

	if (GameViewPort->GetMousePosition(MousePosition))
	{
		FHitResult Hit;
		GetHitResultUnderCursor(ECollisionChannel::ECC_WorldStatic, false, Hit);
		BuildingToPlace->SetActorLocation(Hit.Location);
	}
	else BuildingToPlace->SetActorLocation(FVector(0, 2, 0));
}

void APController::PlaceBuilding() {
	if (!IsPlacingBuilding || !BuildingToPlace->GetIsValidPlacement()) return; // do nothing if not placing building or is overlapping	

	Debug("is placing and valid placement");

	IsPlacingBuilding = false;
	BuildingToPlace->PlaceBuilding();

	AddToOwnedBuildings(BuildingToPlace);



	resources->AffectResouceListOnCounter(BuildingToPlace->GetBuildCost(), false);

	for (int32 i = 0; i < SelectedUnits.Num(); i++) {
		if (SelectedUnits[i]->CanBuild) {
			SelectedUnits[i]->MoveUnit(BuildingToPlace, BuildingToPlace->GetActorLocation(), i, SelectedUnits.Num());
			//Cast<APea>(SelectedUnits[i]).
			//SelectedUnits[i]->SetUnitInstruction(EUnitInstructions::UI_Construct, "building", ToSpawn, ToSpawn->GetActorLocation());
		}
	}

	BuildingToPlace = nullptr;

	//CurrentSelectedBuilding = ToSpawn->GetName();
	//CurrentSelectionHealth = ToSpawn->BuildingHealth;
	//CurrentSelectionMaxHealth = ToSpawn->BuildingMaxHealth;
	SelectedUnits.Empty(); // empty 
	//UpdateOwnedBuildings();
}

void APController::AddToOwnedBuildings(ABuilding* actor) {
	for (int32 i = 0; i < OwnedBuildings.Num(); i++) {
		if (actor == OwnedBuildings[i]) return;
	}
	if (actor->BuildingName == "Market Place") GenerateMarket();
	OwnedBuildings.Add(actor);
}

void APController::RemoveFromOwnedBuildings(ABuilding* actor) {
	for (int32 i = 0; i < OwnedBuildings.Num(); i++) {
		if (actor == OwnedBuildings[i]) {
			OwnedBuildings.RemoveAt(i);
			return;
		}
	}
}

#pragma endregion

#pragma region Building Spawn Management

void APController::AddUnitToBuildingSpawnList(TEnumAsByte<EUnitList::All> unit) {
	SelectedBuildings[0]->AddUnitToSpawnList(unit, this);
	Debug("added to list 2");
}

#pragma endregion

#pragma region Hud Management

UControllerHudMessages* APController::GetHudMessageClass() {
	return HudMessage;
}

void APController::DetermineSelectedUnit() {

	if (SelectedUnits.Num() > 0) {
		if (SelectionDetails == nullptr) SelectionDetails = NewObject<UPlayerSelection>(this);

		AUnits* thisunit = SelectedUnits[0];

		TEnumAsByte<EUnitInstructions::EUnitInstruction> instruction = EUnitInstructions::UI_None;
		if (thisunit->UnitTask->HasTask()) instruction = thisunit->UnitTask->GetInstruction();

		SelectionDetails->SetSelection(
			thisunit->GetName(),
			thisunit->GetHealth(),
			thisunit->GetMaxHealth(),
			instruction, // get activity string here
			thisunit->GetName(),
			thisunit
		);

		SetHasSelectedEntity(true);
	}
	else if (SelectedBuildings.Num() > 0) {
		if (SelectionDetails == nullptr) SelectionDetails = NewObject<UPlayerSelection>(this);

		ABuilding* building = SelectedBuildings[0];

		SelectionDetails->SetSelection(
			building->GetName(),
			building->GetHealth(),
			building->GetMaxHealth(),
			building->GetCurrentState(), // get activity string here
			building->GetName(),
			building
		);

		SetHasSelectedEntity(true);
	}
	else if (SelectedResources.Num() > 0) {
		if (SelectionDetails == nullptr) SelectionDetails = NewObject<UPlayerSelection>(this);

		AResource* res = SelectedResources[0];

		SelectionDetails->SetSelection(
			res->GetName(),
			res->ResourceCount,
			res->ResourceCountOriginal,
			res->GetResourceType(),
			res->GetName(),
			res
		);
		SetHasSelectedEntity(true);
	}
	else {
		SetHasSelectedEntity(false);
		SelectionDetails = nullptr;
	}
}

UPlayerSelection* APController::GetSelectionDetails() {
	return SelectionDetails;
}

void APController::UpdateSelectedUnit() {

}

bool APController::GetHasSelectedEntity() {
	return HasSelectedEntity;
}

void APController::SetHasSelectedEntity(bool val) {
	HasSelectedEntity = val;
}

void APController::ShowHudMessage(FString message) {
	HudMessage->ShowMessage(message);
}

bool APController::GetShowHudMessage() {
	return HudMessage->bShowMessage;
}

bool APController::GetCurrentlyShowingHudMessage() {
	return HudMessage->bCurrentlyShowingMessage;
}

void APController::SetShowHudMessage(bool val) {
	HudMessage->bShowMessage = val;
}

FString APController::GetShowHudMessageText() {
	return HudMessage->Message;
}

void APController::HighlightHoveredUnit() {
	FHitResult Hit;
	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, Hit);

	if (AActor* actor = Hit.GetActor()) {

		if (AUnits* unit = Cast<AUnits>(actor)) {
			unit->bIsHighlighted = true;
			HighlightedUnit = unit;
			HighlightedUnit->ShowHighlighDecals();
		}
		else {
			if (HighlightedUnit != nullptr) {
				HighlightedUnit->bIsHighlighted = false;
				HighlightedUnit = nullptr;
			}
		}
	}
}

#pragma endregion

#pragma region Widgets

void APController::SetWidgetToShow() {
	bool foundBuilder = false;
	if (SelectedUnits.Num() > 0) {
		for (int32 i = 0; i < SelectedUnits.Num(); i++) {
			if (SelectedUnits[i]->CanBuild) {
				//Hudptr->ShowWidget(EWidgets::EWidgetToShow::W_Selection);
				foundBuilder = true;
				break;
			}
		}
		if (!foundBuilder) return; // set widget to army unit
	}
	else if (SelectedBuildings.Num() > 0) {
		ABuilding* firstBuilding = SelectedBuildings[0];

		//Hudptr->HideAllWidgets();

		//switch (firstBuilding->GetBuildingType()) {

		//case EAvailableBuildings::B_Barracks:
		//	//Hudptr->ShowWidget(EWidgets::W_Barracks);
		//}
	}
	else{ }
		//Hudptr->HideAllWidgets();
}

TEnumAsByte<EWidgets::EWidgetToShow> APController::GetWidgetToShow() {
	return WidgetToShow;
}

#pragma endregion

#pragma region Research

TArray<UResearcher*> APController::GetResearchedList() {
	return ResearchedList;
}

void APController::AddToResearchList(UResearcher* research) {
	for (int32 i = 0; i < ResearchedList.Num(); i++) {
		if (research->Name == ResearchedList[i]->Name && research->CurrentVersion == ResearchedList[i]->CurrentVersion) {
			Debug("Already added this research");
			return;
		}
	}
	ResearchedList.Add(research);
}


void APController::AddListToResearchList(TArray<UResearcher*> researchList) {
	for (int32 i = 0; i < researchList.Num(); i++) {
		UResearcher* research = researchList[i];

		for (int32 x = 0; x < ResearchedList.Num(); x++) {
			if (research->Name == ResearchedList[i]->Name) {
				Debug("Already added this research");
				break;
			}
		}
		HudMessage->ShowCompletionMessage(research->Name + " has been successfully researched");
		ResearchedList.Add(research);
	}
}

#pragma endregion

#pragma region Market Management

UMarketHistory* APController::GetMarketHistoryObject() {
	return marketHistory;
}
void APController::TestMarketThread() {
	if (!bIsMarketGenerated) {
		(new FAutoDeleteAsyncTask<MarketTask>(this, marketHistory, resources, true))->StartBackgroundTask();
		bIsMarketGenerated = true;
	}
}

void APController::GenerateMarket() {
	if (!bIsMarketGenerated) {
		(new FAutoDeleteAsyncTask<MarketTask>(this, marketHistory, resources, true))->StartBackgroundTask();
		bIsMarketGenerated = true;
		Debug("Market Place generated");
	}
}

void APController::UpdateMarket(float DeltaTime) {
	MarketUpdateCountDown += DeltaTime;

	if (MarketUpdateCountDown > 5) {
		(new FAutoDeleteAsyncTask<MarketTask>(this, marketHistory, resources, false))->StartBackgroundTask();
		MarketUpdateCountDown = 0;
		Debug("Market Updated");
	}
}

UObject* APController::GetMarketItem(FString resFrom, FString resTo) {
	for (int32 i = 0; i < marketHistory->MarketItems.Num(); i++) {
		UObject* object = marketHistory->MarketItems[i];
		if (UMarketItem* item = Cast<UMarketItem>(object)) {
			if (item->GetResFrom() == resFrom && item->GetResTo() == resTo) return item;
		}
	}
	Debug("Found No Market Item");
	return nullptr;
}

float APController::GetResourceFromAmountFromSlider(float sliderVal, FString resourceFromName) {
	return resources->GetResourceCount(GetResourceFromString(resourceFromName)) * sliderVal;
}

float APController::GetResourceToAmountFromConversionRate(float resourceFromAmount, float conversionRate) {
	return resourceFromAmount * conversionRate;
}

float APController::GetMarketAmountToTrade(float newVal, FString resourceFromName) {
	return resources->GetResourceCount(GetResourceFromString(resourceFromName)) * newVal;
}

float APController::GetMarketAmountToGet(float newVal, FString resourceFromName, float conversionRate) {
	float amount = resources->GetResourceCount(GetResourceFromString(resourceFromName)) * newVal;
	float result = amount * conversionRate;
	return result;
}

void APController::TradeExecuted(FString resFrom, FString resTo, float conversionRate, float amount) {

	EResources::All resourceFromType = resources->GetResourceFromString(resFrom);
	EResources::All resourceToType = resources->GetResourceFromString(resTo);

	if (resources->CanAffordResourceItem(NewObject<UResourceCost>()->Setup(resourceFromType, amount))) {
		resources->AffectResourceCounter(resourceFromType, amount, false);
		float amountToAdd = amount * conversionRate;
		resources->AffectResourceCounter(resourceToType, amountToAdd, true);

		UMarketItem* item = Cast<UMarketItem>(GetMarketItem(resFrom, resTo));

		item->IncrementTimesTraded();

	}
	else {
		Debug("can not afford this trade");
	}
}

#pragma endregion

void APController::Debug(FString string) {
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, string);
}

