// Fill out your copyright notice in the Description page of Project Settings.

#include "Sprout.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "ConstructorHelpers.h"
#include "Engine/Engine.h"
#include "Engine/StaticMesh.h"
#include "PlayerResource/ResourceCost.h"

// Sets default values
ASprout::ASprout()
{
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

	ThisUnitType = EUnitList::UL_Sprout;
	
	//stats
	CriticalChance = 1;
	CriticalMultiplier = 1.2;

	Health = 100;
	MaxHealth = 100;
	Attack = 7;

	CanBuild = true;
	BuildRate = 57;
}

// Called when the game starts or when spawned
void ASprout::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void ASprout::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ASprout::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

