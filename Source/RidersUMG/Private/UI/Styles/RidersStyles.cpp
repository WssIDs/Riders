// Fill out your copyright notice in the Description page of Project Settings.

// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "RidersStyles.h"
#include "UI/SlateTypes/RidersSlateTypes.h"
#include "Engine/Engine.h"
#include "SlateBasics.h"
#include "SlateStyle.h"
#include "RidersUMG.h"


TSharedPtr<ISlateStyle> FRidersStyle::StylePtr = nullptr;


/* FSlateCoreStyle helper class
*****************************************************************************/

class FRidersCoreStyle
	: public FSlateStyleSet
{

public:
	FRidersCoreStyle(const FName& InStyleSetName)
		: FSlateStyleSet(InStyleSetName)

		// These are the colors that are updated by the user style customizations
		, DefaultForeground_LinearRef(MakeShareable(new FLinearColor(0.72f, 0.72f, 0.72f, 1.f)))
		, InvertedForeground_LinearRef(MakeShareable(new FLinearColor(0.0f, 0.0f, 0.0f)))
		, SelectorColor_LinearRef(MakeShareable(new FLinearColor(0.701f, 0.225f, 0.003f)))
		, SelectionColor_LinearRef(MakeShareable(new FLinearColor(0.728f, 0.364f, 0.003f)))
		, SelectionColor_Inactive_LinearRef(MakeShareable(new FLinearColor(0.25f, 0.25f, 0.25f)))
		, SelectionColor_Pressed_LinearRef(MakeShareable(new FLinearColor(0.701f, 0.225f, 0.003f)))
	{
	}

	static void SetColor(const TSharedRef<FLinearColor>& Source, const FLinearColor& Value)
	{
		Source->R = Value.R;
		Source->G = Value.G;
		Source->B = Value.B;
		Source->A = Value.A;
	}

	// These are the colors that are updated by the user style customizations
	const TSharedRef<FLinearColor> DefaultForeground_LinearRef;
	const TSharedRef<FLinearColor> InvertedForeground_LinearRef;
	const TSharedRef<FLinearColor> SelectorColor_LinearRef;
	const TSharedRef<FLinearColor> SelectionColor_LinearRef;
	const TSharedRef<FLinearColor> SelectionColor_Inactive_LinearRef;
	const TSharedRef<FLinearColor> SelectionColor_Pressed_LinearRef;
};


#define BOX_BRUSH( RelativePath, ... ) FSlateBoxBrush(Style->RootToContentDir(RelativePath, TEXT(".png")), __VA_ARGS__)
#define IMAGE_BRUSH( RelativePath, ... ) FSlateImageBrush(Style->RootToContentDir(RelativePath, TEXT(".png")), __VA_ARGS__)

TSharedPtr<ISlateStyle> CreateStyle()
{

	TSharedPtr<FSlateStyleSet> Style = MakeShareable(new FRidersCoreStyle("RidersStyle"));
	Style->SetContentRoot(FPaths::ProjectContentDir() / "UI");

	const FString CanaryPath = Style->RootToContentDir(TEXT("Common/Button"), TEXT(".png"));


	if (!FPaths::FileExists(CanaryPath))
	{
		return Style;
	}

	// RidersSlider defaults...
	{
		FRidersSliderStyle SliderStyle = FRidersSliderStyle()
			.SetBackgroundImage(BOX_BRUSH("Common/ProgressBar_Background", FMargin(5.f / 12.f)))
			.SetDisabledBackgroundImage(BOX_BRUSH("Common/ProgressBar_Background", FMargin(5.f / 12.f)))
			.SetFillImage(BOX_BRUSH("Common/ProgressBar_Fill", FMargin(5.f / 12.f), FLinearColor(1.0f, 0.22f, 0.0f)))
			.SetNormalThumbImage(IMAGE_BRUSH("Common/Button", FVector2D(4.0f, 40.0f)))
			.SetDisabledThumbImage(IMAGE_BRUSH("Common/Button_Disabled", FVector2D(4.0f, 40.0f)))
			.SetBarThickness(20.0f)
			.SetIndention(0.0f)
			.SetAngle(-90.0f);
		Style->Set("RidersSlider", SliderStyle);
	}

	return Style;
}

#undef IMAGE_BRUSH
#undef BOX_BRUSH


void FRidersStyle::Initialize()
{

	if (!StylePtr.IsValid())
	{
		StylePtr = CreateStyle();
		
		FSlateStyleRegistry::RegisterSlateStyle(*StylePtr);
	}
}

void FRidersStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StylePtr);
	ensure(StylePtr.IsUnique());
	StylePtr.Reset();
}

const ISlateStyle& FRidersStyle::Get()
{
	if (!StylePtr.IsValid())
	{
		StylePtr = CreateStyle();

		FSlateStyleRegistry::RegisterSlateStyle(*StylePtr);
	}

	return *StylePtr;
}



/////////////////////////  FNewUMGStyle /////////////////////////////////////


TSharedPtr< FSlateStyleSet > FRidersUMGStyle::UMGStyleInstance = nullptr;

void FRidersUMGStyle::Initialize()
{

	if (!UMGStyleInstance.IsValid())
	{
		UMGStyleInstance = Create();

		FSlateStyleRegistry::RegisterSlateStyle(*UMGStyleInstance.Get());
	}
}

void FRidersUMGStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*UMGStyleInstance.Get());
	ensure(UMGStyleInstance.IsUnique());
	UMGStyleInstance.Reset();
}

FName FRidersUMGStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("NewUMGStyle"));
	return StyleSetName;
}

#define IMAGE_BRUSH( RelativePath, ... ) FSlateImageBrush( Style->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#define BOX_BRUSH( RelativePath, ... ) FSlateBoxBrush( Style->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#define BORDER_BRUSH( RelativePath, ... ) FSlateBorderBrush( Style->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#define TTF_FONT( RelativePath, ... ) FSlateFontInfo( Style->RootToContentDir( RelativePath, TEXT(".ttf") ), __VA_ARGS__ )
#define OTF_FONT( RelativePath, ... ) FSlateFontInfo( Style->RootToContentDir( RelativePath, TEXT(".otf") ), __VA_ARGS__ )

const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);
const FVector2D Icon40x40(40.0f, 40.0f);

TSharedRef< FSlateStyleSet > FRidersUMGStyle::Create()
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("NewUMGStyle"));
	Style->SetContentRoot(FPaths::ProjectContentDir() / TEXT("UI/UMG"));

	Style->Set("ClassIcon.RidersSlider", new IMAGE_BRUSH(TEXT("RidersSlider"), Icon16x16));

	return Style;
}

#undef IMAGE_BRUSH
#undef BOX_BRUSH
#undef BORDER_BRUSH
#undef TTF_FONT
#undef OTF_FONT

void FRidersUMGStyle::ReloadTextures()
{
	FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
}

const ISlateStyle& FRidersUMGStyle::Get()
{
	return *UMGStyleInstance;
}
