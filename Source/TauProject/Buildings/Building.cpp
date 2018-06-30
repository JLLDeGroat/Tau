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
#include "Organic/PhylosopherCave.h"

#include "Organic/Farm.h"
#include "Organic/Depletable/FarmField.h"

#include "Buildings/Researcher.h"



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

	if (!IsPlaced) {
		CheckIsValidPlacement();
		SetMeshOnValidPlacement();
	}

	if (IsPlaced) {
		ChangeStateOnHealthChange();
		SetMeshOnState();

		if (IsConverter && IsConstructed) {
			UpdateResourceConvert(DeltaTime);
		}
	}
	if (SpawnList.Num() > 0) SpawnUnitTick(DeltaTime);


	if (CurrentlyResearching) ResearchTick(DeltaTime);

}

#pragma region Overlaps

void ABuilding::StartOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	FString sentence = "Actor: " + OtherActor->GetName() + " Component: " + OtherComp->GetName();
	if (!IsPlaced && OtherActor != this) {
		OverlappingComponents.Add(OtherComp);
	}
}

void ABuilding::EndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	if (!IsPlaced && OtherActor != this) {
		OverlappingComponents.Remove(OtherComp);
	}
}

#pragma endregion

#pragma region Basic Properties

FString ABuilding::GetName() {
	return BuildingName;
}
FString ABuilding::GetType() {
	return BuildingName;
}
float ABuilding::GetHealth(){
	return Health;
}
float ABuilding::GetMaxHealth() {
	return MaxHealth;
}

#pragma endregion

#pragma region widget properties

FString ABuilding::GetDescription() {
	return Description;
}

void ABuilding::SetDescription(FString desc) {
	Description = desc;
}

FString ABuilding::GetHumanName() {
	return BuildingName;
}

FString ABuilding::GetBuildCostAsUIString() {
	FString CostListString = "";

	for (int32 i = 0; i < BuildCost.Num(); i++) {
		CostListString += FString::SanitizeFloat(BuildCost[i]->Amount) + "x " + BuildCost[i]->GetResourceType() + "   ";
	}
	return CostListString;
}

#pragma endregion

#pragma region build costs

TArray<UResourceCost*> ABuilding::GetBuildCost() {
	return BuildCost;
}

void ABuilding::SetBuildCosts(TArray<UResourceCost*> costList) {
	BuildCost = costList;
}

void ABuilding::SetResearchCosts(TArray<UResearcher*> costList) {
	ResearchCost = costList;
}
#pragma endregion

#pragma region Building Placement

void ABuilding::SetMeshOnValidPlacement() {
	if (GetIsValidPlacement()) {
		Box->SetStaticMesh(BuildingMesh);
	}
	else {
		Box->SetStaticMesh(FailedBuildingMesh);
	}
}

void ABuilding::CheckIsValidPlacement() {
	for (int32 i = 0; i < OverlappingComponents.Num(); i++) {
		Debug(OverlappingComponents[i]->GetName());
		
		if (
			OverlappingComponents[i]->GetName() == "UnitBody" || OverlappingComponents[i]->GetName() == "CollisionCylinder" || // unit is in the way
			OverlappingComponents[i]->GetName() == "BuildingBody" || // building is in the way
			OverlappingComponents[i]->GetName() == "ResourceBody" // Resource Is in the way
			)
		{
			SetIsValidPlacement(false);
			return; // return with fail
		}
	}

	if (RadiusPlaceRules) {
		//check if current location is within distance radius of another building
		APController* pCon = Cast<APController>(GetPlayerController());

		for (int32 i = 0; i < pCon->OwnedBuildings.Num(); i++) {
			ABuilding* building = Cast<ABuilding>(pCon->OwnedBuildings[i]);
			if (building->BuildingType == GetRadiusPlaceActor()) {
				Debug(FString::SanitizeFloat(FVector::Dist(this->GetActorLocation(), pCon->OwnedBuildings[i]->GetActorLocation())));
				
				if (FVector::Dist(this->GetActorLocation(), pCon->OwnedBuildings[i]->GetActorLocation()) > GetRadiusPlaceAmount()) { // is not close enough
					
					SetIsValidPlacement(false);
					return;
				}
			}
		}
	}

	SetIsValidPlacement(true);
}

void ABuilding::SetRadiusPlaceRules(bool value) {
	RadiusPlaceRules = value;
}

bool ABuilding::GetIsRadiusPlaceRule() {
	return RadiusPlaceRules;
}

