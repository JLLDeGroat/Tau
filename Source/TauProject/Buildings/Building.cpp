// Fill out your copyright notice in the Description page of Project Settings.

#include "Building.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "PlayerResource/ResourceCost.h"
#include "Buildings/BuildingStructs.h"
#include "Units/Units.h"
#include "Units/UnitStructs.h"
#include "Buildings/BuildingSpawn.h"
#include "Engine/Engine.h"
#include "Engine/StaticMesh.h"
#include "Controller/PController.h"
#include "Buildings/Converter.h"


#include "Organic/Barracks.h"
#include "Organic/Storage.h"
#include "Organic/SawMill.h"
#include "Organic/CopperForge.h"
#include "Organic/IronForge.h"
#include "Organic/OreRefinery.h"
#include "Organic/TownCenter.h"
#include "Organic/SteelForge.h"



// Sets default values
ABuilding::ABuilding()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ResourceConverter = NewObject<UConverter>();
}

// Called when the game starts or when spawned
void ABuilding::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsPlaced) {
		ChangeStateOnHealthChange();

		if (IsConverter && IsConstructed) {
			UpdateResourceConvert(DeltaTime);
		}
	}
	if (SpawnList.Num() > 0) SpawnUnitTick(DeltaTime);

	
}

#pragma region build costs

TArray<UResourceCost*> ABuilding::GetBuildCost() {
	return BuildCost;
}

void ABuilding::SetBuildCosts(TArray<UResourceCost*> costList) {
	BuildCost = costList;
}
#pragma endregion

#pragma region Building Placement

void ABuilding::CheckIsValidPlacement() {
	for (int32 i = 0; i < OverlappingComponents.Num(); i++) {
		Debug(OverlappingComponents[i]->GetName());
		
		if (
			OverlappingComponents[i]->GetName() == "UnitBody" || OverlappingComponents[i]->GetName() == "CollisionCylinder" || // unit is in the way
			OverlappingComponents[i]->GetName() == "BuildingBody" // building is in the way
			)
		{
			SetIsValidPlacement(false);
			return; // return with fail
		}
	}
	SetIsValidPlacement(true);
}

void ABuilding::SetIsValidPlacement(bool valid) {
	CanPlace = valid;
}

bool ABuilding::GetIsValidPlacement() {
	return CanPlace;
}

void ABuilding::PlaceBuilding() {


	this->SetBuildingAsPlaced();	

	this->SetBuildingState(EBuildStates::BS_Constructing1);
	this->SetActorLocation(this->GetActorLocation());
	this->SetBuildingOwner(EBuildingOwnerships::EBuildingOwnership::BO_Player);
	

	TArray<UStaticMeshComponent*> Components;
	this->GetComponents<UStaticMeshComponent>(Components);
	for (int32 i = 0; i<Components.Num(); i++)
	{
		UStaticMeshComponent* StaticMeshComponent = Components[i];
		StaticMeshComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
	}
}

void ABuilding::SetBuildingAsPlaced() {
	IsPlaced = true;
}

void ABuilding::SetPlayerController(AController* controller) {
	control = controller;
}
AController* ABuilding::GetPlayerController() {
	return control;
}

void ABuilding::SetIsConstructed(bool val) {
	this->IsConstructed = val;
	this->SetBuildingState(EBuildStates::BS_Complete);
}

#pragma endregion

#pragma region Building States

void ABuilding::SetBuildingState(TEnumAsByte<EBuildStates::EBuildingStates> state) {
	CurrentBuildingState = state;
}

TEnumAsByte<EBuildStates::EBuildingStates> ABuilding::GetCurrentState() {
	return CurrentBuildingState;
}

TEnumAsByte<EAvailableBuildings::EAvailableBuildings> ABuilding::GetBuildingType() {
	return BuildingType;
}

#pragma endregion

#pragma region Ownership

void ABuilding::SetBuildingOwner(TEnumAsByte<EBuildingOwnerships::EBuildingOwnership> owner) {
	BuildingOwner = owner;
}
TEnumAsByte<EBuildingOwnerships::EBuildingOwnership> ABuilding::GetBuildingOwnership() {
	return BuildingOwner;
}

#pragma endregion

#pragma region Health changes

void ABuilding::AddToHealth(float amount) {
	this->Health += amount;
}

void ABuilding::SubtractFromHealth(float amount) {
	this->Health -= amount;
}

void ABuilding::SetHealthToMax() {
	this->Health = this->MaxHealth;
}

void ABuilding::ChangeStateOnHealthChange() {
	float healthAsPercent = (Health / MaxHealth) * 100;

	if (!IsConstructed) {
		if (healthAsPercent > 35 && healthAsPercent < 59) {
			SetBuildingState(EBuildStates::BS_Constructing1);
		}
		if (healthAsPercent >= 59 && healthAsPercent < 90) {
			SetBuildingState(EBuildStates::BS_Constructing2);
		}
		if (healthAsPercent >= 90) {
			SetBuildingState(EBuildStates::BS_Constructing3);
		}	
		if (healthAsPercent >= 100) {
			SetBuildingState(EBuildStates::BS_Complete);
		}
	}
	else if (IsConstructed) {
		if (healthAsPercent < 90 && healthAsPercent >= 60) {
			SetBuildingState(EBuildStates::BS_Damaged1);
		}
		if (healthAsPercent < 60 && healthAsPercent >= 30) {
			SetBuildingState(EBuildStates::BS_Damaged2);
		}
		if (healthAsPercent < 30) {
			SetBuildingState(EBuildStates::BS_Damaged3);
		}
	}
}

