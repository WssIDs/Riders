// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Custom/RidersSaveGameTypes.h"
#include "VehicleContent/Riders_FrontWheels.h"
#include "VehiclePartsComponents.generated.h"


USTRUCT(BlueprintType)
struct FBodyMaterialProperty
{
	GENERATED_BODY()

	/* Type Material */
	UPROPERTY(EditAnywhere, Category = "Riders Vehicle Settings", BlueprintReadWrite, SaveGame)
		EVehicleMaterialType TypeMaterial;

	/* Color */
	UPROPERTY(EditAnywhere, Category = "Riders Vehicle Settings", BlueprintReadWrite, SaveGame)
		FLinearColor Color;

	/* Material Slot Name */
	UPROPERTY(EditAnywhere, Category = "Riders Vehicle Settings", BlueprintReadWrite, SaveGame)
		FName MaterialSlotName;

	FBodyMaterialProperty()
	{
		Color = FLinearColor(0.0f, 0.0f, 0.0f, 1.0f);

		MaterialSlotName = "Default";
	}

};


USTRUCT(BlueprintType)
struct FWheelMaterialProp
{
	GENERATED_BODY()

	/* Color */
	UPROPERTY(EditAnywhere, Category = "Riders Vehicle Settings", BlueprintReadWrite, SaveGame)
		FLinearColor Color;

	/* Index Material (Deptecated) */
	UPROPERTY(EditAnywhere, Category = "Riders Vehicle Settings", BlueprintReadWrite, SaveGame)
		int32 MaterialIndex;

	/* Material Slot Name */
	UPROPERTY(EditAnywhere, Category = "Riders Vehicle Settings", BlueprintReadWrite, SaveGame)
		FName MaterialSlotName;

	FWheelMaterialProp()
	{
		Color = FLinearColor(0.0f, 0.0f, 0.0f, 1.0f);
		MaterialIndex = 0;
		MaterialSlotName = "Default";
	}

};


USTRUCT(BlueprintType)
struct FPartsData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = Basic, BlueprintReadWrite, SaveGame)
		int32 ID;

	UPROPERTY(EditAnywhere, Category = Basic, BlueprintReadWrite, SaveGame)
		int32 IDPart;

	UPROPERTY(EditAnywhere, Category = Basic, BlueprintReadWrite, SaveGame)
		FName PartName;

	UPROPERTY(EditAnywhere, Category = Basic, BlueprintReadWrite, SaveGame)
		USkeletalMesh* Mesh;

	/* Type Material */
	UPROPERTY(EditAnywhere, Category = "Riders Vehicle Settings", BlueprintReadWrite, SaveGame)
		EVehicleMaterialType TypeMaterial;

	/* Color */
	UPROPERTY(EditAnywhere, Category = "Riders Vehicle Settings", BlueprintReadWrite, SaveGame)
		FLinearColor Color;

	/* Material Slot Name */
	UPROPERTY(EditAnywhere, Category = "Riders Vehicle Settings", BlueprintReadWrite, SaveGame)
		FName MaterialSlotName;
};



//USTRUCT(BlueprintType)
//struct FPartsData
//{
//	GENERATED_USTRUCT_BODY();
//
//	UPROPERTY(EditAnywhere, Category = Basic, BlueprintReadWrite, SaveGame)
//		int32 ID;
//
//	UPROPERTY(EditAnywhere, Category = Basic, BlueprintReadWrite, SaveGame)
//		USkeletalMesh* Mesh;
//
//	UPROPERTY(EditAnywhere, Category = Basic, BlueprintReadWrite, SaveGame)
//		FBodyMaterialProp MaterialProperty;
//
//	FPartsData()
//	{
//		ID = 0;
//		Mesh = nullptr;
//		MaterialProperty.TypeMaterial = EVehicleMaterialType::Glossy;
//		MaterialProperty.Color = FLinearColor::Black;
//		MaterialProperty.MaterialSlotName = "Default";
//	}
//};

USTRUCT(BlueprintType)
struct FLightMaterials
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = Basic, BlueprintReadWrite, SaveGame)
	FName Name;

	UPROPERTY(EditAnywhere, Category = Basic, BlueprintReadWrite, SaveGame)
	UMaterialInstanceDynamic* Material;

	FLightMaterials()
	{
		Name = "Default";
		Material = nullptr;
	}
};

USTRUCT(BlueprintType)
struct FWheelPartsData
{
	GENERATED_BODY();

