
#include "Riders/Classes/UI/Riders_GameViewportClient.h"
#include "Riders.h"
#include "CanvasItem.h"
#include "Engine/Canvas.h"



URiders_GameViewportClient::URiders_GameViewportClient(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}



void URiders_GameViewportClient::PostInitProperties()
{

	Super::PostInitProperties();

}

void URiders_GameViewportClient::DrawTransition(UCanvas* Canvas)
{
	Super::DrawTransition(Canvas);

	if (bSuppressTransitionMessage == false)
	{
		switch (GetOuterUEngine()->TransitionType)
		{
		case TT_Loading:
			DrawTransitionMessage(Canvas, NSLOCTEXT("GameViewportClient", "LoadingMessage", "LOADING").ToString());
			DrawTransitionMessagePositioned(Canvas, TEXT("LOADING..."), 0.1f, 0.3f);
			break;
		case TT_Saving:
			DrawTransitionMessage(Canvas, NSLOCTEXT("GameViewportClient", "SavingMessage", "SAVING").ToString());
			break;
		case TT_Connecting:
			DrawTransitionMessage(Canvas, NSLOCTEXT("GameViewportClient", "ConnectingMessage", "CONNECTING").ToString());
			break;
		case TT_Precaching:
			DrawTransitionMessage(Canvas, NSLOCTEXT("GameViewportClient", "PrecachingMessage", "PRECACHING").ToString());
			break;
		case TT_Paused:
			DrawTransitionMessage(Canvas, NSLOCTEXT("GameViewportClient", "PausedMessage", "PAUSED").ToString());
			DrawTransitionMessagePositioned(Canvas, TEXT("Game Twice"), 0.5f, 0.1f);
			break;
		case TT_WaitingToConnect:
			DrawTransitionMessage(Canvas, TEXT("Waiting to connect...")); // Temp - localization of the FString messages is broke atm. Loc this when its fixed.
			break;
		}
	}
}



void URiders_GameViewportClient::DrawTransitionMessagePositioned(UCanvas* Canvas, const FString& Message, float PosX, float PosY)
{

	FCanvasTextItem TextItem(FVector2D::ZeroVector, FText::GetEmpty(), GEngine->GetTinyFont(), FLinearColor::Blue);
	TextItem.EnableShadow(FLinearColor::Black);
	TextItem.Text = FText::FromString(Message);
	float XL, YL;
	Canvas->StrLen(GEngine->GetTinyFont(), Message, XL, YL);
	Canvas->DrawItem(TextItem, PosX * (Canvas->ClipX - XL), PosY * Canvas->ClipY - YL * 0.5f);
}
