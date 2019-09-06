// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SlateBasics.h"
#include "Runtime/SlateCore/Public/Styling/ISlateStyle.h"
#include "Styling/SlateStyle.h"
//#include "Runtime/SlateCore/Public/Styling/CoreStyle.h"

/**
 * Main Riders Style
 */
class FRidersStyle
{
public:
	static void Initialize();
	static void Shutdown();

	static const ISlateStyle& Get();

	static TSharedPtr<class ISlateStyle> StylePtr;

};

/**
 * Riders UMG Style
 */
class FRidersUMGStyle
{
public:

	static void Initialize();

	static void Shutdown();

	/** reloads textures used by slate renderer */
	static void ReloadTextures();

	/** @return The Slate style set for the UMG Style */
	static const ISlateStyle& Get();

	static FName GetStyleSetName();

private:

	static TSharedRef< class FSlateStyleSet > Create();

private:

	static TSharedPtr< class FSlateStyleSet > UMGStyleInstance;
};