void ABuilding::SetRadiusPlaceActor(TEnumAsByte<EAvailableBuildings::EAvailableBuildings> value) {
	RadiusPlaceActor = value;
}

TEnumAsByte<EAvailableBuildings::EAvailableBuildings> ABuilding::GetRadiusPlaceActor(){
	return RadiusPlaceActor;
}

void ABuilding::SetRadiusPlaceAmount(float value) {
	RadiusPlaceAmount = value;
}

float ABuilding::GetRadiusPlaceAmount() {
	return RadiusPlaceAmount;
}

void ABuilding::SetIsValidPlacement(bool valid) {
	CanPlace = valid;
}

bool ABuilding::GetIsValidPlacement() {
	return CanPlace;
}

bool ABuilding::SpecialSpawnConditionsMet() {

	if (APController* pCon = Cast<APController>(control)) {

		if (this->BuildingType == EAvailableBuildings::B_FarmLand) {
			//if a Farm is not made (ie email) then this can not be placed ever
			for (int32 i = 0; i < pCon->OwnedBuildings.Num(); i++) {
				if (ABuilding* building = Cast<ABuilding>(pCon->OwnedBuildings[i])) {
					if (building->BuildingType == EAvailableBuildings::B_Farm) {
						return true; //found farm
					}
				}
			}
			return false; // didnt find farm
		}
	}


	return true;
}

