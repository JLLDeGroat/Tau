// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PlayerResource/EResource.h"
#include "ResourceCost.generated.h"

/**
 * 
 */
UCLASS()
class TAUPROJECT_API UResourceCost : public UObject
{
	GENERATED_BODY()
		UResourceCost();

public:
		
	UPROPERTY()
		float Amount;
	UPROPERTY()
		TEnumAsByte<EResources::All> res;	


	UFUNCTION(BlueprintCallable)
		float GetAmount();

	UFUNCTION(BlueprintCallable)
		FString GetResourceType();
	
	

	UResourceCost* Setup(TEnumAsByte<EResources::All> res, float amount);

	UFUNCTION(BlueprintCallable, category = "Resource Utils")
		static FString ResourceListAsUIString(TArray<UResourceCost*> arrayList);
};
