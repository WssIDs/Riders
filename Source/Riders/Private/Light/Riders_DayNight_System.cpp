// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Light/Riders_DayNight_System.h"
#include "Engine/CollisionProfile.h"
#include "UObject/ConstructorHelpers.h"

DEFINE_LOG_CATEGORY(SkySystemLog);

// Sets default values
ARiders_DayNight_System::ARiders_DayNight_System()
{

	static ConstructorHelpers::FObjectFinder<UStaticMesh> DefaultSkyMeshOb(TEXT("StaticMesh'/Game/Environment/Sky/RS_Sphere.RS_Sphere'"));
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> DefaultMaterial(TEXT("Material'/Game/Environment/Sky/Main_Sky_Material.Main_Sky_Material'"));


	MainMaterial = DefaultMaterial.Object;
	SkyMesh = DefaultSkyMeshOb.Object;

	// Structure to hold one-time initialization
	struct FSunConstructorStatics
	{
		FName ID_Lighting;
		FText NAME_Lighting;
		FSunConstructorStatics()
			: ID_Lighting(TEXT("SunLighting"))
			, NAME_Lighting(NSLOCTEXT("SpriteCategory", "SunLighting", "Lighting"))
		{
		}
	};
	static FSunConstructorStatics SunConstructorStatics;

	// Structure to hold one-time initialization
	struct FMoonConstructorStatics
	{
		FName ID_Lighting;
		FText NAME_Lighting;
		FMoonConstructorStatics()
			: ID_Lighting(TEXT("MoonLighting"))
			, NAME_Lighting(NSLOCTEXT("SpriteCategory", "MoonLighting", "Lighting"))
		{
		}
	};
	static FMoonConstructorStatics MoonConstructorStatics;


	bRunConstructionScriptOnDrag = true;
	//bRunningUserConstructionScript = true;

	PrimaryActorTick.bCanEverTick = true;

	Scene = CreateDefaultSubobject<USceneComponent>("BaseScene");
	if (Scene)
	{
		RootComponent = Scene;
	}

	SunLight = CreateDefaultSubobject<UDirectionalLightComponent>(TEXT("SunLight"));
	if (SunLight)
	{
		SunLight->SetMobility(EComponentMobility::Movable);
		SunLight->bUsedAsAtmosphereSunLight = true;
		SunLight->SetupAttachment(Scene);
	}

	MoonLight = CreateDefaultSubobject<UDirectionalLightComponent>(TEXT("MoonLight"));
	if (MoonLight)
	{
		MoonLight->SetMobility(EComponentMobility::Movable);
		MoonLight->bUsedAsAtmosphereSunLight = true;
		MoonLight->SetupAttachment(Scene);
	}

	SkyLight = CreateDefaultSubobject<USkyLightComponent>(TEXT("SkyLight"));
	if (SkyLight)
	{
		SkyLight->SetMobility(EComponentMobility::Movable);
		SkyLight->SetupAttachment(Scene);
	}



	SkyMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SkyMesh"));

	if (SkyMeshComponent)
	{
		SkyMeshComponent->SetStaticMesh(SkyMesh);
		//SkyMeshComponent->SetMaterial(0,MainMaterial);
		SkyMeshComponent->GetBodyInstance()->bAutoWeld = false;
		SkyMeshComponent->SetGenerateOverlapEvents(false);
		//		SkyMeshComponent->bCanEverAffectNavigation = false;
		SkyMeshComponent->CastShadow = false;
		SkyMeshComponent->bCastDynamicShadow = false;
		SkyMeshComponent->bAffectDynamicIndirectLighting = false;
		SkyMeshComponent->bReceivesDecals = false;
		SkyMeshComponent->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
		SkyMeshComponent->SetRelativeScale3D(FVector(400.0f, 400.0f, 400.0f));
		SkyMeshComponent->SetupAttachment(Scene);
	}


	SunLightArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("SunLightArrow"));
	if (SunLightArrowComponent)
	{
		SunLightArrowComponent->ArrowColor = FColor(150, 200, 255);
		SunLightArrowComponent->bTreatAsASprite = true;
		SunLightArrowComponent->SpriteInfo.Category = SunConstructorStatics.ID_Lighting;
		SunLightArrowComponent->SpriteInfo.DisplayName = SunConstructorStatics.NAME_Lighting;
		SunLightArrowComponent->SetupAttachment(SunLight);
		SunLightArrowComponent->bIsScreenSizeScaled = true;
	}

	MoonLightArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("MoonLightArrow"));
	if (SunLightArrowComponent)
	{
		MoonLightArrowComponent->ArrowColor = FColor(150, 200, 255);
		MoonLightArrowComponent->bTreatAsASprite = true;
		MoonLightArrowComponent->SpriteInfo.Category = MoonConstructorStatics.ID_Lighting;
		MoonLightArrowComponent->SpriteInfo.DisplayName = MoonConstructorStatics.NAME_Lighting;
		MoonLightArrowComponent->SetupAttachment(MoonLight);
		MoonLightArrowComponent->bIsScreenSizeScaled = true;
	}




