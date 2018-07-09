// Fill out your copyright notice in the Description page of Project Settings.

#include "BluePrintUtils.h"



void UBluePrintUtils::Create(UClass *ObjectClass, UObject* &CreatedObject)
{
	//NewNode = new ObjectType();
	// Since 4.7/4.8 use:
	CreatedObject = NewObject<UObject>((UObject*)GetTransientPackage(), ObjectClass);
}

void UBluePrintUtils::NullifyActor(AActor* actor) {
	actor = nullptr;
}

bool UBluePrintUtils::IsNullActor(AActor* actor) {
	return actor == nullptr;
}

float UBluePrintUtils::FloorFloat(float flt) {
	return FMath::FloorToFloat(flt);
}

FString UBluePrintUtils::FloatToStringWithDecimal(float flt) {
	return FString::SanitizeFloat(flt, 1);
}
