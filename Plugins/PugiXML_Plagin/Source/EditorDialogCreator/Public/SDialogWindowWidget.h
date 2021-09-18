// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

//#include "DLG_GlobalActor.h"
//#include "../../PugiXML_Plagin/Public/DLG_GlobalActor.h"

//#include "DLGButtonDialog.h"//-----------
//#include "DLGButtonCondition.h"//-----------
//#include "DLGButtonResponse.h"//-----------

#include "Widgets/Input/SSpinBox.h"

#include "Widgets/SCompoundWidget.h"
  
#include "PugiXML_Plagin/Include/pugixml.hpp"
//#include <fstream>   //  pugi load std::ifstream

struct FIndicator
{
	FLinearColor color = FLinearColor(0.7f, 0.77f, 1.f, 1);
	float size = 0.f;
};


struct FVariables
{
	UPROPERTY()  
		FName VariableName = FName("none"); 
		//TSharedPtr<class STextBlock> ConditionVariable_Name_Statick;
		TSharedPtr<class SEditableTextBox> ChangeVariable_Name_Editable;
		TSharedPtr<class UButton> ChangeVariable_Name_Button;
	UPROPERTY()  
		bool IsProperty_VariableName_EditNow = false;

	UPROPERTY()  
		FName VariableValue = FName("none");
		//TSharedPtr<class STextBlock> ConditionVariable_Value_Statick;
		TSharedPtr<class SEditableTextBox> ChangeVariable_Value_Editable;
		TSharedPtr<class UButton> Change_VariableValue_Button;
	UPROPERTY()  
		bool IsProperty_VariableValue_EditNow = false;

	UPROPERTY()  
		bool isVariableGlobal = true;

	UPROPERTY()  
		bool IsUsualMarker = false;
	UPROPERTY()  
		bool IsErrorMarker = false;
	UPROPERTY()  
		bool IsLinkMarker = false;
		//FIndicator Indicator;
};

struct FCondition
{
	UPROPERTY()  
		FName ConditionType = FName("and");
		//TSharedPtr<class STextBlock> Condition_Type_Statick;                 //   DELETE OTHER, THE SAME, STATICK-BLOCK in OTHER SECTIONSS
		TSharedPtr<class SEditableTextBox> Condition_Type_Editable;
		TSharedPtr<class UButton> ChangeCondition_Type_Button;
	UPROPERTY()  
		bool IsProperty_Type_EditNow = false;

	UPROPERTY()  
		FName VariableName = FName("none");
		//TSharedPtr<class STextBlock> ConditionVariable_Name_Statick;
		TSharedPtr<class SEditableTextBox> ConditionVariable_Name_Editable;
		TSharedPtr<class UButton> ChangeConditionVariable_Name_Button;
	UPROPERTY()  
		bool IsProperty_VariableName_EditNow = false;

	UPROPERTY()  
		FName VariableValue = FName("none");
	//TSharedPtr<class STextBlock> ConditionVariable_Value_Statick;
		TSharedPtr<class SEditableTextBox> ConditionVariable_Value_Editable;
		TSharedPtr<class UButton> ChangeCondition_ariableValue_Button;
	UPROPERTY()  
		bool IsProperty_VariableValue_EditNow = false;

	UPROPERTY()  
		bool isVariableGlobal = true;

	UPROPERTY()  
		bool IsUsualMarker = false;
	UPROPERTY()  
		bool IsErrorMarker = false;
	UPROPERTY()  
		bool IsLinkMarker = false;
		//FIndicator Indicator;
};


struct FRepSection
{

	UPROPERTY()  
		FName Time = FName("0");
		//TSharedPtr<class SSpinBox<float>> SB_Delay;

	UPROPERTY()  
		FName Delay = FName("0");
		//TSharedPtr<class SSpinBox<float>> SB_AfterDelay;

	UPROPERTY()  
		FName Speker = FName("none");
		//TSharedPtr<SComboBox<TSharedPtr<FString>>> CB_Spiker;
		//TSharedPtr<FString>	CurrentSpiker = MakeShareable(new FString(TEXT("none")));
		//bool isSpikerComboBoxEditNow = false;

	UPROPERTY()  
		FName Sound = FName("none");
		//TSharedPtr<SComboBox<TSharedPtr<FString>>> CB_Sound;
		//TSharedPtr<FString>	CurrentSound = MakeShareable(new FString(TEXT("none")));
		//bool isSoundComboBoxEditNow = false;

		//TSharedPtr<class SDLGButtonDialog> ReplicTitleCollapsedContent_Button;

		TSharedPtr<class STextBlock> ReplicSectionRepeat_Statick;
		TSharedPtr<class SEditableTextBox> ReplicSectionRepeat_Editable;
		//TSharedPtr<class SDLGButtonDialog> ChangeReplicSectionRepeat_Button;
	 
	UPROPERTY()  
		FString RepEvent = FString("RETURN_EVENT");
		TSharedPtr<class SEditableTextBox> RepEvent_EditableText;
	UPROPERTY()  
		bool isEventPropertyEditNow = false;

	UPROPERTY()  
		FLinearColor TextColor = FLinearColor(0.7f, 0.77f, 1.f, 1);

	UPROPERTY()  
		FString ComentText = FString("none");
	UPROPERTY()  
		float ComentTextZoneSizeY = 0;

		TArray<FCondition> RepCondition;	
		TSharedPtr<class SVerticalBox> RepConditionBlock;
	UPROPERTY()  
		bool IsConditionOpen = false;

	UPROPERTY()  
		//bool IsSectionOpen = true;
		bool IsSectionEditNow = false;

	UPROPERTY()  
		bool IsUsualMarker = false;
	UPROPERTY()  
		bool IsErrorMarker = false;
		//FIndicator Indicator;
};
  
struct FResponseSection 
{

	//FName RepeatProperty = FName("none");   //  once,   always

	//TSharedPtr<class SDLGButtonDialog> ResponseTitleCollapsedContent_Button;

