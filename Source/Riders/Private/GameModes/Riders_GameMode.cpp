// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "GameModes/Riders_GameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "XML/Riders_XMLFile.h"
#include "Riders.h"
#include "XmlParser.h"
#include "Pawns/Vehicles/Riders_Vehicle.h"
#include "Runtime/Core/Public/Misc/Paths.h"


ARiders_GameMode::ARiders_GameMode()
{

	
	
	//PlayerControllerClass = ARiders_GamePlayerController::StaticClass();
	//HUDClass = ARiders_HUD::StaticClass();

	
	StartVehicleClass = ARiders_Vehicle::StaticClass();
	
	//static ConstructorHelpers::FObjectFinder<UBlueprint> PlayerVehicleObject(TEXT("Blueprint'/Game/Vehicles/Lamborghini/Aventador.Aventador'"));
	//if (PlayerVehicleObject.Object != NULL)
	//{
	//	StartVehicleClass = (UClass*)PlayerVehicleObject.Object->GeneratedClass;
	//}
		
}

void ARiders_GameMode::InitHumanMap()
{
	HumanMap.Add(0, "Kate");
	HumanMap.Add(1, "John");
	HumanMap.Add(5, "Martin");
	HumanMap.Add(7, "Lea");
	HumanMap.Add(3, "Richard");
}

bool HumanSortAsc(int32 A, int32 B)
{
	return A < B;
}

bool HumanSortDesc(int32 A, int32 B)
{
	return A > B;
}


void ARiders_GameMode::AddItemHumanMap(int32 idx, FString Text)
{
	HumanMap.Add(idx, Text);
}

void ARiders_GameMode::SortHumanMapByKey(ETypeSort Type)
{
	Type == ETypeSort::Type_ASC ? HumanMap.KeySort(HumanSortAsc) : HumanMap.KeySort(HumanSortDesc);
}

void ARiders_GameMode::OutHumanMap()
{

	for(auto& Elem : HumanMap)
	{
		UE_LOG(SaveGameLog, Log, TEXT("%d - %s\n"), Elem.Key,*Elem.Value);
	}

}


TArray<FXmlColorData> ARiders_GameMode::LoadDataFromXml()
{

	TArray<FXmlColorData> XmlData;

	FString filename = "color_table.xml";

	FString Path = FPaths::ProjectContentDir() + "\\Data\\";

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, *(Path + filename));


	const FXmlFile file(Path+filename);
	const FXmlNode* pRoot = file.GetRootNode();

	const TArray<FXmlNode*> Nodes = pRoot->GetChildrenNodes();

	UE_LOG(SaveGameLog, Warning, TEXT("%s"), *pRoot->GetTag());


	int32 ColumnIndex = 0;
	int32 RowIndex = 0;

	int32 RedChannel = 0;
	int32 GreenChannel = 0;
	int32 BlueChannel = 0;
	int32 AlphaChannel = 0;

	if (Nodes.Num() > 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, *FString::FromInt(Nodes.Num()));
		
		
		for (int32 i = 0; i < Nodes.Num(); i++)
		{

			const TArray<FXmlNode*> ChildNodes = Nodes[i]->GetChildrenNodes();

			for (int32 j = 0; j < ChildNodes.Num(); j++)
			{

				if (ChildNodes[j]->GetTag() == "ColumnIndex")
				{
					ColumnIndex = FCString::Atoi(*ChildNodes[j]->GetContent());
				}

				if (ChildNodes[j]->GetTag() == "RowIndex")
				{
					RowIndex = FCString::Atoi(*ChildNodes[j]->GetContent());
				}


				if (ChildNodes[j]->GetTag() == "R")
				{
					RedChannel = FCString::Atoi(*ChildNodes[j]->GetContent());
				}

				else if (ChildNodes[j]->GetTag() == "G")
				{
					GreenChannel = FCString::Atoi(*ChildNodes[j]->GetContent());
				}

				else if (ChildNodes[j]->GetTag() == "B")
				{
					BlueChannel = FCString::Atoi(*ChildNodes[j]->GetContent());
				}

				else if (ChildNodes[j]->GetTag() == "A")
				{
					AlphaChannel = FCString::Atoi(*ChildNodes[j]->GetContent());
				}

				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor(FCString::Atoi(*RedChannel), FCString::Atoi(*GreenChannel), FCString::Atoi(*BlueChannel), FCString::Atoi(*AlphaChannel)), RedChannel + "," + GreenChannel + "," + BlueChannel+","+ AlphaChannel);



			}

			FColor color = FColor(RedChannel, GreenChannel, BlueChannel, AlphaChannel);

			FXmlColorData data;

			data.ColumnIndex = ColumnIndex;
			data.RowIndex = RowIndex;
			data.Color = color;

			XmlData.Add(data);

			//FString fullmessage = FString::FromInt(i) + ".  Color= " + RedChannel + "," + GreenChannel + "," + BlueChannel + "," + AlphaChannel;

			//UE_LOG(SaveGameLog, Warning, TEXT("%s"), *fullmessage);
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "No Data");
	}

	return XmlData;
}


void ARiders_GameMode::DoXmlFile()
{
	TArray<FXmlColorData> Data = LoadDataFromXml();


	FString filename = "color_table_saved_UE4.xml";

	FString Path = FPaths::ProjectContentDir() + "\\Data\\";

	FString pathall = Path + filename;

	// XML File Process Saveing

	URiders_XMLFile* Xmlfile = NewObject<URiders_XMLFile>();

	Xmlfile->StartDocument();
	Xmlfile->StartRootElement("head");
	
	for (int32 i = 0; i < Data.Num(); i++)
	{
		Xmlfile->AppendChild("color", "index", FString::FromInt(i));
		Xmlfile->AppendSubChild(i, "ColumnIndex" , FString::FromInt(Data[i].ColumnIndex));
		Xmlfile->AppendSubChild(i, "RowIndex" , FString::FromInt(Data[i].RowIndex));
		Xmlfile->AppendSubChild(i, "R" , FString::FromInt(Data[i].Color.R));
		Xmlfile->AppendSubChild(i, "G" , FString::FromInt(Data[i].Color.G));
		Xmlfile->AppendSubChild(i, "B" , FString::FromInt(Data[i].Color.B));
		Xmlfile->AppendSubChild(i, "A" , FString::FromInt(Data[i].Color.A));
	}

	Xmlfile->GenerateChildren();
	Xmlfile->EndRootElement();

	Xmlfile->Save(pathall);

	FString str = Xmlfile->GetAllLines();

	UE_LOG(SaveGameLog, Log,TEXT("%s"),*str);
}