// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Widgets/Input/SSpinBox.h"

#include "Widgets/SCompoundWidget.h"
  
#include "DialogSystem/Include/pugixml.hpp"


UENUM()  //BlueprintType, Blueprintable
enum class EProppertyToChange : uint8
{
	none, 

	DialogName,
	SpeechName,
	ReplicNameCommentary,
	repeatReplic,
	ResponseNameCommentary,
	repeatResponse,
	DialogLink,
	SpeechLink,
	ResponseReturnType, 
	//Delay,
	//AfrerDelay,
	speker,  // rep
	sound,   // rep
	RepEvent,
	time,    // rep
	delay,   // rep

	Speech_condition_type,
	Speech_condition_varType,
	Speech_condition_CompareType,
	Speech_condition_varName,
	Speech_condition_varValue,
	Replic_condition_type,
	Replic_condition_varType,
	Replic_condition_CompareType,
	Replic_condition_varName,
	Replic_condition_varValue,
	rep_condition_type,
	rep_condition_varType,
	rep_condition_CompareType,
	rep_condition_varName,
	rep_condition_varValue,
	Response_condition_type,		// and/or
	Response_condition_varType,   // Global/LOcal
	Response_condition_CompareType,
	Response_condition_varName,
	Response_condition_varValue,

	Response_variable_varType,
	Response_variable_varName,
	Response_variable_varValue,
	Response_variable_IncrDecr,

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
	MoveReplic,
	MoveRep,
	MoveRep_Condition,
	MoveResponse,
	MoveResponse_Variable,
	Move_Condition,

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
	UPROPERTY()
		int32 iDialog = -1;
	UPROPERTY()
		int32 iSpeech = -1;
	UPROPERTY()
		int32 iReplic = -1;
	UPROPERTY()
		int32 iResponse = -1;
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



struct FIndicator
{
	FLinearColor color = FLinearColor(0.7f, 0.77f, 1.f, 1);
	float size = 0.f;
};

struct FVariablesParameter
{
	TSharedPtr<SVerticalBox>* ConditionBlock;
	TSharedPtr<SEditableTextBox>* TextBoxCondition_Type;
	TSharedPtr<SEditableTextBox>* TextBoxVariable_Name;
	TSharedPtr<SEditableTextBox>* TextBoxVariable_Value;
	UPROPERTY()
		FName* Type_Text;
	UPROPERTY()
		FName* VariableName_Text;
	UPROPERTY()
		FName* VariableValue_Text;
	UPROPERTY()
		EProppertyToChange AddButtonPropperty;
	UPROPERTY()
		EProppertyToChange RemoveButtonPropperty;
	UPROPERTY()
		EProppertyToChange ConditionTypePropperty;  // and/or
	UPROPERTY()
		EProppertyToChange CompareType;				//  =, != <, >, <=, >=
	UPROPERTY()
		EProppertyToChange VarTypePropperty;		// local / global
	UPROPERTY()
		EProppertyToChange VarNamePropperty;
	UPROPERTY()
		EProppertyToChange VarValuePropperty;


};

struct FVariables    //  Response change
{

	TSharedPtr<SComboBox<TSharedPtr<FString>>> CB_IncrDecr;                                   //   Increment / Decrement Combo
	TSharedPtr<FString>	Response_VarSet_IncrDecr = MakeShareable(new FString(TEXT("set")));   //   Increment / Decrement Value


	UPROPERTY()  
		FName VariableName = FName("none"); 
		TSharedPtr<class SEditableTextBox> ChangeVariable_Name_Editable;
		TSharedPtr<class UButton> ChangeVariable_Name_Button;
	UPROPERTY()  
		bool IsProperty_VariableName_EditNow = false;

	UPROPERTY()  
		FName VariableValue = FName("none");
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
};

struct FCondition
{
	UPROPERTY()  
		FName ConditionType = FName("and");
		TSharedPtr<class SEditableTextBox> Condition_Type_Editable;
		TSharedPtr<class UButton> ChangeCondition_Type_Button;
	UPROPERTY()  
		bool IsProperty_Type_EditNow = false;

