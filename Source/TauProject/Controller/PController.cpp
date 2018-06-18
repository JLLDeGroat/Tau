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

#include "PlayerResource/EResource.h" 
#include "PlayerResource/All.h"
#include "PlayerResource/ResourceCost.h"

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

	resources = NewObject<UAll>();

	resources->AffectResourceCounter(EResources::R_Lumber, 20, true);
	resources->AffectResourceCounter(EResources::R_Stone, 20, true);
	resources->AffectResourceCounter(EResources::R_Bread, 20, true);
	resources->AffectResourceCounter(EResources::R_Iron, 20, true);
	resources->AffectResourceCounter(EResources::R_Planks, 10, true);

	//grab initial units and assign them this controller
	for (TActorIterator<AUnits> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		// Same as with the Object Iterator, access the subclass instance with the * or -> operators.
		AUnits* unit = *ActorItr;
		if (unit->GetUnitOwner() == EUnitOwnerships::UO_Player) unit->SetController(this);
	}
}


void APController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);	

	if (IsPlacingBuilding) KeepBuildingAtMouse();
}

#pragma region Widgets

void APController::SetWidgetToShow() {
	bool foundBuilder = false;
	if (SelectedUnits.Num() > 0) {
		for (int32 i = 0; i < SelectedUnits.Num(); i++) {
			if (SelectedUnits[i]->CanBuild) {				
				Hudptr->ShowWidget(EWidgets::EWidgetToShow::W_Selection);
				foundBuilder = true;
				break;
			}
		}
		if (!foundBuilder) return; // set widget to army unit
	}
	else if (SelectedBuildings.Num() > 0) {
		ABuilding* firstBuilding = SelectedBuildings[0];

		Hudptr->HideAllWidgets();

		switch (firstBuilding->GetBuildingType()) {

		case EAvailableBuildings::B_Barracks:
			Hudptr->ShowWidget(EWidgets::W_Barracks);
		}
	}
	else
		Hudptr->HideAllWidgets();
}

TEnumAsByte<EWidgets::EWidgetToShow> APController::GetWidgetToShow() {
	return WidgetToShow;
}

#pragma endregion

#pragma region Input Component Binding

void APController::SetupInputComponent() {
	Super::SetupInputComponent();
	InputComponent->BindAction("LeftClick", IE_Pressed, this, &APController::LeftMouseClick);
	InputComponent->BindAction("LeftClick", IE_Released, this, &APController::LeftMouseClickRelease);
	InputComponent->BindAction("RightClick", IE_Pressed, this, &APController::RightMouseClick);
	InputComponent->BindAction("RightClick", IE_Released, this, &APController::RightMouseClickRelease);
}

#pragma endregion

#pragma region Bind Axis

void APController::LeftMouseClick() {
	Hudptr->InitialPoint = Hudptr->GetMousePosition2D();
	Hudptr->bIsSelecting = true;

	if (IsPlacingBuilding) {
		PlaceBuilding();
	}
}

void APController::LeftMouseClickRelease() {
	Hudptr->bIsSelecting = false;
	SelectedUnits = Hudptr->SelectedUnits;
	SelectedBuildings = Hudptr->SelectedBuildings;

	SetWidgetToShow();
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

#pragma endregion

#pragma region Resource Management

float APController::GetResourceCount(TEnumAsByte<EResources::All> resource) {
	return resources->GetResourceCount(resource);
}

void APController::AffectResourceCount(TEnumAsByte<EResources::All> resource, float amount, bool IsAdd) {
	resources->AffectResourceCounter(resource, amount, IsAdd);
}

#pragma endregion 

#pragma region Building Management

void APController::BeginPlaceBuilding(TEnumAsByte<EAvailableBuildings::EAvailableBuildings> EBuilding) {

	if (BuildingToPlace != nullptr) {
		BuildingToPlace->Destroy();
		BuildingToPlace = nullptr;
	}
	
	BuildingToPlace = NewObject<ABuilding>()->FindOrSpawnBuilding(EBuilding, true, this->GetWorld()); // FindOrSpawnBuilding(EBuilding, true); // find

	if (BuildingToPlace == nullptr || !CanBuyBuilding(BuildingToPlace)) return; // found no building or can not afford

	BuildingToPlace = BuildingToPlace->FindOrSpawnBuilding(EBuilding, false, GetWorld()); // spawn

	IsPlacingBuilding = true;

	Debug("IsPlacingBuilding");
}

bool APController::CanBuyBuilding(ABuilding* building) {
	return resources->CanAffordResourceList(building->GetBuildCost());
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
	BuildingToPlace->SetPlayerController(this);

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


void APController::AddToOwnedBuildings(AActor* actor) {
	for (int32 i = 0; i < OwnedBuildings.Num(); i++) {
		if (actor == OwnedBuildings[i]) return;
	}
	OwnedBuildings.Add(actor);
}

void APController::RemoveFromOwnedBuildings(AActor* actor) {
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

void APController::Debug(FString string) {
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, string);
}
