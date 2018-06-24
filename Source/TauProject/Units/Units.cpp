// Fill out your copyright notice in the Description page of Project Settings.

#include "Units.h"
#include "AI/Navigation/NavigationSystem.h"
#include "Components/SphereComponent.h"
#include "UnitTasks.h"
#include "Buildings/Building.h"
#include "Resources/Resource.h"
#include "Controller/PController.h"
#include "Engine/Engine.h"
#include "EngineUtils.h"

#include "PlayerResource/ResourceCost.h"

#include "Units/Organic/Corn.h"
#include "Units/Organic/Pea.h"
#include "Units/Organic/Sprout.h"

// Sets default values
AUnits::AUnits()
{	
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Unit Sight Component
	SightSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Unit Sight"));	
	SightSphere->SetupAttachment(RootComponent);
	SightSphere->bGenerateOverlapEvents = true;

	//unit attack range
	RangeSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Unit Range"));
	RangeSphere->SetupAttachment(RootComponent);
	RangeSphere->bGenerateOverlapEvents = true;

	SightSphere->OnComponentBeginOverlap.AddDynamic(this, &AUnits::WithinSight);
	SightSphere->OnComponentEndOverlap.AddDynamic(this, &AUnits::OutOfSight);

	RangeSphere->OnComponentBeginOverlap.AddDynamic(this, &AUnits::WithinRangeOfAttack);
	RangeSphere->OnComponentEndOverlap.AddDynamic(this, &AUnits::OutOfRangeOfAttack);
	
	SetActorTickEnabled(true);
	SetActorTickInterval(1);

	LineOfSight = 220;
	AttackRange = 170;
}

// Called when the game starts or when spawned
void AUnits::BeginPlay()
{
	Super::BeginPlay();	
	SightSphere->SetSphereRadius(LineOfSight);
	RangeSphere->SetSphereRadius(AttackRange);	

	UnitTask = NewObject<UUnitTasks>();
}

// Called every frame
void AUnits::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!this->IsDead && this->Health > 0) {

		//FString string = "Ticked " + FString::SanitizeFloat(DeltaTime);
		
		if (bIsAttacking) AttackTick();
		if (IsBuilding) BuildBuilding();
		if (IsHarvesting) HarvestTick();

		if (IsHarvesting) Debug("Is Harvesting");

		if (UnitTask->HasTask()) {
			//Debug(UnitTask->GetFirstTask()->Name);
		}


		if (UnitTask != nullptr && UnitTask->HasTask() && UnitTask->GetFirstTask()->GetInstruction() == EUnitInstructions::UI_Move) IsMovementInstructionComplete();
		if (UnitTask != nullptr && UnitTask->HasTask() && UnitTask->GetFirstTask()->GetInstruction() == EUnitInstructions::UI_Attack) IsAttackInstructionComplete();
		

		if (UnitTask != nullptr && !UnitTask->HasTask()) AttemptToGetAutoTask();
	}
}

#pragma region Overlaps

void AUnits::WithinSight(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	
}

void AUnits::OutOfSight(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	
}