	UPROPERTY()  
		FName VariableName = FName("none");
		TSharedPtr<class SEditableTextBox> ConditionVariable_Name_Editable;
		TSharedPtr<class UButton> ChangeConditionVariable_Name_Button;
	UPROPERTY()  
		bool IsProperty_VariableName_EditNow = false;

	UPROPERTY()
		FName VariableCompareType = FName("=");

	UPROPERTY()  
		FName VariableValue = FName("none");
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
};


struct FRepSection
{

	UPROPERTY()  
		FName Time = FName("0");

	UPROPERTY()  
		FName Delay = FName("0");

	UPROPERTY()  
		FName Speker = FName("none");

	UPROPERTY()  
		FName Sound = FName("none");

	TSharedPtr<class STextBlock> ReplicSectionRepeat_Statick;
	TSharedPtr<class SEditableTextBox> ReplicSectionRepeat_Editable;
	 
	UPROPERTY()  
		FString RepEvent = FString("RETURN_EVENT");
		TSharedPtr<class SEditableTextBox> RepEvent_EditableText;
	UPROPERTY()  
		bool isEventPropertyEditNow = false;

	UPROPERTY()  
		FLinearColor TextColor = FLinearColor(0.7f, 0.77f, 1.f, 1);

	UPROPERTY()  
		FString ComentText = FString("Dialog Game-phrase");
	UPROPERTY()  
		float ComentTextZoneSizeY = 0;

		TArray<FCondition> RepCondition;	
		TSharedPtr<class SVerticalBox> RepConditionBlock;
	UPROPERTY()  
		bool IsConditionOpen = false;

	UPROPERTY()  
		bool IsSectionEditNow = false;

	UPROPERTY()  
		bool IsUsualMarker = false;
	UPROPERTY()  
		bool IsErrorMarker = false;
};
  
struct FResponseSection 
{
	TSharedPtr<SComboBox<TSharedPtr<FString>>> CB_ResponseRepeat;
	TSharedPtr<FString>	ResponseRepeatPropperty = MakeShareable(new FString(TEXT("always")));

	TSharedPtr<SComboBox<TSharedPtr<FString>>> CB_ResponseReturnType;
	TSharedPtr<FString>	ResponseReturnTypePropperty = MakeShareable(new FString(TEXT("click"))); 
	 
	UPROPERTY()  
		FName DialogLink = FName("DEFAULT");
	UPROPERTY()  
		FName SpeechLink = FName("DEFAULT");
	UPROPERTY()  
		FString ComentText = FString("Dialog Game-Response");
	UPROPERTY()  
		float ComentTextZoneSizeY = 0;

	TSharedPtr<class SVerticalBox> ResponseBlock;

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
		bool IsSectionEditNow = false;
	UPROPERTY()  
		bool IsUsualMarker = false;
	UPROPERTY()  
		bool IsErrorMarker = false;
	UPROPERTY()  
		bool IsLinkMarker = false;
}; 
 
struct FReplicSection
{
	TSharedPtr<SComboBox<TSharedPtr<FString>>> CB_ReplicRepeat;
	TSharedPtr<FString>	ReplicRepeatPropperty = MakeShareable(new FString(TEXT("always")));

	UPROPERTY()  
		FString ComentText = FString("Commentary about all replic content. It's newer seen in game.");
	UPROPERTY()  
		float ComentTextZoneSizeY = 0;

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
};
     
struct FSpeechSection
{
	UPROPERTY()  
		FName Name = FName("DEFAULT");   

		TSharedPtr<class STextBlock> SpeechSectionName_Statick;
		TSharedPtr<class SEditableTextBox> SpeechSectionName_Editable;	 
	 

		TSharedPtr<class SVerticalBox> ReplicAndResponseBlock;
	UPROPERTY()  
		TArray<FReplicSection> ReplicSection;
	UPROPERTY()  
		TArray<FResponseSection> ResponseSection;
	UPROPERTY()  
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
		bool IsUsualMarker = false;        
	UPROPERTY()  
		bool IsErrorMarker = false;
	UPROPERTY()  
		bool IsSelfLinkMarker = false;
	UPROPERTY()  
		bool IsLinkMarker = false;         
	UPROPERTY()  
		bool IsDestinationMarker = false;  
	UPROPERTY()  
		bool IsFastFindMarker = false;
};


//USTRUCT(BlueprintType, Blueprintable)   
struct FDialogSection
{
//	GENERATED_BODY()

