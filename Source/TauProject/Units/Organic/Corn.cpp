// Fill out your copyright notice in the Description page of Project Settings.

#include "Corn.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Units/UnitInventory.h"
#include "Components/SkeletalMeshComponent.h"
#include "Runtime/Engine/Classes/Animation/AnimBlueprint.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "ConstructorHelpers.h"
#include "Engine/Engine.h"

// Sets default values
ACorn::ACorn()
{

	float _capradius = 60.f;
	float _capheight = 96.0f;

	GetCapsuleComponent()->InitCapsuleSize(_capradius, _capheight);
	GetCapsuleComponent()->bGenerateOverlapEvents = true;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
	

	CurrentMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("UnitBody"));
	CurrentMesh->SetupAttachment(RootComponent);
	CurrentMesh->SetRelativeRotation(FRotator(0, 90, 0)); // rotate mesh to fit direction
	CurrentMesh->SetRelativeLocation(FVector(0, 0, -100)); // move mesh down to fit in capsule
	CurrentMesh->SetWorldScale3D(FVector(.7f));
	CurrentMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CurrentMesh->bGenerateOverlapEvents = true;
	CurrentMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	CurrentMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);

	selectedDecal->SetRelativeLocation(FVector(0, 0, -_capheight));
	highlightedDecal->SetRelativeLocation(FVector(0, 0, -_capheight));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeleMesh(TEXT("/Game/Models/Units/Corn/Idle_Corn.Idle_Corn"));
	if (SkeleMesh.Succeeded()) CurrentMesh->SetSkeletalMesh(SkeleMesh.Object);

	static ConstructorHelpers::FObjectFinder<UAnimBlueprint> AnimObj(TEXT("/Game/Blueprints/AnimationBp/Corn_Anim_Bp.Corn_Anim_Bp"));
	if (AnimObj.Succeeded()) CurrentMesh->SetAnimInstanceClass(AnimObj.Object->GeneratedClass);

	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction when moving
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	this->AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;


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

