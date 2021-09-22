// Fill out your copyright notice in the Description page of Project Settings.


#include "WDisplayDialog.h"

#include "Fonts/FontMeasure.h"
#include "Blueprint/WidgetTree.h"

#include "Components/TextBlock.h"
//#include "Components/Overlay.h"
#include "Components/Border.h"
#include "Components/SizeBox.h"
#include "Components/VerticalBox.h"
#include "Components/HorizontalBox.h"
#include "Components/ScrollBox.h"
#include "Components/Image.h"

#include "Components/AudioComponent.h"

#include "WResponseButton.h"    //#include "Components/Button.h"



      

void UWDisplayDialog::NativeConstruct()
{
	Super::NativeConstruct();
	
}



void UWDisplayDialog::Init(ADLG_GlobalActor* _GlobagDialogActorRef, bool _Scrolling_dialog, bool _IsSpekerImage)
{
	GlobagDialogActorRef = _GlobagDialogActorRef;
	Scrolling_dialog = _Scrolling_dialog;
	IsSpekerImage = _IsSpekerImage;

	


	ShowReplicPanel(false);
	ShowResponsePanel(false);
}

void UWDisplayDialog::ParamsInit()
{

	ReplicPanelSize = ReplicBorder->GetCachedGeometry().GetLocalSize();  //  All replic zone size
	//ResponseBorderSize = ResponseBorder->GetCachedGeometry().GetLocalSize();  //  All Response zone size
	if (ReplicPanelSize.X != 0 )
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle_ParamsInit);
		DrawDialog(*ReplicToDraw, *ResponseToDraw);
	}
}


void UWDisplayDialog::ShowDialogPanel()
{
	ShowReplicPanel(true); 
	ShowResponsePanel(true);
}


