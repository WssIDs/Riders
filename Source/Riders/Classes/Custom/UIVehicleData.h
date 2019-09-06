// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "UIVehicleData.generated.h"

/**
 * 
 */
UCLASS(BlueprintType,Blueprintable, abstract, EditInlineNew)
class RIDERS_API UUIVehicleData : public UObject
{
	GENERATED_BODY()

	// Constructor declaration
	UUIVehicleData();


	UPROPERTY(EditDefaultsOnly)
		float TestFloat;

	UPROPERTY(EditDefaultsOnly)
		int32 TestInt;
	
	
};
