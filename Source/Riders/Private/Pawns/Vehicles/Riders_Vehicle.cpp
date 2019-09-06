
#include "Pawns/Vehicles/Riders_Vehicle.h"
#include "Kismet/GameplayStatics.h"
#include "VehicleContent/VehiclePartsComponents.h"

#include "ObjectAndNameAsStringProxyArchive.h"
#include "Runtime/Core/Public/Serialization/MemoryReader.h"
#include "Runtime/Core/Public/Serialization/MemoryWriter.h"
#include "Runtime/Engine/Public/TimerManager.h"

#include "VehicleContent/RidersVehicleWheel.h"
#include "EngineUtils.h"
#include <Runtime\Engine\Classes\Kismet\KismetMathLibrary.h>



ARiders_Vehicle::ARiders_Vehicle()
{

	//this->PrimaryActorTick.bCanEverTick = true;

	//bTickInEditor = true;

	/* Set Default Mesh for Vehicle Class */
	//static ConstructorHelpers::FObjectFinder<USkeletalMesh> DefaultBaseMeshOb(TEXT("SkeletalMesh'/Game/Vehicles/Defaults/Vehicle_Base.Vehicle_Base'"));

	//static ConstructorHelpers::FObjectFinder<USkeletalMesh> DefaultBodyMeshOb(TEXT("SkeletalMesh'/Game/Vehicles/Audi/R8/Meshes/Default/Audi_R8_Body.Audi_R8_Body'"));
	//static ConstructorHelpers::FObjectFinder<USkeletalMesh> DefaultFrontBumperMeshOb(TEXT("SkeletalMesh'/Game/Vehicles/Audi/R8/Meshes/Default/Audi_R8_FrontBumper.Audi_R8_FrontBumper'"));
	//static ConstructorHelpers::FObjectFinder<USkeletalMesh> DefaultRearBumperMeshOb(TEXT("SkeletalMesh'/Game/Vehicles/Audi/R8/Meshes/Default/Audi_R8_RearBumper.Audi_R8_RearBumper'"));
	//static ConstructorHelpers::FObjectFinder<USkeletalMesh> DefaultInteriorMeshOb(TEXT("SkeletalMesh'/Game/Vehicles/Audi/R8/Meshes/Default/Audi_R8_Interior.Audi_R8_Interior'"));
	//static ConstructorHelpers::FObjectFinder<USkeletalMesh> DefaultMirrorsMeshOb(TEXT("SkeletalMesh'/Game/Vehicles/Audi/R8/Meshes/Default/Audi_R8_Mirrors.Audi_R8_Mirrors'"));
	//static ConstructorHelpers::FObjectFinder<USkeletalMesh> DefaultFrontLightMeshOb(TEXT("SkeletalMesh'/Game/Vehicles/Audi/R8/Meshes/Default/Audi_R8_FrontLights.Audi_R8_FrontLights'"));
	//static ConstructorHelpers::FObjectFinder<USkeletalMesh> DefaultTailLightMeshOb(TEXT("SkeletalMesh'/Game/Vehicles/Audi/R8/Meshes/Default/Audi_R8_TailLights.Audi_R8_TailLights'"));
	//static ConstructorHelpers::FObjectFinder<USkeletalMesh> DefaultWheelsMeshOb(TEXT("SkeletalMesh'/Game/Vehicles/Audi/R8/Meshes/Default/Audi_R8_Wheels.Audi_R8_Wheels'"));
	//static ConstructorHelpers::FObjectFinder<USkeletalMesh> DefaultSpolierMeshOb(TEXT("SkeletalMesh'/Game/Vehicles/Audi/R8/Meshes/Default/Audi_R8_Spoiler.Audi_R8_Spoiler'"));
	//static ConstructorHelpers::FObjectFinder<USkeletalMesh> DefaultRoofScoopMeshOb(TEXT("SkeletalMesh'/Game/Vehicles/Audi/R8/Meshes/Default/Audi_R8_RoofScoop.Audi_R8_RoofScoop'"));


	//if (DefaultBaseMeshOb.Succeeded())
	//{
	//	GetBaseMesh()->SetSkeletalMesh(DefaultBaseMeshOb.Object);
	//}


	//if (DefaultBodyMeshOb.Succeeded())
	//{
	//	GetBodyMesh()->SetSkeletalMesh(DefaultBodyMeshOb.Object);
	//}


	//if (DefaultFrontBumperMeshOb.Succeeded())
	//{
	//	GetFrontBumperMesh()->SetSkeletalMesh(DefaultFrontBumperMeshOb.Object);
	//}


	//if (DefaultRearBumperMeshOb.Succeeded())
	//{
	//	GetRearBumperMesh()->SetSkeletalMesh(DefaultRearBumperMeshOb.Object);
	//}


	//if (DefaultInteriorMeshOb.Succeeded())
	//{
	//	GetInteriorMesh()->SetSkeletalMesh(DefaultInteriorMeshOb.Object);
	//}


	//if (DefaultMirrorsMeshOb.Succeeded())
	//{
	//	GetMirrorsMesh()->SetSkeletalMesh(DefaultMirrorsMeshOb.Object);
	//}


	//if (DefaultFrontLightMeshOb.Succeeded())
	//{
	//	GetFrontLightMesh()->SetSkeletalMesh(DefaultFrontLightMeshOb.Object);
	//}

	//if (DefaultTailLightMeshOb.Succeeded())
	//{
	//	GetTailLightMesh()->SetSkeletalMesh(DefaultTailLightMeshOb.Object);
	//}

	//if (DefaultWheelsMeshOb.Succeeded())
	//{
	//	GetWheelsMesh()->SetSkeletalMesh(DefaultWheelsMeshOb.Object);
	//}

	//if (DefaultSpolierMeshOb.Succeeded())
	//{
	//	GetSpoilerMesh()->SetSkeletalMesh(DefaultSpolierMeshOb.Object);
	//}

	//if (DefaultRoofScoopMeshOb.Succeeded())
	//{
	//	GetRoofMesh()->SetSkeletalMesh(DefaultRoofScoopMeshOb.Object);
	//}

	bEnableFMOD = true;
	PostProcessSpeedInterpolate = 1.0f;


	// Relative Transform rule
	FAttachmentTransformRules RelativeRule = FAttachmentTransformRules::KeepRelativeTransform;


	// Create a spring arm component
	BoomComponent = CreateDefaultSubobject<USpringArmComponent>("BoomComponent");
	//BoomComponent->TargetOffset = FVector(0.f, 0.f, 60.f);
	BoomComponent->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
	BoomComponent->AttachToComponent(RootComponent,RelativeRule);
	BoomComponent->TargetArmLength = 170.0f;
	BoomComponent->bEnableCameraRotationLag = true;
	//BoomComponent->bEnableCameraLag = true;
	//BoomComponent->CameraLagSpeed = 25.0f;
	BoomComponent->CameraRotationLagSpeed = 5.f;
	BoomComponent->bInheritPitch = false;
	BoomComponent->bInheritRoll = false;
	BoomComponent->bInheritYaw = true;

	// Create camera component 
	VehicleCameraComponent = CreateDefaultSubobject<UCameraComponent>("VehicleCameraComponent");
	VehicleCameraComponent->SetupAttachment(BoomComponent, USpringArmComponent::SocketName);
	//VehicleCameraComponent->AttachToComponent(RootComponent, RelativeRule, BoomComponent->SocketName);
	VehicleCameraComponent->bUsePawnControlRotation = false;
	VehicleCameraComponent->FieldOfView = 90.f;

	DefaultFOV = VehicleCameraComponent->FieldOfView;

	

	FreeView.MinDistance = 120.0f;
	FreeView.MaxDistance = 250.0f;
	FreeView.CameraStep = 10.0f;

	FlyingCameraStep = 0.05f;
	StandbyTimeToFlyingCamera = 15.0f;


	/************************************************************************/
	/* Camera                                                               */
	/************************************************************************/

	FirstView.CameraLocation = FVector(0.0f, 0.0f, 60.0f);
	FirstView.CameraOffset = FVector(0.0f, 0.0f, 0.0f);
	FirstView.CameraRotation = FRotator(0.0f, 0.0f, 0.0f);
	FirstView.Distance = 180.0f;
	FirstView.bEnableCameraRotationLag = true;

	SecondView.CameraLocation = FVector(0.0f, 0.0f, 60.0f);
	SecondView.CameraOffset = FVector(0.0f, 0.0f, 0.0f);
	SecondView.CameraRotation = FRotator(0.0f, 0.0f, 0.0f);
	SecondView.Distance = 200.0f;
	FirstView.bEnableCameraRotationLag = true;


	HoodView.CameraLocation = FVector(0.0f, 0.0f, 0.0f);
	HoodView.CameraOffset = FVector(0.0f, 0.0f, 0.0f);
	HoodView.CameraRotation = FRotator(0.0f, 0.0f, 0.0f);
	HoodView.Distance = -63.0f;
	HoodView.bEnableCameraRotationLag = true;

	/*************   LIGHT ******************/


	// Create Front Left Light
	FL_Light = CreateDefaultSubobject<USpotLightComponent>("FL_Light");
	FL_Light->bVisible = false;
	FL_Light->AttachToComponent(RootComponent, RelativeRule, TEXT("Front_LeftLightSocket"));
	FL_Light->SetIsReplicated(true);

	FL_Light->InnerConeAngle = 45.0f;
	FL_Light->OuterConeAngle = 50.0f;
	FL_Light->AttenuationRadius = 5000.0f;
	FL_Light->LightColor = FColor(255, 255, 255);
	FL_Light->CastTranslucentShadows = true;
	FL_Light->bAffectDynamicIndirectLighting = true;
	FL_Light->bUseRayTracedDistanceFieldShadows = true;
	FL_Light->Intensity = 5000.0f;

	// Create Front Right Light
	FR_Light = CreateDefaultSubobject<USpotLightComponent>("FR_Light");
	FR_Light->bVisible = false;
	FR_Light->AttachToComponent(RootComponent, RelativeRule, TEXT("Front_RightLightSocket"));
	FR_Light->SetIsReplicated(true);

	FR_Light->InnerConeAngle = 45.0f;
	FR_Light->OuterConeAngle = 50.0f;
	FR_Light->AttenuationRadius = 5000.0f;
	FR_Light->LightColor = FColor(255, 255, 255);
	FR_Light->CastTranslucentShadows = true;
	FR_Light->bAffectDynamicIndirectLighting = true;
	FR_Light->bUseRayTracedDistanceFieldShadows = true;
	FR_Light->Intensity = 5000.0f;



	// Create Left RearLight

	RL_Light = CreateDefaultSubobject<UPointLightComponent>("RL_Light");
	RL_Light->bVisible = false;
	RL_Light->AttachToComponent(RootComponent, RelativeRule, TEXT("Rear_LeftLightSocket"));
	RL_Light->SetIsReplicated(true);

	RL_Light->AttenuationRadius = 55.0f;
	RL_Light->LightColor = FColor(255, 0, 0);
	RL_Light->CastTranslucentShadows = true;
	RL_Light->bAffectDynamicIndirectLighting = true;
	RL_Light->bUseRayTracedDistanceFieldShadows = true;
	RL_Light->Intensity = 1.0f;


	// Create Right RearLight

	RR_Light = CreateDefaultSubobject<UPointLightComponent>("RR_Light");
	RR_Light->bVisible = false;
	RR_Light->AttachToComponent(RootComponent, RelativeRule, TEXT("Rear_RightLightSocket"));
	RR_Light->SetIsReplicated(true);


	RR_Light->AttenuationRadius = 55.0f;
	RR_Light->LightColor = FColor(255, 0, 0);
	RR_Light->CastTranslucentShadows = true;
	RR_Light->bAffectDynamicIndirectLighting = true;
	RR_Light->bUseRayTracedDistanceFieldShadows = true;
	RR_Light->Intensity = 1.0f;


	// Create Left RevL_Light

	RevL_Light = CreateDefaultSubobject<UPointLightComponent>("RevL_Light");
	RevL_Light->bVisible = false;
	RevL_Light->AttachToComponent(RootComponent, RelativeRule, TEXT("Reverse_LeftLightSocket"));
	RevL_Light->LightColor = FColor::White;
	RevL_Light->SetSourceRadius(50.0f);
	RevL_Light->SetIsReplicated(true);

	RevL_Light->AttenuationRadius = 45.0f;
	RevL_Light->LightColor = FColor(255, 255, 255);
	RevL_Light->CastTranslucentShadows = true;
	RevL_Light->bAffectDynamicIndirectLighting = true;
	RevL_Light->bUseRayTracedDistanceFieldShadows = true;
	RevL_Light->Intensity = 1.0f;

	// Create Right RevL_Light

	RevR_Light = CreateDefaultSubobject<UPointLightComponent>("RevR_Light");
	RevR_Light->bVisible = false;
	RevR_Light->AttachToComponent(RootComponent, RelativeRule, TEXT("Reverse_RightLightSocket"));
	RevR_Light->LightColor = FColor::White;
	RevR_Light->SetSourceRadius(50.0f);
	RevR_Light->SetIsReplicated(true);

	RevR_Light->AttenuationRadius = 45.0f;
	RevR_Light->LightColor = FColor(255, 255, 255);
	RevR_Light->CastTranslucentShadows = true;
	RevR_Light->bAffectDynamicIndirectLighting = true;
	RevR_Light->bUseRayTracedDistanceFieldShadows = true;
	RevR_Light->Intensity = 1.0f;


	/****************** BODY DECALS ************************/


	Left_Door_Decal = CreateDefaultSubobject<UDecalComponent>("Left_Door_Decal");
	Left_Door_Decal->SetRelativeScale3D(FVector(3.0f, 3.0f, 3.0f));
	Left_Door_Decal->SetRelativeLocation(FVector(6.0f, -36.0f, 20.0f));
	Left_Door_Decal->SetRelativeRotation(FRotator(0.0f, 90.0f, 90.0f));
	Left_Door_Decal->DecalSize = FVector(1.0f, 1.0f, 1.0f);
	Left_Door_Decal->AttachToComponent(RootComponent,RelativeRule);

	Right_Door_Decal = CreateDefaultSubobject<UDecalComponent>("Right_Door_Decal");
	Right_Door_Decal->SetRelativeScale3D(FVector(3.0f, 3.0f, 3.0f));
	Right_Door_Decal->SetRelativeLocation(FVector(6.0f, 36.0f, 20.0f));
	Right_Door_Decal->SetRelativeRotation(FRotator(0.0f, -90.0f, 90.0f));
	Right_Door_Decal->DecalSize = FVector(1.0f, 1.0f, 1.0f);
	Right_Door_Decal->AttachToComponent(RootComponent, RelativeRule);

	Roof_Decal = CreateDefaultSubobject<UDecalComponent>("Roof_Decal");
	Roof_Decal->SetRelativeScale3D(FVector(3.0f, 3.0f, 3.0f));
	Roof_Decal->DecalSize = FVector(1.0f, 1.0f, 1.0f);
	Roof_Decal->AttachToComponent(RootComponent, RelativeRule);

	Hood_Decal = CreateDefaultSubobject<UDecalComponent>("Hood_Decal");
	Hood_Decal->SetRelativeScale3D(FVector(3.0f, 3.0f, 3.0f));
	Hood_Decal->DecalSize = FVector(1.0f, 1.0f, 1.0f);
	Hood_Decal->AttachToComponent(RootComponent, RelativeRule);

	/****************  REAR LIGHTS *****************/

	bSwitchCameraTypes = true;

	/*************   DEBUG *****************/

	bShowDebug = false;


	/*************   MOVEMENT **************/

	bEngineStarted = false;


	/******************* Nitro ****************/

	NitroMax = 100.0f;
	Nitro = 100.0f;

	SpeedForStartNitroRecovery = 30.0f;
	BoostMagnitude = 20.0f;

	bActivateBoost = false;

	bEnableNitro = false;

	OverallDistance = 0;
	TypeCamera = 0;

	SkidThresholdVelocity = 30;
	SkidFadeoutTime = 0.1f;
	LongSlipSkidThreshold = 0.8f;
	LateralSlipSkidThreshold = 0.8f;
	LongSlipSmokeThreshold = 0.98f;
	LateralSlipSmokeThreshold = 0.98f;
	SkidDurationRequiredForStopSound = 1.5f;

	SpringCompressionLandingThreshold = 250000.f;

	ImpactEffectNormalForceThreshold = 100000.f;


	SkidSockets[0] = TEXT("F_L_SkidSocket");
	SkidSockets[1] = TEXT("F_R_SkidSocket");
	SkidSockets[2] = TEXT("B_L_SkidSocket");
	SkidSockets[3] = TEXT("B_R_SkidSocket");

	SkidMarkTime = 20.0f;

	//////////////// FMOD //////////////////////


	EngineSoundComponent = CreateDefaultSubobject<UFMODAudioComponent>("EngineSoundComponent");
	EngineSoundComponent->bAutoActivate = false;
	EngineSoundComponent->AttachToComponent(RootComponent,RelativeRule, TEXT("EngineSoundSocket"));




	////////////// AI ////////////////////////

	Distance = 100.0f;

	// Delegates

	MoveCompleted.AddDynamic(this, &ARiders_Vehicle::WhenMoveCompleted);
	OnHandBrake.AddDynamic(this, &ARiders_Vehicle::ReceiveHandBrake);

	OnMoveForward.AddDynamic(this, &ARiders_Vehicle::ReceiveMoveForward);
	OnMoveReverse.AddDynamic(this, &ARiders_Vehicle::ReceiveMoveReverse);
	OnStopping.AddDynamic(this, &ARiders_Vehicle::ReceiveStop);
	OnIdle.AddDynamic(this, &ARiders_Vehicle::ReceiveIdle);
}


