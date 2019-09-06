// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "VehicleContent/RidersVehicleWheel.h"
#include "Riders_FrontWheels.generated.h"

class UPhysicalMaterial;

#if WITH_PHYSX
namespace physx
{
	class PxShape;
}
#endif // WITH_PHYSX


/**
 * 
 */
UCLASS(BlueprintType,EditInlineNew)
class URiders_FrontWheels : public URidersVehicleWheel
{
	GENERATED_BODY()

public:
	// Constructor declaration
	URiders_FrontWheels();
};
