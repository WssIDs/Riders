// Fill out your copyright notice in the Description page of Project Settings.

#include "Anim/BoneControllers/RidersGraphNode_BrakePadHandler.h"
#include "Riders.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "Kismet2/CompilerResultsLog.h"


////////////////////////////////////////////////////
// UAnimGraphNode_WheelHandler

#define LOCTEXT_NAMESPACE "A3Nodes"

URidersGraphNode_BrakePadHandler::URidersGraphNode_BrakePadHandler()
{
}

FText URidersGraphNode_BrakePadHandler::GetControllerDescription() const
{
	return LOCTEXT("RidersAnimGraphNode_BrakePadHandler", "BrakePad Handler for RidersVehicle");
}

FText URidersGraphNode_BrakePadHandler::GetTooltipText() const
{
	return LOCTEXT("RidersAnimGraphNode_BrakePadHandler_Tooltip", "This alters the wheel transform based on set up in Riders Vehicle. This only works when the owner is RidersVehicle.");
}

FText URidersGraphNode_BrakePadHandler::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	FText NodeTitle;
	if (TitleType == ENodeTitleType::ListView || TitleType == ENodeTitleType::MenuTitle)
	{
		NodeTitle = GetControllerDescription();
	}
	else
	{
		// we don't have any run-time information, so it's limited to print  
		// anymore than what it is it would be nice to print more data such as 
		// name of bones for wheels, but it's not available in Persona
		NodeTitle = FText(LOCTEXT("RidersAnimGraphNode_BrakePadHandler_Title", "Riders BrakePad Handler"));
	}
	return NodeTitle;
}

void URidersGraphNode_BrakePadHandler::ValidateAnimNodePostCompile(class FCompilerResultsLog& MessageLog, class UAnimBlueprintGeneratedClass* CompiledClass, int32 CompiledNodeIndex)
{
	// we only support vehicle anim instance
	if (CompiledClass->IsChildOf(URiders_AnimInstance::StaticClass()) == false)
	{
		MessageLog.Error(TEXT("@@ is only allowed in RidersAnimInstance. If this is for vehicle, please change parent to be RidersAnimInstancen (Reparent Class)."), this);
	}
}

bool URidersGraphNode_BrakePadHandler::IsCompatibleWithGraph(const UEdGraph* TargetGraph) const
{
	UBlueprint* Blueprint = FBlueprintEditorUtils::FindBlueprintForGraph(TargetGraph);
	return (Blueprint != nullptr) && Blueprint->ParentClass->IsChildOf<URiders_AnimInstance>() && Super::IsCompatibleWithGraph(TargetGraph);
}


#undef LOCTEXT_NAMESPACE