FName ARiders_Vehicle::GetVehicleBrand()
{
	return VehicleBrand;
}

FName ARiders_Vehicle::GetVehicleModel()
{
	return VehicleModel;
}

UTexture2D* ARiders_Vehicle::GetVehicleBrandLogo()
{
	return VehicleBrandLogo;
}

void ARiders_Vehicle::PostInitProperties()
{
	Super::PostInitProperties();
}


void ARiders_Vehicle::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}


void ARiders_Vehicle::WhenMoveCompleted()
{
	if (bShowDebug)
	{
		UE_LOG(VehicleLog, Log, TEXT("BeginPlay event"));
	}
}

void ARiders_Vehicle::UpdateAIMovement()
{	
	FRotator AIRot = FRotationMatrix::MakeFromX(GetActorLocation() - Destination).Rotator();

	AIRot.Normalize();

	float turn = 0.0f;

	float Min = -75.0f;
	float Max = 75.0f;

	//((InclusiveMin ? (Value >= Min) : (Value > Min)) && (InclusiveMax ? (Value <= Max) : (Value < Max)));




	if (AIRot.Yaw >= Min && AIRot.Yaw <= Max)
	{
		turn = FMath::GetMappedRangeValueUnclamped(FVector2D(-180, 180), FVector2D(-1, 1), AIRot.Yaw);
	}

	else

	{
		turn = 0.0f;
	}

	GetVehicleMovement()->SetSteeringInput(turn);
}