void UWDisplayDialog::DrawDialog(TArray<FReplicToDraw>& _ReplicToDraw,
								TArray<FResponseToDraw>& _ResponseToDraw)
{
	ReplicToDraw = &_ReplicToDraw;
	ResponseToDraw = &_ResponseToDraw;

	if (!AudioComponentRef)
	{
		//   -------   EXIT Dialog  ----------
		StopDialog();
		return;
	}


	//   Image and NameText
	if (IsSpekerImage)
	{
		CurrentSpikerImage->SetVisibility(ESlateVisibility::Visible);
		CurrentSpekerName->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		CurrentSpikerImage->SetVisibility(ESlateVisibility::Collapsed);
		CurrentSpekerName->SetVisibility(ESlateVisibility::Collapsed);
	}


	   
	

	

	//   -------  Params Init  (Wait while widget panel generate size) ---------
	if (ReplicPanelSize.X == 0) 
	{
		GetWorld()->GetTimerManager().SetTimer(TimerHandle_ParamsInit, this, &UWDisplayDialog::ParamsInit, 0.2, true);
		return;
	}



	// Clear Response Panel
	while (ResponseButton.Num() > 0)
	{
			ResponseButton[0]->RemoveFromParent();
			ResponseButton.RemoveAt(0);
	}
	
	// Clear Replic Panel.  if (SCLOLLING == false)
	if (!Scrolling_dialog && 
		(*ReplicToDraw).Num() > 0) // last replic don't delete
	{
		while (ReplicsHorizontalBoxText.Num() > 0)
		{
			ReplicsScrollBox->RemoveChildAt(0);
			ReplicsHorizontalBoxText.RemoveAt(0);
		}
	}



	

	if ((*ReplicToDraw).Num() > 0)
	{

		//  --------  Spacer under Current Text   ------------
		if (BorderPaddingUnder) BorderPaddingUnder->RemoveFromParent();


		//  --------  New Speker's name and image  --------
		if (CurrentSpekerNameStr != (*ReplicToDraw)[0].SpekerName ||
			CurrentSpekerImage_Path != (*ReplicToDraw)[0].SpekerImagePath)
		{

			
			CurrentSpekerNameStr = (*ReplicToDraw)[0].SpekerName;
			CurrentSpekerName->SetText(FText::FromString((*ReplicToDraw)[0].SpekerName));
			CurrentSpekerName->SetFont(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), TextSize * 1.5f));

			if (Scrolling_dialog)
			{
				//---  Draw Empty stting     ///////////// ???????????????? NEED  ADD  Padding insted   ??????????????????????????????
				if (ReplicsScrollBox->GetChildrenCount() != 0)
				{
					UHorizontalBox* ReplicsHorizontalBoxTextTMP_ = WidgetTree->ConstructWidget<UHorizontalBox>(UHorizontalBox::StaticClass());
					ReplicsHorizontalBoxText.Add(ReplicsHorizontalBoxTextTMP_);
					UTextBlock* ReplicTextTMP_ = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
					ReplicTextTMP_->SetText(FText::FromString(FString(" ")));
					ReplicsHorizontalBoxText.Last()->AddChildToHorizontalBox(ReplicTextTMP_);
					ReplicsScrollBox->AddChild(ReplicsHorizontalBoxText.Last());
				}
				//---  Draw Name
				UHorizontalBox* ReplicsHorizontalBoxTextTMP = WidgetTree->ConstructWidget<UHorizontalBox>(UHorizontalBox::StaticClass());
				ReplicsHorizontalBoxText.Add(ReplicsHorizontalBoxTextTMP);
				UTextBlock* SpekerNameinReplic = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
				SpekerNameinReplic->SetFont(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), TextSize * 1.3f));
				SpekerNameinReplic->SetText(FText::FromString(CurrentSpekerNameStr));
				SpekerNameinReplic->SetColorAndOpacity(OpponentNameTextColor);
				ReplicsHorizontalBoxText.Last()->AddChildToHorizontalBox(SpekerNameinReplic);
				ReplicsScrollBox->AddChild(ReplicsHorizontalBoxText.Last());

			}

			  

			if (IsSpekerImage)
			{
				//--- image
				CurrentSpekerImage_Path = (*ReplicToDraw)[0].SpekerImagePath;
				UTexture2D* SpekerTexture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), 
															NULL, *((*ReplicToDraw)[0].SpekerImagePath)));
				CurrentSpikerImage->SetBrushFromTexture(SpekerTexture, false);
			}
			else
			{
				CurrentSpekerImage_Path = FString("none");
			}
		}
		//  ------------ 
		
			  
		
	
		//  ================  My ParseToArray() (with additional "space" and "\n") =================
		// (*ReplicToDraw)[0].ReplicTextStr.ParseIntoArray(TextStringArray, TEXT(" "), true); 
		TArray<FString> TextStringArray;
		DLG_ParseToArray(TextStringArray);
		



		////  ================= Make Vertical and Horisontal BoxStringsArray from FStringArray  =================
		float CurrentReplicSizeY = 0;
		CurrentReplicSizeY = MakeReplicLines(TextStringArray);
		

		//  ==================    Rep Delegate Activate  =============
		GlobagDialogActorRef->OnRepDrawn((*ReplicToDraw)[0].EventStr);
		



		//   ----------------	offset at DialogReplicPanel  bottom   ----------------
		if (ReplicPanelSize.Y > CurrentReplicSizeY)
		{
			//---  Bottom offset in ReplicScrollBox  ------------
			float newScrollOffset = ReplicPanelSize.Y - CurrentReplicSizeY;
			BorderPaddingUnder = WidgetTree->ConstructWidget<USizeBox>(USizeBox::StaticClass());;
			BorderPaddingUnder->SetHeightOverride(newScrollOffset - TextSize / 2.3f);
			ReplicsScrollBox->AddChild(BorderPaddingUnder);
			ReplicsScrollBox->ScrollToEnd();
		}
		//----------------------------------------------
	  



		
		//++++USoundBase* MySoundWave = LoadObject<USoundBase>(this, TEXT("/Game/VoiceSound/Dialog_Test.Dialog_Test"));
		//++++++AudioComponent->SetSound(MySoundWave);
		//+++++AudioComponent->Play();
		//++++if(AudioComponent->IsPlaying())	AudioComponent->Stop();

		//AudioComponent = UGameplayStatics::SpawnSoundAttached(
							//MySoundWave, MeshComp, NAME_None,
							//FVector(ForceInit), EAttachLocation::KeepRelativeOffset,
							//true
		//);

		//++float length = MySoundWave->Duration;
		//UGameplayStatics::PlaySoundAtLocation(this, MySoundWave, ActorSpeker->GetActorLocation());
		//UGameplayStatics::PlaySound2D(this, MySoundWave);

		//USoundBase* MySoundWave = LoadObject<USoundBase>(this, TEXT("/Game/VoiceSound/DialogRUS_Test.DialogRUS_Test"));
		USoundBase* MySoundWave = LoadObject<USoundBase>(this, *(*ReplicToDraw)[0].SoundPath);
		if (MySoundWave)
		{
			AudioComponentRef->SetSound(MySoundWave);
			AudioComponentRef->Play();               //    At Location   7777777777777777777777777777
			//++++if(AudioComponent->IsPlaying())	AudioComponent->Stop();




			//  ===============   Set time Delay   ======================

			if ((*ReplicToDraw)[0].Time == FString("sound_length"))
			{
				float time;
				//if ((*ReplicToDraw)[0].SoundPath == FString("none"))
				//{
				//	time = (*ReplicToDraw)[0].ReplicTextStr.Len() * SoundingSymbolLanght + 1.f;  //   if no sound
				//}
				//else
				//{
					time = MySoundWave->GetDuration();
				//}
				ReplicDelayTime = time + (*ReplicToDraw)[0].Delay;
				GetWorld()->GetTimerManager().SetTimer(TimerHandle_ReplicDelay, this, &UWDisplayDialog::ReplicDelay, ReplicDelayTime, false);
			}
			else if ((*ReplicToDraw)[0].Time != FString("while_press"))
			{
				float time = FCString::Atof(*(*ReplicToDraw)[0].Time);
				ReplicDelayTime = time + (*ReplicToDraw)[0].Delay;
				// ------- if has number of lenght but == 0  -------
				if (ReplicDelayTime == 0) ReplicDelayTime = (*ReplicToDraw)[0].ReplicTextStr.Len() * SoundingSymbolLanght + 1.f;
				GetWorld()->GetTimerManager().SetTimer(TimerHandle_ReplicDelay, this, &UWDisplayDialog::ReplicDelay, ReplicDelayTime, false);
			}

		}
		else
		{

			 
			float time = FCString::Atof(*(*ReplicToDraw)[0].Time);
			ReplicDelayTime = time + (*ReplicToDraw)[0].Delay;

			//  ---------------  dont have saund      OR    seted sound length   ----------------
			if (ReplicDelayTime == 0 || (*ReplicToDraw)[0].SoundPath == FString("none"))
				ReplicDelayTime = (*ReplicToDraw)[0].ReplicTextStr.Len() * SoundingSymbolLanght + 1.f;
			GetWorld()->GetTimerManager().SetTimer(TimerHandle_ReplicDelay, this, &UWDisplayDialog::ReplicDelay, ReplicDelayTime, false);
		}
	


		(*ReplicToDraw).RemoveAt(0);

		ReplicsScrollBox->ScrollToEnd();
		return;
	}
	 




	  


	//  Draw Response Panel
	if ((*ResponseToDraw).Num() > 0)
	{
		for (int32 i = 0; i < (*ResponseToDraw).Num(); i++)
		{
			if (ResponseButtonClassBP && GlobagDialogActorRef)  
			{
				//  ------------    Check if has Response with ReturnParrameter "Pass"   --------------
				if ((*ResponseToDraw)[i].ResponseReturn == EResponseReturn::pass_link_once ||
					(*ResponseToDraw)[i].ResponseReturn == EResponseReturn::pass_link_back ||
					(*ResponseToDraw)[i].ResponseReturn == EResponseReturn::pass_link_noreplic)
				{
					GlobagDialogActorRef->ChangeVariables((*ResponseToDraw)[i]);

					//  ------------    if just one Response    --------------  ==>  AutoTransfer
					if ((*ResponseToDraw).Num() == 1)
					{
						GlobagDialogActorRef->GenerateDialog((*ResponseToDraw)[i].ResponseReturn,
							(*ResponseToDraw)[i].LinkDialog.ToString(),
							(*ResponseToDraw)[i].LinkSpeech.ToString());
							return;
					}
					else   //==> Spend this Response
					{
						continue;
					}

				}

				 
				// ====================     Draw Response     =====================
				UWResponseButton* ResponseBtnTMP = CreateWidget<UWResponseButton>(this, ResponseButtonClassBP);
				///UWResponseButton* ResponseBtnTMP = WidgetTree->ConstructWidget<UWResponseButton>(UWResponseButton::StaticClass());
				ResponseBtnTMP->init(GlobagDialogActorRef, this, (*ResponseToDraw)[i]);
				//ResponseBtnTMP->//
				ResponseButton.Add(ResponseBtnTMP);   

				//++              777777777777777777777777777777              MABE DON'T ADD TO SCROLL
				ResponseScrollBox->AddChild(ResponseBtnTMP);   
			}
		}
	}
	else
	{
		//   -------   EXIT Dialog  ----------
		StopDialog();
	}
}


