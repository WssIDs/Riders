// Fill out your copyright notice in the Description page of Project Settings.

#include "Riders/Classes/GameInstance/Riders_GameInstance.h"
#include "Riders.h"
#include "ObjectAndNameAsStringProxyArchive.h"
#include "Runtime/Core/Public/Serialization/MemoryReader.h"
#include "Runtime/Core/Public/Serialization/MemoryWriter.h"
#include "Paths.h"
#include "PlatformFilemanager.h"
#include "Kismet/GameplayStatics.h"
#include "Riders/Classes/Pawns/Vehicles/Riders_Vehicle.h"


URiders_GameInstance::URiders_GameInstance()
{

}

void URiders_GameInstance::Init()
{
	Super::Init();

	if (!GConfig) return;
	//~~


	FString RidersSection = "Riders.Profile";

	//Retrieve String value
	GConfig->GetString(*RidersSection,TEXT("Profile"),ProfileName,GGameIni);


	LoadGame();


	//WavePlayer = NewObject<UWavePlayer>();

	//WavePlayer->InitSystem();
}

void URiders_GameInstance::Shutdown()
{
	Super::Shutdown();


	SaveGame();


	if (!GConfig) return;
	//~~

	//New Section to Add
	FString RidersSection = "Riders.Profile";

	//String
	GConfig->SetString(*RidersSection,TEXT("Profile"),*ProfileName,GGameIni);


	//ConfigCacheIni.h
	//void Flush( bool Read, const FString& Filename=TEXT("") );
	GConfig->Flush(false, GGameIni);
}






/////  Saving System


TArray<FString> URiders_GameInstance::GetAllProfiles()
{
	FString SaveDir = FPaths::ProjectSavedDir() + "SaveGames/";

	FString Ext = "sav";


	FPaths::NormalizeDirectoryName(SaveDir);

	IFileManager& FileManager = IFileManager::Get();

	//if (Ext == "")
	//{
	//	Ext = "*.*";
	//}
	//else
	//{
	//	Ext = (Ext.Left(1) == ".") ? "*" + Ext : "*." + Ext;
	//}

	TArray<FString> Files;

	TArray<FString> FileNames;

	GetDirectories(*SaveDir, Files);

	for (int32 i = 0; i < Files.Num(); i++)
	{
		FString SaveFile = SaveDir + "/" + Files[i] + "/" + "SaveGame." + Ext;

		if (FileManager.FileExists(*SaveFile))
		{
			FileNames.Add(Files[i]);
			UE_LOG(SaveGameLog, Log, TEXT("%s"), *Files[i]);
		}
	}

	return FileNames;
}

void URiders_GameInstance::CreateNewProfile(FString inProfileName)
{
	LoadedGame = Cast<URiders_SaveGame>(UGameplayStatics::CreateSaveGameObject(URiders_SaveGame::StaticClass()));

	if (LoadedGame)
	{
		if (UGameplayStatics::DoesSaveGameExist(inProfileName + "/SaveGame", 0))
		{
			UE_LOG(SaveGameLog, Error, TEXT("This profile already created"));
		}

		else
		{

			LoadedGame->PlayerMoney = 3000;
			UGameplayStatics::SaveGameToSlot(LoadedGame, inProfileName + "/SaveGame", LoadedGame->UserIndex);

			UE_LOG(SaveGameLog, Warning, TEXT("Profile has been created!"));



		}

	}

	else
	{
		UE_LOG(SaveGameLog, Error, TEXT("load game instance don't have"));
	}

}

void URiders_GameInstance::DeleteCurrentProfile(FString inProfileName)
{
	FString FileName = FPaths::ProjectSavedDir() + "SaveGames/" + inProfileName;
	UE_LOG(SaveGameLog, Error, TEXT("FileName = %s"), *FileName);




	if (!IFileManager::Get().DeleteDirectory(*FileName, false, true))
	{
		UE_LOG(SaveGameLog, Error, TEXT("Could Not Find File"));
		return;
	}
}

