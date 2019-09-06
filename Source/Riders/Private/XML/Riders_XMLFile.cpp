// Fill out your copyright notice in the Description page of Project Settings.

#include "XML/Riders_XMLFile.h"
#include "Runtime/Core/Public/HAL/FileManager.h"
#include "Riders.h"


URiders_XMLFile::URiders_XMLFile()
{

	XmlLines = "";
}

void URiders_XMLFile::StartDocument()
{	
	/* set start line for xml file */
	FString xmlHeader = TEXT("<?xml version=\"1.0\" encoding=\"UTF-8\"?>") LINE_TERMINATOR;
	XmlLines += xmlHeader;
}

void URiders_XMLFile::StartRootElement(FString RootNodeName, FString RootNodeAttributeName, FString RootNodeAttributeValue)
{
	RootNode.NodeName = RootNodeName;
	RootNode.AttributeName = RootNodeAttributeName;
	RootNode.AttributeValue = RootNodeAttributeValue;


	XmlLines += TEXT("<" + RootNode.NodeName +" "+RootNode.AttributeName+"=\""+RootNode.AttributeValue+"\""+">") LINE_TERMINATOR;
}

void URiders_XMLFile::StartRootElement(FString RootNodeName)
{
	RootNode.NodeName = RootNodeName;
	RootNode.AttributeName = "";
	RootNode.AttributeValue = "";

	XmlLines += TEXT("<" + RootNode.NodeName + ">") LINE_TERMINATOR;
}

void URiders_XMLFile::EndRootElement()
{
	XmlLines += TEXT("</" + RootNode.NodeName + ">");
}

void URiders_XMLFile::AppendChild(FString ChildNodeName, FString ChildNodeAttribute, FString ChildNodeAttributeValue)
{
	FXMLChildNode TmpChild;
	TmpChild.NodeName = ChildNodeName;
	TmpChild.AttributeName = ChildNodeAttribute;
	TmpChild.AttributeValue = ChildNodeAttributeValue;

	ChildNodes.Add(TmpChild);
}

void URiders_XMLFile::AppendChild(FString ChildNodeName)
{
	FXMLChildNode TmpChild;
	TmpChild.NodeName = ChildNodeName;
	TmpChild.AttributeName = "";
	TmpChild.AttributeValue = "";

	ChildNodes.Add(TmpChild);
}

void URiders_XMLFile::AppendSubChild(int32 index, FString SubChildNodeName,FString SubChildAttribute,FString SubChildAttributeValue, FString SubChildContent)
{

	if (ChildNodes.Num() > 0)
	{
		FXMLSubChildNode TmpSubChild;
		TmpSubChild.NodeName = SubChildNodeName;
		TmpSubChild.AttributeName = SubChildAttribute;
		TmpSubChild.AttributeValue = SubChildAttributeValue;
		TmpSubChild.Content = SubChildContent;

		ChildNodes[index].SubChildNodes.Add(TmpSubChild);
	}

	UE_LOG(SaveGameLog, Warning, TEXT("%d"), ChildNodes.Num());
}

void URiders_XMLFile::AppendSubChild(int32 index, FString SubChildNodeName, FString SubChildContent)
{

	if (ChildNodes.Num() > 0)
	{
		FXMLSubChildNode TmpSubChild;
		TmpSubChild.NodeName = SubChildNodeName;
		TmpSubChild.AttributeName = "";
		TmpSubChild.AttributeValue = "";
		TmpSubChild.Content = SubChildContent;

		ChildNodes[index].SubChildNodes.Add(TmpSubChild);
	}

	UE_LOG(SaveGameLog, Warning, TEXT("%d"), ChildNodes.Num());
}

void URiders_XMLFile::GenerateChildren()
{
	if (ChildNodes.Num() > 0)
	{
		for (int32 i = 0; i < ChildNodes.Num(); i++)
		{
			if (ChildNodes[i].AttributeName != "")
			{
				XmlLines += PARAGRAPH_TERMINATOR_ONE "<" + ChildNodes[i].NodeName + " " + ChildNodes[i].AttributeName + "=\"" + ChildNodes[i].AttributeValue + "\">" LINE_TERMINATOR;
			}

			else
			{
				XmlLines += PARAGRAPH_TERMINATOR_ONE "<" + ChildNodes[i].NodeName + "\">" LINE_TERMINATOR;
			}

			UE_LOG(SaveGameLog, Warning, TEXT("%s"), *ChildNodes[i].NodeName);


			if (ChildNodes[i].SubChildNodes.Num() > 0)
			{

				for (int32 j = 0; j < ChildNodes[i].SubChildNodes.Num(); j++)
				{
					if (ChildNodes[i].SubChildNodes[j].AttributeName != "")
					{
						XmlLines += PARAGRAPH_TERMINATOR_TWO "<" + ChildNodes[i].SubChildNodes[j].NodeName + " " + ChildNodes[i].SubChildNodes[j].AttributeName + "=\"" + ChildNodes[i].SubChildNodes[j].AttributeValue + "\">" + ChildNodes[i].SubChildNodes[j].Content + "</" + ChildNodes[i].SubChildNodes[j].NodeName + ">" LINE_TERMINATOR;
					}

					else
					{
						XmlLines += PARAGRAPH_TERMINATOR_TWO "<" + ChildNodes[i].SubChildNodes[j].NodeName + ">" + ChildNodes[i].SubChildNodes[j].Content + "</" + ChildNodes[i].SubChildNodes[j].NodeName + ">" LINE_TERMINATOR;
					}

					UE_LOG(SaveGameLog, Warning, TEXT("%s"), *ChildNodes[i].SubChildNodes[j].NodeName);
					UE_LOG(SaveGameLog, Warning, TEXT("%s"), *ChildNodes[i].SubChildNodes[j].Content);
				}
			}

			else
			{
				UE_LOG(SaveGameLog, Warning, TEXT("No Subchildrens"));
			}

			XmlLines += PARAGRAPH_TERMINATOR_ONE "</" + ChildNodes[i].NodeName + ">" LINE_TERMINATOR;

		}
	}
}

void URiders_XMLFile::Save(FString Path)
{
	TUniquePtr<FArchive> Archive(IFileManager::Get().CreateFileWriter(*Path));

	FTCHARToUTF8 Converter(*XmlLines);
	Archive->Serialize(const_cast<char*>(Converter.Get()), Converter.Length());
}

FString URiders_XMLFile::GetAllLines()
{
	return XmlLines;
}
