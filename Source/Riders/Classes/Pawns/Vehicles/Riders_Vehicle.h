#pragma once

#include "CoreMinimal.h"
#include "GenericPlatformMath.h"
#include "Sound/SoundCue.h"
#include "Materials/MaterialInstanceDynamic.h"

/* FMOD Include */
#include "FMODStudioClasses.h"

/* Components */
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/PointLightComponent.h"
#include "Components/SpotLightComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Particles/ParticleSystemComponent.h"

#include "Light/Riders_DayNight_System.h"
#include "GameplayStatics/RidersBlueprintFunctionLibrary.h"

#include "Custom/Riders_VehicleTypes.h"

/* Components owns */
#include "Pawns/Vehicles/Riders_WheeledVehicle.h"
#include "Riders_Vehicle.generated.h"


USTRUCT(BlueprintType)
struct FParamVH
{
	GENERATED_BODY()

	/* maximum acceleration */
	UPROPERTY(Category = "Riders Vehicle Settings", BlueprintReadOnly, SaveGame)
		int32 Acceleration;

	/* maximum controlling  */
	UPROPERTY(Category = "Riders Vehicle Settings", BlueprintReadOnly, SaveGame)
		int32 Controlling;

	/* maximum speed*/
	UPROPERTY(Category = "Riders Vehicle Settings", BlueprintReadOnly, SaveGame)
		int32 MaxSpeed;
};


USTRUCT(BlueprintType)
struct FCameraSettings 
{
	GENERATED_BODY();

	/** Camera Distance */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		float Distance;

	/** CameraPosition */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		FVector CameraLocation;

	/** CameraPosition */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		FVector CameraOffset;

	/** CameraPosition */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		FRotator CameraRotation;

	/** Camera Rotation lag */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		bool bEnableCameraRotationLag;

};



USTRUCT(BlueprintType)
struct FFreeCameraSettings
{
	GENERATED_USTRUCT_BODY();

	/** Min Camera Distance */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		float MinDistance;

	/** Max Camera Distance */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		float MaxDistance;

	/** Camera Step */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (ClampMin = "0.0", UIMin = "0.0", ClampMax = "10.0", UIMax = "10.0"))
		float CameraStep;

	/** Camera Rotation lag */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		bool bEnableCameraRotationLag;

};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHandBrakeDelegate, bool, bHandBrake);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FReverseDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStopDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FForwardDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FIdleDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMoveCompleted);


/**
 * 
  Riders Vehicle Class with features
 */
UCLASS(abstract, ClassGroup = RidersVehicle, BlueprintType)
class RIDERS_API ARiders_Vehicle : public ARiders_WheeledVehicle
{
	GENERATED_BODY()

	// Constructor declaration
	ARiders_Vehicle();

	static FName VehicleCameraComponentName;

	static FName HornSoundComponentName;
	static FName GearShiftSoundComponentName;

	/** Event when this actor bumps into a blocking object, or blocks another actor that bumps into it. */
	virtual void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;
				  
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	virtual void BeginPlay() override;

	/* Debug Camera + HUD */
	virtual void ToggleDebug();


	void TeleportToLCP();

	UFUNCTION(BlueprintCallable, Category = "Vehicle")
	bool IsVehicleInverted();

	float TimeToRespawn;

	float OverallDistance;

	float DiffNumber;

	bool bNightLightActive;
	bool bDayLightActivate;

	bool DebugTouchWheel[4];
	bool DebugWheelSkidding[4];
	bool DebugWantToSkid[4];

	void InitVehicleMaterials();

	FTimerHandle StartEngineHandle;

	UFUNCTION()
	void CarNightLightChange(ETimesOfDay TimeOfDay);

	void CarNightLighActivate();

	void CarNightLighDeactivate();

	float DefaultFOV;

	/* Update brake system material */
	void UpdateBrakeSystem(float DeltaTime);

	void DestroyCachedComponents(float DeltaTime);

	TArray<float> CurrentSkidMarksTimes;

	void EngineSoundGenerate(float DeltaTime);

