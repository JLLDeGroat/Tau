// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Buildings/Building.h"
#include "GameFramework/Actor.h"
#include "Storage.generated.h"

UCLASS()
class TAUPROJECT_API AStorage : public ABuilding
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStorage();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UStaticMeshComponent* Box;
	UStaticMesh* BuildingMesh;
	UStaticMesh* FailedBuildingMesh;
	UStaticMesh* Stage1Construction;
	UStaticMesh* Stage2Construction;
	UStaticMesh* Stage3Construction;
	UStaticMesh* Stage1Damage;
	UStaticMesh* Stage2Damage;
	UStaticMesh* Stage3Damage;
	
};
