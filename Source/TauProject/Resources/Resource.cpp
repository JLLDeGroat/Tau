// Fill out your copyright notice in the Description page of Project Settings.

#include "Resource.h"
#include "Units/UnitStructs.h"

// Sets default values
AResource::AResource()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AResource::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AResource::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

#pragma region Getters

float AResource::GetCurrentResourceCount() {
	return ResourceCount;
}

TEnumAsByte<EUnitInventory::Resource> AResource::GetResourceType() {
	return ResourceType;
}

#pragma endregion

#pragma region Setters


void AResource::SetIsDepleted() {
	IsDepleted = true;
}

#pragma endregion


float AResource::RemoveAmountFromCount(float amount) {
	if (GetCurrentResourceCount() < amount) {
		amount = GetCurrentResourceCount();
	}
	ResourceCount -= amount;
	AfterRemovedChecks();
	return amount;
}

void AResource::AfterRemovedChecks() {
	if (ResourceCount <= 0) {
		SetIsDepleted();
		this->Destroy();
	}
}



