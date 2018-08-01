// Fill out your copyright notice in the Description page of Project Settings.

#include "IronForge.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "ConstructorHelpers.h"
#include "Buildings/Building.h"
#include "Engine.h"
#include "Engine/Engine.h"

// Sets default values
AIronForge::AIronForge()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BoxAsset(TEXT("/Game/Models/Debug/BasicHouse.BasicHouse"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> FailedBoxAsset(TEXT("/Game/Models/Debug/BasicHouse_OL.BasicHouse_OL"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ConstructionStage1Asset(TEXT("/Game/Models/Debug/BasicHouse_UB.BasicHouse_UB"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ConstructionStage2Asset(TEXT("/Game/Models/Debug/BasicHouse_UB2.BasicHouse_UB2"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ConstructionStage3Asset(TEXT("/Game/Models/Debug/BasicHouse_UB2.BasicHouse_UB2"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> DamageStage1Asset(TEXT("/Game/Models/Debug/BasicHouse_UB.BasicHouse_UB"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> DamageStage2Asset(TEXT("/Game/Models/Debug/BasicHouse_UB.BasicHouse_UB"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> DamageStage3Asset(TEXT("/Game/Models/Debug/BasicHouse_UB.BasicHouse_UB"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> DepletedAsset(TEXT("/Game/Models/Debug/BasicHouse_UB.BasicHouse_UB"));

	if (BoxAsset.Succeeded()) {
		BuildingMesh = BoxAsset.Object;
		Box->SetStaticMesh(BuildingMesh);
		Box->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		Box->SetWorldScale3D(FVector(1.5f));
		Box->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Overlap);
		Box->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
		Box->bGenerateOverlapEvents = true;
	}

	if (FailedBoxAsset.Succeeded())  FailedBuildingMesh = FailedBoxAsset.Object;
	else GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Black, TEXT("Failed to get Barracks Overlapping Mesh, Will break"));

	if (ConstructionStage1Asset.Succeeded()) Stage1Construction = ConstructionStage1Asset.Object;
	else GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Black, TEXT("Failed to get Barracks Cons stage1 mesh, Will break"));

	if (ConstructionStage2Asset.Succeeded()) Stage2Construction = ConstructionStage2Asset.Object;
	else GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Black, TEXT("Failed to get Barracks Cons stage1 mesh, Will break"));

	if (ConstructionStage2Asset.Succeeded()) Stage3Construction = ConstructionStage3Asset.Object;
	else GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Black, TEXT("Failed to get Barracks Cons stage1 mesh, Will break"));

	if (DamageStage1Asset.Succeeded()) Stage1Damage = DamageStage1Asset.Object;
	else GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Black, TEXT("Failed to get Barracks Cons stage1 mesh, Will break"));

	if (DamageStage2Asset.Succeeded()) Stage2Damage = DamageStage2Asset.Object;
	else GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Black, TEXT("Failed to get Barracks Cons stage1 mesh, Will break"));

	if (DamageStage3Asset.Succeeded()) Stage3Damage = DamageStage3Asset.Object;
	else GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Black, TEXT("Failed to get Barracks Cons stage1 mesh, Will break"));

	if (DepletedAsset.Succeeded()) DepletedMesh = DepletedAsset.Object;
	else Debug("Failed To Get Depleted Mesh");

	Box->OnComponentBeginOverlap.AddDynamic(this, &AIronForge::StartOverlap);
	Box->OnComponentEndOverlap.AddDynamic(this, &AIronForge::EndOverlap);

	IsPlaced = false;

	BuildingType = EAvailableBuildings::B_IronForge;	
	PostConstructionMethod();
}

// Called when the game starts or when spawned
void AIronForge::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AIronForge::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
