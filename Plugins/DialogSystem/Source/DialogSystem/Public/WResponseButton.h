// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "WDisplayDialog.h"
#include "DLG_GlobalActor.h"

#include "WResponseButton.generated.h"

class UButton;
class UTextBlock;
class USizeBox;


UCLASS()
class DIALOGSYSTEM_API UWResponseButton : public UUserWidget
{
	GENERATED_BODY()



public:

	UPROPERTY(meta = (BindWidget))
		UButton* ResponseButton;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* ResponseText;
	
	
	virtual void NativeConstruct() override;

	UPROPERTY()
		ADLG_GlobalActor* GlobagDialogActorRef = nullptr;
	UPROPERTY()
		UWDisplayDialog* WDisplayDialog = nullptr;

	FResponseToDraw *CurrentResponse;

	UFUNCTION()
		void init(class ADLG_GlobalActor*& _GlobagDialogActorRef, UWDisplayDialog* _WDisplayDialog, FResponseToDraw &_CurrentResponse);
	UFUNCTION()
		void OnClick();

};