void AUnits::WithinRangeOfAttack(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {	
	if (OtherActor != this) {
		if (HitInstructedBuilding(OtherActor)) {
			StartBuilding();
		}
			
			
		if(HasFoundAnEnemy(OtherActor, OtherComp)) {
			NewEnemyHasEnteredAttackRange(OtherActor);

			if (this->UnitOwner == EUnitOwnerships::UO_Player) {
				Debug("Is player");
			}

			
			if (HasNoTaskAndFoundEnemy(OtherActor) || IsTaskedToKillFoundEnemy(OtherActor) && IsEnemyAttackable(OtherActor)) {
				if (!UnitTask->HasTask()) {
					UnitTask->CreateAndAddTaskAUTO("auto attack", this->GetActorLocation(), OtherActor->GetActorLocation(), OtherActor, EUnitInstructions::UI_Attack);
				}

				LookAt(OtherActor);
				StartAttacking(OtherActor);
				Debug(OtherActor->GetName());
			}
		}

		if (AResource * resource = Cast<AResource>(OtherActor)) {
			if (IsTaskedToHarvest() && IsTaskedToHarvestFoundActor(OtherActor) || HasNoTaskAndFoundResourceToHarvest(OtherActor)) {
				if (CanHarvest && resource->GetCurrentResourceCount() > 0) {
					LookAt(OtherActor);
					this->GetController()->StopMovement();
					IsHarvesting = true;
					HarvestingActor = OtherActor;
				}
			}
		}

		if (ABuilding* building = Cast<ABuilding>(OtherActor)) {
			if (building->CanStore && HasHitDropOffBuilding(OtherActor)) {
				DropResourcesOff();
				UnitTask->RemoveFirstTask();

				if (UnitTask->HasTask() && UnitTask->GetFirstTask()->GetInstruction() == EUnitInstructions::UI_Gather || UnitTask->GetFirstTask()->GetInstruction() == EUnitInstructions::UI_GatherBuilding) {
					if (AResource* res = Cast<AResource>(UnitTask->GetFirstTask()->GetTargetActor())) {
						MoveUnitAndHarvest(UnitTask->GetFirstTask()->GetTargetActor(), UnitTask->GetFirstTask()->GetTargetActor()->GetActorLocation());
					}

					if (ABuilding* bui = Cast<ABuilding>(UnitTask->GetFirstTask()->GetTargetActor())) {
						if (bui->IsConstructed && CanHarvest) {
							MoveUnitAndHarvestBuilding(UnitTask->GetFirstTask()->GetTargetActor());
						}
					}
				}
			}

			if (building->IsDepletableResourceBuilding && building->IsConstructed && CanHarvest) {
				if (IsTaskedToHarvestFoundActor(building) || HasNoTaskAndFoundResourceToHarvest(building)) {
					this->GetController()->StopMovement();
					LookAt(building);

					Debug("Found DepletableBuilding");

					IsHarvesting = true;
					HarvestingActor = OtherActor;
				}
			}
		}
	}
}

void AUnits::OutOfRangeOfAttack(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	if (this != OtherActor && Cast<AUnits>(OtherActor) && OtherComp->GetName() == "UnitBody" && Cast<AUnits>(OtherActor)->UnitOwner != this->UnitOwner) {
		EnemyIsOutOfAttackRange(OtherActor);
	}
}

#pragma endregion

#pragma region Basic Properties

void AUnits::SetDisplayName(FString name) {
	DisplayName = name;
}
FString AUnits::GetDisplayName() {
	return DisplayName;
}
FString AUnits::GetType() {
	return DisplayName;
}
float AUnits::GetHealth() {
	return Health;
}
float AUnits::GetMaxHealth() {
	return MaxHealth;
}

#pragma endregion

#pragma region Widget properties


FString AUnits::GetDescription() {
	return Description;
}

void AUnits::SetDescription(FString desc) {
	Description = desc;
}

FString AUnits::GetHumanName() {
	return DisplayName;
}

FString AUnits::GetBuildCostAsUIString() {
	FString CostListString = "";

	for (int32 i = 0; i < BuildCost.Num(); i++) {
		CostListString += FString::SanitizeFloat(BuildCost[i]->Amount) + "x " + BuildCost[i]->GetResourceType();
	}
	return CostListString;
}


#pragma endregion

#pragma region Movement And Actions

void AUnits::MoveUnit(AActor* ActorAtLocation, FVector Location, int32 UnitNumber, int32 UnitCount) {
	ResetUnitInstructionsOnMove();

	UnitTask->CreateAndAddTask("Test Task", this->GetActorLocation(), Location, ActorAtLocation, EUnitInstructions::UI_Move);

	if (ABuilding* building = Cast<ABuilding>(ActorAtLocation)) {
		if (building->Health < building->MaxHealth && this->CanBuild) {
			MoveUnitAndConstruct(building, building->GetActorLocation());
		}

		if (building->GetIsDepletableResourceBuilding() && this->CanHarvest) {
			MoveUnitAndHarvestBuilding(building);
		}
	}
	
	else if (AUnits* unit = Cast<AUnits>(ActorAtLocation)) {
		if (!unit->IsDead && unit->Health > 0) {
			MoveUnitAndAttack(unit);
		}
	}

	else if (AResource* resource = Cast<AResource>(ActorAtLocation)) {
		MoveUnitAndHarvest(ActorAtLocation, ActorAtLocation->GetActorLocation());
	}

	UNavigationSystem::SimpleMoveToLocation(GetController(), Location); // set movement	
}

void AUnits::ResetUnitInstructionsOnMove() {
	if (this->CanBuild) this->IsBuilding = false;
	if (this->bIsAttacking) this->bIsAttacking = false;

}

void AUnits::MoveUnitAndAttack(AActor* actor) {
	UnitTask->CreateAndAddTask("Attack Task", GetActorLocation(), actor->GetActorLocation(), actor, EUnitInstructions::UI_Attack);
	UNavigationSystem::SimpleMoveToActor(GetController(), actor);
}

void AUnits::MoveUnitAndConstruct(AActor* building, FVector location) {
	UnitTask->CreateAndAddTask("Test Task", this->GetActorLocation(), location, building, EUnitInstructions::UI_Construct);		
	UNavigationSystem::SimpleMoveToActor(GetController(), building);
}

void AUnits::MoveUnitAndHarvest(AActor* resource, FVector location) {
	UnitTask->CreateAndAddTask("Harvest task", this->GetActorLocation(), location, resource, EUnitInstructions::UI_Gather);
	UNavigationSystem::SimpleMoveToActor(GetController(), resource);
}

void AUnits::MoveUnitAndHarvestBuilding(AActor* building) {
	UnitTask->CreateAndAddTask("Harvest Building", this->GetActorLocation(), building->GetActorLocation(), building, EUnitInstructions::UI_GatherBuilding);
	UNavigationSystem::SimpleMoveToActor(GetController(), building);
}

void AUnits::IsMovementInstructionComplete() {	
	if (FVector::Dist(this->GetActorLocation(), UnitTask->GetFirstTask()->GetTargetLocation()) <= 100) 	UnitTask->RemoveFirstTask();	
}

void AUnits::IsAttackInstructionComplete() {

	if (AUnits* targetActor = Cast<AUnits>(UnitTask->GetFirstTask()->GetTargetActor())) {
		if (targetActor->IsDead || targetActor->Health <= 0) {
			UnitTask->RemoveFirstTask();
			UnitsWithinRange.Remove(targetActor);
			StopAttacking();
			//apply for new attack task
			if (UnitsWithinRange.Num() > 0) {
				UnitTask->CreateAndAddTaskAUTO("auto attack new enemy", this->GetActorLocation(), UnitsWithinRange[0]->GetActorLocation(), UnitsWithinRange[0], EUnitInstructions::UI_Attack);
			}
		}
	}

	// check if target died,
	// check if target is nearby
	// check if we are fighing	

	for (int32 i = 0; i < UnitsWithinRange.Num(); i++) {
		if (UnitTask->HasTask() && UnitsWithinRange[i] == UnitTask[i].GetFirstTask()->GetTargetActor()) {
			StartAttacking(UnitTask[i].GetFirstTask()->GetTargetActor());
			return; // finished and will attack
		}
	}

	//not dead, not nearby, not fighting
	//so move towards enemy
	if (UnitTask->HasTask()) {
		UNavigationSystem::SimpleMoveToLocation(GetController(), UnitTask->GetFirstTask()->GetTargetActor()->GetActorLocation());
	}
}

void AUnits::AttemptToGetAutoTask() {
	if (!CanBuild && UnitsWithinRange.Num() > 0) { // attempt to find enemy in attack range
		for (int32 i = 0; i < UnitsWithinRange.Num(); i++) {
			if (IsEnemyAttackable(UnitsWithinRange[i])) {
				UnitTask->CreateAndAddTaskAUTO("auto attack unit", GetActorLocation(), UnitsWithinRange[i]->GetActorLocation(), UnitsWithinRange[i], EUnitInstructions::UI_Attack);
			}
		}
	}
}

#pragma endregion

#pragma region Combat

bool AUnits::HasFoundAnEnemy(AActor* actor, UPrimitiveComponent* OtherComp) {
	return 
		Cast<AUnits>(actor) && 
		OtherComp->GetName() == "UnitBody" && 
		Cast<AUnits>(actor)->UnitOwner != this->UnitOwner;
}

bool AUnits::IsEnemyAttackable(AActor* actor) {
	if (AUnits* unit = Cast<AUnits>(actor)) {
		if (!unit->IsDead && unit->Health > 0) return true;
	}
	return false;
}

void AUnits::NewEnemyHasEnteredAttackRange(AActor* actor) {
	UnitsWithinRange.Add(actor);
}

bool AUnits::IsTaskedToKillFoundEnemy(AActor* actor) {
	return
		UnitTask->HasTask() &&
		UnitTask->GetFirstTask()->GetInstruction() == EUnitInstructions::UI_Attack &&
		UnitTask->GetFirstTask()->GetTargetActor() == actor;
}

bool AUnits::HasNoTaskAndFoundEnemy(AActor* actor) {
	return UnitTask->HasTask() == false;
}

void AUnits::StartAttacking(AActor* actor) {
	bIsAttacking = true;
}

void AUnits::StopAttacking() {
	bIsAttacking = false;
}

void AUnits::AttackTick() {
	Debug("Attacking");
	AUnits* enemy = Cast<AUnits>(UnitTask->GetFirstTask()->GetTargetActor());

	if (enemy->Health > 0) {
		int32 i = FMath::RandRange(0, 100);

		float DamageDone = this->Attack - enemy->Defence;
		if (i > this->CriticalChance) DamageDone *= this->CriticalMultiplier;

		enemy->Health -= DamageDone;
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString::SanitizeFloat(enemy->Health));
		if (enemy->Health <= 0) {
			UnitTask->RemoveFirstTask();
			enemy->Destroy();
			enemy->SetIsDead();
			AttemptToFindNewAttackTarget();
		}
	}
}