FString URiders_GameInstance::GetCurrentProfile()
{
	return ProfileName;
}

void URiders_GameInstance::SetCurrentProfile(FString inProfileName)
{

	if (UGameplayStatics::DoesSaveGameExist(inProfileName + "/SaveGame", 0))
	{
		ProfileName = inProfileName;
	}

	else
	{
		UE_LOG(SaveGameLog, Warning, TEXT("don't have this profile"));
	}

}

void URiders_GameInstance::AddVehicle(ARiders_Vehicle* BuyingVehicle)
{
	if (LoadedGame)
	{

		FVehicleRecord VehicleData;

		VehicleData.Class = BuyingVehicle->GetClass();

		VehicleData.ActorData = URidersBlueprintFunctionLibrary::ObjectSaver(BuyingVehicle);
		VehicleData.ComponentData = URidersBlueprintFunctionLibrary::ObjectSaver(BuyingVehicle->GetPartComponents());

		LoadedGame->VehiclesActors.Add(VehicleData);

		LoadedGame->CurrentVehicleIndex = 0;

		SaveGame();
	}
	else
	{
		UE_LOG(SaveGameLog, Error, TEXT("Can't to open savegame file"));
	}
}

//ARiders_Vehicle* URiders_GameInstance::NextVehicle(FTransform SpawnPosition)
//{
//	FString Profile = GetCurrentProfile();
//
//	UE_LOG(SaveGameLog, Warning, TEXT("Profile - %s"), *Profile);
//
//	URiders_GameInstance* GameInstance = Cast<URiders_GameInstance>(GetGameInstance());
//
//	UE_LOG(SaveGameLog, Warning, TEXT("GameInstance class - %s"), *GameInstance->GetName());
//
//	ARiders_Vehicle* VH = GameInstance->Vehicle;
//
//	UE_LOG(SaveGameLog, Warning, TEXT("VH class - %s"), *VH->GetName());
//
//	if (UGameplayStatics::DoesSaveGameExist(Profile + "/SaveGame", 0))
//	{
//		URiders_SaveGame* LoadGameInstance = Cast<URiders_SaveGame>(UGameplayStatics::LoadGameFromSlot(Profile + "/SaveGame", 0));
//
//		UE_LOG(SaveGameLog, Warning, TEXT("LoadGameInstance class - %s"), *LoadGameInstance->GetName());
//
//
//
//		if (LoadGameInstance->Vehicles.Num() > 1)
//		{
//			if (GameInstance->CurrentVehicleIndex < LoadGameInstance->Vehicles.Num())
//			{
//
//				GameInstance->CurrentVehicleIndex++;
//
//				UE_LOG(SaveGameLog, Warning, TEXT("index - %d, from - %d"), GameInstance->CurrentVehicleIndex, LoadGameInstance->Vehicles.Num());
//
//
//				VH->Destroy();
//
//				FActorSpawnParameters SpawnParams;
//				SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
//
//				UWorld* World = GetWorld();
//
//
//				UE_LOG(SaveGameLog, Warning, TEXT("Vehicle class = %s"), *LoadGameInstance->Vehicles[GameInstance->CurrentVehicleIndex].Vehicle->GetName());
//
//				VH = World->SpawnActor<ARiders_Vehicle>(LoadGameInstance->Vehicles[GameInstance->CurrentVehicleIndex].Vehicle, SpawnPosition.GetLocation(), SpawnPosition.GetRotation().Rotator(), SpawnParams);
//
//				if (VH)
//				{
//					UE_LOG(SaveGameLog, Warning, TEXT("VH - %s"), *VH->GetName());
//
//
//					VH->GetPartComponents()->PartsData = LoadGameInstance->Vehicles[GameInstance->CurrentVehicleIndex].VehiclePartData;
//					VH->UpdateVehicleProperties();
//				}
//
//				else
//				{
//					UE_LOG(SaveGameLog, Warning, TEXT("VH don't created"));
//				}
//			}
//
//			else
//			{
//				GameInstance->CurrentVehicleIndex = 0;
//			}
//		}
//
//	}
//
//	return VH;
//}

