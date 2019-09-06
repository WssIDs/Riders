// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Components/ArrowComponent.h"
#include "Curves/CurveLinearColor.h"
#include "Engine/TimelineTemplate.h"
#include "Components/DirectionalLightComponent.h"
#include "Components/SkyLightComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Custom/Riders_DayNightSystemTypes.h"
#include "Riders_DayNight_System.generated.h"

class UArrowComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FChangedTimeOfDayDelegate,ETimesOfDay,TimeDay);


UCLASS(ClassGroup = (Lights, DayNightSystem), meta = (ChildCanTick))
class RIDERS_API ARiders_DayNight_System : public AActor
{
	GENERATED_BODY()


		FRotator SunRot;
	FRotator MoonRot;
	float TimelineRate;
	static const int32 TimelinesCount = 5;


private:

		/**  The main scene for Sky Actor */
		UPROPERTY(meta = (AllowPrivateAccess = "true"))
		class USceneComponent* Scene;

		// Reference to editor visualization arrow
		UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UArrowComponent* SunLightArrowComponent;

		// Reference to editor visualization arrow
		UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UArrowComponent* MoonLightArrowComponent;

		/** Main Mesh Component */
		UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* SkyMeshComponent;

		/** Sun Light Component */
		UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UDirectionalLightComponent* SunLight;

		/** Moon Light Component */
		UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UDirectionalLightComponent* MoonLight;

		/** Sky Light Component */
		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USkyLightComponent* SkyLight;

	void UpdateSunPosition();

	void InitSky();

public:	
	// Sets default values for this actor's properties
	ARiders_DayNight_System();

	UFUNCTION()
	void ReceiveChangedTimeOfDay(ETimesOfDay TimeDay);

	/** When changed time of day */
	UFUNCTION(BlueprintImplementableEvent)
	void ChangedTimeOfDay(ETimesOfDay TimeDay);

	UPROPERTY(BlueprintAssignable, Category = "TimeOfDay")
		FChangedTimeOfDayDelegate OnChangedTimeOfDayDelegate;


	/* Sky Material*/
	UPROPERTY(Replicated)
		UMaterialInstanceDynamic* SkyMaterial;

	/** Horizon */
	UPROPERTY(EditAnywhere, Category = "Sky")
		FRuntimeCurveLinearColor HorizontColorCurve;

	/** Zenith */
	UPROPERTY(EditAnywhere, Category = "Sky")
		FRuntimeCurveLinearColor ZenithColorCurve;

	/** Clouds */
	UPROPERTY(EditAnywhere, Category = "Sky")
		FRuntimeCurveLinearColor CloudColorCurve;


	/** Refresh Material */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sky")
		bool RefreshMaterial;

	/** ColorsDeterminedBySunPos */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sky")
		bool ColorsDeterminedBySunPosition;

	/** Cloud Speed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sky")
		float CloudSpeed;

	/** Sun Brightness */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sky")
		float SunBrightness;

	/** Cloud Opacity */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sky")
		float CloudOpacity;

	/** Stars Brightness */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sky")
		float StarsBrightness;

	/** Moon Brightness */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sky")
		float MoonBrightness;



	/** Sun Height */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Override Settings", meta = (UIMin = "-1", UIMax = "1"))
		float SunHeight;

	/** Horizon Falloff */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Override Settings")
		float HorizonFalloff;

	/** Horizon Color */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Override Settings")
		FLinearColor HorizonColor;

	/** Horizon Color */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Override Settings")
		FLinearColor ZenithColor;

	/** Horizon Color */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Override Settings")
		FLinearColor OveralColor;

	/** Horizon Color */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Override Settings")
		FLinearColor CloudColor;

	/** Main Sky Material */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
		UMaterialInterface* MainMaterial;

	/** Main Sky Mesh */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkyMesh")
		UStaticMesh* SkyMesh;


	////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////

	/** SunPitchCurve */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimeLine")
		FRuntimeFloatCurve SunPitchCurve;

	/** SunYawCurve */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimeLine")
		FRuntimeFloatCurve SunYawCurve;

	/** Time 24 curve */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimeLine")
		FRuntimeFloatCurve Time24Curve;

	/** MoonPitchCurve */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimeLine")
		FRuntimeFloatCurve MoonPitchCurve;

	/** MoonYawCurve */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimeLine")
		FRuntimeFloatCurve MoonYawCurve;

	/** HourDuration (in Real Minutes)*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time", meta = (UIMin = "1", UIMax = "60"))
		int32 HourDuration;


	UFUNCTION(Exec)
		void SetTimeDuration(float inRate);

	/* Current Time */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
		FTime DayTime;

	/** Current Times of Day */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Time")
		ETimesOfDay TimeOfDay;

	/*	Enable/Disable DayNightSystem */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
		bool bEnableDayNightSystem;

	FTimeline DNS_TimeLines[TimelinesCount];

	/** Function which gets called from the Timeline on a Tick */
	UFUNCTION()
		void UpdateSunPitch(float Value);

	/** Function which gets called from the Timeline on a Tick */
	UFUNCTION()
		void UpdateSunYaw(float Value);

	/** Function which gets called from the Timeline on a Tick */
	UFUNCTION()
		void UpdateTime24(float Value);

	/** Function which gets called from the Timeline on a Tick */
	UFUNCTION()
		void UpdateMoonPitch(float Value);

	/** Function which gets called from the Timeline on a Tick */
	UFUNCTION()
		void UpdateMoonYaw(float Value);

	/** Max Sun Light Intensity */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
		float SunLightIntensity;

	/** Max Sky Light Intensity*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
		float SkyLightIntensity;

	/** Max Moon Light Intensity*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
		float MoonLightIntensity;

	/** Sun Light Intensity Interpolation */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
		float SunLightIntensityInterpolation;

	/** Sky Light Intensity Interpolation */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
		float SkyLightIntensityInterpolation;

	/** Moon Light Intensity Interpolation */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
		float MoonLightIntensityInterpolation;



	/** Set DayTime */
	UFUNCTION(BlueprintCallable, Category = "Game Play")
		void SetTime(FTime inTime);


	virtual void UpdateMovement(float DeltaTime);

	///////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;


	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override;

#if WITH_EDITOR

	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;

	//virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedChainEvent) override;

#endif



public:

	/** Returns ArrowComponent subobject **/
	class UArrowComponent* GetSunLightArrowComponent() const;

	/** Returns ArrowComponent subobject **/
	class UArrowComponent* GetMoonLightArrowComponent() const;

	class UStaticMeshComponent* GetSkyMeshComponent() const;

	class UDirectionalLightComponent* GetSunLightComponent() const;

	class UDirectionalLightComponent* GetMoonLightComponent() const;

	class USkyLightComponent* GetSkyLightComponent() const;
	
};


DECLARE_LOG_CATEGORY_EXTERN(SkySystemLog, Log, All);