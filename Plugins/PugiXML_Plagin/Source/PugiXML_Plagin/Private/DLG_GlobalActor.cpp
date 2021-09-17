﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "DLG_GlobalActor.h"

#include "WDisplayDialog.h"

#include "PugiXML_Plagin/Include/pugixml.hpp"           //  PUGI
#include <sstream>   //  777777


#include "Interfaces/IPluginManager.h"

#include "GameFramework/PlayerController.h"  //  InputMode

#include "InputCoreTypes.h"          //InputComponent->BindKey(EKeys::

#include "Components/InputComponent.h"
#include "Components/AudioComponent.h"


//  TESt
//#include "DLG_DialogItem.h"


// Sets default values
ADLG_GlobalActor::ADLG_GlobalActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	DialogInputComponent = CreateDefaultSubobject<UInputComponent>(TEXT("DialogInputComponent"));
	//++AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	//AudioComponent->AttachParent = RootComponent;
	//++AudioComponent->bAutoActivate = true;



	//   --------------  reserve,   If AudioComponent not available ---------------
	ReserveAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	//AudioComponent->AttachParent = RootComponent;
	ReserveAudioComponent->bAutoActivate = true;

}


void ADLG_GlobalActor::BeginPlay()
{
	Super::BeginPlay();
	


	DialogInputComponent->BindKey(EKeys::LeftMouseButton, EInputEvent::IE_Pressed, this, &ADLG_GlobalActor::KeyMouseLeftDown);
	DialogInputComponent->BindKey(EKeys::SpaceBar, EInputEvent::IE_Pressed, this, &ADLG_GlobalActor::KeySpace);
	DialogInputComponent->BindKey(EKeys::Escape, EInputEvent::IE_Pressed, this, &ADLG_GlobalActor::KeyEscape);
	// Unbind
	//DialogInputComponent->BindKey(EKeys::RightMouseButton, EInputEvent::IE_Pressed, this, &ADLG_GlobalActor::UnbindDefaultKeys);

	DLG_InitDialodWidget();
	DLG_InitLocalVariables();

}



void ADLG_GlobalActor::DLG_InitDialodWidget()
{
	if (DisplayDialog_BPClass && GetWorld())
	{
		DisplayDialog = CreateWidget<UWDisplayDialog>(GetWorld(), DisplayDialog_BPClass, TEXT("DisplayDialog"));

		if (DisplayDialog)
		{
			DisplayDialog->Init(this, Scrolling_dialog, IsSpekerImage);
			DisplayDialog->AddToViewport();
		}
	}

}


void ADLG_GlobalActor::DLG_InitLocalVariables()
{
	//   ============   Get LocalVariables from .xml   ====================
	pugi::xml_document xmlVariables;

	FString LVariableXmlPath = FPaths::ProjectContentDir() + FString("Dialog/") + FString("LVariables.xml");
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	if (!PlatformFile.FileExists(*LVariableXmlPath)) return;

	//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXx
	//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXx
	//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXx
	//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXx
	//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXx
	//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXx
	//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXx
	//   ----------------  Parse XML in Pakage to string  ----------------------
	FString str_LocalVariablesContent;
	FFileHelper::LoadFileToString(str_LocalVariablesContent, *LVariableXmlPath);
	std::string std_LocalVariablesContent = (TCHAR_TO_UTF8(*str_LocalVariablesContent));
	//  -----------------  Load string as pugi   -------------------------------
	pugi::xml_parse_result parse_Res = xmlVariables.load(std_LocalVariablesContent.c_str());
	//pugi::xml_parse_result parse_VariablesRes = xmlVariables.load_file(StringCast<ANSICHAR>(*LVariableXmlPath).Get());
	if (!parse_Res)
	{
		UE_LOG(LogTemp, Warning, TEXT("can't parse  %s   ERROR"), *str_LocalVariablesContent);
		return;
	}


	//  Get Root Node
	pugi::xml_node VariableRootNode = xmlVariables.child("local_variables");
	VariableRootNode = xmlVariables.child("local_variables");

	LocalVariables.Empty();
	pugi::xpath_node_set DLG_Var = VariableRootNode.select_nodes("variable");
	for (int32 i_Variables = 0; i_Variables < DLG_Var.size(); i_Variables++)
	{
		std::string STD_VarValueStr(DLG_Var[i_Variables].node().attribute("value").as_string());	//   get attribute("value")
		std::wstring STD_W_VarValueStr = pugi::as_wide(STD_VarValueStr.c_str());
		FString VarValueStr(STD_W_VarValueStr.c_str());
		LocalVariables.Add(FName(*VarValueStr));
	}
	
}

   
void ADLG_GlobalActor::KeyMouseLeftDown()
{
	DisplayDialog->KeyMouseLeftDown();
	UE_LOG(LogTemp, Warning, TEXT("DialogSystem: KeyMouseLeftDown()"));
}
void ADLG_GlobalActor::KeySpace()
{
	DisplayDialog->KeySpace();
	UE_LOG(LogTemp, Warning, TEXT("DialogSystem: KeySpace()"));
}
void ADLG_GlobalActor::KeyEscape()
{
	DisplayDialog->KeyEscape();
	UE_LOG(LogTemp, Warning, TEXT("DialogSystem: KeyEscape()"));
}