void AUnits::EnemyIsOutOfAttackRange(AActor* actor) {
	if (UnitTask->HasTask() && UnitTask->GetFirstTask()->GetTargetActor() == actor && UnitTask->GetFirstTask()->GetInstruction() == EUnitInstructions::UI_Attack) {
		bIsAttacking = false;
		UnitTask->CreateAndAddTask("following fleeing character", this->GetActorLocation(), actor->GetActorLocation(), actor, EUnitInstructions::UI_Attack);
	}
	else {
		bIsAttacking = false;
		if(!IsDead && Health > 0) GetController()->StopMovement();
		// not going to follow if no task to do so
	}
}

void AUnits::AttemptToFindNewAttackTarget() {
	if (UnitsWithinRange.Num() > 0) {
		UnitTask->CreateAndAddTaskAUTO("auto attack new target", this->GetActorLocation(), UnitsWithinRange[0]->GetActorLocation(), UnitsWithinRange[0], EUnitInstructions::UI_Attack);
	}
}

void AUnits::SetIsDead() {
	IsDead = true;
}

bool AUnits::GetIsDead() {
	return IsDead;
}

#pragma endregion

#pragma region Construction

bool AUnits::HitInstructedBuilding(AActor* OtherActor) {
	return UnitTask != nullptr && UnitTask->HasTask() && UnitTask->GetFirstTask()->GetInstruction() == EUnitInstructions::UI_Construct && CanBuild && OtherActor == UnitTask->GetFirstTask()->GetTargetActor();
}

