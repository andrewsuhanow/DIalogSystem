// Fill out your copyright notice in the Description page of Project Settings.


#include "WResponseButton.h"


#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/SizeBox.h"


#include "DLG_GlobalActor.h"

 

void UWResponseButton::NativeConstruct()
{
	Super::NativeConstruct();

	ResponseButton->OnReleased.AddDynamic(this, &UWResponseButton::OnClick);
}


void UWResponseButton::OnClick()
{

	//  ----------    CHange Response's variavles   ---------------
	GlobagDialogActorRef->ChangeVariables(*CurrentResponse);
	 
	//  ----------    if ResponseReturnMose "Exit"   =>>   Finish dialog   ------------
	if ((*CurrentResponse).ResponseReturn == EResponseReturn::exit)
	{
		GlobagDialogActorRef->DLG_StopDialog();
	}


	// Set Response as Done  (if type "onse")
	if ((*CurrentResponse).ResponseNodeRef)
	{
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