void ADLG_GlobalActor::DLG_PlayDialog(AActor* _ActorSpeker,
									FName _PlayerName,
									UAudioComponent*& _AudioComponent,
									FString& _XmlFilePath,
									FDialogParameter& _DialogParameter)
{
	ActorSpeker = _ActorSpeker;
	XmlFilePath = &_XmlFilePath;
	DialogParameter = &_DialogParameter;
	OtherPlayerName = _PlayerName;


	//  ----------  GameMode   Dialog  -----------------
	APlayerController* PC = Cast<APlayerController>(GEngine->GetFirstLocalPlayerController(GetWorld()));
	//PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);    //  #include "Kismet/GameplayStatics.h"
	if (!PC) return;	
	StoredInputComponent = PC->InputComponent;
	if(DialogInputComponent) PC->InputComponent = DialogInputComponent;
	//PC->InputComponent = StoredInputComponent;
	//PC->SetupInputComponent();
	
	PC->SetInputMode(FInputModeGameAndUI());   //  FInputModeGameAndUI(),   FInputModeUIOnly(),  FInputModeGameOnly()
	PC->bShowMouseCursor = true;
	//UWidgetBlueprintLibrary::SetInputMode_GameAndUI();
	//UWidgetBlueprintLibrary::SetInputMode_GameOnly();
	//UWidgetBlueprintLibrary::SetInputMode_UIOnly();




	if (_AudioComponent) DisplayDialog->AudioComponentRef = _AudioComponent;
		else DisplayDialog->AudioComponentRef = ReserveAudioComponent;

	if (DisplayDialog)
		DisplayDialog->ShowDialogPanel();


	GenerateDialog();

}