//ARiders_Vehicle* URiders_GameInstance::PrevVehicle(FTransform SpawnPosition)
//{
//	FString Profile = GetCurrentProfile();
//	URiders_GameInstance* GameInstance = Cast<URiders_GameInstance>(GetGameInstance());
//	ARiders_Vehicle* VH = GameInstance->Vehicle;
//
//	if (UGameplayStatics::DoesSaveGameExist(Profile + "/SaveGame", 0))
//	{
//		URiders_SaveGame* LoadGameInstance = Cast<URiders_SaveGame>(UGameplayStatics::LoadGameFromSlot(Profile + "/SaveGame", 0));
//
//		if (GameInstance->CurrentVehicleIndex >= 0)
//		{
//			VH->Destroy();
//
//			FActorSpawnParameters SpawnParams;
//			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
//
//			UWorld* World = GetWorld();
//
//
//			VH = World->SpawnActor<ARiders_Vehicle>(LoadGameInstance->Vehicles[GameInstance->CurrentVehicleIndex].Vehicle, SpawnPosition.GetLocation(), SpawnPosition.GetRotation().Rotator(), SpawnParams);
//
//			VH->GetPartComponents()->PartsData = LoadGameInstance->Vehicles[GameInstance->CurrentVehicleIndex].VehiclePartData;
//			VH->UpdateVehicleProperties();
//
//			GameInstance->CurrentVehicleIndex--;
//		}
//
//		else
//		{
//			GameInstance->CurrentVehicleIndex = LoadGameInstance->Vehicles.Num() - 1;
//		}
//
//	}
//
//	return VH;
//}

FName URiders_GameInstance::GetCurrentVehicle(ARiders_Vehicle* CurentVehicle)
{
	return CurentVehicle->VehicleBrand;
}




void URiders_GameInstance::AddMoney(int32 inMoney)
{
	Money += inMoney;
}

void URiders_GameInstance::SaveGame()
{

	//int32 VehicleIndex = GetCurrentVehicleIndex();

	////URiders_SaveGame* SaveGameInstance = Cast<URiders_SaveGame>(UGameplayStatics::CreateSaveGameObject(URiders_SaveGame::StaticClass()));
	//ARiders_GamePlayerController* Controller = Cast<ARiders_GamePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	//FString CurrentProfile = GetCurrentProfile();


	//UE_LOG(SaveGameLog, Error, TEXT("Profile = %s"), *CurrentProfile);

	//URiders_SaveGame* SaveGame;

	//if (UGameplayStatics::DoesSaveGameExist(CurrentProfile + "/SaveGame", 0))
	//{

	//	SaveGame = Cast<URiders_SaveGame>(UGameplayStatics::LoadGameFromSlot(CurrentProfile + "/SaveGame", 0));

	//	UE_LOG(SaveGameLog, Warning, TEXT("Current Vehicle index = %d"), VehicleIndex);

	//	ARiders_Vehicle* VH = Cast<ARiders_Vehicle>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));


	//	FVehicleData VehicleData;

	//	VehicleData.Vehicle = VH->GetClass();

	//	VehicleData.VehiclePartData = VH->GetPartComponents()->PartsData;



	//	SaveGame->PlayerLocation = VH->GetActorLocation();
	//	SaveGame->PlayerRotation = VH->GetActorRotation();

	//	SaveGame->PlayerMoney = Controller->PlayerMoney;

	//	SaveGame->Vehicles[VehicleIndex] = VehicleData;

	//	SaveGame->CurrentVehicleIndex = VehicleIndex;

	//	UGameplayStatics::SaveGameToSlot(SaveGame, CurrentProfile + "/SaveGame", SaveGame->UserIndex);
	//}

	//else
	//{
	//	UE_LOG(SaveGameLog, Error, TEXT("load game  don't have"));
	//}


	if (LoadedGame)
	{
		UGameplayStatics::SaveGameToSlot(LoadedGame, GetCurrentProfile() + "/SaveGame", LoadedGame->UserIndex);
	}
}

