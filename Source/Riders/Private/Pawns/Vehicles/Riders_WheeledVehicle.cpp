
#include "Pawns/Vehicles/Riders_WheeledVehicle.h"
#include "DisplayDebugHelpers.h"
#include "Engine/CollisionProfile.h"
#include "Runtime/Launch/Resources/Version.h"


DEFINE_LOG_CATEGORY(VehicleLog);

FName ARiders_WheeledVehicle::RidersMovementComponentName(TEXT("RidersMovementComp"));
FName ARiders_WheeledVehicle::VehicleBaseMeshComponentName(TEXT("VehicleBaseMesh"));
FName ARiders_WheeledVehicle::VehicleBodyMeshComponentName(TEXT("VehicleBodyMesh"));
//FName ARiders_WheeledVehicle::VehicleInteriorMeshComponentName(TEXT("VehicleInteriorMesh"));
FName ARiders_WheeledVehicle::VehicleMirrorsMeshComponentName(TEXT("MirrorMesh"));
FName ARiders_WheeledVehicle::VehicleHoodMeshComponentName(TEXT("HoodMesh"));
FName ARiders_WheeledVehicle::VehicleRoofMeshComponentName(TEXT("RoofMesh"));
FName ARiders_WheeledVehicle::VehicleFrontBumperMeshComponentName(TEXT("FrontBumperMesh"));
FName ARiders_WheeledVehicle::VehicleRearBumperMeshComponentName(TEXT("RearBumperMesh"));
FName ARiders_WheeledVehicle::VehicleSpoilerMeshComponentName(TEXT("SpoilerMesh"));
//FName ARiders_WheeledVehicle::VehicleWheelsMeshComponentName(TEXT("WheelsMesh"));
FName ARiders_WheeledVehicle::VehicleRimMeshComponentName(TEXT("RimMesh"));
FName ARiders_WheeledVehicle::VehicleFrontLightMeshComponentName(TEXT("FrontLightMesh"));
FName ARiders_WheeledVehicle::VehicleTailLightMeshComponentName(TEXT("TailLightMesh"));

