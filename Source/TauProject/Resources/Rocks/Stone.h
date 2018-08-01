// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Resources/Resource.h"
#include "Stone.generated.h"

/**
 * 
 */
UCLASS()
class TAUPROJECT_API AStone : public AResource
{
	GENERATED_BODY()
		AStone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
	
	
};
