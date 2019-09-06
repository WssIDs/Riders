#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimInstanceProxy.h"
//#include "Pawns/Vehicles/Riders_Vehicle.h"
//#include "VehicleContent/Riders_WVHMovComponent4W.h"
#include "Riders_AnimInstance.generated.h"


class URiders_WVHMovComponent4W;


struct FRidersWheelAnimData
{
	FName					BoneName;
	FRotator				RotOffset;
	FVector					LocOffset;
};

/** Proxy override for this UAnimInstance-derived class */
USTRUCT()
struct RIDERS_API FRidersVehicleAnimInstanceProxy : public FAnimInstanceProxy
{
	GENERATED_BODY()

		FRidersVehicleAnimInstanceProxy(): FAnimInstanceProxy()
	{
	}

	FRidersVehicleAnimInstanceProxy(UAnimInstance* Instance)
		: FAnimInstanceProxy(Instance)
	{
	}

public:

	void SetRidersVehicleMovementComponent(const URiders_WVHMovComponent4W* InRidersVehicleMovementComponent);

	/** FAnimInstanceProxy interface begin*/
	virtual void PreUpdate(UAnimInstance* InAnimInstance, float DeltaSeconds) override;
	/** FAnimInstanceProxy interface end*/

	const TArray<FRidersWheelAnimData>& GetWheelAnimData() const
	{
		return WheelInstances;
	}

	const TArray<FRidersWheelAnimData>& GetBrakePadAnimData() const
	{
		return BrakePadInstances;
	}


private:
	TArray<FRidersWheelAnimData> WheelInstances;

	TArray<FRidersWheelAnimData> BrakePadInstances;
};


/**
 * 
 */
UCLASS(transient)
class RIDERS_API URiders_AnimInstance : public UAnimInstance
{
	GENERATED_UCLASS_BODY()

		/** Makes a montage jump to the end of a named section. */
		UFUNCTION(BlueprintCallable, Category = "Animation")
		class ARiders_Vehicle * GetVehicle();

public:
	TArray<FRidersWheelAnimData> WheelData;

	TArray<FRidersWheelAnimData> BrakePadData;

public:
	void SetRidersVehicleMovementComponent(const URiders_WVHMovComponent4W* InRidersVehicleMovementComponent)
	{
		RidersVehicleMovementComponent = InRidersVehicleMovementComponent;
		AnimInstanceProxy.SetRidersVehicleMovementComponent(InRidersVehicleMovementComponent);
	}

	const URiders_WVHMovComponent4W* GetRidersVehicleMovementComponent() const
	{
		return RidersVehicleMovementComponent;
	}

private:

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	/** UAnimInstance interface begin*/
	virtual void NativeInitializeAnimation() override;
	virtual FAnimInstanceProxy* CreateAnimInstanceProxy() override;
	virtual void DestroyAnimInstanceProxy(FAnimInstanceProxy* InProxy) override;
	/** UAnimInstance interface end*/

	FRidersVehicleAnimInstanceProxy AnimInstanceProxy;

	UPROPERTY(transient)
		const URiders_WVHMovComponent4W* RidersVehicleMovementComponent;

};


DECLARE_LOG_CATEGORY_EXTERN(RidersAnimLog, Log, All);