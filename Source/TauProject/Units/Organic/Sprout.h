// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Units/Units.h"
#include "Sprout.generated.h"

UCLASS()
class TAUPROJECT_API ASprout : public AUnits
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASprout();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	
};