////////////////////// DNS


	HourDuration = 1;



	//// Curve

	const ConstructorHelpers::FObjectFinder<UCurveLinearColor> ZenithColorCurveOb(TEXT("CurveLinearColor'/Game/Environment/Sky/Main_Zenith_Color.Main_Zenith_Color'"));
	const ConstructorHelpers::FObjectFinder<UCurveLinearColor> HorizontColorCurveOb(TEXT("CurveLinearColor'/Game/Environment/Sky/Main_Horizont_Color.Main_Horizont_Color'"));
	const ConstructorHelpers::FObjectFinder<UCurveLinearColor> CloudColorCurveOb(TEXT("CurveLinearColor'/Game/Environment/Sky/Main_Cloud_Color.Main_Cloud_Color'"));

	const ConstructorHelpers::FObjectFinder<UCurveFloat> SunPitchCurveOb(TEXT("CurveFloat'/Game/Environment/Sky/LightCurves/R_SunPitch.R_SunPitch'"));
	const ConstructorHelpers::FObjectFinder<UCurveFloat> SunYawCurveOb(TEXT("CurveFloat'/Game/Environment/Sky/LightCurves/R_Sunyaw.R_SunYaw'"));

	const ConstructorHelpers::FObjectFinder<UCurveFloat> Time24Ob(TEXT("CurveFloat'/Game/Environment/Sky/LightCurves/R_Time24.R_Time24'"));

	const ConstructorHelpers::FObjectFinder<UCurveFloat> MoonPitchCurveOb(TEXT("CurveFloat'/Game/Environment/Sky/LightCurves/R_MoonPitch.R_MoonPitch'"));
	const ConstructorHelpers::FObjectFinder<UCurveFloat> MoonYawCurveOb(TEXT("CurveFloat'/Game/Environment/Sky/LightCurves/R_MoonYaw.R_MoonYaw'"));



	ZenithColorCurve.ExternalCurve = ZenithColorCurveOb.Object;
	HorizontColorCurve.ExternalCurve = HorizontColorCurveOb.Object;
	CloudColorCurve.ExternalCurve = CloudColorCurveOb.Object;

	SunPitchCurve.ExternalCurve = SunPitchCurveOb.Object;
	SunYawCurve.ExternalCurve = SunYawCurveOb.Object;
	Time24Curve.ExternalCurve = Time24Ob.Object;

	MoonPitchCurve.ExternalCurve = MoonPitchCurveOb.Object;
	MoonYawCurve.ExternalCurve = MoonYawCurveOb.Object;


	FOnTimelineFloat sunPitchFunction{};
	sunPitchFunction.BindUFunction(this, "UpdateSunPitch");

	FOnTimelineFloat sunYawFunction{};
	sunYawFunction.BindUFunction(this, "UpdateSunYaw");

	FOnTimelineFloat Time24Function{};
	Time24Function.BindUFunction(this, "UpdateTime24");

	FOnTimelineFloat moonPitchFunction{};
	moonPitchFunction.BindUFunction(this, "UpdateMoonPitch");

	FOnTimelineFloat moonYawFunction{};
	moonYawFunction.BindUFunction(this, "UpdateMoonYaw");


	//SunPitch
	DNS_TimeLines[0] = FTimeline();
	DNS_TimeLines[0].SetLooping(true);
	DNS_TimeLines[0].AddInterpFloat(SunPitchCurve.ExternalCurve, sunPitchFunction, FName{ TEXT("SunPitch") });

	//SunYaw
	DNS_TimeLines[1] = FTimeline();
	DNS_TimeLines[1].SetLooping(true);
	DNS_TimeLines[1].AddInterpFloat(SunYawCurve.ExternalCurve, sunYawFunction, FName{ TEXT("SunYaw") });

	//Time24
	DNS_TimeLines[2] = FTimeline();
	DNS_TimeLines[2].SetLooping(true);
	DNS_TimeLines[2].AddInterpFloat(Time24Curve.ExternalCurve, Time24Function, FName{ TEXT("Time24") });

	//MoonPitch
	DNS_TimeLines[3] = FTimeline();
	DNS_TimeLines[3].SetLooping(true);
	DNS_TimeLines[3].AddInterpFloat(MoonPitchCurve.ExternalCurve, moonPitchFunction, FName{ TEXT("MoonPitch") });

	//MoonYaw
	DNS_TimeLines[4] = FTimeline();
	DNS_TimeLines[4].SetLooping(true);
	DNS_TimeLines[4].AddInterpFloat(MoonYawCurve.ExternalCurve, moonYawFunction, FName{ TEXT("MoonYaw") });





	SunLightIntensityInterpolation = 1.0f;
	SkyLightIntensityInterpolation = 1.0f;
	MoonLightIntensityInterpolation = 1.0f;

	SunLightIntensity = 5.0f;
	SkyLightIntensity = 1.0f;
	MoonLightIntensity = 0.01f;




	CloudSpeed = 1.0f;
	SunBrightness = 50.0f;
	CloudOpacity = 2.0f;
	StarsBrightness = 0.1f;
	MoonBrightness = 0.1f;


	HorizonFalloff = 3.0f;
	HorizonColor = FLinearColor(1.979559, 2.586644, 3.000000, 1.000000);
	ZenithColor = FLinearColor(0.034046, 0.109247, 0.295000, 1.000000);
	OveralColor = FLinearColor(1.000000, 1.000000, 1.000000, 1.000000);
	CloudColor = FLinearColor(0.855778, 0.919020, 1.000000, 1.000000);


	OnChangedTimeOfDayDelegate.AddDynamic(this, &ARiders_DayNight_System::ReceiveChangedTimeOfDay);

}