	float LastSpeed;

	UTireConfig* DefaultTireConfigs[4];
	bool bDrifting;

public:

	FLinearColor InBodyColor;

	UPROPERTY(Category = "Decals", VisibleDefaultsOnly, BlueprintReadWrite)
		UDecalComponent* Left_Door_Decal;

	UPROPERTY(Category = "Decals", VisibleDefaultsOnly, BlueprintReadWrite)
		UDecalComponent* Right_Door_Decal;

	UPROPERTY(Category = "Decals", VisibleDefaultsOnly, BlueprintReadWrite)
		UDecalComponent* Roof_Decal;

	UPROPERTY(Category = "Decals", VisibleDefaultsOnly, BlueprintReadWrite)
		UDecalComponent* Hood_Decal;


	/** is handbrake active? */
	UFUNCTION(BlueprintCallable, Category = "Vehicle")
		bool IsHandbrakeActive() const;

	bool bOnMoveForward;

	bool bOnMoveReverse;

	bool bOnStopping;

	bool bOnIdle;

	UFUNCTION(BlueprintNativeEvent)
		void ReceiveHandBrake(bool bHandBrake);

	UFUNCTION()
		void ReceiveMoveForward();

	UFUNCTION()
		void ReceiveMoveReverse();

	/* When vehicle is stopping */
	UFUNCTION()
		void ReceiveStop();

	UFUNCTION()
		void ReceiveIdle();

	UPROPERTY(BlueprintAssignable, Category = "Events")
		FHandBrakeDelegate OnHandBrake;

	UPROPERTY(BlueprintAssignable, Category = "Events")
		FReverseDelegate OnMoveReverse;

	UPROPERTY(BlueprintAssignable, Category = "Events")
		FForwardDelegate OnMoveForward;

	UPROPERTY(BlueprintAssignable, Category = "Events")
		FStopDelegate OnStopping;

	UPROPERTY(BlueprintAssignable, Category = "Events")
		FIdleDelegate OnIdle;


	UFUNCTION(BlueprintCallable, Category = "Sounds")
		virtual void StopEngineSound();

	UPROPERTY(Category = "Distance", EditDefaultsOnly, BlueprintReadWrite, meta = (UIMin = "0", UIMax = "9"), SaveGame)
		int32 MeterUnits;

	UPROPERTY(Category = "Distance", EditDefaultsOnly, BlueprintReadWrite, meta = (UIMin = "0", UIMax = "9"), SaveGame)
		int32 MeterDecs;

	UPROPERTY(Category = "Distance", EditDefaultsOnly, BlueprintReadWrite, meta = (UIMin = "0", UIMax = "9"), SaveGame)
		int32 Meterhundreds;

	UPROPERTY(Category = "Distance", EditDefaultsOnly, BlueprintReadWrite, meta = (UIMin = "0", UIMax = "9"), SaveGame)
		int32 KilometerUnits;

	UPROPERTY(Category = "Distance", EditDefaultsOnly, BlueprintReadWrite, meta = (UIMin = "0", UIMax = "9"), SaveGame)
		int32 KilometerDecs;

	UPROPERTY(Category = "Distance", EditDefaultsOnly, BlueprintReadWrite, meta = (UIMin = "0", UIMax = "9"), SaveGame)
		int32 Kilometerhundreds;

	/************************************************************************/
	/* Vehicle Information                                                  */
	/************************************************************************/

	/* Vehicle Brand Logo */
	UPROPERTY(EditAnywhere, Category = "Information", BlueprintReadOnly, SaveGame)
		UTexture2D* VehicleBrandLogo;

	/* Vehicle Brand Name */
	UPROPERTY(EditAnywhere, Category = "Information", BlueprintReadOnly, SaveGame)
		FName VehicleBrand;

	/* Vehicle Model Name */
	UPROPERTY(EditAnywhere, Category = "Information", BlueprintReadOnly, SaveGame)
		FName VehicleModel;

	/* Cost vehicle */
	UPROPERTY(EditAnywhere, Category = "Information", BlueprintReadWrite, SaveGame)
		int32 Cost;