void AUnits::StartBuilding() {
	GetController()->StopMovement();
	IsBuilding = true;
	LookAt(UnitTask->GetFirstTask()->GetTargetActor());
}

void AUnits::BuildBuilding() {
	ABuilding* building = Cast<ABuilding>(UnitTask->GetFirstTask()->GetTargetActor());
	building->AddToHealth(this->BuildRate);
	if (building->Health >= building->MaxHealth) { 
		building->SetHealthToMax();
		building->SetIsConstructed(true);
		BuildingFinished();
	}
}

void AUnits::BuildingFinished() {
	IsBuilding = false;
	UnitTask->RemoveFirstTask();
}

#pragma endregion

#pragma region Harvesting

bool AUnits::IsTaskedToHarvest() {
	return UnitTask->HasTask() && UnitTask->GetFirstTask()->GetInstruction() == EUnitInstructions::UI_Gather;
}

bool AUnits::IsTaskedToHarvestFoundActor(AActor* actor) {
	return UnitTask->HasTask() && UnitTask->GetFirstTask()->GetTargetActor() == actor;
}

bool AUnits::HasNoTaskAndFoundResourceToHarvest(AActor* actor) {
	return !UnitTask->HasTask();
}

void AUnits::HarvestTick() {
	float AmountHarvested = HarvestRate;
	float SpaceRemaining = (Inventory->GetMaxResourceCount() - Inventory->GetCurrentResourceCount());
	if (SpaceRemaining == 0) {
		//theres no space left, stop and find a storage house
	}
	else if (SpaceRemaining < HarvestRate) {
		AmountHarvested = SpaceRemaining;
	}

	if (AResource* resource = Cast<AResource>(HarvestingActor)) {
		if (resource->IsDepleted) {
			IsHarvesting = false;

			Debug("Stopped harvesting due to know resource in this resource Actor");

			UnitTask->RemoveFirstTask();
			AttemptToFindAnotherResourceOfType(resource);
			return;
		}

		Inventory->AddToResourceCount(resource->RemoveAmountFromCount(AmountHarvested), resource->GetResourceType());
		//remove amount from the resource.;

		if (Inventory->IsInventoryFull()) {
			IsHarvesting = false;

			AResource* res = Cast<AResource>(UnitTask->GetFirstTask()->GetTargetActor());
			ABuilding* storage = Cast<ABuilding>(FindNearestStorageBuilding());

			UnitTask->RemoveFirstTask();

			if (storage == nullptr) {
				Debug("Could not find Storage building");
				return;
			}

			UnitTask->CreateAndAddTaskAUTO("auto drop off", this->GetActorLocation(), storage->GetActorLocation(), storage, EUnitInstructions::UI_DropOff);
			Debug("Dropping Off");
			UnitTask->CreateAndAddTaskAUTO("auto return and gather", this->GetActorLocation(), res->GetActorLocation(), res, EUnitInstructions::UI_Gather, false);
			Debug("Going to Auto gather");
			UNavigationSystem::SimpleMoveToActor(this->GetController(), storage);
		}
	}

	if (ABuilding* building = Cast<ABuilding>(HarvestingActor)) {
		if (building->GetIsDepletableResourceDepleted()) {
			IsHarvesting = false;

			Debug("Stopped harvesting due to no resource in this resource building");

			UnitTask->RemoveFirstTask();
			//AttemptToFindAnotherResourceOfType(resource);
			return;
		}

		Inventory->AddToResourceCount(building->RemoveAmountFromDepletableResource(AmountHarvested), Cast<UResourceCost>(building->DepletableResource)->res);

		//remove amount harvested from resource building

		if (Inventory->IsInventoryFull()) {
			IsHarvesting = false;

			ABuilding* storage = Cast<ABuilding>(FindNearestStorageBuilding());

			UnitTask->RemoveFirstTask();

			if (storage == nullptr) {
				Debug("Could not find storage building");
				return;
			}

			UnitTask->CreateAndAddTaskAUTO("auto drop off", this->GetActorLocation(), storage->GetActorLocation(), storage, EUnitInstructions::UI_DropOff);
			Debug("Dropping off");
			UnitTask->CreateAndAddTaskAUTO("Auto return and gather", this->GetActorLocation(), building->GetActorLocation(), building, EUnitInstructions::UI_GatherBuilding);
			Debug("going to auto gather");
			UNavigationSystem::SimpleMoveToActor(this->GetController(), building);
		}

	}
}