	UPROPERTY(EditAnywhere, Category = Basic, BlueprintReadWrite, SaveGame)
		int32 ID;

	/* Front Mesh */
	UPROPERTY(EditAnywhere, Category = Basic, BlueprintReadWrite, SaveGame)
		UStaticMesh* FrontMesh;

	/* RearMesh */
	UPROPERTY(EditAnywhere, Category = Basic, BlueprintReadWrite, SaveGame)
		UStaticMesh* RearMesh;

	/* Color */
	UPROPERTY(EditAnywhere, Category = "Riders Vehicle Settings", BlueprintReadWrite, SaveGame)
		FLinearColor Color;

	/* Material Slot Name */
	UPROPERTY(EditAnywhere, Category = "Riders Vehicle Settings", BlueprintReadWrite, SaveGame)
		FName MaterialSlotName;
};


UCLASS( ClassGroup=(Parts), meta=(BlueprintSpawnableComponent), HideCategories=(Sockets))
class RIDERS_API UVehiclePartsComponents : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UVehiclePartsComponents();


	UPROPERTY(EditAnywhere, SaveGame)
		FString TestVar;

	UFUNCTION(BlueprintCallable, Category = "Vehicle")
		void SetPartMaterial(USkeletalMeshComponent* PartComponent, FPartsData PartData);

		void SetPartMaterial(UStaticMeshComponent* PartComponent, FWheelPartsData PartData, UMaterialInterface* Material);

		UMaterialInstanceDynamic* InitPartMaterial(FPartsData PartData);

		UMaterialInstanceDynamic* InitPartMaterial(FWheelPartsData PartData, UMaterialInterface* Material);

		UFUNCTION(BlueprintCallable, Category = "Vehicle")
		virtual void UpdateVehicleMaterials();



		void UpdateBodyVehicleMaterial();

		void UpdateFrontBumperVehicleMaterial();

		void UpdateRearBumperVehicleMaterial();

		void UpdateHoodVehicleMaterial();

		void UpdateMirrorsVehicleMaterial();

		void UpdateRoofVehicleMaterial();

		void UpdateSpoilerVehicleMaterial();

		void UpdateWheelsVehicleMaterial();

		void UpdateBrakePadsVehicleMaterial();		
		
		UFUNCTION(BlueprintCallable, Category = "Vehicle")
		virtual void UpdateVehicleProperties();

		void UpdateBodyVehicleProperty();

		void UpdateFrontBumperVehicleProperty();

		void UpdateRearBumperVehicleProperty();

		void UpdateHoodVehicleProperty();

		void UpdateMirrorsVehicleProperty();

		void UpdateRoofVehicleProperty();

		void UpdateSpoilerVehicleProperty();

		void UpdateWheelsVehicleProperty();

		void UpdateBrakePadsVehicleProperty();


	/** The MyProperty */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game", SaveGame)
		TMap<FName,FPartsData> BodyPartsData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game", SaveGame)
		FWheelPartsData WheelPartsData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game", SaveGame)
		FWheelPartsData BrakePadPartsData;

	/** The MyProperty */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "-2.0", ClampMax = "2.0", UIMin = "-2.0", UIMax = "2.0"),AdvancedDisplay, SaveGame)
		float WheelOffset;

	/** The MyProperty */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "2.0"), AdvancedDisplay, SaveGame)
		float CamberWheel;

	/** The MyProperty */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "1.0", UIMax = "1.1"), AdvancedDisplay, SaveGame)
		float WheelSize;

	// Called when the game starts
	virtual void BeginPlay() override;

	/** Init color,material type for all components*/
	UFUNCTION(BlueprintCallable)
		void InitVehiclePartsMaterial(FLinearColor Color, EVehicleMaterialType MaterialType);

	/** Init color,material type for all components*/
	UFUNCTION(BlueprintCallable)
		FPartsData SetPartMaterialByName(FName Name, FLinearColor Color, EVehicleMaterialType MaterialType);

	/** Init color,material type for all components*/
	UFUNCTION(BlueprintCallable)
		FPartsData SetFrontBumperMaterial(FLinearColor Color, EVehicleMaterialType MaterialType);

	/** Init color,material type for all components*/
	UFUNCTION(BlueprintCallable)
		FPartsData SetRearBumperMaterial(FLinearColor Color, EVehicleMaterialType MaterialType);

	UFUNCTION(BlueprintCallable)
		void InitWheelPartsMaterial(FLinearColor Color);

	UFUNCTION(BlueprintCallable)
		void InitBrakePadPartsMaterial(FLinearColor Color);

	/** Init Mesg for Spoiler component*/
	UFUNCTION(BlueprintCallable)
		FPartsData SetSpoilerMesh(int32 IDPart, FName PartName, USkeletalMesh* Mesh);

	/** Init Mesg for FrontBumper component*/
	UFUNCTION(BlueprintCallable)
		FPartsData SetFrontBumperMesh(int32 IDPart, FName PartName, USkeletalMesh* Mesh);

	/** Init Mesh for Custom component*/
	UFUNCTION(BlueprintCallable)
		FPartsData SetCustomMesh(FName PartType, int32 IDPart, FName PartName, USkeletalMesh* Mesh);

	/** Init Material for Custom component*/
	UFUNCTION(BlueprintCallable)
		FPartsData SetCustomMeshMaterial(FName PartName, FLinearColor Color, EVehicleMaterialType MaterialType);

	/** Init Material for All components*/
	UFUNCTION(BlueprintCallable)
		FPartsData SetAllVehicleMaterial(FLinearColor Color, EVehicleMaterialType MaterialType);

	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override;

