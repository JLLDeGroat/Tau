// Fill out your copyright notice in the Description page of Project Settings.

#include "Resource.h"
#include "Units/UnitStructs.h"
#include "PlayerResource/EResource.h"

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

TEnumAsByte<EResources::All> AResource::GetResourceType() {
	return ResourceType;
}

float AResource::SetInitialResources(TEnumAsByte<EResources::All> resource) {
	float count = FMath::RandRange(100, 501);
	this->ResourceCountOriginal = count;
	return count;
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