void URiders_GameInstance::LoadGame()
{

	FString SaveDir = FPaths::ProjectSavedDir() + "SaveGames/";

	FPaths::NormalizeDirectoryName(SaveDir);

	TArray<FString> Files;

	GetDirectories(*SaveDir, Files);

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, SaveDir);

	for (int32 i = 0; i < Files.Num(); i++)
	{
		IFileManager& FileManager = IFileManager::Get();

		FString SaveFile = SaveDir + "/" + Files[i] + "/" + "SaveGame.sav";

		if (FileManager.FileExists(*SaveFile))
		{
			//Files.Add(Files[i]);
			//UE_LOG(SaveGameLog, Log, TEXT("%s"), *Files[i]);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, Files[i]);
		}
	}


	if (LoadedGame == nullptr)
	{
		if (UGameplayStatics::DoesSaveGameExist(GetCurrentProfile() + "/SaveGame", 0))
		{
			LoadedGame = Cast<URiders_SaveGame>(UGameplayStatics::LoadGameFromSlot(GetCurrentProfile() + "/SaveGame", 0));

			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, GetCurrentProfile());


			//ARiders_GamePlayerController* Controller = Cast<ARiders_GamePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

			//UWorld* World = GetWorld();

			//ARiders_Vehicle* OldVH = Cast<ARiders_Vehicle>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

			//Controller->UnPossess();

			//OldVH->Destroy();

			//FActorSpawnParameters SpawnParams;
			//SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;


			//ARiders_Vehicle* VH = World->SpawnActor<ARiders_Vehicle>(LoadGame->Vehicles[GetCurrentVehicleIndex()].Vehicle, LoadGame->PlayerLocation, LoadGame->PlayerRotation, SpawnParams);

			//if (VH)
			//{
			//	Controller->Possess(VH);
			//	Controller->SetIgnoreMoveInput(true);
			//	VH = Cast<ARiders_Vehicle>(Controller->GetPawn());

			//	VH->GetPartComponents()->PartsData = LoadGame->Vehicles[0].VehiclePartData;
			//	VH->UpdateVehicleProperties();

			//	//VH->SetPartMaterial(VH->GetBodyMesh(), LoadGameInstance->Vehicles[0].VehiclePartData.Body.MaterialProperty);
			//	//VH->SetPartMaterial(VH->GetBodyMesh(), LoadGameInstance->Vehicles[0].VehiclePartData.Mirrors.MaterialProperty);
			//	//VH->SetPartMaterial(VH->GetBodyMesh(), LoadGameInstance->Vehicles[0].VehiclePartData.FrontBumper.MaterialProperty);
			//	//VH->SetPartMaterial(VH->GetBodyMesh(), LoadGameInstance->Vehicles[0].VehiclePartData.RearBumper.MaterialProperty);
			//	//VH->SetPartMaterial(VH->GetBodyMesh(), LoadGameInstance->Vehicles[0].VehiclePartData.Spoiler.MaterialProperty);
			//	//VH->SetPartMaterial(VH->GetRoofMesh(), LoadGameInstance->Vehicles[0].VehiclePartData.Roof.MaterialProperty);
			//}

			//else
			//{
			//	UE_LOG(SaveGameLog, Error, TEXT("Vehicle don't Spawn"));
			//}


			//FVector Location = LoadGame->PlayerLocation;
			//FRotator Rotation = LoadGame->PlayerRotation;

			//int32 PlayerMoney = LoadGame->PlayerMoney;

			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, Location.ToString());
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, Rotation.ToString());
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::FromInt(PlayerMoney));

		}

		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "No SaveGame files");
		}
	}
}

int32 URiders_GameInstance::GetCurrentVehicleIndex()
{
	if (LoadedGame)
	{
		return LoadedGame->CurrentVehicleIndex;
	}

	else
	{
		return 0;
	}
}
