
#include "SRidersSlider.h"
#include "Rendering/DrawElements.h"


void SRidersSlider::Construct(const SRidersSlider::FArguments& InDeclaration)
{
	check(InDeclaration._Style);

	Style = InDeclaration._Style;

	LockedAttribute = InDeclaration._Locked;
	Orientation = InDeclaration._Orientation;
	StepSize = InDeclaration._StepSize;
	ValueAttribute = InDeclaration._Value;
	bIsFocusable = InDeclaration._IsFocusable;
	OnMouseCaptureBegin = InDeclaration._OnMouseCaptureBegin;
	OnMouseCaptureEnd = InDeclaration._OnMouseCaptureEnd;
	OnControllerCaptureBegin = InDeclaration._OnControllerCaptureBegin;
	OnControllerCaptureEnd = InDeclaration._OnControllerCaptureEnd;
	OnValueChanged = InDeclaration._OnValueChanged;;

}


void PushTransformedClip(FSlateWindowElementList& OutDrawElements, const FGeometry& AllottedGeometry, FVector2D InsetPadding, FVector2D ProgressOrigin, FSlateRect Progress)
{
	const FSlateRenderTransform& Transform = AllottedGeometry.GetAccumulatedRenderTransform();

	const FVector2D MaxSize = AllottedGeometry.GetLocalSize() - (InsetPadding * 2.0f);

	OutDrawElements.PushClip(FSlateClippingZone(
		Transform.TransformPoint(InsetPadding + (ProgressOrigin - FVector2D(Progress.Left, Progress.Top)) * MaxSize),
		Transform.TransformPoint(InsetPadding + FVector2D(ProgressOrigin.X + Progress.Right, ProgressOrigin.Y - Progress.Top) * MaxSize),
		Transform.TransformPoint(InsetPadding + FVector2D(ProgressOrigin.X - Progress.Left, ProgressOrigin.Y + Progress.Bottom) * MaxSize),
		Transform.TransformPoint(InsetPadding + (ProgressOrigin + FVector2D(Progress.Right, Progress.Bottom)) * MaxSize)
	));
}


