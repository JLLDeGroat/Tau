// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include "Units/UnitStructs.h"
#include "PlayerResource/EResource.h"
#include "Engine/StaticMesh.h"
#include "GameFramework/Actor.h"
#include "Resource.generated.h"

UCLASS()
class TAUPROJECT_API AResource : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AResource();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	


	UPROPERTY(EditAnywhere, Category = GlobalResource)
		float ResourceCount;

	UPROPERTY(EditAnywhere, Category = GlobalResource)
		float ResourceCountOriginal;

	UPROPERTY(EditAnywhere, Category = GlobalResource)
		FString DisplayName;

	UPROPERTY(EditAnywhere, Category = GlobalResource)
		float MaxResourceCount;

	UPROPERTY(EditAnywhere, Category = GlobalResource)
		float MinResourceCount;

	UPROPERTY(EditAnywhere, Category = GlobalResource)
		bool IsDepleted;

	UPROPERTY(EditAnywhere, Category = GlobalResource)
		TEnumAsByte<EResources::All> ResourceType;

	#pragma region Getters

	UFUNCTION(BlueprintCallable)
		float GetCurrentResourceCount();

	TEnumAsByte<EResources::All> GetResourceType();
	#pragma endregion

	#pragma region Setters

	void SetIsDepleted();

	float SetInitialResources(TEnumAsByte<EResources::All> resource);
	
	#pragma endregion


	#pragma region Harvested

	float RemoveAmountFromCount(float amount);

	void AfterRemovedChecks();

	#pragma endregion
	
};