void ARiders_DayNight_System::ReceiveChangedTimeOfDay(ETimesOfDay TimeDay)
{
	ChangedTimeOfDay(TimeDay);

	UE_LOG(SkySystemLog, Log, TEXT("Change Time of Day"));
}

void ARiders_DayNight_System::UpdateSunPosition()
{

	//SunLight->AddLocalRotation(FRotator(0.01f, 0.0f, 0.0f).Quaternion());


	//UE_LOG(SkySystemLog, Log, TEXT("SunPos %f"), SunLight->GetRelativeTransform().Rotator().Pitch);


	//float Test = FMath::GetMappedRangeValueClamped(FVector2D(-90, 90), FVector2D(0, 24), SunLight->GetRelativeTransform().Rotator().Pitch);

	//UE_LOG(SkySystemLog, Log, TEXT("SunTime %f"), Test);




	SkyMaterial->SetVectorParameterValue(FName(TEXT("Moon Direction")), MoonLight->GetRelativeTransform().Rotator().Vector());
	SkyMaterial->SetVectorParameterValue(FName(TEXT("Moon Color")), MoonLight->LightColor);

	SkyMaterial->SetVectorParameterValue(FName(TEXT("Light Direction")), SunLight->GetRelativeTransform().Rotator().Vector());
	SkyMaterial->SetVectorParameterValue(FName(TEXT("Sun Color")), SunLight->LightColor);

	SunHeight = FMath::GetMappedRangeValueClamped(FVector2D(-90, 90), FVector2D(1, -1), SunLight->GetRelativeTransform().Rotator().Pitch);

	SkyMaterial->SetVectorParameterValue(FName(TEXT("Horizon color")), HorizontColorCurve.ExternalCurve->GetLinearColorValue(SunHeight));
	SkyMaterial->SetVectorParameterValue(FName(TEXT("Zenith color")), ZenithColorCurve.ExternalCurve->GetLinearColorValue(SunHeight));
	SkyMaterial->SetVectorParameterValue(FName(TEXT("Cloud color")), CloudColorCurve.ExternalCurve->GetLinearColorValue(SunHeight));
	SkyMaterial->SetScalarParameterValue(FName(TEXT("Horizon falloff")), FMath::Lerp(3, 8, FMath::Abs(SunHeight)));
	SkyMaterial->SetScalarParameterValue(FName(TEXT("Sun height")), FMath::FloatSelect(SunHeight, 0.0f, FMath::Abs(SunHeight)));

}


