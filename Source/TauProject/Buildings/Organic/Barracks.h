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

	UStaticMeshComponent* Box;
	UStaticMesh* BuildingMesh;
	UStaticMesh* FailedBuildingMesh;
	UStaticMesh* Stage1Construction;
	UStaticMesh* Stage2Construction;
	UStaticMesh* Stage3Construction;
	UStaticMesh* Stage1Damage;
	UStaticMesh* Stage2Damage;
	UStaticMesh* Stage3Damage;

	UFUNCTION()
		void StartOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void EndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	void SetMeshOnState();


	void SetBarracksMesh(bool placed);
	
};