	TSharedPtr<SComboBox<TSharedPtr<FString>>> CB_ResponseRepeat;
	TSharedPtr<FString>	ResponseRepeatPropperty = MakeShareable(new FString(TEXT("always")));

	TSharedPtr<SComboBox<TSharedPtr<FString>>> CB_ResponseReturnType;
	TSharedPtr<FString>	ResponseReturnTypePropperty = MakeShareable(new FString(TEXT("click"))); 

	UPROPERTY()  
		FName DialogLink = FName("DEFAULT");
	UPROPERTY()  
		FName SpeechLink = FName("DEFAULT");
		//TSharedPtr<class STextBlock> ResponseSectionRepeat_Statick;
		//TSharedPtr<class SEditableTextBox> ResponseSectionRepeat_Editable;
		//TSharedPtr<class SDLGButtonDialog> ChangeResponseSectionRepeat_Button;
	UPROPERTY()  
		FString ComentText = FString("none");
	UPROPERTY()  
		float ComentTextZoneSizeY = 0;

		TSharedPtr<class SVerticalBox> ResponseBlock;
		//TArray<FSpeechSection> SpeechSection;

	UPROPERTY()  
		TArray<FCondition> ResponseCondition;
		TSharedPtr<class SVerticalBox> ResponseConditionBlock;
	UPROPERTY()  
		bool IsConditionOpen = false;
	 
	UPROPERTY()  
		FLinearColor TextColor = FLinearColor(0.7f, 0.77f, 1.f, 1);
	UPROPERTY()  
		TArray<FVariables> VariableSection;

		TSharedPtr<class SVerticalBox> VariableBlock;
	UPROPERTY()  
		bool IsVariableOpen = false;
	 
	UPROPERTY()  
		//bool IsSectionOpen = true;
		bool IsSectionEditNow = false;
	UPROPERTY()  
		bool IsUsualMarker = false;
	UPROPERTY()  
		bool IsErrorMarker = false;
	UPROPERTY()  
		bool IsLinkMarker = false;
		//FIndicator Indicator;

}; 
 
struct FReplicSection
{
	//FName RepeatProperty = FName("none");   //  once,   after_once,   return_breack,  always

	//TSharedPtr<class SDLGButtonDialog> ReplicTitleCollapsedContent_Button;


	TSharedPtr<SComboBox<TSharedPtr<FString>>> CB_ReplicRepeat;
	TSharedPtr<FString>	ReplicRepeatPropperty = MakeShareable(new FString(TEXT("always")));

	//TSharedPtr<class STextBlock> ReplicSectionRepeat_Statick;
	//TSharedPtr<class SEditableTextBox> ReplicSectionRepeat_Editable;
	//TSharedPtr<class SDLGButtonDialog> ChangeReplicSectionRepeat_Button;


	UPROPERTY()  
		FString ComentText = FString("Commentary about all replic content. It's newer seen in game.");
	UPROPERTY()  
		float ComentTextZoneSizeY = 0;
		//TSharedPtr<class SMultiLineEditableTextBox> ReplicComent_EditableMultiline;

		TSharedPtr<class SVerticalBox> RepBlock;
	UPROPERTY()  
		TArray<FRepSection> RepSection; 

	UPROPERTY()  
		FLinearColor TextColor = FLinearColor(0.7f, 0.77f, 1.f, 1); 

	UPROPERTY()  
		TArray<FCondition> ReplicCondition;
		TSharedPtr<class SVerticalBox> ReplicConditionBlock;
	UPROPERTY()  
		bool IsConditionOpen = false;

	UPROPERTY()  
		bool IsSectionOpen = false;
	UPROPERTY()  
		bool IsSectionEditNow = false;

	UPROPERTY()  
		bool IsSelfUsualMarker = false;
	UPROPERTY()  
		bool IsUsualMarker = false;
	UPROPERTY()  
		bool IsErrorMarker = false;
	//FIndicator Indicator;

};
     
struct FSpeechSection
{
	UPROPERTY()  
		FName Name = FName("DEFAULT");   //  a lot of "DEFAULT" or lot of "What_user_set"

		//TSharedPtr<class SDLGButtonDialog> SpeechTitleCollapsedContent_Button;

		TSharedPtr<class STextBlock> SpeechSectionName_Statick;
		TSharedPtr<class SEditableTextBox> SpeechSectionName_Editable;
		//TSharedPtr<class SDLGButtonDialog> ChangeSpeechSectionName_Button;
	 
	 

		TSharedPtr<class SVerticalBox> ReplicAndResponseBlock;
	UPROPERTY()  
		TArray<FReplicSection> ReplicSection;
	UPROPERTY()  
		TArray<FResponseSection> ResponseSection;
	UPROPERTY()  
		//TSharedPtr<class SVerticalBox> SpeechConditionBlock;
		//TArray<FReplicSection> SpeechConditionSection;
		TArray<FCondition> SpeechCondition;

		TSharedPtr<class SVerticalBox> SpeechConditionBlock;
	UPROPERTY()  
		bool IsConditionOpen = false;

	UPROPERTY()  
		FLinearColor TextColor = FLinearColor(0.7f, 0.77f, 1.f, 1);
	
	UPROPERTY()  
		bool IsSectionOpen = false;
	UPROPERTY()  
		bool IsSectionEditNow = false;

	UPROPERTY()  
		bool IsSelfUsualMarker = false;
	UPROPERTY()  
		bool IsUsualMarker = false;        //  consider a Child
	UPROPERTY()  
		bool IsErrorMarker = false;
	UPROPERTY()  
		bool IsSelfLinkMarker = false;
	UPROPERTY()  
		bool IsLinkMarker = false;         //  consider a Child
	UPROPERTY()  
		bool IsDestinationMarker = false;  //  consider a Child
	UPROPERTY()  
		bool IsFastFindMarker = false;
		//FIndicator Indicator;
};