void ARiders_DayNight_System::InitSky()
{

	if (SkyMesh)
	{
		SkyMeshComponent->SetStaticMesh(SkyMesh);
	}

	if (!SkyMaterial)
	{
		SkyMaterial = SkyMeshComponent->CreateAndSetMaterialInstanceDynamicFromMaterial(0, MainMaterial);
	}


	if (SkyMaterial)
	{


		UE_LOG(SkySystemLog, Log, TEXT("Material Name = %s"), *SkyMaterial->GetMaterial()->GetName());
		UE_LOG(SkySystemLog, Log, TEXT("Set Material"));

		SkyMeshComponent->SetMaterial(0, SkyMaterial);

		if (RefreshMaterial || !RefreshMaterial)
		{
			RefreshMaterial = false;
		}

		if (MoonLight)
		{
			SkyMaterial->SetVectorParameterValue(FName(TEXT("Moon Direction")), MoonLight->GetRelativeTransform().Rotator().Vector());
			SkyMaterial->SetVectorParameterValue(FName(TEXT("Moon Color")), MoonLight->LightColor);
			UE_LOG(SkySystemLog, Log, TEXT("MoonLight valid"));
		}

		else if (!MoonLight)
		{

			UE_LOG(SkySystemLog, Warning, TEXT("MoonLight not valid"));
		}

		if (SunLight)
		{
			SkyMaterial->SetVectorParameterValue(FName(TEXT("Light Direction")), SunLight->GetRelativeTransform().Rotator().Vector());
			SkyMaterial->SetVectorParameterValue(FName(TEXT("Sun Color")), SunLight->LightColor);

			SunHeight = FMath::GetMappedRangeValueClamped(FVector2D(-90, 90), FVector2D(1, -1), SunLight->GetRelativeTransform().Rotator().Pitch);

			UE_LOG(SkySystemLog, Log, TEXT("SunLight valid"));

			UE_LOG(SkySystemLog, Log, TEXT("SunHeight %f"), SunHeight);
			UE_LOG(SkySystemLog, Log, TEXT("SunLight Pos %f"), SunLight->GetRelativeTransform().Rotator().Pitch);

		}

		else if (!SunLight)
		{
			SkyMaterial->SetVectorParameterValue(FName(TEXT("Light Direction")), (FRotator(FMath::GetMappedRangeValueClamped(FVector2D(-1, 1), FVector2D(90, -90), SunHeight), SunLight->GetRelativeTransform().Rotator().Yaw, 0.0f)).Vector());
			SkyMaterial->SetVectorParameterValue(FName(TEXT("Sun Color")), FMath::Lerp(FLinearColor(1.0f, 0.221f, 0.04f, 1.0f), FLinearColor(0.954f, 0.901f, 0.744f, 1.0f), FMath::Clamp(SunHeight + 0.2f, 0.0f, 1.0f)));

			UE_LOG(SkySystemLog, Warning, TEXT("Light not valid"));
		}


		if (ColorsDeterminedBySunPosition)
		{
			if (HorizontColorCurve.ExternalCurve)
			{
				SkyMaterial->SetVectorParameterValue(FName(TEXT("Horizon color")), HorizontColorCurve.ExternalCurve->GetLinearColorValue(SunHeight));
			}

			if (ZenithColorCurve.ExternalCurve)
			{
				SkyMaterial->SetVectorParameterValue(FName(TEXT("Zenith color")), ZenithColorCurve.ExternalCurve->GetLinearColorValue(SunHeight));
			}

			if (CloudColorCurve.ExternalCurve)
			{
				SkyMaterial->SetVectorParameterValue(FName(TEXT("Cloud color")), CloudColorCurve.ExternalCurve->GetLinearColorValue(SunHeight));
			}

			SkyMaterial->SetScalarParameterValue(FName(TEXT("Horizon falloff")), FMath::Lerp(3, 8, FMath::Abs(SunHeight)));
			UE_LOG(SkySystemLog, Log, TEXT("ColorDeterminedbysunposition true"));
		}

		else if (!ColorsDeterminedBySunPosition)
		{
			SkyMaterial->SetVectorParameterValue(FName(TEXT("Horizon color")), HorizonColor);
			SkyMaterial->SetVectorParameterValue(FName(TEXT("Zenith color")), ZenithColor);
			SkyMaterial->SetVectorParameterValue(FName(TEXT("Cloud color")), CloudColor);
			SkyMaterial->SetScalarParameterValue(FName(TEXT("Horizon falloff")), HorizonFalloff);
			UE_LOG(SkySystemLog, Warning, TEXT("ColorDeterminedbysunposition false"));
		}

		SkyMaterial->SetScalarParameterValue(FName(TEXT("Cloud speed")), CloudSpeed);
		SkyMaterial->SetScalarParameterValue(FName(TEXT("Sun brightness")), SunBrightness);
		SkyMaterial->SetScalarParameterValue(FName(TEXT("Moon brightness")), MoonBrightness);

		SkyMaterial->SetScalarParameterValue(FName(TEXT("Sun height")), FMath::FloatSelect(SunHeight, 0.0f, FMath::Abs(SunHeight)));

		SkyMaterial->SetScalarParameterValue(FName(TEXT("Cloud opacity")), CloudOpacity);
		SkyMaterial->SetScalarParameterValue(FName(TEXT("Stars brightness")), StarsBrightness);
	}

	else
	{
		UE_LOG(SkySystemLog, Error, TEXT("SkyMaterial don't created!"));
	}

}

