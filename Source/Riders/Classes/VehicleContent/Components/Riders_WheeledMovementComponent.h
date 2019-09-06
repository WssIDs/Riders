// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PawnMovementComponent.h"
#include "WheeledVehicleMovementComponent.h"
#include "Riders_WheeledMovementComponent.generated.h"

class UVehicleWheel;

/**
* Component to handle the vehicle simulation for an actor.
*/
UCLASS(Abstract, hidecategories = (PlanarMovement, "Components|Movement|Planar", Activation, "Components|Activation"))
class RIDERS_API URiders_WheeledMovementComponent : public UPawnMovementComponent
{
	GENERATED_BODY()

		// Construct component class
		URiders_WheeledMovementComponent();


	/** Wheels to create */
	UPROPERTY(EditAnywhere, Category = VehicleSetup)
		TArray<FWheelSetup> WheelSetups;
	
};