	UPROPERTY()  
		FName Name = FName("DEFAULT");   //  1 - "DEFAULT" and other "What_user_set"

	
	TSharedPtr<class SEditableTextBox> DialogSectionName_Editable;

	TSharedPtr<class SVerticalBox> SpeechBlock;

	UPROPERTY()  
		TArray<FSpeechSection> SpeechSection;

	UPROPERTY()  
		FLinearColor TextColor = FLinearColor(0.7f, 0.77f, 1.f, 1);

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
	UPROPERTY()  
		bool IsSelfLinkMarker = false;
	UPROPERTY()  
		bool IsLinkMarker = false;         
	UPROPERTY()  
		bool IsDestinationMarker = false;  
	UPROPERTY()  
		bool IsFastFindMarker = false;
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
		FString SpekersAssetPath;
	UPROPERTY()  
		FSlateBrush SpekersImageBrush;

	UPROPERTY()  
		TArray<FSound> Sound;

	UPROPERTY()  
		bool IsSectionEditNow = false;
};


UENUM()  //BlueprintType, Blueprintable
enum class ECurrentMainPanel : uint8
{
	Content,
	Variables,
	Spekers,
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

		TSharedPtr<class SButton> ContentPanelShowButton;
		TSharedPtr<class SButton> VariablesPanelShowButton;
		TSharedPtr<class SButton> SpekerPanelShowButton;
	UFUNCTION()
		FReply OnButtonSelectLayer(FName MainPanelType);

	UPROPERTY()  
		ECurrentMainPanel CurrentMainPanel = ECurrentMainPanel::Content;
	UPROPERTY()  
		EVisibility DialogContentVisibility = EVisibility::Visible;   
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
		EVisibility GetButtonAddNewElement_Visibility() const;
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


	
	//  =====================  Helper Comentary Text  ===============================
	UFUNCTION()
		FReply OnMouseConcreteBorderHover(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent, EProppertyToChange _ProppertyToChange);
	virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;  // Call hover on eny SlateElement
	UPROPERTY()
		FGeometry* CurrentGeometry = nullptr;
	UPROPERTY()
		float gTimeToHelperTextDraven = 6.0f;
	UPROPERTY()
		float gCurrentTimeToHelperTextDraven = 6.0f;
	UFUNCTION()
		EVisibility GetHelperCommentaryVisibility() const;
	UPROPERTY()
		bool isHelperCommentaryMenuOpen = false;

	UFUNCTION()
		FString GetCommentaryText(EProppertyToChange _ProppertyToChange);
	TSharedPtr<STextBlock> CommentaryTextBlock;

	//  =====================  copy or move section  ===============================
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
		FText GetCurrentDialogName() const;
	UFUNCTION()  
		FReply SaveAll();
	UFUNCTION()  
		FReply LoadAll();
	  

	UFUNCTION()  
		void UpdateDialogBlock();
	UFUNCTION()
		void DrawConditionElement(FPropertyIndex& CurrentPropertyIndex, FVariablesParameter& VarParam);

	UPROPERTY()  
		EShouldUpdate ShouldUpdate = EShouldUpdate::none;

	UFUNCTION()  
		void EditProperty(EProppertyToChange _ProppertyToChange, FPropertyIndex PropertyIndex);  
	UFUNCTION()  
		void SwitchCollapsedSection(EProppertyToChange _ProppertyToChange, FPropertyIndex PropertyIndex);

	UPROPERTY()  
		TArray<FDialogSection> DialogSection;


	//        ============================   Marker   ================================
	UFUNCTION()  
		FReply OnButtonMarkerUsual(const FGeometry& Geomet, const FPointerEvent& PEvent, EProppertyToChange ProppertyToChange, FPropertyIndex PropertyIndex);
	UFUNCTION()  
		FReply OnButtonMarkerLink(EProppertyToChange ProppertyToChange, FPropertyIndex PropertyIndex);
	UPROPERTY()  
		bool IsLinkMarkerDrawn = false;			 
	UPROPERTY()  
		int32 LastClickedSectionDialogIndex;  
	UPROPERTY()  
		int32 LastClickedSectionSpeechIndex;  
	UPROPERTY()  
		int32 LastClickedSectionResponseIndex;  
	