void ARiders_DayNight_System::SetTimeDuration(float inRate)
{
	inRate = TimelineRate;
}

void ARiders_DayNight_System::UpdateSunPitch(float Value)
{
	//SunMovement.

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("SunPitch: timeline: %f  value:%f"), DNS_TimeLines[0].GetPlaybackPosition(), Value));

	SunRot.Pitch = Value;
}

void ARiders_DayNight_System::UpdateSunYaw(float Value)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("SunYaw: timeline: %f  value:%f"), DNS_TimeLines[1].GetPlaybackPosition(), Value));

	SunRot.Yaw = Value;

	//SetActorRotation(ActorRot);
	// do something
}

void ARiders_DayNight_System::UpdateTime24(float Value)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Time: timeline: %f  value:%f"), DNS_TimeLines[2].GetPlaybackPosition(), Value));

	DayTime.Hours = Value * 60.0f / 60.0f;

	DayTime.Minutes = int32(Value * 60) % 60;

	DayTime.Seconds = int32(Value * 60 * 60) % 60;

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Time:" + FString::FromInt(Hours) + ":" + FString::FromInt(Minutes) + ":" + FString::FromInt(Seconds)));
}

void ARiders_DayNight_System::UpdateMoonPitch(float Value)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("MoonPitch: timeline: %f  value:%f"), DNS_TimeLines[3].GetPlaybackPosition(), Value));

	MoonRot.Pitch = Value;
}

