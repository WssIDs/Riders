// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "UObject/Object.h"
#include "UObject/Class.h"
#include "Styling/SlateColor.h"
#include "Fonts/CompositeFont.h"
#include "Fonts/SlateFontInfo.h"
#include "Layout/Margin.h"
#include "Sound/SlateSound.h"
#include "Styling/SlateBrush.h"
#include "Styling/SlateWidgetStyle.h"
#include "RidersSlateTypes.generated.h"


/**
* Represents the appearance of an SSlider
*/
USTRUCT(BlueprintType)
struct RIDERSUMG_API FRidersSliderStyle : public FSlateWidgetStyle
{
	GENERATED_USTRUCT_BODY()

		FRidersSliderStyle();

	virtual ~FRidersSliderStyle() {}

	virtual void GetResources(TArray< const FSlateBrush* >& OutBrushes) const override;

	static const FName TypeName;
	virtual const FName GetTypeName() const override { return TypeName; };

	static const FRidersSliderStyle& GetDefault();

	/** Background image to use for the progress bar */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)
		FSlateBrush BackgroundImage;
	FRidersSliderStyle& SetBackgroundImage(const FSlateBrush& InBackgroundImage) { BackgroundImage = InBackgroundImage; return *this; }

	/** Background image to use for the progress bar */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)
		FSlateBrush DisabledBackgroundImage;
	FRidersSliderStyle& SetDisabledBackgroundImage(const FSlateBrush& InDisabledBackgroundImage) { DisabledBackgroundImage = InDisabledBackgroundImage; return *this; }

	/** Foreground image to use for the progress bar */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)
		FSlateBrush FillImage;
	FRidersSliderStyle& SetFillImage(const FSlateBrush& InFillImage) { FillImage = InFillImage; return *this; }

	/** Image to use when the slider thumb is in its normal state */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)
		FSlateBrush NormalThumbImage;
	FRidersSliderStyle& SetNormalThumbImage(const FSlateBrush& InNormalThumbImage) { NormalThumbImage = InNormalThumbImage; return *this; }

	/** Image to use when the slider thumb is in its disabled state */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)
		FSlateBrush DisabledThumbImage;
	FRidersSliderStyle& SetDisabledThumbImage(const FSlateBrush& InDisabledThumbImage) { DisabledThumbImage = InDisabledThumbImage; return *this; }

	/** SliderBar height */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)
		float BarThickness;
	FRidersSliderStyle& SetBarThickness(float InBarThickness) { BarThickness = InBarThickness; return *this; }

	/** Slider thumb Indention */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)
		float Indention;
	FRidersSliderStyle& SetIndention(float InIndention) { Indention = InIndention; return *this; }

	/** Slider thumb Angle */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)
		float Angle;
	FRidersSliderStyle& SetAngle(float InAngle) { Angle = InAngle; return *this; }

};



/**
 * 
 */
UCLASS()
class RIDERSUMG_API URidersSlateTypes : public UObject
{
	GENERATED_BODY()
	
};
