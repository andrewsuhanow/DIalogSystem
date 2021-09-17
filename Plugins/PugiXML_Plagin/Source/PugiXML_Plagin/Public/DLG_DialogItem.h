// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "DialogParameter.h"

#include "DLG_GlobalActor.h"

#include "DialogInterface.h"

#include "Components/AudioComponent.h"

#include "DLG_DialogItem.generated.h"




 









UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PUGIXML_PLAGIN_API UDLG_DialogItem : public UActorComponent, public IDialogInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDLG_DialogItem();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

//public:	
	// Called every frame
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;




public:


	UPROPERTY(BlueprintReadWrite, Category = "DialogSystem")
		class UAudioComponent* AudioComponentRef;          
	UFUNCTION(BlueprintCallable, Category = "DialogSystem")
		void SetAudioComponent(UAudioComponent* _AudioComponentRef);


	UPROPERTY()
		UClass* BP_GLobalActorClass;


	
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "DialogSystem")
		FString PathToFile = FString("Your dialog file.xml");      //   PATH TO DIALOG.XML (only end),   should be set in "DLGObjectCustomizationDetails.cpp"
	//UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "DialogSystem")
	//	FString FullPathToFile = FString("none"); //   FULL PATH TO DIALOG.XML ( ...Conntent/ + ...DIALOG.XML),
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
/////UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
//		virtual void StartDialog_Implementation() override;
//
//	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
//		void aaa() ;
//	virtual void aaa_Implementation() override;
//
//
//	//UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
//		void bbb_Implementation() ;
//	//virtual void bbb_Implementation() override;
//	//virtual void bbb_Internal();
//	//UFUNCTION()
//	//virtual void StartDialog_Implementation() override;
//
//	//virtual void GetActorAudioCompomemt(class UAudioComponent*& AudioComponent) override;
//  ----------------------------------------------   INTERFACE   ----------------------------------------------



	//UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Dialog settings")
	//--	TSubclassOf< class static ADLG_GlobalActor>   fffffffff;
};
