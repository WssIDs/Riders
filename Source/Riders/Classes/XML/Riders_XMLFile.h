// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "Runtime/CoreUObject/Public/UObject/Object.h"
#include "Riders_XMLFile.generated.h"

#ifndef PARAGRAPH_TERMINATOR_ONE						
#define PARAGRAPH_TERMINATOR_ONE TEXT("	")
#endif

#ifndef PARAGRAPH_TERMINATOR_TWO						
#define PARAGRAPH_TERMINATOR_TWO TEXT("		")
#endif




USTRUCT(BlueprintType)
struct FXMLSubChildNode
{
	GENERATED_USTRUCT_BODY();

	/** Child Node Name */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
		FString NodeName;

	/** Child Node Attribute Name */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
		FString AttributeName;

	/** Child Node Attribute Value */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
		FString AttributeValue;

	/** Child Node Content */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
		FString Content;



	FXMLSubChildNode()
	{

	}
};


USTRUCT(BlueprintType)
struct FXMLChildNode
{
	GENERATED_USTRUCT_BODY();

	/** Child Node Name */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
		FString NodeName;

	/** Child Node Attribute Name */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
		FString AttributeName;

	/** Child Node Attribute Value */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
		FString AttributeValue;

	/** SubChild Nodes */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
	TArray<FXMLSubChildNode> SubChildNodes;


	FXMLChildNode()
	{

	}
};


USTRUCT(BlueprintType)
struct FXMLRootNode
{
	GENERATED_USTRUCT_BODY();

	/** Root Node Name */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
		FString NodeName;

	/** Root Node Attribute Name */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
		FString AttributeName;

	/** Root Node Attribute Value */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
		FString AttributeValue;


	FXMLRootNode()
	{

	}
};



/**
 * Main Class for work with XML files
 */
UCLASS()
class RIDERS_API URiders_XMLFile : public UObject
{
	GENERATED_BODY()
	
	URiders_XMLFile();

	/* string for saving xml */
	FString XmlLines;

public:

	/* start xml documnet */
	void StartDocument();

	void StartRootElement(FString RootNodeName,FString RootNodeAttributeName, FString RootNodeAttributeValue);
	void StartRootElement(FString RootNodeName);

	void EndRootElement();

	/** Root Node */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
	FXMLRootNode RootNode;

	/** Child Nodes */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
	TArray<FXMLChildNode> ChildNodes;


	void AppendChild(FString ChildNodeName,FString ChildNodeAttribute,FString ChildNodeAttributeValue);
	void AppendChild(FString ChildNodeName);

	void AppendSubChild(int32 index, FString SubChildNodeName, FString SubChildAttribute, FString SubChildAttributeValue, FString SubChildContent);
	void AppendSubChild(int32 index, FString SubChildNodeName, FString SubChildContent);

	void GenerateChildren();

	void Save(FString Path);

	/** GetXmlLines */
	UFUNCTION(BlueprintCallable, Category = "Game Play")
	FString GetAllLines();


};