int32 SRidersSlider::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyClippingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{

	const float AllottedWidth = Orientation == Orient_Horizontal ? AllottedGeometry.GetLocalSize().X : AllottedGeometry.GetLocalSize().Y;
	const float AllottedHeight = Orientation == Orient_Horizontal ? AllottedGeometry.GetLocalSize().Y : AllottedGeometry.GetLocalSize().X;

	// Used to track the layer ID we will return.
	int32 RetLayerId = LayerId;

	bool bEnabled = ShouldBeEnabled(bParentEnabled);
	const ESlateDrawEffect DrawEffects = bEnabled ? ESlateDrawEffect::None : ESlateDrawEffect::DisabledEffect;

	const FSlateBrush* CurrentFillImage = &Style->FillImage;

	const FLinearColor FillColorAndOpacitySRGB(InWidgetStyle.GetColorAndOpacityTint() * CurrentFillImage->GetTint(InWidgetStyle));


	const float SliderPercent = ValueAttribute.Get();

	// Paint inside the border only. 
	// Pre-snap the clipping rect to try and reduce common jitter, since the padding is typically only a single pixel.
	FSlateRect SnappedClippingRect = FSlateRect(FMath::RoundToInt(MyClippingRect.Left), FMath::RoundToInt(MyClippingRect.Top), FMath::RoundToInt(MyClippingRect.Right), FMath::RoundToInt(MyClippingRect.Bottom));
	//const FSlateRect ForegroundClippingRect = SnappedClippingRect.InsetBy(FMargin(BorderPadding.Get().X, BorderPadding.Get().Y));

	const FSlateBrush* CurrentBackgroundImage = &Style->BackgroundImage;

	const FSlateBrush* CurrentDisabledBackgroundImage = &Style->DisabledBackgroundImage;

	//float HandleRotation;
	FVector2D HandleTopLeftPoint;

	//*  Test */
	FVector2D SliderStartPoint;
	//* Test */
	FVector2D SliderEndPoint;


	// calculate slider geometry as if it's a horizontal slider (we'll rotate it later if it's vertical)
	const FVector2D HandleSize = Style->NormalThumbImage.ImageSize;
	const FVector2D HalfHandleSize = 0.5f * HandleSize;
	
	const float Indentation = Style->Indention;

	const float SliderLength = AllottedWidth - Indentation;
	const float SliderHandleOffset = SliderPercent * SliderLength;
	const float SliderY = 0.5f * AllottedHeight;

	//HandleRotation = 0.0f;
	HandleTopLeftPoint = FVector2D(SliderHandleOffset - (HandleSize.X * SliderPercent) + 0.5f * Indentation, SliderY - HalfHandleSize.Y);


	//SliderStartPoint = FVector2D(HalfHandleSize.X, SliderY);
	//SliderEndPoint = FVector2D(AllottedWidth - HalfHandleSize.X, SliderY);

	SliderStartPoint = FVector2D(0.0f, SliderY);
	SliderEndPoint = FVector2D(AllottedWidth - 0.0f, SliderY);

	FSlateRect RotatedClippingRect = MyClippingRect;
	FGeometry SliderGeometry = AllottedGeometry;


		// rotate the slider 90deg if it's vertical. The 0 side goes on the bottom, the 1 side on the top.
		if (Orientation == Orient_Vertical)
		{
			// Do this by translating along -X by the width of the geometry, then rotating 90 degreess CCW (left-hand coords)
			FSlateRenderTransform SlateRenderTransform = TransformCast<FSlateRenderTransform>(Concatenate(Inverse(FVector2D(AllottedWidth, 0)), FQuat2D(FMath::DegreesToRadians(-90.0f))));
			// create a child geometry matching this one, but with the render transform.
			SliderGeometry = AllottedGeometry.MakeChild(
				FVector2D(AllottedWidth, AllottedHeight),
				FSlateLayoutTransform(),
				SlateRenderTransform, FVector2D::ZeroVector);

			// The clipping rect is already given properly in window space. But we do not support layout rotations, so our local space rendering cannot
			// get the clipping rect into local space properly for the local space clipping we do in the shader.
			// Thus, we transform the clip coords into local space manually, UNDO the render transform so it will clip properly,
			// and then bring the clip coords back into window space where DrawElements expect them.
			//RotatedClippingRect = TransformRect(
			//	Concatenate(
			//		Inverse(SliderGeometry.GetAccumulatedLayoutTransform()),
			//		Inverse(SlateRenderTransform),
			//		SliderGeometry.GetAccumulatedLayoutTransform()),
			//	MyClippingRect);
		}

		// draw slider bar
		auto BarTopLeft = FVector2D(SliderStartPoint.X, SliderStartPoint.Y - Style->BarThickness * 0.5f);
		auto BarSize = FVector2D(SliderEndPoint.X - SliderStartPoint.X, Style->BarThickness);

		PushTransformedClip(OutDrawElements, AllottedGeometry, FVector2D(0.0f, 0.0f), FVector2D(0, 0), FSlateRect(0, 0, 1, 1));

		FSlateDrawElement::MakeBox(
			OutDrawElements,
			RetLayerId++,
			SliderGeometry.ToPaintGeometry(BarTopLeft, BarSize),
			LockedAttribute.Get() ? CurrentDisabledBackgroundImage : CurrentBackgroundImage,
			DrawEffects,
			LockedAttribute.Get() ? CurrentDisabledBackgroundImage->GetTint(InWidgetStyle) * InWidgetStyle.GetColorAndOpacityTint() : CurrentBackgroundImage->GetTint(InWidgetStyle) * InWidgetStyle.GetColorAndOpacityTint()
		);

		// old
		//FSlateDrawElement::MakeBox(
		//	OutDrawElements,
		//	RetLayerId++,
		//	SliderGeometry.ToPaintGeometry(BarTopLeft, BarSize),
		//	LockedAttribute.Get() ? CurrentDisabledBackgroundImage : CurrentBackgroundImage,
		//	RotatedClippingRect,
		//	DrawEffects,
		//	LockedAttribute.Get() ? CurrentDisabledBackgroundImage->GetTint(InWidgetStyle) * InWidgetStyle.GetColorAndOpacityTint() : CurrentBackgroundImage->GetTint(InWidgetStyle) * InWidgetStyle.GetColorAndOpacityTint()
		//);


		//new
		OutDrawElements.PopClip();


		if (ValueAttribute.IsSet())
		{
			const float ClampedFraction = FMath::Clamp(SliderPercent, 0.0f, 1.0f);
			
			if (Orientation == Orient_Vertical)
			{
				PushTransformedClip(OutDrawElements, AllottedGeometry, FVector2D(0.0f, 0.0f), FVector2D(0, 1), FSlateRect(0, ClampedFraction, 1, 0));

				FSlateRect ClippedAllotedGeometry = FSlateRect(SliderGeometry.AbsolutePosition, SliderGeometry.AbsolutePosition + SliderGeometry.Size * SliderGeometry.Scale);
				ClippedAllotedGeometry.Right = ClippedAllotedGeometry.Left + ClippedAllotedGeometry.GetSize().X * ClampedFraction;

				// Draw Fill
				FSlateDrawElement::MakeBox(
					OutDrawElements,
					RetLayerId++,
					SliderGeometry.ToPaintGeometry(BarTopLeft, FVector2D(SliderGeometry.GetLocalSize().X, BarSize.Y)),
					LockedAttribute.Get() ? CurrentDisabledBackgroundImage : CurrentFillImage,
					DrawEffects,
					FillColorAndOpacitySRGB
				);

				OutDrawElements.PopClip();
			}

			else if (Orientation == Orient_Horizontal)
			{
				PushTransformedClip(OutDrawElements, AllottedGeometry, FVector2D(0.0f, 0.0f), FVector2D(0, 0), FSlateRect(0, 0, ClampedFraction, 1));

				// Draw Fill
				FSlateDrawElement::MakeBox(
					OutDrawElements,
					RetLayerId++,
					SliderGeometry.ToPaintGeometry(BarTopLeft, FVector2D(SliderGeometry.GetLocalSize().X, BarSize.Y)),
					LockedAttribute.Get() ? CurrentDisabledBackgroundImage : CurrentFillImage,
					DrawEffects,
					FillColorAndOpacitySRGB
				);

				OutDrawElements.PopClip();
			}


			//FSlateRect ClippedAllotedGeometry = FSlateRect(SliderGeometry.AbsolutePosition, SliderGeometry.AbsolutePosition + SliderGeometry.Size * SliderGeometry.Scale);
			//ClippedAllotedGeometry.Right = ClippedAllotedGeometry.Left + ClippedAllotedGeometry.GetSize().X * ClampedFraction;

			//old
			//FSlateDrawElement::MakeBox(
			//	OutDrawElements,
			//	RetLayerId++,
			//	SliderGeometry.ToPaintGeometry(BarTopLeft, FVector2D(SliderGeometry.Size.X, BarSize.Y)),
			//	LockedAttribute.Get() ? CurrentDisabledBackgroundImage : CurrentFillImage,
			//	RotatedClippingRect.IntersectionWith(ClippedAllotedGeometry),
			//	DrawEffects,
			//	FillColorAndOpacitySRGB
			//);

			//new

		}

		const FSlateBrush* ThumbImage =  LockedAttribute.Get() ? &Style->DisabledThumbImage  : &Style->NormalThumbImage;
		const FLinearColor ThumbColorAndOpacity = ThumbImage->GetTint(InWidgetStyle) * InWidgetStyle.GetColorAndOpacityTint();


		PushTransformedClip(OutDrawElements, AllottedGeometry, FVector2D(0.0f, 0.0f), FVector2D(0, 0), FSlateRect(0, 0, 1, 1));

	// draw slider thumb
		FSlateDrawElement::MakeBox(
			OutDrawElements,
			RetLayerId++,
			SliderGeometry.ToPaintGeometry(HandleTopLeftPoint, Style->NormalThumbImage.ImageSize),
			LockedAttribute.Get() ? &Style->DisabledThumbImage : &Style->NormalThumbImage,
			DrawEffects,
			ThumbColorAndOpacity
		);

		//old
		//FSlateDrawElement::MakeBox(
		//	OutDrawElements,
		//	RetLayerId++,
		//	SliderGeometry.ToPaintGeometry(HandleTopLeftPoint, Style->NormalThumbImage.ImageSize),
		//	LockedAttribute.Get() ? &Style->DisabledThumbImage : &Style->NormalThumbImage,
		//	RotatedClippingRect,
		//	DrawEffects,
		//	ThumbColorAndOpacity
		//);

		//new
		OutDrawElements.PopClip();

	return RetLayerId;
}