void ARiders_Vehicle::BeginPlay()
{
	Super::BeginPlay();

	DefaultTireConfigs[0] = GetVehicleMovement()->Wheels[0]->TireConfig;
	DefaultTireConfigs[1] = GetVehicleMovement()->Wheels[1]->TireConfig;
	DefaultTireConfigs[2] = GetVehicleMovement()->Wheels[2]->TireConfig;
	DefaultTireConfigs[3] = GetVehicleMovement()->Wheels[3]->TireConfig;

	if (bShowDebug)
	{
		if (Controller->IsValidLowLevel())
		{
			UE_LOG(VehicleLog, Log, TEXT("%s"), *GetController()->GetFName().ToString());
		}
	}


	SetCameraType(TypeCamera);

	InitVehicleMaterials();



	// init Respawn position After Start Game
	VehicleRespawnPosition.SetLocation(GetActorLocation());
	VehicleRespawnPosition.SetRotation(GetActorRotation().Quaternion());
	VehicleRespawnPosition.SetScale3D(GetActorScale());

	Specifications.MaxSpeed = GetVehicleMaxSpeed();


	//if (IsControlled())
	//{
		for (TActorIterator<ARiders_DayNight_System> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		{
			if (ActorItr)
			{
				ActorItr->OnChangedTimeOfDayDelegate.AddDynamic(this, &ARiders_Vehicle::CarNightLightChange);

				CarNightLightChange(ActorItr->TimeOfDay);
			}
		}
	//}

}


void ARiders_Vehicle::InitVehicleMaterials()
{

	// Add Reference to materials

		TMap<FName,FSLightMaterialProp> FrontLightsAr = GetPartComponents()->FrontLight;

		for (auto & Item : FrontLightsAr)
		{
			for (auto & Component : GetComponentsByTag(USkeletalMeshComponent::StaticClass(), Item.Key))
			{
				USkeletalMeshComponent* MeshComponent = Cast<USkeletalMeshComponent>(Component);

				FSLightMaterialProp Data = Item.Value;

				if (MeshComponent->GetMaterial(MeshComponent->GetMaterialIndex(Data.MaterialSlotName)))
				{

					UMaterialInstanceDynamic* Material = UMaterialInstanceDynamic::Create(MeshComponent->GetMaterial(MeshComponent->GetMaterialIndex(Data.MaterialSlotName)), this);

					if (Material)
					{
						MeshComponent->SetMaterialByName(Data.MaterialSlotName, Material);

						GetPartComponents()->FrontLightMaterials.Add(Item.Key, Material);

						if (bShowDebug)
						{
							UE_LOG(VehicleLog, Log, TEXT("Material for - %s"), *Component->GetName());
						}
					}
				}
			}
		}


		TArray<FSLightMaterialProp> RearLightsAr = GetPartComponents()->RearLight;

		for (auto & Item : RearLightsAr)
		{
			for (auto & Component : GetComponentsByTag(USkeletalMeshComponent::StaticClass(), Item.Name))
			{

				USkeletalMeshComponent* MeshComponent = Cast<USkeletalMeshComponent>(Component);

				FSLightMaterialProp Data = Item;

				if (MeshComponent->GetMaterial(MeshComponent->GetMaterialIndex(Data.MaterialSlotName)))
				{

					UMaterialInstanceDynamic* Material = UMaterialInstanceDynamic::Create(MeshComponent->GetMaterial(MeshComponent->GetMaterialIndex(Data.MaterialSlotName)), this);

					if (Material)
					{
						MeshComponent->SetMaterialByName(Data.MaterialSlotName, Material);

						FLightMaterials LightData;
						LightData.Name = Item.Name;
						LightData.Material = Material;

						GetPartComponents()->RearLightMaterials.Add(LightData);

						if (bShowDebug)
						{
							UE_LOG(VehicleLog, Log, TEXT("Material for - %s"), *Component->GetName());
						}
					}
				}


			}
		}


		TMap<FName, FSLightMaterialProp> ReverseLightsAr = GetPartComponents()->ReverseLight;

		for (auto & Item : ReverseLightsAr)
		{
			for (auto & Component : GetComponentsByTag(USkeletalMeshComponent::StaticClass(), Item.Key))
			{

				USkeletalMeshComponent* MeshComponent = Cast<USkeletalMeshComponent>(Component);

				FSLightMaterialProp Data = Item.Value;

				if (MeshComponent->GetMaterial(MeshComponent->GetMaterialIndex(Data.MaterialSlotName)))
				{

					UMaterialInstanceDynamic* Material = UMaterialInstanceDynamic::Create(MeshComponent->GetMaterial(MeshComponent->GetMaterialIndex(Data.MaterialSlotName)), this);

					if (Material)
					{
						MeshComponent->SetMaterialByName(Data.MaterialSlotName, Material);

						GetPartComponents()->ReverseLightMaterials.Add(Item.Key, Material);

						if (bShowDebug)
						{
							UE_LOG(VehicleLog, Log, TEXT("Material for - %s"), *Component->GetName());
						}
					}
				}
			}
		}


		BrakeDiskMaterial = UMaterialInstanceDynamic::Create(GetWheelMeshes()[0]->GetMaterial(GetWheelMeshes()[0]->GetMaterialIndex(BrakeMaterialSlotName)), this);

		if (BrakeDiskMaterial)
		{
			if (GetWheelMeshes().Num() > 0)
			{
				for (int32 i = 0; i < GetWheelMeshes().Num(); i++)
				{
					GetWheelMeshes()[i]->SetMaterialByName(BrakeMaterialSlotName, BrakeDiskMaterial);
				}
			}
		}
}

void ARiders_Vehicle::CarNightLightChange(ETimesOfDay TimeOfDay)
{
	if (bShowDebug)
	{
		UE_LOG(VehicleLog, Log, TEXT("DayNight System change day"));
	}

	if (TimeOfDay == ETimesOfDay::DNS_Night)
	{
		CarNightLighActivate();
	}

	else if (TimeOfDay == ETimesOfDay::DNS_Day)
	{
		CarNightLighDeactivate();
	}


}

void ARiders_Vehicle::CarNightLighActivate()
{
	if (!bNightLightActive)
	{
		FrontLightTurnOn();

		//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("CarNightActivated"));
		bNightLightActive = true;
		bDayLightActivate = false;
	}
}

void ARiders_Vehicle::CarNightLighDeactivate()
{
	if (!bDayLightActivate)
	{
		FrontLightTurnOff();

		//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("CarNightDeactivated"));
		bDayLightActivate = true;
		bNightLightActive = false;
	}
}

void ARiders_Vehicle::UpdateBrakeSystem(float DeltaTime)
{

	float CurrentSpeed = FMath::Abs(GetVehicleMovement()->GetForwardSpeed() * 0.036);

	if (IsHandbrakeActive())
	{
		if (CurrentSpeed < MinSpeedToReactBrakeDiscHeat)
		{
			if (CurrentBrakeDiscTemperature > 0)
			{
				if (CurrentBrakeDiscTemperature < MaxBrakeDiscTemperature)
				{
					CoolingEffect = AirCooling;
				}

				else
				{
					CoolingEffect = CurrentSpeed / Specifications.MaxSpeed;
				}


				CurrentBrakeDiscTemperature = CurrentBrakeDiscTemperature - CoolingEffect;

				if (BrakeDiskMaterial)
				{
					BrakeDiskMaterial->SetScalarParameterValue("TemperatureBrake", FMath::GetMappedRangeValueClamped(FVector2D(0.0f, MaxBrakeDiscTemperature), FVector2D(0.0f, 1.0f), CurrentBrakeDiscTemperature));
				}
			}
		}

		else
		{
			if (CurrentBrakeDiscTemperature < MaxBrakeDiscTemperature)
			{
				TimeBrakes = TimeBrakes + DeltaTime;

				if (CurrentSpeed >= MinSpeedToReactBrakeDiscHeat)
				{
					CurrentBrakeDiscTemperature = CurrentBrakeDiscTemperature + (CurrentSpeed / Specifications.MaxSpeed * TimeBrakes);

					if (BrakeDiskMaterial)
					{
						BrakeDiskMaterial->SetScalarParameterValue("TemperatureBrake", FMath::GetMappedRangeValueClamped(FVector2D(0.0f, MaxBrakeDiscTemperature), FVector2D(0.0f, 1.0f), CurrentBrakeDiscTemperature));
					}
				}
			}
		}
	}

	else
	{
		TimeBrakes = 0;

		if (CurrentBrakeDiscTemperature > 0)
		{
			if (CurrentBrakeDiscTemperature < MaxBrakeDiscTemperature)
			{
				CoolingEffect = AirCooling;
			}

			else
			{
				CoolingEffect = CurrentSpeed / Specifications.MaxSpeed;
			}


			CurrentBrakeDiscTemperature = CurrentBrakeDiscTemperature - CoolingEffect;

			if (BrakeDiskMaterial)
			{
				BrakeDiskMaterial->SetScalarParameterValue("TemperatureBrake", FMath::GetMappedRangeValueClamped(FVector2D(0.0f, MaxBrakeDiscTemperature), FVector2D(0.0f, 1.0f), CurrentBrakeDiscTemperature));
			}
		}
	}
}

void ARiders_Vehicle::DestroyCachedComponents(float DeltaTime)
{
	if (CacheSkidPSC.Num() > 0)
	{
		for (int32 i = 0; i < CacheSkidPSC.Num(); i++)
		{ 
			if (CurrentSkidMarksTimes.Num() > 0)
			{
				if (CurrentSkidMarksTimes[i] > 0)
				{
					CurrentSkidMarksTimes[i] = CurrentSkidMarksTimes[i] - DeltaTime;

					if (CurrentSkidMarksTimes[i] <= 0)
					{
						CacheSkidPSC[i]->UnregisterComponent();

						CacheSkidPSC.RemoveAt(i);

						CurrentSkidMarksTimes.RemoveAt(i);

						if (bShowDebug)
						{
							if (CacheSkidPSC.Num() > 0)
							{
								UE_LOG(VehicleLog, Warning, TEXT("Need to remove the %d components"), CacheSkidPSC.Num());
							}

							else if (CacheSkidPSC.Num() == 0)
							{
								UE_LOG(VehicleLog, Warning, TEXT("All Cached components has been deleted!"));
							}
						}
					}
				}
			}
		}
	}
}

void ARiders_Vehicle::EngineSoundGenerate(float DeltaTime)
{
	EngineSoundComponent->SetParameter("RPM",GetVehicleMovement()->GetEngineRotationSpeed());

	EngineSoundComponent->SetParameter("Load", (GetVehicleMovement()->GetEngineRotationSpeed() - LastSpeed) / DeltaTime);

	LastSpeed = GetVehicleMovement()->GetEngineRotationSpeed();
}

void ARiders_Vehicle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Controlled by user

	//URiders_FrontWheels* FLWheel = Cast<URiders_FrontWheels>(GetVehicleMovement()->Wheels[0]);
	//URiders_FrontWheels* FRWheel = Cast<URiders_FrontWheels>(GetVehicleMovement()->Wheels[1]);

	//URiders_RearWheels* RLWheel = Cast<URiders_RearWheels>(GetVehicleMovement()->Wheels[2]);
	//URiders_RearWheels* RRWheel = Cast<URiders_RearWheels>(GetVehicleMovement()->Wheels[3]);

	if (bDrifting)
	{
	//	if (FMath::Abs(FLWheel->DebugLatForce) > 250000.0f)
	//	{

	//		UE_LOG(VehicleLog, Error, TEXT("Drifting On"));
	//		UE_LOG(VehicleLog, Error, TEXT("Lat force %f"), RLWheel->DebugLatForce);
	//		UE_LOG(VehicleLog, Error, TEXT("Lat slip %f"), RLWheel->DebugLatSlip);
	//	}
	//	else
	//	{
	//		bDrifting = false;
	//		UE_LOG(VehicleLog, Error, TEXT("Drifting off"));
	//		UE_LOG(VehicleLog, Log, TEXT("Lat force %f"), RLWheel->DebugLatForce);
	//		UE_LOG(VehicleLog, Log, TEXT("Lat slip %f"), RLWheel->DebugLatSlip);

	//		GetWorldTimerManager().SetTimer(DriftHandle, this, &ARiders_Vehicle::DriftingStop, 0.0f, false, 1.0f);

	//	}
	}


	if (IsPlayerControlled())
	{
		//UE_LOG(VehicleLog, Log, TEXT("%s"),*GetController()->GetFName().ToString());

		if (TypeCamera == 1)
		{
			if (BoomComponent->TargetArmLength < SecondView.Distance)
			{
				BoomComponent->TargetArmLength = FMath::FInterpTo(BoomComponent->TargetArmLength, SecondView.Distance, GetWorld()->GetDeltaSeconds(), 10.0f);

			}
		}

		FlyingCamera(DeltaTime);
	}

	else
	{
		//UE_LOG(VehicleLog, Log, TEXT("%s"), *GetController()->GetFName().ToString());
	}


	// VEHICLE AUTORESPAWN 

	if (IsVehicleInverted())
	{
		TimeToRespawn += DeltaTime;

		if (TimeToRespawn >= 10.0f)
		{
			TeleportToLCP();
		}
	}

	//  NITRO USE

	if (bEnableNitro)
	{
		float CurrentSpeed = GetVehicleMovement()->GetForwardSpeed() * 0.036f;

		if (Nitro < NitroMax)
		{
			if (!bActivateBoost)
			{

				if (VehicleThrottle > 0)
				{
					Nitro = Nitro + (CurrentSpeed / (Specifications.MaxSpeed * 10));

					if (Nitro > 100.0f)
					{
						Nitro = 100.0f;
					}
				}

			}
		}

		if (Nitro > 0.0f)
		{
			if (bActivateBoost)
			{
				if (VehicleThrottle > 0)
				{
					FVector BoostDir;

					BoostDir = GetActorForwardVector();

					GetBaseMesh()->SetAllPhysicsLinearVelocity(BoostDir* BoostMagnitude, true);

					Nitro = Nitro - (BoostMagnitude / 20.0f);
				}
			}
		}


		FDetachmentTransformRules DetachRule = FDetachmentTransformRules::KeepWorldTransform;

		if (Nitro <= 0.0f)
		{
			if (LeftBoosterSoundComponent != nullptr)
			{
				LeftBoosterSoundComponent->Stop();

				LeftBoosterSoundComponent->DetachFromComponent(DetachRule);
				LeftBoosterSoundComponent->UnregisterComponent();
				LeftBoosterSoundComponent->DestroyComponent();

				LeftBoosterSoundComponent = nullptr;
			}

			if (RightBoosterSoundComponent != nullptr)
			{
				RightBoosterSoundComponent->Stop();

				RightBoosterSoundComponent->DetachFromComponent(DetachRule);
				RightBoosterSoundComponent->UnregisterComponent();
				RightBoosterSoundComponent->DestroyComponent();

				RightBoosterSoundComponent = nullptr;
			}

			if (LeftBoosterParticleSystemComponent != nullptr)
			{
				LeftBoosterParticleSystemComponent->DeactivateSystem();
				LeftBoosterParticleSystemComponent->DetachFromComponent(DetachRule);
				LeftBoosterParticleSystemComponent->UnregisterComponent();
				LeftBoosterParticleSystemComponent->DestroyComponent();

				LeftBoosterParticleSystemComponent = nullptr;
			}

			if (RightBoosterParticleSystemComponent != nullptr)
			{
				RightBoosterParticleSystemComponent->DeactivateSystem();
				RightBoosterParticleSystemComponent->DetachFromComponent(DetachRule);
				RightBoosterParticleSystemComponent->UnregisterComponent();
				RightBoosterParticleSystemComponent->DestroyComponent();

				RightBoosterParticleSystemComponent = nullptr;
			}

			VehicleCameraComponent->PostProcessBlendWeight = FMath::FInterpTo(VehicleCameraComponent->PostProcessBlendWeight, 0.0f, DeltaTime, PostProcessSpeedInterpolate);

			VehicleCameraComponent->FieldOfView = FMath::FInterpTo(VehicleCameraComponent->FieldOfView, DefaultFOV, DeltaTime, PostProcessSpeedInterpolate);

			Nitro = 0;

			//DeactivateBoosters();
		}

		InterpolateCameraPostProcess(DeltaTime);

		//UE_LOG(VehicleLog, Log, TEXT("Nitro = %f"),Nitro);
	}

	//if (EngineAC)
	//{

		//EngineAC->SetParameter(TEXT("Load"), GetVehicleMovement()->GetEngineRotationSpeed());

		//SoundForGear - int params
	if (VehicleThrottle != 0)
	{
		if (GetVehicleMovement()->GetCurrentGear() == 0 && GetVehicleMovement()->GetForwardSpeed() * 3600.f / 100000.f > 10.0f)
		{

			if (VehicleThrottle > 0)
			{

				const USkeletalMeshSocket* LeftSocket = GetBaseMesh()->GetSocketByName("BoosterLeftSocket");

				if (LeftSocket)
				{
					if (!LeftGearShiftParticleSystemComponent)
					{
						LeftGearShiftParticleSystemComponent = NewObject<UParticleSystemComponent>(this, TEXT("LeftGearShiftEffect"));
						LeftGearShiftParticleSystemComponent->bAutoRegister = true;
						LeftGearShiftParticleSystemComponent->SetTemplate(GearShiftParticle);
						LeftGearShiftParticleSystemComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform, TEXT("BoosterLeftSocket"));
						LeftGearShiftParticleSystemComponent->RegisterComponent();
					}

					else if (LeftGearShiftParticleSystemComponent)
					{
						LeftGearShiftParticleSystemComponent->ActivateSystem();

						if (LeftGearShiftParticleSystemComponent->HasCompleted())
						{
							LeftGearShiftParticleSystemComponent->DeactivateSystem();
							LeftGearShiftParticleSystemComponent->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
							LeftGearShiftParticleSystemComponent->UnregisterComponent();
							LeftGearShiftParticleSystemComponent->DestroyComponent();
						}
					}
				}

				const USkeletalMeshSocket* RightSocket = GetBaseMesh()->GetSocketByName("BoosterRightSocket");

				if (RightSocket)
				{
					if (!RightGearShiftParticleSystemComponent)
					{
						RightGearShiftParticleSystemComponent = NewObject<UParticleSystemComponent>(this, TEXT("RightGearShiftEffect"));
						RightGearShiftParticleSystemComponent->bAutoRegister = true;
						RightGearShiftParticleSystemComponent->SetTemplate(GearShiftParticle);
						RightGearShiftParticleSystemComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform, TEXT("BoosterRightSocket"));
						RightGearShiftParticleSystemComponent->RegisterComponent();
					}

					else if (RightGearShiftParticleSystemComponent)
					{
						RightGearShiftParticleSystemComponent->ActivateSystem();

						if (RightGearShiftParticleSystemComponent->HasCompleted())
						{
							RightGearShiftParticleSystemComponent->DeactivateSystem();
							RightGearShiftParticleSystemComponent->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
							RightGearShiftParticleSystemComponent->UnregisterComponent();
							RightGearShiftParticleSystemComponent->DestroyComponent();
						}
					}
				}

				//////////////////////////////////////////////
				/////////  ADD One socket particle ///////////
				///////////////////////////////////////////////
			}

			const USkeletalMeshSocket* EngineSocket = GetBaseMesh()->GetSocketByName("EngineSoundSocket");

			if (EngineSocket)
			{
				if (!GearShiftSoundComponent)
				{
					GearShiftSoundComponent = NewObject<UAudioComponent>(this, TEXT("GearShitSound"));
					GearShiftSoundComponent->bAutoRegister = true;
					GearShiftSoundComponent->SetSound(GearShiftSound);
					GearShiftSoundComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform, TEXT("EngineSoundSocket"));
					GearShiftSoundComponent->bAutoActivate = false;
					GearShiftSoundComponent->RegisterComponent();
				}


				else if (GearShiftSoundComponent)
				{
					GearShiftSoundComponent->Play();

					if (!GearShiftSoundComponent->IsPlaying())
					{
						GearShiftSoundComponent->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
						GearShiftSoundComponent->UnregisterComponent();
						GearShiftSoundComponent->DestroyComponent();
					}
				}
			}
		}

	}
	//}


	//// When Reverse

	//if (VehicleThrottle < 0.0f)
	//{

	//	if (GetVehicleMovement()->GetForwardSpeed() >= 0)
	//	{
	//		//TMap<FName, UMaterialInstanceDynamic*> ReverseMats = GetPartComponents()->ReverseLightMaterials;

	//		//for (auto & Item : ReverseMats)
	//		//{
	//		//	if (Item.Value != nullptr)
	//		//	{
	//		//		Item.Value->SetVectorParameterValue("EmissiveColor", GetPartComponents()->ReverseLight.Find(Item.Key)->ReturnColor);

	//		//		RevL_Light->SetVisibility(true, false);
	//		//		RevR_Light->SetVisibility(true, false);
	//		//	}
	//		//}


	//		//if (!IsHandbrakeActive())
	//		//{
	//		TMap<FName, UMaterialInstanceDynamic*> RearMats = GetPartComponents()->RearLightMaterials;

	//			for (auto & Item : RearMats)
	//			{
	//				if (Item.Value != nullptr)
	//				{
	//					Item.Value->SetVectorParameterValue("EmissiveColor", GetPartComponents()->RearLight.Find(Item.Key)->LightColor);

	//					RL_Light->SetVisibility(true, false);
	//					RR_Light->SetVisibility(true, false);
	//				}
	//			}
	//		//}
	//	}


	//	else if (GetVehicleMovement()->GetForwardSpeed() < 0)
	//	{

	//		//TMap<FName, UMaterialInstanceDynamic*> ReverseMats = GetPartComponents()->ReverseLightMaterials;

	//		//for (auto & Item : ReverseMats)
	//		//{
	//		//	if (Item.Value != nullptr)
	//		//	{
	//		//		Item.Value->SetVectorParameterValue("EmissiveColor", GetPartComponents()->ReverseLight.Find(Item.Key)->LightColor);

	//		//		RevL_Light->SetVisibility(true, false);
	//		//		RevR_Light->SetVisibility(true, false);
	//		//	}
	//		//}

	//		//if (!IsHandbrakeActive())
	//		//{

	//			TMap<FName, UMaterialInstanceDynamic*> RearMats = GetPartComponents()->RearLightMaterials;

	//			for (auto & Item : RearMats)
	//			{
	//				if (Item.Value != nullptr)
	//				{
	//					Item.Value->SetVectorParameterValue("EmissiveColor", GetPartComponents()->RearLight.Find(Item.Key)->ReturnColor);

	//					RL_Light->SetVisibility(false, false);
	//					RR_Light->SetVisibility(false, false);
	//				}
	//			}

	//		//}


	//	}


	//}

	//else if (VehicleThrottle == 0 || VehicleThrottle > 0.0f)
	//{

	//	//TMap<FName, UMaterialInstanceDynamic*> ReverseMats = GetPartComponents()->ReverseLightMaterials;

	//	//for (auto & Item : ReverseMats)
	//	//{
	//	//	if (Item.Value != nullptr)
	//	//	{
	//	//		Item.Value->SetVectorParameterValue("EmissiveColor", GetPartComponents()->ReverseLight.Find(Item.Key)->ReturnColor);

	//	//		RevL_Light->SetVisibility(true, false);
	//	//		RevR_Light->SetVisibility(true, false);
	//	//	}
	//	//}

	//	//if (!IsHandbrakeActive())
	//	//{

	//		TMap<FName, UMaterialInstanceDynamic*> RearMats = GetPartComponents()->RearLightMaterials;

	//		for (auto & Item : RearMats)
	//		{
	//			if (Item.Value != nullptr)
	//			{
	//				Item.Value->SetVectorParameterValue("EmissiveColor", GetPartComponents()->RearLight.Find(Item.Key)->ReturnColor);

	//				RL_Light->SetVisibility(false, false);
	//				RR_Light->SetVisibility(false, false);
	//			}
	//		}

	//	//}

	//}

	CalculateDistance(DeltaTime);

	// Update wheel skid
	WheelFXUpdate();

	/// needs improve function
	DestroyCachedComponents(DeltaTime);


	//if (IsControlled())
	//{
	//	for (TActorIterator<ARiders_DayNight_System> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	//	{
	//		if (ActorItr->TimeOfDay == ETimesOfDay::DNS_Night)
	//		{
	//			CarNightLighActivate();
	//		}

	//		else if (ActorItr->TimeOfDay == ETimesOfDay::DNS_Day)
	//		{
	//			CarNightLighDeactivate();
	//		}
	//	}
	//}



	UpdateBrakeSystem(DeltaTime);

	EngineSoundGenerate(DeltaTime);


	/*Camera shaking update */



	if (TypeCamera >2)
	{
		ARiders_GamePlayerController* PC = Cast<ARiders_GamePlayerController>(Controller);
		
		if (PC)
		{
			if (bShowDebug)
			{
				UE_LOG(VehicleLog, Log, TEXT("%d - CameraShaking"), TypeCamera);
			}

			PC->ClientPlayCameraShake(IdleCameraShake, 0.3f);
		}
	}

}


