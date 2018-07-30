// Fill out your copyright notice in the Description page of Project Settings.

#include "Coal.h"
#include "Components/StaticMeshComponent.h"
#include "ConstructorHelpers.h"
#include "PlayerResource/EResource.h"
#include "Engine/Engine.h"
#include "Engine/StaticMesh.h"

// Sets default values
ACoal::ACoal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/*static ConstructorHelpers::FObjectFinder<UStaticMesh> BoxAsset(TEXT("/Game/Models/Debug/BasicTree.BasicTree"));
	if (BoxAsset.Succeeded()) {
		resourceMesh->SetStaticMesh(BoxAsset.Object);
	}*/

	ResourceType = EResources::R_Coal;
}

// Called when the game starts or when spawned
void ACoal::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACoal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