//USTRUCT(BlueprintType, Blueprintable)   
struct FDialogSection
{
//	GENERATED_BODY()

	UPROPERTY()  
	//UPROPERTY()
		FName Name = FName("DEFAULT");   //  1 - "DEFAULT" and other "What_user_set"

		//TSharedPtr<class STextBlock> DialogSectionName_Statick;
		TSharedPtr<class SEditableTextBox> DialogSectionName_Editable;
		//TSharedPtr<class SDLGButtonDialog> DialogTitleCollapsedContent_Button;
		//TSharedPtr<class SDLGButtonDialog> ChangeDialodSectionName_Button;
	

		TSharedPtr<class SVerticalBox> SpeechBlock;
	UPROPERTY()  
		TArray<FSpeechSection> SpeechSection;

	UPROPERTY()  
		FLinearColor TextColor = FLinearColor(0.7f, 0.77f, 1.f, 1);

	UPROPERTY()  
		//bool IsIndicatorShow = false;
		bool IsSectionOpen = false;
	UPROPERTY()  
		bool IsSectionEditNow = false;


	UPROPERTY()  
		//TAttay<int32> HasChildrenMarker;
		bool IsSelfUsualMarker = false;  
	UPROPERTY()  
		bool IsUsualMarker = false;        //  consider a Child
	UPROPERTY()  
		bool IsErrorMarker = false;
	UPROPERTY()  
		bool IsSelfLinkMarker = false;
	UPROPERTY()  
		bool IsLinkMarker = false;         //  consider a Child
	UPROPERTY()  
		bool IsDestinationMarker = false;  //  consider a Child
	UPROPERTY()  
		bool IsFastFindMarker = false;
		//FIndicator Indicator;
		//TSharedPtr<class SButton> DialogIndicator;
};



struct FSound
{
	UPROPERTY()  
		FName name = FName("none");

	UPROPERTY()  
		FString SoundAssetPath;
	UPROPERTY()  
		FString SoundComment;


		TSharedPtr<class STextBlock> SoundrName_Statick;
		//TSharedPtr<class SEditableTextBox> SoundrName_Editable;

};

//USTRUCT(BlueprintType, Blueprintable)   
struct FSpekers
{
//	GENERATED_BODY()

	UPROPERTY()  
		FName name = FName("none");

		TSharedPtr<class STextBlock> SpekerName_Statick;
		TSharedPtr<class SEditableTextBox> SpekerName_Editable;

		TSharedPtr<class SScrollBox> SounsScroll;


	UPROPERTY()  
	//UPROPERTY()
		FString SpekersAssetPath;
	UPROPERTY()  
		FSlateBrush SpekersImageBrush;

	UPROPERTY()  
		TArray<FSound> Sound;

	UPROPERTY()  
		bool IsSectionEditNow = false;

		// sounsAsset Path ++++++++++++++++++++++++++
};


UENUM()  //BlueprintType, Blueprintable
enum class ECurrentMainPanel : uint8
{
	Content,
	Variables,
	Spekers,
};

UENUM()  //BlueprintType, Blueprintable
enum class EProppertyToChange : uint8
{
	none,

	DialogName,
	SpeechName,
	repeatReplic,   
	repeatResponse,   
	DialogLink,
	SpeechLink,
	//Delay,
	//AfrerDelay,
	speker,
	sound,
	RepEvent,
	time,
	delay,
	 
	Speech_condition_type,
	Speech_condition_varType,
	Speech_condition_varName,
	Speech_condition_varValue,
	Replic_condition_type,
	Replic_condition_varType,
	Replic_condition_varName,
	Replic_condition_varValue,
	rep_condition_type,
	rep_condition_varType,
	rep_condition_varName,
	rep_condition_varValue,
	Response_condition_type,		// and/or
	Response_condition_varType,   // Global/LOcal
	Response_condition_varName,
	Response_condition_varValue,

	//Response_variable_type,
	Response_variable_varType,
	Response_variable_varName,
	Response_variable_varValue,
	//VariableName_Property,
	//VariableValue_Property,
	//dialogLink,
	//gotoMarker,
	//gotoType,

	replicComent,
	repComent,
	responseComent,




	SpekerinSpekerBlock,


	AddDialog,
	AddSpeech,
	AddReplick,
	AddResponse,
	ButtonAddRep,
	ButtonAddSpeech_Condition,
	ButtonAddReplic_Condition,
	ButtonAddResponse_Condition,
	ButtonAddResponse_Variable,
	ButtonAddRep_Condition,

	MoveDialog,
	MoveSpeech,
	//MoveSpeech_Condition,  //--
	MoveReplic,
	//MoveReplic_Condition,  //--
	MoveRep,
	MoveRep_Condition,
	MoveResponse,
	//MoveResponse_Condition,  //--
	MoveResponse_Variable,
	Move_Condition,//77777777777777777777

	RemoveDialog,
	RemoveSpeech,
	RemoveSpeech_Condition,
	RemoveReplic,
	RemoveReplic_Condition,
	RemoveRep,
	RemoveRep_Condition,
	RemoveResponse,
	RemoveResponse_Condition,
	RemoveResponse_Variable,

	CollapsedDialogSection,
	CollapsedSpeechSection,
	CollapsedSpeech_Condition,
	CollapsedReplicSection,
	CollapsedReplic_Condition,
	CollapsedRep_Condition,
	CollapsedResponseSection,
	CollapsedResponse_Condition,
	CollapsedResponse_Variables,

	MarkerDialog,
	MarkerSpeech,
	MarkerReplic,
	MarkerRep,
	MarkerResponse,

	ButtonAdd_Variable,
	ButtonRemove_Variable,
	Variable_varName,
	Variable_varValue
};


UENUM()  //BlueprintType, Blueprintable
enum class EShouldUpdate : uint8
{
	none,
	inDialog,
	inSpeech,
	inReplic,
	inRep,
	inResponse
};


