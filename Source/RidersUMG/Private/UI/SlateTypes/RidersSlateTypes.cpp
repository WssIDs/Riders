// Fill out your copyright notice in the Description page of Project Settings.

#include "RidersSlateTypes.h"
#include "Brushes/SlateNoResource.h"
#include "Styling/StyleDefaults.h"


FRidersSliderStyle::FRidersSliderStyle()
{
}

void FRidersSliderStyle::GetResources(TArray< const FSlateBrush* >& OutBrushes) const
{
	OutBrushes.Add(&BackgroundImage);
	OutBrushes.Add(&DisabledBackgroundImage);
	OutBrushes.Add(&FillImage);
	OutBrushes.Add(&NormalThumbImage);
	OutBrushes.Add(&DisabledThumbImage);
}

const FName FRidersSliderStyle::TypeName(TEXT("FRidersSliderStyle"));

const FRidersSliderStyle& FRidersSliderStyle::GetDefault()
{
	static FRidersSliderStyle Default;
	return Default;
}


