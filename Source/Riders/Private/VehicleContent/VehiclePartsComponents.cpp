// Fill out your copyright notice in the Description page of Project Settings.
#include "Riders/Classes/VehicleContent/VehiclePartsComponents.h"
#include "Pawns/Vehicles/Riders_Vehicle.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
//#include "Riders.h"


// Sets default values for this component's properties
UVehiclePartsComponents::UVehiclePartsComponents()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	//bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...


	BodyMaterials.Add(EVehicleMaterialType::Glossy);
	BodyMaterials.Add(EVehicleMaterialType::Metallic);
	BodyMaterials.Add(EVehicleMaterialType::Matted);
	BodyMaterials.Add(EVehicleMaterialType::TwoColors);
	BodyMaterials.Add(EVehicleMaterialType::Carbon);


}


void UVehiclePartsComponents::SetPartMaterial(USkeletalMeshComponent* PartComponent, FPartsData PartData)
{
	UMaterialInstanceDynamic* TempMaterial = nullptr;

	if (PartComponent)
	{
		if (BodyMaterials.Num() > 0)
		{
			//EVehicleMaterialType Type = PartMaterialProperty.TypeMaterial;

			TempMaterial = UMaterialInstanceDynamic::Create(*BodyMaterials.Find(PartData.TypeMaterial),this);

			PartComponent->SetMaterialByName(PartData.MaterialSlotName, TempMaterial);

			TempMaterial->SetVectorParameterValue("Color", PartData.Color);
		}
	}
}

void UVehiclePartsComponents::SetPartMaterial(UStaticMeshComponent * PartComponent, FWheelPartsData PartData, UMaterialInterface* Material)
{
	UMaterialInstanceDynamic* TempMaterial = nullptr;

	if (PartComponent)
	{
		if (Material)
		{
			//ARiders_Vehicle* Owner = Cast<ARiders_Vehicle>(GetOwner());

			TempMaterial = UMaterialInstanceDynamic::Create(Material, this);

			PartComponent->SetMaterialByName(PartData.MaterialSlotName, TempMaterial);

			TempMaterial->SetVectorParameterValue("Color", PartData.Color);
		}
	}
}

UMaterialInstanceDynamic * UVehiclePartsComponents::InitPartMaterial(FPartsData PartData)
{
	UMaterialInstanceDynamic* TempMaterial = nullptr;

	if (BodyMaterials.Num() > 0)
	{
		return UMaterialInstanceDynamic::Create(*BodyMaterials.Find(PartData.TypeMaterial), this);
	}

	return nullptr;
}

UMaterialInstanceDynamic * UVehiclePartsComponents::InitPartMaterial(FWheelPartsData PartData, UMaterialInterface* Material)
{
	if (Material)
	{
		return UMaterialInstanceDynamic::Create(Material, this);
	}

	return nullptr;
}

void UVehiclePartsComponents::UpdateVehicleMaterials()
{

	//ARiders_Vehicle* Owner = Cast<ARiders_Vehicle>(GetOwner());
	
	UpdateBodyVehicleMaterial();
	UpdateFrontBumperVehicleMaterial();
	UpdateRearBumperVehicleMaterial();
	UpdateHoodVehicleMaterial();
	UpdateMirrorsVehicleMaterial();
	UpdateRoofVehicleMaterial();
	UpdateSpoilerVehicleMaterial();

	UpdateWheelsVehicleMaterial();
	UpdateBrakePadsVehicleMaterial();

}

void UVehiclePartsComponents::UpdateBodyVehicleMaterial()
{	
	ARiders_Vehicle* Owner = Cast<ARiders_Vehicle>(GetOwner());

	if (Owner->GetBodyMesh()->SkeletalMesh)
	{
		FPartsData BodyData = *BodyPartsData.Find(Owner->GetBodyMesh()->ComponentTags[0]);

		Owner->InBodyColor = BodyData.Color;

		BodyMaterial = InitPartMaterial(BodyData);

		if (BodyMaterial)
		{
			Owner->GetBodyMesh()->SetMaterialByName(BodyData.MaterialSlotName, BodyMaterial);

			BodyMaterial->SetVectorParameterValue("Color", BodyData.Color);
		}
	}
}

