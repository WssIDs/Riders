// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "WheeledVehicleMovementComponent4W.h"
#include "TireConfig.h"
#include "Riders_WVHMovComponent4W.generated.h"
/**
 * 
 */
UCLASS()
class URiders_WVHMovComponent4W : public UWheeledVehicleMovementComponent4W
{
	GENERATED_BODY()

	// Constructor declaration
	URiders_WVHMovComponent4W(const FObjectInitializer& ObjectInitializer);

public:

	/** Brake Bones */
	UPROPERTY(EditAnywhere, Category = VehicleSetup)
	TArray<FName> BrakeBones;

	bool CheckSlipWheel(float AbsLongSlipThreshold, float AbsLatSlipThreshold, int WheelIndex) const;

	/** Set Wheel Offset. */
	UFUNCTION(BlueprintCallable, Category = "Game Play")
		void SetWheelsOffset(FVector Offset);


	UFUNCTION(BlueprintCallable, Category = Movement)
		void ChangeTireConfig(UTireConfig* Config);


	/** Wheel Lat Stiff */
	UFUNCTION(BlueprintCallable, Category = "Wheel")
		void SetWheelLatStiff(int32 WheelIndex, float LatStiffValue, float LatStiffMaxLoad, float LongStiffValue, class UTireConfig* TireConfig);
};
