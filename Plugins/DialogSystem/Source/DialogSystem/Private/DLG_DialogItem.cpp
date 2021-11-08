// Fill out your copyright notice in the Description page of Project Settings.


#include "DLG_DialogItem.h"

#include "DialogSystem/Include/pugixml.hpp"                   //  PUGI


#include "EngineUtils.h"           //    ActorIterator

#include "Kismet/GameplayStatics.h"  // Sound at location

#include <sstream>


 
 
UDLG_DialogItem::UDLG_DialogItem()  
{

	PrimaryComponentTick.bCanEverTick = false;


}






void UDLG_DialogItem::BeginPlay()
{
	Super::BeginPlay();

	InitDialog();
}



void UDLG_DialogItem::SetAudioComponent(UAudioComponent* _AudioComponentRef)
{
	AudioComponentRef = _AudioComponentRef;
}


void UDLG_DialogItem::InitDialog()
{

	//UE_LOG(LogTemp, Warning, TEXT("1111111111111111111111111111111   DLG"));

	if (PathToFile == FString("Your dialog file.xml"))
	{
		UE_LOG(LogTemp, Error, TEXT("Unit '%s' try to Init don't assign dialog"), *GetOwner()->GetName());
		return;
	}


	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	


	//   ============   Get LocalVariables from .xml   ====================
	pugi::xml_document xmlVariables;

	FString LVariableXmlPath = FPaths::ProjectContentDir() + FString("Dialog/") + FString("LVariables.xml");
	
	if (!PlatformFile.FileExists(*LVariableXmlPath)) return;


	//   ----------------  Parse XML in Pakage to string  ----------------------
	FString str_LocalVariablesContent;
	FFileHelper::LoadFileToString(str_LocalVariablesContent, *LVariableXmlPath);
	std::string std_LocalVariablesContent = (TCHAR_TO_UTF8(*str_LocalVariablesContent));
	//  -----------------  Load string as pugi   -------------------------------
	pugi::xml_parse_result parse_VariablesRes = xmlVariables.load(std_LocalVariablesContent.c_str());
	if (!parse_VariablesRes) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Unit %s  can't parse '..content/Dialog/LVariables.xml'   ERROR"), *GetOwner()->GetName());
		return;
	}
	//  Get Root Node
	pugi::xml_node VariableRootNode = xmlVariables.child("local_variables");



	

	auto MatchVariables = [&](FVariables& _Variable,   //  return
		pugi::xml_node _VariableRootNode,              //  node from LVariable.xml
		std::string& STD_VarTypeStr, // local/global	//  parrameter from node from Dialog.xml
		std::string& STD_VarNameStr,					//  parrameter from node from Dialog.xml
		FString& VarValueStr)							//  parrameter from node from Dialod.xml
	{
		if (STD_VarTypeStr == "local")
		{
			//   444444444444444444  ================    LVariable   nodes  =================	
			//bool isVariableAbsent = true;
			pugi::xpath_node_set DLG_SpeechVariables = _VariableRootNode.select_nodes("variable");

			//  if local variable absent =>> save index = -1
			_Variable.Name = FName("CURRENT__LOCAL_VARIABLE__IS__ABSENT"); //FName(*FString::FromInt(-1));

			// ----- find variables in variablesFile.xml, and save--------
			for (int32 i_Variables = 0; i_Variables < DLG_SpeechVariables.size(); i_Variables++)
			{
				std::string STD_Tmp_SpeechVarNameStr(DLG_SpeechVariables[i_Variables].node().attribute("name").as_string());  //   get attribute("var_name")
				if (STD_VarNameStr == STD_Tmp_SpeechVarNameStr)
				{
					_Variable.Name = FName(*FString::FromInt(i_Variables));   //  save index of local variable
					_Variable.Value = FName(*VarValueStr);
					break;
				}
			}
		}
		else // if Global
		{
			//  --------  name variables in speech node   --------
			FString SpeechVarNameStr(STD_VarNameStr.c_str());

			_Variable.Name = FName(*SpeechVarNameStr);
			_Variable.Value = FName(*VarValueStr);
		}
	};






	//   ============   Get DialogParam from .xml   ====================
	pugi::xml_document xmlDoc;

	


	//   ----------------------   Content fron XML   ----------------------
	PathToFile = FPaths::ProjectContentDir() + PathToFile;
	//   ----------------  Parse XML in Pakage to string  ----------------------
	FString str_LocalDlgFileContent;
	FFileHelper::LoadFileToString(str_LocalDlgFileContent, *PathToFile);
	std::string std_LocalDlgFileContent = (TCHAR_TO_UTF8(*str_LocalDlgFileContent));
	//  -----------------  Load string as pugi   -------------------------------
	pugi::xml_parse_result parse_Res = xmlDoc.load(std_LocalDlgFileContent.c_str());
	if (!parse_Res) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Unit %s  can't parse ..dialog..(.xml)   ERROR"), *GetOwner()->GetName());
		return;
	}

	 
	//UE_LOG(LogTemp, Warning, TEXT("OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO   DLG"));


	//  Get Root Node
	pugi::xml_node RootNode = xmlDoc.child("name");

	std::string STD_dlgStr;
	std::string STD_SpeechStr;

	//  1111   =================   DIALOG   nodes  =================
	pugi::xpath_node_set DLG_DialogNodes = RootNode.select_nodes("dialog");
	for (int32 i_Dlg = 0; i_Dlg < DLG_DialogNodes.size(); i_Dlg++)
	{
		FDialogNode DialogTMP;


		STD_dlgStr = std::string(DLG_DialogNodes[i_Dlg].node().attribute("dialog_name").as_string());  //   get attribute("dialog_name")
		std::wstring STD_W_DlgStr = pugi::as_wide(STD_dlgStr.c_str());
		FString DlgStr(STD_W_DlgStr.c_str());

		DialogTMP.Name = FName(*DlgStr);


		//   2222  ================    SPEECH   nodes  =================		
		pugi::xpath_node_set DLG_SpeechNodes = DLG_DialogNodes[i_Dlg].node().select_nodes("speech");  
		for (int32 i_Speech = 0; i_Speech < DLG_SpeechNodes.size(); i_Speech++)
		{
			FSpeechNode SpeechTMP;;

			STD_SpeechStr = std::string(DLG_SpeechNodes[i_Speech].node().attribute("speech_name").as_string());  //   get attribute("speech_name")
			std::wstring STD_W_SpeechStr = pugi::as_wide(STD_SpeechStr.c_str());
			FString SpeechStr(STD_W_SpeechStr.c_str());

			SpeechTMP.Name = FName(*SpeechStr);
		 	
			//   3333333  ================    SPEECH_CONDITION   nodes      (Cash Variable to Compare)   =================	
			pugi::xpath_node_set DLG_SpeechConditionNodes = DLG_SpeechNodes[i_Speech].node().select_nodes("speech_condition");
			for (int32 i_SpeechCondition = 0; i_SpeechCondition < DLG_SpeechConditionNodes.size(); i_SpeechCondition++)
			{
				std::string STD_SpeechVarTypeStr(DLG_SpeechConditionNodes[i_SpeechCondition].node().attribute("var_type").as_string());  //   get attribute("Local/Global")

				std::string STD_SpeechVarNameStr(DLG_SpeechConditionNodes[i_SpeechCondition].node().attribute("var_name").as_string());  //   get attribute("var_name")
					// -----  get var value -----
				std::string STD_SpeechVarValueStr(DLG_SpeechConditionNodes[i_SpeechCondition].node().text().as_string());     //  var value
				FString SpeechVarValueStr(STD_SpeechVarValueStr.c_str());
				
				// ----    Asociate ConditionVariable from SPEECH with LocalVarInFile or GlobalVar   ------
				FVariables VariableTMP;
				MatchVariables(VariableTMP, 
					VariableRootNode, 
					STD_SpeechVarTypeStr,
					STD_SpeechVarNameStr,
					SpeechVarValueStr);  
				SpeechTMP.Variables.Add(VariableTMP);
			} 

			//   33333  ================    REPLIC   nodes  =================	
			pugi::xpath_node_set DLG_ReplicNodes = DLG_SpeechNodes[i_Speech].node().select_nodes("replic");
			for (int32 i_Replic = 0; i_Replic < DLG_ReplicNodes.size(); i_Replic++)
			{
				FReplicNode ReplicTMP;

				////   444444  ================    REPLIC_CONDITION   nodes      (Cash Variable to Compare)   =================	
				pugi::xpath_node_set DLG_ReplicConditionNodes = DLG_ReplicNodes[i_Replic].node().select_nodes("replic_condition");
				for (int32 i_ReplicCondition = 0; i_ReplicCondition < DLG_ReplicConditionNodes.size(); i_ReplicCondition++)
				{					
					std::string STD_ReplicVarTypeStr(DLG_ReplicConditionNodes[i_ReplicCondition].node().attribute("var_type").as_string());  //   get attribute("var_type")

					std::string STD_ReplicVarNameStr(DLG_ReplicConditionNodes[i_ReplicCondition].node().attribute("var_name").as_string());  //   get attribute("var_name")
						// -----  get var value -----
					std::string STD_ReplicVarValueStr(DLG_ReplicConditionNodes[i_ReplicCondition].node().text().as_string());     //  var value
					FString ReplicVarValueStr(STD_ReplicVarValueStr.c_str());

					// ----    Asociate ConditionVariable from REOLIC with LocalVarInFile or GlobalVar   ------
					FVariables VariableTMP;
					MatchVariables(VariableTMP,
						VariableRootNode,
						STD_ReplicVarTypeStr,
						STD_ReplicVarNameStr,
						ReplicVarValueStr);
					ReplicTMP.Variables.Add(VariableTMP);
				}
				
				//   44444  ================    REP   nodes  =================	
				pugi::xpath_node_set DLG_RepNodes = DLG_ReplicNodes[i_Replic].node().select_nodes("rep");
				for (int32 i_Rep = 0; i_Rep < DLG_RepNodes.size(); i_Rep++)
				{
					FRepNode RepTMP;

				//	 55555  ================    REP_CONDITION   nodes        (Cash Variable to Compare)   =================	
					pugi::xpath_node_set DLG_RepConditionNodes = DLG_RepNodes[i_Rep].node().select_nodes("rep_condition");
					for (int32 i_RepCondition = 0; i_RepCondition < DLG_RepConditionNodes.size(); i_RepCondition++)
					{
						std::string STD_RepVarTypeStr(DLG_RepConditionNodes[i_RepCondition].node().attribute("var_type").as_string());  //   get attribute("var_type")

						std::string STD_RepVarNameStr(DLG_RepConditionNodes[i_RepCondition].node().attribute("var_name").as_string());  //   get attribute("var_name")
							// -----  get var value -----
						std::string STD_RepVarValueStr(DLG_RepConditionNodes[i_RepCondition].node().text().as_string());  //  var value
						FString RepVarValueStr(STD_RepVarValueStr.c_str());

						// ----    Asociate ConditionVariable from REP with LocalVarInFile or GlobalVar   ------
						FVariables VariableTMP;
						MatchVariables(VariableTMP,
							VariableRootNode,
							STD_RepVarTypeStr,
							STD_RepVarNameStr,
							RepVarValueStr);
						RepTMP.Variables.Add(VariableTMP);
					}
					ReplicTMP.RepNode.Add(RepTMP);
				}				
				SpeechTMP.ReplicNode.Add(ReplicTMP);
			}

			//   3333   ================    RESPONSE   nodes  =================	
			pugi::xpath_node_set DLG_ResponseNodes = DLG_SpeechNodes[i_Speech].node().select_nodes("response");
			for (int32 i_Response = 0; i_Response < DLG_ResponseNodes.size(); i_Response++)
			{
				FResponseNode ResponseTMP;

				////   444444  ================    RESPONSE_CONDITION   nodes      (Cash Variable to Compare)   =================	
				pugi::xpath_node_set DLG_ResponseConditionNodes = DLG_ResponseNodes[i_Response].node().select_nodes("response_condition");
				for (int32 i_ResponseCondition = 0; i_ResponseCondition < DLG_ResponseConditionNodes.size(); i_ResponseCondition++)
				{
					std::string STD_ResponseVarTypeStr(DLG_ResponseConditionNodes[i_ResponseCondition].node().attribute("var_type").as_string());  //   get attribute("var_type")

					std::string STD_ResponseVarNameStr(DLG_ResponseConditionNodes[i_ResponseCondition].node().attribute("var_name").as_string());  //   get attribute("var_name")
						// -----  get var value -----
					std::string STD_ResponseVarValueStr(DLG_ResponseConditionNodes[i_ResponseCondition].node().text().as_string());  //  var value
					FString ResponseVarValueStr(STD_ResponseVarValueStr.c_str());

					// ----    Asociate ConditionVariable from REP with LocalVarInFile or GlobalVar   ------
					FVariables VariableTMP;
					MatchVariables(VariableTMP,
						VariableRootNode,
						STD_ResponseVarTypeStr,
						STD_ResponseVarNameStr,
						ResponseVarValueStr);
					ResponseTMP.Variables.Add(VariableTMP);
				}


				////   444444  ================    RESPONSE_Change_VARIABLES   nodes     (Cash Variable to change)  =================	
				pugi::xpath_node_set DLG_ResponseVariablesNodes = DLG_ResponseNodes[i_Response].node().select_nodes("change_variable");
				for (int32 i_ResponseVariables = 0; i_ResponseVariables < DLG_ResponseVariablesNodes.size(); i_ResponseVariables++)
				{
					std::string STD_ResponseVarTypeStr(DLG_ResponseVariablesNodes[i_ResponseVariables].node().attribute("var_type").as_string());  //   get attribute("var_type")

					std::string STD_ResponseVarNameStr(DLG_ResponseVariablesNodes[i_ResponseVariables].node().attribute("var_name").as_string());  //   get attribute("var_name")
					// -----  get var value -----
					std::string STD_ResponseVarValueStr(DLG_ResponseVariablesNodes[i_ResponseVariables].node().text().as_string());  //  var value
					FString ResponseVarValueStr(STD_ResponseVarValueStr.c_str());

					// ----    Asociate ConditionVariable from REP with LocalVarInFile or GlobalVar   ------
					FVariables VariableTMP;
					MatchVariables(VariableTMP,
						VariableRootNode,
						STD_ResponseVarTypeStr,
						STD_ResponseVarNameStr,
						ResponseVarValueStr);
					ResponseTMP.Variables_ToChange.Add(VariableTMP);
				}

				SpeechTMP.ResponseNode.Add(ResponseTMP);
			} 

			DialogTMP.SpeechNode.Add(SpeechTMP);
		}//
		DialogParameter.DialogNode.Add(DialogTMP);
	}//

}


