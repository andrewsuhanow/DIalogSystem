//FDialogParameter

#pragma once

#include "DialogParameter.generated.h"



 
UENUM()  //BlueprintType, Blueprintable
enum class EReplicRepeat : uint8
{
	once,
	after_once,
	always,
	back,
};

UENUM()  //BlueprintType, Blueprintable
enum class EResponseRepeat : uint8
{
	once,
	always,
};
UENUM()  //BlueprintType, Blueprintable
enum class EResponseReturn : uint8
{
	none,       // Onse, Afer_Onse
	exit,		
	click_link_once,
	click_link_back,									 
	click_link_noreplic,						 

	pass_link_once,
	pass_link_back,											
	pass_link_noreplic,										
};














USTRUCT(BlueprintType, Blueprintable)
struct FVariables
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY()
		FName Name = "none";   //  name - if global;  index if local

		UPROPERTY()
			FName Value = "none";
};




USTRUCT(BlueprintType, Blueprintable)
struct FRepNode
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
		TArray<FVariables> Variables;
};
 
USTRUCT(BlueprintType, Blueprintable)
struct FResponseNode
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
		TArray<FVariables> Variables;
	UPROPERTY()
		TArray<FVariables> Variables_ToChange;
	UPROPERTY()
		bool IsRepeatOnce_Done = false;

};

USTRUCT(BlueprintType, Blueprintable)
struct FReplicNode
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
		TArray<FVariables> Variables;

	UPROPERTY()
		TArray<FRepNode> RepNode;
};

USTRUCT(BlueprintType, Blueprintable)
struct FSpeechNode
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
		TArray<FVariables> Variables;	

	UPROPERTY()
		FName Name;
	UPROPERTY()
		TArray<FReplicNode> ReplicNode;		 
	UPROPERTY()
		TArray<FResponseNode> ResponseNode;  
	UPROPERTY()
		bool IsRepeatOnce_Done = false;

};

USTRUCT(BlueprintType, Blueprintable)
struct FDialogNode
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
		FName Name;
	UPROPERTY()
		TArray<FSpeechNode> SpeechNode;
	
};

USTRUCT(BlueprintType, Blueprintable)
struct FDialogParameter
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
		TArray<FString> MissingVariablesStr;
	UPROPERTY()
		TArray<FDialogNode> DialogNode;
};