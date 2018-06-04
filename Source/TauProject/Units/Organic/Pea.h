// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Units/Units.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Pea.generated.h"

UCLASS()
class TAUPROJECT_API APea : public AUnits
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APea();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
