#pragma once

#include "CoreMinimal.h"
#include "Custom/Riders_VehicleTypes.h"
#include "Engine/SkeletalMesh.h"
#include "Engine/StaticMesh.h"
#include "Engine/StaticMeshActor.h"
//#include "Pawns/Vehicles/Riders_Vehicle.h"
#include "Runtime/Engine/Classes/Animation/SkeletalMeshActor.h"
#include "Archive.h"
#include "RidersSaveGameTypes.generated.h"


class AStaticMeshActor;
class ASkeletalMeshActor;

USTRUCT(BlueprintType)
struct FStaticActorRecord
{

	GENERATED_BODY();

	UPROPERTY(EditAnywhere, Category = Basic, BlueprintReadWrite, SaveGame)
		TSubclassOf<AStaticMeshActor>	Class;

	UPROPERTY(EditAnywhere, Category = Basic, BlueprintReadWrite, SaveGame)
		UStaticMesh*	Mesh;

	UPROPERTY(EditAnywhere, Category = Basic, BlueprintReadWrite, SaveGame)
		FTransform    Transform;

	UPROPERTY(EditAnywhere, Category = Basic, BlueprintReadWrite, SaveGame)
		TArray<uint8> ActorData;


	FORCEINLINE FArchive& Serialize(FArchive& Ar)
	{
		//Ar << ClassName;
		Ar << Class;
		Ar << Mesh;
		Ar << Transform;
		Ar << ActorData;
		return Ar;
	}
};


USTRUCT(BlueprintType)
struct FSkeletalActorRecord
{
	GENERATED_BODY();

	UPROPERTY(EditAnywhere, Category = Basic, BlueprintReadWrite, SaveGame)
		TSubclassOf<ASkeletalMeshActor>	Class;

	UPROPERTY(EditAnywhere, Category = Basic, BlueprintReadWrite, SaveGame)
		USkeletalMesh*	Mesh;

	UPROPERTY(EditAnywhere, Category = Basic, BlueprintReadWrite, SaveGame)
		FTransform    Transform;

	UPROPERTY(EditAnywhere, Category = Basic, BlueprintReadWrite, SaveGame)
		TArray<uint8> ActorData;


	FORCEINLINE FArchive& Serialize(FArchive& Ar)
	{
		//Ar << ClassName;
		Ar << Class;
		Ar << Mesh;
		Ar << Transform;
		Ar << ActorData;
		return Ar;
	}
};



USTRUCT(BlueprintType)
struct FVehicleRecord
{
	GENERATED_USTRUCT_BODY();

	UPROPERTY(EditAnywhere, Category = Basic, BlueprintReadWrite, SaveGame)
	 TSubclassOf<ARiders_Vehicle> Class;

	UPROPERTY(EditAnywhere, Category = Basic, BlueprintReadWrite, SaveGame)
		FTransform    Transform;

	UPROPERTY(EditAnywhere, Category = Basic, BlueprintReadWrite, SaveGame)
		FName        Name;

	UPROPERTY(EditAnywhere, Category = Basic, BlueprintReadWrite, SaveGame)
		TArray<uint8> ActorData;

	UPROPERTY(EditAnywhere, Category = Basic, BlueprintReadWrite, SaveGame)
		TArray<uint8> ComponentData;

	//UPROPERTY(EditAnywhere, Category = Basic, BlueprintReadWrite, SaveGame)
	//	FTunningParts WorkshopMenu;
};
