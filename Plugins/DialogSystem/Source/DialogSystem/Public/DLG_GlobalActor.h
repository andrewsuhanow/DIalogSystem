// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "DialogParameter.h"



#include "DLG_GlobalActor.generated.h"





DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FDLGVariableChange, const TArray<FName>&, VariableName, 
																	const TArray<FName>&, LastValue,
																	const TArray<FName>&, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDLGReplicDrawn, const FString, EventStr);

USTRUCT(BlueprintType, Blueprintable)
struct FReplicToDraw
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
		FString SpekerName = FString("None");
	UPROPERTY()
		FString ReplicTextStr = FString("...");
	UPROPERTY()
		FString SpekerImagePath = FString("none"); 
	UPROPERTY()
		FString SoundPath = FString("none");
	UPROPERTY()
		FString EventStr = FString("RETURN_EVENT");
	UPROPERTY()
		FString Time = FString("none");
	UPROPERTY()
		float Delay = 0;   //  Time waiting after
};
 
USTRUCT(BlueprintType, Blueprintable)
struct FResponseToDraw
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
		FString str = FString("...");
	UPROPERTY()
		FName LinkDialog = FName("DEFAULT");
	UPROPERTY()
		FName LinkSpeech = FName("DEFAULT");
	UPROPERTY()
		EResponseReturn ResponseReturn = EResponseReturn::none;

	UPROPERTY()
		TArray<FString> VariableToChange_LocalOrGlobal;
	UPROPERTY()
		TArray<FString> VariableToChange_Name;
	UPROPERTY()
		TArray<FString> VariableToChange_Value;

	FResponseNode* ResponseNodeRef;
};


UCLASS()
class DIALOGSYSTEM_API ADLG_GlobalActor : public AActor
{
	GENERATED_BODY()
	

public:	
	// Sets default values for this actor's properties
	ADLG_GlobalActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:
	  
	UPROPERTY()
		class UAudioComponent* ReserveAudioComponent;          
	  
	UFUNCTION()
		void DLG_InitLocalVariables();
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "DialogSystem")
		TArray<FVariables> LVariablesStored;

		TMap<FName, FName> *GlobalVariable;
	UFUNCTION(BlueprintCallable, Category="DialogSystem")
		void SetGlobalVariablesMapRef(UPARAM(ref) TMap<FName, FName>& _GlobalVariable);
	UFUNCTION(BlueprintCallable, Category = "DialogSystem")
		void AddGlobalVar(FName _key, FName _value);
	UFUNCTION(BlueprintCallable, Category = "DialogSystem")
		FName GetGlobalVar(FName _key);
	 
	UPROPERTY()
		class UWDisplayDialog* DisplayDialog;
	UFUNCTION()
		void DLG_InitDialodWidget();

public:

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "DialogSystem")
		TSubclassOf<class UWDisplayDialog> DisplayDialog_BPClass;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "DialogSystem")
		bool Scrolling_dialog = false;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "DialogSystem")
		bool IsSpekerImage = false;
	
	UPROPERTY(BlueprintAssignable)
		FDLGVariableChange DLGVariableChange;       //  Response Delegate
	UFUNCTION(BlueprintCallable)
		void OnVariableChange(TArray<FName>& _VarName, TArray<FName>& _VarLastValue, TArray<FName>& _NewValue);
	UPROPERTY()
		TArray<FName> VarName;
	UPROPERTY()
		TArray<FName> VarLastValue;
	UPROPERTY()
		TArray<FName> NewValue;
	UPROPERTY(BlueprintAssignable)               //  Replic Delegate
		FDLGReplicDrawn DLGReplicDrawn;
	UFUNCTION(BlueprintCallable)
		void OnRepDrawn(FString _Event);

	//   =============  Dialog draw  ================
	UPROPERTY()
		AActor* ActorSpeker;
		FString* XmlFilePath;
		FDialogParameter* DialogParameter;
	 
	UPROPERTY()
		TArray<FReplicToDraw> ReplicsToDraw;
	UPROPERTY()
		TArray<FResponseToDraw> ResponsesToDraw;

	 
	UFUNCTION()
		void ChangeVariables(FResponseToDraw& _CurrentResponse);
	UFUNCTION()
		void DLG_StopDialog();
	UFUNCTION()
		void DLG_PlayDialog(AActor* _ActorSpeker,
							FName _PlayerName,
							UAudioComponent*& _AudioComponent,
							FString& _XmlFilePath,
							FDialogParameter& _DialogParameter);

	UFUNCTION()
		void GenerateDialog(EResponseReturn ResponseReturn = EResponseReturn::none,
								FString _NextDialogNode = FString("DEFAULT"),
								FString _NextSpeechNode = FString("DEFAULT"));

	UPROPERTY()
		FName PlayerName = FName("Noname");
	UPROPERTY()
		FName OtherPlayerName = FName("none");
	UFUNCTION(BlueprintCallable, Category = "DialogSystem")
		void SetPlayerName(FName Name) { PlayerName = Name; }
	UFUNCTION(BlueprintCallable, Category = "DialogSystem")
		FName GetPlayerName() { return PlayerName; };

	UPROPERTY()
		class UInputComponent* DialogInputComponent;
	UPROPERTY()
		class UInputComponent* StoredInputComponent;
	UFUNCTION()
		void KeyMouseLeftDown();
	UFUNCTION()
		void KeySpace();
	UFUNCTION()
		void KeyEscape();


};