struct FPropertyIndex
{
	//EProppertyToChange ProppertyToChange;
	UPROPERTY()  
		int32 iDialog = -1;
	UPROPERTY()  
		int32 iSpeech = -1;
	UPROPERTY()  
		//int32 iReplicOrResponse = -1;
		int32 iReplic = -1;
	UPROPERTY()  
		int32 iResponse = -1;
		//int32 iRepOrResponsCondition = -1;  //777777777
		//-----------int32 iResponseCondition = -1;  //77777777777777	
	UPROPERTY()  
		int32 iRep = -1;
	

	UPROPERTY()  
		int32 iSpeechCondition = -1;
	UPROPERTY()  
		int32 iReplicCondition = -1;
	UPROPERTY()  
		int32 iRepCondition = -1;
	UPROPERTY()  
		int32 iResponseCondition = -1;
	UPROPERTY()  
		int32 iResponseVariable = -1;   // response block

	 
	UPROPERTY()  
		int32 iVariable = -1;     //  Variable block
	UPROPERTY()  
		int32 SpekerIndex = -1;
};

  
 
class SDialogWindowWidget : public SCompoundWidget  //  PUGIXML_PLAGIN_API
{
public:
	SLATE_BEGIN_ARGS(SDialogWindowWidget)
	{}
		//SLATE_ARGUMENT()
		SLATE_ATTRIBUTE(FString*, PathToFile)
//		SLATE_ATTRIBUTE(FSlateColor, myLinearImageColor_TEST)
//		SLATE_ATTRIBUTE(FVector2D, ViewportSizeParam)
//		SLATE_ATTRIBUTE(class AWorldBoundActor*, BoundWorldActor)
//		SLATE_ATTRIBUTE(class UGlobalGameInstance*, GameInstance)
		//SLATE_EVENT()
		SLATE_END_ARGS()

	

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;

	
	int32 OnPaint
	(
		const FPaintArgs& Args,
		const FGeometry& AllottedGeometry,
		const FSlateRect& MyCullingRect,
		FSlateWindowElementList& OutDrawElements,
		int32 LayerId,
		const FWidgetStyle& InWidgetStyle,
		bool bParentEnabled
	) const override;


public:


	//+++++++++++++++++++++++++++++++++++++++++++++++


		TSharedPtr<class SButton> ContentPanelShowButton;
		TSharedPtr<class SButton> VariablesPanelShowButton;
		TSharedPtr<class SButton> SpekerPanelShowButton;
	UFUNCTION()//======77777
		FReply OnButtonSelectLayer(FName MainPanelType);

	UPROPERTY()  
		ECurrentMainPanel CurrentMainPanel = ECurrentMainPanel::Content;
	UPROPERTY()  
		EVisibility DialogContentVisibility = EVisibility::Visible;   //  // Collapsed  Visible
	UPROPERTY()  
		EVisibility DialogVariablesVisibility = EVisibility::Collapsed;
	UPROPERTY()  
		EVisibility DialogSpikersVisibility = EVisibility::Collapsed;


		TSharedPtr<class SVerticalBox> LeftIndicator_1;
		TSharedPtr<class SVerticalBox> LeftIndicator_2;
		TSharedPtr<class SVerticalBox> RightIndicator;
		TSharedPtr<class SScrollBox> MainContentPanelBlock;           //   Main content, where will add new content.   ScrollBox
	

	UPROPERTY()  
		const FSlateBrush* MarkerLink;
	UPROPERTY()  
		const FSlateBrush* PlaySound;
	UPROPERTY()  
		const FSlateBrush* ImageLayerActivate;
	UPROPERTY()  
		const FSlateBrush* ImageLayerDefault;
	UPROPERTY()  
		const FSlateBrush* TitleDialog;
	UPROPERTY()  
		const FSlateBrush* TitleDialogStart;
	UPROPERTY()  
		const FSlateBrush* TitleDialogEnd;
	UPROPERTY()  
		const FSlateBrush* TitleReplic;
	UPROPERTY()  
		const FSlateBrush* TitleReplicStart;
	UPROPERTY()  
		const FSlateBrush* TitleReplicEnd;
	UPROPERTY()  
		const FSlateBrush* TitleResponse;
	UPROPERTY()  
		const FSlateBrush* TitleResponseStart;
	UPROPERTY()  
		const FSlateBrush* TitleResponseEnd;

	UPROPERTY()  
		const FSlateBrush* ImageAddElement;
		//const FSlateBrush* ImageRemoveElement;
	UPROPERTY()  
		const FSlateBrush* ImageMoveElement;
	UPROPERTY()  
		const FSlateBrush* ImageDeleteElement;
	UPROPERTY()  
		const FSlateBrush* ImageAddSoundElement;
	UPROPERTY()  
		const FSlateBrush* ImageConditionButtonOn;
	UPROPERTY()  
		const FSlateBrush* ImageConditionButtonOFF;
	UPROPERTY()  
		const FSlateBrush* ImageVariableButtonOn;
	UPROPERTY()  
		const FSlateBrush* ImageVariableButtonOff;
	UPROPERTY()  
		const FSlateBrush* GetImageConditionButton(EProppertyToChange _ProppertyToChange, FPropertyIndex PropertyIndex)  const;
	UPROPERTY()  
		const FSlateBrush* PropertyDialog;
	UPROPERTY()  
		const FSlateBrush* PropertyDialogStart;
	UPROPERTY()  
		const FSlateBrush* PropertyDialogEnd;
	UPROPERTY()  
		const FSlateBrush* PropertyReplic;
	UPROPERTY()  
		const FSlateBrush* PropertyReplicStart;
	UPROPERTY()  
		const FSlateBrush* PropertyReplicEnd;
	UPROPERTY()  
		const FSlateBrush* PropertyResponse;
	UPROPERTY()  
		const FSlateBrush* PropertyResponseStart;
	UPROPERTY()  
		const FSlateBrush* PropertyResponseEnd;

