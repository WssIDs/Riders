// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Widgets/RidersSlider.h"
#include "Widgets/DeclarativeSyntaxSupport.h"


#define LOCTEXT_NAMESPACE "UMG"

URidersSlider::URidersSlider(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Orientation = EOrientation::Orient_Horizontal;
	SRidersSlider::FArguments Defaults;
	WidgetStyle = *Defaults._Style;
	StepSize = 0.01f;
	IsFocusable = true;
}


TSharedRef<SWidget> URidersSlider::RebuildWidget()
{
	MySlider = SNew(SRidersSlider)
		.Style(&WidgetStyle)
		.IsFocusable(IsFocusable)
		.OnMouseCaptureBegin(BIND_UOBJECT_DELEGATE(FSimpleDelegate, HandleOnMouseCaptureBegin))
		.OnMouseCaptureEnd(BIND_UOBJECT_DELEGATE(FSimpleDelegate, HandleOnMouseCaptureEnd))
		.OnControllerCaptureBegin(BIND_UOBJECT_DELEGATE(FSimpleDelegate, HandleOnControllerCaptureBegin))
		.OnControllerCaptureEnd(BIND_UOBJECT_DELEGATE(FSimpleDelegate, HandleOnControllerCaptureEnd))
		.OnValueChanged(BIND_UOBJECT_DELEGATE(FOnFloatValueChanged, HandleOnValueChanged));

	return MySlider.ToSharedRef();
}

void URidersSlider::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	TAttribute<float> ValueBinding = PROPERTY_BINDING(float, Value);

	MySlider->SetOrientation(Orientation);
	MySlider->SetValue(Value);
	MySlider->SetLocked(Locked);
	MySlider->SetStepSize(StepSize);
}

void URidersSlider::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	MySlider.Reset();
}

void URidersSlider::HandleOnValueChanged(float InValue)
{
	OnValueChanged.Broadcast(InValue);
}

void URidersSlider::HandleOnMouseCaptureBegin()
{
	OnMouseCaptureBegin.Broadcast();
}

void URidersSlider::HandleOnMouseCaptureEnd()
{
	OnMouseCaptureEnd.Broadcast();
}

void URidersSlider::HandleOnControllerCaptureBegin()
{
	OnControllerCaptureBegin.Broadcast();
}

void URidersSlider::HandleOnControllerCaptureEnd()
{
	OnControllerCaptureEnd.Broadcast();
}

float URidersSlider::GetValue() const
{
	if (MySlider.IsValid())
	{
		return MySlider->GetValue();
	}

	return Value;
}

void URidersSlider::SetValue(float InValue)
{
	Value = InValue;
	if (MySlider.IsValid())
	{
		MySlider->SetValue(InValue);
	}
}

void URidersSlider::SetLocked(bool InLocked)
{
	Locked = InLocked;
	if (MySlider.IsValid())
	{
		MySlider->SetLocked(InLocked);
	}
}

void URidersSlider::SetStepSize(float InValue)
{
	StepSize = InValue;
	if (MySlider.IsValid())
	{
		MySlider->SetStepSize(InValue);
	}
}

#if WITH_EDITOR

const FText URidersSlider::GetPaletteCategory()
{
	return LOCTEXT("Riders", "Riders");
}



//const FSlateBrush* URidersSlider::GetEditorIcon()
//{
//	return FNewUMGStyle::Get().GetBrush("Widget.NewSlider2");
//}

#endif

#undef LOCTEXT_NAMESPACE





