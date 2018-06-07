// Fill out your copyright notice in the Description page of Project Settings.

#include "Storage.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "ConstructorHelpers.h"
#include "Buildings/Building.h"
#include "Engine.h"
#include "Engine/Engine.h"

// Sets default values
AStorage::AStorage()
{
	Box = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BuildingBody"));
	Box->SetupAttachment(RootComponent);

	//StaticMesh'/Game/Models/Debug/BasicHouse_UB.BasicHouse_UB'
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BoxAsset(TEXT("/Game/Models/Debug/BasicHouse.BasicHouse"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> FailedBoxAsset(TEXT("/Game/Models/Debug/BasicHouse_OL.BasicHouse_OL"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ConstructionStage1Asset(TEXT("/Game/Models/Debug/BasicHouse_UB.BasicHouse_UB"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ConstructionStage2Asset(TEXT("/Game/Models/Debug/BasicHouse_UB2.BasicHouse_UB2"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ConstructionStage3Asset(TEXT("/Game/Models/Debug/BasicHouse_UB2.BasicHouse_UB2"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> DamageStage1Asset(TEXT("/Game/Models/Debug/BasicHouse_UB.BasicHouse_UB"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> DamageStage2Asset(TEXT("/Game/Models/Debug/BasicHouse_UB.BasicHouse_UB"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> DamageStage3Asset(TEXT("/Game/Models/Debug/BasicHouse_UB.BasicHouse_UB"));

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
	else GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Black, TEXT("Failed to get Storage Overlapping Mesh, Will break"));

	if (ConstructionStage1Asset.Succeeded()) Stage1Construction = ConstructionStage1Asset.Object;
	else GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Black, TEXT("Failed to get Storage Cons stage1 mesh, Will break"));

	if (ConstructionStage2Asset.Succeeded()) Stage2Construction = ConstructionStage2Asset.Object;
	else GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Black, TEXT("Failed to get Storage Cons stage1 mesh, Will break"));

	if (ConstructionStage2Asset.Succeeded()) Stage3Construction = ConstructionStage3Asset.Object;
	else GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Black, TEXT("Failed to get Storage Cons stage1 mesh, Will break"));

	if (DamageStage1Asset.Succeeded()) Stage1Damage = DamageStage1Asset.Object;
	else GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Black, TEXT("Failed to get Storage Cons stage1 mesh, Will break"));

	if (DamageStage2Asset.Succeeded()) Stage2Damage = DamageStage2Asset.Object;
	else GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Black, TEXT("Failed to get Storage Cons stage1 mesh, Will break"));

	if (DamageStage3Asset.Succeeded()) Stage3Damage = DamageStage3Asset.Object;
	else GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Black, TEXT("Failed to get Storage Cons stage1 mesh, Will break"));


	CanStore = true;

	Health = 1;
	MaxHealth = 350;


	PrimaryActorTick.bCanEverTick = true;
	SetActorTickInterval(1);

	SetBuildCosts();
}

// Called when the game starts or when spawned
void AStorage::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void AStorage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!IsPlaced) {
		CheckIsValidPlacement();
		SetStorageMesh(IsPlaced);
	}
	else {
		SetMeshOnState();
	}
}


#pragma region Overlaps

void AStorage::StartOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	FString sentence = "Actor: " + OtherActor->GetName() + " Component: " + OtherComp->GetName();
	if (!IsPlaced && OtherActor != this) {
		OverlappingComponents.Add(OtherComp);
	}
}

void AStorage::EndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	if (!IsPlaced && OtherActor != this) {
		OverlappingComponents.Remove(OtherComp);
	}
}

#pragma endregion

#pragma region Build Costs

void AStorage::SetBuildCosts() {
	UResourceCost* cost1 = NewObject<UResourceCost>();
	UResourceCost* cost2 = NewObject<UResourceCost>();

	cost1->res = EResources::R_Lumber;
	cost1->Amount = 4;

	cost2->res = EResources::R_Stone;
	cost2->Amount = 2;

	BuildCost.Add(cost1);
	BuildCost.Add(cost2);
}

#pragma endregion

#pragma region Placing Building

void AStorage::SetStorageMesh(bool placed) {

	if (!placed) {
		if (GetIsValidPlacement()) {
			Box->SetStaticMesh(BuildingMesh);
		}
		else {
			Box->SetStaticMesh(FailedBuildingMesh);
		}
	}
}

#pragma endregion

#pragma region Building Mesh changes

void AStorage::SetMeshOnState() {
	if (CurrentBuildingState == EBuildStates::BS_Complete) {
		Box->SetStaticMesh(BuildingMesh);
	}
	if (CurrentBuildingState == EBuildStates::BS_Constructing1) {
		Box->SetStaticMesh(Stage1Construction);
	}
	if (CurrentBuildingState == EBuildStates::BS_Constructing2) {
		Box->SetStaticMesh(Stage2Construction);
	}
	if (CurrentBuildingState == EBuildStates::BS_Constructing3) {
		Box->SetStaticMesh(Stage3Construction);
	}
	if (CurrentBuildingState == EBuildStates::BS_Damaged1) {
		Box->SetStaticMesh(Stage1Damage);
	}
	if (CurrentBuildingState == EBuildStates::BS_Damaged2) {
		Box->SetStaticMesh(Stage2Damage);
	}
	if (CurrentBuildingState == EBuildStates::BS_Damaged3) {
		Box->SetStaticMesh(Stage3Damage);
	}
}
#pragma endregion