void ARiders_Vehicle::WheelFXUpdate()
{
		// Simulation
		URiders_WVHMovComponent4W* Vehicle4W = CastChecked<URiders_WVHMovComponent4W>(GetVehicleMovement());


		//iterate through all the wheels
		for (int32 Itr = 0; Itr < 4; Itr++)
		{
			if (Vehicle4W->Wheels[Itr]->GetContactSurfaceMaterial()) //on the floor, will use GetContactSurfaceMaterial() later to change particle based on surface
			{

				FVector Vel = GetVelocity();
				bool bVehicleStopped = Vel.SizeSquared2D() < SkidThresholdVelocity*SkidThresholdVelocity;

				if(!bVehicleStopped && GetVehicleMovement()->CheckSlipWheel(LongSlipSmokeThreshold, LateralSlipSmokeThreshold, Itr))
				{
					//bottom of the wheel location
					const FVector ParticleLoc = Vehicle4W->Wheels[Itr]->Location + FVector(0, 0, 1) * -(Vehicle4W->Wheels[0]->ShapeRadius / 2);
					//spawn smoke particle
					UGameplayStatics::SpawnEmitterAtLocation(this, WheelSlipFX, ParticleLoc, GetActorRotation());
				}

				bool TireSlipping = GetVehicleMovement()->CheckSlipWheel(LongSlipSkidThreshold, LateralSlipSkidThreshold, Itr);
				bool WantsToSkid = !bVehicleStopped && TireSlipping;
				DebugWantToSkid[Itr] = WantsToSkid;

				float FL_CurrTime = GetWorld()->GetTimeSeconds();

				if (WantsToSkid && !bSkidding[Itr])
				{

					const USkeletalMeshSocket* AudioSocket = GetBaseMesh()->GetSocketByName(SkidSockets[Itr]);

					if (AudioSocket)
					{
						if (!SkidAudioComponent[Itr])
						{
							FString TempStr = TEXT("SkidSound");
							TempStr.Append(SkidSockets[Itr].ToString());

							SkidAudioComponent[Itr] = NewObject<UAudioComponent>(this, FName(*TempStr));
							SkidAudioComponent[Itr]->bAutoRegister = true;
							SkidAudioComponent[Itr]->SetSound(SkidSound);
							SkidAudioComponent[Itr]->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform,SkidSockets[Itr]);
							SkidAudioComponent[Itr]->bAutoActivate = false;
							SkidAudioComponent[Itr]->RegisterComponent();
						}


						else if (SkidAudioComponent[Itr])
						{


							if (!bSkiddingSound[Itr])
							{
								bSkiddingSound[Itr] = true;


								SkidAudioComponent[Itr]->Play();

								if (!SkidAudioComponent[Itr]->IsPlaying())
								{
									SkidAudioComponent[Itr]->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
									SkidAudioComponent[Itr]->UnregisterComponent();
									SkidAudioComponent[Itr]->DestroyComponent();

									SkidAudioComponent[Itr] = nullptr;
								}

								SkidStartTime[Itr] = FL_CurrTime;
							}


						}
					}


					bSkidding[Itr] = true;

					if (SkidWheelPSC[Itr] == NULL)
					{
						SkidWheelPSC[Itr] = NewObject<UParticleSystemComponent>(this);
						SkidWheelPSC[Itr]->bAutoRegister = true;
						SkidWheelPSC[Itr]->SetTemplate(SkidWheelFX);
						SkidWheelPSC[Itr]->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform ,SkidSockets[Itr]);
						SkidWheelPSC[Itr]->RegisterComponent();

						SkidWheelPSC[Itr]->SetFloatParameter("LifeTime", SkidMarkTime);

						if (!SkidWheelPSC[Itr])
						{
							UE_LOG(VehicleLog, Error, TEXT("Error Create Component"));

							return;
						}


						//UE_LOG(VehicleLog, Warning, TEXT("Registered Particle = %s"), *SkidWheelPSC[Itr]->GetName());

						//UE_LOG(VehicleLog, Warning, TEXT("Create Emitter Component"));
					}

					else if(SkidWheelPSC[Itr] != NULL)
					{
						SkidWheelPSC[Itr]->SetWorldRotation(GetActorRotation());
						SkidWheelPSC[Itr]->ActivateSystem();

						//UE_LOG(VehicleLog, Warning, TEXT("Emmiter Activate"));
					}

				}

				if (!WantsToSkid && bSkidding[Itr])
				{
					if (SkidAudioComponent[Itr] != nullptr)
					{
						if (bSkiddingSound[Itr])
						{
							bSkiddingSound[Itr] = false;
							SkidAudioComponent[Itr]->FadeOut(SkidFadeoutTime, 0);

							if (!SkidAudioComponent[Itr]->IsPlaying())
							{
								SkidAudioComponent[Itr]->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
								SkidAudioComponent[Itr]->UnregisterComponent();
								SkidAudioComponent[Itr]->DestroyComponent();

								SkidAudioComponent[Itr] = nullptr;
							}

							if (FL_CurrTime - SkidStartTime[Itr] > SkidDurationRequiredForStopSound)
							{
								UGameplayStatics::PlaySoundAtLocation(this, SkidSoundStop, GetActorLocation());
							}
						}
					}

					bSkidding[Itr] = false;

					if (SkidWheelPSC[Itr] != NULL)
					{
						SkidWheelPSC[Itr]->DeactivateSystem();

						//UE_LOG(VehicleLog, Warning, TEXT("Emmiter Deactivate"));

						if (SkidWheelPSC[Itr]->IsRegistered())
						{
							SkidWheelPSC[Itr]->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);

							CacheSkidPSC.Add(SkidWheelPSC[Itr]);
							CurrentSkidMarksTimes.Add(SkidMarkTime+1.0f);
							//SkidWheelPSC[Itr]->UnregisterComponent();
							//SkidWheelPSC[Itr]->DestroyComponent();

							SkidWheelPSC[Itr] = nullptr;
						}

						//UE_LOG(VehicleLog, Warning, TEXT("Cached Particle Components = %d"), CacheSkidPSC.Num());


					}
				}

				DebugWheelSkidding[Itr] = bSkidding[Itr];
				DebugTouchWheel[Itr] = true;

			}

			else if (!Vehicle4W->Wheels[Itr]->GetContactSurfaceMaterial())
			{
				if (SkidWheelPSC[Itr] != NULL)
				{
					SkidWheelPSC[Itr]->DeactivateSystem();

					if (SkidWheelPSC[Itr]->IsRegistered())
					{
						SkidWheelPSC[Itr]->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);

						CacheSkidPSC.Add(SkidWheelPSC[Itr]);
						CurrentSkidMarksTimes.Add(SkidMarkTime + 1.0f);
						//SkidWheelPSC[Itr]->UnregisterComponent();
						//SkidWheelPSC[Itr]->DestroyComponent();

						SkidWheelPSC[Itr] = nullptr;
					}
				}

				if (SkidAudioComponent[Itr] != nullptr)
				{
					if (SkidAudioComponent[Itr]->IsPlaying())
					{
						SkidAudioComponent[Itr]->FadeOut(SkidFadeoutTime, 0);

						if (!SkidAudioComponent[Itr]->IsPlaying())
						{
							SkidAudioComponent[Itr]->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
							SkidAudioComponent[Itr]->UnregisterComponent();
							SkidAudioComponent[Itr]->DestroyComponent();

							SkidAudioComponent[Itr] = nullptr;
						}
					}
				}
				DebugTouchWheel[Itr] = false;
			}
		}

}


