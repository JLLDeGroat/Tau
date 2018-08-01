// Fill out your copyright notice in the Description page of Project Settings.

#include "Copper.h"
#include "Components/StaticMeshComponent.h"
#include "ConstructorHelpers.h"
#include "PlayerResource/EResource.h"
#include "Engine/Engine.h"
#include "Engine/StaticMesh.h"

ACopper::ACopper() {

	static ConstructorHelpers::FObjectFinder<UStaticMesh> BoxAsset(TEXT("/Game/Models/Debug/ResourceBlock.ResourceBlock"));
	if (BoxAsset.Succeeded()) {
		resourceMesh->SetStaticMesh(BoxAsset.Object);
	}
	ResourceType = EResources::R_CopperOre;
}

// Called when the game starts or when spawned
void ACopper::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ACopper::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

