// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "Anim/RidersAnimNode_BrakePadHandler.h"
#include "AnimationRuntime.h"
#include "Pawns/Vehicles/Riders_Vehicle.h"
#include "VehicleWheel.h"
#include "VehicleContent/Riders_WVHMovComponent4W.h"


/////////////////////////////////////////////////////
// FAnimNode_WheelHandler

FRidersAnimNode_BrakePadHandler::FRidersAnimNode_BrakePadHandler()
{
	AnimInstanceProxy = nullptr;
}

void FRidersAnimNode_BrakePadHandler::GatherDebugData(FNodeDebugData& DebugData)
{
	FString DebugLine = DebugData.GetNodeName(this);

	DebugLine += "(";
	AddDebugNodeData(DebugLine);
	DebugLine += ")";

	DebugData.AddDebugItem(DebugLine);

	const TArray<FRidersWheelAnimData>& BrakePadAnimData = AnimInstanceProxy->GetBrakePadAnimData();

	for (const FRidersLookupData& BrakePad : BrakePads)
	{
		if (BrakePad.BoneReference.BoneIndex != INDEX_NONE)
		{
			DebugLine = FString::Printf(TEXT(" [Wheel Index : %d] Bone: %s , Rotation Offset : %s, Location Offset : %s"),
				BrakePad.WheelIndex, *BrakePad.BoneReference.BoneName.ToString(), *BrakePadAnimData[BrakePad.WheelIndex].RotOffset.ToString(), *BrakePadAnimData[BrakePad.WheelIndex].LocOffset.ToString());
		}
		else
		{
			DebugLine = FString::Printf(TEXT(" [Wheel Index : %d] Bone: %s (invalid bone)"),
				BrakePad.WheelIndex, *BrakePad.BoneReference.BoneName.ToString());
		}

		DebugData.AddDebugItem(DebugLine);
	}

	ComponentPose.GatherDebugData(DebugData);
}

void FRidersAnimNode_BrakePadHandler::EvaluateSkeletalControl_AnyThread(FComponentSpacePoseContext& Output, TArray<FBoneTransform>& OutBoneTransforms)
{
	check(OutBoneTransforms.Num() == 0);

	const TArray<FRidersWheelAnimData>& BrakePadAnimData = AnimInstanceProxy->GetBrakePadAnimData();

	const FBoneContainer& BoneContainer = Output.Pose.GetPose().GetBoneContainer();

	FTransform ComponentTransform = Output.AnimInstanceProxy->GetComponentTransform();

	for (const FRidersLookupData& BrakePad : BrakePads)
	{
		if (BrakePad.BoneReference.IsValidToEvaluate(BoneContainer))
		{
			FCompactPoseBoneIndex WheelSimBoneIndex = BrakePad.BoneReference.GetCompactPoseIndex(BoneContainer);
			//FCompactPoseBoneIndex WheelSimBoneIndex = Wheel.BrakePadInfo.BoneReference.GetCompactPoseIndex(BoneContainer);

			// the way we apply transform is same as FMatrix or FTransform
			// we apply scale first, and rotation, and translation
			// if you'd like to translate first, you'll need two nodes that first node does translate and second nodes to rotate. 
			FTransform NewBoneTM = Output.Pose.GetComponentSpaceTransform(WheelSimBoneIndex);

			FAnimationRuntime::ConvertCSTransformToBoneSpace(ComponentTransform, Output.Pose, NewBoneTM, WheelSimBoneIndex, BCS_ComponentSpace);

			// Apply rotation offset
			const FQuat BoneQuat(BrakePadAnimData[BrakePad.WheelIndex].RotOffset);
			NewBoneTM.SetRotation(BoneQuat * NewBoneTM.GetRotation());

			// Apply loc offset
			NewBoneTM.AddToTranslation(BrakePadAnimData[BrakePad.WheelIndex].LocOffset);

			// Convert back to Component Space.
			FAnimationRuntime::ConvertBoneSpaceTransformToCS(ComponentTransform, Output.Pose, NewBoneTM, WheelSimBoneIndex, BCS_ComponentSpace);

			// add back to it
			OutBoneTransforms.Add(FBoneTransform(BrakePad.BoneReference.GetCompactPoseIndex(BoneContainer), NewBoneTM));

		}
	}
}


bool FRidersAnimNode_BrakePadHandler::IsValidToEvaluate(const USkeleton* Skeleton, const FBoneContainer& RequiredBones)
{
	// if both bones are valid
	for (const FRidersLookupData& BrakePad : BrakePads)
	{
		// if one of them is valid
		if (BrakePad.BoneReference.IsValidToEvaluate(RequiredBones) == true)
		{
			return true;
		}
	}

	return false;
}

void FRidersAnimNode_BrakePadHandler::InitializeBoneReferences(const FBoneContainer& RequiredBones)
{
	const TArray<FRidersWheelAnimData>& BrakePadAnimData = AnimInstanceProxy->GetBrakePadAnimData();
	const int32 NumWheels = BrakePadAnimData.Num();
	BrakePads.Empty(NumWheels);

	for (int32 WheelIndex = 0; WheelIndex < NumWheels; ++WheelIndex)
	{
		FRidersLookupData* BrakePad = new(BrakePads)FRidersLookupData();
		BrakePad->WheelIndex = WheelIndex;
		BrakePad->BoneReference.BoneName = BrakePadAnimData[WheelIndex].BoneName;

		BrakePad->BoneReference.Initialize(RequiredBones);

		//UE_LOG(RidersAnimLog, Log, TEXT("numbrakepads = %d - %s"), BrakePad->WheelIndex, *BrakePad->BoneReference.BoneName.ToString());
	}

	// sort by bone indices
	BrakePads.Sort([](const FRidersLookupData& L, const FRidersLookupData& R) { return L.BoneReference.BoneIndex < R.BoneReference.BoneIndex; });
}

void FRidersAnimNode_BrakePadHandler::Initialize_AnyThread(const FAnimationInitializeContext & Context)
{
	AnimInstanceProxy = (FRidersVehicleAnimInstanceProxy*)Context.AnimInstanceProxy;	//TODO: This is cached for now because we need it in eval bone transforms.
}
