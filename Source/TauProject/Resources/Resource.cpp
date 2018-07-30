// Fill out your copyright notice in the Description page of Project Settings.

#include "Resource.h"
#include "Units/UnitStructs.h"
#include "Components/StaticMeshComponent.h"
#include "ResourceHelpers.h"
#include "ConstructorHelpers.h"
#include "ResourceHelpers.h"
#include "PlayerResource/EResource.h"

// Sets default values
AResource::AResource()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	resourceMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ResourceBody"));
	resourceMesh->SetupAttachment(RootComponent);
	resourceMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Overlap);
	resourceMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	/*
	resourceMesh->bGenerateOverlapEvents = true;
	*/
}

// Called when the game starts or when spawned
void AResource::BeginPlay()
{
	Super::BeginPlay();
	
	UResourceHelpers::SetResourceMinMaxAmount(this);
	UResourceHelpers::SetInitialResourceAmount(this);	
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
	
	UResourceHelpers::CheckIfDepleted(this);

	return amount;
}



