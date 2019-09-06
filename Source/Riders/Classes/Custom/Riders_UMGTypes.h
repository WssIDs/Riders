#pragma once

#include "Riders.h"
#include "SkeletalMeshTypes.h"
#include "Engine/DataTable.h"
#include "Riders_UMGTypes.generated.h"


UENUM(BlueprintType)
namespace EWorkShopMenuType
{
	enum Type
	{
		GeneralMenu,
		PreviewMenu,
		VisualsMenu,
		PerformanceMenu,
		QuitMenu,
		BuyMenu,
		FrontBumpersMenu,
		RearBumpersMenu,
		SideSkirtsMenu,
		SpoilersMenu,
		HoodsMenu,
		RoofScoopsMenu,
		HeadlightsMenu,
		TaillightsMenu,
		SideMirrorsMenu,
		ExhaustTipsMenu,
		RimsMenu,
		WideBodyKitsMenu,
		ColorPartsMenu,
		SelfPositioningVinylsMenu,
		PremadeLayoutsVinylsMenu,
		WindshieldVinylsMenu,
		RearWindowVinylsMenu,
		NeonMenu,
		WindowTintMenu,
		LightsMenu,
		NitrousPurgeMenu,
		SpinnersMenu,
		ColorPartsSubMenu,
	};
}


UENUM(BlueprintType)
enum class EItemType : uint8
{
	FrontBumper,
	RearBumper,
	SideSkirt,
	Spoiler,
	Hood,
	RoofScoop,
	Headlight,
	Taillight,
	SideMirror,
	ExhaustTip,
	Rim,
	Light,
	Spinner,
	ColorParts
};


USTRUCT(BlueprintType)
struct FModificationButton
{
	GENERATED_USTRUCT_BODY();

	/* ID item */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Modification Level")
		int32 ID;

	/* Type item */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Modification Level")
	EItemType ItemType;

	/* Name of button */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Modification Level")
		FName ButtonName;

	/** Cost */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Modification Level")
		int32 Cost;

	/** AddedToCart */
	UPROPERTY(BlueprintReadWrite, Category = "Modification Level")
		bool AddedToCart;

	/** Installed */
	UPROPERTY(BlueprintReadWrite, Category = "Modification Level")
		bool IsInstalled;

	/** Locked */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Modification Level")
		bool IsLocked;

	/** Locked Message */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Modification Level")
		FString LockedMessage;

	/** The MyProperty */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Modification Level")
		USkeletalMesh* ComponentObject;

	/** Camera Position */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Modification Level")
		FTransform CameraPos;

	FModificationButton()
	{
		ButtonName = "Default";
	}

};


USTRUCT(BlueprintType)
struct FSmallTunningPartsButton
{
	GENERATED_USTRUCT_BODY();

	/* Name of button */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Small Visuals")
		FName ButtonName;

	/** button icon */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Small Visuals")
		UTexture2D* ButtonIcon;

	/** Camera */
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Small Visuals")
	//	ACameraActor* Camera;

	/** Camera Transform */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Small Visuals")
		FTransform CameraPos;

	/** Modifications */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Modifications")
		TArray<FModificationButton> Modifications;

	FSmallTunningPartsButton()
	{
		ButtonName = "Default";
	}

};

USTRUCT(BlueprintType)
struct FColorModificationButton
{
	GENERATED_USTRUCT_BODY();

	/* Name of button */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Modification Level")
		FName ButtonName;

	/** Cost */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Modification Level")
		int32 Cost;

	/** Locked */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Modification Level")
		bool IsLocked;

	/** Locked Message */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Modification Level")
		FString LockedMessage;


	/** Camera */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color Parts")
		ACameraActor* Camera;

	/** Camera Transform */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Small Visuals")
		FTransform CameraPos;

	FColorModificationButton()
	{
		ButtonName = "Default";
	}

};


USTRUCT(BlueprintType)
struct FColorPartsButton
{
	GENERATED_USTRUCT_BODY();

	/* Name of button */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color Parts")
		FName ButtonName;

	/** button icon */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color Parts")
		UTexture2D* ButtonIcon;

	/** Modifications */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color Parts")
		TArray<FColorModificationButton> Parts;

	FColorPartsButton()
	{
		ButtonName = "Default";
	}

};



USTRUCT(BlueprintType)
struct FGeneralVisualTunningPartsButton
{
	GENERATED_USTRUCT_BODY();

	/* Name of button */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visuals")
		FName ButtonName;

	/** button icon */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visuals")
		UTexture2D* ButtonIcon;

	/** Front Bumpers */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SubCategoryVisuals")
		FSmallTunningPartsButton FrontBumpers;

	/** Rear Bumpers */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SubCategoryVisuals")
		FSmallTunningPartsButton RearBumpers;

	/** Side Skirts */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SubCategoryVisuals")
		FSmallTunningPartsButton SideSkirts;