void ADLG_GlobalActor::GenerateDialog(EResponseReturn _ResponseReturn,
										FString _NextDialogNode,
										FString _NextSpeechNode)
{
/*	//  ============================== Draw all Parameter ============================  ((( TEST )))

GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, FString::Printf(TEXT("%s"), *XmlFilePath));
UE_LOG(LogTemp, Warning, TEXT("replic-------: = '%s'"), *XmlFilePath);
for (int32 i = 0; i < DialogParameter.DialogNode.Num(); i++)
{
	UE_LOG(LogTemp, Warning, TEXT("DIALOG '%s'"), *DialogParameter.DialogNode[i].Name.ToString());
	for (int32 i1 = 0; i1 < DialogParameter.DialogNode[i].SpeechNode.Num(); i1++)
	{
		UE_LOG(LogTemp, Warning, TEXT("     SPEECH '%s'"), *DialogParameter.DialogNode[i].SpeechNode[i1].Name.ToString());
		for (int32 i1_1 = 0; i1_1 < DialogParameter.DialogNode[i].SpeechNode[i1].DLGVariable_Checking.Num(); i1_1++)
		{
			UE_LOG(LogTemp, Warning, TEXT("     SPEECH_CONDITION   '%s',   '%i',    '%s'"), *DialogParameter.DialogNode[i].SpeechNode[i1].DLGVariable_Checking[i1_1].NameGlobalVar.ToString(),
																	DialogParameter.DialogNode[i].SpeechNode[i1].DLGVariable_Checking[i1_1].IndexLocalVar,
																	*DialogParameter.DialogNode[i].SpeechNode[i1].DLGVariable_Checking[i1_1].Value.ToString());
		}
		for (int32 i1_2 = 0; i1_2 < DialogParameter.DialogNode[i].SpeechNode[i1].ReplicNode.Num(); i1_2++)
		{
			for (int32 i1_2_1 = 0; i1_2_1 < DialogParameter.DialogNode[i].SpeechNode[i1].ReplicNode[i1_2].DLGVariable_Checking.Num(); i1_2_1++)
			{
				UE_LOG(LogTemp, Warning, TEXT("     REOLIC_CONDITION   '%s',   '%i',    '%s'"), *DialogParameter.DialogNode[i].SpeechNode[i1].ReplicNode[i1_2].DLGVariable_Checking[i1_2_1].NameGlobalVar.ToString(),
																								DialogParameter.DialogNode[i].SpeechNode[i1].ReplicNode[i1_2].DLGVariable_Checking[i1_2_1].IndexLocalVar,
																								*DialogParameter.DialogNode[i].SpeechNode[i1].ReplicNode[i1_2].DLGVariable_Checking[i1_2_1].Value.ToString());	
			}
		}
	}
}
*/


	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
//  ================================  Get xmlDialog Content ====================
	pugi::xml_document xmlDoc;

	//IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	if (!PlatformFile.FileExists(**XmlFilePath)) return;




	//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXx
	//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXx
	//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXx
	//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXx
	//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXx   +++++++++++++++++++++++++++
	//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXx
	//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXx
	//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXx
	//   ----------------------   Content fron XML   ----------------------
	//   ----------------  Parse XML in Pakage to string  ----------------------
	FString str_DlgFileContent;
	FFileHelper::LoadFileToString(str_DlgFileContent, **XmlFilePath);
	std::string std_DlgFileContent = (TCHAR_TO_UTF8(*str_DlgFileContent));
	//  -----------------  Load string as pugi   -------------------------------
	pugi::xml_parse_result parse_Res = xmlDoc.load(std_DlgFileContent.c_str());
//	pugi::xml_parse_result parse_Res = xmlDoc.load_file(StringCast<ANSICHAR>(**XmlFilePath).Get());
	if (!parse_Res)
	{
		UE_LOG(LogTemp, Warning, TEXT("can't parse  %s   ERROR"), *str_DlgFileContent);
		return;
	}

	//  Get Root Node
	pugi::xml_node DialogRootNode = xmlDoc.child("name");
	
	//std::string RootNodeStr(RootNode.attribute("name").as_string());
//   ================================   Get LocalVariables from .xml   ====================
	pugi::xml_document xmlVariables;

	FString LVariableXmlPath = FPaths::ProjectContentDir() + FString("Dialog/") + FString("LVariables.xml");
	//IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	if (!PlatformFile.FileExists(*LVariableXmlPath)) return;



	//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
	//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
	//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
	//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx        Local Variables       7777777777777777777777
	//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
	//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
	//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
	//   ----------------  Parse XML in Pakage to string  ----------------------
	FString str_LocalVariablesContent;
	FFileHelper::LoadFileToString(str_LocalVariablesContent, *LVariableXmlPath);
	std::string std_LocalVariablesContent = (TCHAR_TO_UTF8(*str_LocalVariablesContent));
	//  -----------------  Load string as pugi   -------------------------------
	pugi::xml_parse_result parse_VariablesRes = xmlVariables.load(std_LocalVariablesContent.c_str());
	//pugi::xml_parse_result parse_VariablesRes = xmlVariables.load_file(StringCast<ANSICHAR>(*LVariableXmlPath).Get());
	if (!parse_VariablesRes)
	{
		UE_LOG(LogTemp, Warning, TEXT("can't parse  %s   ERROR"), *str_LocalVariablesContent);
		return;
	}

	//  Get Root Node
	pugi::xml_node VariableRootNode = xmlVariables.child("local_variables");
	


	 
	//  =========================  Check Node Condition AtAll  =======================
	auto CheckCondition = [&](pugi::xml_node _DlgBranchRootNode,      //  XXXXXXXXXXXXXXXXXXXXXXXXXXXXX   COPY OR REF
							pugi::char_t* NodeNameStr,
							TArray<FName>& _LocalVariables,
							pugi::xml_node _VariableRootNode,      //  XXXXXXXXXXXXXXXXXXXXXXXXXXXXX   COPY OR REF
							//TArray<int32>& _Checking_LocalVariable,
							TMap<FName, FName> *&_GlobalVariable)
	{

		// ==========================    CONDITION  ============================
		bool isCurrentNodeTest = true;
		TArray<std::string> Or_ToCheck;
		TArray<std::string> Or_ToIgnor;
		//std::wstring STD_W_NodeNameStr = pugi::as_wide(STD_NodeNameStr.c_str());
		pugi::xpath_node_set DLG_ConditionNode = _DlgBranchRootNode.select_nodes(NodeNameStr);
		for (int32 i_Condition = 0; i_Condition < DLG_ConditionNode.size(); i_Condition++)
		{
			// ======== Get Condition Type  (And/Or) =========
			std::string STD_TypeOrAnd_Str(DLG_ConditionNode[i_Condition].node().attribute("type").as_string()); // Attribute(Or/And)
			// ======== Get variable Type  (Local/Global) =========
			std::string STD_TypeLocalGlobal_Str(DLG_ConditionNode[i_Condition].node().attribute("var_type").as_string());  //   get attribute("Local/Global")
			// ======== Get variable Value =========
			std::string STD_VarValue_Str(DLG_ConditionNode[i_Condition].node().text().as_string());   //   get variable "Value"
			FString VarValue_Str(STD_VarValue_Str.c_str());
			// ======== Get variable Name =========
			std::string STD_VarName_Str(DLG_ConditionNode[i_Condition].node().attribute("var_name").as_string()); // Attribute(var_name)
			FString VarName_Str(STD_VarName_Str.c_str());

			// ======== Check if need ignore variable, becose "Or-type" and alredy "true" ========
			if (Or_ToIgnor.Contains(STD_TypeOrAnd_Str)) continue;

			bool isCurrentConditionTest = true;

			// ==============   "global"   ===================
			if (STD_TypeLocalGlobal_Str == "global")
			{
				// ========  Compare with 'GlobalVariable_value'  =========
				// ------- Find "Variable" in global by "Name" -------
				FName* GlobalValueRef = (*_GlobalVariable).Find(FName(*VarName_Str));
				if (GlobalValueRef) 
				{
					FName realGlobalVariable_value = *GlobalValueRef;
					if (FName(*VarValue_Str) != realGlobalVariable_value) isCurrentConditionTest = false;
				}
				else isCurrentConditionTest = false;
			}

			// ==============   "Local"   ===================
			else  
			{ 
				bool VariableIsAbsent = true;
				pugi::xpath_node_set XML_Var = VariableRootNode.select_nodes("variable");
				for (int32 i_Variables = 0; i_Variables < XML_Var.size(); i_Variables++)
				{
					//  name of local variable in LVariable_XmlFile
					std::string STD_XmlVarNameStr(XML_Var[i_Variables].node().attribute("name").as_string());	//   get attribute("name")

					if (STD_VarName_Str == STD_XmlVarNameStr)
					{
						VariableIsAbsent = false;

						//std::string STD_XmlVarValueStr(XML_Var[i_Variables].node().attribute("value").as_string());	//   get attribute("value")				
						if (VarValue_Str != _LocalVariables[i_Variables].ToString()) isCurrentConditionTest = false;
						//if (STD_VarValue_Str != STD_XmlVarValueStr) isCurrentConditionTest = false;
						break;
					}
				}
				if(VariableIsAbsent) isCurrentConditionTest = false;  // Variable is absent in LVariable_XmlFile
										 
			}

			//   And / Or   (result alredy have)
			if (!isCurrentConditionTest)
			{
				//  Result NOT correct
				if (STD_TypeOrAnd_Str == "and") isCurrentNodeTest = false;
				else if (!Or_ToCheck.Contains(STD_TypeOrAnd_Str)) Or_ToCheck.Add(STD_TypeOrAnd_Str);
			}
			else
			{
				//  Result correct
				if (STD_TypeOrAnd_Str == "and") continue;
				else if (Or_ToCheck.Contains(STD_TypeOrAnd_Str)) Or_ToCheck.Remove(STD_TypeOrAnd_Str);
				Or_ToIgnor.Add(STD_TypeOrAnd_Str);
			}

			if (!isCurrentNodeTest) break;
		}
		if (Or_ToCheck.Num() > 0) isCurrentNodeTest = false;

		return isCurrentNodeTest;
	};

	 

	auto GetAppropriateREP = [&](pugi::xml_node _DlgBranchRootNode, // REPLIC.node()  // XXXXXXXXXXXXXX   COPY OR REF
									pugi::char_t* NodeNameStr, 
									TArray<FName>& _LocalVariables,
									FReplicNode& ReplicNodeParam,
									TMap<FName, FName> *&_GlobalVariable,
									FReplicToDraw& ReplicsToDrawTMP_Ref)
	{
		TArray<int32> CorrectReps;
		pugi::xpath_node_set DLG_Rep = _DlgBranchRootNode.select_nodes(NodeNameStr);
		for (int32 i_Rep = 0; i_Rep < DLG_Rep.size(); i_Rep++)
		{
			bool isCurrentRepTest = CheckCondition(DLG_Rep[i_Rep].node(),
												"rep_condition",
												_LocalVariables,
												VariableRootNode,
												//ReplicNodeParam.RepNode[i_Rep].IndexLocalVar,
												_GlobalVariable);

			// -----------  if this "Rep" satisfy of condition =>> save it for further (random) Geting  ----------
			if (isCurrentRepTest) CorrectReps.Add(i_Rep);
		}

		int32 IndexOfChosedRep = 0;
		if (CorrectReps.Num() == 0) return false;  // if NOone "Reps" is alloud =>> spend "Replic"
		else
		{
			//  ---------    Get random Rep from allowed Rep   ----------
			IndexOfChosedRep = FMath::RandRange(0, CorrectReps.Num() - 1);
	
				
				std::string STD_ReturnTextStr(DLG_Rep[IndexOfChosedRep].node().text().as_string());   //  Get "Text" Value
				std::wstring STD_W_ReturnTextStr = pugi::as_wide(STD_ReturnTextStr.c_str());
				FString ReturnTextStr(STD_W_ReturnTextStr.c_str());
				ReturnTextStr.TrimStartAndEndInline();               //  remove \t \n
			ReplicsToDrawTMP_Ref.ReplicTextStr = ReturnTextStr;   //   Return Value "phrase Text"


				std::string STD_ReturnTimeStr(DLG_Rep[IndexOfChosedRep].node().attribute("time").as_string()); // Attribute(time)
				FString ReturnTimeStr(STD_ReturnTimeStr.c_str());
			ReplicsToDrawTMP_Ref.Time = ReturnTimeStr;           //   Return Value "time"


				std::string STD_ReturnDelayStr(DLG_Rep[IndexOfChosedRep].node().attribute("delay").as_string()); // Attribute(delay)
				FString ReturnDelayStr(STD_ReturnDelayStr.c_str());
			ReplicsToDrawTMP_Ref.Delay = FCString::Atof(*ReturnDelayStr);   //   Return Value "delay"
				

				std::string STD_ReturnEventStr(DLG_Rep[IndexOfChosedRep].node().attribute("event").as_string()); // Attribute(event)
				FString ReturnEventStr(STD_ReturnEventStr.c_str());
			ReplicsToDrawTMP_Ref.EventStr = ReturnEventStr;  //   Return Value "Event"


			//  -----------------  Get data from Speker.xml  -----------------
			std::string STD_RequiredSpekerNameStr(DLG_Rep[IndexOfChosedRep].node().attribute("speker").as_string()); // Attribute(speker)
			std::string STD_RequireSpekerSoundStr(DLG_Rep[IndexOfChosedRep].node().attribute("sound").as_string()); // Attribute(sound)

			pugi::xml_document xmlSpeker;
			FString SpekerXmlPath = FPaths::ProjectContentDir() + FString("Dialog/") + FString("Spekers.xml");
			IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();//----------
			if (!PlatformFile.FileExists(*SpekerXmlPath)) return false;//-------+++++

			//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
			//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
			//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
			//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
			//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
			//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
			//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
			//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
			//   ----------------  Parse XML in Pakage to string  ----------------------
			FString str_SpekerXmlContent;
			FFileHelper::LoadFileToString(str_SpekerXmlContent, *SpekerXmlPath);
			std::string std_SpekerXmlContent = (TCHAR_TO_UTF8(*str_SpekerXmlContent));
			//  -----------------  Load string as pugi   -------------------------------
			pugi::xml_parse_result parse_SpekerRes = xmlSpeker.load(std_SpekerXmlContent.c_str());
			//pugi::xml_parse_result parse_SpekerRes = xmlSpeker.load_file(StringCast<ANSICHAR>(*SpekerXmlPath).Get());
			if (!parse_SpekerRes)
			{
				UE_LOG(LogTemp, Warning, TEXT("can't parse  %s   ERROR"), *str_SpekerXmlContent);
				return false;
			}





			pugi::xml_node SpekerRootNode = xmlSpeker.child("game_spekers"); //  Get Root Node

			//  ----------  Found Required Speker  ----------
			pugi::xpath_node_set SpekerNode = SpekerRootNode.select_nodes("speker");
			for (int32 i_Speker = 0; i_Speker < SpekerNode.size(); i_Speker++)
			{

				std::string STD_CurrentSpekerName(SpekerNode[i_Speker].node().attribute("name").as_string());
				if (STD_CurrentSpekerName == STD_RequiredSpekerNameStr)
				{
					FString ReturnSpekerName(STD_CurrentSpekerName.c_str());
					ReplicsToDrawTMP_Ref.SpekerName = ReturnSpekerName;

					std::string STD_ReturnImagePath(SpekerNode[i_Speker].node().text().as_string());
					FString ReturnImagePath(STD_ReturnImagePath.c_str());
					ReturnImagePath.TrimStartAndEndInline();               //  remove \t \n
					ReplicsToDrawTMP_Ref.SpekerImagePath = ReturnImagePath;   //   Return Value "Image Path"


					//  ----------  Found Required Sound  ----------
					pugi::xpath_node_set SoundNode = SpekerNode[i_Speker].node().select_nodes("sound");
					for (int32 i_Sound = 0; i_Sound < SoundNode.size(); i_Sound++)
					{
						std::string STD_CurrentSpekerSound(SoundNode[i_Sound].node().attribute("name").as_string());
						if (STD_CurrentSpekerSound == STD_RequireSpekerSoundStr)
						{
							std::string STD_ReturnSoundPath(SoundNode[i_Sound].node().text().as_string());
							FString ReturnSoundPath(STD_ReturnSoundPath.c_str());
							ReturnSoundPath.TrimStartAndEndInline();               //  remove \t \n
							ReplicsToDrawTMP_Ref.SoundPath = ReturnSoundPath;   //   Return Value "Sound Path"
						}
					}
				}
			}
		}
		return true;
	};




	ReplicsToDraw.Empty();

	// ==========================    DIALOG  ============================
	bool ExtremalExit = false;
	pugi::xpath_node_set DLG_Dialog = DialogRootNode.select_nodes("dialog");
	for (int32 i_Dlg = 0; i_Dlg < DLG_Dialog.size(); ++i_Dlg)
	{
	std::string STD_DlgStr(DLG_Dialog[i_Dlg].node().attribute("dialog_name").as_string());  //   get attribute("dialog_name")
	FString DlgStr(STD_DlgStr.c_str());
	if (DlgStr == _NextDialogNode)
	{
		// ==========================    SPEECH  ============================
		bool IsSpeechNodeGenerate_ok = false;
		pugi::xpath_node_set DLG_Speech = DLG_Dialog[i_Dlg].node().select_nodes("speech");
		for (int32 i_Speech = 0; i_Speech < DLG_Speech.size(); ++i_Speech)
		{
		std::string STD_SpeechStr(DLG_Speech[i_Speech].node().attribute("speech_name").as_string());  //   get attribute("speech_name")
		FString SpeechStr(STD_SpeechStr.c_str());
		if (SpeechStr == _NextSpeechNode)
		{			
			//  ========================   Check "Speech" CONDITION  ===========================
			bool isCurrentSpeechTest = CheckCondition(DLG_Speech[i_Speech].node(),
											"speech_condition",
											LocalVariables,
											VariableRootNode,
											//(*DialogParameter).DialogNode[i_Dlg].SpeechNode[i_Speech].IndexLocalVar,
											GlobalVariable);

			//  ------  if desired "Speech" node don't pass requide test  ---------   
			//   =>>  go throught  "Speech(default -> default -> default...)" node or start from "DEFAULD"   ---  
			if (!isCurrentSpeechTest)
			{
				if (_NextSpeechNode != FString("DEFAULT"))
				{
					_NextSpeechNode = FString("DEFAULT");
					_ResponseReturn = EResponseReturn::click_link_back;
					i_Speech = -1;  // loop to begin (0)
				}					
				continue;
			}












			//  ============================  If  PROPERTY "NO-REPLIC" =>> PASS "Replik" zone  =========================
			if (_ResponseReturn != EResponseReturn::click_link_noreplic &&
				//_ResponseReturn != EResponseReturn::click_default_noreplic &&
				_ResponseReturn != EResponseReturn::pass_link_noreplic)
				//_ResponseReturn != EResponseReturn::pass_default_noreplic)
			{

				//  ======================  Check Replick Repeat mode  =========================

					std::string RequireReplicRepeat = "always";
					//EReplicRepeat RequireReplicRepeat = EReplicRepeat::always;

					if (_ResponseReturn == EResponseReturn::click_link_back ||
						//_ResponseReturn == EResponseReturn::click_default_back ||
						_ResponseReturn == EResponseReturn::pass_link_back)
						//_ResponseReturn == EResponseReturn::pass_default_back)
					{
						RequireReplicRepeat = "back";
						//RequireReplicRepeat = EReplicRepeat::back;
					}
					else if (_ResponseReturn == EResponseReturn::click_link_once ||
							 //_ResponseReturn == EResponseReturn::click_default_once ||
							 //_ResponseReturn == EResponseReturn::pass_default_once ||
							 _ResponseReturn == EResponseReturn::none ||
							 _ResponseReturn == EResponseReturn::pass_link_once)
					{
						if (!(*DialogParameter).DialogNode[i_Dlg].SpeechNode[i_Speech].IsRepeatOnce_Done)
							//RequireReplicRepeat = EReplicRepeat::once;
								RequireReplicRepeat = "once";
						else
							//RequireReplicRepeat = EReplicRepeat::after_once;
							RequireReplicRepeat = "after_once";
					}


				// ==========================    REPLIC   ============================

				pugi::xpath_node_set DLG_Replic = DLG_Speech[i_Speech].node().select_nodes("replic");
				for (int32 i_Replic = 0; i_Replic < DLG_Replic.size(); i_Replic++)
				{

					std::string STD_ReplicRepeatStr(DLG_Replic[i_Replic].node().attribute("repeat").as_string());  //   get attribute("repeat")
					//FString ReplicRepeatStr(STD_ReplicRepeatStr.c_str());

					// ===============  Check repet property:  (once/after_once/comeback), (always)  =================
					if(RequireReplicRepeat != STD_ReplicRepeatStr && STD_ReplicRepeatStr != "always") continue;
				
					//  ========================   CHECK "Replic" CONDITION  ===========================
					bool isCurrentReplicTest = CheckCondition(DLG_Replic[i_Replic].node(),
																"replic_condition",
																LocalVariables,
																VariableRootNode,
																//(*DialogParameter).DialogNode[i_Dlg].SpeechNode[i_Speech]
																//			.ReplicNode[i_Replic].IndexLocalVar,
																GlobalVariable);

					if (!isCurrentReplicTest) continue;
					else
					{
						FReplicToDraw ReplicsToDrawTMP;
						bool IsAlloudRepExist = GetAppropriateREP(DLG_Replic[i_Replic].node(),
												"rep",
												LocalVariables,
												(*DialogParameter).DialogNode[i_Dlg].SpeechNode[i_Speech]
																				.ReplicNode[i_Replic],
												GlobalVariable,
												ReplicsToDrawTMP);

						if (IsAlloudRepExist) ReplicsToDraw.Add(ReplicsToDrawTMP);
					}
				}

				 
				//  -----  if No-One "Replic" has satisfied conditions  -----  
				//   =>> goto next "Speech=(default -> default -> default...)" node or start from "DEFAULD"   ---
				if (ReplicsToDraw.Num() == 0)
				{
					if (_NextSpeechNode != FString("DEFAULT"))
					{
						_NextSpeechNode = FString("DEFAULT");
						_ResponseReturn = EResponseReturn::click_link_back;
						i_Speech = -1;   // loop to begin (0)
					}
					continue;
				}

				IsSpeechNodeGenerate_ok = true;

				//  -------   mark this "Replic" as using "after_once" next time   -------
				(*DialogParameter).DialogNode[i_Dlg].SpeechNode[i_Speech].IsRepeatOnce_Done = true;
			}



			// ==========================    RESPONSE   ============================

			ResponsesToDraw.Empty();

			pugi::xpath_node_set DLG_Response = DLG_Speech[i_Speech].node().select_nodes("response");
			for (int32 i_Response = 0; i_Response < DLG_Response.size(); i_Response++)
			{

				std::string STD_ResponseRepeatStr(DLG_Response[i_Response].node().attribute("repeat").as_string());  //   get attribute("repeat")
				//FString ResponseRepeatStr(STD_ResponseRepeatStr.c_str());


				// ===============  Check repet property:  (once / always)  =================
				if (STD_ResponseRepeatStr == "once" &&
					(*DialogParameter).DialogNode[i_Dlg].SpeechNode[i_Speech].ResponseNode[i_Response].IsRepeatOnce_Done)
				//if (STD_ResponseRepeatStr == "once")
				{
					if ((*DialogParameter).DialogNode[i_Dlg].SpeechNode[i_Speech].ResponseNode[i_Response].IsRepeatOnce_Done)	continue;
					//else (*DialogParameter).DialogNode[i_Dlg].SpeechNode[i_Speech].ResponseNode[i_Response].IsRepeatOnce_Done = true;
				}

				//  ========================   CHECK "Response" CONDITION  ===========================
				bool isCurrentResponseTest = CheckCondition(DLG_Response[i_Response].node(),
															"response_condition",
															LocalVariables,
															VariableRootNode,
															GlobalVariable);

				if (!isCurrentResponseTest) continue;
				else
				{
					FResponseToDraw ResponseToDrawTMP;


					//   777777777777777777777777777777777777777777777777777777777777777777777777777777777
					//   777777777777777777777777777777777777777777777777777777777777777777777777777777777
					//						 Referens      (use in WResponseButton)
					//   777777777777777777777777777777777777777777777777777777777777777777777777777777777
					//   777777777777777777777777777777777777777777777777777777777777777777777777777777777
					//FResponseNode * sssssssssss = &(*DialogParameter).DialogNode[i_Dlg].SpeechNode[i_Speech].ResponseNode[i_Response];
					// -------  if this response will activate =>> then set it as done
					ResponseToDrawTMP.ResponseNodeRef = &(*DialogParameter).DialogNode[i_Dlg].SpeechNode[i_Speech].ResponseNode[i_Response];
					//++++++ResponseToDrawTMP.ResponseNodeRef = MakeShared<FResponseNode>((*DialogParameter).DialogNode[i_Dlg].SpeechNode[i_Speech].ResponseNode[i_Response]);
					//---ResponseToDrawTMP.IsActivateDone = MakeShareable((*DialogParameter).DialogNode[i_Dlg].SpeechNode[i_Speech].ResponseNode[i_Response].IsRepeatOnce_Done);



						std::string STD_ResponseTextStr(DLG_Response[i_Response].node().text().as_string());
						std::wstring STD_W_ResponseTextStr = pugi::as_wide(STD_ResponseTextStr.c_str());
						FString ResponseTextStr(STD_W_ResponseTextStr.c_str());
						ResponseTextStr.TrimStartAndEndInline();               //  remove \t \n
					ResponseToDrawTMP.str = ResponseTextStr;

						std::string STD_ResponseDialogLinkStr(DLG_Response[i_Response].node().attribute("dialog_link").as_string());  //   get attribute("dialog_link")
						FString ResponseDialogLinkStr(STD_ResponseDialogLinkStr.c_str());
					ResponseToDrawTMP.LinkDialog = FName(*ResponseDialogLinkStr);
					
						std::string STD_ResponseSpeechLinkStr(DLG_Response[i_Response].node().attribute("speech_link").as_string());  //   get attribute("speech_link")
						FString ResponseSpeechLinkStr(STD_ResponseSpeechLinkStr.c_str());
					ResponseToDrawTMP.LinkSpeech = FName(*ResponseSpeechLinkStr);

						const std::string STD_ResponseReturnTypeStr(DLG_Response[i_Response].node().attribute("return_type").as_string());  //   get attribute("return_type")
					//if(STD_ResponseReturnTypeStr == "CLO (click_link_once)")
					if(STD_ResponseReturnTypeStr == "click")
						ResponseToDrawTMP.ResponseReturn = EResponseReturn::click_link_once;
					//else if(STD_ResponseReturnTypeStr == "CLR (click_link_return)")
					else if(STD_ResponseReturnTypeStr == "click_back")
						ResponseToDrawTMP.ResponseReturn = EResponseReturn::click_link_back;
					//else if(STD_ResponseReturnTypeStr == "CLN (click_link_noreplic)")
					else if(STD_ResponseReturnTypeStr == "click_noreplic")
						ResponseToDrawTMP.ResponseReturn = EResponseReturn::click_link_noreplic;

					else if(STD_ResponseReturnTypeStr == "pass")
						ResponseToDrawTMP.ResponseReturn = EResponseReturn::pass_link_once;
					//else if(STD_ResponseReturnTypeStr == "PLR (pass_link_return)")
					else if(STD_ResponseReturnTypeStr == "pass_back")
						ResponseToDrawTMP.ResponseReturn = EResponseReturn::pass_link_back;
					//else if(STD_ResponseReturnTypeStr == "PLN (pass_link_noreplic)")
					else if(STD_ResponseReturnTypeStr == "pass_noreplic")
						ResponseToDrawTMP.ResponseReturn = EResponseReturn::pass_link_noreplic;
					else //std::string("EXT (exit)")
						ResponseToDrawTMP.ResponseReturn = EResponseReturn::exit;
					


					// ==========================     RESPONSE    Variable_To_Change    ============================

					pugi::xpath_node_set DLG_ResponseCondition = DLG_Response[i_Response].node().select_nodes("change_variable");
					for (int32 i_ResponseCondition = 0; i_ResponseCondition < DLG_ResponseCondition.size(); i_ResponseCondition++)
					{

							std::string STD_ResponseVarTypeStr(DLG_ResponseCondition[i_ResponseCondition].node().attribute("var_type").as_string());  //   get attribute("var_type")
							FString ResponseVarTypeStr(STD_ResponseVarTypeStr.c_str());
						ResponseToDrawTMP.VariableToChange_LocalOrGlobal.Add(ResponseVarTypeStr);

							std::string STD_ResponseVarNameStr(DLG_ResponseCondition[i_ResponseCondition].node().attribute("var_name").as_string());  //   get attribute("var_name")

						if (ResponseVarTypeStr == FString("global"))
						{
							FString ResponseVarNameStr(STD_ResponseVarNameStr.c_str());
							ResponseToDrawTMP.VariableToChange_Name.Add(ResponseVarNameStr);
						}
						else  //  =========  "Local"  =========
						{
							bool VariableIsAbsent = true;
							pugi::xpath_node_set DLG_Var = VariableRootNode.select_nodes("variable");
							for (int32 i_Variables = 0; i_Variables < DLG_Var.size(); i_Variables++)
							{
								//  name of local variable in LVariable_XmlFile
								std::string STD_VarNameStr(DLG_Var[i_Variables].node().attribute("name").as_string());	//   get attribute("name")

								if (STD_VarNameStr == STD_ResponseVarNameStr)
								{
									ResponseToDrawTMP.VariableToChange_Name.Add(FString::FromInt(i_Variables));
									VariableIsAbsent = false;
									break;
								}
							}
							if(VariableIsAbsent) ResponseToDrawTMP.VariableToChange_Name.Add(FString::FromInt(-1));
						}
						
							std::string STD_ResponseVarValueStr(DLG_ResponseCondition[i_ResponseCondition].node().text().as_string());  //   Get var "Value"
							FString ResponseVarValueStr(STD_ResponseVarValueStr.c_str());
						ResponseToDrawTMP.VariableToChange_Value.Add(ResponseVarValueStr);
					}
					
					ResponsesToDraw.Add(ResponseToDrawTMP); 
				}
			} // response loop END

			//  ----    if Responses No-One Exist    -----   =>>  goto next "Speech=default" node or 
			//  -----  go thought "Speech (default -> default -> default...)" node or start from "DEFAULD"   ---
			if (ResponsesToDraw.Num() == 0)
			{
				ReplicsToDraw.Empty();
				IsSpeechNodeGenerate_ok = false;

				if (_NextSpeechNode != FString("DEFAULT"))
				{
					_NextSpeechNode = FString("DEFAULT");
					_ResponseReturn = EResponseReturn::click_link_back;
					i_Speech = 0;
				}
				continue;  
			}
			
			IsSpeechNodeGenerate_ok = true;

			break;  ///  don't Check other "Speech"
		}
		}  // Speech loop END

		//  ------  if desired "Dialog" don't have any correct "replics" or "responses"  ---------    
		//   =>>  go throught "DEFAULT" Dialog and Speech nodes  ---------
		if(IsSpeechNodeGenerate_ok)	break;  //  don't Check other "Dialog"
		else
		{
			i_Dlg = -1;  // loop to begin (0)
			ReplicsToDraw.Empty();
			ResponsesToDraw.Empty();
			_NextDialogNode = FString("DEFAULT");
			_NextSpeechNode = FString("DEFAULT"); 
			_ResponseReturn = EResponseReturn::click_link_back;
			if (!ExtremalExit)
			{
				ExtremalExit = true;
				continue;
			}
			else
			{
				DLG_StopDialog();
				return;
			}

			   
		}
	}
	  
	}


	 //    ===============    Play Widget Dialog-block   ===============
	//if (AudioComponentRef)
	if (DisplayDialog->AudioComponentRef)
	{
		//  test   ResponsesToDraw.Empty();
		DisplayDialog->DrawDialog(ReplicsToDraw, ResponsesToDraw);
	}
	



	///std::ostringstream ss;
	///xmlDoc.save(ss);
	///std::string s = ss.str();



	///FString FSs(s.c_str());
	///UE_LOG(LogTemp, Warning, TEXT("unit->data->py = '%s'"), *FSs);

	///std::wstring ws = pugi::as_wide(ss.str());
	///FString FSss(ws.c_str());
	///UE_LOG(LogTemp, Warning, TEXT("unit->data->py = '%s'"), *FSss);


}