	UPROPERTY()  
		const FSlateBrush* ImageValueZone;
	UPROPERTY()  
		const FSlateBrush* Condition;
	UPROPERTY()  
		const FSlateBrush* ConditionStart;
	UPROPERTY()  
		const FSlateBrush* ConditionEnd;
	UPROPERTY()  
		const FSlateBrush* ImageButtonSectionRollUp;
	UPROPERTY()  
		const FSlateBrush* ImageButtonSectionExpand;
	UPROPERTY()  
		const FSlateBrush* GetImageButtonSectionCollapsed(EProppertyToChange _ProppertyToChange, FPropertyIndex PropertyIndex)  const;
	UFUNCTION()  
		EVisibility IsSectionCollapsed(EProppertyToChange _ProppertyToChange, FPropertyIndex PropertyIndex) const;
	UFUNCTION()  
		FSlateColor GetSectionTextColor(EProppertyToChange ProppertyToChange, FPropertyIndex PropertyIndex) const;

	UFUNCTION()  
	FReply AddNewElement();
	UFUNCTION()  
	void AddDialogSection(FPropertyIndex PropertyIndex);
	UFUNCTION()  
	void AddSpeechSection(FPropertyIndex PropertyIndex);
	UFUNCTION()  
	void AddReplicSection(FPropertyIndex PropertyIndex);
	UFUNCTION()  
	void AddResponseSection(FPropertyIndex PropertyIndex);
	UFUNCTION()  
	void AddRepSection(FPropertyIndex PropertyIndex);
	UFUNCTION()  
	void AddSpeechCondition(FPropertyIndex PropertyIndex);
	UFUNCTION()  
	void AddRepCondition(FPropertyIndex PropertyIndex);
	UFUNCTION()  
	void AddReplicCondition(FPropertyIndex PropertyIndex);
	UFUNCTION()  
	void AddResponseCondition(FPropertyIndex PropertyIndex);
	UFUNCTION()  
	void AddResponseVariable(FPropertyIndex PropertyIndex);


	
	//  ========  copu or move section
	UPROPERTY()  
	EProppertyToChange SectionToMove_Propperty;
	UPROPERTY()  
	FPropertyIndex iSectionToMove;
	UPROPERTY()  
	FCondition MovingCondition;
	UPROPERTY()  
	bool isCurrSectionToMove_Cut = false;
	//--------------

	UFUNCTION()  
	FReply SaveAll();
	UFUNCTION()  
	FReply LoadAll();
	  
	//void UpdateContentPanel();
	UFUNCTION()  
	void UpdateDialogBlock();
	UFUNCTION()  
	void DrawConditionElement(TSharedPtr<SVerticalBox>& RepConditionBlock,
								FPropertyIndex& CurrentPropertyIndex,
								EProppertyToChange AddButtonPropperty,
								//EProppertyToChange MoveButtonPropperty,
								EProppertyToChange RemoveButtonPropperty,

								TSharedPtr<class SEditableTextBox> &TextBoxCondition_Type,
								FName& Type_Text,
								EProppertyToChange ConditionTypePropperty,
								TSharedPtr<class SEditableTextBox> &TextBoxVariable_Name,
								FName& VariableName_Text,
								EProppertyToChange VarNamePropperty,
								TSharedPtr<class SEditableTextBox> &TextBoxVariable_Value,
								FName& VariableValue_Text,
								EProppertyToChange VarValuePropperty,

								EProppertyToChange VarTypePropperty);

	//bool Update = true;
	UPROPERTY()  
	EShouldUpdate ShouldUpdate = EShouldUpdate::none;

	UFUNCTION()  
	void EditProperty(EProppertyToChange _ProppertyToChange, FPropertyIndex PropertyIndex);  
	UFUNCTION()  
	void SwitchCollapsedSection(EProppertyToChange _ProppertyToChange, FPropertyIndex PropertyIndex);

	UPROPERTY()  
	TArray<FDialogSection> DialogSection;


	//        ============================   Marker   ================================
	//++++++++++++FReply OnButtonMarkerUsual(EProppertyToChange ProppertyToChange, FPropertyIndex PropertyIndex);
	UFUNCTION()  
	FReply OnButtonMarkerUsual(const FGeometry& Geomet, const FPointerEvent& PEvent, EProppertyToChange ProppertyToChange, FPropertyIndex PropertyIndex);
	UFUNCTION()  
	FReply OnButtonMarkerLink(EProppertyToChange ProppertyToChange, FPropertyIndex PropertyIndex);
	//FLinearColor GetSectionTextColor(EProppertyToChange ProppertyToChange, FPropertyIndex PropertyIndex);
	UPROPERTY()  
	bool IsLinkMarkerDrawn = false;			 //  selected child
	UPROPERTY()  
	int32 LastClickedSectionDialogIndex;  //  selected child
	UPROPERTY()  
	int32 LastClickedSectionSpeechIndex;  //  selected child
	UPROPERTY()  
	int32 LastClickedSectionResponseIndex;  //  selected child
	