#pragma endregion

#pragma region UnitSpawning 

void ABuilding::AddUnitToSpawnList(TEnumAsByte<EUnitList::All> unit, AController* controller) {
	AUnits* unitClass = NewObject<AUnits>();
	unitClass = unitClass->GetUnitClassOfType(unit);

	APController* playerCon = Cast<APController>(controller);

	if (!playerCon->resources->CanAffordResourceList(unitClass->GetBuildCost())) return; // could not afford the unit

	playerCon->resources->AffectResouceListOnCounter(unitClass->GetBuildCost(), false);

	UBuildingSpawn* SpawnItem = NewObject<UBuildingSpawn>();

	SpawnItem->SetupSpawnitem(unitClass, unitClass->GetSpawnTime(), controller);

	SpawnList.Add(SpawnItem);
}

void ABuilding::SpawnUnitTick(float DeltaTime) {
	if (this->SpawnList.Num() > 0) {
		UBuildingSpawn* spawner = Cast<UBuildingSpawn>(SpawnList[0]);

		Debug("Spawning: " + spawner->GetUnit()->GetName() + " time: " + FString::SanitizeFloat(spawner->GetCurrentSpawnDeltaTime()) + " / " + FString::SanitizeFloat(spawner->GetSpawnCompleteDeltaTime()));

		spawner->UpdateSpawnList(DeltaTime);

		if (spawner->IsSpawncomplete()) {
			FVector spawnLocation = (this->GetActorForwardVector() * 150) + this->GetActorLocation() + (this->GetActorLocation().Z + 50);
			// (GetActorForwardVector() * 100) 100 being the amount forward it spawns

			auto spawnedinUnit = spawner->unit->SpawnUnitOfType(spawner->GetUnit()->ThisUnitType, spawnLocation, this->GetActorRotation(), GetWorld());
					
			spawnedinUnit->SetController(spawner->GetUnitController());
			spawnedinUnit->SetUnitOwner(EUnitOwnerships::UO_Player);

			SpawnList.Remove(spawner);
		}
	}
}

#pragma endregion

#pragma region Resource Converting

void ABuilding::SetResourceConversions(TArray<UResourceCost*> Cost, TArray<UResourceCost*> Reward, float Rate) {
	UConverter* cc = Cast<UConverter>(ResourceConverter);

	for (int32 i = 0; i < Cost.Num(); i++) {
		cc->SetConverterFromItem(Cost[i]);
	}

	for (int32 i = 0; i < Reward.Num(); i++) {
		cc->SetConverterToItem(Reward[i]);
	}

	cc->SetConversionRate(Rate);
}

void ABuilding::SetIsConverter(bool converter) {
	IsConverter = converter;
}
bool ABuilding::GetIsConverter() {
	return this->IsConverter;
}

void ABuilding::UpdateResourceConvert(float DeltaTime) {	
	UConverter* cc = Cast<UConverter>(ResourceConverter);
	APController* pCon = Cast<APController>(control);


	if (cc->CurrentlyConverting) {
		cc->UpdateConvert(DeltaTime);

		Debug(FString::SanitizeFloat(cc->CurrentConversion) + " out of " + FString::SanitizeFloat(cc->ConversionRate));

		if (cc->GetConversionComplete()) {
			cc->CompletedConversion();
			
			pCon->resources->AffectResouceListOnCounter(cc->GetConverterToItem(), true);
			pCon->resources->AffectResouceListOnCounter(cc->GetConverterFromItem(), false);


			cc->SetConversionComplete(false);
			cc->SetCurrentlyConverting(false);
		}
	}
	else {
		if (pCon->resources->CanAffordResourceList(cc->GetConverterFromItem())) {
			cc->SetCurrentlyConverting(true);			
		}
		else {
			Debug("Not Enough Resource To Convert from this building " + this->GetName());
		}
	}
	
}

#pragma endregion

#pragma region Utils

ABuilding* ABuilding::FindOrSpawnBuilding(TEnumAsByte<EAvailableBuildings::EAvailableBuildings> building, bool Find, UWorld* world) {

	switch (building) {

	case EAvailableBuildings::EAvailableBuildings::B_Barracks:
		if (Find) return NewObject<ABarracks>();
		else return world->SpawnActor<ABarracks>();
		break;

	case EAvailableBuildings::EAvailableBuildings::B_Storage:
		if (Find) return NewObject<AStorage>();
		else return world->SpawnActor<AStorage>();

	case EAvailableBuildings::EAvailableBuildings::B_SawMill:
		if (Find) return NewObject<ASawMill>();
		else return world->SpawnActor<ASawMill>();


	case EAvailableBuildings::EAvailableBuildings::B_None:
		return nullptr;
	}
	return nullptr;

}

#pragma endregion

void ABuilding::Debug(FString string) {
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, string);
}
