// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "GameFramework/GameMode.h"
#include "Custom/Riders_XMLTypes.h"
#include "Runtime/CoreUObject/Public/UObject/UnrealType.h"

#include "Sound/SoundWave.h"
#include "Riders_GameMode.generated.h"


UENUM()
enum class ETypeSort : uint8
{
	Type_ASC  UMETA(DisplayName = "ASC"),
	Type_DESC UMETA(DisplayName = "DESC"),
};


/**
 * 
 */
UCLASS()
class ARiders_GameMode : public AGameMode
{
	GENERATED_BODY()

	

public:

// Constructor declaration
	ARiders_GameMode();

	/** The start player vehicle. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Classes)
	TSubclassOf<class ARiders_Vehicle> StartVehicleClass;

	//FString xmlString;
	//FString rootElementName;

	TMap<int32, FString> HumanMap;

	UFUNCTION(BlueprintCallable, Category = "Test")
		void InitHumanMap();

	UFUNCTION(BlueprintCallable, Category = "Test")
		void AddItemHumanMap(int32 idx, FString Text);

	UFUNCTION(BlueprintCallable, Category = "Test")
		void SortHumanMapByKey(ETypeSort Type);

	UFUNCTION(BlueprintCallable, Category = "Test")
		void OutHumanMap();

	//FString TestStr;
	//FString inserttxt;

	/** Does the thing. */
	UFUNCTION(exec,BlueprintCallable, Category = "Game Play")
		void DoXmlFile();

	/** Load Color Data from Xml file */
	UFUNCTION(exec,BlueprintCallable, Category = "Game Play")
		TArray<FXmlColorData> LoadDataFromXml();

	/** Does end of game handling for the online layer */
	//virtual void RestartPlayer(class AController* NewPlayer);
};
