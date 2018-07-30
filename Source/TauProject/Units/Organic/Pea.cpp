// Fill out your copyright notice in the Description page of Project Settings.

#include "Pea.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Runtime/Engine/Classes/Animation/AnimBlueprint.h"
#include "ConstructorHelpers.h"
#include "Engine/Engine.h"
#include "Engine/StaticMesh.h"
#include "PlayerResource/ResourceCost.h"


//#include "Weapons/Weapon.h"
//#include "Weapons/Swords/BasicSword.h"

// Sets default values
APea::APea()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	float _capradius = 60.f;
	float _capheight = 96.0f;

	GetCapsuleComponent()->InitCapsuleSize(_capradius, _capheight);
	GetCapsuleComponent()->bGenerateOverlapEvents = true;

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

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeleMesh(TEXT("/Game/Models/Units/Pea/IdlePea_Anim.IdlePea_Anim"));
	if (SkeleMesh.Succeeded()) CurrentMesh->SetSkeletalMesh(SkeleMesh.Object);

	static ConstructorHelpers::FObjectFinder<UAnimBlueprint> AnimObj(TEXT("/Game/Blueprints/AnimationBp/Pea_Anim_Bp.Pea_Anim_Bp"));
	if (AnimObj.Succeeded()) CurrentMesh->SetAnimInstanceClass(AnimObj.Object->GeneratedClass);
	
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction when moving
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
	
	this->AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;	

	//set unit type
	ThisUnitType = EUnitList::UL_Pea;
	
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


