// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BluePrintUtils.generated.h"

/**
 * 
 */
UCLASS()
class TAUPROJECT_API UBluePrintUtils : public UObject
{
	GENERATED_BODY()
	
	
public:
	UFUNCTION(BlueprintCallable, Category = "Object")
		static void Create(UClass *ObjectClass, UObject* &CreatedObject);


	UFUNCTION(BlueprintCallable, Category = "Object")
		static void NullifyActor(AActor* actor);

	UFUNCTION(BlueprintCallable, Category = "Object")
		static bool IsNullActor(AActor* actor);
	

	UFUNCTION(BlueprintCallable, Category = "floats")
		static float FloorFloat(float flt);

	UFUNCTION(BlueprintCallable, Category = "floats")
		FString FloatToStringWithDecimal(float flt);

};
