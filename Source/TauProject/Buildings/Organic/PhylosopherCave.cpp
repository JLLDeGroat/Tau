// Fill out your copyright notice in the Description page of Project Settings.

#include "PhylosopherCave.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "ConstructorHelpers.h"
#include "Buildings/Building.h"
#include "Engine.h"
#include "Engine/Engine.h"


APhylosopherCave::APhylosopherCave() {
	Box = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BuildingBody"));
	Box->SetupAttachment(RootComponent);

	//StaticMesh'/Game/Models/Debug/BasicHouse_UB.BasicHouse_UB'
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BoxAsset(TEXT("/Game/Models/Debug/PhylosopherRoom.PhylosopherRoom"));
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
		Box->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn,		   ECollisionResponse::ECR_Overlap);
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

	Box->OnComponentBeginOverlap.AddDynamic(this, &APhylosopherCave::StartOverlap);
	Box->OnComponentEndOverlap.AddDynamic(this, &APhylosopherCave::EndOverlap);

	BuildingName = "Think Tank";
	Description = "The peas come together, and think through the needs and wants that will bring the peas into the future.";
	Health = 1;
	MaxHealth = 1200;

	IsPlaced = false;

	BuildingType = EAvailableBuildings::B_PhylosopherCave;


	//setting build costs
	TArray<UResourceCost*> resCost;
	resCost.Add(NewObject<UResourceCost>()->Setup(EResources::R_Stone, 20));
	//resCost.Add(NewObject<UResourceCost>()->Setup(EResources::R_Iron, 5));
	resCost.Add(NewObject<UResourceCost>()->Setup(EResources::R_Planks, 10));
	SetBuildCosts(resCost);


	//can research
	SetIsResearchBuilding(true);

	//setting research	
	SetupResearchItems();
	SetupBuildingNeedsItem();
	SetupBuildCosts();
}

// Called when the game starts or when spawned
void APhylosopherCave::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APhylosopherCave::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void APhylosopherCave::SetupResearchItems() {
	TArray<UResearcher*> researchList;


	//ORE REFINERY
	UResearcher* oreRefinery = NewObject<UResearcher>();
	oreRefinery->Name = "Ore Refinery";
	oreRefinery->Description = "Learn the way of duplication, your smithee will alt f4 at the right moment allows doubling of smithed ingots";
	oreRefinery->ResearchCost.Add(NewObject<UResourceCost>()->Setup(EResources::R_IronOre, 10));
	oreRefinery->ResearchCost.Add(NewObject<UResourceCost>()->Setup(EResources::R_CopperOre, 10));
	oreRefinery->ResearchTime = 5;

	//IRON FORGE
	UResearcher* ironForge = NewObject<UResearcher>();
	ironForge->Name = "Iron Forge";
	ironForge->Description = "Learn the ways of heating, by debating the best ways of cooking a fish.";
	ironForge->ResearchCost.Add(NewObject<UResourceCost>()->Setup(EResources::R_Bread, 5));
	ironForge->ResearchCost.Add(NewObject<UResourceCost>()->Setup(EResources::R_Copper, 5));
	ironForge->ResearchTime = 5;

	//COPPER FORGE
	UResearcher* copperForge = NewObject<UResearcher>();
	copperForge->Name = "Copper Forge";
	copperForge->Description = "Learn the ways of heating, by debating the best ways of cooking a egg.";
	copperForge->ResearchCost.Add(NewObject<UResourceCost>()->Setup(EResources::R_Bread, 5));
	copperForge->ResearchCost.Add(NewObject<UResourceCost>()->Setup(EResources::R_CopperOre, 5));
	copperForge->ResearchTime = 5;

	//HARVESTING I
	UResearcher* harvestingI = NewObject<UResearcher>();
	harvestingI->Name = "HarvestingI";
	harvestingI->Description = "discussing the hoe, the sickle and the scythe creates new ways of ripping plants from their home";
	harvestingI->ResearchCost.Add(NewObject<UResourceCost>()->Setup(EResources::R_Bread, 5));
	harvestingI->ResearchTime = 5;


	//FINISH
	researchList.Add(ironForge);
	researchList.Add(harvestingI);
	researchList.Add(oreRefinery);
	SetResearchObjects(researchList);
}

void APhylosopherCave::SetupBuildingNeedsItem() {
	TArray<FString> names;
	names.Add("Farm");
	names.Add("Market");
	SetNeededBuildingList(names);
}

void APhylosopherCave::SetupBuildCosts() {
	TArray<UResourceCost*> resCost;
	resCost.Add(NewObject<UResourceCost>()->Setup(EResources::R_Stone, 10));
	resCost.Add(NewObject<UResourceCost>()->Setup(EResources::R_Planks, 15));
	SetBuildCosts(resCost);
}