void UWDisplayDialog::DrawResponseAsReplic(FString sText)
{

	if (Scrolling_dialog)
	{

		//  --------  Spacer under Current Text   ------------
		if (BorderPaddingUnder) BorderPaddingUnder->RemoveFromParent();


		//   ----------------  Player name. Own or other  ------------------
		FString ActualPlayername = FString("None");
		if (GlobagDialogActorRef->OtherPlayerName == FName("none"))	ActualPlayername = GlobagDialogActorRef->PlayerName.ToString();
		else ActualPlayername = GlobagDialogActorRef->OtherPlayerName.ToString();


		//  -----------   String to draw (response as Raplic)   -------------
		FReplicToDraw ReplicToDrawTMP;
		//ReplicToDrawTMP.SpekerName = ActualPlayername;
		CurrentSpekerNameStr = ActualPlayername;
		ReplicToDrawTMP.ReplicTextStr = sText;
		(*ReplicToDraw).Add(ReplicToDrawTMP);

	
		//---  Draw Empty stting     ///////////// ???????????????? NEED  ADD  Padding insted   ??????????????????????????????
		if (ReplicsScrollBox->GetChildrenCount() != 0)
		{
			UHorizontalBox* ReplicsHorizontalBoxTextTMP_ = WidgetTree->ConstructWidget<UHorizontalBox>(UHorizontalBox::StaticClass());
			ReplicsHorizontalBoxText.Add(ReplicsHorizontalBoxTextTMP_);
			UTextBlock* ReplicTextTMP_ = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
			ReplicTextTMP_->SetText(FText::FromString(FString(" ")));
			ReplicsHorizontalBoxText.Last()->AddChildToHorizontalBox(ReplicTextTMP_);
			ReplicsScrollBox->AddChild(ReplicsHorizontalBoxText.Last());
		}
		//---  Draw Name
		UHorizontalBox* ReplicsHorizontalBoxTextTMP = WidgetTree->ConstructWidget<UHorizontalBox>(UHorizontalBox::StaticClass());
		ReplicsHorizontalBoxText.Add(ReplicsHorizontalBoxTextTMP);
		UTextBlock* SpekerNameinReplic = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
		SpekerNameinReplic->SetFont(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), TextSize * 1.3f));
		SpekerNameinReplic->SetText(FText::FromString(CurrentSpekerNameStr));
		SpekerNameinReplic->SetColorAndOpacity(PlayerNameTextColor);
		ReplicsHorizontalBoxText.Last()->AddChildToHorizontalBox(SpekerNameinReplic);
		ReplicsScrollBox->AddChild(ReplicsHorizontalBoxText.Last());


		//  ================  My ParseToArray() (with additional "space" and "\n") =================
		// (*ReplicToDraw)[0].ReplicTextStr.ParseIntoArray(TextStringArray, TEXT(" "), true); 
		TArray<FString> TextStringArray;
		DLG_ParseToArray(TextStringArray);

		////  ================= Make Vertical and Horisontal BoxStringsArray from FStringArray  =================
		float CurrentReplicSizeY = 0;
		CurrentReplicSizeY = MakeReplicLines(TextStringArray);

		//   ----------------	offset at DialogReplicPanel  bottom   ----------------
		if (ReplicPanelSize.Y > CurrentReplicSizeY)  
		{
			//---  Bottom offset in ReplicScrollBox  ------------
			float newScrollOffset = ReplicPanelSize.Y - CurrentReplicSizeY;
			BorderPaddingUnder = WidgetTree->ConstructWidget<USizeBox>(USizeBox::StaticClass());;
			BorderPaddingUnder->SetHeightOverride(newScrollOffset - TextSize / 2.3f);
			ReplicsScrollBox->AddChild(BorderPaddingUnder);
			ReplicsScrollBox->ScrollToEnd();
		}
		//----------------------------------------------



		(*ReplicToDraw).Empty();

	}
	


	//UE_LOG(LogTemp, Warning, TEXT("REsponse TEXT   %s"), *sText);
}