ARiders_WheeledVehicle::ARiders_WheeledVehicle()
{


	VehicleBaseMesh = CreateDefaultSubobject<USkeletalMeshComponent>(VehicleBaseMeshComponentName);
	VehicleBaseMesh->SetCollisionProfileName(UCollisionProfile::Vehicle_ProfileName);
	VehicleBaseMesh->BodyInstance.bSimulatePhysics = true;
	VehicleBaseMesh->BodyInstance.bNotifyRigidBodyCollision = true;
	VehicleBaseMesh->BodyInstance.bUseCCD = true;
	VehicleBaseMesh->bBlendPhysics = true;
	VehicleBaseMesh->SetGenerateOverlapEvents(true);
	VehicleBaseMesh->PrimaryComponentTick.TickGroup = TG_PostPhysics;
	VehicleBaseMesh->ComponentTags.Add("Base");
	RootComponent = VehicleBaseMesh;



	VehicleBodyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(VehicleBodyMeshComponentName);
	VehicleBodyMesh->SetCollisionProfileName(UCollisionProfile::Vehicle_ProfileName);
	//VehicleBodyMesh->BodyInstance.bSimulatePhysics = true;
	//VehicleBodyMesh->BodyInstance.bNotifyRigidBodyCollision = true;
	//VehicleBodyMesh->BodyInstance.bUseCCD = true;
	//VehicleBodyMesh->bBlendPhysics = true;
	//VehicleBodyMesh->bGenerateOverlapEvents = true;
	//VehicleBodyMesh->PrimaryComponentTick.TickGroup = TG_PostPhysics;
	VehicleBodyMesh->ComponentTags.Add("Body");
	VehicleBodyMesh->SetupAttachment(RootComponent);
	VehicleBodyMesh->SetMasterPoseComponent(VehicleBaseMesh);

	VehicleMirrorsMesh = CreateDefaultSubobject<USkeletalMeshComponent>(VehicleMirrorsMeshComponentName);
	VehicleMirrorsMesh->SetCollisionProfileName(UCollisionProfile::Vehicle_ProfileName);
	//VehicleMirrorsMesh->BodyInstance.bSimulatePhysics = true;
	//VehicleMirrorsMesh->BodyInstance.bNotifyRigidBodyCollision = true;
	//VehicleMirrorsMesh->BodyInstance.bUseCCD = true;
	//VehicleMirrorsMesh->bBlendPhysics = true;
	//VehicleMirrorsMesh->bGenerateOverlapEvents = true;	
	VehicleMirrorsMesh->ComponentTags.Add("Mirrors");
	VehicleMirrorsMesh->SetupAttachment(RootComponent);
	VehicleMirrorsMesh->SetMasterPoseComponent(VehicleBaseMesh);

	VehicleHoodMesh = CreateDefaultSubobject<USkeletalMeshComponent>(VehicleHoodMeshComponentName);
	VehicleHoodMesh->SetCollisionProfileName(UCollisionProfile::Vehicle_ProfileName);
	//VehicleHoodMesh->BodyInstance.bSimulatePhysics = true;
	//VehicleHoodMesh->BodyInstance.bNotifyRigidBodyCollision = true;
	//VehicleHoodMesh->BodyInstance.bUseCCD = true;
	//VehicleHoodMesh->bBlendPhysics = true;
	//VehicleHoodMesh->bGenerateOverlapEvents = true;
	VehicleHoodMesh->ComponentTags.Add("Hood");	
	VehicleHoodMesh->SetupAttachment(RootComponent);
	VehicleHoodMesh->SetMasterPoseComponent(VehicleBaseMesh);

	VehicleRoofMesh = CreateDefaultSubobject<USkeletalMeshComponent>(VehicleRoofMeshComponentName);
	VehicleRoofMesh->SetCollisionProfileName(UCollisionProfile::Vehicle_ProfileName);
	//VehicleRoofMesh->BodyInstance.bSimulatePhysics = true;
	//VehicleRoofMesh->BodyInstance.bNotifyRigidBodyCollision = true;
	//VehicleRoofMesh->BodyInstance.bUseCCD = true;
	//VehicleRoofMesh->bBlendPhysics = true;
	//VehicleRoofMesh->bGenerateOverlapEvents = true;
	VehicleRoofMesh->SetupAttachment(RootComponent);
	VehicleRoofMesh->ComponentTags.Add("Roof");
	VehicleRoofMesh->SetMasterPoseComponent(VehicleBaseMesh);

	VehicleFrontBumperMesh = CreateDefaultSubobject<USkeletalMeshComponent>(VehicleFrontBumperMeshComponentName);
	VehicleFrontBumperMesh->SetCollisionProfileName(UCollisionProfile::Vehicle_ProfileName);
	//VehicleFrontBumperMesh->BodyInstance.bSimulatePhysics = true;
	//VehicleFrontBumperMesh->BodyInstance.bNotifyRigidBodyCollision = true;
	//VehicleFrontBumperMesh->BodyInstance.bUseCCD = true;
	//VehicleFrontBumperMesh->bBlendPhysics = true;
	//VehicleFrontBumperMesh->bGenerateOverlapEvents = true;
	VehicleFrontBumperMesh->SetupAttachment(RootComponent);
	VehicleFrontBumperMesh->ComponentTags.Add("FrontBumper");
	VehicleFrontBumperMesh->SetMasterPoseComponent(VehicleBaseMesh);

	VehicleRearBumperMesh = CreateDefaultSubobject<USkeletalMeshComponent>(VehicleRearBumperMeshComponentName);
	VehicleRearBumperMesh->SetCollisionProfileName(UCollisionProfile::Vehicle_ProfileName);
	//VehicleRearBumperMesh->BodyInstance.bSimulatePhysics = true;
	//VehicleRearBumperMesh->BodyInstance.bNotifyRigidBodyCollision = true;
	//VehicleRearBumperMesh->BodyInstance.bUseCCD = true;
	//VehicleRearBumperMesh->bBlendPhysics = true;
	//VehicleRearBumperMesh->bGenerateOverlapEvents = true;
	VehicleRearBumperMesh->SetupAttachment(RootComponent);
	VehicleRearBumperMesh->ComponentTags.Add("RearBumper");
	VehicleRearBumperMesh->SetMasterPoseComponent(VehicleBaseMesh);


	VehicleSpoilerMesh = CreateDefaultSubobject<USkeletalMeshComponent>(VehicleSpoilerMeshComponentName);
	VehicleSpoilerMesh->SetCollisionProfileName(UCollisionProfile::Vehicle_ProfileName);
	//VehicleSpoilerMesh->BodyInstance.bSimulatePhysics = true;
	//VehicleSpoilerMesh->BodyInstance.bNotifyRigidBodyCollision = true;
	//VehicleSpoilerMesh->BodyInstance.bUseCCD = true;
	//VehicleSpoilerMesh->bBlendPhysics = true;
	//VehicleSpoilerMesh->bGenerateOverlapEvents = true;
	VehicleSpoilerMesh->SetupAttachment(RootComponent);
	VehicleSpoilerMesh->ComponentTags.Add("Spoiler");
	VehicleSpoilerMesh->SetMasterPoseComponent(VehicleBaseMesh);

	VehicleRimMesh = CreateDefaultSubobject<USkeletalMeshComponent>(VehicleRimMeshComponentName);
	VehicleRimMesh->SetCollisionProfileName(UCollisionProfile::Vehicle_ProfileName);
	//VehicleRimMesh->BodyInstance.bSimulatePhysics = true;
	//VehicleRimMesh->BodyInstance.bNotifyRigidBodyCollision = true;
	//VehicleRimMesh->BodyInstance.bUseCCD = true;
	//VehicleRimMesh->bBlendPhysics = true;
	//VehicleRimMesh->bGenerateOverlapEvents = true;
	VehicleRimMesh->SetupAttachment(RootComponent);
	VehicleRimMesh->SetMasterPoseComponent(VehicleBaseMesh);

	VehicleFrontLightMesh = CreateDefaultSubobject<USkeletalMeshComponent>(VehicleFrontLightMeshComponentName);
	VehicleFrontLightMesh->SetCollisionProfileName(UCollisionProfile::Vehicle_ProfileName);
	//VehicleFrontLightMesh->BodyInstance.bSimulatePhysics = true;
	//VehicleFrontLightMesh->BodyInstance.bNotifyRigidBodyCollision = true;
	//VehicleFrontLightMesh->BodyInstance.bUseCCD = true;
	//VehicleFrontLightMesh->bBlendPhysics = true;
	//VehicleFrontLightMesh->bGenerateOverlapEvents = true;
	VehicleFrontLightMesh->SetupAttachment(RootComponent);
	VehicleFrontLightMesh->ComponentTags.Add("FrontLight");
	VehicleFrontLightMesh->SetMasterPoseComponent(VehicleBaseMesh);

	VehicleTailLightMesh = CreateDefaultSubobject<USkeletalMeshComponent>(VehicleTailLightMeshComponentName);
	VehicleTailLightMesh->SetCollisionProfileName(UCollisionProfile::Vehicle_ProfileName);
	//VehicleTailLightMesh->BodyInstance.bSimulatePhysics = true;
	//VehicleTailLightMesh->BodyInstance.bNotifyRigidBodyCollision = true;
	//VehicleTailLightMesh->BodyInstance.bUseCCD = true;
	//VehicleTailLightMesh->bBlendPhysics = true;
	//VehicleTailLightMesh->bGenerateOverlapEvents = true;
	VehicleTailLightMesh->SetupAttachment(RootComponent);
	VehicleTailLightMesh->ComponentTags.Add("TailLight");
	VehicleTailLightMesh->SetMasterPoseComponent(VehicleBaseMesh);










	RidersMovement = CreateDefaultSubobject<URiders_WVHMovComponent4W>(RidersMovementComponentName);
	RidersMovement->SetIsReplicated(true); // Enable replication by default
	RidersMovement->UpdatedComponent = RootComponent;

	FL_WheelMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FL_Wheel"));
	FL_WheelMesh->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	FL_WheelMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform, RidersMovement->WheelSetups[0].BoneName);
	FL_WheelMesh->ComponentTags.Add("FL_Wheel");

	FL_TireMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FL_Tire"));
	FL_TireMesh->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	FL_TireMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform, RidersMovement->WheelSetups[0].BoneName);
	FL_TireMesh->ComponentTags.Add("FL_Tire");

	FL_BrakePadMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FL_BrakePad"));
	FL_BrakePadMesh->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	FL_BrakePadMesh->SetRelativeRotation(FRotator(20.0f, 0.0f, 0.0f));
	FL_BrakePadMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform, RidersMovement->BrakeBones[0]);
	FL_BrakePadMesh->ComponentTags.Add("FL_BrakePad");


	FR_WheelMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FR_Wheel"));
	FR_WheelMesh->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	FR_WheelMesh->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
	FR_WheelMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform, RidersMovement->WheelSetups[1].BoneName);
	FR_WheelMesh->ComponentTags.Add("FR_Wheel");

	FR_TireMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FR_Tire"));
	FR_TireMesh->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	FR_TireMesh->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
	FR_TireMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform, RidersMovement->WheelSetups[1].BoneName);
	FR_TireMesh->ComponentTags.Add("FR_Tire");

	FR_BrakePadMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FR_BrakePad"));
	FR_BrakePadMesh->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	FR_BrakePadMesh->SetRelativeRotation(FRotator(160.0f, 180.0f, 0.0f));
	FR_BrakePadMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform, RidersMovement->BrakeBones[1]);
	FR_BrakePadMesh->ComponentTags.Add("FR_BrakePad");


	BL_WheelMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BL_Wheel"));
	BL_WheelMesh->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	BL_WheelMesh->SetRelativeScale3D(FVector(1.0f, 1.1f, 1.0f));
	BL_WheelMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform, RidersMovement->WheelSetups[2].BoneName);
	BL_WheelMesh->ComponentTags.Add("BL_Wheel");

	BL_TireMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BL_Tire"));
	BL_TireMesh->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	BL_TireMesh->SetRelativeScale3D(FVector(1.0f, 1.1f, 1.0f));
	BL_TireMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform, RidersMovement->WheelSetups[2].BoneName);
	BL_TireMesh->ComponentTags.Add("BL_Tire");

	BL_BrakePadMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BL_BrakePad"));
	BL_BrakePadMesh->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	BL_BrakePadMesh->SetRelativeScale3D(FVector(1.0f, 1.1f, 1.0f));
	BL_BrakePadMesh->SetRelativeRotation(FRotator(160.0f, 0.0f, 0.0f));
	BL_BrakePadMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform, RidersMovement->BrakeBones[2]);
	BL_BrakePadMesh->ComponentTags.Add("BL_BrakePad");

	BR_WheelMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BR_Wheel"));
	BR_WheelMesh->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	BR_WheelMesh->SetRelativeScale3D(FVector(1.0f, 1.1f, 1.0f));
	BR_WheelMesh->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
	BR_WheelMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform, RidersMovement->WheelSetups[3].BoneName);
	BR_WheelMesh->ComponentTags.Add("BR_Wheel");

	BR_TireMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BR_Tire"));
	BR_TireMesh->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	BR_TireMesh->SetRelativeScale3D(FVector(1.0f, 1.1f, 1.0f));
	BR_TireMesh->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
	BR_TireMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform, RidersMovement->WheelSetups[3].BoneName);
	BR_TireMesh->ComponentTags.Add("BR_Tire");

	BR_BrakePadMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BR_BrakePad"));
	BR_BrakePadMesh->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	BR_BrakePadMesh->SetRelativeScale3D(FVector(1.0f, 1.1f, 1.0f));
	BR_BrakePadMesh->SetRelativeRotation(FRotator(20.0f, 180.0f, 0.0f));
	BR_BrakePadMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform, RidersMovement->BrakeBones[3]);
	BR_BrakePadMesh->ComponentTags.Add("BR_BrakePad");




	PartComponents = CreateDefaultSubobject<UVehiclePartsComponents>(TEXT("PartComponents"));
	PartComponents->SetIsReplicated(true);


}

