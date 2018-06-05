// Fill out your copyright notice in the Description page of Project Settings.

#include "Building.h"
#include "Components/StaticMeshComponent.h"
#include "Buildings/BuildingStructs.h"
#include "Engine/Engine.h"

// Sets default values
ABuilding::ABuilding()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

	Debug("Building Health: " + FString::SanitizeFloat(Health));

	if (IsPlaced) ChangeStateOnHealthChange();
}

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

#pragma endregion

#pragma region Building States

void ABuilding::SetBuildingState(TEnumAsByte<EBuildStates::EBuildingStates> state) {
	CurrentBuildingState = state;
}

TEnumAsByte<EBuildStates::EBuildingStates> ABuilding::GetCurrentState() {
	return CurrentBuildingState;
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

void ABuilding::Debug(FString string) {
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, string);
}
