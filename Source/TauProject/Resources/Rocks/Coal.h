// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Resources/Resource.h"
#include "Coal.generated.h"

UCLASS()
class TAUPROJECT_API ACoal : public AResource
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACoal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