void UVehiclePartsComponents::UpdateFrontBumperVehicleMaterial()
{
	ARiders_Vehicle* Owner = Cast<ARiders_Vehicle>(GetOwner());

	if (Owner->GetFrontBumperMesh()->SkeletalMesh)
	{
		FPartsData FrontBumperData = *BodyPartsData.Find(Owner->GetFrontBumperMesh()->ComponentTags[0]);

		FrontBumperMaterial = InitPartMaterial(FrontBumperData);

		if (FrontBumperMaterial)
		{
			Owner->GetFrontBumperMesh()->SetMaterialByName(FrontBumperData.MaterialSlotName, FrontBumperMaterial);

			FrontBumperMaterial->SetVectorParameterValue("Color", FrontBumperData.Color);
		}
	}

}

void UVehiclePartsComponents::UpdateRearBumperVehicleMaterial()
{
	ARiders_Vehicle* Owner = Cast<ARiders_Vehicle>(GetOwner());

	if (Owner->GetRearBumperMesh()->SkeletalMesh)
	{
		FPartsData RearBumperData = *BodyPartsData.Find(Owner->GetRearBumperMesh()->ComponentTags[0]);

		RearBumperMaterial = InitPartMaterial(RearBumperData);

		if (RearBumperMaterial)
		{
			Owner->GetRearBumperMesh()->SetMaterialByName(RearBumperData.MaterialSlotName, RearBumperMaterial);

			RearBumperMaterial->SetVectorParameterValue("Color", RearBumperData.Color);
		}
	}
}

void UVehiclePartsComponents::UpdateHoodVehicleMaterial()
{
	ARiders_Vehicle* Owner = Cast<ARiders_Vehicle>(GetOwner());

	if (Owner->GetHoodMesh()->SkeletalMesh)
	{
		FPartsData HoodData = *BodyPartsData.Find(Owner->GetHoodMesh()->ComponentTags[0]);

		HoodMaterial = InitPartMaterial(HoodData);

		if (HoodMaterial)
		{
			Owner->GetHoodMesh()->SetMaterialByName(HoodData.MaterialSlotName, HoodMaterial);

			HoodMaterial->SetVectorParameterValue("Color", HoodData.Color);
		}
	}
}

void UVehiclePartsComponents::UpdateMirrorsVehicleMaterial()
{
	ARiders_Vehicle* Owner = Cast<ARiders_Vehicle>(GetOwner());

if (Owner->GetMirrorsMesh()->SkeletalMesh)
	{
		FPartsData MirrorsData = *BodyPartsData.Find(Owner->GetMirrorsMesh()->ComponentTags[0]);
		MirrorsMaterial = InitPartMaterial(MirrorsData);

		if (MirrorsMaterial)
		{
			Owner->GetMirrorsMesh()->SetMaterialByName(MirrorsData.MaterialSlotName, MirrorsMaterial);

			MirrorsMaterial->SetVectorParameterValue("Color", MirrorsData.Color);
		}
	}
}

void UVehiclePartsComponents::UpdateRoofVehicleMaterial()
{
	ARiders_Vehicle* Owner = Cast<ARiders_Vehicle>(GetOwner());

	if (Owner->GetRoofMesh()->SkeletalMesh)
	{
		FPartsData RoofData = *BodyPartsData.Find(Owner->GetRoofMesh()->ComponentTags[0]);

		RoofMaterial = InitPartMaterial(RoofData);

		if (RoofMaterial)
		{
			Owner->GetRoofMesh()->SetMaterialByName(RoofData.MaterialSlotName, RoofMaterial);

			RoofMaterial->SetVectorParameterValue("Color", RoofData.Color);
		}
	}
}

void UVehiclePartsComponents::UpdateSpoilerVehicleMaterial()
{
	ARiders_Vehicle* Owner = Cast<ARiders_Vehicle>(GetOwner());

	if (Owner->GetSpoilerMesh()->SkeletalMesh)
	{
		FPartsData SpoilerData = *BodyPartsData.Find(Owner->GetSpoilerMesh()->ComponentTags[0]);

		SpoilerMaterial = InitPartMaterial(SpoilerData);

		if (SpoilerMaterial)
		{
			Owner->GetSpoilerMesh()->SetMaterialByName(SpoilerData.MaterialSlotName, SpoilerMaterial);

			SpoilerMaterial->SetVectorParameterValue("Color", SpoilerData.Color);
		}
	}
}

