// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Components/ActorComponent.h"
#include "Sound/SoundWave.h"
#include "Sound/AmbientSound.h"
#include "Runtime/MediaAssets/Public/MediaPlayer.h"
#include "Runtime/MediaAssets/Public/MediaPlaylist.h"
#include "Runtime/MediaAssets/Public/FileMediaSource.h"
//#include "Runtime/MediaAssets/Public/MediaSoundWave.h"
#include "WavePlayer.generated.h"


class UMediaPlayer;
class UMediaPlayList;
class UMediaSource;
class UMediaSoundWave;
class AAmbientSound;

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable, ClassGroup = (MusicPlayer), meta =(BlueprintSpawnableComponent))
class RIDERS_API UWavePlayer : public UActorComponent
{
	GENERATED_BODY()
	
public:

	// Sets default values for this component's properties
	UWavePlayer();

	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FString PathName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bManual;

	UFUNCTION(BlueprintCallable)
	bool GetAllWaveFiles();

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (EditCondition = "bManual"))
	TArray<FString> WaveFiles;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UMediaPlayer* MediaPlayer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (EditCondition = "bManual"))
	bool bUsePlayList;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (EditCondition = "bUsePlayList"))
	UMediaPlaylist* PlayList;

	UMediaSoundWave* SoundWave;

	UFUNCTION(BlueprintCallable)
	void InitSystem();

	void GeneratePlayList();


};

DECLARE_LOG_CATEGORY_EXTERN(WavePlayerLog, Log, All);