	/* others Params of the Vehicle */
	UPROPERTY(Category = "Information", BlueprintReadOnly, SaveGame)
		FParamVH Specifications;

	/************************************************************************/
	/* Nitro                                                                */
	/************************************************************************/

	/** bEnable Nitro */
	UPROPERTY(EditAnywhere, Category = "Nitro", BlueprintReadWrite, SaveGame)
		bool bEnableNitro;

	/** Count of Nitro */
	UPROPERTY(EditAnywhere, Category = "Nitro", BlueprintReadWrite, SaveGame)
		float Nitro;

	/** Max Count of Nitro */
	UPROPERTY(EditAnywhere, Category = "Nitro", BlueprintReadWrite, SaveGame)
		float NitroMax;

	/** Boost Magnitude */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nitro", meta = (UIMin = "10", UIMax = "20"), SaveGame)
		float BoostMagnitude;

	/** Speed in KmpH when nitro start recovery */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nitro", SaveGame)
		float SpeedForStartNitroRecovery;




	/************************************************************************/
	/* Camera Settings                                                      */
	/************************************************************************/

	/** camera shake on default */
	UPROPERTY(Category = Effects, EditDefaultsOnly)
		TSubclassOf<UCameraShake> IdleCameraShake;

	/** Camera FOV when using Nitro */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nitro")
		float NitroCameraFieldOfView;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nitro", meta = (UIMin = "0.5", UIMax = "5.0"))
	float PostProcessSpeedInterpolate;

	/** First View Settings */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera")
		FCameraSettings FirstView;

	/** Second View Settings */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera")
		FCameraSettings SecondView;

	/** Third View Settings */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera")
		FCameraSettings HoodView;

	/** Free View Settings */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera")
		FFreeCameraSettings FreeView;

	/** WIP Setting FlyingCamera Step */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera", meta = (ClampMin = "0.02", UIMin = "0.02", ClampMax = "1.0", UIMax = "1.0"))
		float FlyingCameraStep;

	/** WIP Standby time up to the Flying Camera */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera")
		float StandbyTimeToFlyingCamera;



	/************************************************************************/
	/* BrakeDisk Heating                                                    */
	/************************************************************************/

	/** The MyProperty */
	UPROPERTY(BlueprintReadWrite, Category = "BrakeSystem")
		float CurrentBrakeDiscTemperature;

	/** The MyProperty */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BrakeSystem", SaveGame)
		float AirCooling;

	/** The MyProperty */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BrakeSystem", SaveGame)
		float MaxBrakeDiscTemperature;

	/** The MyProperty */
	UPROPERTY(BlueprintReadWrite, Category = "BrakeSystem", SaveGame)
		float CoolingEffect;

	/** The MyProperty */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BrakeSystem")
		int32 BrakeMaterialindex;

	/** The MyProperty */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BrakeSystem")
		FName BrakeMaterialSlotName;

	/** The MyProperty */
	UPROPERTY(BlueprintReadWrite, Category = "BrakeSystem", Replicated)
		UMaterialInstanceDynamic* BrakeDiskMaterial;

	/** The MyProperty */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BrakeSystem")
		float MinSpeedToReactBrakeDiscHeat;

	/** The MyProperty */
	UPROPERTY(BlueprintReadWrite, Category = "BrakeSystem")
		float TimeBrakes;



	/************************************************************************/
	/* AI Control                                                           */
	/************************************************************************/