	/** Spoilers */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SubCategoryVisuals")
		FSmallTunningPartsButton Spoilers;

	/** Hoods */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SubCategoryVisuals")
		FSmallTunningPartsButton Hoods;

	/** Roof Scoops */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SubCategoryVisuals")
		FSmallTunningPartsButton RoofScoops;

	/** HeadLights */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SubCategoryVisuals")
		FSmallTunningPartsButton Headlights;

	/** TailLights */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SubCategoryVisuals")
		FSmallTunningPartsButton Taillights;

	/** Side Mirrors */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SubCategoryVisuals")
		FSmallTunningPartsButton SideMirrors;

	/** Exhaust Tips */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SubCategoryVisuals")
		FSmallTunningPartsButton ExhaustTips;

	/** Rims */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SubCategoryVisuals")
		FSmallTunningPartsButton Rims;

	/** Wide Body Kits */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SubCategoryVisuals")
		FSmallTunningPartsButton WideBodyKits;

	/** Color Parts */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SubCategoryVisuals")
		FColorPartsButton ColorParts;

	/** Self Positioning Vinyls */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SubCategoryVisuals")
		FSmallTunningPartsButton SelfPositioningVinyls;

	/** Premade Layouts Vinyls */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SubCategoryVisuals")
		FSmallTunningPartsButton PremadeLayoutsVinyls;

	/** Windshield Vinyls */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SubCategoryVisuals")
		FSmallTunningPartsButton WindshieldVinyls;

	/** RearWindow Vinyls */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SubCategoryVisuals")
		FSmallTunningPartsButton RearWindowVinyls;

	/** Neon */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SubCategoryVisuals")
		FSmallTunningPartsButton Neon;

	/** Window Tint */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SubCategoryVisuals")
		FSmallTunningPartsButton WindowTint;

	/** Lights */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SubCategoryVisuals")
		FSmallTunningPartsButton Lights;

	/** Nitrous Purge */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SubCategoryVisuals")
		FSmallTunningPartsButton NitrousPurge;

	/** Spinners */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SubCategoryVisuals")
		FSmallTunningPartsButton Spinners;

	FGeneralVisualTunningPartsButton()
	{
		FrontBumpers.ButtonName = "Front Bumpers";
		RearBumpers.ButtonName = "Rear Bumpers";
		SideSkirts.ButtonName = "Side Skirts";
		Spoilers.ButtonName = "Spoilers";
		Hoods.ButtonName = "Hoods";
		RoofScoops.ButtonName = "Roof Scoops";
		Headlights.ButtonName = "Headlights";
		Taillights.ButtonName = "Taillight";
		SideMirrors.ButtonName = "Side Mirrors";
		ExhaustTips.ButtonName = "Exhaust Tips";
		Rims.ButtonName = "Rims";
		WideBodyKits.ButtonName = "Wide Body Kits";
		ColorParts.ButtonName = "Color Parts";
		SelfPositioningVinyls.ButtonName = "Self positioning Vinyls";
		PremadeLayoutsVinyls.ButtonName = "Premade Layouts Vinyls";
		WindshieldVinyls.ButtonName = "Windshield Vinyls";
		RearWindowVinyls.ButtonName = "Rear Window Vinyls";
		Neon.ButtonName = "Neon";
		WindowTint.ButtonName = "Window Tint";
		Lights.ButtonName = "Lights";
		NitrousPurge.ButtonName = "Nitrous Purge";
		Spinners.ButtonName = "Spinners";
	}

};


USTRUCT(BlueprintType)
struct FGeneralPerformanceTunningPartsButton
{
	GENERATED_USTRUCT_BODY();

	/* Name of button */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
		FName ButtonName;

	/** button icon */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
		UTexture2D* ButtonIcon;

	FGeneralPerformanceTunningPartsButton()
	{
	}

};


USTRUCT(BlueprintType)
struct FTunningParts
{
	GENERATED_USTRUCT_BODY();

	/* Visuals */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visuals")
		FGeneralVisualTunningPartsButton Visuals;

	/* Performance */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
		FGeneralPerformanceTunningPartsButton Performance;

	FTunningParts()
	{
		Visuals.ButtonName = "Visuals";
		Performance.ButtonName = "Performance";
	}

};

/** Button Structure */
USTRUCT(BlueprintType)
struct FButtonData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	FButtonData()
		: ID(0)
		, Caption(TEXT("Default"))
	{}

	/** ID Button */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Button)
	int32 ID;

	/** Button name */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Button)
	FString Caption;

	/** Icon */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Button)
	UTexture2D* Icon;

	/** Camera */
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Button)
	//	ACameraActor* Camera;

	/** Camera Transform */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Button)
		FTransform CameraPos;

	/** Modifications */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Button)
	TArray<FModificationButton> Parts;
};


