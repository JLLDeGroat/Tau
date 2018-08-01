// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/Engine.h"
#include "ArmUnits.generated.h"
/**
 * 
 */
UCLASS()
class TAUPROJECT_API UArmUnits : public UObject
{
	GENERATED_BODY()
		UArmUnits();


public:
	
	static void ArmSpawnedUnit(UWorld* world, AActor* unitActor, USkeletalMeshComponent* parentMesh);
	
};
