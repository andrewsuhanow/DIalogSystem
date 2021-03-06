// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "DLG_GlobalActor.h"

#include "WDisplayDialog.generated.h"



class UImage;
class UBorder;
class UVerticalBox;
class UHorizontalBox;
class USizeBox;
class UScrollBox;
class UTextBlock;
class UWResponseButton;

 

UCLASS()
class DIALOGSYSTEM_API UWDisplayDialog : public UUserWidget
{
	GENERATED_BODY()
	

public:

	virtual void NativeConstruct() override;

protected:

	//   ------------ Replics -------------
	UPROPERTY(meta = (BindWidget))
		UScrollBox* ReplicsScrollBox;
	UPROPERTY()
		TArray<UHorizontalBox*> ReplicsHorizontalBoxText;
	UPROPERTY(meta = (BindWidget))
		UBorder* ReplicBorder;
	UPROPERTY(meta = (BindWidget))
		USizeBox* ReplicSizeBox;

	
	UPROPERTY()
		TArray<UTextBlock*> AllSpekersName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "DialogSystem")
		float TextSize = 32.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "DialogSystem")
		float CurrentSpikerImageSize = 50.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "DialogSystem")
		float SoundingSymbolLanght = 0.04f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "DialogSystem")
		FSlateColor PlayerNameTextColor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "DialogSystem")
		FSlateColor OpponentNameTextColor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "DialogSystem")
		FSlateColor TextColor;
	UPROPERTY()
		USizeBox* BorderPaddingUnder;
	UPROPERTY()
		FString CurrentSpekerImage_Path = FString("none");
	UPROPERTY()
		FString CurrentSpekerNameStr = FString("none");


	//   ------------ Response ------------
	UPROPERTY(meta = (BindWidget))
		UBorder* ResponseBorder;
	UPROPERTY(meta = (BindWidget))
		UScrollBox* ResponseScrollBox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "DialogSystem")
		TSubclassOf<UWResponseButton> ResponseButtonClassBP;
	UPROPERTY(meta = (BindWidget))
		TArray<UWResponseButton*> ResponseButton;



public:

	//   ------------ Use ------------

	UFUNCTION()
		void ShowDialogPanel();

	UPROPERTY()
		bool iSDialogInProgress = false;
	UFUNCTION()
		void DrawDialog(TArray<FReplicToDraw> &_ReplicToDraw,
						TArray<FResponseToDraw> &_ResponseToDraw);
	UFUNCTION()
		void DrawResponseAsReplic(FString sText);

	UFUNCTION()
		void StopDialog();

	UFUNCTION()
		void KeyMouseLeftDown();
	UFUNCTION()
		void KeySpace();
	UFUNCTION()
		void KeyEscape();

	TArray<FReplicToDraw> *ReplicToDraw;
	TArray<FResponseToDraw> *ResponseToDraw;

	UPROPERTY()
		UAudioComponent* AudioComponentRef;

	UPROPERTY()
		FTimerHandle TimerHandle_ReplicDelay;
	UFUNCTION()
		void ReplicDelay();  
	UPROPERTY()
		float ReplicDelayTime = -1;
	//  ---  init parrams  ---
	UFUNCTION()
		void ParamsInit();
	UPROPERTY()
		FVector2D ReplicPanelSize = FVector2D(0,0);
	UPROPERTY()
		FTimerHandle TimerHandle_ParamsInit;

	UFUNCTION()
		void DLG_ParseToArray(TArray<FString>& TextStringArray);
	UFUNCTION()
		float MakeReplicLines(TArray<FString>& TextStringArray);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void OnShowReplicPanel(UPARAM(ref) bool& Show, UPARAM(ref) FString& s);
		void OnShowReplicPanel_Implementation(UPARAM(ref) bool& Show, UPARAM(ref) FString& s);
	UFUNCTION(BlueprintCallable)
		void ShowReplicPanel(bool Show = true);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void OnShowResponsePanel(UPARAM(ref) bool& Show, UPARAM(ref) FString& s);
		void OnShowResponsePanel_Implementation(UPARAM(ref) bool& Show, UPARAM(ref) FString& s);
	UFUNCTION(BlueprintCallable)
		void ShowResponsePanel(bool Show = true);
	
	
public:

	//   --------  Base parameter  ---------
	UFUNCTION()
		void Init(ADLG_GlobalActor* _GlobagDialogActorRef, bool _Scrolling_dialog, bool _IsSpekerImage);
	UPROPERTY()
		bool Scrolling_dialog = false;
	UPROPERTY()
		bool IsSpekerImage = false;
	UPROPERTY()
		float PhraseTimeWait_PerLetr = 0.2f;
	UPROPERTY(meta = (BindWidget))
		UImage* CurrentSpikerImage;   
	UPROPERTY(meta = (BindWidget))
		UTextBlock* CurrentSpekerName;          //  Global name, Drawing Outside
	  
public:

	//   --------  for CallBack with DLG_GlobalActor  ---------
	UPROPERTY()
		ADLG_GlobalActor* GlobagDialogActorRef = nullptr;

};