void UVehiclePartsComponents::UpdateWheelsVehicleMaterial()
{
	ARiders_Vehicle* Owner = Cast<ARiders_Vehicle>(GetOwner());

	if (Owner->GetWheelMeshes().Num() > 0)
	{
		FWheelPartsData WheelData = WheelPartsData;

		WheelMaterial = InitPartMaterial(WheelData, WheelMat);

		TArray<UStaticMeshComponent*> Wheels = Owner->GetWheelMeshes();

		for (UStaticMeshComponent* Item : Wheels)
		{
			if (WheelMaterial)
			{
				Item->SetMaterialByName(WheelData.MaterialSlotName, WheelMaterial);

				WheelMaterial->SetVectorParameterValue("Color", WheelData.Color);
			}
		}
	}
}

void UVehiclePartsComponents::UpdateBrakePadsVehicleMaterial()
{
	ARiders_Vehicle* Owner = Cast<ARiders_Vehicle>(GetOwner());

	if (Owner->GetBrakePadMeshes().Num() > 0)
	{
		FWheelPartsData BrakePadData = BrakePadPartsData;

		BrakePadMaterial = InitPartMaterial(BrakePadData, BrakePadMat);

		TArray<UStaticMeshComponent*> BrakePads = Owner->GetBrakePadMeshes();

		for (UStaticMeshComponent* Item : BrakePads)
		{
			if (BrakePadMaterial)
			{
				Item->SetMaterialByName(BrakePadData.MaterialSlotName, BrakePadMaterial);

				BrakePadMaterial->SetVectorParameterValue("Color", BrakePadData.Color);
			}
		}
	}
}


void UVehiclePartsComponents::UpdateVehicleProperties()
{

	UpdateBodyVehicleProperty();
	UpdateFrontBumperVehicleProperty();
	UpdateRearBumperVehicleProperty();
	UpdateHoodVehicleProperty();
	UpdateMirrorsVehicleProperty();
	UpdateRoofVehicleProperty();
	UpdateSpoilerVehicleProperty();

	UpdateWheelsVehicleProperty();
	UpdateBrakePadsVehicleProperty();

}



void UVehiclePartsComponents::UpdateBodyVehicleProperty()
{
	ARiders_Vehicle* Owner = Cast<ARiders_Vehicle>(GetOwner());

	///////// BODY

	if (BodyPartsData.Find(Owner->GetBodyMesh()->ComponentTags[0]) != nullptr)
	{
		Owner->GetBodyMesh()->SetSkeletalMesh(BodyPartsData.Find(Owner->GetBodyMesh()->ComponentTags[0])->Mesh);

		UE_LOG(VehicleLog, Warning, TEXT("SetSkeletalMesh Body"));

		if (Owner->GetBodyMesh()->SkeletalMesh != nullptr)
		{
			FPartsData BodyData = *BodyPartsData.Find(Owner->GetBodyMesh()->ComponentTags[0]);

			Owner->InBodyColor = BodyData.Color;
			BodyMaterial = InitPartMaterial(BodyData);

			UE_LOG(VehicleLog, Warning, TEXT("InitMaterial Body"));

			if (BodyMaterial)
			{
				Owner->GetBodyMesh()->SetMaterialByName(BodyData.MaterialSlotName, BodyMaterial);
				BodyMaterial->SetVectorParameterValue("Color", BodyData.Color);

				UE_LOG(VehicleLog, Warning, TEXT("SetAndChangeMaterial Body"));
			}
		}
	}
}

