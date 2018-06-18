// Fill out your copyright notice in the Description page of Project Settings.

#include "ResourceCost.h"



UResourceCost::UResourceCost() {

}


UResourceCost* UResourceCost::Setup(TEnumAsByte<EResources::All> r, float a) {
	this->res = r;
	this->Amount = a;
	return this;
}