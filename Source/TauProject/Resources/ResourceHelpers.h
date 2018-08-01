// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Runtime/Core/Public/Async/AsyncWork.h"
#include "Resource.h"
#include "UObject/NoExportTypes.h"
#include "ResourceHelpers.generated.h"

/**
 * 
 */
UCLASS()
class TAUPROJECT_API UResourceHelpers : public UObject
{
	GENERATED_BODY()
		UResourceHelpers();

public:
	
	static void SetInitialResourceAmount(AResource* resource);
	
	
	static void SetResourceMinMaxAmount(AResource* resource);

	static void CheckIfDepleted(AResource* resource);

};
