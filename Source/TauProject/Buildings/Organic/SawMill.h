// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Buildings/Building.h"
#include "SawMill.generated.h"

/**
 * 
 */
UCLASS()
class TAUPROJECT_API ASawMill : public ABuilding
{
	GENERATED_BODY()
		ASawMill();


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
