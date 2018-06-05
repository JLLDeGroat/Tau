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

#include "Units/Units.h"
#include "Units/Organic/Pea.h"
#include "Units/Organic/Sprout.h"

#include "Engine/Engine.h"
#include "Blueprint/UserWidget.h"

APController::APController() {
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableTouchEvents = true;	
}

// GET HUD
void APController::BeginPlay() {
	Super::BeginPlay();
	Hudptr = Cast<APHUD>(GetHUD()); // Hud ptr
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

	if (IsPlacingBuilding) PlaceBuilding();
}

void APController::LeftMouseClickRelease() {
	Hudptr->bIsSelecting = false;
	SelectedUnits = Hudptr->SelectedUnits;

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

float APController::GetCurrentMinerals() {
	return CurrentMinerals;
}

float APController::GetCurrentLumber() {
	return CurrentLumber;
}

float APController::GetCurrentCopper() {
	return CurrentCopper;
}

float APController::GetCurrentIron() {
	return CurrentIron;
}

float APController::GetCurrentSteel() {
	return CurrentSteel;
}

float APController::GetCurrentFood() {
	return CurrentFood;
}

void APController::AddToCurrentMinerals(float minerals) {
	CurrentMinerals += minerals;
}

void APController::SubtractFromCurrentMinerals(float minerals) {
	CurrentMinerals -= minerals;
}

void APController::AddToCurrentLumber(float lumber) {
	CurrentLumber += lumber;
}

void APController::SubtractFromCurrentLumber(float lumber) {
	CurrentLumber -= lumber;
}

void APController::AddToCurrentCopper(float copper) {
	CurrentCopper += copper;
}

void APController::SubtractFromCurrentCopper(float copper) {
	CurrentCopper -= copper;
}

void APController::AddToCurrentIron(float iron) {
	CurrentIron += iron;
}

void APController::SubtractFromCurrentIron(float iron) {
	CurrentIron -= iron;
}

void APController::AddToCurrentSteel(float steel) {
	CurrentSteel += steel;
}

void APController::SubtractFromCurrentSteel(float steel) {
	CurrentSteel -= steel;
}

void APController::AddToCurrentFood(float food) {
	CurrentFood += food;
}

void APController::SubractFromCurrentFood(float food) {
	CurrentFood -= food;
}


#pragma endregion 

#pragma region Building Management

void APController::BeginPlaceBuilding(TEnumAsByte<EAvailableBuildings::EAvailableBuildings> EBuilding) {
	
	BuildingToPlace = FindOrSpawnBuilding(EBuilding, true); // find

	if (BuildingToPlace == nullptr || !CanBuyBuilding(BuildingToPlace)) return; // found no building or can not afford

	BuildingToPlace = FindOrSpawnBuilding(EBuilding, false); // spawn

	IsPlacingBuilding = true;
}
ABuilding* APController::FindOrSpawnBuilding(TEnumAsByte<EAvailableBuildings::EAvailableBuildings> EBuilding, bool Find) {

	switch (EBuilding) {

		case EAvailableBuildings::EAvailableBuildings::B_Barracks:
			if(Find) return NewObject<ABarracks>();
			else return GetWorld()->SpawnActor<ABarracks>();
			break;

		case EAvailableBuildings::EAvailableBuildings::B_Storage:
			if (Find) return NewObject<AStorage>();
			else return GetWorld()->SpawnActor<AStorage>();

		case EAvailableBuildings::EAvailableBuildings::B_None:
			return nullptr;
	}
	return nullptr;
}

bool APController::CanBuyBuilding(ABuilding* building) {
	if (GetCurrentMinerals() >= building->MineralCost && 
		GetCurrentLumber()   >= building->LumberCost) 
		return true;	
	else 
		return false;
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

	IsPlacingBuilding = false;
	BuildingToPlace->PlaceBuilding();

	AddToOwnedBuildings(BuildingToPlace);

	for (int32 i = 0; i < SelectedUnits.Num(); i++) {
		if (SelectedUnits[i]->CanBuild) {
			//Cast<APea>(SelectedUnits[i]).
			//SelectedUnits[i]->SetUnitInstruction(EUnitInstructions::UI_Construct, "building", ToSpawn, ToSpawn->GetActorLocation());
		}
	}

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

void APController::Debug(FString string) {
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, string);
}