	/** LastSpeed */
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "AIControl")
		float LastAISpeed;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "AIControl")
		bool bRollingStop;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "AIControl")
		float Started;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "AIControl")
		float Distance;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "AIControl")
		FVector Destination;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "AIControl")
		EAIState AIState;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "AIControl")
		float LenghPath;

	UPROPERTY(BlueprintAssignable, Category = "AIControl", BlueprintCallable)
		FMoveCompleted MoveCompleted;

	UFUNCTION()
		void WhenMoveCompleted();


	void UpdateAIMovement();

	/* flag to show debug */
	bool bShowDebug;


	/** GetMaxSpeed */
	UFUNCTION(BlueprintCallable, Category = "Vehicle")
	float GetVehicleMaxSpeed() const;

	/** get current speed */
	float GetVehicleSpeed() const;

	/** get current RPM */
	float GetEngineRotationSpeed() const;

	/** get maximum RPM */
	float GetEngineMaxRotationSpeed() const;

	////////////////// LIGHT //////////////////

	/* Serialize object params to object data*/
	UFUNCTION(BlueprintCallable, Category = "RidersBPLibrary")
		TArray<uint8> ObjectSaver();

	/* Deserialize object data to object params*/
	UFUNCTION(BlueprintCallable, Category = "RidersBPLibrary")
		void ObjectLoader(TArray<uint8> ObjectData);
	
	FTransform VehicleRespawnPosition;

	/** Toggle FrontLight */
	UFUNCTION(BlueprintCallable, Category = "Vehicle")
	void FrontLightToggle();

	/** Turn On FrontLight */
	UFUNCTION(BlueprintCallable, Category = "Vehicle")
	void FrontLightTurnOn();

	/** Turn Off FrontLight */
	UFUNCTION(BlueprintCallable, Category = "Vehicle")
	void FrontLightTurnOff();

	/** StartEngine */
	UFUNCTION(BlueprintCallable, Category = "Vehicle")
		void PressStartEngine();

	virtual void PostInitializeComponents() override;
	
	virtual void PostInitProperties() override;

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override;


	UFUNCTION(BlueprintCallable)
	void SetCameraType(int32 Types);