void ARiders_Vehicle::InterpolateCameraPostProcess(float DeltaSeconds)
{
	if (bActivateBoost)
	{
		if (Nitro > 0)
		{
			VehicleCameraComponent->PostProcessBlendWeight = FMath::FInterpTo(VehicleCameraComponent->PostProcessBlendWeight, 1.0f, DeltaSeconds, PostProcessSpeedInterpolate);

			if (TypeCamera == 0 || TypeCamera == 1)
			{
				VehicleCameraComponent->FieldOfView = FMath::FInterpTo(VehicleCameraComponent->FieldOfView, NitroCameraFieldOfView, DeltaSeconds, PostProcessSpeedInterpolate);
			}
		}
		
	}
	else
	{
		VehicleCameraComponent->PostProcessBlendWeight = FMath::FInterpTo(VehicleCameraComponent->PostProcessBlendWeight, 0.0f, DeltaSeconds, PostProcessSpeedInterpolate);

		VehicleCameraComponent->FieldOfView = FMath::FInterpTo(VehicleCameraComponent->FieldOfView, DefaultFOV, DeltaSeconds, PostProcessSpeedInterpolate);
	}


}

void ARiders_Vehicle::CalculateDistance(float DeltaTime)
{
	OverallDistance = OverallDistance + FMath::Abs((GetVehicleMovement()->GetForwardSpeed() * 3600 / 100000) * DeltaTime);

	MeterUnits = OverallDistance;

	if (MeterUnits >= 10)
	{
		MeterUnits = 0;
		MeterDecs++;

		if (MeterDecs >= 10)
		{
			MeterDecs = 0;
			Meterhundreds++;

			if (Meterhundreds >= 10)
			{
				Meterhundreds = 0;
				KilometerUnits++;

				if (KilometerUnits >= 10)
				{
					KilometerUnits = 0;
					KilometerDecs++;

					if (KilometerDecs >= 10)
					{
						KilometerDecs = 0;
						Kilometerhundreds++;

						if (Kilometerhundreds >= 10)
						{
							MeterUnits = 0;
							MeterDecs = 0;
							Meterhundreds = 0;

							KilometerUnits = 0;
							KilometerDecs = 0;
							Kilometerhundreds = 0;
						}
					}
				}
			}
		}
	}

	if (OverallDistance >= 10)
	{
		OverallDistance = 0.0;
	}
}


////////////////////////////////////////////////////////////
/******************* NITRO FUNCTIONS **********************/
////////////////////////////////////////////////////////////

void ARiders_Vehicle::ActivateBoosters()
{
	if (bEnableNitro)
	{
		if (VehicleThrottle > 0.0f)
		{
			if (Nitro > 0)
			{
				bActivateBoost = true;

				const USkeletalMeshSocket* LeftBoosterSocket = GetBaseMesh()->GetSocketByName("BoosterLeftSocket");

				if (LeftBoosterSocket)
				{
					if (LeftBoosterSoundComponent == nullptr)
					{
						LeftBoosterSoundComponent = NewObject<UAudioComponent>(this, TEXT("LeftBoosterSound"));
						LeftBoosterSoundComponent->bAutoRegister = true;
						LeftBoosterSoundComponent->SetSound(BoosterSound);
						LeftBoosterSoundComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform,TEXT("BoosterLeftSocket"));
						LeftBoosterSoundComponent->bAutoActivate = false;
						LeftBoosterSoundComponent->RegisterComponent();

						if (!LeftBoosterSoundComponent->IsPlaying())
						{
							LeftBoosterSoundComponent->Play();
						}
					}

					if (LeftBoosterParticleSystemComponent == nullptr)
					{
						LeftBoosterParticleSystemComponent = NewObject<UParticleSystemComponent>(this, TEXT("LeftBooster"));
						LeftBoosterParticleSystemComponent->bAutoRegister = true;
						LeftBoosterParticleSystemComponent->SetTemplate(BoosterEffect);						
						LeftBoosterParticleSystemComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform, TEXT("BoosterLeftSocket"));

						LeftBoosterParticleSystemComponent->bAutoActivate = false;
						LeftBoosterParticleSystemComponent->RegisterComponent();


						LeftBoosterParticleSystemComponent->ActivateSystem(true);
					}


				}


				const USkeletalMeshSocket* RightBoosterSocket = GetBaseMesh()->GetSocketByName("BoosterRightSocket");

				if (RightBoosterSocket)
				{
					if (RightBoosterSoundComponent == nullptr)
					{
						RightBoosterSoundComponent = NewObject<UAudioComponent>(this, TEXT("RightBoosterSound"));
						RightBoosterSoundComponent->bAutoRegister = true;
						RightBoosterSoundComponent->SetSound(BoosterSound);
						RightBoosterSoundComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform , TEXT("BoosterRightSocket"));
						RightBoosterSoundComponent->bAutoActivate = false;
						RightBoosterSoundComponent->RegisterComponent();

						if (!RightBoosterSoundComponent->IsPlaying())
						{
							RightBoosterSoundComponent->Play();
						}
					}

					if (RightBoosterParticleSystemComponent == nullptr)
					{
						RightBoosterParticleSystemComponent = NewObject<UParticleSystemComponent>(this, TEXT("RightBooster"));
						RightBoosterParticleSystemComponent->bAutoRegister = true;
						RightBoosterParticleSystemComponent->SetTemplate(BoosterEffect);
						RightBoosterParticleSystemComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform,TEXT("BoosterRightSocket"));
						RightBoosterParticleSystemComponent->bAutoActivate = false;
						RightBoosterParticleSystemComponent->RegisterComponent();


						RightBoosterParticleSystemComponent->ActivateSystem(true);
					}
				}
			}
		}
	}
}


void ARiders_Vehicle::DeactivateBoosters()
{
	if (bEnableNitro)
	{
		bActivateBoost = false;

		if (LeftBoosterSoundComponent != nullptr)
		{
			LeftBoosterSoundComponent->Stop();
			LeftBoosterSoundComponent->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
			LeftBoosterSoundComponent->UnregisterComponent();
			LeftBoosterSoundComponent->DestroyComponent();

			LeftBoosterSoundComponent = nullptr;
		}

		if (RightBoosterSoundComponent != nullptr)
		{
			RightBoosterSoundComponent->Stop();
			RightBoosterSoundComponent->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
			RightBoosterSoundComponent->UnregisterComponent();
			RightBoosterSoundComponent->DestroyComponent();

			RightBoosterSoundComponent = nullptr;
		}

		if (LeftBoosterParticleSystemComponent != nullptr)
		{
			LeftBoosterParticleSystemComponent->DeactivateSystem();
			LeftBoosterParticleSystemComponent->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
			LeftBoosterParticleSystemComponent->UnregisterComponent();
			LeftBoosterParticleSystemComponent->DestroyComponent();

			LeftBoosterParticleSystemComponent = nullptr;
		}

		if (RightBoosterParticleSystemComponent != nullptr)
		{
			RightBoosterParticleSystemComponent->DeactivateSystem();
			RightBoosterParticleSystemComponent->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
			RightBoosterParticleSystemComponent->UnregisterComponent();
			RightBoosterParticleSystemComponent->DestroyComponent();

			RightBoosterParticleSystemComponent = nullptr;
		}

	}
}




void ARiders_Vehicle::SetFullNitro()
{
	if (Nitro < NitroMax)
	{
		Nitro = NitroMax;
		if (bShowDebug)
		{
			UE_LOG(VehicleLog, Log, TEXT("SetFullNitro"));
		}
	}

	else if (Nitro >= NitroMax)
	{
		if (bShowDebug)
		{
			UE_LOG(VehicleLog, Log, TEXT("MaxNitro"));
		}
	}
}


void ARiders_Vehicle::AddNitro(int32 CountNitro)
{
	if (Nitro < NitroMax)
	{
		Nitro += CountNitro;

		if (Nitro > NitroMax)
		{
			if (bShowDebug)
			{
				UE_LOG(VehicleLog, Log, TEXT("MaxNitro"));
			}
			Nitro = NitroMax;
		}
	}

	else if (Nitro >= NitroMax)
	{
		if (bShowDebug)
		{
			UE_LOG(VehicleLog, Log, TEXT("MaxNitro"));
		}
	}

}

//void ARiders_Vehicle::InitRandomVehicleColor()
//{
//	GetPartComponents()->PartsData.Body.MaterialProperty.Color = FLinearColor(FMath::FRand(), FMath::FRand(), FMath::FRand(), FMath::FRand());
//}

void ARiders_Vehicle::SetupPlayerInputComponent(class UInputComponent* InputComp)
{

	Super::SetupPlayerInputComponent(InputComp);

	check(InputComp);

	ARiders_GamePlayerController* PC = Cast<ARiders_GamePlayerController>(Controller);

	if (PC)
	{
		InputComp->BindAction("SwitchVehicle", IE_Pressed, PC, &ARiders_GamePlayerController::SetSelectedCar);
	}

	InputComp->BindAction("Return", IE_Pressed, this, &ARiders_Vehicle::TeleportToLCP);
	InputComp->BindAction("UseNitro", IE_Pressed, this, &ARiders_Vehicle::ActivateBoosters);
	InputComp->BindAction("UseNitro", IE_Released, this, &ARiders_Vehicle::DeactivateBoosters);
	InputComp->BindAction("FrontLight", IE_Pressed, this, &ARiders_Vehicle::FrontLightToggle);
	InputComp->BindAction("ToggleDebugWheel", IE_Pressed, this, &ARiders_Vehicle::ToggleDebug);
	InputComp->BindAction("FGCamera", IE_Pressed, this, &ARiders_Vehicle::ToggleScreenShotCamera);

	InputComp->BindAction("HandBrake", IE_Pressed, this, &ARiders_Vehicle::HandBrakeOn);
	InputComp->BindAction("HandBrake", IE_Released, this, &ARiders_Vehicle::HandBrakeOff);

	InputComp->BindAction("ScreenShotCameraZoomIn", IE_Pressed, this, &ARiders_Vehicle::ScreenShotCameraZoomIn);
	InputComp->BindAction("ScreenShotCameraZoomOut", IE_Pressed, this, &ARiders_Vehicle::ScreenShotCameraZoomOut);

	InputComp->BindAxis("MoveForward", this, &ARiders_Vehicle::MoveForward);
	InputComp->BindAxis("MoveRight", this, &ARiders_Vehicle::MoveRight);
	InputComp->BindAxis("Turn", this, &ARiders_Vehicle::AddControllerYawInput);
	InputComp->BindAxis("LookUp", this, &ARiders_Vehicle::AddControllerPitchInput);

	InputComp->BindAction("StartEngine", IE_Pressed, this, &ARiders_Vehicle::PressStartEngine);

	InputComp->BindAction("NextCamera", IE_Pressed, this, &ARiders_Vehicle::ChangeCamera);
	InputComp->BindAction("FrontView", IE_Pressed, this, &ARiders_Vehicle::FrontViewActivate);
	InputComp->BindAction("FrontView", IE_Released, this, &ARiders_Vehicle::FrontViewDeactivate);
	InputComp->BindAction("LeftView", IE_Pressed, this, &ARiders_Vehicle::LeftViewActivate);
	InputComp->BindAction("LeftView", IE_Released, this, &ARiders_Vehicle::LeftViewDeactivate);
	InputComp->BindAction("RightView", IE_Pressed, this, &ARiders_Vehicle::RightViewActivate);
	InputComp->BindAction("RightView", IE_Released, this, &ARiders_Vehicle::RightViewDeactivate);


	InputComp->BindAction("PlayHorn", IE_Pressed, this, &ARiders_Vehicle::PlayHornSound);
	InputComp->BindAction("PlayHorn", IE_Released, this, &ARiders_Vehicle::StopHornSound);


	InputComp->BindAction("NextGear", IE_Pressed, this, &ARiders_Vehicle::GearUP);
	InputComp->BindAction("PrevGear", IE_Pressed, this, &ARiders_Vehicle::GearDown);

}




////////////////////////////////////////////////////////////
/******************* CAMERA FUNCTIONS *********************/
////////////////////////////////////////////////////////////