void UVehiclePartsComponents::UpdateFrontBumperVehicleProperty()
{
	ARiders_Vehicle* Owner = Cast<ARiders_Vehicle>(GetOwner());

	if (BodyPartsData.Find(Owner->GetFrontBumperMesh()->ComponentTags[0]) != nullptr)
	{
		Owner->GetFrontBumperMesh()->SetSkeletalMesh(BodyPartsData.Find(Owner->GetFrontBumperMesh()->ComponentTags[0])->Mesh);

		UE_LOG(VehicleLog, Warning, TEXT("SetSkeletalMesh FrontBumper"));

		if (Owner->GetFrontBumperMesh()->SkeletalMesh != nullptr)
		{
			FPartsData FrontBumperData = *BodyPartsData.Find(Owner->GetFrontBumperMesh()->ComponentTags[0]);

			FrontBumperMaterial = InitPartMaterial(FrontBumperData);

			UE_LOG(VehicleLog, Warning, TEXT("InitMaterial FrontBumper"));

			if (FrontBumperMaterial)
			{
				Owner->GetFrontBumperMesh()->SetMaterialByName(FrontBumperData.MaterialSlotName, FrontBumperMaterial);
				FrontBumperMaterial->SetVectorParameterValue("Color", FrontBumperData.Color);

				UE_LOG(VehicleLog, Warning, TEXT("SetAndChangeMaterial FrontBumper"));
			}
		}
	}
}

void UVehiclePartsComponents::UpdateRearBumperVehicleProperty()
{
	ARiders_Vehicle* Owner = Cast<ARiders_Vehicle>(GetOwner());

	if (BodyPartsData.Find(Owner->GetRearBumperMesh()->ComponentTags[0]) != nullptr)
	{
		Owner->GetRearBumperMesh()->SetSkeletalMesh(BodyPartsData.Find(Owner->GetRearBumperMesh()->ComponentTags[0])->Mesh);

		UE_LOG(VehicleLog, Warning, TEXT("SetSkeletalMesh RearBumper"));

		if (Owner->GetRearBumperMesh()->SkeletalMesh != nullptr)
		{
			FPartsData RearBumperData = *BodyPartsData.Find(Owner->GetRearBumperMesh()->ComponentTags[0]);

			RearBumperMaterial = InitPartMaterial(RearBumperData);

			UE_LOG(VehicleLog, Warning, TEXT("InitMaterial RearBumper"));

			if (RearBumperMaterial)
			{
				Owner->GetRearBumperMesh()->SetMaterialByName(RearBumperData.MaterialSlotName, RearBumperMaterial);
				RearBumperMaterial->SetVectorParameterValue("Color", RearBumperData.Color);

				UE_LOG(VehicleLog, Warning, TEXT("SetAndChangeMaterial RearBumper"));
			}
		}
	}
}

void UVehiclePartsComponents::UpdateHoodVehicleProperty()
{
	ARiders_Vehicle* Owner = Cast<ARiders_Vehicle>(GetOwner());

	if (BodyPartsData.Find(Owner->GetHoodMesh()->ComponentTags[0]) != nullptr)
	{
		Owner->GetHoodMesh()->SetSkeletalMesh(BodyPartsData.Find(Owner->GetHoodMesh()->ComponentTags[0])->Mesh);

		UE_LOG(VehicleLog, Warning, TEXT("SetSkeletalMesh Hood"));

		if (Owner->GetHoodMesh()->SkeletalMesh != nullptr)
		{
			FPartsData HoodData = *BodyPartsData.Find(Owner->GetHoodMesh()->ComponentTags[0]);

			BodyMaterial = InitPartMaterial(HoodData);

			UE_LOG(VehicleLog, Warning, TEXT("InitMaterial Hood"));

			if (HoodMaterial)
			{
				Owner->GetHoodMesh()->SetMaterialByName(HoodData.MaterialSlotName, HoodMaterial);
				HoodMaterial->SetVectorParameterValue("Color", HoodData.Color);

				UE_LOG(VehicleLog, Warning, TEXT("SetAndChangeMaterial Hood"));
			}
		}
	}
}

void UVehiclePartsComponents::UpdateMirrorsVehicleProperty()
{
	ARiders_Vehicle* Owner = Cast<ARiders_Vehicle>(GetOwner());

	if (BodyPartsData.Find(Owner->GetMirrorsMesh()->ComponentTags[0]) != nullptr)
	{
		Owner->GetMirrorsMesh()->SetSkeletalMesh(BodyPartsData.Find(Owner->GetMirrorsMesh()->ComponentTags[0])->Mesh);

		UE_LOG(VehicleLog, Warning, TEXT("SetSkeletalMesh Mirrors"));

		if (Owner->GetMirrorsMesh()->SkeletalMesh != nullptr)
		{
			FPartsData MirrorsData = *BodyPartsData.Find(Owner->GetMirrorsMesh()->ComponentTags[0]);

			MirrorsMaterial = InitPartMaterial(MirrorsData);

			UE_LOG(VehicleLog, Warning, TEXT("InitMaterial Mirrors"));

			if (MirrorsMaterial)
			{
				Owner->GetMirrorsMesh()->SetMaterialByName(MirrorsData.MaterialSlotName, MirrorsMaterial);
				MirrorsMaterial->SetVectorParameterValue("Color", MirrorsData.Color);

				UE_LOG(VehicleLog, Warning, TEXT("SetAndChangeMaterial Mirrors"));
			}
		}
	}
}