void ARiders_DayNight_System::UpdateMoonYaw(float Value)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("MoonYaw: timeline: %f  value:%f"), DNS_TimeLines[4].GetPlaybackPosition(), Value));

	MoonRot.Yaw = Value;
}

void ARiders_DayNight_System::SetTime(FTime inTime)
{

	float tmpTime = inTime.Hours + (inTime.Minutes / 60.0f) + (inTime.Seconds / 3600.0f);

	for (int32 i = 0; i < TimelinesCount; i++)
	{
		DNS_TimeLines[i].SetPlaybackPosition(tmpTime, false);

		if (TimeOfDay == ETimesOfDay::DNS_Day)
		{
			SunLight->SetIntensity(SunLightIntensity);
			SkyLight->SetIntensity(SkyLightIntensity);
			MoonLight->SetIntensity(0.0f);

			SunLight->SetCastShadows(true);
			MoonLight->SetCastShadows(false);
		}
		else if (TimeOfDay == ETimesOfDay::DNS_Night)
		{
			SunLight->SetIntensity(0.0f);
			SkyLight->SetIntensity(0.001f);
			MoonLight->SetIntensity(MoonLightIntensity);

			SunLight->SetCastShadows(false);
			MoonLight->SetCastShadows(true);
		}
	}

	//DNS_TimeLines[index].SetNewTime(tmpTime);
}

void ARiders_DayNight_System::UpdateMovement(float DeltaTime)
{
	SunLight->SetRelativeRotation(SunRot);
	MoonLight->SetRelativeRotation(MoonRot);

	//if (SkySphere)
	//{
	//	SkySphere->UpdateSunPos();
	//}
}

// Called when the game starts or when spawned
void ARiders_DayNight_System::BeginPlay()
{
	Super::BeginPlay();

	SkyMaterial = SkyMeshComponent->CreateDynamicMaterialInstance(0, SkyMeshComponent->GetMaterial(0));
	SkyMeshComponent->SetMaterial(0, SkyMaterial);



	//////// DNS

	TimelineRate = 1.0f / (HourDuration * 60.0f);

	if (GEngine)
	{

		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("DayNightSystem are initialized!"));
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::FromInt(TimelinesCount));

	}

	if (bEnableDayNightSystem)
	{
		SetTime(DayTime);

		for (int32 i = 0; i < TimelinesCount; i++)
		{
			DNS_TimeLines[i].SetPlayRate(TimelineRate);
			DNS_TimeLines[i].Play();
		}
	}
	
}

