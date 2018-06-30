// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerSelection.h"
#include "Utils/DetailsStringLibrary.h"
#include "Controller/PController.h"

UPlayerSelection::UPlayerSelection() {

}

UPlayerSelection::UPlayerSelection(APlayerController * controller) {
	controllerClass = controller;
}


#pragma region Getters

FString UPlayerSelection::GetName() {
	return Name;
}

float UPlayerSelection::GetHealth() {
	return Health;
}

float UPlayerSelection::GetMaxHealth() {
	return MaxHealth;
}

float UPlayerSelection::GetHealthAsPercent() {
	return HealthAsPercent;
}

FString UPlayerSelection::GetActivity() {
	return Activity;
}

FString UPlayerSelection::GetType() {
	return Type;
}

FString UPlayerSelection::GetHealthOfMax() {
	return FString::SanitizeFloat(GetHealth()) + "(" + FString::SanitizeFloat(GetMaxHealth()) + ")";
}

AActor* UPlayerSelection::GetActorClass() {
	return ActorClass;
}

#pragma endregion

#pragma region Setters
void UPlayerSelection::SetName(FString name) {
	Name = name;
}
void UPlayerSelection::SetHealth(float health) {
	Health = health;
}
void UPlayerSelection::SetMaxHealth(float health) {
	MaxHealth = health;
}
void UPlayerSelection::SetHealthAsPercentage(float health) {
	HealthAsPercent = health;
}
void UPlayerSelection::SetActivity(FString activity) {
	Activity = activity;
}
void UPlayerSelection::SetType(FString type) {
	Type = type;
}
void UPlayerSelection::SetActorClass(AActor* actor) {
	ActorClass = actor;
}
#pragma endregion

#pragma region Setups

void UPlayerSelection::SetSelection(FString name, float health, float maxHealth, TEnumAsByte<EUnitInstructions::EUnitInstruction> activity, FString type, AActor* actor) {
	SetName(name);
	SetHealth(health);
	SetMaxHealth(maxHealth);
	SetHealthAsPercentage(CalculatePercantage(health, maxHealth));
	SetActivity(GetActivityFromState(activity));
	SetType(type);
	SetActorClass(actor);
}
void UPlayerSelection::SetSelection(FString name, float health, float maxHealth, TEnumAsByte<EBuildStates::EBuildingStates> activity, FString type, AActor* actor) {
	SetName(name);
	SetHealth(health);
	SetMaxHealth(maxHealth);
	SetHealthAsPercentage(CalculatePercantage(health, maxHealth));
	SetActivity(GetActivityFromState(activity));
	SetType(type);
	SetActorClass(actor);
}
void UPlayerSelection::SetSelection(FString name, float health, float maxHealth, TEnumAsByte<EResources::All> activity, FString type, AActor* actor) {
	SetName(name);
	SetHealth(health);
	SetMaxHealth(maxHealth);
	SetHealthAsPercentage(CalculatePercantage(health, maxHealth));
	SetActivity(GetActivityFromState(activity));
	SetType(type);
	SetActorClass(actor);
}

#pragma endregion

#pragma region Utils

float UPlayerSelection::CalculatePercantage(float num, float max) {
	return  num / max;
}

FString UPlayerSelection::GetActivityFromState(TEnumAsByte<EUnitInstructions::EUnitInstruction> activity) {
	if (APController* control = Cast<APController>(controllerClass)) {

		switch (activity) {
		case EUnitInstructions::UI_Attack:
			return control->ActivityLibrary->FightingActivity();

		case EUnitInstructions::UI_Construct:
			return control->ActivityLibrary->ConstructingActivity();

		case EUnitInstructions::UI_DropOff:
			return control->ActivityLibrary->DroppingOffActivity();

		case EUnitInstructions::UI_Gather:
			return control->ActivityLibrary->GatheringActivity();

		case EUnitInstructions::UI_GatherBuilding:
			return control->ActivityLibrary->GatheringActivity();

		case EUnitInstructions::UI_Move:
			return control->ActivityLibrary->MovingActivity();

		case EUnitInstructions::UI_Multiple:
			return "Multiple";

		case EUnitInstructions::UI_None:
			return control->ActivityLibrary->NoneActivity();

		default:
			return "Doing something";
		}
	}
	return "";
}

FString UPlayerSelection::GetActivityFromState(TEnumAsByte<EBuildStates::EBuildingStates> activity) {
	if (APController* control = Cast<APController>(controllerClass)) {
		switch (activity) {
		case EBuildStates::BS_Complete:
			return "Good to Go";

		case EBuildStates::BS_Constructing1:
			return "Planning";

		case EBuildStates::BS_Constructing2:
			return "Scaffolded";

		case EBuildStates::BS_Constructing3:
			return "Last stretch";

		case EBuildStates::BS_Damaged1:
			return "Ouch";

		case EBuildStates::BS_Damaged2:
			return "Double Ouch";

		case EBuildStates::BS_Damaged3:
			return "Abandon Building";

		case EBuildStates::BS_Depleted:
			return "Empty";

		case EBuildStates::BS_Destroyed:
			return "Bleh";

		case EBuildStates::BS_Placed:
			return "Placed";

		case EBuildStates::BS_Spawning:
			return "Spawning";

		default:
			return "Building";
		}
	}
	return "A Building";
}

FString UPlayerSelection::GetActivityFromState(TEnumAsByte<EResources::All> activity) {
	if (APController* control = Cast<APController>(controllerClass)) {
		switch (activity) {
		case EResources::All::E_CopperSword:
			return "Copper Sword";

		case EResources::All::E_IronSword:
			return "Iron Sword";

		case EResources::All::E_SteelSword:
			return "Steel Sword";

		case EResources::All::R_Alcohol:
			return "Alcohol";

		case EResources::All::R_Bread:
			return "Bread";

		case EResources::All::R_Coal:
			return "Coal";

		case EResources::All::R_Copper:
			return "Copper";

		case EResources::All::R_CopperOre:
			return "Copper Ore";

		case EResources::All::R_Food:
			return "Food";

		case EResources::All::R_Iron:
			return "Iron";

		case EResources::All::R_IronOre:
			return "Iron Ore";

		case EResources::All::R_Lumber:
			return "Lumber";

		case EResources::All::R_Planks:
			return "Planks";

		case EResources::All::R_Peatanium:
			return "Peatanium";

		case EResources::All::R_Stone:
			return "Stone";

		case EResources::All::R_Water:
			return "Water";

		case EResources::All::R_Wheat:
			return "Wheat";

		case EResources::All::R_Steel:
			return "Steel";

		default:
			return "Resource";
		}
	}
	return "";
}

#pragma endregion