void UVehiclePartsComponents::UpdateRoofVehicleProperty()
{
	ARiders_Vehicle* Owner = Cast<ARiders_Vehicle>(GetOwner());

	if (BodyPartsData.Find(Owner->GetRoofMesh()->ComponentTags[0]) != nullptr)
	{
		Owner->GetRoofMesh()->SetSkeletalMesh(BodyPartsData.Find(Owner->GetRoofMesh()->ComponentTags[0])->Mesh);

		UE_LOG(VehicleLog, Warning, TEXT("SetSkeletalMesh Roof"));

		if (Owner->GetRoofMesh()->SkeletalMesh != nullptr)
		{
			FPartsData RoofData = *BodyPartsData.Find(Owner->GetRoofMesh()->ComponentTags[0]);

			RoofMaterial = InitPartMaterial(RoofData);

			UE_LOG(VehicleLog, Warning, TEXT("InitMaterial Roof"));

			if (RoofMaterial)
			{
				Owner->GetRoofMesh()->SetMaterialByName(RoofData.MaterialSlotName, RoofMaterial);
				RoofMaterial->SetVectorParameterValue("Color", RoofData.Color);

				UE_LOG(VehicleLog, Warning, TEXT("SetAndChangeMaterial Roof"));
			}
		}
	}
}

void UVehiclePartsComponents::UpdateSpoilerVehicleProperty()
{
	ARiders_Vehicle* Owner = Cast<ARiders_Vehicle>(GetOwner());

	if (BodyPartsData.Find(Owner->GetSpoilerMesh()->ComponentTags[0]) != nullptr)
	{
		Owner->GetSpoilerMesh()->SetSkeletalMesh(BodyPartsData.Find(Owner->GetSpoilerMesh()->ComponentTags[0])->Mesh);

		UE_LOG(VehicleLog, Warning, TEXT("SetSkeletalMesh Spoiler"));

		if (Owner->GetSpoilerMesh()->SkeletalMesh != nullptr)
		{
			FPartsData SpoilerData = *BodyPartsData.Find(Owner->GetSpoilerMesh()->ComponentTags[0]);

			SpoilerMaterial = InitPartMaterial(SpoilerData);

			UE_LOG(VehicleLog, Warning, TEXT("InitMaterial Spoiler"));

			if (SpoilerMaterial)
			{
				Owner->GetSpoilerMesh()->SetMaterialByName(SpoilerData.MaterialSlotName, SpoilerMaterial);
				SpoilerMaterial->SetVectorParameterValue("Color", SpoilerData.Color);

				UE_LOG(VehicleLog, Warning, TEXT("SetAndChangeMaterial Spoiler"));
			}
		}
	}
}

void UVehiclePartsComponents::UpdateWheelsVehicleProperty()
{
	ARiders_Vehicle* Owner = Cast<ARiders_Vehicle>(GetOwner());

	if (Owner->GetWheelMeshes().Num() > 0)
	{
		FWheelPartsData WheelData = WheelPartsData;

		WheelMaterial = InitPartMaterial(WheelData, WheelMat);

		UE_LOG(VehicleLog, Warning, TEXT("InitMaterial Wheel"));

		TArray<UStaticMeshComponent*> Wheels = Owner->GetWheelMeshes();

		for (UStaticMeshComponent* Item : Wheels)
		{
			Item->SetStaticMesh(WheelPartsData.FrontMesh);

			UE_LOG(VehicleLog, Warning, TEXT("SetSkeletalMesh Wheel %s"), *Item->GetName());

			if (Item->GetStaticMesh() != nullptr)
			{
				if (WheelMaterial)
				{
					Item->SetMaterialByName(WheelData.MaterialSlotName, WheelMaterial);
					UE_LOG(VehicleLog, Warning, TEXT("SetMaterialMesh Wheel %s"), *Item->GetName());
					WheelMaterial->SetVectorParameterValue("Color", WheelData.Color);
				}
			}
		}
	}
}

