// Fill out your copyright notice in the Description page of Project Settings.

#include "GameplayStatics/RidersBlueprintFunctionLibrary.h"
#include "ObjectAndNameAsStringProxyArchive.h"
#include "Runtime/Core/Public/Serialization/MemoryReader.h"
#include "Runtime/Core/Public/Serialization/MemoryWriter.h"
#include "DelayAction.h"



TArray<uint8> URidersBlueprintFunctionLibrary::ObjectSaver(UObject * SaveObject)
{
	TArray<uint8> ObjectData;
	if (SaveObject == nullptr) return ObjectData;


	FMemoryWriter MemoryWriter(ObjectData, true);
	// use a wrapper archive that converts FNames and UObject*'s to strings that can be read back in
	FRidersSaveGameArchive SaveGameArchive(MemoryWriter, false);
	// serialize the object
	SaveObject->Serialize(SaveGameArchive);

	return ObjectData;
}

void URidersBlueprintFunctionLibrary::ObjectLoader(UObject * LoadObject, TArray<uint8> ObjectData)
{
	if (ObjectData.Num() <= 0) return;
	//TODO how to check if valid binary?

	FMemoryReader MemoryReader(ObjectData, true);
	FRidersSaveGameArchive LoadGameArchive(MemoryReader, true);
	LoadObject->Serialize(LoadGameArchive);
}

FStaticActorRecord URidersBlueprintFunctionLibrary::StaticMeshSaver(AStaticMeshActor * SaveActor)
{
	FStaticActorRecord ActorData;

	ActorData.Class = SaveActor->GetClass();
	ActorData.Mesh = SaveActor->GetStaticMeshComponent()->GetStaticMesh();
	ActorData.Transform = SaveActor->GetActorTransform();

	FMemoryWriter DataWriter = FMemoryWriter(ActorData.ActorData);
	DataWriter.ArIsSaveGame = true;
	SaveActor->Serialize(DataWriter);
	return ActorData;
}

void URidersBlueprintFunctionLibrary::StaticMeshLoader(AStaticMeshActor * LoadActor, FStaticActorRecord ActorData)
{

	FMemoryReader Reader = FMemoryReader(ActorData.ActorData);
	LoadActor->Serialize(Reader);
	
	LoadActor->GetStaticMeshComponent()->SetStaticMesh(ActorData.Mesh);	//so we can properly save again
	
	LoadActor->SetMobility(EComponentMobility::Movable);
	LoadActor->GetStaticMeshComponent()->SetSimulatePhysics(true);

	//LoadActor->SetActorTransform(ActorData.Transform,false, nullptr, ETeleportType::TeleportPhysics);


}

FSkeletalActorRecord URidersBlueprintFunctionLibrary::SkeletalMeshSaver(ASkeletalMeshActor * SaveActor)
{
	FSkeletalActorRecord ActorData;

	ActorData.Class = SaveActor->GetClass();
	ActorData.Mesh = SaveActor->GetSkeletalMeshComponent()->SkeletalMesh;
	ActorData.Transform = SaveActor->GetActorTransform();

	FMemoryWriter DataWriter = FMemoryWriter(ActorData.ActorData);
	DataWriter.ArIsSaveGame = true;
	SaveActor->Serialize(DataWriter);
	return ActorData;
}

void URidersBlueprintFunctionLibrary::SkeletalMeshLoader(ASkeletalMeshActor * LoadActor, FSkeletalActorRecord ActorData)
{	
	
	

	FMemoryReader Reader = FMemoryReader(ActorData.ActorData);
	LoadActor->Serialize(Reader);

	LoadActor->GetSkeletalMeshComponent()->SetSkeletalMesh(ActorData.Mesh);	//so we can properly save again
	
	//LoadActor->SetActorTransform(ActorData.Transform, false, nullptr, ETeleportType::TeleportPhysics);

	//LoadActor->GetSkeletalMeshComponent()->SetSimulatePhysics(true);
}


void URidersBlueprintFunctionLibrary::RidersDelay(UObject* WorldContextObject, float Duration, FLatentActionInfo LatentInfo)
{
	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		FLatentActionManager& LatentActionManager = World->GetLatentActionManager();
		if (LatentActionManager.FindExistingAction<FDelayAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL)
		{
			LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID, new FDelayAction(Duration, LatentInfo));
		}
	}
}
