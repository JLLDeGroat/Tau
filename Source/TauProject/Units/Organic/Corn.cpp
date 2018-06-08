// Fill out your copyright notice in the Description page of Project Settings.

#include "Corn.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Units/UnitInventory.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "ConstructorHelpers.h"
#include "Engine/Engine.h"

// Sets default values
ACorn::ACorn()
{

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

	//this->AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;


	LineOfSight = 190;
	AttackRange = 100;

	//stats

	CriticalChance = 1;
	CriticalMultiplier = 1.2;

	Health = 100;
	MaxHealth = 100;
	Attack = 7;


	CanHarvest = true;
	HarvestRate = 1;

	
}

// Called when the game starts or when spawned
void ACorn::BeginPlay()
{
	Super::BeginPlay();
	
	//inventory
	Inventory = NewObject<UUnitInventory>();
	Inventory->MaxResourceCount = 6;
}

// Called every frame
void ACorn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACorn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

