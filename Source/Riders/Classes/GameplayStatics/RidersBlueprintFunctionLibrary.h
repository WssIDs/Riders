// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LatentActionManager.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Custom/RidersSaveGameTypes.h"
#include "ObjectAndNameAsStringProxyArchive.h"
#include "Engine/StaticMeshActor.h"
#include "RidersBlueprintFunctionLibrary.generated.h"


struct FRidersSaveGameArchive : public FObjectAndNameAsStringProxyArchive
{
	FRidersSaveGameArchive(FArchive& InInnerArchive, bool bInLoadIfFindFails)
		: FObjectAndNameAsStringProxyArchive(InInnerArchive, bInLoadIfFindFails)
	{
		ArIsSaveGame = true;
	}
};

/**
 * 
 */
UCLASS()
class RIDERS_API URidersBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	/* Serialize object params to object data*/
	UFUNCTION(BlueprintCallable, Category = "RidersBPLibrary")
	static TArray<uint8> ObjectSaver(UObject * SaveObject);

	/* Deserialize object data to object params*/
	UFUNCTION(BlueprintCallable, Category = "RidersBPLibrary")
	static void ObjectLoader(UObject * LoadObject, TArray<uint8> ObjectData);


	/* Serialize static mesh params to object data*/
	UFUNCTION(BlueprintCallable, Category = "RidersBPLibrary")
		static FStaticActorRecord StaticMeshSaver(AStaticMeshActor * SaveActor);

	/* Deserialize static mesh data to object params*/
	UFUNCTION(BlueprintCallable, Category = "RidersBPLibrary")
		static void StaticMeshLoader(AStaticMeshActor * LoadObject, FStaticActorRecord ActorData);


	/* Serialize static mesh params to object data*/
	UFUNCTION(BlueprintCallable, Category = "RidersBPLibrary")
		static FSkeletalActorRecord SkeletalMeshSaver(ASkeletalMeshActor * SaveActor);

	/* Deserialize static mesh data to object params*/
	UFUNCTION(BlueprintCallable, Category = "RidersBPLibrary")
		static void SkeletalMeshLoader(ASkeletalMeshActor * LoadActor, FSkeletalActorRecord ActorData);

	UFUNCTION(BlueprintCallable, Category = "Utilities|FlowControl", meta = (WorldContext = "WorldContextObject", LatentInfo = "LatentInfo", Duration = "0.2", Keywords = "sleep"))
		static void	RidersDelay(UObject* WorldContextObject, float Duration, struct FLatentActionInfo LatentInfo);


	
};