// Called every frame
void ARiders_DayNight_System::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	UpdateSunPosition();





	if (bEnableDayNightSystem)
	{

		// Start Set Hour Duration

		for (int32 i = 0; i < TimelinesCount; i++)
		{

			DNS_TimeLines[i].TickTimeline(DeltaTime);

			if (DNS_TimeLines[i].IsPlaying())
			{
				DNS_TimeLines[i].SetPlayRate(TimelineRate);
			}

			else if (!DNS_TimeLines[i].IsPlaying())
			{
				DNS_TimeLines[i].Play();
			}


		}

		// End Set Hour Duration

		if (SunLight->IsValidLowLevel())
		{

			if (SunLight->GetRelativeTransform().Rotator().Pitch > 0)
			{
				if (TimeOfDay != ETimesOfDay::DNS_Night)
				{
					TimeOfDay = ETimesOfDay::DNS_Night;

					OnChangedTimeOfDayDelegate.Broadcast(TimeOfDay);
					//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Night"));
				}

				else if (TimeOfDay == ETimesOfDay::DNS_Night)
				{

					if (SunLight->Intensity != 0.0f)
					{
						SunLight->SetIntensity(FMath::Lerp(SunLight->Intensity, 0.0f, DeltaTime * SunLightIntensityInterpolation));
						//UE_LOG(SkySystemLog, Log, TEXT("SunLight Intensity = %f"), SunLight->Intensity);
					}

					if (SkyLight->Intensity != 0.001f)
					{
						SkyLight->SetIntensity(FMath::Lerp(SkyLight->Intensity, 0.001f, DeltaTime * SkyLightIntensityInterpolation));
						//UE_LOG(SkySystemLog, Log, TEXT("SkyLight Intensity = %f"), SkyLight->Intensity);
					}

					if (MoonLight->Intensity < MoonLightIntensity)
					{
						MoonLight->SetIntensity(FMath::Lerp(MoonLight->Intensity, MoonLightIntensity, DeltaTime * MoonLightIntensityInterpolation));
						//UE_LOG(SkySystemLog, Log, TEXT("MoonLight Intensity = %f"), MoonLight->Intensity);
					}


					if (SunLight->Intensity == 0.0f)
					{
						SunLight->SetCastShadows(false);
					}

					if (MoonLight->Intensity != 0.0f)
					{
						MoonLight->SetCastShadows(true);
					}

				}

			}

			else if (SunLight->GetRelativeTransform().Rotator().Pitch <= 0)
			{
				if (TimeOfDay != ETimesOfDay::DNS_Day)
				{
					TimeOfDay = ETimesOfDay::DNS_Day;
					OnChangedTimeOfDayDelegate.Broadcast(TimeOfDay);
				}

				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Day"));
				else if (TimeOfDay == ETimesOfDay::DNS_Day)
				{

					if (SunLight->Intensity < SunLightIntensity)
					{
						SunLight->SetIntensity(FMath::Lerp(SunLight->Intensity, SunLightIntensity, DeltaTime * SunLightIntensityInterpolation));
						//UE_LOG(SkySystemLog, Log, TEXT("SunLight Intensity = %f"), SunLight->Intensity);
					}

					if (SkyLight->Intensity < SkyLightIntensity)
					{
						SkyLight->SetIntensity(FMath::Lerp(SkyLight->Intensity, SkyLightIntensity, DeltaTime * SkyLightIntensityInterpolation));
						//UE_LOG(SkySystemLog, Log, TEXT("SkyLight Intensity = %f"), SkyLight->Intensity);
					}

					if (MoonLight->Intensity != 0.0f)
					{
						MoonLight->SetIntensity(FMath::Lerp(MoonLight->Intensity, 0.0f, DeltaTime * MoonLightIntensityInterpolation));
						//UE_LOG(SkySystemLog, Log, TEXT("MoonLight Intensity = %f"), MoonLight->Intensity);
					}


					if (SunLight->Intensity != 0.0f)
					{
						SunLight->SetCastShadows(true);
					}

					if (MoonLight->Intensity == 0.0f)
					{
						MoonLight->SetCastShadows(false);
					}

				}
			}

		}

		UpdateMovement(DeltaTime);
	}

	else if (!bEnableDayNightSystem)
	{
		for (int32 i = 0; i < TimelinesCount; i++)
		{
			if (DNS_TimeLines[i].IsPlaying())
			{
				DNS_TimeLines[i].Stop();
			}
		}
	}



}