void ADLG_GlobalActor::DLG_StopDialog()
{
	APlayerController* PC = Cast<APlayerController>(GEngine->GetFirstLocalPlayerController(GetWorld()));
	if (!PC) return;
	//PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);    //  #include "Kismet/GameplayStatics.h"
	//===  Set Game InputCompomemt -----
	PC->InputComponent = StoredInputComponent; 
	DisplayDialog->StopDialog();
	DisplayDialog->AudioComponentRef = nullptr;
	
	PC->bShowMouseCursor = false;
	PC->SetInputMode(FInputModeGameOnly());


	OtherPlayerName = FName("none");


}



  
//  ==================  Delegate.   Response Activate  =================== 
void ADLG_GlobalActor::OnVariableChange(TArray<FName>& _VarName, TArray<FName>& _VarLastValue, TArray<FName>& _NewValue)
//void ADLG_GlobalActor::OnVariableChange(TArray<FName> VarName, TArray<FName> VarLastValue, TArray<FName> NewValue)
{
	if (DLGVariableChange.IsBound())
	{
		DLGVariableChange.Broadcast(_VarName, _VarLastValue, _NewValue);
	}
}

void ADLG_GlobalActor::OnRepDrawn(FString _Event)
{
	if (DLGReplicDrawn.IsBound())
	{
		DLGReplicDrawn.Broadcast(_Event);
	}
}