	UFUNCTION()  
	FReply OnButtonClick(EProppertyToChange ProppertyToChange, FPropertyIndex PropertyIndex);
	UFUNCTION()  
	FReply OnButtonRemoveClick(EProppertyToChange ProppertyToChange, FPropertyIndex PropertyIndex);
/*	void OnDLGButtonClick(EButtonDialogType _ButtonDialogType,       //  77777777777777777777777777777777777777777777
							int32 _Param_DialodIndex = -1,
							int32 _Param_SpeechIndex = -1,
							int32 _Param_ReplicOrResponseIndex = -1,
							int32 _Param_RepOrConditionIndex = -1,						int32 _Param_ConditionIndex = -1

							//int32 Param_Replic = -1,
							////int32 Param_Replic_condition = -1,
							//
							//int32 Param_Rep = -1,
							//int32 Param_condition = -1
						);
	*/
	///////////////////////////////int32 changingDialod_Index = -1;
	//////////////////////////////int32 changingSpeech_Index = -1;
	/////////////////////////////////int32 changingReplicOrResponse_Index = -1;
	//int32 changingRepOrCondition_Index = -1;
	////////////////////////////////EProppertyToChange  changingPropperty = EProppertyToChange::none;
	UFUNCTION()  
	EVisibility GetVisibility_LocalVarIndicator(EProppertyToChange _ProppertyToChange, FPropertyIndex PropertyIndex) const;
	UFUNCTION()  
	EVisibility GetVisibility_GlobalVarIndicator(EProppertyToChange _ProppertyToChange, FPropertyIndex PropertyIndex) const;
	UFUNCTION()  
	EVisibility GetVisibilityOfSectionPropperty_Static(EProppertyToChange _ProppertyToChange, FPropertyIndex PropertyIndex) const;  
	UFUNCTION()  
	EVisibility GetVisibilityOfSectionPropperty_Editable(EProppertyToChange _ProppertyToChange, FPropertyIndex PropertyIndex) const;
	UFUNCTION()  
	FText GetProppertyText(EProppertyToChange _ProppertyToChange, FPropertyIndex PropertyIndex) const;   
	UFUNCTION()  
	void ConfirmEditableTextBox(const FText& Text, ETextCommit::Type TextType, EProppertyToChange ProppertyToChange, FPropertyIndex PropertyIndex);
	UFUNCTION()  
	void ConfirmEditableMultilineTextBox(const FText& Text, ETextCommit::Type TextType, EProppertyToChange ProppertyToChange, FPropertyIndex PropertyIndex);


	//   ConfirmCurrentSelection  //  HIDDEN-BUTTON BECOME UNHITTED, Breack this
	UFUNCTION()  
	void ConfirmCurrentSelection(EProppertyToChange _ProppertyToChange, FPropertyIndex changingPropperty);
	UFUNCTION()  
	void OnEditableTextChange(const FText& _Text);





	//  ================================           Combo-Box         ==============================================
	UFUNCTION()  
	void InitComboBox_StaticList();   
	TSharedRef<SWidget> HandleComboBoxGenerateWidget(TSharedPtr<FString> InItem);
	UPROPERTY()  
	TArray<TSharedPtr<FString>> ReplicRepeatComboList;
	UPROPERTY()  
	TArray<TSharedPtr<FString>> ResponseRepeatComboList;
	UPROPERTY()  
	TArray<TSharedPtr<FString>> ResponseReturnTypeComboList;

	
	UFUNCTION()  
	void GetReplicRepeatComboList(TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo, FPropertyIndex PropertyIndex);   //XXXXXXXXXXX   ++++++++++++++
	UFUNCTION()  
	void GetResponseRepeatComboList(TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo, FPropertyIndex PropertyIndex);   //XXXXXXXXXXX   ++++++++++++++
	UFUNCTION()  
	void GetResponseReturnTypeComboList(TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo, FPropertyIndex PropertyIndex);   //XXXXXXXXXXX   ++++++++++++++
	//void OnReplicRepeatComboBoxOpening(FPropertyIndex PropertyIndex);
	UFUNCTION()  
	FText GetCurrentReplicRepeatLabel(FPropertyIndex PropertyIndex) const;
	UFUNCTION()  
	FText GetCurrentResponseRepeatLabel(FPropertyIndex PropertyIndex) const;
	UFUNCTION()  
	FText GetCurrentResponseReturnTypeLabel(FPropertyIndex PropertyIndex) const;

	UPROPERTY()
		FString EditableChangedText;


	// ================================        SMenuAnchor   "HelperMeny"     ==============================================

	//FGeometry CachedGeometry;
	UPROPERTY()
		EProppertyToChange CurrProppertyToChange;
	UPROPERTY()
		FPropertyIndex CurrPropertyIndex;

	TSharedPtr<class SEditableTextBox> OnHelperPanel_FindingEditableText;

	UPROPERTY()  
	float HelperMenu_Height = 30.f;
	UFUNCTION()  
	FOptionalSize GetHelperMenu_Height() const;
	UPROPERTY()  
	bool CalculateHelperMenuPosition = false;
	UPROPERTY()  
	bool isHelperMenuOpen = false; 
	UFUNCTION()  
	EVisibility GetHelperPanelVisibility() const;
	UPROPERTY()  
	FMargin HelperPanelPosition = FMargin(0,0,0,0);
	UFUNCTION()  
	FMargin  GetHelperPanelPosition() const;
	UFUNCTION()  
	FReply CancelHelperPanel();
	UFUNCTION()  
	FReply OnHelperPanelClick(EProppertyToChange ProppertyToChange, FPropertyIndex PropertyIndex);  
	UFUNCTION()  
	FReply OnHelperPanelElementClick(EProppertyToChange ProppertyToChange, FPropertyIndex PropertyIndex, int32 index);
	UPROPERTY()  
	TSharedPtr<class SScrollBox> HelperMenulList;
	UPROPERTY()  
	TSharedPtr<class SEditableTextBox> HelperMenulEditableText;
	UPROPERTY()  
	TArray<FString> ListElementTmp;   //  HelperPanel temporare list
	UFUNCTION()  
	void OnHelperPanel_FindingTextChange(const FText& _Text);
	UPROPERTY()  
	FString FastFindingHelperString = FString("");
	UPROPERTY()  
	TArray<int32> HelperPanel_FastFindingListIndexes;


	
	// ---------------- SSpinBox -----------------------
	//float GetTimeValue(float value);
	UFUNCTION()  
	void SetTimeValue(float value, ETextCommit::Type _Type, EProppertyToChange ProppertyToChange, FPropertyIndex PropertyIndex);
	//void SetTimeValue(double _NewValue, ECommitMethod _CommitMethod, ETextCommit::Type _Type);
	//++++static void SetDelayValue(float value/*, EProppertyToChange _ProppertyToChange, FPropertyIndex PropertyIndex*/);
	