void UVehiclePartsComponents::UpdateBrakePadsVehicleProperty()
{
	ARiders_Vehicle* Owner = Cast<ARiders_Vehicle>(GetOwner());

	if (Owner->GetBrakePadMeshes().Num() > 0)
	{
		FWheelPartsData BrakePadData = BrakePadPartsData;

		BrakePadMaterial = InitPartMaterial(BrakePadData, BrakePadMat);
		UE_LOG(VehicleLog, Warning, TEXT("InitMaterial Brakepads"));

		TArray<UStaticMeshComponent*> BrakePads = Owner->GetBrakePadMeshes();

		for (UStaticMeshComponent* Item : BrakePads)
		{
			Item->SetStaticMesh(BrakePadPartsData.FrontMesh);
			UE_LOG(VehicleLog, Warning, TEXT("SetSkeletalMesh Brakepad %s"), *Item->GetName());

			if (Item->GetStaticMesh() != nullptr)
			{
				if (BrakePadMaterial)
				{
					Item->SetMaterialByName(BrakePadData.MaterialSlotName, BrakePadMaterial);
					UE_LOG(VehicleLog, Warning, TEXT("SetMaterialMesh Brakepad %s"), *Item->GetName());
					BrakePadMaterial->SetVectorParameterValue("Color", BrakePadData.Color);
				}
			}
		}
	}
}

// Called when the game starts
void UVehiclePartsComponents::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UVehiclePartsComponents::InitVehiclePartsMaterial(FLinearColor Color, EVehicleMaterialType MaterialType)
{
	ARiders_Vehicle* Owner = Cast<ARiders_Vehicle>(GetOwner());

	FPartsData Data;
	Data.TypeMaterial = MaterialType;
	Data.Color = Color;

	for (auto & Item : BodyPartsData)
	{
		UE_LOG(VehicleLog, Log, TEXT("%s - componentname"), *Item.Key.ToString());

		Data.MaterialSlotName = Item.Value.MaterialSlotName;

		for (auto & Component : Owner->GetComponentsByTag(USkeletalMeshComponent::StaticClass(), Item.Key))
		{
			SetPartMaterial((USkeletalMeshComponent*)Component, Data);		
			
			UE_LOG(VehicleLog, Log, TEXT("%s - getting component name"), *Component->GetName());
		}
	}
}

FPartsData UVehiclePartsComponents::SetPartMaterialByName(FName Name,FLinearColor Color, EVehicleMaterialType MaterialType)
{
	ARiders_Vehicle* Owner = Cast<ARiders_Vehicle>(GetOwner());
	
	FPartsData MaterialData;

	MaterialData.Color = Color;
	MaterialData.TypeMaterial = MaterialType;
	MaterialData.MaterialSlotName = BodyPartsData.Find(Name)->MaterialSlotName;

	for (auto Component : Owner->GetComponentsByTag(USkeletalMeshComponent::StaticClass(), Name))
	{
		SetPartMaterial((USkeletalMeshComponent*)Component, MaterialData);
		return MaterialData;
	}

	return FPartsData();
}

FPartsData UVehiclePartsComponents::SetFrontBumperMaterial(FLinearColor Color, EVehicleMaterialType MaterialType)
{
	return FPartsData();
}

FPartsData UVehiclePartsComponents::SetRearBumperMaterial(FLinearColor Color, EVehicleMaterialType MaterialType)
{
	return FPartsData();
}

void UVehiclePartsComponents::InitWheelPartsMaterial(FLinearColor Color)
{
	ARiders_Vehicle* Owner = Cast<ARiders_Vehicle>(GetOwner());

	FWheelPartsData Data;
	Data.Color = Color;

	Data.MaterialSlotName = WheelPartsData.MaterialSlotName;

	TArray<UStaticMeshComponent*> Wheels = Owner->GetWheelMeshes();

	for (auto & Component : Wheels)
	{
		SetPartMaterial((UStaticMeshComponent*)Component, Data, WheelMat);

		UE_LOG(VehicleLog, Log, TEXT("%s - getting component name"), *Component->GetName());
	}
}

