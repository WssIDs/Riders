// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "Anim/RidersAnimNode_WheelHandler.h"
#include "AnimationRuntime.h"
#include "Pawns/Vehicles/Riders_Vehicle.h"
#include "VehicleWheel.h"
#include "VehicleContent/Riders_WVHMovComponent4W.h"


/////////////////////////////////////////////////////
// FAnimNode_WheelHandler


DEFINE_LOG_CATEGORY(RidersAnimWheelHandlerLog);

FRidersAnimNode_WheelHandler::FRidersAnimNode_WheelHandler()
{
	AnimInstanceProxy = nullptr;
}

void FRidersAnimNode_WheelHandler::GatherDebugData(FNodeDebugData& DebugData)
{
	FString DebugLine = DebugData.GetNodeName(this);

	DebugLine += "(";
	AddDebugNodeData(DebugLine);
	DebugLine += ")";

	DebugData.AddDebugItem(DebugLine);

	const TArray<FRidersWheelAnimData>& WheelAnimData = AnimInstanceProxy->GetWheelAnimData();

	for (const FRidersLookupData& Wheel : Wheels)
	{
		if (Wheel.BoneReference.BoneIndex != INDEX_NONE)
		{
			DebugLine = FString::Printf(TEXT(" [Wheel Index : %d] Bone: %s , Rotation Offset : %s, Location Offset : %s"),
				Wheel.WheelIndex, *Wheel.BoneReference.BoneName.ToString(), *WheelAnimData[Wheel.WheelIndex].RotOffset.ToString(), *WheelAnimData[Wheel.WheelIndex].LocOffset.ToString());
		}
		else
		{
			DebugLine = FString::Printf(TEXT(" [Wheel Index : %d] Bone: %s (invalid bone)"),
				Wheel.WheelIndex, *Wheel.BoneReference.BoneName.ToString());
		}

		DebugData.AddDebugItem(DebugLine);
	}

	/////////////////////////////////////////
	/// brakepads

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

	////////////////////////////////////////////////

	ComponentPose.GatherDebugData(DebugData);
}

void FRidersAnimNode_WheelHandler::EvaluateSkeletalControl_AnyThread(FComponentSpacePoseContext& Output, TArray<FBoneTransform>& OutBoneTransforms)
{
	check(OutBoneTransforms.Num() == 0);

	const TArray<FRidersWheelAnimData>& WheelAnimData = AnimInstanceProxy->GetWheelAnimData();

	const FBoneContainer& BoneContainer = Output.Pose.GetPose().GetBoneContainer();
	for (const FRidersLookupData& Wheel : Wheels)
	{
		if (Wheel.BoneReference.IsValidToEvaluate(BoneContainer))
		{
			FCompactPoseBoneIndex WheelSimBoneIndex = Wheel.BoneReference.GetCompactPoseIndex(BoneContainer);
			//FCompactPoseBoneIndex WheelSimBoneIndex = Wheel.BrakePadInfo.BoneReference.GetCompactPoseIndex(BoneContainer);

			// the way we apply transform is same as FMatrix or FTransform
			// we apply scale first, and rotation, and translation
			// if you'd like to translate first, you'll need two nodes that first node does translate and second nodes to rotate. 
			FTransform NewBoneTM = Output.Pose.GetComponentSpaceTransform(WheelSimBoneIndex);

			FAnimationRuntime::ConvertCSTransformToBoneSpace(Output.AnimInstanceProxy->GetComponentTransform(), Output.Pose, NewBoneTM, WheelSimBoneIndex, BCS_ComponentSpace);

			// Apply rotation offset
			const FQuat BoneQuat(WheelAnimData[Wheel.WheelIndex].RotOffset);
			NewBoneTM.SetRotation(BoneQuat * NewBoneTM.GetRotation());

			// Apply loc offset
			NewBoneTM.AddToTranslation(WheelAnimData[Wheel.WheelIndex].LocOffset);

			// Convert back to Component Space.
			FAnimationRuntime::ConvertBoneSpaceTransformToCS(Output.AnimInstanceProxy->GetComponentTransform(), Output.Pose, NewBoneTM, WheelSimBoneIndex, BCS_ComponentSpace);

			// add back to it
			OutBoneTransforms.Add(FBoneTransform(WheelSimBoneIndex, NewBoneTM));

		}
	}


	const TArray<FRidersWheelAnimData>& BrakePadAnimData = AnimInstanceProxy->GetBrakePadAnimData();

	const FBoneContainer& PadsBoneContainer = Output.Pose.GetPose().GetBoneContainer();

	FTransform ComponentTransform = Output.AnimInstanceProxy->GetComponentTransform();

	for (const FRidersLookupData& BrakePad : BrakePads)
	{
		if (BrakePad.BoneReference.IsValidToEvaluate(PadsBoneContainer))
		{
			FCompactPoseBoneIndex WheelSimBoneIndex = BrakePad.BoneReference.GetCompactPoseIndex(PadsBoneContainer);
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
			OutBoneTransforms.Add(FBoneTransform(BrakePad.BoneReference.GetCompactPoseIndex(PadsBoneContainer), NewBoneTM));

		}
	}

}


bool FRidersAnimNode_WheelHandler::IsValidToEvaluate(const USkeleton* Skeleton, const FBoneContainer& RequiredBones)
{
	// if both bones are valid
	for (const FRidersLookupData& Wheel : Wheels)
	{
		// if one of them is valid
		if (Wheel.BoneReference.IsValidToEvaluate(RequiredBones) == true)
		{
			return true;
		}
	}

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

void FRidersAnimNode_WheelHandler::InitializeBoneReferences(const FBoneContainer& RequiredBones)
{
	const TArray<FRidersWheelAnimData>& WheelAnimData = AnimInstanceProxy->GetWheelAnimData();
	const int32 NumWheels = WheelAnimData.Num();
	Wheels.Empty(NumWheels);

	for (int32 WheelIndex = 0; WheelIndex < NumWheels; ++WheelIndex)
	{
		FRidersLookupData* Wheel = new(Wheels)FRidersLookupData();
		Wheel->WheelIndex = WheelIndex;
		Wheel->BoneReference.BoneName = WheelAnimData[WheelIndex].BoneName;
		Wheel->BoneReference.Initialize(RequiredBones);

		//UE_LOG(RidersAnimLog, Log, TEXT("numwheels = %d - %s"), Wheel->WheelIndex, *Wheel->BoneReference.BoneName.ToString());
	}

	// sort by bone indices
	Wheels.Sort([](const FRidersLookupData& L, const FRidersLookupData& R) { return L.BoneReference.BoneIndex < R.BoneReference.BoneIndex; });


	const TArray<FRidersWheelAnimData>& BrakePadAnimData = AnimInstanceProxy->GetBrakePadAnimData();
	const int32 NumBrakeWheels = BrakePadAnimData.Num();
	BrakePads.Empty(NumBrakeWheels);

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

void FRidersAnimNode_WheelHandler::Initialize_AnyThread(const FAnimationInitializeContext & Context)
{
	AnimInstanceProxy = (FRidersVehicleAnimInstanceProxy*)Context.AnimInstanceProxy;	//TODO: This is cached for now because we need it in eval bone transforms.
}