	UFUNCTION()  
	void SaveDialogToXML();
	UFUNCTION()  
	void LoadDialogFromXML();
	UFUNCTION()  
	void ChoiseLoadingXmlFile();
	UFUNCTION()  
	FReply OnButtonExportDialog();
	UFUNCTION()  
	FReply OnButtonImportDialog();
	UPROPERTY()  
	FString* PathToCurrentXML = nullptr;

	//++++++++++++++++++++++++++++++++++++++++   SPEKER Block  ++++++++++++++++++++++
	  
	TSharedPtr<class SScrollBox> MainSpikersPanelBlock;       //    Spikers
	TSharedPtr<class SScrollBox> MainSpikersEditablePanelBlock;       //    Spikers sEditable TimerPanel 
	UFUNCTION()  
	void MainSpikersEditablePanel_FindExtBlock(const FText& _Text, int32 type);  // type 1=Sound, 2=Image
	//TSharedPtr<class SEditableTextBox> bMainSpikersEditablePanel_Find;

	UPROPERTY()  
	TArray<FString> AssetPathName;
	UPROPERTY()  
	TArray<int32> AssetPathSortByName;
	UPROPERTY()  
	FString FindedText_InMainSpikerEditablePanel;
	UPROPERTY()  
	bool IsStartFinding = false;

	UPROPERTY()  
	int32 iCurrentEditableSpeker;
	UPROPERTY()  
	int32 iCurrentEditableSound;

	UFUNCTION()  
	void SaveSpekersToXML();
	UFUNCTION()  
	void LoadSpekersfromXML();
	UFUNCTION()  
	void LoadSoundFromXMLSpeker(FName FoundingSpeker);  
	UPROPERTY()  
	const FSlateBrush* SpekersImageDefault;
	UFUNCTION()  
	void RedrawSpekersBlock();
	//FReply AddSpekersElenemt();
	UFUNCTION()  
	FReply RemoveSpekerElenemt(int32 _index);
	UPROPERTY()  
	TArray<FSpekers> Speker;  //  Temp loaded Speker (combo bob-loaded)
	//TArray<FSound> Sound;

	//int32 changingSpeker_Index = -1;

	UFUNCTION()  
	FReply StoredSpekerIndex(EProppertyToChange _ProppertyToChange, int32 _index);
	UFUNCTION()  
	FReply ChangeSpekerImage(int32 _index);
	UFUNCTION()  
	void RedrawSpekerImageFindingItem(int32 iSpeker, int32 iSound);
	//FReply AddSpekerSound(int32 _index);
	
	UFUNCTION()  
	FReply ApplayImageAssetToSpeker(int32 _index);
	UFUNCTION()  
	const FSlateBrush* GetSpekerImage(int32 _index) const;
	UFUNCTION()  
	EVisibility GetVisibilitySpekerNameText_Static(int32 _Index) const;
	UFUNCTION()  
	EVisibility GetVisibilitySpekerNameText_Editable(int32 _Index) const;
	UFUNCTION()  
	FText GetSpikerNameText(int32 _Index) const;

	UPROPERTY()  
	TArray<FString> AssetImagePath;
	UPROPERTY()  
	TArray<FSlateBrush> AssetImageBrush;
	UPROPERTY()  
	EVisibility vMainSpikersEditablePanel_FindImage = EVisibility::Collapsed;  //  find Editable block is visible in LoadingVindow

	//  ConfirmCurrentSelection();



	//++++++++++++++++++++++++++++++++++++++++   SOUND Block  ++++++++++++++++++++++
	  
	UFUNCTION()  
	FSlateColor GetSelectedSoundItem_Color(int32 iSpeker, int32 iSound) const;
	UPROPERTY()  
	TArray<FSound> Sound;     //  Temp loaded SpekerSound (combo bob-loaded)
	UFUNCTION()  
	FReply AddSpekerSound(int32 iSpeker);
	UFUNCTION()  
	void RedrawSoundsBlock(int32 iSpeker);
	UFUNCTION()  
	FReply ChangeSpekerSoundItem(int32 iSpeker, int32 iSound);
	UFUNCTION()  
	FReply PlaySoundItem(int32 iSpeker, int32 iSound);
	UFUNCTION()  
	void RedrawSpekerSoundFindingItem(int32 iSpeker, int32 iSound);
	UFUNCTION()  
	FReply ShowSpekerSoundItem(int32 iSpeker, int32 iSound);
	UFUNCTION()  
	FReply ApplaySaundToSpekerSound(int32 iSpeker, int32 iSpekerSound, int32 iSound);
	UFUNCTION()  
	FText GetSoundNameText(int32 _iSpeker, int32 _iSound) const;
	UFUNCTION()  
	FText GetSoundCommentText(int32 _iSpeker, int32 _iSound) const;
	UFUNCTION()  
	FText GetSoundPathText(int32 _iSpeker, int32 _iSound) const;
	UFUNCTION()  
	void SpekerSoundNameEditableTextBox(const FText& Text, ETextCommit::Type TextType, int32 iSpeker, int32 iSpekerSound);
	UFUNCTION()  
	void SpekerSoundCommentEditableTextBox(const FText& Text, ETextCommit::Type TextType, int32 iSpeker, int32 iSpekerSound);
	UPROPERTY()  
	EVisibility vMainSpikersEditablePanel_FindSound = EVisibility::Collapsed;  //  find Editable block is visible in LoadingVindow
	//int32 changingSpekerSound_Index = -1; 

	UPROPERTY()  
	TArray<FString> AssetSoundPath;
	//TArray<FString> AssetPathName;   //+++++
	//TArray<int32> AssetPathSortByName;  //++++++

	 
	//++++++++++++++++++++++++++++++++++++++  indicator  **********************************

	UFUNCTION()
		void RedrawIndicator();