protected:

	UPROPERTY(Category = "Lights", VisibleDefaultsOnly, BlueprintReadOnly)
		UPointLightComponent* RevL_Light;

	UPROPERTY(Category = "Lights", VisibleDefaultsOnly, BlueprintReadOnly)
		UPointLightComponent* RevR_Light;

	UPROPERTY(Category = "Lights", VisibleDefaultsOnly, BlueprintReadOnly)
		UPointLightComponent* RL_Light;

	UPROPERTY(Category = "Lights", VisibleDefaultsOnly, BlueprintReadOnly)
		UPointLightComponent* RR_Light;

	UPROPERTY(Category = "Lights", VisibleDefaultsOnly, BlueprintReadOnly)
		USpotLightComponent* FL_Light;

	UPROPERTY(Category = "Lights", VisibleDefaultsOnly, BlueprintReadOnly)
		USpotLightComponent* FR_Light;


	/** Boom Component that will offset the camera */
	UPROPERTY(Category = "Camera", VisibleDefaultsOnly, BlueprintReadOnly)
		USpringArmComponent* BoomComponent;

	/** Camera component that will be our viewpoint */
	UPROPERTY(Category = "Camera", VisibleDefaultsOnly, BlueprintReadOnly)
		UCameraComponent* VehicleCameraComponent;

	/** camera shake on impact */
	UPROPERTY(Category = Effects, EditDefaultsOnly)
	TSubclassOf<UCameraShake> ImpactCameraShake;

	UPROPERTY(Category = Effects, EditDefaultsOnly)
	UParticleSystem* WheelSlipFX;

	/** Time tire marks show */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Effects")
	float SkidMarkTime;

	UParticleSystemComponent* LeftBoosterParticleSystemComponent;

	UParticleSystemComponent* RightBoosterParticleSystemComponent;

	UPROPERTY(Category = "Effects", EditDefaultsOnly, BlueprintReadWrite)
		UParticleSystem* BoosterEffect;

	UPROPERTY(Category = "Effects", EditDefaultsOnly, BlueprintReadWrite)
		UParticleSystem* GearShiftParticle;

	UPROPERTY(Category = "Effects", EditDefaultsOnly, BlueprintReadWrite)
		UParticleSystem* SmokeEffect;

	/*Smoke effect Exhaust */
		UParticleSystemComponent* LeftSmokeParticleSystemComponent;

	/*Smoke effect Exhaust */
		UParticleSystemComponent* RightSmokeParticleSystemComponent;

	UParticleSystemComponent* LeftGearShiftParticleSystemComponent;

	UParticleSystemComponent* RightGearShiftParticleSystemComponent;

	/** Engine Audio Component (FMOD) */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Sounds")
		UFMODAudioComponent* EngineSoundComponent;

	UAudioComponent* HornSoundComponent;

	/** HornSound */
	UPROPERTY(Category= "Sounds",EditDefaultsOnly, BlueprintReadWrite)
		USoundCue* HornSound;

	UAudioComponent* GearShiftSoundComponent;

	/** GearShiftSound */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sounds")
		USoundCue* GearShiftSound;

	/** GearShiftSound */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sounds")
		USoundCue* BoosterSound;

	/* Left Booster Sound Component */
		UAudioComponent* LeftBoosterSoundComponent;

	/* Right Booster Sound Component */
		UAudioComponent* RightBoosterSoundComponent;

	/** impact FX config */
	UPROPERTY(Category = "Effects", EditDefaultsOnly)
	TSubclassOf<class ARiders_VehicleImpactEffect> ImpactTemplate;

	/** The minimum amount of normal force that must be applied to the chassis to spawn an Impact Effect and camera shake effect */
	UPROPERTY(EditAnywhere, Category = Effects)
	float ImpactEffectNormalForceThreshold;


	/////////////////////////////////////////////////////////
	///////////////////// Skid //////////////////////////////
	/////////////////////////////////////////////////////////


	/** skid FX components */
	UParticleSystemComponent* SkidWheelPSC[4];
	FName SkidSockets[4];

	TArray<UParticleSystemComponent*> CacheSkidPSC;

	UPROPERTY(Category = "Effects", EditDefaultsOnly)
	UParticleSystem* SkidWheelFX;

	/** skid sound stop */
	UPROPERTY(Category = "Sounds", EditDefaultsOnly)
		USoundCue* SkidSoundStop;

	/** skid sound */
	UPROPERTY(Category = "Sounds", EditDefaultsOnly)
		USoundCue* SkidSound;

	/** skid fadeout time */
	UPROPERTY(Category = "Effects", EditDefaultsOnly)
	float SkidFadeoutTime;

	/** skid effects cannot play if velocity is lower than this */
	UPROPERTY(Category = "Effects", EditDefaultsOnly)
	float SkidThresholdVelocity;

	/** skid effects will play if absolute value of tire longitudinal slip is more than this. */
	UPROPERTY(Category = "Effects", EditDefaultsOnly, meta = (ClampMin = "0.0", UIMin = "0.0", ClampMax = "1.0", UIMax = "1.0"))
	float LongSlipSkidThreshold;

	/** skid effects will play if absolute value of tire lateral slip is more than this. */
	UPROPERTY(Category = "Effects", EditDefaultsOnly, meta = (ClampMin = "0.0", UIMin = "0.0", ClampMax = "1.0", UIMax = "1.0"))
	float LateralSlipSkidThreshold;

	/** skid effects will play if absolute value of tire longitudinal slip is more than this. */
	UPROPERTY(Category = "Effects", EditDefaultsOnly, meta = (ClampMin = "0.0", UIMin = "0.0", ClampMax = "1.0", UIMax = "1.0"))
	float LongSlipSmokeThreshold;

	/** skid effects will play if absolute value of tire lateral slip is more than this. */
	UPROPERTY(Category = "Effects", EditDefaultsOnly, meta = (ClampMin = "0.0", UIMin = "0.0", ClampMax = "1.0", UIMax = "1.0"))
	float LateralSlipSmokeThreshold;

	UAudioComponent* SkidAudioComponent[4];

	/** The amount of spring compression required during landing to play sound */
	UPROPERTY(Category = "Effects", EditDefaultsOnly)
	float SpringCompressionLandingThreshold;

	/** if skidding is shorter than this value, SkidSoundStop won't be played */
	UPROPERTY(Category = "Effects", EditDefaultsOnly)
		float SkidDurationRequiredForStopSound;


	////////////////////////////////////////////

	/** FMOD Switch */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Debug")
	bool bEnableFMOD;


	//////////////////////////////////////////



	/** is vehicle currently skidding */
	bool bSkidding[4];

	/** is vehicle tire currently skidding */
	bool bSkiddingSound[4];

	/** time when skidding started */
	float SkidStartTime[4];


	float VehicleThrottle;

	float VehicleSteering;

	/** is handbrake active? */
	uint32 bHandbrakeActive : 1;

	UFUNCTION(exec)
		void RotVehicle();

	void CalculateDistance(float DeltaTime);

	/////////////////////////////////////////////////////////////////
	/**************************** NITRO ****************************/
	/////////////////////////////////////////////////////////////////

	/* Allow to Activate Boosters */
	bool bActivateBoost;

	void ActivateBoosters();
	void DeactivateBoosters();

	UFUNCTION(exec)
	void SetFullNitro();

	UFUNCTION(exec)
	void AddNitro(int32 CountNitro);

	//UFUNCTION(exec)
	//	void InitRandomVehicleColor();

	/* Allow switch camera */
	bool bSwitchCameraTypes;

	/* Overall time to switch to the fly camera type */
	float TimeFlyCam;
	
	void FlyingCamera(float DeltaTime);

	/* Enable Fly Camera */
	bool bFlyCamera;

	/* Camera Type from 0 to 2 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, SaveGame)
	int32 TypeCamera;

	/* Prev Camera Position */
	int32 LastCameraType;

	/* Update Camera position */
	//virtual void CalcCamera(float DeltaTime, FMinimalViewInfo& OutResult);

	/* Function update every frame */
	virtual void Tick(float DeltaTime);


	/* Switching Camera types */
	void ChangeCamera();
	
	bool bScreenShotsCamera;
	
	void ToggleScreenShotCamera();

	void ScreenShotCameraZoomIn();

	void ScreenShotCameraZoomOut();


	void FrontViewActivate();

	void FrontViewDeactivate();

	void LeftViewActivate();

	void LeftViewDeactivate();

	void RightViewActivate();

	void RightViewDeactivate();

	UFUNCTION(exec)
	void SetAutoGearBox(bool bAutoGearBox);

	int32 CurrentGear = 0;

	void GearUP();

	void GearDown();

	UFUNCTION(BlueprintCallable)
	void HandBrakeOn();

	UFUNCTION(BlueprintCallable)
	void HandBrakeOff();

	UFUNCTION(BlueprintCallable)
	void MoveForward(float Value);

	UFUNCTION(BlueprintCallable)
	void MoveRight(float Value);

	FTimerHandle DriftHandle;
	float TimerDuration;
	void DriftingStop();

	bool bEngineStarted;

	/////////////////// SOUNDS ////////////////////////////


	virtual void StartEngineSound();

	virtual void StartEngineSoundTimed();

	UPROPERTY(EditAnywhere, Category = "Sounds")
	float EngineStartOffsetSecs;

	virtual void VehiclePlayEnterSound();

	virtual void PlayHornSound();

	virtual void StopHornSound();

	////////////////// LIGHT //////////////////

	bool bFrontLightActivate;


	/** update effects under wheels */
	void UpdateWheelEffects(float DeltaTime);

	/* update effect whesel skid and sounds */
	void WheelFXUpdate();

	/* Change blendweight post process by time */
	void InterpolateCameraPostProcess(float DeltaSeconds);


public:

	virtual void OnConstruction(const FTransform& Transform) override;

	UFUNCTION()
		void SetInbodyColor(FLinearColor Color);


#if WITH_EDITOR

	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;

	virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedChainEvent) override;

#endif


	UFUNCTION(BlueprintCallable, Category = "Vehicle")
		FName GetVehicleBrand();

	UFUNCTION(BlueprintCallable, Category = "Vehicle")
		FName GetVehicleModel();

	UFUNCTION(BlueprintCallable, Category = "Vehicle")
		UTexture2D* GetVehicleBrandLogo();

};