//  ==================   ResponseButton.    ChangeVariables  =================== 
void ADLG_GlobalActor::ChangeVariables(FResponseToDraw& CurrentResponse)
{
	//  -----------  for return delegate Event  ------------
	VarName.Empty();
	VarLastValue.Empty();
	NewValue.Empty();

	//     --------  Change Variable  ----------
	for (int32 i = 0; i < CurrentResponse.VariableToChange_Name.Num(); i++)
	{
		if (CurrentResponse.VariableToChange_LocalOrGlobal[i] == FString("local"))
		{
			int32 LocalVarIndex = FCString::Atoi(*CurrentResponse.VariableToChange_Name[i]);
			if (LocalVarIndex != -1)
				LocalVariables[LocalVarIndex] =	FName(*CurrentResponse.VariableToChange_Value[i]);
		}
		else   //  ========  "Global"  =========
		{
			//  -------- faind Global var by name  -----------
			FName* GlobalValueRef = GlobalVariable->Find(FName(*CurrentResponse.VariableToChange_Name[i]));		
			if (GlobalValueRef)
			{
				//  -----------  for return delegate Event  (name, last value)   ------------
				VarName.Add(FName(*CurrentResponse.VariableToChange_Name[i]));  // name
				VarLastValue.Add(*GlobalValueRef);								// last value
			
				// --------------  Change Global var  ---------------
				if (GlobalValueRef) *GlobalValueRef = FName(*CurrentResponse.VariableToChange_Value[i]);

				//  -----------  for return delegate Event  (new value)   ------------			
				NewValue.Add(*GlobalValueRef);		 //  new walue
			}
		}

	}

	// ----------------  exequte delegane Change variable  ---------------
	OnVariableChange(VarName, VarLastValue, NewValue);

}




//  ===============================================================================================
//  ===============================================================================================
//  ===========================              Global variable           ============================
//  ===============================================================================================
//  ===============================================================================================


void ADLG_GlobalActor::SetGlobalVariablesMapRef(UPARAM(ref) TMap<FName, FName>& _GlobalVariable)
{
	GlobalVariable = &_GlobalVariable; //  ref to TMap
	
	GlobalVariable->KeySort([](FName A, FName B) { return A.LexicalLess(B); });

}


//TMap<FName, FName> GlobalVariable;

void ADLG_GlobalActor::AddGlobalVar(FName _key, FName _value)
{	
	GlobalVariable->Add(_key, _value);
	//GlobalVariable.KeySort([](FName A, FName B)	{ return A < B; });
	GlobalVariable->KeySort([](FName A, FName B) { return A.LexicalLess(B); });


}

FName ADLG_GlobalActor::GetGlobalVar(FName _key)    //---------------------------NOT
{
	FName val = (*GlobalVariable)[_key];
	//UE_LOG(LogTemp, Warning, TEXT("TMap-------: = '%s', '%s'"), *_key.ToString(), *val.ToString());
	return val;
	//return _key;
}