AActor* AUnits::FindNearestStorageBuilding() {
	if(playerController != nullptr) {
		APController* pCon = Cast<APController>(playerController);

		FVector location = this->GetActorLocation();
		float distance = -1;
		bool foundStorage = false;

		TArray<ABuilding*> StorageBuildings;
		ABuilding* ClosestBuilding = nullptr;

		for (int32 i = 0; i < pCon->OwnedBuildings.Num(); i++) {
			ABuilding* building = Cast<ABuilding>(pCon->OwnedBuildings[i]);
			if (building->CanStore) {
				StorageBuildings.Add(building);
				foundStorage = true;
			}
		}

		if (!foundStorage) {
			Debug("this Actor: " + this->GetName() + " Could not find a storage building");
			UnitTask->RemoveFirstTask();
			this->GetController()->StopMovement();
			return nullptr;
		}

		for (int32 i = 0; i < StorageBuildings.Num(); i++) {
			float newDistance = FVector::Dist(this->GetActorLocation(), StorageBuildings[i]->GetActorLocation());
			if (distance == -1 || distance > newDistance) {
				distance = newDistance;
				ClosestBuilding = StorageBuildings[i];
			}
		}
		return ClosestBuilding;
	}
	else {
		return nullptr;
	}
}

bool AUnits::HasHitDropOffBuilding(AActor* actor) {
	return UnitTask->HasTask() && UnitTask->GetFirstTask()->GetInstruction() == EUnitInstructions::UI_DropOff;
}

