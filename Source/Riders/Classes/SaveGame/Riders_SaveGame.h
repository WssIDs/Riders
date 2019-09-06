// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "Riders.h"
#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Custom/Riders_VehicleTypes.h"
#include "Custom/RidersSaveGameTypes.h"
#include "Riders_SaveGame.generated.h"


USTRUCT(BlueprintType)
struct FLevelRecord
{
	GENERATED_BODY();

	UPROPERTY(EditAnywhere, Category = Basic, BlueprintReadWrite, SaveGame)
		TArray<FStaticActorRecord> StaticMeshActors;

	UPROPERTY(EditAnywhere, Category = Basic, BlueprintReadWrite, SaveGame)
		TArray<FSkeletalActorRecord> SkeletalMeshActors;
};

/**
 * Main Riders SaveGame Class 
 */
UCLASS()
class RIDERS_API URiders_SaveGame : public USaveGame
{
	GENERATED_BODY()
	
	
	URiders_SaveGame(const FObjectInitializer& ObjectInitializer);

public:


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Basic")
		int32 CurrentVehicleIndex;

	UPROPERTY(VisibleAnywhere, Category = Basic, BlueprintReadWrite)
		FVector PlayerLocation;

	UPROPERTY(VisibleAnywhere, Category = Basic, BlueprintReadWrite)
		FRotator PlayerRotation;

	UPROPERTY(VisibleAnywhere, Category = Basic, BlueprintReadWrite)
		FString ProfileName;

	UPROPERTY(VisibleAnywhere, Category = Basic, BlueprintReadWrite)
		FString SaveSlotName;

	UPROPERTY(VisibleAnywhere, Category = Basic, BlueprintReadWrite)
		int32 UserIndex;

	UPROPERTY(VisibleAnywhere, Category = Basic, BlueprintReadWrite)
		int32 PlayerMoney;

	UPROPERTY(VisibleAnywhere, Category = Basic, BlueprintReadWrite, SaveGame)
		TArray<FVehicleRecord> VehiclesActors;

	UPROPERTY(VisibleAnywhere, Category = Basic, BlueprintReadWrite, SaveGame)
		TMap<FName,FLevelRecord> Levels;

	void SetSlotNameAsPlayerName(FString InSlotName);

};
