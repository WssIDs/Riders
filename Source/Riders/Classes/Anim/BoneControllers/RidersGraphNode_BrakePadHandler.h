// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "AnimGraphNode_SkeletalControlBase.h"
#include "Anim/RidersAnimNode_BrakePadHandler.h"
#include "RidersGraphNode_BrakePadHandler.generated.h"


class UEdGraph;

/**
 * 
 */
UCLASS()
class RIDERS_API URidersGraphNode_BrakePadHandler : public UAnimGraphNode_SkeletalControlBase
{
	GENERATED_BODY()

	URidersGraphNode_BrakePadHandler();
	
	
	UPROPERTY(EditAnywhere, Category = Settings)
	FRidersAnimNode_BrakePadHandler Node;

public:
	// UEdGraphNode interface
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FText GetTooltipText() const override;
	// validate if this is within VehicleAnimInstance
	virtual void ValidateAnimNodePostCompile(class FCompilerResultsLog& MessageLog, class UAnimBlueprintGeneratedClass* CompiledClass, int32 CompiledNodeIndex) override;
	virtual bool IsCompatibleWithGraph(const UEdGraph* TargetGraph) const override;
	// End of UEdGraphNode interface

protected:
	// UAnimGraphNode_SkeletalControlBase interface
	virtual FText GetControllerDescription() const override;
	virtual const FAnimNode_SkeletalControlBase* GetNode() const override { return &Node; }
	// End of UAnimGraphNode_SkeletalControlBase interface	
	
};