void UVehiclePartsComponents::InitBrakePadPartsMaterial(FLinearColor Color)
{
	ARiders_Vehicle* Owner = Cast<ARiders_Vehicle>(GetOwner());

	FWheelPartsData Data;
	Data.Color = Color;

	Data.MaterialSlotName = BrakePadPartsData.MaterialSlotName;
	
	TArray<UStaticMeshComponent*> BrakePads = Owner->GetBrakePadMeshes();

	for (auto & Component : BrakePads)
	{
		SetPartMaterial((UStaticMeshComponent*)Component, Data, BrakePadMat);
	
		UE_LOG(VehicleLog, Log, TEXT("%s - getting component name"), *Component->GetName());
	}

}

FPartsData UVehiclePartsComponents::SetSpoilerMesh(int32 IDPart, FName PartName, USkeletalMesh* Mesh)
{
	//ARiders_Vehicle* Owner = Cast<ARiders_Vehicle>(GetOwner());

	FPartsData* SpoilerData = BodyPartsData.Find("Spoiler");

	SpoilerData->Mesh = Mesh;
	SpoilerData->IDPart = IDPart;
	SpoilerData->PartName = PartName;

	//FPartsData MaterialData;


	//MaterialData.Color = Color;
	//MaterialData.TypeMaterial = MaterialType;
	//MaterialData.MaterialSlotName = BodyPartsData.Find(Name)->MaterialSlotName;

	//for (auto Component : Owner->GetComponentsByTag(USkeletalMeshComponent::StaticClass(), Name))
	//{
	//	SetPartMaterial((USkeletalMeshComponent*)Component, MaterialData);
	//	return MaterialData;
	//}

	return FPartsData();
}

FPartsData UVehiclePartsComponents::SetFrontBumperMesh(int32 IDPart, FName PartName, USkeletalMesh* Mesh)
{
	FPartsData* FrontBumperData = BodyPartsData.Find("FrontBumper");

	FrontBumperData->Mesh = Mesh;
	FrontBumperData->IDPart = IDPart;
	FrontBumperData->PartName = PartName;


	return FPartsData();
}

FPartsData UVehiclePartsComponents::SetCustomMesh(FName PartType, int32 IDPart, FName PartName, USkeletalMesh* Mesh)
{
	FPartsData* CustomData = BodyPartsData.Find(PartType);

	CustomData->Mesh = Mesh;
	CustomData->IDPart = IDPart;
	CustomData->PartName = PartName;

	return FPartsData();
}

FPartsData UVehiclePartsComponents::SetCustomMeshMaterial(FName PartName, FLinearColor Color, EVehicleMaterialType MaterialType)
{
	FPartsData* CustomData = BodyPartsData.Find(PartName);
	CustomData->Color = Color;
	CustomData->TypeMaterial = MaterialType;

	ARiders_Vehicle* Owner = Cast<ARiders_Vehicle>(GetOwner());

	for (auto Component : Owner->GetComponentsByTag(USkeletalMeshComponent::StaticClass(), PartName))
	{
		SetPartMaterial((USkeletalMeshComponent*)Component, *CustomData);
	}

	return FPartsData();
}

FPartsData UVehiclePartsComponents::SetAllVehicleMaterial(FLinearColor Color, EVehicleMaterialType MaterialType)
{
	ARiders_Vehicle* Owner = Cast<ARiders_Vehicle>(GetOwner());

	for (auto& Part : BodyPartsData)
	{

		Part.Value.Color = Color;
		Part.Value.TypeMaterial = MaterialType;

		for (auto Component : Owner->GetComponentsByTag(USkeletalMeshComponent::StaticClass(), Part.Key))
		{
			SetPartMaterial((USkeletalMeshComponent*)Component, Part.Value);
		}
	}

	return FPartsData();
}

// Called every frame
void UVehiclePartsComponents::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

void UVehiclePartsComponents::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

#if WITH_EDITOR


void UVehiclePartsComponents::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
}

void UVehiclePartsComponents::PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedChainEvent)
{
	Super::PostEditChangeChainProperty(PropertyChangedChainEvent);
}

#endif

