// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "DLG_GlobalActor.h"

#include "WDisplayDialog.generated.h"



//class UOverlay;
class UImage;
class UBorder;
class UVerticalBox;
class UHorizontalBox;
class USizeBox;
class UScrollBox;
class UTextBlock;
class UWResponseButton;



UCLASS()
class PUGIXML_PLAGIN_API UWDisplayDialog : public UUserWidget
{
	GENERATED_BODY()
	

public:

	virtual void NativeConstruct() override;

protected:

	//   ------------ Replics -------------
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UScrollBox* ReplicsScrollBox;
	UPROPERTY()
		TArray<UHorizontalBox*> ReplicsHorizontalBoxText;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UBorder* ReplicBorder;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		USizeBox* ReplicSizeBox;
//	UPROPERTY()
//		TArray<UVerticalBox*> FullReplicsBySpeker;
	//UPROPERTY()
	//	int32 TextStringsNum = 0;
	
	UPROPERTY()
		TArray<UTextBlock*> AllSpekersName;
	//UPROPERTY()
	//	bool doOffsetReplicScroll = true;
	//UPROPERTY()
	//	float SctollOffset = 0;
		//bool IsNewSpekerIsOld = false;
//	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
//		TArray<UTextBlock*> ReplicsText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "DialogSystem")
		float TextSize = 32.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "DialogSystem")
		float CurrentSpikerImageSize = 50.f;
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
	///	TArray <UBorder*> TextBorder;
	///UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Dialog (Read only)")
	///	TArray<FString> Replic;


	//   ------------ Response ------------
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UBorder* ResponseBorder;
	//UPROPERTY()
	//	FVector2D ResponseBorderSize;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UScrollBox* ResponseScrollBox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<UWResponseButton> ResponseButtonClassBP;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		TArray<UWResponseButton*> ResponseButton;
	//	TArray<UButton*> ResponseButton;
	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	//	TArray<UTextBlock*> ResponseText;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dialog (Read only)")
	//	TArray<FString> Response;


public:

	//   ------------ Use ------------

	UFUNCTION()
		void ShowDialogPanel();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dialog (Read only)")
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

	//UPROPERTY()
		TArray<FReplicToDraw> *ReplicToDraw;
	//UPROPERTY()
		TArray<FResponseToDraw> *ResponseToDraw;
	UPROPERTY()
		UAudioComponent* AudioComponentRef;

	UPROPERTY()
		FTimerHandle TimerHandle_ReplicDelay;
	UFUNCTION()
		void ReplicDelay();   // 7777777777777777777
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

	//UFUNCTION(BlueprintImplementableEvent)  
	//	void OnShowReplicPanel();
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
	
	
	//UFUNCTION()
	//	void DrawReplicPrepare();
	//UFUNCTION()
	//	void DrawResponsePrepare();


	
/*


	//UFUNCTION()
		//+++++++++++++++++++++++++++++++++++
	//	void DrawReplic(FString& XmlFileContent, FString& _LastDialog, FString& _LastSpeech,
	//										FString& _Replic, float _SoundDelay, ETransitType _TransitTypePlayingCategory);
	UFUNCTION()
		void DrawResponse(FString& _XmlFileContent, FString& _LastDialog, FString& _LastSpeech, 
											TArray<FString>& _Response, TArray<int32>& _ResponseIndex);


*/
	
public:

	//   --------  Base parameter  ---------
	UFUNCTION()
		void Init(ADLG_GlobalActor* _GlobagDialogActorRef, bool _Scrolling_dialog, bool _IsSpekerImage);
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dialog (Read only)")
		bool Scrolling_dialog = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dialog (Read only)")
		bool IsSpekerImage = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dialog (Read only)")
		float PhraseTimeWait_PerLetr = 0.2f;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UImage* CurrentSpikerImage;   
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* CurrentSpekerName;          //  Global name, Drawing Outside

	//++++++++++++void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	  
public:

	//   --------  for CallBack with DLG_GlobalActor  ---------
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dialog (Read only)")
		ADLG_GlobalActor* GlobagDialogActorRef = nullptr;
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dialog (Read only)")
	//	FString LastDialog; 
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dialog (Read only)")
	//	FString LastSpeech;
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dialog (Read only)")
	//	FString Replic; 
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dialog (Read only)")
	//	float SoundDelay;

	//FString* XmlFileContent;


	//	bool aaa = true;
};