	UFUNCTION()  
		FReply OnButtonClick(EProppertyToChange ProppertyToChange, FPropertyIndex PropertyIndex);
	UFUNCTION()  
		FReply OnButtonRemoveClick(EProppertyToChange ProppertyToChange, FPropertyIndex PropertyIndex);

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
		TArray<TSharedPtr<FString>> ResponseVariableSetting_InctDecr_ComboList;
	UPROPERTY()  
		TArray<TSharedPtr<FString>> ResponseReturnTypeComboList;

	
	UFUNCTION()  
		void GetReplicRepeatComboList(TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo, FPropertyIndex PropertyIndex);   //XXXXXXXXXXX   ++++++++++++++
	UFUNCTION()  
		void GetResponseRepeatComboList(TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo, FPropertyIndex PropertyIndex);   //XXXXXXXXXXX   ++++++++++++++
	UFUNCTION()
		void GetResponseVarSet_InctDecr_ComboList(TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo, FPropertyIndex PropertyIndex);   //XXXXXXXXXXX   ++++++++++++++
	UFUNCTION()  
		void GetResponseReturnTypeComboList(TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo, FPropertyIndex PropertyIndex);   //XXXXXXXXXXX   ++++++++++++++
	UFUNCTION()  
		FText GetCurrentReplicRepeatLabel(FPropertyIndex PropertyIndex) const;
	UFUNCTION()  
		FText GetCurrentResponseRepeatLabel(FPropertyIndex PropertyIndex) const;
	UFUNCTION()
		FText GetCurrentResponseVarSet_InctDecr(FPropertyIndex PropertyIndex) const;
	UFUNCTION()  
		FText GetCurrentResponseReturnTypeLabel(FPropertyIndex PropertyIndex) const;

	UPROPERTY()
		FString EditableChangedText;


	// ================================        SMenuAnchor   "HelperMeny"     ==============================================

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
	UFUNCTION()  
		void SetTimeValue(float value, ETextCommit::Type _Type, EProppertyToChange ProppertyToChange, FPropertyIndex PropertyIndex);
	
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
	UFUNCTION()  
		FReply RemoveSpekerElenemt(int32 _index);
	UPROPERTY()  
		TArray<FSpekers> Speker;  //  Temp loaded Speker (combo box-loaded)

	UFUNCTION()  
		FReply StoredSpekerIndex(EProppertyToChange _ProppertyToChange, int32 _index);
	UFUNCTION()  
		FReply ChangeSpekerImage(int32 _index);
	UFUNCTION()  
		void RedrawSpekerImageFindingItem(int32 iSpeker, int32 iSound);
	
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

	UPROPERTY()  
		TArray<FString> AssetSoundPath;
	 
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
	UFUNCTION()
		void SelectFindingContentBlock(bool Select = false,
						FString DialogName = FString("DEFAULT"),
						FString SpeechName = FString("DEFAULT"));
	UFUNCTION()
		FReply FindNextContentBlock();
	UFUNCTION()
		float GetContentBlockIndex(int32& _iDialodSection, int32& _iSpeechSection);

	//   +++++++++++++++++++++++    VARIABLE Block    ++++++++++++++++++++++

	UPROPERTY()  
		TArray<FVariables> Variables;   
	TSharedPtr<class SScrollBox> MainVariablesPanelBlock;	//   Main Panel Variables, where will add new variables.   ScrollBox
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

	//+++++++++++++++++++++    Element SIZE    ++++++++++++++++++++++++++ 

	UPROPERTY()  
		float SizeKoef = 0.8f;   
	 
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

	UPROPERTY()  
		FLinearColor ColorLinkMarked = FLinearColor(0.15f, 0.15f, 0.8f, 1);        // blue                  ///  purple 

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

	UFUNCTION()  
		FOptionalSize GetButtonSize(float size) const;
	UFUNCTION()  
		FMargin GetPadding(float left, float Up, float Right, float Bottom);   

};