FVector2D SRidersSlider::ComputeDesiredSize(float) const
{
	static const FVector2D SSliderDesiredSize(16.0f, 16.0f);

	if (Style == nullptr)
	{
		return SSliderDesiredSize;
	}

	const float Thickness = FMath::Max(Style->BarThickness, Style->NormalThumbImage.ImageSize.Y);

	if (Orientation == Orient_Vertical)
	{
		return FVector2D(Thickness, SSliderDesiredSize.Y);
	}

	return FVector2D(SSliderDesiredSize.X, Thickness);
}

float SRidersSlider::PositionToValue(const FGeometry& MyGeometry, const FVector2D& AbsolutePosition)
{
	const FVector2D LocalPosition = MyGeometry.AbsoluteToLocal(AbsolutePosition);

	float RelativeValue;

	if (Orientation == Orient_Horizontal)
	{
		RelativeValue = (LocalPosition.X) / (MyGeometry.Size.X);
	}
	else
	{
		RelativeValue = (MyGeometry.Size.Y - LocalPosition.Y) / (MyGeometry.Size.Y);
	}

	return FMath::Clamp(RelativeValue, 0.0f, 1.0f);
}

float SRidersSlider::GetValue() const
{
	return ValueAttribute.Get();
}

void SRidersSlider::SetValue(const TAttribute<float>& InValueAttribute)
{
	ValueAttribute = InValueAttribute;
}