void UDLG_DialogItem::PlayDialog(FName _PlayerName)
{
	

	//    Check if GlobalDialog_Actor exist    //   if NOT =>> spawn it
	if (!DLG_GlobalActor)
	{
		//for (TObjectIterator<ADLG_GlobalActor> Itr; Itr; ++Itr)
		for (TActorIterator<ADLG_GlobalActor> Itr(GetWorld()); Itr; ++Itr)
		{
			if (Itr->IsA(ADLG_GlobalActor::StaticClass()))
			{
				DLG_GlobalActor = *Itr;
				break;
			}
		}

		//  ------ Spawn, if not  ------
		if (!DLG_GlobalActor)
		{
			BP_GLobalActorClass = StaticLoadClass(ADLG_GlobalActor::StaticClass(), nullptr,
				TEXT("/DialogSystem/DLG_GlobalActorBP.DLG_GlobalActorBP_C"));
			DLG_GlobalActor = GetWorld()->SpawnActor<ADLG_GlobalActor>(BP_GLobalActorClass);
		}

		if (!DLG_GlobalActor)UE_LOG(LogTemp, Error, TEXT("Not Exist Global DLG_Actor.  Reporter '%s'"), *GetOwner()->GetName());
	}


	if (PathToFile == FString("Your dialog file.xml"))
	{
		UE_LOG(LogTemp, Error, TEXT("Unit '%s' start dialog but don't assign it"), *GetOwner()->GetName());
		return;
	}









	if (DLG_GlobalActor)
	{
		if (_PlayerName == FName("IfOtherName"))
		{
			_PlayerName = DLG_GlobalActor->GetPlayerName();
		}
		DLG_GlobalActor->DLG_PlayDialog(GetOwner(), _PlayerName, AudioComponentRef, PathToFile, DialogParameter);
	}
   
}






//  ==============================================   INTERFACE   ======================================

/*
bool UDLG_DialogItem::StartDialog_Implementation() 
{

	if (DLG_GlobalActor)
	{
		PlayDialog(FName("IfOtherName"));
		return true;
	}
	//UE_LOG(LogTemp, Warning, TEXT("StartDialog"));
	return false;
}
*/