public:


	UPROPERTY(Category = "Materials", EditDefaultsOnly, EditFixedSize, SaveGame)
		TMap<EVehicleMaterialType, UMaterialInterface*> BodyMaterials;

	UPROPERTY(Category = "Materials", EditDefaultsOnly, AdvancedDisplay, SaveGame)
		UMaterialInterface* WheelMat;

	UPROPERTY(Category = "Materials", EditDefaultsOnly, AdvancedDisplay, SaveGame)
		UMaterialInterface* BrakePadMat;

	UPROPERTY(Category = "Materials", EditDefaultsOnly, BlueprintReadWrite, SaveGame)
		TMap<FName, FSLightMaterialProp> FrontLight;

	UPROPERTY(Category = "Materials", EditDefaultsOnly, BlueprintReadWrite, SaveGame)
		TArray<FSLightMaterialProp> RearLight;

	UPROPERTY(Category = "Materials", EditDefaultsOnly, BlueprintReadWrite, SaveGame)
		TMap<FName, FSLightMaterialProp> ReverseLight;

	TMap<FName, UMaterialInstanceDynamic*> FrontLightMaterials;

	//UPROPERTY(Category = "Materials", VisibleAnywhere, BlueprintReadWrite, SaveGame)
	TArray<FLightMaterials> RearLightMaterials;

	TMap<FName, UMaterialInstanceDynamic*> ReverseLightMaterials;


	UPROPERTY(Replicated, BlueprintReadWrite)
		UMaterialInstanceDynamic* BodyMaterial;

	UPROPERTY(Replicated, BlueprintReadWrite)
		UMaterialInstanceDynamic* MirrorsMaterial;

	UPROPERTY(Replicated, BlueprintReadWrite)
		UMaterialInstanceDynamic* HoodMaterial;

	UPROPERTY(Replicated, BlueprintReadWrite)
		UMaterialInstanceDynamic* RoofMaterial;

	UPROPERTY(Replicated, BlueprintReadWrite)
		UMaterialInstanceDynamic* FrontBumperMaterial;

	UPROPERTY(Replicated, BlueprintReadWrite)
		UMaterialInstanceDynamic* RearBumperMaterial;

	UPROPERTY(Replicated, BlueprintReadWrite)
		UMaterialInstanceDynamic* SpoilerMaterial;

	/*  Front Light Material */
	UPROPERTY(Replicated, BlueprintReadWrite)
		UMaterialInstanceDynamic* FrontLightMaterial;

	/* Rear Light Material Handbrake */
	UPROPERTY(Replicated, BlueprintReadWrite)
		UMaterialInstanceDynamic* RearLightMaterial;

	/* Reverse Light Material Reverse */
	UPROPERTY(Replicated, BlueprintReadWrite)
		UMaterialInstanceDynamic* RevLightMaterial;


	/*  Wheel Material */
	UPROPERTY(Replicated, BlueprintReadWrite)
		UMaterialInstanceDynamic* WheelMaterial;

	/*  BrakePad Material */
	UPROPERTY(Replicated, BlueprintReadWrite)
		UMaterialInstanceDynamic* BrakePadMaterial;

#if WITH_EDITOR

	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;

	virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedChainEvent) override;

#endif
	
};
