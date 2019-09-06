// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#pragma once
//#include "Pawns/Vehicles/Riders_Vehicle.h"
#include "CoreMinimal.h"
#include "Materials/MaterialInterface.h"
#include "ObjectAndNameAsStringProxyArchive.h"
#include "Riders_VehicleTypes.generated.h"




struct FSaveGameArchive : public FObjectAndNameAsStringProxyArchive
{
	FSaveGameArchive(FArchive& InInnerArchive, bool bInLoadIfFindFails)
		: FObjectAndNameAsStringProxyArchive(InInnerArchive, bInLoadIfFindFails)
	{
		ArIsSaveGame = true;
	}
};



/** UI Vehicle Structure 
	-Vehicle Class
	-UIVehcielData Class */
USTRUCT(BlueprintType)
struct FUIVehicleDataStruct
{

	GENERATED_USTRUCT_BODY();

	/** Vehicle Class */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
		TSubclassOf<class ARiders_Vehicle> VehicleClass;

	/** Vehicle Data Class */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
		TSubclassOf<class UUIVehicleData> VehicleDataClass;


	FUIVehicleDataStruct()
	{

	}
};



UENUM(BlueprintType)
enum class EAIState : uint8
{
	AI_Idle UMETA(DisplayName = "Idle"),
	AI_Moving UMETA(DisplayName = "Moving"),
	AI_Stopping UMETA(DisplayName = "Stopping"),
	AI_Reverse UMETA(DisplayName = "Reverse"),
	AI_Avoidance UMETA(DisplayName = "Avoidance")
};


/** keep in sync with VehicleImpactEffect, VehicleWheelEffect  */
/** This enum type is deprecated, so please do not use this **/
UENUM()
enum class EPhysMaterialType : uint8
{
	Unknown,
	Asphalt,
	Dirt,
	Water,
	Wood,
	Stone,
	Metal
};

UENUM(BlueprintType)
enum class EVehicleMaterialType : uint8
{
	Glossy,
	Metallic,
	Matted,
	TwoColors,
	Carbon
};


USTRUCT(BlueprintType)
struct FBodyMaterialProp
{
	GENERATED_BODY();

	/* Type Material */
	UPROPERTY(EditAnywhere, Category = "Riders Vehicle Settings", BlueprintReadWrite, SaveGame)
		EVehicleMaterialType TypeMaterial;

	/* Color */
	UPROPERTY(EditAnywhere, Category = "Riders Vehicle Settings", BlueprintReadWrite, SaveGame)
		FLinearColor Color;

	/* Material Slot Name */
	UPROPERTY(EditAnywhere, Category = "Riders Vehicle Settings", BlueprintReadWrite, SaveGame)
		FName MaterialSlotName;

	FBodyMaterialProp()
	{
		Color = FLinearColor(0.0f, 0.0f, 0.0f, 1.0f);

		MaterialSlotName = "Default";
	}

};



/* Vehicle Light Struct */
USTRUCT(BlueprintType)
struct FSLightMaterialProp
{
	GENERATED_BODY();

	UPROPERTY(EditAnywhere, Category = "Riders Vehicle Settings", BlueprintReadOnly, SaveGame)
		FName Name;

	UPROPERTY(EditAnywhere, Category = "Riders Vehicle Settings", BlueprintReadOnly, SaveGame)
		FLinearColor LightColor;

	/* Change return color at night */
	UPROPERTY(EditAnywhere, Category = "Riders Vehicle Settings", BlueprintReadOnly, SaveGame)
		bool bNight;

	UPROPERTY(EditAnywhere, Category = "Riders Vehicle Settings", BlueprintReadOnly, SaveGame)
		FLinearColor ReturnColor;

	UPROPERTY(EditAnywhere, Category = "Riders Vehicle Settings", BlueprintReadOnly, SaveGame)
		FName MaterialSlotName;
};


/** When you add new types, make sure you add to
*	[/Script/Engine.PhysicsSettings] section DefaultEngine.INI
*/
#define VEHICLE_SURFACE_Default		SurfaceType_Default
#define VEHICLE_SURFACE_Asphalt		SurfaceType1
#define VEHICLE_SURFACE_Dirt		SurfaceType2
#define VEHICLE_SURFACE_Water		SurfaceType3
#define VEHICLE_SURFACE_Wood		SurfaceType4
#define VEHICLE_SURFACE_Stone		SurfaceType5
#define VEHICLE_SURFACE_Metal		SurfaceType6
#define VEHICLE_SURFACE_Grass		SurfaceType7
#define VEHICLE_SURFACE_Gravel		SurfaceType8