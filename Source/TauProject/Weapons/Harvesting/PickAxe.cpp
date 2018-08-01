// Fill out your copyright notice in the Description page of Project Settings.

#include "PickAxe.h"
#include "ConstructorHelpers.h"

#include "Components/StaticMeshComponent.h"

APickAxe::APickAxe()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> mesh(TEXT("/Game/Models/Debug/Weapons/BasicPickaxe.BasicPickaxe"));

	if (mesh.Succeeded()) {
		WeaponMesh->SetStaticMesh(mesh.Object);
		WeaponMesh->SetWorldScale3D(FVector(0.6));
		WeaponMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
		WeaponMesh->SetRelativeRotation(FRotator(0, 0, 0));
	}
}


