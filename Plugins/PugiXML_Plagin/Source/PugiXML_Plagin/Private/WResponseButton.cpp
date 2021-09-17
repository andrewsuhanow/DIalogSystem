// Fill out your copyright notice in the Description page of Project Settings.


#include "WResponseButton.h"


#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/SizeBox.h"


#include "DLG_GlobalActor.h"


/*
UWResponseButton::UWResponseButton(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}
*/


void UWResponseButton::NativeConstruct()
{
	Super::NativeConstruct();

	ResponseButton->OnReleased.AddDynamic(this, &UWResponseButton::OnClick);

	//ActionButtonClicked.BindUObject(this, &AFreeCamerController::ActionButtonClicked);
}


void UWResponseButton::OnClick()
{

	//  ----------    CHange Response's variavles   ---------------
	GlobagDialogActorRef->ChangeVariables(*CurrentResponse);
	 
	///  ----------    Call Delegate (OnChangeVariables)   ---------------
	///OnVariableChange

	//  ----------    if ResponseReturnMose "Exit"   =>>   Finish dialog   ------------
	if ((*CurrentResponse).ResponseReturn == EResponseReturn::exit)
	{
		GlobagDialogActorRef->DLG_StopDialog();
	}


	//   777777777777777777777777777777777777777777777777777777777777777777777777777777777
	//   777777777777777777777777777777777777777777777777777777777777777777777777777777777
	//				 Referens      (make in DlgGlobalActor, in Response)       !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//   777777777777777777777777777777777777777777777777777777777777777777777777777777777
	//   777777777777777777777777777777777777777777777777777777777777777777777777777777777
	// Set Response as Done  (if type "onse")
	//(*DialogParameter).DialogNode[i_Dlg].SpeechNode[i_Speech].ResponseNode[i_Response].IsRepeatOnce_Done = true
	if ((*CurrentResponse).ResponseNodeRef)
	//if ((*CurrentResponse).ResponseNodeRef.Get())
	{
		//(*CurrentResponse).ResponseNodeRef.Get()->IsRepeatOnce_Done = true;
		(*CurrentResponse).ResponseNodeRef->IsRepeatOnce_Done = true;
	}

	if ((*CurrentResponse).ResponseReturn != EResponseReturn::click_link_noreplic &&
		(*CurrentResponse).ResponseReturn != EResponseReturn::pass_link_noreplic)
	{
		WDisplayDialog->DrawResponseAsReplic((*CurrentResponse).str);
	}


	//  -----------    Generate next DialogStep  --------------------
	GlobagDialogActorRef->GenerateDialog((*CurrentResponse).ResponseReturn, 
											(*CurrentResponse).LinkDialog.ToString(),
											(*CurrentResponse).LinkSpeech.ToString());
	///UE_LOG(LogTemp, Warning, TEXT("YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY '%s'"), *(*CurrentResponse).str);

}



void UWResponseButton::init(ADLG_GlobalActor*& _GlobagDialogActorRef, UWDisplayDialog* _WDisplayDialog, FResponseToDraw& _CurrentResponse)
{
	GlobagDialogActorRef = _GlobagDialogActorRef;
	WDisplayDialog = _WDisplayDialog;
	CurrentResponse = &_CurrentResponse;

	ResponseText->SetText(FText::FromString((*CurrentResponse).str));
}









/*
	Ix_InGlobalCommandArray = _Ix_InGlobalCommandArray;
	Ix_InSharedCommandArray = _Ix_InSharedCommandArray;
	//ComandButtonType = _ComandButtonType;

	FreeCameraControllerFef = _FreeCameraControllerRef;

	//  Set button Color
	if (CurrentActiveState)
	{
		ButtonStyle.Normal.TintColor = FSlateColor(FLinearColor(ButtobColor_ActivatedHold));
		ButtonStyle.Hovered.TintColor = FSlateColor(FLinearColor(ButtobColor_ActivatedHold));
		ButtonStyle.Pressed.TintColor = FSlateColor(FLinearColor(ButtobColor_ActivatedHold_Hovered));
	}
	else
	{
		ButtonStyle = ComandButton->WidgetStyle;
		ButtonStyle.Normal.TintColor = FSlateColor(FLinearColor(ButtobColor_Normal));
		ButtonStyle.Hovered.TintColor = FSlateColor(FLinearColor(ButtobColor_Hovered));
		ButtonStyle.Pressed.TintColor = FSlateColor(FLinearColor(ButtobColor_Pressed));
	}
	ButtonStyle.Disabled.TintColor = FSlateColor(FLinearColor(ButtobColor_Disabled));
	ComandButton->SetStyle(ButtonStyle);
}
*/
/*
void UWResponseButton::SatAsActivateHold(bool State)
{
	if (!State)
	{
		ButtonStyle.Normal.TintColor = FSlateColor(FLinearColor(ButtobColor_Normal));
		ButtonStyle.Hovered.TintColor = FSlateColor(FLinearColor(ButtobColor_Hovered));
		ButtonStyle.Pressed.TintColor = FSlateColor(FLinearColor(ButtobColor_Pressed));
	}
	else
	{
		ButtonStyle.Normal.TintColor = FSlateColor(FLinearColor(ButtobColor_ActivatedHold));
		ButtonStyle.Hovered.TintColor = FSlateColor(FLinearColor(ButtobColor_ActivatedHold));
		ButtonStyle.Pressed.TintColor = FSlateColor(FLinearColor(ButtobColor_ActivatedHold_Hovered));
	}
	ComandButton->SetStyle(ButtonStyle);

}*/