void ARiders_Vehicle::FlyingCamera(float DeltaTime)
{
	if (Controller != NULL)
	{

		if (GetVehicleMovement()->GetForwardSpeed() * 3600.f / 100000.f <= 0.1f && GetVehicleMovement()->GetForwardSpeed() * 3600.f / 100000.f >= -0.1f)
		{
			if (TypeCamera == 0 || TypeCamera == 1)
			{
				if (!bFlyCamera)
				{

					TimeFlyCam += DeltaTime;


					if (TimeFlyCam >= StandbyTimeToFlyingCamera)
					{
						LastCameraType = TypeCamera;


						TypeCamera = 6;
						SetCameraType(TypeCamera);

						bFlyCamera = true;

						TimeFlyCam = 0.0f;

						bSwitchCameraTypes = false;


					}

				}
			}
		}


		if (TypeCamera == 6)
		{
			if (bFlyCamera)
			{
				BoomComponent->SetRelativeRotation(FRotator(0.0f, BoomComponent->RelativeRotation.Yaw + FlyingCameraStep, 0.0f));

				if (GetVehicleMovement()->GetForwardSpeed() * 3600.f / 100000.f >= 0.1f || GetVehicleMovement()->GetForwardSpeed() * 3600.f / 100000.f <= -0.1f)
				{
					bSwitchCameraTypes = true;
					TimeFlyCam = 0.0f;
					TypeCamera = LastCameraType;
					SetCameraType(TypeCamera);

					bFlyCamera = false;

				}
			}
		}
	}
}


void ARiders_Vehicle::ChangeCamera()
{
	if (bSwitchCameraTypes)
	{
		if (TypeCamera < 2 && TypeCamera >= 0)
		{
			TypeCamera++;
			SetCameraType(TypeCamera);
		}

		else
		{
			TypeCamera = 0;
			SetCameraType(TypeCamera);
		}

		TimeFlyCam = 0.0f;

	}
}


void ARiders_Vehicle::ScreenShotCameraZoomIn()
{
	if (TypeCamera == 7)
	{       
		if (BoomComponent->TargetArmLength > FreeView.MinDistance)
		{
			BoomComponent->TargetArmLength = BoomComponent->TargetArmLength - FreeView.CameraStep;
		}
	}
}

void ARiders_Vehicle::ScreenShotCameraZoomOut()
{
	if (TypeCamera == 7)
	{
		if (BoomComponent->TargetArmLength < FreeView.MaxDistance)
		{
			BoomComponent->TargetArmLength = BoomComponent->TargetArmLength + FreeView.CameraStep;
		}
	}
}



void ARiders_Vehicle::FrontViewActivate()
{
	if (TypeCamera == 0 || TypeCamera == 1)
	{
		bSwitchCameraTypes = false;

		LastCameraType = TypeCamera;


		TypeCamera = 5;

		SetCameraType(TypeCamera);

		TimeFlyCam = 0.0f;
	}
}

void ARiders_Vehicle::FrontViewDeactivate()
{
	if (TypeCamera == 5)
	{
		TimeFlyCam = 0.0f;

		bSwitchCameraTypes = true;
		TypeCamera = LastCameraType;
		SetCameraType(TypeCamera);

	}
}


bool ARiders_Vehicle::IsHandbrakeActive() const
{
	return bHandbrakeActive;
}

//void ARiders_Vehicle::ReceiveHandBrake(bool bHandBrake)
//{
//
//}

void ARiders_Vehicle::ReceiveHandBrake_Implementation(bool bHandBrake)
{
	if (bShowDebug)
	{
		UE_LOG(VehicleLog, Log, TEXT("HandBrake Event %"), (bHandBrake ? TEXT("True") : TEXT("False")));
	}
}


void ARiders_Vehicle::ReceiveMoveForward()
{
	if (bShowDebug)
	{
		UE_LOG(VehicleLog, Log, TEXT("On Move Forward"));
	}

	TMap<FName, UMaterialInstanceDynamic*> ReverseMats = GetPartComponents()->ReverseLightMaterials;

	for (auto & Item : ReverseMats)
	{
		if (Item.Value != nullptr)
		{
			Item.Value->SetVectorParameterValue("EmissiveColor", GetPartComponents()->ReverseLight.Find(Item.Key)->ReturnColor);

			RevL_Light->SetVisibility(false, false);
			RevR_Light->SetVisibility(false, false);
		}
	}

	TArray<FLightMaterials> RearMats = GetPartComponents()->RearLightMaterials;

	int i = 0;

	for (auto & Item : RearMats)
	{
		if (Item.Material != nullptr)
		{
			Item.Material ->SetVectorParameterValue("EmissiveColor", GetPartComponents()->RearLight[i].ReturnColor);

			RL_Light->SetVisibility(false, false);
			RR_Light->SetVisibility(false, false);
		}

		i++;
	}
}

void ARiders_Vehicle::ReceiveMoveReverse()
{
	if (bShowDebug)
	{
		UE_LOG(VehicleLog, Log, TEXT("On Move Reverse"));
	}

	TMap<FName, UMaterialInstanceDynamic*> ReverseMats = GetPartComponents()->ReverseLightMaterials;

	for (auto & Item : ReverseMats)
	{
		if (Item.Value != nullptr)
		{
			Item.Value->SetVectorParameterValue("EmissiveColor", GetPartComponents()->ReverseLight.Find(Item.Key)->LightColor);

			RevL_Light->SetVisibility(true, false);
			RevR_Light->SetVisibility(true, false);
		}
	}

	TArray<FLightMaterials> RearMats = GetPartComponents()->RearLightMaterials;

	int i = 0;

	for (auto & Item : RearMats)
	{
		if (Item.Material != nullptr)
		{
			Item.Material->SetVectorParameterValue("EmissiveColor", GetPartComponents()->RearLight[i].ReturnColor);

			RL_Light->SetVisibility(false, false);
			RR_Light->SetVisibility(false, false);
		}

		i++;
	}
}

void ARiders_Vehicle::ReceiveStop()
{
	if (bShowDebug)
	{
		UE_LOG(VehicleLog, Log, TEXT("On Stop"));
	}

	TArray<FLightMaterials> RearMats = GetPartComponents()->RearLightMaterials;

	int i = 0;

	for (auto & Item : RearMats)
	{
		if (Item.Material != nullptr)
		{
			Item.Material->SetVectorParameterValue("EmissiveColor", GetPartComponents()->RearLight[i].LightColor);

			RL_Light->SetVisibility(true, false);
			RR_Light->SetVisibility(true, false);
		}

		i++;
	}
}

void ARiders_Vehicle::ReceiveIdle()
{
	if (bShowDebug)
	{
		UE_LOG(VehicleLog, Log, TEXT("On Idle"));
	}

	TArray<FLightMaterials> RearMats = GetPartComponents()->RearLightMaterials;

	int i = 0;

	for (auto & Item : RearMats)
	{
		if (Item.Material != nullptr)
		{
			Item.Material->SetVectorParameterValue("EmissiveColor", GetPartComponents()->RearLight[i].ReturnColor);

			RL_Light->SetVisibility(false, false);
			RR_Light->SetVisibility(false, false);
		}

		i++;
	}
}

float ARiders_Vehicle::GetEngineRotationSpeed() const
{
	return (GetVehicleMovement()) ? FMath::Abs(GetVehicleMovement()->GetEngineRotationSpeed()) : 0.0f;
}


float ARiders_Vehicle::GetVehicleMaxSpeed() const
{
	return (GetVehicleMovement()->GetEngineMaxRotationSpeed() * GetVehicleMovement()->Wheels[2]->ShapeRadius * 2) / (GetVehicleMovement()->TransmissionSetup.ForwardGears[GetVehicleMovement()->TransmissionSetup.ForwardGears.Num() - 1].Ratio*GetVehicleMovement()->TransmissionSetup.FinalRatio*530.616);
}

float ARiders_Vehicle::GetVehicleSpeed() const
{
	return (GetVehicleMovement()) ? FMath::Abs(GetVehicleMovement()->GetForwardSpeed()) : 0.0f;
}

float ARiders_Vehicle::GetEngineMaxRotationSpeed() const
{
	return (GetVehicleMovement()) ? FMath::Abs(GetVehicleMovement()->MaxEngineRPM) : 1.f;
}

TArray<uint8> ARiders_Vehicle::ObjectSaver()
{
	TArray<uint8> ObjectData;

	FMemoryWriter MemoryWriter(ObjectData, true);
	// use a wrapper archive that converts FNames and UObject*'s to strings that can be read back in
	FRidersSaveGameArchive SaveGameArchive(MemoryWriter, false);
	// serialize the object
	Serialize(SaveGameArchive);

	return ObjectData;
}

void ARiders_Vehicle::ObjectLoader(TArray<uint8> ObjectData)
{
	if (ObjectData.Num() <= 0) return;
	//TODO how to check if valid binary?

	FMemoryReader MemoryReader(ObjectData, true);
	FRidersSaveGameArchive LoadGameArchive(MemoryReader, true);
	Serialize(LoadGameArchive);
}


void ARiders_Vehicle::LeftViewActivate()
{

	if (GetVehicleMovement()->GetForwardSpeed() * 3600.f / 100000.f <= 10.0f && GetVehicleMovement()->GetForwardSpeed() * 3600.f / 100000.f >= -10.0f)
	{
		if (TypeCamera == 0 || TypeCamera == 1)
		{
			bSwitchCameraTypes = false;

			LastCameraType = TypeCamera;


			TypeCamera = 3;

			SetCameraType(TypeCamera);
		}
	}
}

void ARiders_Vehicle::LeftViewDeactivate()
{
	if (TypeCamera == 3)
	{
		bSwitchCameraTypes = true;
		TypeCamera = LastCameraType;
		SetCameraType(TypeCamera);
		TimeFlyCam = 0.0f;
	}
}



void ARiders_Vehicle::RightViewActivate()
{
	if (GetVehicleMovement()->GetForwardSpeed() * 3600.f / 100000.f <= 10.0f && GetVehicleMovement()->GetForwardSpeed() * 3600.f / 100000.f >= -10.0f)
	{
		if (TypeCamera == 0 || TypeCamera == 1)
		{
			bSwitchCameraTypes = false;

			LastCameraType = TypeCamera;


			TypeCamera = 4;
			SetCameraType(TypeCamera);
		}
	}
}

void ARiders_Vehicle::RightViewDeactivate()
{

	if (TypeCamera == 4)
	{
		bSwitchCameraTypes = true;
		TypeCamera = LastCameraType;
		SetCameraType(TypeCamera);
		TimeFlyCam = 0.0f;
	}
}

