// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "SaveGame/Riders_SaveGame.h"
#include "Custom/Riders_UMGTypes.h"
#include "VehicleContent/VehiclePartsComponents.h"
#include "GameplayStatics/RidersBlueprintFunctionLibrary.h"
#include "Paths.h"
#include "PlatformFilemanager.h"
#include "MusicPlayer/WavePlayer.h"
#include "Riders_GameInstance.generated.h"


template <class FunctorType>
class PlatformFileFunctor : public IPlatformFile::FDirectoryVisitor	//GenericPlatformFile.h
{
public:

	virtual bool Visit(const TCHAR* FilenameOrDirectory, bool bIsDirectory) override
	{
		return Functor(FilenameOrDirectory, bIsDirectory);
	}

	PlatformFileFunctor(FunctorType&& FunctorInstance)
		: Functor(MoveTemp(FunctorInstance))
	{
	}

private:
	FunctorType Functor;
};

template <class Functor>
PlatformFileFunctor<Functor> MakeDirectoryVisitor(Functor&& FunctorInstance)
{
	return PlatformFileFunctor<Functor>(MoveTemp(FunctorInstance));
}


/**
 * 
 */
UCLASS()
class RIDERS_API URiders_GameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	static FORCEINLINE bool GetDirectories(const FString& FullPathOfBaseDir, TArray<FString>& DirsOut, bool Recursive = false, const FString& ContainsStr = "")
	{
		FString Str;
		auto FilenamesVisitor = MakeDirectoryVisitor(
			[&](const TCHAR* FilenameOrDirectory, bool bIsDirectory)
		{
			if (bIsDirectory)
			{
				//Using a Contains Filter?
				if (ContainsStr != "")
				{
					Str = FPaths::GetCleanFilename(FilenameOrDirectory);

					//Only if Directory Contains Str
					if (Str.Contains(ContainsStr))
					{
						if (Recursive) DirsOut.Push(FilenameOrDirectory); //need whole path for recursive
						else DirsOut.Push(Str);
					}
				}

				//Get ALL Directories!
				else
				{
					//Just the Directory
					Str = FPaths::GetCleanFilename(FilenameOrDirectory);

					if (Recursive) DirsOut.Push(FilenameOrDirectory); //need whole path for recursive
					else DirsOut.Push(Str);
				}
			}
			return true;
		}
		);
		if (Recursive)
		{
			return FPlatformFileManager::Get().GetPlatformFile().IterateDirectoryRecursively(*FullPathOfBaseDir, FilenamesVisitor);
		}
		else
		{
			return FPlatformFileManager::Get().GetPlatformFile().IterateDirectory(*FullPathOfBaseDir, FilenamesVisitor);
		}
	}







	URiders_GameInstance();

	/** Current Profile */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
		FString ProfileName;

	/** Player Money */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
		int32 Money;

	/** Current Vehicle */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
	class ARiders_Vehicle* Vehicle;

	UPROPERTY(VisibleAnywhere, Category = Basic, BlueprintReadWrite)
	class URiders_SaveGame* LoadedGame;

	/** Menu */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
		FTunningParts Menu;

	/** Cameras */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
		TArray<ACameraActor*> Cameras;

	/** PreviewCamera */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
		float MyProperty;



	/** VehicleIndex */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
		int32 CurrentVehicleIndex;


	UFUNCTION(BlueprintCallable, Category = "SaveGame")
	void SaveGame();

	UFUNCTION(BlueprintCallable, Category = "SaveGame")
	void LoadGame();

	/** Get Current Vehicle index */
	UFUNCTION(BlueprintCallable, Category = "Game Play")
		int32 GetCurrentVehicleIndex();

	/** GetAll Profiles */
	UFUNCTION(exec, BlueprintCallable, Category = "Game Play")
		TArray<FString> GetAllProfiles();

	UFUNCTION(exec, BlueprintCallable, Category = "Game Play")
		void CreateNewProfile(FString inProfileName);

	UFUNCTION(exec, BlueprintCallable, Category = "Game Play")
		void DeleteCurrentProfile(FString inProfileName);

	UFUNCTION(exec, BlueprintCallable, Category = "Game Play")
		FString GetCurrentProfile();

	UFUNCTION(exec, BlueprintCallable, Category = "Game Play")
		void SetCurrentProfile(FString inProfileName);

	UFUNCTION(exec, BlueprintCallable, Category = "Game Play")
		void AddVehicle(ARiders_Vehicle* BuyingVehicle);

	//UFUNCTION(BlueprintCallable, Category = "Game Play")
	//	ARiders_Vehicle* NextVehicle(FTransform SpawnPosition);

	//UFUNCTION(BlueprintCallable, Category = "Game Play")
	//	ARiders_Vehicle* PrevVehicle(FTransform SpawnPosition);

	UFUNCTION(BlueprintCallable, Category = "Game Play")
		FName GetCurrentVehicle(ARiders_Vehicle* CurentVehicle);


	/** vehicle part components */
	UPROPERTY(Category = Music, EditAnywhere, BlueprintReadWrite)
		class UWavePlayer* WavePlayer;

	// Money

	/** Add Player Money. */
	UFUNCTION(BlueprintCallable, Category = "Game Play",Exec)
	void AddMoney(int32 inMoney);


	virtual void Init() override;

	/** virtual function to allow custom GameInstances an opportunity to do cleanup when shutting down */
	virtual void Shutdown() override;

};