void AUnits::DropResourcesOff() {
	APController* con = Cast<APController>(playerController);
	con->AffectResourceCount(Inventory->ResourceType, Inventory->ResourceCount, true);

	Inventory->EmptyInventory();
}

void AUnits::AttemptToFindAnotherResourceOfType(AActor* res) {
	AResource* resource = Cast<AResource>(res);

	TArray<AResource*> resourcesFound;

	bool resourceFound = false;
	float distancetoResource = -1;

	AResource* closestResource = nullptr;

	for (TActorIterator<AResource> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		// Same as with the Object Iterator, access the subclass instance with the * or -> operators.
		AResource* r = *ActorItr;
		if (r->ResourceType == resource->ResourceType && !r->IsDepleted) {
			resourcesFound.Add(r);
			resourceFound = true;
		}
	}

	if (!resourceFound) {
		Debug("Could not find another resource of this type");
		return;
	}

	for (int32 i = 0; i < resourcesFound.Num(); i++) {
		float newDistance = FVector::Dist(this->GetActorLocation(), resourcesFound[i]->GetActorLocation());
		if (distancetoResource == -1 || distancetoResource > newDistance) {
			distancetoResource = newDistance;
			closestResource = resourcesFound[i];
		}
	}

	if (distancetoResource != -1) {
		UnitTask->CreateAndAddTaskAUTO("Auto harvest new resource", this->GetActorLocation(), closestResource->GetActorLocation(), closestResource, EUnitInstructions::UI_Gather);
		UNavigationSystem::SimpleMoveToActor(this->GetController(), closestResource);
	}
}

#pragma endregion

#pragma region Build Costs and Upgrade

TArray<UResourceCost*> AUnits::GetBuildCost() {
	return BuildCost;
}

float AUnits::GetSpawnTime() {
	return SpawnTime;
}

#pragma endregion

#pragma region Utilis

void AUnits::LookAt(AActor* actor) {
	FRotator PlayerRot = FRotationMatrix::MakeFromX(this->GetActorLocation() - actor->GetActorLocation()).Rotator();
	SetActorLocation(this->GetActorLocation());
	SetActorRotation(PlayerRot);
}

void AUnits::SetController(AController* con) {
	playerController = con;
}

TEnumAsByte<EUnitOwnerships::EUnitOwnerShip> AUnits::GetUnitOwner() {
	return UnitOwner;
}

void AUnits::SetUnitOwner(TEnumAsByte<EUnitOwnerships::EUnitOwnerShip> newowner) {
	UnitOwner = newowner;
}

AUnits* AUnits::GetUnitClassOfType(TEnumAsByte<EUnitList::All> unit) {
	switch (unit) {

	case EUnitList::UL_None:
		return nullptr;


	case EUnitList::UL_Corn:
		return NewObject<ACorn>();


	case EUnitList::UL_Pea:
		return NewObject<APea>();


	case EUnitList::UL_Sprout:
		return NewObject<ASprout>();
	}

	return nullptr;
}

AUnits* AUnits::SpawnUnitOfType(TEnumAsByte<EUnitList::All> unit, FVector spawnLocation, FRotator rotation, UWorld* ThisWorld) {
	FActorSpawnParameters SpawnInfo; // generate spawning rules
	SpawnInfo.bNoFail = false;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	

	switch (unit) {

	case EUnitList::UL_None:
		return nullptr;


	case EUnitList::UL_Corn:		
		return 
			ThisWorld->SpawnActor<ACorn>(ACorn::StaticClass(), spawnLocation, rotation, SpawnInfo);

	case EUnitList::UL_Pea:
		return
			ThisWorld->SpawnActor<APea>(APea::StaticClass(), spawnLocation, rotation, SpawnInfo);

	case EUnitList::UL_Sprout:
		return
			ThisWorld->SpawnActor<ASprout>(ASprout::StaticClass(), spawnLocation, rotation, SpawnInfo);
	}
	return nullptr;
}

#pragma endregion

void AUnits::Debug(FString message) {
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, message);
}