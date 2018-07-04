// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Buildings/Building.h"
#include "Barracks.generated.h"

UCLASS()
class TAUPROJECT_API ABarracks : public ABuilding
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABarracks();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetupResearchItems();
	void SetupBuildingNeedsItem();
	void SetupBuildCosts();
};