void UWDisplayDialog::ReplicDelay()
{
	DrawDialog(*ReplicToDraw, *ResponseToDraw);
}

void UWDisplayDialog::StopDialog()
{
	//doOffsetReplicScroll = false;

	// Clear Response Panel
	while (ResponseButton.Num() > 0)
	{
		ResponseButton[0]->RemoveFromParent();
		ResponseButton.RemoveAt(0);
	}

	//++++++++ Clear Replic Panel          
	/*while (ReplicsText.Num() > 0)
	{
		ReplicsText[0]->RemoveFromParent();
		ReplicsText.RemoveAt(0);
	}*/

	CurrentSpikerImage->SetVisibility(ESlateVisibility::Collapsed);
	CurrentSpekerName->SetVisibility(ESlateVisibility::Collapsed);

	ShowReplicPanel(false);
	ShowResponsePanel(false);	
}



void UWDisplayDialog::DLG_ParseToArray(TArray<FString>& TextStringArray)
{
	//  ================  My ParseToArray() (with additional "space" and "\n") =================
		/// (*ReplicToDraw)[0].ReplicTextStr.ParseIntoArray(TextStringArray, TEXT(" "), true); // Breack text
	//TArray<FString> TextStringArray;
	int32 Space_Symbol = (*ReplicToDraw)[0].ReplicTextStr.Find(" ",
			ESearchCase::Type::IgnoreCase, ESearchDir::Type::FromStart, 0);
	int32 startMid = 0;
	while (Space_Symbol != -1)
	{
		int32 CoundMid = Space_Symbol - startMid;
		TextStringArray.Add((*ReplicToDraw)[0].ReplicTextStr.Mid(startMid, CoundMid));
		//--- check if last Added element has "\n"	
		{int32 n_Symbol = TextStringArray.Last().Find("\n",
			ESearchCase::Type::IgnoreCase, ESearchDir::Type::FromStart, 0);
		while (n_Symbol != -1)
		{
			FString StrTMP = TextStringArray.Last();
			if (StrTMP == FString("\n")) break;
			TextStringArray.Last() = StrTMP.Mid(0, n_Symbol);
			TextStringArray.Add(FString("\n"));
			if (StrTMP.Len() > n_Symbol + 1)
			{
				TextStringArray.Add(StrTMP.Mid(n_Symbol + 1, StrTMP.Len() - n_Symbol + 1));
			}
			n_Symbol = TextStringArray.Last().Find("\n",
				ESearchCase::Type::IgnoreCase, ESearchDir::Type::FromStart, 0);
		}}
		//--- check If more then one "space" forward
		int32 TMP = Space_Symbol;
		startMid = Space_Symbol;
		Space_Symbol = (*ReplicToDraw)[0].ReplicTextStr.Find(" ",
			ESearchCase::Type::IgnoreCase, ESearchDir::Type::FromStart, ++Space_Symbol);

		while (Space_Symbol != -1 && Space_Symbol - TMP == 1)
		{
			TMP = Space_Symbol;
			Space_Symbol = (*ReplicToDraw)[0].ReplicTextStr.Find(" ",
				ESearchCase::Type::IgnoreCase, ESearchDir::Type::FromStart, ++Space_Symbol);
		}
	}
	//--- Add last element (if exist)
	int32 Lenght = (*ReplicToDraw)[0].ReplicTextStr.Len();
	int32 CoundMid = Lenght - startMid;
	if (CoundMid > 0)
	{
		TextStringArray.Add((*ReplicToDraw)[0].ReplicTextStr.Mid(startMid, CoundMid));
	}
	//---    DELETE   "\n"-String
	for (int32 nSumbol = 0; nSumbol < TextStringArray.Num(); nSumbol++)
	{
		if (TextStringArray[nSumbol] == FString("\n"))
		{
			TextStringArray.RemoveAt(nSumbol);
			nSumbol--;
		}
	}
	//-----------------------------------
}