	//++++++++++++++++++++++++++++++++++++++++   Content, Fast Blocks finder  ++++++++++++++++++++++
	UFUNCTION()
		TSharedPtr<class SEditableTextBox> FindDialodBlock_EditableText;
	UFUNCTION()
		TSharedPtr<class SEditableTextBox> FindSpeechBlock_EditableText;
	UPROPERTY()
		FString sContentDialogFinder = FString("DEFAULT");
	UPROPERTY()
		FString sContentSpeechFinder = FString("DEFAULT");
	UFUNCTION()
		void OnEditableTextChange_ContentFinding(const FText& _Text, FName Type);
	//TSharedPtr<class SButton> FindContentBlock_Button;
	UFUNCTION()
		void SelectFindingContentBlock(bool Select = false,
						FString DialogName = FString("DEFAULT"),
						FString SpeechName = FString("DEFAULT"));
	UFUNCTION()
		FReply FindNextContentBlock();
	//UFUNCTION()
		//FReply ScrollToContentBlock(int32 iDialog, int32 iSpeech);
	UFUNCTION()
		float GetContentBlockIndex(int32& _iDialodSection, int32& _iSpeechSection);

	//   +++++++++++++++++++++++    VARIABLE Block    ++++++++++++++++++++++

	UPROPERTY()  
	TArray<FVariables> Variables;   // iVariable
	TSharedPtr<class SScrollBox> MainVariablesPanelBlock;		  //   Main Panel Variables, where will add new variables.   ScrollBox
	UPROPERTY()  
	FString DefaultDialog = FString("DEFAULT");

	UFUNCTION()  
	void RedrawVariablesBlock();
	UFUNCTION()  
	void AddVariable(FPropertyIndex PropertyIndex);
	UFUNCTION()  
	void RemoveVariable(FPropertyIndex PropertyIndex);

	UFUNCTION()  
	void SaveVariablesToXML();
	UFUNCTION()  
	void LoadVariablesFromXML();
	// LoadSpekersfromXML
	//
	//+++++++++++++++++++++    Element SIZE    ++++++++++++++++++++++++++ 

	UPROPERTY()  
	float SizeKoef = 0.8f;   //    * SizeKoef
	//float buttonSizeKoef = 1.f;
	 
	UPROPERTY()  
	float DialogSectionSize = 50.f;
	UPROPERTY()  
	float SpeechSectionSize = 45.f;
	UPROPERTY()  
	float ReplicSectionSize = 40.f; 
	UPROPERTY()  
	float ReplicMultiplyTextSize = 80.f;
	UPROPERTY()  
	float RepSectionSize = 40.f;	
	UPROPERTY()  
	float RepMultiplyTextSize = 80.f;	
	UPROPERTY()  
	float ResponseSectionSize = 40.f;
	UPROPERTY()  
	float ResponseMultiplyTextSize = 80.f;
	UPROPERTY()  
	float ConditionSectionSize = 35.f;
	UPROPERTY()  
	float RepsonseVariablesSectionSize = 35.f;
	UPROPERTY()  
	float MultiplyTextSize = 20.f;
	UPROPERTY()  
	float MultiplyTextMaxSize = 80.f;

	UPROPERTY()  
	float DialogButtonSmallSize = 22.f;
	UPROPERTY()  
	float DialogButtonBigSize = 42.f;

	UPROPERTY()  
	float SpeechButtonSmallSize = 22.f;
	UPROPERTY()  
	float SpeechButtonBigSize = 38.f;

	UPROPERTY()  
	float ReplicButtonRemoveSize = 24.f;
	UPROPERTY()  
	float ReplicButtonMoveSize = 22.f;
	UPROPERTY()  
	float ReplicButtonAddSize = 21.f;
	UPROPERTY()  
	float ReplicButtonSmallSize = 20.f;
	UPROPERTY()  
	float ReplicButtonBigSize = 35.f;
	UPROPERTY()  
	float RepButtonSmallSize = 22.f;
	UPROPERTY()  
	float RepButtonSmallInsileSSize = 20.f;

	UPROPERTY()  
		FLinearColor ColorUsualText = FLinearColor(0.7f, 0.77f, 1.f, 1);     // Blue (light)
	UPROPERTY()  
		FLinearColor ColorUsualMarked = FLinearColor(1.f, 0.25f, 0.f, 1);     // Brown
	UPROPERTY()  
		FLinearColor ColorFastFindMarked = FLinearColor(1.f, 0.7f, 0.3f, 1);     // Brown (light)

	//FLinearColor ColorLinkMarked = FLinearColor(0.f, 0.f, 1.f, 1);        //  Blue
	UPROPERTY()  
		FLinearColor ColorLinkMarked = FLinearColor(0.15f, 0.15f, 0.8f, 1);        // blue                  ///  purple 

	//FLinearColor ColorDestinationLinkMarked = FLinearColor(0.f, 0.7f, 0.f, 1);  // Green
	UPROPERTY()  
		FLinearColor ColorDestinationLinkMarked = FLinearColor(0.3f, 0.8f, 0.3f, 1);  //  Green          // blue
	UPROPERTY()  
		FLinearColor ColorErrorMarked = FLinearColor(0.8f, 0.f, 0.f, 1);     // Red
	UPROPERTY()  
		FLinearColor ColorInvisible = FLinearColor(0.f, 0.f, 0.f, 0);     // Red

	UPROPERTY()  
		FSlateColor SelectedSoundItemColor = FSlateColor(FLinearColor(0.8f, 0.8f, 0.8f, 0.5f));
	UPROPERTY()  
		FSlateColor UnSelectedSoundItemColor = FSlateColor(FLinearColor(1.f, 1.f, 1.f, 0.2f));

	//float RepButtonBigSize = 27.f;
	UFUNCTION()  
		FOptionalSize GetButtonSize(float size) const;
	UFUNCTION()  
		FMargin GetPadding(float left, float Up, float Right, float Bottom);
	//this, &SDialogWindowWidget::GetDuttonSize, ReplicButtonBigSize
	
	//++++++++++++++++++++++++++++++++++++++++++++++++
   

};
