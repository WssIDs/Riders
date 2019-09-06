

#include "Anim/Riders_AnimInstance.h"
#include "Riders.h"
#include "AnimationRuntime.h"
#include "Pawns/Vehicles/Riders_Vehicle.h"
#include "VehicleContent/Riders_WVHMovComponent4W.h"


DEFINE_LOG_CATEGORY(RidersAnimLog);

URiders_AnimInstance::URiders_AnimInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}


class ARiders_Vehicle * URiders_AnimInstance::GetVehicle()
{
	return Cast<ARiders_Vehicle>(GetOwningActor());
}

void URiders_AnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}

void URiders_AnimInstance::NativeInitializeAnimation()
{
	// Find a wheeled movement component
	if (AActor* Actor = GetOwningActor())
	{
		if (URiders_WVHMovComponent4W* FoundRidersVehicleMovementComponent = Actor->FindComponentByClass<URiders_WVHMovComponent4W>())
		{
			SetRidersVehicleMovementComponent(FoundRidersVehicleMovementComponent);
		}
	}
}

FAnimInstanceProxy* URiders_AnimInstance::CreateAnimInstanceProxy()
{
	return &AnimInstanceProxy;
}

void URiders_AnimInstance::DestroyAnimInstanceProxy(FAnimInstanceProxy* InProxy)
{
}

/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
//// PROXY ///

void FRidersVehicleAnimInstanceProxy::SetRidersVehicleMovementComponent(const URiders_WVHMovComponent4W * InRidersVehicleMovementComponent)
{	
	const URiders_WVHMovComponent4W* WheeledVehicleMovementComponent = InRidersVehicleMovementComponent;

	//initialize wheel data
	const int32 NumOfwheels = WheeledVehicleMovementComponent->WheelSetups.Num();
	WheelInstances.Empty(NumOfwheels);

	if (NumOfwheels > 0)
	{
		WheelInstances.AddZeroed(NumOfwheels);
		
		// now add wheel data
		for (int32 WheelIndex = 0; WheelIndex<WheelInstances.Num(); ++WheelIndex)
		{
			FRidersWheelAnimData& WheelInstance = WheelInstances[WheelIndex];
			const FWheelSetup& WheelSetup = WheeledVehicleMovementComponent->WheelSetups[WheelIndex];

			// set data
			//WheelInstance.
			WheelInstance.BoneName = WheelSetup.BoneName;
			WheelInstance.LocOffset = FVector::ZeroVector;
			WheelInstance.RotOffset = FRotator::ZeroRotator;
		}
	}


	//initialize wheel data
	const int32 NumOfBrakePads = WheeledVehicleMovementComponent->BrakeBones.Num();
	BrakePadInstances.Empty(NumOfBrakePads);

	if (NumOfBrakePads > 0)
	{
		BrakePadInstances.AddZeroed(NumOfBrakePads);

		// now add wheel data
		for (int32 WheelIndex = 0; WheelIndex<BrakePadInstances.Num(); ++WheelIndex)
		{
			FRidersWheelAnimData& BrakePadInstance = BrakePadInstances[WheelIndex];
			FName BrakePadBoneName = WheeledVehicleMovementComponent->BrakeBones[WheelIndex];

			// set data
			//WheelInstance.
			BrakePadInstance.BoneName = BrakePadBoneName;
			BrakePadInstance.LocOffset = FVector::ZeroVector;
			BrakePadInstance.RotOffset = FRotator::ZeroRotator;
		}
	}

}

void FRidersVehicleAnimInstanceProxy::PreUpdate(UAnimInstance* InAnimInstance, float DeltaSeconds)
{
	Super::PreUpdate(InAnimInstance, DeltaSeconds);

	const URiders_AnimInstance* RidersAnimInstance = CastChecked<URiders_AnimInstance>(InAnimInstance);
	if (const URiders_WVHMovComponent4W* WheeledVehicleMovementComponent = RidersAnimInstance->GetRidersVehicleMovementComponent())
	{
		for (int32 WheelIndex = 0; WheelIndex < WheelInstances.Num(); ++WheelIndex)
		{
			FRidersWheelAnimData& WheelInstance = WheelInstances[WheelIndex];

			if (WheeledVehicleMovementComponent->Wheels.IsValidIndex(WheelIndex))
			{
				if (const UVehicleWheel* VehicleWheel = WheeledVehicleMovementComponent->Wheels[WheelIndex])
				{
				
					WheelInstance.RotOffset.Pitch = VehicleWheel->GetRotationAngle();
					WheelInstance.RotOffset.Yaw = VehicleWheel->GetSteerAngle();
					WheelInstance.RotOffset.Roll = 0.f;

					WheelInstance.LocOffset.X = 0.f;
					WheelInstance.LocOffset.Y = 0.f;
					WheelInstance.LocOffset.Z = VehicleWheel->GetSuspensionOffset();
				}
			}
		}

		for (int32 WheelIndex = 0; WheelIndex < BrakePadInstances.Num(); ++WheelIndex)
		{
			FRidersWheelAnimData& BrakePadInstance = BrakePadInstances[WheelIndex];

			if (WheeledVehicleMovementComponent->Wheels.IsValidIndex(WheelIndex))
			{
				if (const UVehicleWheel* VehicleWheel = WheeledVehicleMovementComponent->Wheels[WheelIndex])
				{

					BrakePadInstance.RotOffset.Pitch = 0.0f;
					BrakePadInstance.RotOffset.Yaw = VehicleWheel->GetSteerAngle();
					BrakePadInstance.RotOffset.Roll = 0.f;

					BrakePadInstance.LocOffset.X = 0.f;
					BrakePadInstance.LocOffset.Y = 0.f;
					BrakePadInstance.LocOffset.Z = VehicleWheel->GetSuspensionOffset();
				}
			}
		}

	}
}
