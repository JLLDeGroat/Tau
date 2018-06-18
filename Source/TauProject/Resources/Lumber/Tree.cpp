// Fill out your copyright notice in the Description page of Project Settings.

#include "Tree.h"
#include "Components/StaticMeshComponent.h"
#include "ConstructorHelpers.h"
#include "PlayerResource/EResource.h"
#include "Engine/Engine.h"
#include "Engine/StaticMesh.h"

// Sets default values
ATree::ATree()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	UStaticMeshComponent* Box = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ResourceBody"));
	Box->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> BoxAsset(TEXT("/Game/Models/Debug/ResourceBlock.ResourceBlock"));
	if (BoxAsset.Succeeded()) {
		Box->SetStaticMesh(BoxAsset.Object);
		Box->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		Box->SetWorldScale3D(FVector(.5f));
		Box->bGenerateOverlapEvents = true;
	}

	ResourceType = EResources::R_Lumber;
	ResourceCount = SetInitialResources(ResourceType);

}

// Called when the game starts or when spawned
void ATree::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ATree::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}