TArray<UStaticMeshComponent*> ARiders_WheeledVehicle::GetTireMeshes() const
{
	TArray<UStaticMeshComponent*> TempComponents;

	TempComponents.Add(FL_TireMesh);
	TempComponents.Add(FR_TireMesh);
	TempComponents.Add(BL_TireMesh);
	TempComponents.Add(BR_TireMesh);

	return TempComponents;
}

TArray<UStaticMeshComponent*> ARiders_WheeledVehicle::GetBrakePadMeshes() const
{
	TArray<UStaticMeshComponent*> TempComponents;

	TempComponents.Add(FL_BrakePadMesh);
	TempComponents.Add(FR_BrakePadMesh);
	TempComponents.Add(BL_BrakePadMesh);
	TempComponents.Add(BR_BrakePadMesh);

	return TempComponents;
}

void ARiders_WheeledVehicle::DisplayDebug(UCanvas* Canvas, const FDebugDisplayInfo& DebugDisplay, float& YL, float& YPos)
{
	static FName NAME_Vehicle = FName(TEXT("Vehicle"));

	Super::DisplayDebug(Canvas, DebugDisplay, YL, YPos);

	if (DebugDisplay.IsDisplayOn(NAME_Vehicle))
	{
		GetVehicleMovement()->DrawDebug(Canvas, YL, YPos);
	}
}


