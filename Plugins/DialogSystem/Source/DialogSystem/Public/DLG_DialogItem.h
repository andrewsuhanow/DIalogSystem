// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "DialogParameter.h"

#include "DLG_GlobalActor.h"

//#include "DialogInterface.h"

#include "Components/AudioComponent.h"

#include "DLG_DialogItem.generated.h"




 









UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )

class DIALOGSYSTEM_API UDLG_DialogItem : public UActorComponent//, public IDialogInterface
{
	GENERATED_BODY()

public:	

	UDLG_DialogItem();

protected:

	virtual void BeginPlay() override;




public:


	UPROPERTY(BlueprintReadWrite, Category = "DialogSystem")
		class UAudioComponent* AudioComponentRef;          
	UFUNCTION(BlueprintCallable, Category = "DialogSystem")
		void SetAudioComponent(UAudioComponent* _AudioComponentRef);


	UPROPERTY()
		UClass* BP_GLobalActorClass;


	
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "DialogSystem")
		FString PathToFile = FString("Your dialog file.xml");      //   PATH TO DIALOG.XML.   should be set in "DLGObjectCustomizationDetails.cpp"
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "DialogSystem")
		FDialogParameter DialogParameter;
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "DialogSystem")
		TArray<FName> LocalVariables;
	/*UPROPERTY()
		FString PathToFileRuntime = FString("none");*/

	UPROPERTY()
		FString XmlFileContent = FString("none");
	UPROPERTY()
		FString DefaultDialog = FString("DEFAULT");

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "DialogSystem")
		class ADLG_GlobalActor* DLG_GlobalActor;
	//UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Dialog settings")
	//	TSubclassOf<class AGameMode> CurrentGameMod;

	  
	UFUNCTION(BlueprintCallable)
		void InitDialog();
	UFUNCTION(BlueprintCallable)
		void PlayDialog(FName _PlayerName = FName("IfOtherName"));




	//  ==============================================   INTERFACE   ======================================

	//bool StartDialog_Implementation() override;

};
 