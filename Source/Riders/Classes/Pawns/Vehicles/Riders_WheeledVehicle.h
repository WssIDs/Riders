

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Player/Riders_GamePlayerController.h"
#include "VehicleContent/VehiclePartsComponents.h"
#include "Effects/Riders_VehicleImpactEffect.h"
#include "VehicleContent/Riders_WVHMovComponent4W.h"
#include "DisplayDebugHelpers.h"
#include "Riders_WheeledVehicle.generated.h"

class FDebugDisplayInfo;
//dependsOn = (AController)

/**
 * 
 Main Riders_Vehicle Class
 */
UCLASS(abstract, BlueprintType)
class RIDERS_API ARiders_WheeledVehicle : public APawn
{
	GENERATED_BODY()



private:

	/**  The base skeletal mesh associated with this Vehicle */
		UPROPERTY(Category = Vehicle, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class   USkeletalMeshComponent* VehicleBaseMesh;

	/**  The Body skeletal mesh associated with this Vehicle */
		UPROPERTY(Category = Vehicle, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class   USkeletalMeshComponent* VehicleBodyMesh;

	UPROPERTY(Category = Vehicle, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class	USkeletalMeshComponent* VehicleMirrorsMesh;

	UPROPERTY(Category = Vehicle, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class	USkeletalMeshComponent* VehicleHoodMesh;

	UPROPERTY(Category = Vehicle, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class	USkeletalMeshComponent* VehicleRoofMesh;

	UPROPERTY(Category = Vehicle, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class	USkeletalMeshComponent* VehicleFrontBumperMesh;

	UPROPERTY(Category = Vehicle, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class	USkeletalMeshComponent* VehicleRearBumperMesh;

	UPROPERTY(Category = Vehicle, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class	USkeletalMeshComponent* VehicleSpoilerMesh;

	UPROPERTY(Category = Vehicle, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class	USkeletalMeshComponent* VehicleRimMesh;

	UPROPERTY(Category = Vehicle, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class	USkeletalMeshComponent* VehicleFrontLightMesh;

	UPROPERTY(Category = Vehicle, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class	USkeletalMeshComponent* VehicleTailLightMesh;

	/////////////////////////////////

	UPROPERTY(Category = Vehicle, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class	UStaticMeshComponent* FL_WheelMesh;

	UPROPERTY(Category = Vehicle, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class	UStaticMeshComponent* FL_BrakePadMesh;

	UPROPERTY(Category = Vehicle, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class	UStaticMeshComponent* FL_TireMesh;


	UPROPERTY(Category = Vehicle, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class	UStaticMeshComponent* FR_WheelMesh;

	UPROPERTY(Category = Vehicle, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class	UStaticMeshComponent* FR_BrakePadMesh;

	UPROPERTY(Category = Vehicle, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class	UStaticMeshComponent* FR_TireMesh;


	UPROPERTY(Category = Vehicle, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class	UStaticMeshComponent* BL_WheelMesh;

	UPROPERTY(Category = Vehicle, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class	UStaticMeshComponent* BL_BrakePadMesh;

	UPROPERTY(Category = Vehicle, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class	UStaticMeshComponent* BL_TireMesh;


	UPROPERTY(Category = Vehicle, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class	UStaticMeshComponent* BR_WheelMesh;

	UPROPERTY(Category = Vehicle, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class	UStaticMeshComponent* BR_BrakePadMesh;

	UPROPERTY(Category = Vehicle, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class	UStaticMeshComponent* BR_TireMesh;




	/** vehicle simulation component */
		UPROPERTY(Category = Vehicle, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class URiders_WVHMovComponent4W* RidersMovement;

	/** vehicle part components */
	UPROPERTY(Category = Vehicle, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UVehiclePartsComponents* PartComponents;


public:

	ARiders_WheeledVehicle();



	static FName VehicleBaseMeshComponentName;
	static FName VehicleBodyMeshComponentName;
	static FName RidersMovementComponentName;
	//static FName VehicleInteriorMeshComponentName;
	static FName VehicleMirrorsMeshComponentName;
	static FName VehicleHoodMeshComponentName;
	static FName VehicleRoofMeshComponentName;
	static FName VehicleFrontBumperMeshComponentName;
	static FName VehicleRearBumperMeshComponentName;
	static FName VehicleSpoilerMeshComponentName;
	//static FName VehicleWheelsMeshComponentName;
	static FName VehicleRimMeshComponentName;
	static FName VehicleFrontLightMeshComponentName;
	static FName VehicleTailLightMeshComponentName;

	/** Returns BaseMesh subobject **/
	class USkeletalMeshComponent* GetBaseMesh() const { return  VehicleBaseMesh; }

	/** Returns BodyMesh subobject **/
	class USkeletalMeshComponent* GetBodyMesh() const { return VehicleBodyMesh; }

	/** Returns MirrorsMesh subobject **/
	class USkeletalMeshComponent* GetMirrorsMesh() const { return VehicleMirrorsMesh; }

	/** Returns HoodMesh subobject **/
	class USkeletalMeshComponent* GetHoodMesh() const { return VehicleHoodMesh; }

	/** Returns RoofMesh subobject **/
	class USkeletalMeshComponent* GetRoofMesh() const { return VehicleRoofMesh; }

	/** Returns FrontBumperMesh subobject **/
	class USkeletalMeshComponent* GetFrontBumperMesh() const { return VehicleFrontBumperMesh; }

	/** Returns RearBumperMesh subobject **/
	class USkeletalMeshComponent* GetRearBumperMesh() const { return VehicleRearBumperMesh; }

	/** Returns SpoilerMesh subobject **/
	class USkeletalMeshComponent* GetSpoilerMesh() const { return VehicleSpoilerMesh; }

	/** Returns RimMesh subobject **/
	class USkeletalMeshComponent* GetRimMesh() const { return VehicleRimMesh; }

	/** Returns FrontLightMesh subobject **/
	class USkeletalMeshComponent* GetFrontLightMesh() const { return VehicleFrontLightMesh; }

	/** Returns TailLightMesh subobject **/
	class USkeletalMeshComponent* GetTailLightMesh() const { return VehicleTailLightMesh; }

	/** Returns VehicleMovement subobject **/
	class URiders_WVHMovComponent4W* GetVehicleMovement() const { return RidersMovement; }

	/** Returns VehicleParComponent subobject **/
	class UVehiclePartsComponents* GetPartComponents() const { return PartComponents; }

	/** Return WheelMeshComponents **/
	TArray<UStaticMeshComponent*> GetWheelMeshes() const
	{
		TArray<UStaticMeshComponent*> TempComponents;

		TempComponents.Add(FL_WheelMesh);
		TempComponents.Add(FR_WheelMesh);
		TempComponents.Add(BL_WheelMesh);
		TempComponents.Add(BR_WheelMesh);

		return TempComponents;
	}

	/** Return WheelMeshComponents **/
	TArray<UStaticMeshComponent*> GetTireMeshes() const;

	/** Return WheelMeshComponents **/
	TArray<UStaticMeshComponent*> GetBrakePadMeshes() const;

	// Begin AActor interface
	virtual void DisplayDebug(class UCanvas* Canvas, const FDebugDisplayInfo& DebugDisplay, float& YL, float& YPos) override;
	// End Actor interface

};


DECLARE_LOG_CATEGORY_EXTERN(VehicleLog, Log, All);