// Fill out your copyright notice in the Description page of Project Settings.

#include "ArmUnits.h"
#include "UnitStructs.h"
#include "Units.h"
#include "Engine/Engine.h"
#include "Components/SkeletalMeshComponent.h"
//include Weapons
#include "Weapons/Weapon.h"
//swords
#include "Weapons/Swords/BasicSword.h"
//Guns
#include "Weapons/Ranged/Musket.h"
//harvesting
#include "Weapons/Harvesting/PickAxe.h"

UArmUnits::UArmUnits() {

}


void UArmUnits::ArmSpawnedUnit(UWorld* world, AActor* unitActor, USkeletalMeshComponent* parentMesh) {
	if (AUnits* unit = Cast<AUnits>(unitActor)) {
		FName rightArmSocket = TEXT("RASocket");
		FName leftArmSocket = TEXT("LASocket");

		AWeapon* rightArm = nullptr;
		AWeapon* leftArm = nullptr;

		//world->SpawnActor<ABasicSword>();
		//rArmWeapon = world->SpawnActor<ABasicSword>();
		//rArmWeapon->AttachToComponent(CurrentMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, fnWeaponSocket);
		//rArmWeapon->SetActorRelativeRotation(FRotator(90, -90, 0)); // pea position for Basic Sword 	



		if (unit->bIsArmed && unit->ThisUnitType == EUnitList::UL_Pea) { //is soldier unit and should be equipped with soldier stuff
			rightArm = world->SpawnActor<ABasicSword>();
			rightArm->AttachToComponent(parentMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, rightArmSocket);
			rightArm->SetActorRelativeRotation(FRotator(90, -90, 0)); // position to point foward
			unit->rArmWeapon = rightArm;
		}

		if (unit->bIsArmed && unit->ThisUnitType == EUnitList::UL_MusketPea) {
			rightArm = world->SpawnActor<AMusket>();
			rightArm->AttachToComponent(parentMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, rightArmSocket);
			rightArm->SetActorRelativeRotation(FRotator(90, -90, 0));
			unit->rArmWeapon = rightArm;
		}

		if (unit->CanHarvest) { // is harvester unit, equip with pickaxe			
			rightArm = world->SpawnActor<APickAxe>();
			rightArm->AttachToComponent(parentMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, rightArmSocket);
			rightArm->SetActorRelativeRotation(FRotator(90, -90, 0)); // position to point foward
			unit->rArmWeapon = rightArm;
		}
	}
}

