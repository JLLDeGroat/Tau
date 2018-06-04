// Fill out your copyright notice in the Description page of Project Settings.

#include "Pea.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "ConstructorHelpers.h"
#include "Engine/Engine.h"

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

	CriticalChance = 1;
	CriticalMultiplier = 1.2;

	Health = 100;
	MaxHealth = 100;
	Attack = 7;
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


