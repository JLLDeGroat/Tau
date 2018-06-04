// Fill out your copyright notice in the Description page of Project Settings.

#include "Iron.h"
#include "Components/StaticMeshComponent.h"
#include "ConstructorHelpers.h"
#include "Engine/Engine.h"

// Sets default values
AIron::AIron()
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

}

// Called when the game starts or when spawned
void AIron::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AIron::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

