// Fill out your copyright notice in the Description page of Project Settings.

#include "MusicPlayer/WavePlayer.h"
#include "Misc/FileHelper.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"
#include "Components/AudioComponent.h"
#include "Misc/Paths.h"



// Sets default values for this component's properties
UWavePlayer::UWavePlayer()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	//bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	PathName = "Music";
	bManual = false;
}


// Called when the game starts
void UWavePlayer::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void UWavePlayer::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UWavePlayer::GetAllWaveFiles()
{
	FString MusicDir = FPaths::ProjectContentDir() + PathName + "/";


	if (!FPaths::DirectoryExists(MusicDir))
	{
		return false;
	}

	else if (FPaths::DirectoryExists(MusicDir))
	{
		UE_LOG(WavePlayerLog, Log, TEXT("%s"), *MusicDir);

		FString Ext = "mp3";

		FPaths::NormalizeDirectoryName(MusicDir);

		IFileManager& FileManager = IFileManager::Get();


		if (Ext == "")
		{
			Ext = "*.*";
		}
		else
		{
			Ext = (Ext.Left(1) == ".") ? "*" + Ext : "*." + Ext;
		}

		FString FinalPath = MusicDir + "/" + Ext;
		FileManager.FindFiles(WaveFiles, *FinalPath, true, false);


		if (WaveFiles.Num() == 0)
		{
			return false;
		}

		for (auto & item : WaveFiles)
		{
			item.RemoveFromEnd(".mp3", ESearchCase::IgnoreCase);

			UE_LOG(WavePlayerLog, Log, TEXT("%s"), *item);
		}

		return true;
	}

	return false;
}

void UWavePlayer::InitSystem()
{
	if (bManual)
	{
		if (!bUsePlayList)
		{
			GeneratePlayList();
		}


		else if (bUsePlayList)
		{
			WaveFiles.AddZeroed(0);

			for (int32 i = 0; i < PlayList->Num(); i++)
			{
				UFileMediaSource* Source = (UFileMediaSource*)PlayList->Get(i);

				FString item = Source->GetUrl();

				WaveFiles.Add(item);
			}
		}

		MediaPlayer->OpenPlaylistIndex(PlayList, 0);
	}

	else
	{
		if (GetAllWaveFiles())
		{
			GeneratePlayList();

			MediaPlayer->OpenPlaylistIndex(PlayList, 0);
		}

		else
		{
			UE_LOG(WavePlayerLog, Log, TEXT("No files in folder"));
		}
	}

}

void UWavePlayer::GeneratePlayList()
{
	if (WaveFiles.Num() > 0)
	{
		PlayList = NewObject<UMediaPlaylist>();

		if (PlayList->IsValidLowLevel())
		{
			UE_LOG(WavePlayerLog, Log, TEXT("%s"), *PlayList->GetName());

			for (auto & item : WaveFiles)
			{
				UFileMediaSource* Source = NewObject<UFileMediaSource>();

				if (Source->IsValidLowLevel())
				{
					Source->SetFilePath(FPaths::ProjectContentDir() + PathName + "/" + item + ".mp3");

					UE_LOG(WavePlayerLog, Log, TEXT("%s"), *Source->GetUrl());

					PlayList->Add(Source);
				}
			}
		}
	}
}


DEFINE_LOG_CATEGORY(WavePlayerLog);