void ARiders_Vehicle::SetCameraType(int32 Types)
{
	TypeCamera = Types;

	switch (TypeCamera)
	{
	case 0: /// Follow 1 camera
		VehicleCameraComponent->AttachToComponent(BoomComponent, FAttachmentTransformRules::KeepRelativeTransform ,USpringArmComponent::SocketName);
		BoomComponent->TargetOffset = FirstView.CameraLocation;
		BoomComponent->SocketOffset = FirstView.CameraOffset;
		BoomComponent->SetRelativeRotation(FirstView.CameraRotation);
		BoomComponent->TargetArmLength = FirstView.Distance;
		BoomComponent->bEnableCameraRotationLag = FirstView.bEnableCameraRotationLag;
		//BoomComponent->bEnableCameraLag = true;

		//BoomComponent->bInheritPitch = false;
		//BoomComponent->bInheritRoll = false;
		//BoomComponent->bInheritYaw = true;


		BoomComponent->bUsePawnControlRotation = false;

		break;

	case 1: /// Follow 2 Camera

		VehicleCameraComponent->AttachToComponent(BoomComponent, FAttachmentTransformRules::KeepRelativeTransform, USpringArmComponent::SocketName);
		BoomComponent->TargetOffset = SecondView.CameraLocation;

		BoomComponent->SocketOffset = SecondView.CameraOffset;
		BoomComponent->SetRelativeRotation(SecondView.CameraRotation);

		BoomComponent->bEnableCameraRotationLag = SecondView.bEnableCameraRotationLag;
		//BoomComponent->bEnableCameraLag = true;


		//BoomComponent->bInheritPitch = false;
		//BoomComponent->bInheritRoll = false;
		//BoomComponent->bInheritYaw = true;


		BoomComponent->bUsePawnControlRotation = false;

		break;

	case 2: /// Hood Camera

		VehicleCameraComponent->AttachToComponent(GetBaseMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("HoodCamera"));
		//BoomComponent->TargetOffset = HoodView.CameraLocation;
		//BoomComponent->SetRelativeRotation(HoodView.CameraRotation);
		//BoomComponent->TargetArmLength = HoodView.Distance;  // -63.0f
		//BoomComponent->bEnableCameraRotationLag = HoodView.bEnableCameraRotationLag;
		//BoomComponent->bInheritPitch = true;
		//BoomComponent->bInheritRoll = true;
		//BoomComponent->bInheritYaw = true;


		BoomComponent->bUsePawnControlRotation = false;

		break;

	case 3: /// Left View Camera
		VehicleCameraComponent->AttachToComponent(BoomComponent, FAttachmentTransformRules::KeepRelativeTransform, USpringArmComponent::SocketName);
		//BoomComponent->TargetOffset = FVector(0.f, 0.f, 60.f);
		BoomComponent->SetRelativeRotation(FRotator(0.f, -90.0f, 0.f));
		//BoomComponent->TargetArmLength = 100.0f;
		BoomComponent->bEnableCameraRotationLag = true;
		//BoomComponent->bEnableCameraLag = true;

		//BoomComponent->bInheritPitch = false;
		//BoomComponent->bInheritRoll = false;
		//BoomComponent->bInheritYaw = true;




		BoomComponent->bUsePawnControlRotation = false;
		break;

	case 4: /// Right View Camera
		VehicleCameraComponent->AttachToComponent(BoomComponent, FAttachmentTransformRules::KeepRelativeTransform, USpringArmComponent::SocketName);
		//BoomComponent->TargetOffset = FVector(0.f, 0.f, 60.f);
		BoomComponent->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
		//BoomComponent->TargetArmLength = 100.0f;
		BoomComponent->bEnableCameraRotationLag = true;
		//BoomComponent->bEnableCameraLag = true;

		//BoomComponent->bInheritPitch = false;
		//BoomComponent->bInheritRoll = false;
		//BoomComponent->bInheritYaw = true;


		BoomComponent->bUsePawnControlRotation = false;
		break;



	case 5: /// Back View Camera
		VehicleCameraComponent->AttachToComponent(BoomComponent, FAttachmentTransformRules::KeepRelativeTransform, USpringArmComponent::SocketName);
		//BoomComponent->TargetOffset = FVector(0.f, 0.f, BoomComponent->TargetOffset.Z);
		BoomComponent->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));
		BoomComponent->TargetArmLength = 500.0f;
		BoomComponent->bEnableCameraRotationLag = true;
		//BoomComponent->bEnableCameraLag = false;

		//BoomComponent->bInheritPitch = false;
		//BoomComponent->bInheritRoll = false;
		//BoomComponent->bInheritYaw = true;

		BoomComponent->bUsePawnControlRotation = false;

		break;

	case 6: /// Around Camera
		VehicleCameraComponent->AttachToComponent(BoomComponent, FAttachmentTransformRules::KeepRelativeTransform, USpringArmComponent::SocketName);
		BoomComponent->bUsePawnControlRotation = false;

		break;

	case 7: /// Around Free Movement Camera
		VehicleCameraComponent->AttachToComponent(BoomComponent, FAttachmentTransformRules::KeepRelativeTransform, USpringArmComponent::SocketName);
		//BoomComponent->TargetOffset = FVector(0.f, 0.f, 60.f);
		BoomComponent->bUsePawnControlRotation = true;


		break;
	}

}

void ARiders_Vehicle::ToggleScreenShotCamera()
{
	if (TypeCamera == 0 || TypeCamera == 1 || TypeCamera == 7)
	{
		bScreenShotsCamera = !bScreenShotsCamera;


		ARiders_GamePlayerController* VHplayer = Cast<ARiders_GamePlayerController>(Controller);

			if (VHplayer)
			{
				//VHplayer->MyHUD->ShowHUD();
			}

		if (bScreenShotsCamera == true)
		{
			LastCameraType = TypeCamera;

			TypeCamera = 7;
			SetCameraType(TypeCamera);
			bSwitchCameraTypes = false;
		}

		else if (bScreenShotsCamera == false)
		{
			TypeCamera = LastCameraType;
			SetCameraType(TypeCamera);
			bSwitchCameraTypes = true;

			TimeFlyCam = 0.0f;
		}
	}
}

void ARiders_Vehicle::NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

	ARiders_GamePlayerController* PC = Cast<ARiders_GamePlayerController>(Controller);

	if (ImpactTemplate && NormalImpulse.Size() > ImpactEffectNormalForceThreshold)
	{
		//ARiders_VehicleImpactEffect* EffectActor = GetWorld()->SpawnActorDeferred<ARiders_VehicleImpactEffect>(ImpactTemplate, HitLocation, HitNormal.Rotation());

		FTransform NewTransform = FTransform(HitNormal.Rotation(),HitLocation, FVector(1.0f,1.0f,1.0f));

		ARiders_VehicleImpactEffect* EffectActor = GetWorld()->SpawnActorDeferred<ARiders_VehicleImpactEffect>(ImpactTemplate, NewTransform,nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		if (EffectActor)
		{
			float DotBetweenHitAndUpRotation = FVector::DotProduct(HitNormal, GetBaseMesh()->GetUpVector());
			EffectActor->HitSurface = Hit;
			EffectActor->HitForce = NormalImpulse;
			EffectActor->bWheelLand = DotBetweenHitAndUpRotation > 0.8;
			UGameplayStatics::FinishSpawningActor(EffectActor, FTransform(HitNormal.Rotation(), HitLocation));
		}


		if (PC)
		{
			PC->ClientPlayCameraShake(ImpactCameraShake, 20.0f);
		}
	}
}


void ARiders_Vehicle::PressStartEngine()
{
	if (!bEngineStarted)
	{
		VehiclePlayEnterSound();
		bEngineStarted = true;

		if (bShowDebug)
		{
			UE_LOG(VehicleLog, Log, TEXT("Press Start Vehicle Engine"));
		}
	}
}


void ARiders_Vehicle::MoveForward(float Value)
{
	//APlayer_GamePlayerController* RiderPC = Cast<ARiders_GamePlayerController>(Controller);


	//UE_LOG(VehicleLog,Log,TEXT("Input Throttle - %f"),Value)


	//UE_LOG(VehicleLog, Log, TEXT("GetCurrentGear %d"), GetVehicleMovement()->GetCurrentGear());
	//UE_LOG(VehicleLog, Log, TEXT("GetTargetGear %d"), GetVehicleMovement()->GetTargetGear());


	if (Controller)
	{

		if (Controller->IsMoveInputIgnored() == false)
		{
			GetVehicleMovement()->SetThrottleInput(Value);
			VehicleThrottle = Value;
				
			TMap<FName, UMaterialInstanceDynamic*> ReverseMats = GetPartComponents()->ReverseLightMaterials;
			
			if (VehicleThrottle > 0)
			{
				if (!bOnMoveForward)
				{
					bOnMoveForward = true;
					bOnStopping = false;
					bOnMoveReverse = false;
					bOnIdle = false;
					OnMoveForward.Broadcast();
				}

				//for (auto & Item : ReverseMats)
				//{
				//	if (Item.Value != nullptr)
				//	{
				//		Item.Value->SetVectorParameterValue("EmissiveColor", GetPartComponents()->ReverseLight.Find(Item.Key)->ReturnColor);

				//		RevL_Light->SetVisibility(false, false);
				//		RevR_Light->SetVisibility(false, false);
				//	}
				//}
			}

			else if(VehicleThrottle < 0)
			{
				if (GetVehicleMovement()->GetCurrentGear() < 0)
				{
					if (!bOnMoveReverse)
					{
						bOnMoveReverse = true;
						bOnStopping = false;
						bOnMoveForward = false;
						bOnIdle = false;
						OnMoveReverse.Broadcast();
					}
					//for (auto & Item : ReverseMats)
					//{
					//	if (Item.Value != nullptr)
					//	{
					//		Item.Value->SetVectorParameterValue("EmissiveColor", GetPartComponents()->ReverseLight.Find(Item.Key)->LightColor);

					//		RevL_Light->SetVisibility(true, false);
					//		RevR_Light->SetVisibility(true, false);
					//	}
					//}
				}

				else
				{
					if (GetVehicleMovement()->GetForwardSpeed() > 0)
					{
						if (!bOnStopping)
						{
							bOnMoveForward = false;
							bOnMoveReverse = false;
							bOnStopping = true;
							bOnIdle = false;
							OnStopping.Broadcast();
						}
					}
				}
			}

			else
			{
				if (!bOnIdle)
				{
					bOnMoveForward = false;
					bOnMoveReverse = false;
					bOnStopping = false;
					bOnIdle = true;

					OnIdle.Broadcast();
				}

			}
		}

	}
}

void ARiders_Vehicle::MoveRight(float Value)
{

	//ARiders_GamePlayerController* RiderPC = Cast<ARiders_GamePlayerController>(Controller);
	if (Controller)
	{

		if (Controller->IsMoveInputIgnored() == false)
		{
			GetVehicleMovement()->SetSteeringInput(Value);
			VehicleSteering = Value;
		}
	}
}

void ARiders_Vehicle::DriftingStop()
{
	GetVehicleMovement()->SetWheelLatStiff(0, 50.0f, 2.0f, 2000.0f, DefaultTireConfigs[0]);
	GetVehicleMovement()->SetWheelLatStiff(1, 50.0f, 2.0f, 2000.0f, DefaultTireConfigs[1]);
	GetVehicleMovement()->SetWheelLatStiff(2, 50.0f, 2.0f, 1000.0f, DefaultTireConfigs[2]);
	GetVehicleMovement()->SetWheelLatStiff(3, 50.0f, 2.0f, 1000.0f, DefaultTireConfigs[3]);
}



void ARiders_Vehicle::HandBrakeOn()
{
	//ARiders_GamePlayerController* RiderPC = Cast<ARiders_GamePlayerController>(Controller);

	if (Controller)
	{

		if (Controller->IsMoveInputIgnored() == false)
		{
			bHandbrakeActive = true;
			GetVehicleMovement()->SetHandbrakeInput(true);

			OnHandBrake.Broadcast(bHandbrakeActive);

			//URiders_FrontWheels* FLWheel = Cast<URiders_FrontWheels>(GetVehicleMovement()->Wheels[0]);

			//if (FMath::Abs(FLWheel->DebugLatForce) > 350000.0f)
			//{

			//	bDrifting = true;
				//GetVehicleMovement()->SetWheelLatStiff(0, 0.0f, 2.0f, 0.0f, Cast<URidersVehicleWheel>(GetVehicleMovement()->Wheels[0])->HandbrakeTireConfig);
				//GetVehicleMovement()->SetWheelLatStiff(1, 0.0f, 2.0f, 0.0f, Cast<URidersVehicleWheel>(GetVehicleMovement()->Wheels[1])->HandbrakeTireConfig);
				//GetVehicleMovement()->SetWheelLatStiff(2, 5.0f, 2.0f, 1000.0f, Cast<URidersVehicleWheel>(GetVehicleMovement()->Wheels[2])->HandbrakeTireConfig);
				//GetVehicleMovement()->SetWheelLatStiff(3, 5.0f, 2.0f, 1000.0f, Cast<URidersVehicleWheel>(GetVehicleMovement()->Wheels[3])->HandbrakeTireConfig);

			//	TimerDuration = UKismetMathLibrary::MapRangeClamped(FMath::Abs(FLWheel->DebugLatForce), 350000.0f, 1000000.0f, 0.1f, 3.0f);
			//}

			//TMap<FName, UMaterialInstanceDynamic*> RearMats = GetPartComponents()->RearLightMaterials;

			//for (auto & Item : RearMats)
			//{
			//	if (Item.Value != nullptr)
			//	{
			//		Item.Value->SetVectorParameterValue("EmissiveColor", GetPartComponents()->RearLight.Find(Item.Key)->LightColor);

			//		RL_Light->SetVisibility(true, false);
			//		RR_Light->SetVisibility(true, false);
			//	}
			//}
		}

	}
}

void ARiders_Vehicle::HandBrakeOff()
{
	//ARiders_GamePlayerController* RiderPC = Cast<ARiders_GamePlayerController>(Controller);

	if (Controller)
	{
		bHandbrakeActive = false;
		GetVehicleMovement()->SetHandbrakeInput(false);

		OnHandBrake.Broadcast(bHandbrakeActive);


		//URiders_FrontWheels* FLWheel = Cast<URiders_FrontWheels>(GetVehicleMovement()->Wheels[0]);
		//URiders_FrontWheels* FRWheel = Cast<URiders_FrontWheels>(GetVehicleMovement()->Wheels[1]);

		//URiders_RearWheels* RLWheel = Cast<URiders_RearWheels>(GetVehicleMovement()->Wheels[2]);
		//URiders_RearWheels* RRWheel = Cast<URiders_RearWheels>(GetVehicleMovement()->Wheels[3]);

		//TMap<FName, UMaterialInstanceDynamic*> RearMats = GetPartComponents()->RearLightMaterials;

		//for (auto & Item : RearMats)
		//{
		//	if (Item.Value != nullptr)
		//	{
		//		Item.Value->SetVectorParameterValue("EmissiveColor", GetPartComponents()->RearLight.Find(Item.Key)->ReturnColor);

		//		RL_Light->SetVisibility(false, false);
		//		RR_Light->SetVisibility(false, false);
		//	}
		//}
	}
}




