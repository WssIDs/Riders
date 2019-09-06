// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
#include "Riders/Classes/VehicleContent/Riders_WVHMovComponent4W.h"
#include "Riders.h"

//#if WITH_PHYSX
//#include "PhysXIncludes.h"
//#endif //WITH_PHYSX

#include "PhysXPublic.h"
#include "PhysXVehicleManager.h"

#include "VehicleWheel.h"
#include "Riders/Classes/VehicleContent/Riders_FrontWheels.h"
#include "Riders/Classes/VehicleContent/Riders_RearWheels.h"

#include "Runtime/Engine/Classes/Engine/Engine.h"

URiders_WVHMovComponent4W::URiders_WVHMovComponent4W(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

    WheelSetups[0].BoneName = "Phys_FL";
	WheelSetups[1].BoneName = "Phys_FR";
	WheelSetups[2].BoneName = "Phys_RL";
	WheelSetups[3].BoneName = "Phys_RR";

	WheelSetups[0].WheelClass = URiders_FrontWheels::StaticClass();
	WheelSetups[1].WheelClass = URiders_FrontWheels::StaticClass();
	WheelSetups[2].WheelClass = URiders_RearWheels::StaticClass();
	WheelSetups[3].WheelClass = URiders_RearWheels::StaticClass();

	BrakeBones.SetNum(4);

	BrakeBones[0] = "FL_BrakePad";
	BrakeBones[1] = "FR_BrakePad";
	BrakeBones[2] = "RL_BrakePad";
	BrakeBones[3] = "RR_BrakePad";

}


bool URiders_WVHMovComponent4W::CheckSlipWheel(float AbsLongSlipThreshold, float AbsLatSlipThreshold, int WheelIndex) const
{

	float LatSlip = FMath::Abs(Wheels[WheelIndex]->DebugLatSlip);
	float LongSlip = FMath::Abs(Wheels[WheelIndex]->DebugLongSlip);


	if (LatSlip > AbsLatSlipThreshold)
	{
		return true;
	}

	if (LongSlip > AbsLongSlipThreshold)
	{
		return true;
	}

	return false;
}

void URiders_WVHMovComponent4W::SetWheelsOffset(FVector Offset)
{
	FVector LeftOffset = FVector(Offset.X, Offset.Y*-1, Offset.Z);
	FVector RightOffset = Offset;

	WheelSetups[0].AdditionalOffset = LeftOffset;
	WheelSetups[1].AdditionalOffset = RightOffset;
	WheelSetups[2].AdditionalOffset = LeftOffset;
	WheelSetups[3].AdditionalOffset = RightOffset;


	RecreatePhysicsState();

}

void URiders_WVHMovComponent4W::ChangeTireConfig(UTireConfig* Config)
{
	for (UVehicleWheel* WheelItem : Wheels)
	{
		WheelItem->TireConfig = Config;
	}
}

#if WITH_PHYSX
#if WITH_PHYSX_VEHICLES
void URiders_WVHMovComponent4W::SetWheelLatStiff(int32 WheelIndex, float LatStiffValue, float LatStiffMaxLoad, float LongStiffValue, UTireConfig* TireConfig)
{
	if (WheelIndex >= 0 && LatStiffValue > 0.01 && LatStiffMaxLoad > 0.01 && LongStiffValue > 0.01 && Wheels.Num() > WheelIndex)
	{
		Wheels[WheelIndex]->LatStiffValue = LatStiffValue;
		Wheels[WheelIndex]->LatStiffMaxLoad = LatStiffMaxLoad;
		Wheels[WheelIndex]->LongStiffValue = LongStiffValue;
		Wheels[WheelIndex]->TireConfig = TireConfig;

		// init tire data
		PxVehicleTireData PTireData;
		//class physx::PxVehicleTireData PTireData;
		PTireData.mType = Wheels[WheelIndex]->TireConfig ? Wheels[WheelIndex]->TireConfig->GetTireConfigID() : FPhysXVehicleManager::GetDefaultTireConfig()->GetTireConfigID();
		PTireData.mLatStiffX = Wheels[WheelIndex]->LatStiffMaxLoad;
		PTireData.mLatStiffY = Wheels[WheelIndex]->LatStiffValue;
		PTireData.mLongitudinalStiffnessPerUnitGravity = Wheels[WheelIndex]->LongStiffValue;

		PVehicle->mWheelsSimData.setTireData(WheelIndex, PTireData);
	}
}
#endif
#endif