float UWDisplayDialog::MakeReplicLines(TArray<FString>& TextStringArray)
{
	//  ================= Make Vertical and Horisontal BoxStringsArray from FStringArray  =================
	float CurrentReplicSizeY = 0;  // diallog Text UnderOffset
	bool isNeedNewRow = true;
	FString AllNewString = FString("");
	for (int32 i = 0; i < TextStringArray.Num(); i++)
	{
		//---  New  UTextBlock
		UTextBlock* ReplicTextTMP = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
		ReplicTextTMP->SetFont(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), TextSize));

		FString StringTMP = TextStringArray[i];

		if (StringTMP == FString("\n") || isNeedNewRow)
		{
			//--- add previous HorizontalBox to VertialBox  
			if (ReplicsHorizontalBoxText.Num() > 0 && ReplicsHorizontalBoxText.Last()->GetChildrenCount() > 0 && i != 0)
			{
				ReplicsScrollBox->AddChild(ReplicsHorizontalBoxText.Last());
			}
			//--- create new HorizontalBox ~~ NewStringLine
			UHorizontalBox* ReplicsHorizontalBoxTextTMP = WidgetTree->ConstructWidget<UHorizontalBox>(UHorizontalBox::StaticClass());
			ReplicsHorizontalBoxText.Add(ReplicsHorizontalBoxTextTMP);
			AllNewString = FString("");
			isNeedNewRow = false;

			//---  Get Text Height for forming BottomPadding in ReplicScrollBox
			TSharedRef<FSlateFontMeasure> WFontSize_TMP = (FSlateApplication::Get().GetRenderer()->GetFontMeasureService());
			FVector2D FontSizeTMP = WFontSize_TMP->Measure(AllNewString, ReplicTextTMP->Font);
			CurrentReplicSizeY += FontSizeTMP.Y;
		}
		AllNewString += StringTMP;   //  "AllNewString" -- need for check text Horizontal size in one line

		//---  Get Text size
		TSharedRef<FSlateFontMeasure> PaddingUnder = (FSlateApplication::Get().GetRenderer()->GetFontMeasureService());
		FVector2D TextSizeTMP = PaddingUnder->Measure(AllNewString, ReplicTextTMP->Font);

		//--  if string with next word fit in cutrrent string =>> add it
		if (TextSizeTMP.X < ReplicPanelSize.X - TextSize / 5)
		{
			if (StringTMP != FString("\n")) {
				ReplicTextTMP->SetText(FText::FromString(StringTMP));
				ReplicTextTMP->SetColorAndOpacity(TextColor);
				ReplicsHorizontalBoxText.Last()->AddChildToHorizontalBox(ReplicTextTMP);
			}
		}
		//--- else create new string
		else
		{
			isNeedNewRow = true;
			i--;                // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!       ERROR when Wery long WORD
		}				       //    !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!  !!!!!!!!!!!!!!!!!	
	}
	ReplicsScrollBox->AddChild(ReplicsHorizontalBoxText.Last());

	return CurrentReplicSizeY;
}