bool SRidersSlider::IsLocked() const
{
	return LockedAttribute.Get();
}

bool SRidersSlider::IsInteractable() const
{
	return IsEnabled() && !IsLocked() && SupportsKeyboardFocus();
}

bool SRidersSlider::SupportsKeyboardFocus() const
{
	return bIsFocusable;
}

void SRidersSlider::ResetControllerState()
{
	if (bControllerInputCaptured)
	{
		OnControllerCaptureEnd.ExecuteIfBound();
		bControllerInputCaptured = false;
	}
}

FReply SRidersSlider::OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent)
{
	FReply Reply = FReply::Unhandled();
	const FKey KeyPressed = InKeyEvent.GetKey();

	if (IsInteractable())
	{
		// The controller's bottom face button must be pressed once to begin manipulating the slider's value.
		// Navigation away from the widget is prevented until the button has been pressed again or focus is lost.
		// The value can be manipulated by using the game pad's directional arrows ( relative to slider orientation ).
		if (KeyPressed == EKeys::Enter || KeyPressed == EKeys::SpaceBar || KeyPressed == EKeys::Virtual_Accept)
		{
			if (bControllerInputCaptured == false)
			{
				// Begin capturing controller input and allow user to modify the slider's value.
				bControllerInputCaptured = true;
				OnControllerCaptureBegin.ExecuteIfBound();
				Reply = FReply::Handled();
			}
			else
			{
				ResetControllerState();
				Reply = FReply::Handled();
			}
		}

		if (bControllerInputCaptured)
		{
			float NewValue = ValueAttribute.Get();
			if (Orientation == EOrientation::Orient_Horizontal)
			{
				if (KeyPressed == EKeys::Left || KeyPressed == EKeys::Gamepad_DPad_Left || KeyPressed == EKeys::Gamepad_LeftStick_Left)
				{
					NewValue -= StepSize.Get();
				}
				else if (KeyPressed == EKeys::Right || KeyPressed == EKeys::Gamepad_DPad_Right || KeyPressed == EKeys::Gamepad_LeftStick_Right)
				{
					NewValue += StepSize.Get();
				}
			}
			else
			{
				if (KeyPressed == EKeys::Down || KeyPressed == EKeys::Gamepad_DPad_Down || KeyPressed == EKeys::Gamepad_LeftStick_Down)
				{
					NewValue -= StepSize.Get();
				}
				else if (KeyPressed == EKeys::Up || KeyPressed == EKeys::Gamepad_DPad_Up || KeyPressed == EKeys::Gamepad_LeftStick_Up)
				{
					NewValue += StepSize.Get();
				}
			}

			CommitValue(FMath::Clamp(NewValue, 0.0f, 1.0f));
			Reply = FReply::Handled();
		}
		else
		{
			Reply = SLeafWidget::OnKeyDown(MyGeometry, InKeyEvent);
		}
	}
	else
	{
		Reply = SLeafWidget::OnKeyDown(MyGeometry, InKeyEvent);
	}

	return Reply;
}

