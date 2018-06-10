// Fill out your copyright notice in the Description page of Project Settings.

#include "Pea.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "ConstructorHelpers.h"
#include "Engine/Engine.h"
#include "Engine/StaticMesh.h"
#include "PlayerResource/ResourceCost.h"

// Sets default values
APea::APea()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	GetCapsuleComponent()->InitCapsuleSize(42.f, 42.0f);
	GetCapsuleComponent()->bGenerateOverlapEvents = true;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;


	UStaticMeshComponent* Box = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("UnitBody"));
	Box->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> BoxAsset(TEXT("/Game/Models/Debug/Box.Box"));
	if (BoxAsset.Succeeded()) {
		Box->SetStaticMesh(BoxAsset.Object);
		Box->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		Box->SetWorldScale3D(FVector(.5f));
		Box->bGenerateOverlapEvents = true;
	}

	this->AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;


	LineOfSight = 220;
	AttackRange = 140;

	//stats
	ThisUnitType = EUnitList::UL_Pea;


	CriticalChance = 1;
	CriticalMultiplier = 1.2;

	Health = 100;
	MaxHealth = 100;
	Attack = 7;

	SpawnTime = 7;


	UResourceCost* c1 = NewObject<UResourceCost>();
	UResourceCost* c2 = NewObject<UResourceCost>();

	c1->res = EResources::R_Bread;
	c1->Amount = 1;
	c2->res = EResources::R_Iron;
	c2->Amount = 1;

	BuildCost.Add(c1);
	BuildCost.Add(c2);

}

// Called when the game starts or when spawned
void APea::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