void ARiders_DayNight_System::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	InitSky();


	float tmpTime = DayTime.Hours + (DayTime.Minutes / 60.0f) + (DayTime.Seconds / 3600.0f);


	for (int32 i = 0; i < TimelinesCount; i++)
	{
		DNS_TimeLines[i].SetPlaybackPosition(tmpTime, false);
	}


	if (SunPitchCurve.ExternalCurve && SunYawCurve.ExternalCurve)
	{
		SunLight->SetRelativeRotation(FRotator(SunPitchCurve.ExternalCurve->GetFloatValue(tmpTime), SunYawCurve.ExternalCurve->GetFloatValue(tmpTime), SunLight->GetRelativeTransform().Rotator().Roll));
	}

	if (MoonPitchCurve.ExternalCurve && MoonYawCurve.ExternalCurve)
	{
		MoonLight->SetRelativeRotation(FRotator(MoonPitchCurve.ExternalCurve->GetFloatValue(tmpTime), MoonYawCurve.ExternalCurve->GetFloatValue(tmpTime), MoonLight->GetRelativeTransform().Rotator().Roll));
	}

	if (SkyMaterial)
	{

		SkyMaterial->SetVectorParameterValue(FName(TEXT("Moon Direction")), MoonLight->GetRelativeTransform().Rotator().Vector());
		SkyMaterial->SetVectorParameterValue(FName(TEXT("Moon Color")), MoonLight->LightColor);

		SkyMaterial->SetVectorParameterValue(FName(TEXT("Light Direction")), SunLight->GetRelativeTransform().Rotator().Vector());
		SkyMaterial->SetVectorParameterValue(FName(TEXT("Sun Color")), SunLight->LightColor);

		SunHeight = FMath::GetMappedRangeValueClamped(FVector2D(-90, 90), FVector2D(1, -1), SunLight->GetRelativeTransform().Rotator().Pitch);

		if (HorizontColorCurve.ExternalCurve)
		{
			SkyMaterial->SetVectorParameterValue(FName(TEXT("Horizon color")), HorizontColorCurve.ExternalCurve->GetLinearColorValue(SunHeight));
		}

		if (ZenithColorCurve.ExternalCurve)
		{
			SkyMaterial->SetVectorParameterValue(FName(TEXT("Zenith color")), ZenithColorCurve.ExternalCurve->GetLinearColorValue(SunHeight));
		}

		if (CloudColorCurve.ExternalCurve)
		{
			SkyMaterial->SetVectorParameterValue(FName(TEXT("Cloud color")), CloudColorCurve.ExternalCurve->GetLinearColorValue(SunHeight));
		}

		SkyMaterial->SetScalarParameterValue(FName(TEXT("Horizon falloff")), FMath::Lerp(3, 8, FMath::Abs(SunHeight)));
		SkyMaterial->SetScalarParameterValue(FName(TEXT("Sun height")), FMath::FloatSelect(SunHeight, 0.0f, FMath::Abs(SunHeight)));




		if (SunLight->IsValidLowLevel())
		{

			if (SunLight->GetRelativeTransform().Rotator().Pitch > 0)
			{
				TimeOfDay = ETimesOfDay::DNS_Night;

				if (TimeOfDay == ETimesOfDay::DNS_Night)
				{
					SunLight->SetIntensity(0.0f);
					SkyLight->SetIntensity(0.001f);
					MoonLight->SetIntensity(MoonLightIntensity);

					SunLight->SetCastShadows(false);
					MoonLight->SetCastShadows(true);
				}
			}

			else if (SunLight->GetRelativeTransform().Rotator().Pitch <= 0)
			{
				TimeOfDay = ETimesOfDay::DNS_Day;

				if (TimeOfDay == ETimesOfDay::DNS_Day)
				{
					SunLight->SetIntensity(SunLightIntensity);
					SkyLight->SetIntensity(SkyLightIntensity);
					MoonLight->SetIntensity(0.0f);

					SunLight->SetCastShadows(true);
					MoonLight->SetCastShadows(false);
				}
			}
		}



		GetSunLightArrowComponent()->ArrowColor = SunLight->GetLightColor().ToFColor(true);
		GetMoonLightArrowComponent()->ArrowColor = MoonLight->GetLightColor().ToFColor(true);

	}

	else
	{
		UE_LOG(SkySystemLog, Log, TEXT("Sky Material don't created"));
	}



}

void ARiders_DayNight_System::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

#if WITH_EDITORONLY_DATA

void ARiders_DayNight_System::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	TimelineRate = 1.0f / (HourDuration * 60.0f);
	UE_LOG(SkySystemLog, Log, TEXT("Property Changed"));


	SetTime(DayTime);

	Super::PostEditChangeProperty(PropertyChangedEvent);
}

#endif

class UArrowComponent* ARiders_DayNight_System::GetMoonLightArrowComponent() const
{
	return MoonLightArrowComponent;
}

class UArrowComponent* ARiders_DayNight_System::GetSunLightArrowComponent() const
{
	return SunLightArrowComponent;
}

	