FReply SRidersSlider::OnKeyUp(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent)
{
	FReply Reply = FReply::Unhandled();
	if (bControllerInputCaptured)
	{
		Reply = FReply::Handled();
	}
	return Reply;
}

void SRidersSlider::OnFocusLost(const FFocusEvent& InFocusEvent)
{
	if (bControllerInputCaptured)
	{
		// Commit and reset state
		CommitValue(ValueAttribute.Get());
		ResetControllerState();
	}
}

FReply SRidersSlider::OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	if ((MouseEvent.GetEffectingButton() == EKeys::LeftMouseButton) && !IsLocked())
	{
		OnMouseCaptureBegin.ExecuteIfBound();
		CommitValue(PositionToValue(MyGeometry, MouseEvent.GetLastScreenSpacePosition()));

		// Release capture for controller/keyboard when switching to mouse.
		ResetControllerState();

		return FReply::Handled().CaptureMouse(SharedThis(this));
	}

	return FReply::Unhandled();
}

FReply SRidersSlider::OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	if ((MouseEvent.GetEffectingButton() == EKeys::LeftMouseButton) && HasMouseCapture())
	{
		SetCursor(EMouseCursor::Default);
		OnMouseCaptureEnd.ExecuteIfBound();

		// Release capture for controller/keyboard when switching to mouse.
		ResetControllerState();

		return FReply::Handled().ReleaseMouseCapture();
	}

	return FReply::Unhandled();
}

FReply SRidersSlider::OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	if (this->HasMouseCapture() && !IsLocked())
	{
		SetCursor((Orientation == Orient_Horizontal) ? EMouseCursor::ResizeLeftRight : EMouseCursor::ResizeUpDown);
		//SetCursor(EMouseCursor::ResizeLeftRight);
		CommitValue(PositionToValue(MyGeometry, MouseEvent.GetLastScreenSpacePosition()));

		// Release capture for controller/keyboard when switching to mouse
		ResetControllerState();

		return FReply::Handled();
	}

	return FReply::Unhandled();
}

void SRidersSlider::CommitValue(float NewValue)
{
	if (!ValueAttribute.IsBound())
	{
		ValueAttribute.Set(NewValue);
	}

	OnValueChanged.ExecuteIfBound(NewValue);
}


void SRidersSlider::SetLocked(const TAttribute<bool>& InLocked)
{
	LockedAttribute = InLocked;
}

void SRidersSlider::SetOrientation(EOrientation InOrientation)
{
	Orientation = InOrientation;
}

void SRidersSlider::SetStepSize(const TAttribute<float>& InStepSize)
{
	StepSize = InStepSize;
}