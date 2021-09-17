// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


//#include "DLG_GlobalActor.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "DialogParameter.h"



#include "DLG_GlobalActor.generated.h"





DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FDLGVariableChange, const TArray<FName>&, VariableName, 
																	const TArray<FName>&, LastValue,
																	const TArray<FName>&, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDLGReplicDrawn, const FString, EventStr);

//OnCanvasRenderTargetUpdate.Broadcast(Canvas, GetSurfaceWidth(), GetSurfaceHeight());

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

	//UPROPERTY()
	//TSharedPtr<bool> IsActivateDone;
	//TSharedPtr<FResponseNode> ResponseNodeRef;
	FResponseNode* ResponseNodeRef;
};


UCLASS()
class PUGIXML_PLAGIN_API ADLG_GlobalActor : public AActor
{
	GENERATED_BODY()
	





		//UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Dialog settings")
		//UTexture2D* TTTTTTTTTTT;



public:	
	// Sets default values for this actor's properties
	ADLG_GlobalActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:

	//   
	//UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Dialog settings")
	//	TMap<FName, FString> Avatar;

	UPROPERTY()
		class UAudioComponent* ReserveAudioComponent;          
	
	UFUNCTION()
		void DLG_InitLocalVariables();
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "DialogSystem")
		TArray<FName> LocalVariables;
	//UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "DialogSystem")
		//TMap<FName, FName*> GlobalVariable;
		TMap<FName, FName> *GlobalVariable;
	UFUNCTION(BlueprintCallable, Category="DialogSystem")
		void SetGlobalVariablesMapRef(UPARAM(ref) TMap<FName, FName>& _GlobalVariable);
	UFUNCTION(BlueprintCallable, Category = "DialogSystem")
		void AddGlobalVar(FName _key, FName _value);
	UFUNCTION(BlueprintCallable, Category = "DialogSystem")
		FName GetGlobalVar(FName _key);
	//UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	//	void OnVariableSet(FName& key, FName& value);
		//void OnVariableSet(UPARAM(ref) FName& key, UPARAM(ref) FName& value);
		//void OnVariableSet_Implementation(UPARAM(ref) bool& Show, UPARAM(ref) FString& s);

	UPROPERTY()
		class UWDisplayDialog* DisplayDialog;
	UFUNCTION()
		void DLG_InitDialodWidget();
	//UFUNCTION()
	//	void DLG_GenerateDialog(FString &_LastDialog, FString &_LastSpeech, TArray<FString> &_Replic, 
	//							TArray<FString> &_Response, TArray<int32> &_ResponseIndex, bool isNew = false);

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
	//UFUNCTION(BlueprintCallable)
		//void aaa(TArray<FName> VarName, TArray<FName> VarLastValue, TArray<FName> NewValue);
	//   =============  Dialog draw  ================
	UPROPERTY()
		AActor* ActorSpeker;
	//UPROPERTY()
		FString* XmlFilePath;
	//UPROPERTY()
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
	/*UFUNCTION()
		void DLG_DrawResponseAsReplic(FString sText,
									EResponseReturn ResponseReturn = EResponseReturn::none,
									FString _NextDialogNode = FString("DEFAULT"),
									FString _NextSpeechNode = FString("DEFAULT"));

	*/



	//UPROPERTY(BlueprintReadWrite, Category = "DialogSystem")
	//	class UAudioComponent* AudioComponentRef;
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