// ------  Space =>>  Next Replic  ------
void UWDisplayDialog::KeyMouseLeftDown()
{
	if (GetWorld()->GetTimerManager().IsTimerActive(TimerHandle_ReplicDelay))
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle_ReplicDelay);
	}
	DrawDialog(*ReplicToDraw, *ResponseToDraw);
}
// ------  Space =>>  Next Replic  ------
void UWDisplayDialog::KeySpace()
{
	if (GetWorld()->GetTimerManager().IsTimerActive(TimerHandle_ReplicDelay))
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle_ReplicDelay);	
	}
	DrawDialog(*ReplicToDraw, *ResponseToDraw);
}

// ------  Escape =>>  Exit Dialog  ------
void UWDisplayDialog::KeyEscape()
{
	StopDialog();
}













/////////////=======================		Not USE now		  ========================



void UWDisplayDialog::OnShowReplicPanel_Implementation(UPARAM(ref) bool& Show, UPARAM(ref) FString& s)
{

}
void UWDisplayDialog::ShowReplicPanel(bool Show)
{

	if (Show)ReplicBorder->SetVisibility(ESlateVisibility::Visible);   //   Collapsed,  Hidden,  Visible  
	else ReplicBorder->SetVisibility(ESlateVisibility::Collapsed);
																
	//OnShowReplicPanel(Show, Replic);           //  For flexible logic
}


void UWDisplayDialog::OnShowResponsePanel_Implementation(UPARAM(ref) bool& Show, UPARAM(ref) FString& s)
{

}
void UWDisplayDialog::ShowResponsePanel(bool Show)
{
	if (Show) ResponseBorder->SetVisibility(ESlateVisibility::Visible);   //   Collapsed,  Hidden,  Visible  
	else ResponseBorder->SetVisibility(ESlateVisibility::Collapsed);


}


