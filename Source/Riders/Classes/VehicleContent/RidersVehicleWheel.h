// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VehicleWheel.h"
#include "Riders.h"
#include "RidersVehicleWheel.generated.h"

class UPhysicalMaterial;
class FPhysXVehicleManager;

#if WITH_PHYSX
namespace physx
{
	class PxShape;
}
#endif // WITH_PHYSX

/**
 * 
 */
UCLASS()
class RIDERS_API URidersVehicleWheel : public UVehicleWheel
{
	GENERATED_BODY()


public:
	UPROPERTY(EditAnywhere, Category = Tire)
		UTireConfig* HandbrakeTireConfig;

	UFUNCTION(BlueprintCallable, Category = "Game|Components|WheeledVehicleMovement")
		float GetLongSlip() const { return DebugLongSlip; }

	UFUNCTION(BlueprintCallable, Category = "Game|Components|WheeledVehicleMovement")
		float GetLatSlip() const { return DebugLatSlip; }

	UFUNCTION(BlueprintCallable, Category = "Game|Components|WheeledVehicleMovement")
		float GetLatForce() const { return DebugLatForce; }

	UFUNCTION(BlueprintCallable, Category = "Game|Components|WheeledVehicleMovement")
		float GetLongForce() const { return DebugLongSlip; }


	/**
	 * Tick this wheel when the vehicle ticks
	 */
	virtual void Tick(float DeltaTime) override;
};