void ABuilding::PlaceBuilding() {
	this->SetBuildingAsPlaced();	

	this->SetBuildingState(EBuildStates::BS_Constructing1);
	this->SetActorLocation(this->GetActorLocation());
	this->SetBuildingOwner(EBuildingOwnerships::EBuildingOwnership::BO_Player);
	
	this->SetActorTickInterval(1);

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

#pragma region Depletable Region

void ABuilding::SetIsDepletableResourceBuilding(bool val) {
	IsDepletableResourceBuilding = val;
}

bool ABuilding::GetIsDepletableResourceBuilding() {
	return IsDepletableResourceBuilding;
}

void ABuilding::SetupDepletableResource(UObject* resource) {
	DepletableResource = NewObject<UResourceCost>();
	DepletableResource = Cast<UResourceCost>(resource);
}

float ABuilding::GetCurrentDepletableResource() {
	return Cast<UResourceCost>(DepletableResource)->Amount;
}

void ABuilding::AffectCurrentDepletableResource(float amount, bool IsAdd) {
	if (IsAdd) Cast<UResourceCost>(DepletableResource)->Amount += amount;
	else Cast<UResourceCost>(DepletableResource)->Amount -= amount;	

	UResourceCost* rCost = Cast<UResourceCost>(DepletableResource);
	if (rCost->Amount <= 0) {
		SetIsDepletableResourceDepleted();
	}
}

bool ABuilding::GetIsDepletableResourceDepleted() {
	return IsDepletableResourceDepleted;
}

void ABuilding::SetIsDepletableResourceDepleted(bool val) {
	IsDepletableResourceDepleted = val;
}

float ABuilding::RemoveAmountFromDepletableResource(float amount) {
	UResourceCost* resource = Cast<UResourceCost>(DepletableResource);

	if (resource->Amount < amount) {
		amount = resource->Amount;
	}
	resource->Amount -= amount;
	
	if (resource->Amount <= 0) {
		this->SetBuildingState(EBuildStates::BS_Depleted);
	}

	return amount;
}
#pragma endregion

#pragma region Researchable

TArray<UResearcher*> ABuilding::GetResearchList() {
	return ResearchObject;
}

void ABuilding::SetResearchObjects(TArray<UResearcher*> researchList) {
	ResearchObject = researchList;
}

FString ABuilding::GetResearchCostAsUIString(FString name) {
	UResearcher* chosenResearch = GetResearchItemByName(name);
	
	FString CostListString = "";

	for (int32 i = 0; i < chosenResearch->ResearchCost.Num(); i++) {
		CostListString += FString::SanitizeFloat(chosenResearch->ResearchCost[i]->Amount) + "x " + chosenResearch->ResearchCost[i]->GetResourceType() + "   ";
	}
	return CostListString;
}

FString ABuilding::GetResearchDescription(FString name) {
	UResearcher* chosenResearch = GetResearchItemByName(name);
	return chosenResearch->Description;
}

UResearcher* ABuilding::GetResearchItemByName(FString name) {
	for (int32 i = 0; i < ResearchObject.Num(); i++) {
		if (name == ResearchObject[i]->GetResearchName()) {
			return ResearchObject[i];
		}
	}
	return nullptr;
}

bool ABuilding::GetIsResearchBuilding() {
	return CanResearch;
}

void ABuilding::SetIsResearchBuilding(bool val) {
	CanResearch = val;
}

void ABuilding::BeginResearching(FString Name) {
	UResearcher* thisResearch = nullptr;
	APController* pCon = Cast<APController>(control);

	for (int32 i = 0; i < ResearchObject.Num(); i++) {
		Debug(ResearchObject[i]->GetResearchName());
		if (ResearchObject[i]->GetResearchName() == Name) {
			thisResearch = ResearchObject[i];
			break;
		}
	}

	if (thisResearch == nullptr) {
		Debug("Found no research item of name" + Name);
		return;
	}

	if (!pCon->resources->CanAffordResourceList(thisResearch->ResearchCost)) {
		Debug("Can not afford research");
		return;
	}

	pCon->resources->AffectResouceListOnCounter(thisResearch->ResearchCost, false); // remove resource from player controller
	CurrentlyResearchingObject = thisResearch;
	CurrentlyResearchingObject->SetHasStarted(true);
	CurrentlyResearching = true;

	Debug("Started Researching");
}

void ABuilding::ResearchTick(float DeltaTime) {
	CurrentlyResearchingObject->UpdateResearch(DeltaTime);
	Debug("ResearchTick");
	if (CurrentlyResearchingObject->GetIsFinished()) {
		//show screen to say completed
		Debug("Finished Researching " + CurrentlyResearchingObject->Name);
		CurrentlyResearching = false;

		Debug(CurrentlyResearchingObject->Name);
		Debug(CurrentlyResearchingObject->Description);		

		APController* pCon = Cast<APController>(control);

		pCon->AddToResearchList(CurrentlyResearchingObject);
		Debug("Added to Players completion list");
	}
}



#pragma endregion

#pragma region Utils

ABuilding* ABuilding::FindOrSpawnBuilding(TEnumAsByte<EAvailableBuildings::EAvailableBuildings> building, bool Find, UWorld* world) {

	switch (building) {

	case EAvailableBuildings::EAvailableBuildings::B_Barracks:
		if (Find) return NewObject<ABarracks>();
		else return world->SpawnActor<ABarracks>();		

	case EAvailableBuildings::EAvailableBuildings::B_Storage:
		if (Find) return NewObject<AStorage>();
		else return world->SpawnActor<AStorage>();
		

	case EAvailableBuildings::EAvailableBuildings::B_SawMill:
		if (Find) return NewObject<ASawMill>();
		else return world->SpawnActor<ASawMill>();
		

	case EAvailableBuildings::EAvailableBuildings::B_Farm:
		if (Find) return NewObject<AFarm>();
		else return world->SpawnActor<AFarm>();


	case EAvailableBuildings::EAvailableBuildings::B_FarmLand:
		if (Find) return NewObject<AFarmField>();
		else return world->SpawnActor<AFarmField>();

	case EAvailableBuildings::EAvailableBuildings::B_PhylosopherCave:
		if (Find) return NewObject<APhylosopherCave>();
		else return world->SpawnActor<APhylosopherCave>();

	case EAvailableBuildings::EAvailableBuildings::B_None:
		return nullptr;

	default:
		return nullptr;
	}
}

void ABuilding::SetMeshOnState() {
	if (CurrentBuildingState == EBuildStates::BS_Complete) {
		Box->SetStaticMesh(BuildingMesh);
	}
	if (CurrentBuildingState == EBuildStates::BS_Constructing1) {
		Box->SetStaticMesh(Stage1Construction);
	}
	if (CurrentBuildingState == EBuildStates::BS_Constructing2) {
		Box->SetStaticMesh(Stage2Construction);
	}
	if (CurrentBuildingState == EBuildStates::BS_Constructing3) {
		Box->SetStaticMesh(Stage3Construction);
	}
	if (CurrentBuildingState == EBuildStates::BS_Damaged1) {
		Box->SetStaticMesh(Stage1Damage);
	}
	if (CurrentBuildingState == EBuildStates::BS_Damaged2) {
		Box->SetStaticMesh(Stage2Damage);
	}
	if (CurrentBuildingState == EBuildStates::BS_Damaged3) {
		Box->SetStaticMesh(Stage3Damage);
	}
}

#pragma endregion

void ABuilding::Debug(FString string) {
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, string);
}
