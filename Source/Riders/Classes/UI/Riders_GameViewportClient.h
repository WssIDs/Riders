#pragma once

#include "Engine/GameViewportClient.h"
#include "Riders_GameViewportClient.generated.h"

/**
 * 
 */
UCLASS()
class URiders_GameViewportClient : public UGameViewportClient
{
	GENERATED_BODY()

	// Constructor declaration
	URiders_GameViewportClient(const FObjectInitializer& ObjectInitializer);

	
public:

	// Begin UObject Interface
	virtual void PostInitProperties() override;


	/**
	* Displays the transition screen.
	* @param Canvas - The canvas to use for rendering.
	*/
	virtual void DrawTransition(class UCanvas* Canvas);

	/** Print a custom position transition message with a drop shadow. */
	void DrawTransitionMessagePositioned(class UCanvas* Canvas, const FString& Message, float PosX, float PosY);
};
