// Fill out your copyright notice in the Description page of Project Settings.

#include "SaveGame/Riders_SaveGame.h"
#include "Riders.h"

URiders_SaveGame::URiders_SaveGame(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SaveSlotName = TEXT("TestSaveSlot");
	UserIndex = 0;
	CurrentVehicleIndex = 0;
}

void URiders_SaveGame::SetSlotNameAsPlayerName(FString InSlotName)
{

	SaveSlotName = InSlotName;
	//SaveSlotName = PC->PlayerState->PlayerName;
}