void ARiders_Vehicle::SetAutoGearBox(bool bAutoGearBox)
{
	GetVehicleMovement()->SetUseAutoGears(bAutoGearBox);
}

void ARiders_Vehicle::GearUP()
{
	if (!GetVehicleMovement()->GetUseAutoGears())
	{

		if (GetVehicleMovement()->GetCurrentGear() < GetVehicleMovement()->TransmissionSetup.ForwardGears.Num())
		{
			CurrentGear = GetVehicleMovement()->GetCurrentGear() + 1;

			GetVehicleMovement()->SetTargetGear(0, true);

			GetVehicleMovement()->SetTargetGear(CurrentGear, true);

		}
	}
}

void ARiders_Vehicle::GearDown()
{
	if (!GetVehicleMovement()->GetUseAutoGears())
	{
		if (GetVehicleMovement()->GetCurrentGear() > 1)
		{
			CurrentGear = GetVehicleMovement()->GetCurrentGear() - 1;

			GetVehicleMovement()->SetTargetGear(0, true);

			GetVehicleMovement()->SetTargetGear(CurrentGear, true);
		}
	}
}



void ARiders_Vehicle::VehiclePlayEnterSound()
{
	StartEngineSoundTimed();
}


void ARiders_Vehicle::StartEngineSoundTimed()
{

	if (EngineStartOffsetSecs > 0.0f)
	{
		if (bEnableFMOD)
		{
			if (!EngineSoundComponent->IsPlaying())
			{
				EngineSoundComponent->Play();
			}
		}

		GetWorldTimerManager().SetTimer(StartEngineHandle,this,&ARiders_Vehicle::StartEngineSound,GetWorld()->GetDeltaSeconds(),false,EngineStartOffsetSecs);
	}

	else
	{
		StartEngineSound();
	}

}

void ARiders_Vehicle::StartEngineSound()
{
	ARiders_GamePlayerController* RiderPC = Cast<ARiders_GamePlayerController>(Controller);

	if (RiderPC)
	{
		RiderPC->SetIgnoreMoveInput(false);


		const USkeletalMeshSocket* LeftParticleSocket = GetBaseMesh()->GetSocketByName(TEXT("BoosterLeftSocket"));

		if (LeftParticleSocket)
		{
			if (!LeftSmokeParticleSystemComponent)
			{
				LeftSmokeParticleSystemComponent = NewObject<UParticleSystemComponent>(this,TEXT("LeftSmokeComponent"));
				LeftSmokeParticleSystemComponent->bAutoRegister = true;
				LeftSmokeParticleSystemComponent->SetTemplate(SmokeEffect);
				LeftSmokeParticleSystemComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform, TEXT("BoosterLeftSocket"));
				LeftSmokeParticleSystemComponent->RegisterComponent();
			}

			else if (LeftSmokeParticleSystemComponent)
			{
				LeftSmokeParticleSystemComponent->ActivateSystem(true);
			}
		}



		const USkeletalMeshSocket* RightParticleSocket = GetBaseMesh()->GetSocketByName(TEXT("BoosterRightSocket"));

		if (RightParticleSocket)
		{
			if (!RightSmokeParticleSystemComponent)
			{
				RightSmokeParticleSystemComponent = NewObject<UParticleSystemComponent>(this, TEXT("RightSmokeComponent"));
				RightSmokeParticleSystemComponent->bAutoRegister = true;
				RightSmokeParticleSystemComponent->SetTemplate(SmokeEffect);
				RightSmokeParticleSystemComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform, TEXT("BoosterRightSocket"));
				RightSmokeParticleSystemComponent->RegisterComponent();
			}

			else if (RightSmokeParticleSystemComponent)
			{
				RightSmokeParticleSystemComponent->ActivateSystem(true);
			}
		}
	}

	GetWorldTimerManager().ClearTimer(StartEngineHandle);
}

void ARiders_Vehicle::StopEngineSound()
{

	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("Engine Stopped"));

	if (LeftSmokeParticleSystemComponent)
	{
		LeftSmokeParticleSystemComponent->DeactivateSystem();
	}

	if (RightSmokeParticleSystemComponent)
	{
		RightSmokeParticleSystemComponent->DeactivateSystem();
	}
	bEngineStarted = false;

	//EngineAC->Stop();

}

void ARiders_Vehicle::PlayHornSound()
{

	HornSoundComponent = NewObject<UAudioComponent>(this,TEXT("HornSound"));
	HornSoundComponent->bAutoRegister = true;
	HornSoundComponent->SetSound(HornSound);
	HornSoundComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform,TEXT("EngineSoundSocket"));
	HornSoundComponent->bAutoActivate = false;	
	HornSoundComponent->RegisterComponent();



	if (HornSoundComponent)
	{
		HornSoundComponent->Play();
	}
}


void ARiders_Vehicle::StopHornSound()
{
	if (HornSoundComponent)
	{
		HornSoundComponent->Stop();


		HornSoundComponent->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		HornSoundComponent->UnregisterComponent();
		HornSoundComponent->DestroyComponent();
	}
}




void ARiders_Vehicle::ToggleDebug()
{
	bShowDebug = !bShowDebug;
}


void ARiders_Vehicle::TeleportToLCP()
{
	
	for (int i = 0; i > GetVehicleMovement()->Wheels.Num(); i++)
	{
		bSkidding[i] = false;
		if (SkidWheelPSC[i] != NULL)
		{
			SkidWheelPSC[i]->DeactivateSystem();
		}
		//WheelSmokePSC[i]->DeactivateSystem();
	}

	GetBaseMesh()->SetAllPhysicsPosition(VehicleRespawnPosition.GetLocation());
	GetBaseMesh()->SetAllPhysicsRotation(VehicleRespawnPosition.GetRotation().Rotator());
	GetBaseMesh()->SetAllPhysicsAngularVelocityInRadians(FVector(0.0f, 0.0f, 0.0f), false);
	GetBaseMesh()->SetAllPhysicsLinearVelocity(FVector(0.0f, 0.0f, 0.0f), false);

	TimeToRespawn = 0.0f;
}


void ARiders_Vehicle::RotVehicle()
{
	FRotator VHTempRot;
	FVector VHTempLoc;

	VHTempRot = GetActorRotation();
	VHTempRot.Roll = VHTempRot.Roll + 180.0f;

	VHTempLoc = GetActorLocation() + 50.0f;


	GetBaseMesh()->SetAllPhysicsPosition(VHTempLoc);
	GetBaseMesh()->SetAllPhysicsRotation(VHTempRot);
}



void ARiders_Vehicle::FrontLightToggle()
{
	bFrontLightActivate = !bFrontLightActivate;

	if (bFrontLightActivate)
	{
		//FL_Light->SetVisibility(true);
		//FR_Light->SetVisibility(true);

		//if (FL_Light->bVisible == true && FR_Light->bVisible == true)
		//{
		//	TMap<FName, UMaterialInstanceDynamic*> FrontMats = GetPartComponents()->FrontLightMaterials;

		//	for (auto & Item : FrontMats)
		//	{
		//		if (Item.Value != nullptr)
		//		{
		//			Item.Value->SetVectorParameterValue("EmissiveColor", GetPartComponents()->FrontLight.Find(Item.Key)->LightColor);
		//		}
		//	}
		//}

		FrontLightTurnOn();

	}

	else if (!bFrontLightActivate)
	{
		//FL_Light->SetVisibility(false);
		//FR_Light->SetVisibility(false);

		//if (FL_Light->bVisible == false && FR_Light->bVisible == false)
		//{
		//	TMap<FName, UMaterialInstanceDynamic*> FrontMats = GetPartComponents()->FrontLightMaterials;

		//	for (auto & Item : FrontMats)
		//	{
		//		if (Item.Value != nullptr)
		//		{
		//			Item.Value->SetVectorParameterValue("EmissiveColor", GetPartComponents()->FrontLight.Find(Item.Key)->ReturnColor);
		//		}
		//	}
		//}

		FrontLightTurnOff();
	}
}


void ARiders_Vehicle::FrontLightTurnOn()
{
	bFrontLightActivate = true;

	if (bFrontLightActivate)
	{
		FL_Light->SetVisibility(true);
		FR_Light->SetVisibility(true);

		if (FL_Light->bVisible == true && FR_Light->bVisible == true)
		{
			TMap<FName, UMaterialInstanceDynamic*> FrontMats = GetPartComponents()->FrontLightMaterials;

			for (auto & Item : FrontMats)
			{
				if (Item.Value != nullptr)
				{
					Item.Value->SetVectorParameterValue("EmissiveColor", GetPartComponents()->FrontLight.Find(Item.Key)->LightColor);
				}
			}
		}
	}

	TArray<FLightMaterials> RearMats = GetPartComponents()->RearLightMaterials;

	int i = 0;

	for (auto & Item : RearMats)
	{
		if (Item.Material != nullptr)
		{

			if (GetPartComponents()->RearLight[i].bNight)
			{
				GetPartComponents()->RearLight[i].ReturnColor = FLinearColor(0.5f, 0.0f, 0.0f, 1.0f);
			}

			Item.Material->SetVectorParameterValue("EmissiveColor", GetPartComponents()->RearLight[i].ReturnColor);
		}

		i++;
	}
}

void ARiders_Vehicle::FrontLightTurnOff()
{
	bFrontLightActivate = false;

	if (!bFrontLightActivate)
	{
		FL_Light->SetVisibility(false);
		FR_Light->SetVisibility(false);

		if (FL_Light->bVisible == false && FR_Light->bVisible == false)
		{
			TMap<FName, UMaterialInstanceDynamic*> FrontMats = GetPartComponents()->FrontLightMaterials;

			for (auto & Item : FrontMats)
			{
				if (Item.Value != nullptr)
				{
					Item.Value->SetVectorParameterValue("EmissiveColor", GetPartComponents()->FrontLight.Find(Item.Key)->ReturnColor);
				}
			}
		}
	}

	TArray<FLightMaterials> RearMats = GetPartComponents()->RearLightMaterials;

	int i = 0;

	for (auto & Item : RearMats)
	{
		if (Item.Material != nullptr)
		{
			if (GetPartComponents()->RearLight[i].bNight)
			{
				GetPartComponents()->RearLight[i].ReturnColor = FLinearColor(0.0f, 0.0f, 0.0f, 1.0f);
			}
			Item.Material->SetVectorParameterValue("EmissiveColor", GetPartComponents()->RearLight[i].ReturnColor);
		}

		i++;
	}
}

bool ARiders_Vehicle::IsVehicleInverted()
{

	if (GetActorRotation().Roll >= 90.0f || GetActorRotation().Roll <= -90.0f || GetActorRotation().Pitch >= 90.0f || GetActorRotation().Pitch <= -90.0f)
	{
		return true;
	}

	else
	{
		return false;
	}
}

#if WITH_EDITOR
void ARiders_Vehicle::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	FName PropertyName = (PropertyChangedEvent.Property != NULL) ? PropertyChangedEvent.Property->GetFName() : NAME_None;

	if (PropertyName == TEXT("bUseTwoColorMaterial") ||
		PropertyName == TEXT("TypeMaterial") ||
		PropertyName == TEXT("Color") ||
		PropertyName == TEXT("MaterialIndex")
		)
	{
		if (bShowDebug)
		{
			UE_LOG(VehicleLog, Warning, TEXT("changed - %s"), *PropertyName.ToString());
		}
	}

	//GetPartComponents()->UpdateVehicleProperties();

	//if (PropertyName == GET_MEMBER_NAME_CHECKED(ARiders_Vehicle, Test))
	//{
	//	// look for cycles
	//	
	//	UE_LOG(VehicleLog, Warning, TEXT("changed - %s"), *PropertyName.ToString());
	//}
	//OnMaterialChange();

	Super::PostEditChangeProperty(PropertyChangedEvent);
}

void ARiders_Vehicle::PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedChainEvent)
{
	Super::PostEditChangeChainProperty(PropertyChangedChainEvent);
}
#endif


void ARiders_Vehicle::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (!GetVehicleMovement()->IsRegistered())
	{
		GetVehicleMovement()->RegisterComponent();
	}


	if (GetVehicleMovement()->IsRegistered())
	{
	}


	if (GetPartComponents()->IsRegistered())
	{
		GetPartComponents()->UpdateVehicleProperties();
	}
}

void ARiders_Vehicle::SetInbodyColor(FLinearColor Color)
{
	InBodyColor = Color;
}

////////////////////////////////////////////////////////////////////////////
/******************************  Network Replicate ************************/
////////////////////////////////////////////////////////////////////////////

void ARiders_Vehicle::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}