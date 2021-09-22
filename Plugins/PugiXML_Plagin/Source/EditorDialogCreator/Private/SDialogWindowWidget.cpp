// Fill out your copyright notice in the Description page of Project Settings.




#include "SDialogWindowWidget.h"
#include "SlateOptMacros.h"

#include "AssetRegistryModule.h"
#include "Engine/Texture2D.h"  //#include "MediaTexture.h"
#include "Blueprint/WidgetBlueprintLibrary.h" // UWidgetBlueprintLibrary::MakeBrushFromTexture(FoundTexture2D, 64, 64)
//#include "Slate/DeferredCleanupSlateBrush.h"      //--------------

#include "EditorDialogCreatorStyle.h"    //const FDockTabStyle* GenericTabStyle = &FCoreStyle::Get().GetWidgetStyle<FDockTabStyle>("Docking.Tab");
#include "EditorDialogResourceStyle.h"   // DLG_EditorPanelStyle  (StyleResource in Editor)

#include "widgets/SCanvas.h"//
#include "Widgets/Layout/SBorder.h"
#include "Widgets/SOverlay.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Input/SEditableTextBox.h"
#include "Widgets/Input/SMultiLineEditableTextBox.h"
#include "Components/Spacer.h"
#include "Widgets/SBoxPanel.h"   //  VerticalBox, HorisontalBox
#include "Widgets/Images/SImage.h"
#include "Widgets/Input/SComboBox.h"//

#include "Widgets/Layout/SScrollBox.h"//
#include "Widgets/Layout/SExpandableArea.h"//

//#include "Kismet/GameplayStatics.h"   //   GetPlayerController    ,  GetAllActorsOfClass
//#include "Engine/GameViewportClient.h"
//#include "Framework/Application/SlateApplication.h"


//#include "StyleSet.h"
//#include "StyleSlate01Style.h"

#include "DesktopPlatformModule.h"					 // Dialog Window
#include "IDesktopPlatform.h"						 // Dialog Window

#include "Kismet/GameplayStatics.h"



#include "Rendering/DrawElements.h"

#include "Widgets/Images/SImage.h"

#include "../../PugiXML_Plagin/Include/pugiconfig.hpp"
#include "../../PugiXML_Plagin/Include/pugixml.cpp"
#include "../../PugiXML_Plagin/Include/pugixml.hpp"

#include "Sound/SoundBase.h"

#include "Misc/Paths.h"







BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SDialogWindowWidget::Construct(const FArguments& InArgs)
{

	PathToCurrentXML = InArgs._PathToFile.Get();



	ImageLayerActivate = &FEditorDialogCreatorStyle::GetContentStyle().GetWidgetStyle<FEditorDialogResourceStyle>("DLG_EditorPanelStyle").ImageLayerActivate;
	ImageLayerDefault = &FEditorDialogCreatorStyle::GetContentStyle().GetWidgetStyle<FEditorDialogResourceStyle>("DLG_EditorPanelStyle").ImageLayerDefault;
	TitleDialog = &FEditorDialogCreatorStyle::GetContentStyle().GetWidgetStyle<FEditorDialogResourceStyle>("DLG_EditorPanelStyle").TitleDialog;
	TitleDialogStart = &FEditorDialogCreatorStyle::GetContentStyle().GetWidgetStyle<FEditorDialogResourceStyle>("DLG_EditorPanelStyle").TitleDialogStart;
	TitleDialogEnd = &FEditorDialogCreatorStyle::GetContentStyle().GetWidgetStyle<FEditorDialogResourceStyle>("DLG_EditorPanelStyle").TitleDialogEnd;
	TitleReplic = &FEditorDialogCreatorStyle::GetContentStyle().GetWidgetStyle<FEditorDialogResourceStyle>("DLG_EditorPanelStyle").TitleReplic;
	TitleReplicStart = &FEditorDialogCreatorStyle::GetContentStyle().GetWidgetStyle<FEditorDialogResourceStyle>("DLG_EditorPanelStyle").TitleReplicStart;
	TitleReplicEnd = &FEditorDialogCreatorStyle::GetContentStyle().GetWidgetStyle<FEditorDialogResourceStyle>("DLG_EditorPanelStyle").TitleReplicEnd;
	TitleResponse = &FEditorDialogCreatorStyle::GetContentStyle().GetWidgetStyle<FEditorDialogResourceStyle>("DLG_EditorPanelStyle").TitleResponse;
	TitleResponseStart = &FEditorDialogCreatorStyle::GetContentStyle().GetWidgetStyle<FEditorDialogResourceStyle>("DLG_EditorPanelStyle").TitleResponseStart;
	TitleResponseEnd = &FEditorDialogCreatorStyle::GetContentStyle().GetWidgetStyle<FEditorDialogResourceStyle>("DLG_EditorPanelStyle").TitleResponseEnd;
	ImageButtonSectionRollUp = &FEditorDialogCreatorStyle::GetContentStyle().GetWidgetStyle<FEditorDialogResourceStyle>("DLG_EditorPanelStyle").ImageButtonSectionRollUp;
	ImageButtonSectionExpand = &FEditorDialogCreatorStyle::GetContentStyle().GetWidgetStyle<FEditorDialogResourceStyle>("DLG_EditorPanelStyle").ImageButtonSectionExpand;
	PropertyDialog = &FEditorDialogCreatorStyle::GetContentStyle().GetWidgetStyle<FEditorDialogResourceStyle>("DLG_EditorPanelStyle").PropertyDialog;
	PropertyDialogStart = &FEditorDialogCreatorStyle::GetContentStyle().GetWidgetStyle<FEditorDialogResourceStyle>("DLG_EditorPanelStyle").PropertyDialogStart;
	PropertyDialogEnd = &FEditorDialogCreatorStyle::GetContentStyle().GetWidgetStyle<FEditorDialogResourceStyle>("DLG_EditorPanelStyle").PropertyDialogEnd;
	PropertyReplic = &FEditorDialogCreatorStyle::GetContentStyle().GetWidgetStyle<FEditorDialogResourceStyle>("DLG_EditorPanelStyle").PropertyReplic;
	PropertyReplicStart = &FEditorDialogCreatorStyle::GetContentStyle().GetWidgetStyle<FEditorDialogResourceStyle>("DLG_EditorPanelStyle").PropertyReplicStart;
	PropertyReplicEnd = &FEditorDialogCreatorStyle::GetContentStyle().GetWidgetStyle<FEditorDialogResourceStyle>("DLG_EditorPanelStyle").PropertyReplicEnd;
	PropertyResponse = &FEditorDialogCreatorStyle::GetContentStyle().GetWidgetStyle<FEditorDialogResourceStyle>("DLG_EditorPanelStyle").PropertyResponse;
	PropertyResponseStart = &FEditorDialogCreatorStyle::GetContentStyle().GetWidgetStyle<FEditorDialogResourceStyle>("DLG_EditorPanelStyle").PropertyResponseStart;
	PropertyResponseEnd = &FEditorDialogCreatorStyle::GetContentStyle().GetWidgetStyle<FEditorDialogResourceStyle>("DLG_EditorPanelStyle").PropertyResponseEnd;

	ImageValueZone = &FEditorDialogCreatorStyle::GetContentStyle().GetWidgetStyle<FEditorDialogResourceStyle>("DLG_EditorPanelStyle").ImageValueZone;
	Condition = &FEditorDialogCreatorStyle::GetContentStyle().GetWidgetStyle<FEditorDialogResourceStyle>("DLG_EditorPanelStyle").Condition;
	ConditionStart = &FEditorDialogCreatorStyle::GetContentStyle().GetWidgetStyle<FEditorDialogResourceStyle>("DLG_EditorPanelStyle").ConditionStart;
	ConditionEnd = &FEditorDialogCreatorStyle::GetContentStyle().GetWidgetStyle<FEditorDialogResourceStyle>("DLG_EditorPanelStyle").ConditionEnd;
	ImageAddElement = &FEditorDialogCreatorStyle::GetContentStyle().GetWidgetStyle<FEditorDialogResourceStyle>("DLG_EditorPanelStyle").ImageAddElement;
	//ImageRemoveElement = &FEditorDialogCreatorStyle::GetContentStyle().GetWidgetStyle<FEditorDialogResourceStyle>("DLG_EditorPanelStyle").ImageRemoveElement;
	ImageMoveElement = &FEditorDialogCreatorStyle::GetContentStyle().GetWidgetStyle<FEditorDialogResourceStyle>("DLG_EditorPanelStyle").ImageMoveElement;
	SpekersImageDefault = &FEditorDialogCreatorStyle::GetContentStyle().GetWidgetStyle<FEditorDialogResourceStyle>("DLG_EditorPanelStyle").SpekersImageDefault;
	ImageDeleteElement = &FEditorDialogCreatorStyle::GetContentStyle().GetWidgetStyle<FEditorDialogResourceStyle>("DLG_EditorPanelStyle").ImageDeleteElement;
	ImageAddSoundElement = &FEditorDialogCreatorStyle::GetContentStyle().GetWidgetStyle<FEditorDialogResourceStyle>("DLG_EditorPanelStyle").ImageAddSoundElement;
	ImageConditionButtonOn = &FEditorDialogCreatorStyle::GetContentStyle().GetWidgetStyle<FEditorDialogResourceStyle>("DLG_EditorPanelStyle").ImageConditionButtonOn;
	ImageConditionButtonOFF = &FEditorDialogCreatorStyle::GetContentStyle().GetWidgetStyle<FEditorDialogResourceStyle>("DLG_EditorPanelStyle").ImageConditionButtonOFF;
	ImageVariableButtonOn = &FEditorDialogCreatorStyle::GetContentStyle().GetWidgetStyle<FEditorDialogResourceStyle>("DLG_EditorPanelStyle").ImageVariableButtonOn;
	ImageVariableButtonOff = &FEditorDialogCreatorStyle::GetContentStyle().GetWidgetStyle<FEditorDialogResourceStyle>("DLG_EditorPanelStyle").ImageVariableButtonOff;
	PlaySound = &FEditorDialogCreatorStyle::GetContentStyle().GetWidgetStyle<FEditorDialogResourceStyle>("DLG_EditorPanelStyle").PlaySound;
	MarkerLink = &FEditorDialogCreatorStyle::GetContentStyle().GetWidgetStyle<FEditorDialogResourceStyle>("DLG_EditorPanelStyle").MarkerLink;













	ChildSlot		
		[
			SNew(SBorder)
			[			
				SNew(SOverlay)
				.Visibility(EVisibility::Visible)//.Visibility(EVisibility::HitTestInvisible)

				+SOverlay::Slot()   //   ==============  All
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[

					//  ==================================================
					//  =============  TOP gorisontal Panel   ============
					//  ==================================================

					SNew(SVerticalBox)

					+ SVerticalBox::Slot()
					.HAlign(HAlign_Fill)
					//.VAlign(VAlign_Fill)
					.AutoHeight()
					//.MaxHeight(30.f)

					[
						SNew(SHorizontalBox)


						+SHorizontalBox::Slot()
						.Padding(4, 6, 2, 5)
						.HAlign(HAlign_Left)
						.VAlign(VAlign_Fill)
						.AutoWidth()
						//.FillWidth(1)
						[
							SAssignNew(ContentPanelShowButton, SButton)                        //    BUTTON  1
							//.ButtonStyle(&BallHUD->MenuButtonStyle)
							.Text(FText::FromString("Content"))
							// 777 .ButtonStyle(&InvStorage->EmptySlotButtonStyle)
							.ContentPadding(FMargin(4.f))
							.OnClicked(this, &SDialogWindowWidget::OnButtonSelectLayer, FName("content"))
						]
						+ SHorizontalBox::Slot()
						.Padding(2, 6, 2, 5)
						.HAlign(HAlign_Left)
						.VAlign(VAlign_Fill)
						.AutoWidth()
						//.FillWidth(1)
						[
							SAssignNew(VariablesPanelShowButton, SButton)                        //    BUTTON  2
							//.ButtonStyle(&BallHUD->MenuButtonStyle)
							.Text(FText::FromString("Variables"))
							.ContentPadding(FMargin(4.f))
							.OnClicked(this, &SDialogWindowWidget::OnButtonSelectLayer, FName("variables"))
						]
						+ SHorizontalBox::Slot()
						.Padding(2, 6, 2, 5)
						.HAlign(HAlign_Left)
						.VAlign(VAlign_Fill)
						.AutoWidth()
						//.FillWidth(1)
						[
							SAssignNew(SpekerPanelShowButton, SButton)							 //    BUTTON  3
							//.ButtonStyle(&BallHUD->MenuButtonStyle)
							.Text(FText::FromString("Spikers"))
							.ContentPadding(FMargin(4.f))
							.OnClicked(this, &SDialogWindowWidget::OnButtonSelectLayer, FName("spikers"))
						]





						// --------------   add New  ------------------------
						+ SHorizontalBox::Slot()
						.Padding(2, 6, 2, 5)
						.HAlign(HAlign_Left)
						.VAlign(VAlign_Fill)
						.AutoWidth()
						//.FillWidth(1)
						[

							SNew(SBox)
							.WidthOverride(32.f)
							.HeightOverride(32.f)
							[
								SNew(SButton)
								.ContentPadding(0)
								.OnClicked(this, &SDialogWindowWidget::AddNewElement)
								[
									SNew(SImage)
									.Image(ImageAddElement)
								]
							]
						]






						//    =====================   Fast finding (in Dialog content block)   ===================
						+SHorizontalBox::Slot()
						.Padding(1, 6, 1, 5)    // L, Up, R, Dn
						.HAlign(HAlign_Right)
						.VAlign(VAlign_Fill)
						//.AutoWidth()
						.FillWidth(1)
						[
							SNew(STextBlock)
							.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 14 * SizeKoef))
							//.ColorAndOpacity(FLinearColor(0.7f, 0.77f, 1.f, 1))
							.ColorAndOpacity(ColorUsualText)
							.Text(FText::FromString("Dialog:"))
						]
						+SHorizontalBox::Slot()
						.Padding(1, 6, 1, 5)    // L, Up, R, Dn
						.HAlign(HAlign_Right)
						.VAlign(VAlign_Fill)
						.AutoWidth()
						//.FillWidth(1)
						[
							SNew(SBox)
							.Padding(GetPadding(0, 0, 0, 0))
							//MaxDesiredWidth(FOptionalSize())
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Fill)
							.WidthOverride_Lambda([this]() -> float { return (200.f * SizeKoef); })
							//.HeightOverride(40.f * SizeKoef)
							[
								SAssignNew(FindDialodBlock_EditableText, SEditableTextBox)
								.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 14 * SizeKoef))
								.Text(FText::FromString(FString("DEFAULT")))
								.OnTextChanged_Raw(this, &SDialogWindowWidget::OnEditableTextChange_ContentFinding, FName("dialog")) // "dialog" , "speech"  // void OnButtonT(const FText& Text);
							]
						]
						+ SHorizontalBox::Slot()
						.Padding(3, 6, 1, 5)    // L, Up, R, Dn
						.HAlign(HAlign_Right)
						.VAlign(VAlign_Fill)
						.AutoWidth()
						//.FillWidth(1)
						[
							SNew(STextBlock)
							.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 14 * SizeKoef))
							//.ColorAndOpacity(FLinearColor(0.7f, 0.77f, 1.f, 1))
							.ColorAndOpacity(ColorUsualText)
							.Text(FText::FromString("Speech:"))
						]
						+SHorizontalBox::Slot()
						.Padding(1, 6, 1, 5)    // L, Up, R, Dn
						.HAlign(HAlign_Right)
						.VAlign(VAlign_Fill)
						.AutoWidth()
						//.FillWidth(1)
						[
							SNew(SBox)
							.Padding(GetPadding(0, 0, 0, 0))
							//MaxDesiredWidth(FOptionalSize())
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Fill)
							.WidthOverride_Lambda([this]() -> float { return (200.f * SizeKoef); })
							//.HeightOverride(40.f * SizeKoef)
							[
								SAssignNew(FindSpeechBlock_EditableText, SEditableTextBox)
								//.SetMinimumDesiredWidth(60.f * SizeKoef)
								.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 14 * SizeKoef))
								.Text(FText::FromString(FString("DEFAULT")))
								.OnTextChanged_Raw(this, &SDialogWindowWidget::OnEditableTextChange_ContentFinding, FName("speech")) // "dialog" , "speech"  // void OnButtonT(const FText& Text);
							]
				
						]

						//***********************************************************************
						//***********************************************************************
						//******************             FAST   FINDING   BUTTON     ************     ///   NOT WORK
						//***********************************************************************
						//***********************************************************************
						+SHorizontalBox::Slot()
						.Padding(GetPadding(1, 6, 30, 5))    // L, Up, R, Dn
						.HAlign(HAlign_Right)
						.VAlign(VAlign_Fill)
						.AutoWidth()
						//.FillWidth(1)
						[
							SNew(SButton)							 //    BUTTON  Fast-Find 
							//.ButtonStyle(&BallHUD->MenuButtonStyle)
							.Text(FText::FromString("zzz"))
							.ContentPadding(FMargin(0.f))
							.OnClicked(this, &SDialogWindowWidget::FindNextContentBlock) 
						]
			
						//***********************************************************************
						//***********************************************************************
						//***********************************************************************
						//***********************************************************************



						+ SHorizontalBox::Slot()
						.Padding(2, 6, 2, 5)
						.HAlign(HAlign_Right)
						.VAlign(VAlign_Fill)
						.AutoWidth()
						//.FillWidth(1)
						[
							SAssignNew(SpekerPanelShowButton, SButton)							 //    BUTTON  Right
							//.ButtonStyle(&BallHUD->MenuButtonStyle)
							.Text(FText::FromString("Save dialog"))
							.ContentPadding(FMargin(4.f))
							.OnClicked(this, &SDialogWindowWidget::SaveAll) //  FName("Save")
						]
						+ SHorizontalBox::Slot()
						.Padding(2, 6, 2, 5)
						.HAlign(HAlign_Right)
						.VAlign(VAlign_Fill)
						.AutoWidth()
						//.FillWidth(1)
						[
							SAssignNew(SpekerPanelShowButton, SButton)							 //    BUTTON  Right
							//.ButtonStyle(&BallHUD->MenuButtonStyle)
							.Text(FText::FromString("Load dialog"))
							.ContentPadding(FMargin(4.f))
							.OnClicked(this, &SDialogWindowWidget::LoadAll) // FName("Load")
						]
					]



		
					//  ============================================================
					//  ======================     CONTENT     =====================
					//  ============================================================
					+SVerticalBox::Slot()
					.VAlign(VAlign_Fill)
					.HAlign(HAlign_Fill)
					.FillHeight(1)
					[

						SNew(SHorizontalBox)             //  LeftMarker + SCROLL_Content + Right_Marker
						.Visibility_Lambda([this]() -> EVisibility { return DialogContentVisibility; })  // Collapsed  Visible




						+ SHorizontalBox::Slot()             //  CONTENT  SCROLL
						.HAlign(HAlign_Fill)
						.VAlign(VAlign_Fill)
						//.MaxHeight(30.f)

						[
							//=======================================================================================
							// ===============================  SCROLL in Content  ==================================
							//=======================================================================================

							SAssignNew(MainContentPanelBlock, SScrollBox)                      
						]

						+ SHorizontalBox::Slot()            // --------------   Right indicators  Content ------------------------
						//.Padding(4.f)
						.AutoWidth()
						.HAlign(HAlign_Left)
						.VAlign(VAlign_Fill)
						.MaxWidth(DialogButtonSmallSize * SizeKoef)
						[
								SAssignNew(RightIndicator, SVerticalBox)
						]
					]


		 

					//  ============================================================
					//  ===================   VARIABLES Block    ===================
					//  ============================================================
					+SVerticalBox::Slot()
					.VAlign(VAlign_Fill)
					.HAlign(HAlign_Fill)
					//.AutoHeight()   //  not scrplling
					.FillHeight(1)
					[

						SNew(SHorizontalBox)             //  LeftMarker + SCROLL_Content + Right_Marker
						.Visibility_Lambda([this]() -> EVisibility { return DialogVariablesVisibility; })  // Collapsed  Visible

						+ SHorizontalBox::Slot()             //  CONTENT  SCROLL
						.HAlign(HAlign_Fill)
						.VAlign(VAlign_Fill)
						//.MaxHeight(30.f)

						[
							SAssignNew(MainVariablesPanelBlock, SScrollBox)                       // SCROLL in Content 
						]
					]



					//  ============================================================
					//  ===================   SPEKERS  ===================
					//  ============================================================
					+SVerticalBox::Slot()
					.VAlign(VAlign_Fill)
					.HAlign(HAlign_Fill)
					//.AutoHeight()   //  not scrolling
					.FillHeight(1)
					[

						SNew(SHorizontalBox)             //  LeftMarker + SCROLL_Content + Right_Marker
						//--.Padding(10)
						.Visibility_Lambda([this]() -> EVisibility { return DialogSpikersVisibility; })  // Collapsed  Visible

						+ SHorizontalBox::Slot()             //  CONTENT  SCROLL
						.HAlign(HAlign_Fill)
						.VAlign(VAlign_Fill)
						//.AutoWidth()
						.FillWidth(1)
						//.MaxHeight(30.f)

						[
							SNew(SHorizontalBox)

							+ SHorizontalBox::Slot()
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Fill)
							//.HillWidth(1)
							[
								SAssignNew(MainSpikersPanelBlock, SScrollBox)               // SCROLL in SpikersPanelBlock 

							]

							+ SHorizontalBox::Slot()
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Fill)
							//.HillWidth(1)
							[

								SNew(SVerticalBox)

								+ SVerticalBox::Slot()
								.HAlign(HAlign_Fill)
								.VAlign(VAlign_Top)
								.AutoHeight()
								[
									SNew(SBox)
									.HeightOverride(30.f * SizeKoef)
									[
										SNew(SEditableTextBox)
										.Visibility_Lambda([this]() -> EVisibility { return vMainSpikersEditablePanel_FindSound; })
										.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 12 * SizeKoef))
										.OnTextChanged_Raw(this, &SDialogWindowWidget::MainSpikersEditablePanel_FindExtBlock, 1) // 1=Sound  // void OnButtonconst FText& Text);
										.Text_Lambda([this]() -> FText { return FText::FromString(FindedText_InMainSpikerEditablePanel); })

									]
								]
						
								+ SVerticalBox::Slot()
								.HAlign(HAlign_Fill)
								.VAlign(VAlign_Top)
								.AutoHeight()
								[
									SNew(SBox)
									.HeightOverride(30.f * SizeKoef)
									[
										SNew(SEditableTextBox)
										.Visibility_Lambda([this]() -> EVisibility { return vMainSpikersEditablePanel_FindImage; })
										.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 12 * SizeKoef))
										.OnTextChanged_Raw(this, &SDialogWindowWidget::MainSpikersEditablePanel_FindExtBlock, 2) // 1=Image  // void OnButtonconst FText& Text);
										.Text_Lambda([this]() -> FText { return FText::FromString(FindedText_InMainSpikerEditablePanel); })
									]
								]

								+ SVerticalBox::Slot()
								.HAlign(HAlign_Fill)
								.VAlign(VAlign_Top)
								[
									SAssignNew(MainSpikersEditablePanelBlock, SScrollBox)        // SCROLL - Editable in SpikersPanelBlock 
								]
							]
		
						]
					]
				]

				//  =====================================================
				//  =====================================================
				//  ==================  HelperMenu   ====================
				//  =====================================================
				//  =====================================================
				+ SOverlay::Slot()
				[
					SNew(SButton)
					.ButtonColorAndOpacity(FLinearColor(0.05f, 0.05f, 0.06f, 0.0f))
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.Visibility(this, &SDialogWindowWidget::GetHelperPanelVisibility)
					.OnClicked(this, &SDialogWindowWidget::CancelHelperPanel)
				]

				+ SOverlay::Slot()
				//.Padding(20.f, 100, 0, 0)    
				.Padding(TAttribute<FMargin>(this, &SDialogWindowWidget::GetHelperPanelPosition))   //  related menu Position
				.HAlign(HAlign_Left)
				.VAlign(VAlign_Top)
				[
					SNew(SBox)
					.Visibility(this, &SDialogWindowWidget::GetHelperPanelVisibility)
					//.Padding(FMargin(20.f, 100))
					//.WidthOverride(100.f)
					//.HeightOverride(700.f)													
					.HeightOverride(this, &SDialogWindowWidget::GetHelperMenu_Height)             
					.MinDesiredHeight(60.f)
					[
						SNew(SBorder)
						.Padding(0)
						.HAlign(HAlign_Fill)
						.VAlign(VAlign_Fill)
						.BorderImage(TitleDialog)
						[

							SNew(SBox)
							.Padding(FMargin(0))
							//.MaxDesiredWidth(300.f)
							.MinDesiredHeight(60.f)
							//.HAlign(HAlign_Fill)
							.VAlign(VAlign_Top)
							//.WidthOverride(20.f)
							//.HeightOverride(25.f)
							[
								SNew(SVerticalBox)

								+SVerticalBox::Slot()
								.Padding(0.f)
								.HAlign(HAlign_Fill)
								.VAlign(VAlign_Top)
								.AutoHeight()
								[
									SNew(SBox)
									.Padding(GetPadding(5.f, 5.f, 5.f, 5.f))
									//.MinDesiredWidth(70.f)
									.HeightOverride(36.f * SizeKoef)  // HelperMenu_Height = 30
									.HAlign(HAlign_Fill)
									.VAlign(VAlign_Fill)
									[
										//  ===========================  DIALOG-Name EditableText  ================================
										SAssignNew(OnHelperPanel_FindingEditableText, SEditableTextBox)
										.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 12 * SizeKoef))
										.Text_Lambda([this]() -> FText { return FText::FromString(FastFindingHelperString); })
										.OnTextChanged_Raw(this, &SDialogWindowWidget::OnHelperPanel_FindingTextChange)  // void OnButtonT(const FText& Text);
									]
								]

								+SVerticalBox::Slot()
								.Padding(0.f)
								.HAlign(HAlign_Fill)
								.VAlign(VAlign_Top)
								[
									SAssignNew(HelperMenulList, SScrollBox)                       // SCROLL in HelperMenulList 
								]
							]
						]
					]
				]

			]
		];

	//        END   END   END   END   END   END   END   END   END   END   END   END   END   END   END   END   END   END   END   END  
	//     END   END   END   END   END   END   END   END   END   END   END   END   END   END   END   END   END   END   END   END   
	//        END   END   END   END   END   END   END   END   END   END   END   END   END   END   END   END   END   END   END   END   
	 



	InitComboBox_StaticList();

	LoadDialogFromXML();
	LoadSpekersfromXML();
	LoadVariablesFromXML();




}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
 


void SDialogWindowWidget::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{



	//   ========================   Draw   HelperMenu at  Cursor Position  ========================

	//  ******************************************************************************************************************************
	//  **********************************************************    Not Correct Work   ***************************************************
	//  ************************************************************************************************************************

	//CachedGeometry = AllottedGeometry;
	if (CalculateHelperMenuPosition && isHelperMenuOpen == false)
	{ 
		FSlateApplication& SlateAplication = FSlateApplication::Get();
		if (SlateAplication.GetActiveTopLevelWindow())
		{
			isHelperMenuOpen = true;
			FVector2D _ClickPos = SlateAplication.GetCursorPos();
			FVector2D _ViewportSize = SlateAplication.GetActiveTopLevelWindow()->GetViewportSize();  //AllottedGeometry.GetAbsoluteSize();  
			//FVector2D _ViewportSize = AllottedGeometry.GetAbsoluteSize();  

			_ClickPos = AllottedGeometry.AbsoluteToLocal(_ClickPos);

			float aaa = _ViewportSize.Y - _ClickPos.Y;
			if (HelperMenu_Height > _ViewportSize.Y)
			{
				HelperPanelPosition = HelperPanelPosition = FMargin(_ClickPos.X, 0, 0, 0);
			}
			else if (HelperMenu_Height < aaa)  //700
			{
				HelperPanelPosition = FMargin(_ClickPos.X, _ClickPos.Y, 0, 0);

				//
			}
			else
			{
				int32 delta_Y = (_ClickPos.Y + HelperMenu_Height) - _ViewportSize.Y;  //700
				HelperPanelPosition = FMargin(_ClickPos.X, _ClickPos.Y - delta_Y, 0, 0);
			}
		//UE_LOG(LogTemp, Warning, TEXT("ddddddddd  x= %f,      x= %f"), ClickPos.X, ClickPos.Y);
		}
		CalculateHelperMenuPosition = false;
	}
	 
}





int32 SDialogWindowWidget::OnPaint(const FPaintArgs& Args,
							const FGeometry& AllottedGeometry,
							const FSlateRect& MyCullingRect,
							FSlateWindowElementList& OutDrawElements,
							int32 LayerId,
							const FWidgetStyle& InWidgetStyle,
							bool bParentEnabled) const
{

	LayerId = SCompoundWidget::OnPaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);

return LayerId;
}







FReply SDialogWindowWidget::SaveAll()
{
	iCurrentEditableSpeker = -1;
	iCurrentEditableSound = -1;
	vMainSpikersEditablePanel_FindImage = EVisibility::Collapsed;
	vMainSpikersEditablePanel_FindSound = EVisibility::Collapsed;
	MainSpikersEditablePanelBlock->ClearChildren();   //  CLear Speker-EditablePanel


	SaveDialogToXML();
	SaveSpekersToXML();
	SaveVariablesToXML();

	return FReply::Handled();
}

FReply SDialogWindowWidget::LoadAll()
{
	iCurrentEditableSpeker = -1;
	iCurrentEditableSound = -1;
	vMainSpikersEditablePanel_FindImage = EVisibility::Collapsed;
	vMainSpikersEditablePanel_FindSound = EVisibility::Collapsed;
	MainSpikersEditablePanelBlock->ClearChildren();   //  CLear Speker-EditablePanel


	ChoiseLoadingXmlFile();

	LoadDialogFromXML();
	LoadSpekersfromXML();
	LoadVariablesFromXML();


	return FReply::Handled();
}

  
/*
FReply SDialogWindowWidget::OnButtonContentDialog(FName str)
{
	if (str == FName("dlg_content"))
	{
		ContentPanelState = EVisibility::Visible;
		VariablesPanelState = EVisibility::Collapsed;
	}
	else if (str == FName("var"))
	{
		ContentPanelState = EVisibility::Collapsed;
		VariablesPanelState = EVisibility::Visible;
	}

	return FReply::Handled();
}
 */


void SDialogWindowWidget::UpdateDialogBlock()
{

	MainContentPanelBlock->ClearChildren();

	FPropertyIndex CurrentPropertyIndex;


	for (int32 i_Dlg = 0; i_Dlg < DialogSection.Num(); i_Dlg++)
	{
		CurrentPropertyIndex.iSpeech = -1;
		CurrentPropertyIndex.iReplic = -1;
		CurrentPropertyIndex.iResponse = -1;
		CurrentPropertyIndex.iRep = -1;
		CurrentPropertyIndex.iDialog = i_Dlg;

		MainContentPanelBlock->AddSlot()
		.Padding(GetPadding(7, 0, 0, 0))
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		//--.AutoHeight()
		[
			SNew(SVerticalBox)

			//  --------------   All  DIALIG-Title  --------------
			+ SVerticalBox::Slot()             
			.Padding(0.f)
			.AutoHeight()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SHorizontalBox)

			  
				+ SHorizontalBox::Slot()  			
				.Padding(GetPadding(0, 0, 3, 0))
				.HAlign(HAlign_Left)
				.VAlign(VAlign_Top)
				.AutoWidth()
				[ 
					SNew(SVerticalBox)

					//   ====================      DIALOG       Remove Section   ============================
					+ SVerticalBox::Slot()
					.HAlign(HAlign_Left)
					.VAlign(VAlign_Top)
					//.AutoHeight()
					.FillHeight(1)
					[
						SNew(SBox)
						.Padding(0)
						.HAlign(HAlign_Fill)
						.VAlign(VAlign_Fill)
						.WidthOverride(this, &SDialogWindowWidget::GetButtonSize, DialogButtonSmallSize)
						.HeightOverride(this, &SDialogWindowWidget::GetButtonSize, DialogButtonSmallSize) 
						//.HeightOverride(20.f)
						[
							SNew(SButton)         
							.ContentPadding(0)
							.ButtonColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 0.f))
							.OnClicked(this, &SDialogWindowWidget::OnButtonRemoveClick, EProppertyToChange::RemoveDialog, CurrentPropertyIndex)
							[
								SNew(SImage)
								.Image(ImageDeleteElement)  ////  ReMove 
							]	
						]
					]

					//   ======================       DIALOG  ( Move )        ============================
					+ SVerticalBox::Slot()
					.Padding(0.f, 0.f, 0.f, 0.f)
					.AutoHeight()
					//.FillHeight(1)
					//.MaxWidth(30.f)
					.HAlign(HAlign_Left)
					.VAlign(VAlign_Bottom)
					[
						SNew(SBox)
						.Padding(0)
						.HAlign(HAlign_Fill)
						.VAlign(VAlign_Fill)
						.WidthOverride(this, &SDialogWindowWidget::GetButtonSize, DialogButtonSmallSize)
						.HeightOverride(this, &SDialogWindowWidget::GetButtonSize, DialogButtonSmallSize)
						[
							SNew(SButton)
							.ContentPadding(0)
							.ButtonColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 0.f))
							.OnClicked(this, &SDialogWindowWidget::OnHelperPanelClick, EProppertyToChange::MoveDialog, CurrentPropertyIndex)
							[
								SNew(SImage)
								.Image(ImageMoveElement)
							]						
						]
					]

					//   ======================       DIALOG  ( Add )        ============================
					+ SVerticalBox::Slot()
					.Padding(0.f, 0.f, 0.f, 0.f)
					.AutoHeight()
					.HAlign(HAlign_Left)
					.VAlign(VAlign_Bottom)
					[
						SNew(SBox)
						.WidthOverride(this, &SDialogWindowWidget::GetButtonSize, DialogButtonSmallSize)
						.HeightOverride(this, &SDialogWindowWidget::GetButtonSize, DialogButtonSmallSize)
						[

							SNew(SButton)         
							.ContentPadding(0)
							.ButtonColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 0.f))
							.OnClicked(this, &SDialogWindowWidget::OnButtonClick, EProppertyToChange::AddDialog, CurrentPropertyIndex)
							[
								SNew(SImage)
								.Image(ImageAddElement)
							]
						]
					]

				]


			//   =========================    ALL DIALOG-title    ===========================


			//  ---------- Title-Dialog    START  ----------------
				+SHorizontalBox::Slot()
				.Padding(0.f, 0.f, 0.f, 0.f)        // L, Up, R, Dn            2, 4
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.AutoWidth()
				[
					SNew(SBox)
					.Padding(0)
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.WidthOverride(5.f * SizeKoef)
					[
						SNew(SBorder)
						.Padding(0)
						.HAlign(HAlign_Fill)
						.VAlign(VAlign_Fill)
						.BorderImage(TitleDialogStart)                  //   Title-Dialog    START
					]
				]

				//------------  DIALOG-title----------
				+ SHorizontalBox::Slot()
				.Padding(0.f, 0.f, 0.f, 0.f)        // L, Up, R, Dn            0, 4
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				//+++++++++.VAlign(VAlign_Center)
				.FillWidth(1)
				[ 
					SNew(SBorder)
					.Padding(FMargin(0.f, 0.f, 0.f, 0.f))
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.BorderImage(TitleDialog)
					.OnMouseButtonDown(this, &SDialogWindowWidget::OnButtonMarkerUsual, EProppertyToChange::MarkerDialog, CurrentPropertyIndex)
					[
						SNew(SHorizontalBox)

						//////===========================    DIALOG     (Collapse Element)  =================================

						+ SHorizontalBox::Slot()
						//.Padding(1.f, 0.f, 0.f, 0.f)        // L, Up, R, Dn
						.Padding(GetPadding(1.f, 0, 0, 0))
						.HAlign(HAlign_Left)
						.VAlign(VAlign_Center)
						.AutoWidth()
						[
 
						//   ====================      DIALOG       Colapsed  Section   ============================
							SNew(SBox)
							.Padding(0)
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Fill)
							.WidthOverride(this, &SDialogWindowWidget::GetButtonSize, DialogButtonBigSize)
							.HeightOverride(this, &SDialogWindowWidget::GetButtonSize, DialogButtonBigSize)// ++++++++ Section HEIGHT++++++++++++
							[   
								//   -------------------- DIALOG-Section title----COLLAPSED-----Content Button
								SNew(SButton)
								.ContentPadding(0)
								.ButtonColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 0.f)) 
								.OnClicked(this, &SDialogWindowWidget::OnButtonClick, EProppertyToChange::CollapsedDialogSection, CurrentPropertyIndex)
								[
									SNew(SImage)
									.Image(this, &SDialogWindowWidget::GetImageButtonSectionCollapsed, EProppertyToChange::CollapsedDialogSection, CurrentPropertyIndex) 
								]
							]
						]

						//]


						//     =======================    DIALOG   PROPERTY    "Name"    =======================
						+ SHorizontalBox::Slot()
						//.Padding(FMargin(10, 1, 4, 1))
						.Padding(GetPadding(10, 1, 4, 1))
						.HAlign(HAlign_Left)
						.VAlign(VAlign_Center)
						//++++++.FillWidth(1) 
						.AutoWidth()
						[ 
							 
							SNew(SBox)
							//.Padding(FMargin(0, 3, 4, 3))
							.Padding(GetPadding(0, 3, 4, 3))
							.HAlign(HAlign_Left)
							.VAlign(VAlign_Center)
							.HeightOverride(DialogSectionSize* SizeKoef)			//---------- - Heigh TITLE - Zone------------
							[
								 
								SNew(SHorizontalBox)


								//   -------   ImagePropertyZone     Start  -------------
								+SHorizontalBox::Slot()
								//.Padding(FMargin(0, 2, 0, 2))
								.Padding(GetPadding(0, 2, 0, 2))
								.HAlign(HAlign_Left)
								.VAlign(VAlign_Fill)
								.AutoWidth()
								[
									SNew(SBox)
									
									.Padding(0)
									.HAlign(HAlign_Fill)
									.VAlign(VAlign_Fill)
									.WidthOverride(4.f * SizeKoef)
									[
										SNew(SBorder)
										.Padding(0)
										.HAlign(HAlign_Fill)
										.VAlign(VAlign_Fill)
										.BorderImage(PropertyDialogStart)       //   -------   ImagePropertyZone     Start  -------------
									]
								]

								//     -------   DIALOG  Proprty  Name     ------------- 
								+ SHorizontalBox::Slot()
								.Padding(GetPadding(0, 2, 0, 2))
								.HAlign(HAlign_Left)
								.VAlign(VAlign_Center)
								.AutoWidth()
								[
									SNew(SBorder)
									.Padding(0)
									.HAlign(HAlign_Fill)
									.VAlign(VAlign_Fill)
									.BorderImage(PropertyDialog)
									[
										SNew(SHorizontalBox)

										+ SHorizontalBox::Slot()
										.Padding(GetPadding(5, 1, 2, 1))
										.HAlign(HAlign_Left)
										.VAlign(VAlign_Center)
										.AutoWidth()
										[
											SNew(STextBlock)
											.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 14 * SizeKoef))
											.ColorAndOpacity(this, &SDialogWindowWidget::GetSectionTextColor, EProppertyToChange::DialogName, CurrentPropertyIndex)
											.Text(FText::FromString("DIALOG: "))
										]

										+ SHorizontalBox::Slot()
										.Padding(GetPadding(2, 2, 2, 2))
										.HAlign(HAlign_Left)
										.VAlign(VAlign_Center)
										[

											SNew(SButton)
											.ContentPadding(0)
											.HAlign(HAlign_Left)
											.VAlign(VAlign_Center)
											.ButtonColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 0.f))    
											.OnClicked(this, &SDialogWindowWidget::OnButtonClick, EProppertyToChange::DialogName, CurrentPropertyIndex)
											[ 
												SNew(SOverlay)  

												+ SOverlay::Slot()           
												.HAlign(HAlign_Fill)
												.VAlign(VAlign_Center)
												//--.AutoWidth()
												[
													SNew(SBox)
													.Padding(GetPadding(0, 4, 0, 6))
													.HAlign(HAlign_Fill)
													.VAlign(VAlign_Fill)
													[
														SNew(SImage)
														.Image(ImageValueZone)      //       ImageValueZone
													]
												]

												+ SOverlay::Slot()
												.HAlign(HAlign_Center)
												.VAlign(VAlign_Center)
												[
													//  ===========================  DIALOG-Name StaticText  ================================
													SNew(SHorizontalBox)
														
													+ SHorizontalBox::Slot()
													.Padding(GetPadding(4, 0, 4, 0))
													//+++++.HAlign(HAlign_Fill)
													.HAlign(HAlign_Center)
													.VAlign(VAlign_Center)
													//.FillWidth(1)
													.AutoWidth()
													[
															     
														SNew(STextBlock)
														.Visibility(this, &SDialogWindowWidget::GetVisibilityOfSectionPropperty_Static, EProppertyToChange::DialogName, CurrentPropertyIndex)
														.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 18 * SizeKoef))
														.ColorAndOpacity(this, &SDialogWindowWidget::GetSectionTextColor, EProppertyToChange::DialogName, CurrentPropertyIndex)
														.Text(this, &SDialogWindowWidget::GetProppertyText, EProppertyToChange::DialogName, CurrentPropertyIndex)
													]
													    
													+ SHorizontalBox::Slot()
													.HAlign(HAlign_Center)
													.VAlign(VAlign_Center)
													[
														SNew(SBox)
														.MinDesiredWidth(70.f * SizeKoef)
														.HAlign(HAlign_Fill)
														.VAlign(VAlign_Fill)
														[
															//  ===========================  DIALOG-Name EditableText  ================================
															SAssignNew(DialogSection[i_Dlg].DialogSectionName_Editable, SEditableTextBox)
															.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 18 * SizeKoef))
															.Visibility(this, &SDialogWindowWidget::GetVisibilityOfSectionPropperty_Editable, EProppertyToChange::DialogName, CurrentPropertyIndex)
															.Text(FText::FromString(DialogSection[i_Dlg].Name.ToString()))
															.OnTextCommitted(this, &SDialogWindowWidget::ConfirmEditableTextBox, EProppertyToChange::DialogName, CurrentPropertyIndex)  // PRES_ENTER:   void ConfirmEditableTextBox(const FText& Text, ETextCommit::Type TextType);
															.OnTextChanged_Raw(this, &SDialogWindowWidget::OnEditableTextChange)  // void OnButtonT(const FText& Text);
														]
													]
														 
												]
											]
										]
									]
								]
								//   -------   ImagePropertyZone     End  -------------
								+ SHorizontalBox::Slot()
								.Padding(GetPadding(0, 2, 5, 2))
								.HAlign(HAlign_Left)
								.VAlign(VAlign_Fill)
								.AutoWidth()
								[
									SNew(SBox)

									.Padding(0)
									.HAlign(HAlign_Fill)
									.VAlign(VAlign_Fill)
									.WidthOverride(4.f * SizeKoef)
									[
										SNew(SBorder)
										.Padding(0)
										//.HAlign(HAlign_Left)
										.HAlign(HAlign_Fill)
										.VAlign(VAlign_Fill)
										.BorderImage(PropertyDialogEnd)       //   -------   ImagePropertyZone     End  -------------
									]
								]
							]
						]

						//  ============================   DIALOG    Link-Marker      ============================

						+ SHorizontalBox::Slot()
						//.Padding(1.f, 0.f, 0.f, 0.f)        // L, Up, R, Dn
						.Padding(GetPadding(0.f, 5.f, 0.f, 0.f))
						.HAlign(HAlign_Right)
						.VAlign(VAlign_Top)
						.FillWidth(1)
						[
							SNew(SButton)
							.ContentPadding(0)
							.HAlign(HAlign_Right)
							.VAlign(VAlign_Fill)
							.ButtonColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 0.f))
							.OnClicked(this, &SDialogWindowWidget::OnButtonMarkerLink, EProppertyToChange::MarkerDialog, CurrentPropertyIndex)
							[
								SNew(SBox)
								.Padding(0)
								.HAlign(HAlign_Right)
								.VAlign(VAlign_Fill)
								.HeightOverride((DialogSectionSize * 0.45f) * SizeKoef)
								.WidthOverride((DialogSectionSize * 0.4f) * SizeKoef)
								[
									SNew(SImage)
									.Image(MarkerLink)
								]
							]
						] //   DIALOG    Link-Marker
					]
				]	
				
				//  ---------- Title-Dialog    End  ----------------
				+ SHorizontalBox::Slot()
				.Padding(0.f, 0.f, 0.f, 0.f)        // L, Up, R, Dn               0, 4
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				//+++++++++.VAlign(VAlign_Center)
				.AutoWidth()
				[
					SNew(SBox)
					//MaxDesiredWidth(FOptionalSize())
				.Padding(0)
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.WidthOverride(5.f * SizeKoef)
				//.HeightOverride(20.f)
					[
					SNew(SBorder)
					.Padding(0)
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.BorderImage(TitleDialogEnd)                  //   Title-Dialog    End
					]
				]
			]
			//  ===============================   SpeechBlock  (Dynamick Add)   =============================
			+ SVerticalBox::Slot()           //
				.Padding(0.f)
				//.AutoWidth()
				//.FillWidth(1)
				.AutoHeight()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
			[
				SAssignNew(DialogSection[i_Dlg].SpeechBlock, SVerticalBox)
				//.Visibility(this, &SDialogWindowWidget::GetIsSectionCollapsed, EButtonDialogType::CollapsedDialogSection, i_Dlg, -1, -1)
				.Visibility(this, &SDialogWindowWidget::IsSectionCollapsed, EProppertyToChange::CollapsedDialogSection, CurrentPropertyIndex)
			]
		];  



		
		//***************************************************************************************************************************************
		//***************************************************************************************************************************************
		//*************************************************         SPEECH  BLOCK         *******************************************************
		//***************************************************************************************************************************************
		//***************************************************************************************************************************************


		for (int32 i_Speech = 0; i_Speech < DialogSection[i_Dlg].SpeechSection.Num(); i_Speech++)
		{

			CurrentPropertyIndex.iReplic = -1;
			CurrentPropertyIndex.iResponse = -1;
			CurrentPropertyIndex.iRep = -1;
			CurrentPropertyIndex.iSpeech = i_Speech;


			DialogSection[i_Dlg].SpeechBlock->AddSlot()
			.Padding(GetPadding(70.f, 0.f, 10.f, 0.f))   //(70, 0, 10, 0)
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.AutoHeight()
			[
				SNew(SVerticalBox)

				//  All SPEECH-Section
				+ SVerticalBox::Slot()            
				.Padding(GetPadding(3.f, 3.f, 3.f, 3.f))
				.AutoHeight()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
					SNew(SHorizontalBox)

					//  --------------   Buttons new SPEECH-Section (Add_Down)  -----------------
					+ SHorizontalBox::Slot()
					.Padding(GetPadding(2.f, 2.f, 2.f, 0.f))        // L, Up, R, Dn
					.HAlign(HAlign_Left)
					.VAlign(VAlign_Center)
					.AutoWidth()
					[

						SNew(SVerticalBox)

						//   ====================      SPEECH       Remove Section   ============================
						+ SVerticalBox::Slot()
						.HAlign(HAlign_Left)
						.VAlign(VAlign_Top)
						//.AutoHeight()
						.FillHeight(1)
						[
							SNew(SBox)
							.Padding(0)
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Fill)
							.WidthOverride(this, &SDialogWindowWidget::GetButtonSize, SpeechButtonSmallSize)
							.HeightOverride(this, &SDialogWindowWidget::GetButtonSize, SpeechButtonSmallSize)
							//.HeightOverride(20.f)
							[
								SNew(SButton)         
								.ContentPadding(0)
								.ButtonColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 0.f))
								.OnClicked(this, &SDialogWindowWidget::OnButtonRemoveClick, EProppertyToChange::RemoveSpeech, CurrentPropertyIndex)
								[
									SNew(SImage)
									.Image(ImageDeleteElement)  ////  ReMove element
								]	
							]
						]

						//   ======================       SPEECH  ( Move )        ============================
						+ SVerticalBox::Slot()
						.Padding(0.f, 0.f, 0.f, 0.f)
						.AutoHeight()
						//.FillHeight(1)
						//.MaxWidth(30.f)
						.HAlign(HAlign_Left)
						.VAlign(VAlign_Bottom)
						[
							SNew(SBox)
							.Padding(0)
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Fill)
							.WidthOverride(this, &SDialogWindowWidget::GetButtonSize, SpeechButtonSmallSize)
							.HeightOverride(this, &SDialogWindowWidget::GetButtonSize, SpeechButtonSmallSize)
							[
								SNew(SButton)
								.ContentPadding(0)
								.ButtonColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 0.f))
								.OnClicked(this, &SDialogWindowWidget::OnHelperPanelClick, EProppertyToChange::MoveSpeech, CurrentPropertyIndex)
								[
									SNew(SImage)
									.Image(ImageMoveElement)
								]						
							]
						]
						
					]

					//  ---------- Title-SPEECH    START  ----------------
					+SHorizontalBox::Slot()
					.Padding(GetPadding(2.f, 0.f, 0.f, 0.f))        // L, Up, R, Dn
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.AutoWidth()
					[
						SNew(SBox)
						.Padding(0)
						.HAlign(HAlign_Fill)
						.VAlign(VAlign_Fill)
						.WidthOverride(5.f * SizeKoef)
						[
							SNew(SBorder)
							.Padding(0)
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Fill)
							.BorderImage(TitleDialogStart)                  //   Title-SPEECH    START
						]
					]

					//------------  SPEECH-title----------
					+ SHorizontalBox::Slot()
					.Padding(0.f, 0.f, 0.f, 0.f)        // L, Up, R, Dn
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.FillWidth(1)
					
					[
						//  ------------------------------    SPEECH   (Add) + (COLLAPSED--BUTTON)    ----------------------
						SNew(SBorder)
						.HAlign(HAlign_Fill)
						.VAlign(VAlign_Fill)
						.BorderImage(TitleDialog)
						.OnMouseButtonDown(this, &SDialogWindowWidget::OnButtonMarkerUsual, EProppertyToChange::MarkerSpeech, CurrentPropertyIndex)
						[
							SNew(SHorizontalBox)


							+ SHorizontalBox::Slot()    
							.Padding(GetPadding(0, 3.f, 0, 3.f))

							.HAlign(HAlign_Left)
							.VAlign(VAlign_Fill)
							.AutoWidth()
							[
								 
								SNew(SVerticalBox)



								// ----------------    SPEECH        AddElenemt   -------------------
								+SVerticalBox::Slot()
								.Padding(0.f, 0.f, 0.f, 0.f)

								.AutoHeight()
								//.MaxWidth(30.f)
								.HAlign(HAlign_Center)
								.VAlign(VAlign_Center)
								[
									SNew(SBox)
									.HAlign(HAlign_Center)
									.VAlign(VAlign_Center)
									.WidthOverride(this, &SDialogWindowWidget::GetButtonSize, SpeechButtonSmallSize)
									.HeightOverride(this, &SDialogWindowWidget::GetButtonSize, SpeechButtonSmallSize)
									[

										SNew(SButton)                     //  Button new-SPEECH-Section  (Add_Down)
										.ContentPadding(0)
										.ButtonColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 0.f))
										.OnClicked(this, &SDialogWindowWidget::OnButtonClick, EProppertyToChange::AddSpeech, CurrentPropertyIndex)
										[
											SNew(SImage)
											.Image(ImageAddElement)
										]
									]
								]

								//     =====================  SPEECH   "Condition   COLLAPSED   button"  ===================
								+ SVerticalBox::Slot()    
								.Padding(0.f, 0.f, 0.f, 0.f)        

								.AutoHeight()
								//.MaxWidth(30.f)
								.HAlign(HAlign_Center)
								.VAlign(VAlign_Center)
								[
									SNew(SBox)
									.HAlign(HAlign_Center)
									.VAlign(VAlign_Center)
									.WidthOverride(this, &SDialogWindowWidget::GetButtonSize, SpeechButtonSmallSize)
									.HeightOverride(this, &SDialogWindowWidget::GetButtonSize, SpeechButtonSmallSize)
									[ 
										//   =====================  SPEECH   "Condition   COLLAPSED   button"  ===================
										SNew(SButton)
										.ContentPadding(0)
										.ButtonColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 0.f))
										.OnClicked(this, &SDialogWindowWidget::OnButtonClick, EProppertyToChange::CollapsedSpeech_Condition, CurrentPropertyIndex)
										[
											SNew(SImage)
											.Image(this, &SDialogWindowWidget::GetImageConditionButton, EProppertyToChange::CollapsedSpeech_Condition, CurrentPropertyIndex)
										]
									]
								]

								
							]

							+ SHorizontalBox::Slot()
							.Padding(GetPadding(1.f, 0.f, 0, 0.f))
							.HAlign(HAlign_Left)
							.VAlign(VAlign_Center)
							.AutoWidth()
							[

								//    --------------------------   SPEECH-Section 	 COLLAPSED   Button   ---------------------
								SNew(SBox)

								.HAlign(HAlign_Fill)
								.VAlign(VAlign_Fill)
								.WidthOverride(this, &SDialogWindowWidget::GetButtonSize, SpeechButtonBigSize)
								.HeightOverride(this, &SDialogWindowWidget::GetButtonSize, SpeechButtonBigSize)
								[
									//	  ------------------       SPEECH-Section title----COLLAPSED-----Content Button
									SNew(SButton)
									.ContentPadding(0)
									.ButtonColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 0.f))
									.OnClicked(this, &SDialogWindowWidget::OnButtonClick, EProppertyToChange::CollapsedSpeechSection, CurrentPropertyIndex)
									[
										SNew(SImage)
										.Image(this, &SDialogWindowWidget::GetImageButtonSectionCollapsed, EProppertyToChange::CollapsedSpeechSection, CurrentPropertyIndex)
									]
								]
							]






							//     =======================    SPEECH   PROPERTY    "Name"    =======================
							+ SHorizontalBox::Slot()
							.Padding(GetPadding(4, 1, 4, 1))
							.AutoWidth()
							.HAlign(HAlign_Left)
							.VAlign(VAlign_Center)
							[
								//     ------------------    Property Editable-Name Zone  --------------------
								SNew(SBox)
								.Padding(GetPadding(4, 3, 4, 3))
								//MaxDesiredWidth(FOptionalSize())
								.HAlign(HAlign_Left)
								.VAlign(VAlign_Center)
								//.WidthOverride(20.f)
								.HeightOverride(SpeechSectionSize * SizeKoef)//    -----------   Heigh TITLE-Zone  ------------
								[
									SNew(SHorizontalBox)

									//   -------   SPEECH   ImagePropertyZone     Start  -------------
									+SHorizontalBox::Slot()
									.Padding(GetPadding(2, 1, 0, 2))
									.HAlign(HAlign_Left)
									.VAlign(VAlign_Fill)
									.AutoWidth()
									[
										SNew(SBox)
									
										.Padding(0)
										.HAlign(HAlign_Fill)
										.VAlign(VAlign_Fill)
										.WidthOverride(4.f * SizeKoef)
										[
											SNew(SBorder)
											.Padding(0)
											//.HAlign(HAlign_Left)
											.HAlign(HAlign_Fill)
											.VAlign(VAlign_Fill)
											.BorderImage(PropertyDialogStart)       //   -------   SPEECH    ImagePropertyZone     Start  -------------
										]
									]

									//     -------   SPEECH  Proprty  Name     ------------- 
									+SHorizontalBox::Slot()
									.Padding(GetPadding(0, 1, 0, 2))
									.HAlign(HAlign_Left)
									.VAlign(VAlign_Center)
									.AutoWidth()
									[
										SNew(SBorder)
										.Padding(0)
										//.HAlign(HAlign_Left)
										.HAlign(HAlign_Fill)
										.VAlign(VAlign_Fill)
										.BorderImage(PropertyDialog)
										[

											SNew(SHorizontalBox)

											+ SHorizontalBox::Slot()
											.Padding(GetPadding(4, 1, 2, 1))
											.HAlign(HAlign_Left)
											.VAlign(VAlign_Center)
											.AutoWidth()
											[
												SNew(STextBlock)
												.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 12 * SizeKoef))
												//.ColorAndOpacity(FLinearColor(0.7f, 0.77f, 1.f, 1))
												.ColorAndOpacity(this, &SDialogWindowWidget::GetSectionTextColor, EProppertyToChange::SpeechName, CurrentPropertyIndex)
												.Text(FText::FromString("SPEECH:"))
											]

											+ SHorizontalBox::Slot()
											.Padding(GetPadding(2, 2, 2, 0))
											.HAlign(HAlign_Left)
											.VAlign(VAlign_Center)
											.AutoWidth()
											[
												SNew(SButton)
												.ContentPadding(0)
												.HAlign(HAlign_Left)
												.VAlign(VAlign_Center)
												.ButtonColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 0.f))    
												.OnClicked(this, &SDialogWindowWidget::OnButtonClick, EProppertyToChange::SpeechName, CurrentPropertyIndex)
												[ 
													SNew(SOverlay)  

													+ SOverlay::Slot()           
													.HAlign(HAlign_Fill)
													.VAlign(VAlign_Center)
													[
														SNew(SBox)
														.Padding(GetPadding(0, 4, 0, 6))
														.HAlign(HAlign_Fill)
														.VAlign(VAlign_Fill)
														[
															SNew(SImage)
															.Image(ImageValueZone)      //       ImageValueZone
														]
													]

													+ SOverlay::Slot()
													.HAlign(HAlign_Center)
													.VAlign(VAlign_Center)
													[
														//  ===========================  SPEECH-Name StaticText  ================================
														SNew(SHorizontalBox)
														
														+ SHorizontalBox::Slot()
														.Padding(GetPadding(5, 0, 4, 0))
														//+++++.HAlign(HAlign_Fill)
														.HAlign(HAlign_Center)
														.VAlign(VAlign_Center)
														//.FillWidth(1)
														.AutoWidth()
														[
															//  ===========================  SPEECH-Name StaticText  ================================
															//SAssignNew(DialogSection[i_Dlg].SpeechSection[i_Speech].SpeechSectionName_Statick, STextBlock)   
															SNew(STextBlock)   
															.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 14 * SizeKoef))
															

															.Visibility(this, &SDialogWindowWidget::GetVisibilityOfSectionPropperty_Static, EProppertyToChange::SpeechName, CurrentPropertyIndex)
															//.ColorAndOpacity(FLinearColor(0.7f, 0.77f, 1.f, 1))	
															.ColorAndOpacity(this, &SDialogWindowWidget::GetSectionTextColor, EProppertyToChange::SpeechName, CurrentPropertyIndex)
															.Text(this, &SDialogWindowWidget::GetProppertyText, EProppertyToChange::SpeechName, CurrentPropertyIndex)
														]

														+ SHorizontalBox::Slot()
														.HAlign(HAlign_Center)
														.VAlign(VAlign_Center)
														[
															SNew(SBox)
															.MinDesiredWidth(70.f * SizeKoef)
															.HAlign(HAlign_Fill)
															.VAlign(VAlign_Fill)
															[
																//  ===========================  SPEECH-Name EditableText  ================================
																SAssignNew(DialogSection[i_Dlg].SpeechSection[i_Speech].SpeechSectionName_Editable, SEditableTextBox)
																.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 14 * SizeKoef))
																.Visibility(this, &SDialogWindowWidget::GetVisibilityOfSectionPropperty_Editable, EProppertyToChange::SpeechName, CurrentPropertyIndex)
																.Text(FText::FromString(DialogSection[i_Dlg].SpeechSection[i_Speech].Name.ToString()))
																.OnTextCommitted(this, &SDialogWindowWidget::ConfirmEditableTextBox, EProppertyToChange::SpeechName, CurrentPropertyIndex)  // PRES_ENTER:   void ConfirmEditableTextBox(const FText& Text, ETextCommit::Type TextType);
																.OnTextChanged_Raw(this, &SDialogWindowWidget::OnEditableTextChange)  // void OnButtonT(const FText& Text);
															]
														]
													]
												]
											]
										]		
									]

									//   -------  SPEECH  ImagePropertyZone     End  -------------
									+ SHorizontalBox::Slot()
									.Padding(GetPadding(0, 1, 5, 2))
									.HAlign(HAlign_Left)
									.VAlign(VAlign_Fill)
									.AutoWidth()
									[
										SNew(SBox)

										.Padding(0)
										.HAlign(HAlign_Fill)
										.VAlign(VAlign_Fill)
										.WidthOverride(4.f * SizeKoef)
										[
											SNew(SBorder)
											.Padding(0)
											//.HAlign(HAlign_Left)
											.HAlign(HAlign_Fill)
											.VAlign(VAlign_Fill)
											.BorderImage(PropertyDialogEnd)       //   -------  SPEECH  ImagePropertyZone     End  -------------
										]
									]

								]
							]

							//  ==========================      SPEECH  Link-Marker      ===========================

							+ SHorizontalBox::Slot()
							//.Padding(1.f, 0.f, 0.f, 0.f)        // L, Up, R, Dn
							.Padding(GetPadding(0.f, 5.f, 0.f, 0.f))
							.HAlign(HAlign_Right)
							.VAlign(VAlign_Top)
							.FillWidth(1)
							[
								SNew(SButton)
								.ContentPadding(0)
								.HAlign(HAlign_Right)
								.VAlign(VAlign_Fill)
								.ButtonColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 0.f))
								.OnClicked(this, &SDialogWindowWidget::OnButtonMarkerLink, EProppertyToChange::MarkerSpeech, CurrentPropertyIndex)
								[
									SNew(SBox)
									.Padding(0)
									.HAlign(HAlign_Right)
									.VAlign(VAlign_Fill)
									.HeightOverride((SpeechSectionSize * 0.45f) * SizeKoef)
									.WidthOverride((SpeechSectionSize * 0.4f) * SizeKoef)
									[
										SNew(SImage)
										.Image(MarkerLink)
									]
								]
							] // SPEECH  Link-Marker

						]
					]
					//  ---------- Title-SPEECH    End  ----------------
					+SHorizontalBox::Slot()
					.Padding(GetPadding(0.f, 0.f, 2.f, 0.f))        // L, Up, R, Dn
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.AutoWidth()
					[
						SNew(SBox)
						.Padding(0)
						.HAlign(HAlign_Fill)
						.VAlign(VAlign_Fill)
						.WidthOverride(5.f * SizeKoef)
						[
							SNew(SBorder)
							.Padding(0)
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Fill)
							.BorderImage(TitleDialogEnd)                  //   Title-SPEECH    End
						]
					]
				]


				//  ================   SPEECH   CONDITION BLOCK:      (Dynamick Add)   ================
				+ SVerticalBox::Slot()
				.Padding(GetPadding(175.f, 1.f, 77.f, 1.f))
				.AutoHeight()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Top)
				[
					SAssignNew(DialogSection[i_Dlg].SpeechSection[i_Speech].SpeechConditionBlock, SVerticalBox)
					.Visibility(this, &SDialogWindowWidget::IsSectionCollapsed, EProppertyToChange::CollapsedSpeech_Condition, CurrentPropertyIndex)

				]

				// ---------- SPEECH  REPLICK and RESPONSE  CONTENT  -----------
				+ SVerticalBox::Slot()
				.Padding(0.f)
				.AutoHeight()
				//.FillHeight(1)
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Top)
				[
					SAssignNew(DialogSection[i_Dlg].SpeechSection[i_Speech].ReplicAndResponseBlock, SVerticalBox)
					.Visibility(this, &SDialogWindowWidget::IsSectionCollapsed, EProppertyToChange::CollapsedSpeechSection, CurrentPropertyIndex)						
				]
			];
				
					
			//***************************************************************************************************************************************
			//*************************************************                               *******************************************************
			//***********************************************         SPEECH--Condition         *****************************************************
			//***************************************************************************************************************************************
			
			
			for (int32 i_SpeechCondition = 0; i_SpeechCondition < DialogSection[i_Dlg].SpeechSection[i_Speech].SpeechCondition.Num(); i_SpeechCondition++)
			{
				CurrentPropertyIndex.iReplic = -1;
				CurrentPropertyIndex.iReplicCondition = -1;
				CurrentPropertyIndex.iResponse = -1;
				CurrentPropertyIndex.iResponseCondition = -1;
				CurrentPropertyIndex.iRep = -1;
				CurrentPropertyIndex.iRepCondition = -1;
				CurrentPropertyIndex.iSpeechCondition = i_SpeechCondition;


				FVariablesParameter SpeechVariablesParameter;
				SpeechVariablesParameter.ConditionBlock = &DialogSection[i_Dlg].SpeechSection[i_Speech].SpeechConditionBlock;
				SpeechVariablesParameter.TextBoxCondition_Type = &DialogSection[CurrentPropertyIndex.iDialog]
					.SpeechSection[CurrentPropertyIndex.iSpeech]
					.SpeechCondition[CurrentPropertyIndex.iSpeechCondition]
					.Condition_Type_Editable;
				SpeechVariablesParameter.TextBoxVariable_Name = &DialogSection[CurrentPropertyIndex.iDialog]
					.SpeechSection[CurrentPropertyIndex.iSpeech]
					.SpeechCondition[CurrentPropertyIndex.iSpeechCondition]
					.ConditionVariable_Name_Editable;
				SpeechVariablesParameter.TextBoxVariable_Value = &DialogSection[CurrentPropertyIndex.iDialog]
					.SpeechSection[CurrentPropertyIndex.iSpeech]
					.SpeechCondition[CurrentPropertyIndex.iSpeechCondition]
					.ConditionVariable_Value_Editable;
				SpeechVariablesParameter.Type_Text = &DialogSection[CurrentPropertyIndex.iDialog]
					.SpeechSection[CurrentPropertyIndex.iSpeech]
					.SpeechCondition[CurrentPropertyIndex.iSpeechCondition].ConditionType;
				SpeechVariablesParameter.VariableName_Text = &DialogSection[CurrentPropertyIndex.iDialog]
					.SpeechSection[CurrentPropertyIndex.iSpeech]
					.SpeechCondition[CurrentPropertyIndex.iSpeechCondition].VariableName;
				SpeechVariablesParameter.VariableValue_Text = &DialogSection[CurrentPropertyIndex.iDialog]
					.SpeechSection[CurrentPropertyIndex.iSpeech]
					.SpeechCondition[CurrentPropertyIndex.iSpeechCondition].VariableValue;
				SpeechVariablesParameter.AddButtonPropperty = EProppertyToChange::ButtonAddSpeech_Condition;
				SpeechVariablesParameter.RemoveButtonPropperty = EProppertyToChange::RemoveSpeech_Condition;
				SpeechVariablesParameter.ConditionTypePropperty = EProppertyToChange::Speech_condition_type;
				SpeechVariablesParameter.CompareType = EProppertyToChange::Speech_condition_CompareType;
				SpeechVariablesParameter.VarTypePropperty = EProppertyToChange::Speech_condition_varType;
				SpeechVariablesParameter.VarNamePropperty = EProppertyToChange::Speech_condition_varName;
				SpeechVariablesParameter.VarValuePropperty = EProppertyToChange::Speech_condition_varValue;

/*
				TSharedPtr<SVerticalBox>* RepConditionBlock = &DialogSection[i_Dlg].SpeechSection[i_Speech].SpeechConditionBlock;
				TSharedPtr<SEditableTextBox> TextBoxCondition_Type = DialogSection[CurrentPropertyIndex.iDialog]
						.SpeechSection[CurrentPropertyIndex.iSpeech]
						.SpeechCondition[CurrentPropertyIndex.iSpeechCondition]
						.Condition_Type_Editable;

				TSharedPtr<SEditableTextBox> *TextBoxVariable_Name = &DialogSection[CurrentPropertyIndex.iDialog]
					.SpeechSection[CurrentPropertyIndex.iSpeech]
					.SpeechCondition[CurrentPropertyIndex.iSpeechCondition].ConditionVariable_Name_Editable;

				TSharedPtr<SEditableTextBox> TextBoxVariable_Value = DialogSection[CurrentPropertyIndex.iDialog]
					.SpeechSection[CurrentPropertyIndex.iSpeech]
					.SpeechCondition[CurrentPropertyIndex.iSpeechCondition]
					.ConditionVariable_Value_Editable;
				FName* Type_Text = &DialogSection[CurrentPropertyIndex.iDialog].SpeechSection[CurrentPropertyIndex.iSpeech]
					.SpeechCondition[CurrentPropertyIndex.iSpeechCondition].ConditionType;
				FName* VariableName_Text = &DialogSection[CurrentPropertyIndex.iDialog].SpeechSection[CurrentPropertyIndex.iSpeech]
					.SpeechCondition[CurrentPropertyIndex.iSpeechCondition].VariableName;
				FName* VariableValue_Text = &DialogSection[CurrentPropertyIndex.iDialog].SpeechSection[CurrentPropertyIndex.iSpeech]
					.SpeechCondition[CurrentPropertyIndex.iSpeechCondition].VariableValue;

				EProppertyToChange AddButtonPropperty = EProppertyToChange::ButtonAddSpeech_Condition;    
				EProppertyToChange RemoveButtonPropperty = EProppertyToChange::RemoveSpeech_Condition;
				EProppertyToChange ConditionTypePropperty = EProppertyToChange::Speech_condition_type;
				EProppertyToChange CompareType = EProppertyToChange::Speech_condition_CompareType;
				EProppertyToChange VarTypePropperty = EProppertyToChange::Speech_condition_varType;
				EProppertyToChange VarNamePropperty = EProppertyToChange::Speech_condition_varName;
				EProppertyToChange VarValuePropperty = EProppertyToChange::Speech_condition_varValue;

*/
				DrawConditionElement(CurrentPropertyIndex, SpeechVariablesParameter);
			}
			
			//***************************************************************************************************************************************
			//****************************************************          REPLIC          *********************************************************
			//*******************************************                                           *************************************************
			//***************************************************************************************************************************************
			   
			for (int32 i_Replic = 0; i_Replic < DialogSection[i_Dlg].SpeechSection[i_Speech].ReplicSection.Num(); i_Replic++)
			{

				CurrentPropertyIndex.iResponse = -1;
				CurrentPropertyIndex.iRep = -1;
				CurrentPropertyIndex.iReplic = i_Replic;


				DialogSection[i_Dlg].SpeechSection[i_Speech].ReplicAndResponseBlock->AddSlot()
				.Padding(GetPadding(70.f, 0.f, 10.f, 0.f))
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.AutoHeight()
				[
					SNew(SVerticalBox)

					//  -------------  All REPLICK-Title  --------------
					+ SVerticalBox::Slot()            
					.Padding(0.f)
					.AutoHeight()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					[
						SNew(SHorizontalBox)

						// ---------------- Button new-REPLICK-Section, Button-MOVE-Section  ) -------------------
						+ SHorizontalBox::Slot()
						.Padding(GetPadding(0.f, 2.f, 0.f, 2.f))       // L, Up, R, Dn
						.HAlign(HAlign_Left)
						.VAlign(VAlign_Center)
						.AutoWidth()
						[

							SNew(SVerticalBox)

							//   ====================      REPLICK       (Remove Section)   ============================
							+ SVerticalBox::Slot()
							.HAlign(HAlign_Left)
							.VAlign(VAlign_Center)
							//.AutoHeight()
							.FillHeight(1)
							[
								SNew(SBox)
								.Padding(0)
								.HAlign(HAlign_Left)
								.VAlign(VAlign_Top)
								.WidthOverride(this, &SDialogWindowWidget::GetButtonSize, ReplicButtonRemoveSize)
								.HeightOverride(this, &SDialogWindowWidget::GetButtonSize, ReplicButtonRemoveSize)
								[
									SNew(SButton)
									.ContentPadding(0)
									.ButtonColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 0.f))
									.OnClicked(this, &SDialogWindowWidget::OnButtonRemoveClick, EProppertyToChange::RemoveReplic, CurrentPropertyIndex)
									[
										SNew(SImage)
										.Image(ImageDeleteElement)  
									]
								]
							]

							//   ======================       REPLIC  ( Move )        ============================
							+ SVerticalBox::Slot()
							.Padding(0.f, 0.f, 0.f, 0.f)
							.AutoHeight()
							.HAlign(HAlign_Left)
							.VAlign(VAlign_Center)
							[
								SNew(SBox)
								.HAlign(HAlign_Fill)
								.VAlign(VAlign_Fill)
								.WidthOverride(this, &SDialogWindowWidget::GetButtonSize, ReplicButtonMoveSize)
								.HeightOverride(this, &SDialogWindowWidget::GetButtonSize, ReplicButtonMoveSize)
								[
									SNew(SButton)
									.ContentPadding(0)
									.ButtonColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 0.f))
									.OnClicked(this, &SDialogWindowWidget::OnHelperPanelClick, EProppertyToChange::MoveReplic, CurrentPropertyIndex)
									[
										SNew(SImage)
										.Image(ImageMoveElement)
									]						
								]
							]

						]

					
						//  ---------- Title-REPLICK    START  ----------------
						+SHorizontalBox::Slot()
						.Padding(0.f, 0.f, 0.f, 0.f)        // L, Up, R, Dn
						.HAlign(HAlign_Fill)
						.VAlign(VAlign_Fill)

						.AutoWidth()
						[
							SNew(SBox)

							.Padding(0)
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Fill)
							.WidthOverride(5.f * SizeKoef)  
							[
								SNew(SBorder)
								.Padding(0)
								.HAlign(HAlign_Fill)
								.VAlign(VAlign_Fill)
								.BorderImage(TitleReplicStart)                  //   Title-REPLICK    START 
							]
						]


						+ SHorizontalBox::Slot()
						.Padding(0.f, 0.f, 0.f, 0.f)        // L, Up, R, Dn
						.HAlign(HAlign_Fill)
						.VAlign(VAlign_Fill)
						.FillWidth(1)
						[
							//------------ALL REPLICK-Title----------
							SNew(SBorder)
							.HAlign(HAlign_Fill)/////
							.VAlign(VAlign_Fill)//////
							.BorderImage(TitleReplic)
							.OnMouseButtonDown(this, &SDialogWindowWidget::OnButtonMarkerUsual, EProppertyToChange::MarkerReplic, CurrentPropertyIndex)
							[

								SNew(SHorizontalBox)

								+ SHorizontalBox::Slot()
								.Padding(0, 0.f, 0, 0.f)
								//.FillWidth(1)
								.AutoWidth()
								.HAlign(HAlign_Left)
								.VAlign(VAlign_Fill)
								[

									SNew(SVerticalBox)
									
									// -----------------   REPLICK      (Add_Down)    -----------------------
									+ SVerticalBox::Slot()
									.Padding(GetPadding(0.f, 2.f, 0.f, 0.f))
									.AutoHeight()
									.HAlign(HAlign_Left)
									.VAlign(VAlign_Center)
									[
										SNew(SBox)
										.WidthOverride(this, &SDialogWindowWidget::GetButtonSize, ReplicButtonAddSize)
										.HeightOverride(this, &SDialogWindowWidget::GetButtonSize, ReplicButtonAddSize)
										.HAlign(HAlign_Fill)
										.VAlign(VAlign_Fill)
										[

											SNew(SButton)    // -------------   REPLICK      (Add_Down)    ---------------
											.ContentPadding(0)
											.ButtonColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 0.f))
											.HAlign(HAlign_Left)
											.VAlign(VAlign_Bottom)
											.OnClicked(this, &SDialogWindowWidget::OnButtonClick, EProppertyToChange::AddReplick, CurrentPropertyIndex)
											[
												SNew(SImage)
												.Image(ImageAddElement)
											]										
										]
									]

									//   =====================  REPLICK   "Condition COLLAPSED button"  ===================
									+ SVerticalBox::Slot()
									.Padding(0.f, 0.f, 0.f, 0.f)
									.FillHeight(1)
									.HAlign(HAlign_Left)
									.VAlign(VAlign_Center)
									[
										SNew(SBox)
										.HAlign(HAlign_Left)
										.VAlign(VAlign_Top)
										.WidthOverride(this, &SDialogWindowWidget::GetButtonSize, ReplicButtonSmallSize)
										.HeightOverride(this, &SDialogWindowWidget::GetButtonSize, ReplicButtonSmallSize)
										[
											//   =====================  REPLICK   "Condition COLLAPSED button"  ===================
											SNew(SButton)
											.ContentPadding(0)
											.ButtonColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 0.f))
											.OnClicked(this, &SDialogWindowWidget::OnButtonClick, EProppertyToChange::CollapsedReplic_Condition, CurrentPropertyIndex)
											[
												SNew(SImage)
												.Image(this, &SDialogWindowWidget::GetImageConditionButton, EProppertyToChange::CollapsedReplic_Condition, CurrentPropertyIndex)
											]
										]
									]					
								]

								//  ===============   REPLICK     "COLLAPSED   Content Button"    =======================
								+ SHorizontalBox::Slot()
								.Padding(GetPadding(2, 0.f, 0, 0.f))
								//.FillWidth(1)
								.AutoWidth()
								.HAlign(HAlign_Left)
								.VAlign(VAlign_Center)
								[
									//  ===============   REPLICK      "COLLAPSED  Content Button"    =======================
									SNew(SBox)
									.HAlign(HAlign_Fill)
									.VAlign(VAlign_Fill)
									.WidthOverride(this, &SDialogWindowWidget::GetButtonSize, ReplicButtonBigSize)
									.HeightOverride(this, &SDialogWindowWidget::GetButtonSize, ReplicButtonBigSize)
									[
										//   -----------------------     REPLICK-Section title----COLLAPSED-----Content Button
										SNew(SButton)
										.ContentPadding(0)
										.ButtonColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 0.f))
										.OnClicked(this, &SDialogWindowWidget::OnButtonClick, EProppertyToChange::CollapsedReplicSection, CurrentPropertyIndex)
										[
											SNew(SImage)
											.Image(this, &SDialogWindowWidget::GetImageButtonSectionCollapsed, EProppertyToChange::CollapsedReplicSection, CurrentPropertyIndex)
										]
									]
								]

								
						   


								+ SHorizontalBox::Slot()
								.Padding(GetPadding(5, 1, 4, 1))
								.AutoWidth()
								.HAlign(HAlign_Left)
								.VAlign(VAlign_Center)
								[
									//     ------------------    Property Editable-Repeat Zone  --------------------

									SNew(SBox)
									.Padding(GetPadding(0, 3, 4, 3))
									.HAlign(HAlign_Left)
									.VAlign(VAlign_Center)
									.HeightOverride(ReplicSectionSize * SizeKoef)         // -----------   Heigh TITLE-Zone  ------------
									[
										
										SNew(SHorizontalBox)

										//   -------   REPLIC   ImagePropertyZone     Start  -------------
										+SHorizontalBox::Slot()
										.Padding(GetPadding(2, 0, 0, 1))
										.HAlign(HAlign_Left)
										.VAlign(VAlign_Fill)
										.AutoWidth()
										[
											SNew(SBox)
									
											.Padding(0)
											.HAlign(HAlign_Fill)
											.VAlign(VAlign_Fill)
											.WidthOverride(4.f * SizeKoef)  
											[
												SNew(SBorder)
												.Padding(0)
												.HAlign(HAlign_Fill)
												.VAlign(VAlign_Fill)
												.BorderImage(PropertyReplicStart)       //   -------   REPLICK    ImagePropertyZone     Start  -------------
											]
										]

										+SHorizontalBox::Slot()
										.Padding(GetPadding(0, 0, 0, 1))
										.HAlign(HAlign_Left)
										.VAlign(VAlign_Fill)
										.AutoWidth()
										[
											SNew(SBorder)
											.Padding(0)
											.HAlign(HAlign_Fill)
											.VAlign(VAlign_Center)
											.BorderImage(PropertyReplic)
											[
													SNew(STextBlock)
													.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 14 * SizeKoef))
													.ColorAndOpacity(this, &SDialogWindowWidget::GetSectionTextColor, EProppertyToChange::repeatReplic, CurrentPropertyIndex)
													.Text(FText::FromString("REPLIC:"))
											]
										]
										//   -------  REPLICK  ImagePropertyZone     End  -------------
										+ SHorizontalBox::Slot()
										.Padding(GetPadding(0, 0, 0, 1))
										.HAlign(HAlign_Left)
										.VAlign(VAlign_Fill)
										.AutoWidth()
										[
											SNew(SBox)

											.Padding(0)
											.HAlign(HAlign_Fill)
											.VAlign(VAlign_Fill)
											.WidthOverride(4.f * SizeKoef)   
											[
												SNew(SBorder)
												.Padding(0)
												.HAlign(HAlign_Fill)
												.VAlign(VAlign_Fill)
												.BorderImage(PropertyReplicEnd)       //   -------  REPLICK  ImagePropertyZone     End  -------------
											]
										]



										//   -------   REPLICK   ImagePropertyZone     Start  -------------
										+SHorizontalBox::Slot()
										.Padding(GetPadding(15, 0, 0, 1))
										.HAlign(HAlign_Left)
										.VAlign(VAlign_Fill)
										.AutoWidth()
										[
											SNew(SBox)
									
											.Padding(0)
											.HAlign(HAlign_Fill)
											.VAlign(VAlign_Fill)
											.WidthOverride(4.f * SizeKoef)  
											[
												SNew(SBorder)
												.Padding(0)
												.HAlign(HAlign_Fill)
												.VAlign(VAlign_Fill)
												.BorderImage(PropertyReplicStart)       //   -------   REPLICK    ImagePropertyZone     Start  -------------
											]
										]

										//     -------   REPLICK  Proprty  Name     ------------- 
										+SHorizontalBox::Slot()
										.Padding(GetPadding(0, 0, 0, 1))
										.HAlign(HAlign_Left)
										.VAlign(VAlign_Center)
										.AutoWidth()
										[
											SNew(SBorder)
											.Padding(0)
											.HAlign(HAlign_Fill)
											.VAlign(VAlign_Fill)
											.BorderImage(PropertyReplic)
											[

												SNew(SHorizontalBox)

												+ SHorizontalBox::Slot()
												.Padding(GetPadding(4, 1, 2, 1))
												.HAlign(HAlign_Left)
												.VAlign(VAlign_Center)
												.AutoWidth()
												[
													SNew(STextBlock)
													.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 12 * SizeKoef))
													.ColorAndOpacity(this, &SDialogWindowWidget::GetSectionTextColor, EProppertyToChange::repeatReplic, CurrentPropertyIndex)
													.Text(FText::FromString("repeat:"))
												]

												+ SHorizontalBox::Slot() 
												.Padding(GetPadding(7, 4, 4, 3))
												.HAlign(HAlign_Left)
												.VAlign(VAlign_Center)
												.AutoWidth()
												[
													//  ===============  CombobBox  ==================
													SAssignNew(DialogSection[i_Dlg].SpeechSection[i_Speech].ReplicSection[i_Replic].CB_ReplicRepeat,
																																SComboBox<TSharedPtr<FString>>)
													.ContentPadding(GetPadding(4.0f, 0, 4.0f, 5.0f))
													.OptionsSource(&ReplicRepeatComboList)
													.OnGenerateWidget(this, &SDialogWindowWidget::HandleComboBoxGenerateWidget)
													.OnSelectionChanged(this, &SDialogWindowWidget::GetReplicRepeatComboList, CurrentPropertyIndex)
													[ 
														SNew(STextBlock)
														.Margin(0)
														.Text(this, &SDialogWindowWidget::GetCurrentReplicRepeatLabel, CurrentPropertyIndex)
														.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 12 * SizeKoef))
														.ColorAndOpacity(FLinearColor(0.0f, 0.0f, 0.08f, 1))
													]//  ComboBox

												]
											]		
										]
										//   -------  REPLICK  ImagePropertyZone     End  -------------
										+ SHorizontalBox::Slot()
										.Padding(GetPadding(0, 0, 5, 1))
										.HAlign(HAlign_Left)
										.VAlign(VAlign_Fill)
										.AutoWidth()
										[
											SNew(SBox)

											.Padding(0)
											.HAlign(HAlign_Fill)
											.VAlign(VAlign_Fill)
											.WidthOverride(4.f * SizeKoef)   
											[
												SNew(SBorder)
												.Padding(0)
												.HAlign(HAlign_Fill)
												.VAlign(VAlign_Fill)
												.BorderImage(PropertyReplicEnd)       //   -------  REPLICK  ImagePropertyZone     End  -------------
											]
										]
									]
								]
							]
						]
							//  ---------- Title-REPLICK    End  ----------------
						+SHorizontalBox::Slot()
						.Padding(GetPadding(0.f, 0.f, 2.f, 0.f))       // L, Up, R, Dn
						.HAlign(HAlign_Fill)
						.VAlign(VAlign_Fill)
						.AutoWidth()
						[
							SNew(SBox)
							.Padding(0)
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Fill)
							.WidthOverride(5.f * SizeKoef)  
							[
								SNew(SBorder)
								.Padding(0)
								.HAlign(HAlign_Fill)
								.VAlign(VAlign_Fill)
								.BorderImage(TitleReplicEnd)                  //   Title-REPLICK    End
							]
						]
					]

					//  ================   REPLICK   CONDITION    BLOCK:      (Dynamick Add)   ================
					+ SVerticalBox::Slot()
					.Padding(GetPadding(100.f, 1.f, 67.f, 1.f))
					.AutoHeight()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Top) 
					[
						SAssignNew(DialogSection[i_Dlg].SpeechSection[i_Speech].ReplicSection[i_Replic].ReplicConditionBlock, SVerticalBox)
						.Visibility(this, &SDialogWindowWidget::IsSectionCollapsed, EProppertyToChange::CollapsedReplic_Condition, CurrentPropertyIndex)
						  
					]
					  
					//       ======================     REPLICK  Editable Multiline zone     ========================
					+ SVerticalBox::Slot()
						.Padding(GetPadding(90.f, 3.f, 10.f, 1.f))
						.AutoHeight()
						.HAlign(HAlign_Fill)
						.VAlign(VAlign_Fill)
						[
							SNew(SBox)
							.MaxDesiredHeight(ReplicMultiplyTextSize * SizeKoef)
						[
							SNew(SMultiLineEditableTextBox)
							.BackgroundColor(FLinearColor(0.13f, 0.13f, 0.13f, 1))
							//---.ColorAndOpacity(ColorUsualText)
							.ForegroundColor(ColorUsualText)
							.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 12 * SizeKoef))
							.Text(FText::FromString(DialogSection[i_Dlg].SpeechSection[i_Speech].ReplicSection[i_Replic].ComentText))
							.OnTextCommitted(this, &SDialogWindowWidget::ConfirmEditableMultilineTextBox, EProppertyToChange::replicComent, CurrentPropertyIndex)
							.OnTextChanged_Raw(this, &SDialogWindowWidget::OnEditableTextChange)  // void OnButtonT(const FText& Text);
						]
					]


					//  ================   REPLICK  RepContent:      (Dynamick Add)   ================
					+ SVerticalBox::Slot()           
					.Padding(GetPadding(3.f, 3.f, 3.f, 3.f))
					.AutoHeight()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Top)
					[
						SAssignNew(DialogSection[i_Dlg].SpeechSection[i_Speech].ReplicSection[i_Replic].RepBlock, SVerticalBox)
						.Visibility(this, &SDialogWindowWidget::IsSectionCollapsed, EProppertyToChange::CollapsedReplicSection, CurrentPropertyIndex)						
					]
				]; 


				 

				//***************************************************************************************************************************************
				//*************************************************                               *******************************************************
				//***********************************************         REPLIC--Condition         *****************************************************
				//***************************************************************************************************************************************

					for (int32 i_ReplicCondition = 0; i_ReplicCondition < DialogSection[i_Dlg].SpeechSection[i_Speech].ReplicSection[i_Replic].ReplicCondition.Num(); i_ReplicCondition++)
					{
						CurrentPropertyIndex.iSpeechCondition = -1;
						CurrentPropertyIndex.iResponse = -1;
						CurrentPropertyIndex.iResponseCondition = -1;
						CurrentPropertyIndex.iRep = -1;
						CurrentPropertyIndex.iRepCondition = -1;
						CurrentPropertyIndex.iReplicCondition = i_ReplicCondition;


						FVariablesParameter SpeechVariablesParameter;
						SpeechVariablesParameter.ConditionBlock = &DialogSection[CurrentPropertyIndex.iDialog]
							.SpeechSection[CurrentPropertyIndex.iSpeech]
							.ReplicSection[CurrentPropertyIndex.iReplic].ReplicConditionBlock;
						SpeechVariablesParameter.TextBoxCondition_Type = &DialogSection[CurrentPropertyIndex.iDialog]
							.SpeechSection[CurrentPropertyIndex.iSpeech]
							.ReplicSection[CurrentPropertyIndex.iReplic]
							.ReplicCondition[CurrentPropertyIndex.iReplicCondition].Condition_Type_Editable;
						SpeechVariablesParameter.TextBoxVariable_Name = &DialogSection[CurrentPropertyIndex.iDialog]
							.SpeechSection[CurrentPropertyIndex.iSpeech]
							.ReplicSection[CurrentPropertyIndex.iReplic]
							.ReplicCondition[CurrentPropertyIndex.iReplicCondition].ConditionVariable_Name_Editable;
						SpeechVariablesParameter.TextBoxVariable_Value = &DialogSection[CurrentPropertyIndex.iDialog]
							.SpeechSection[CurrentPropertyIndex.iSpeech]
							.ReplicSection[CurrentPropertyIndex.iReplic]
							.ReplicCondition[CurrentPropertyIndex.iReplicCondition].ConditionVariable_Value_Editable;
						SpeechVariablesParameter.Type_Text = &DialogSection[CurrentPropertyIndex.iDialog]
							.SpeechSection[CurrentPropertyIndex.iSpeech]
							.ReplicSection[CurrentPropertyIndex.iReplic]
							.ReplicCondition[CurrentPropertyIndex.iReplicCondition].ConditionType;
						SpeechVariablesParameter.VariableName_Text = &DialogSection[CurrentPropertyIndex.iDialog]
							.SpeechSection[CurrentPropertyIndex.iSpeech]
							.ReplicSection[CurrentPropertyIndex.iReplic]
							.ReplicCondition[CurrentPropertyIndex.iReplicCondition].VariableName;
						SpeechVariablesParameter.VariableValue_Text = &DialogSection[CurrentPropertyIndex.iDialog]
							.SpeechSection[CurrentPropertyIndex.iSpeech]
							.ReplicSection[CurrentPropertyIndex.iReplic]
							.ReplicCondition[CurrentPropertyIndex.iReplicCondition].VariableValue;
						SpeechVariablesParameter.AddButtonPropperty = EProppertyToChange::ButtonAddReplic_Condition;
						SpeechVariablesParameter.RemoveButtonPropperty = EProppertyToChange::RemoveReplic_Condition;
						SpeechVariablesParameter.ConditionTypePropperty = EProppertyToChange::Replic_condition_type;
						SpeechVariablesParameter.CompareType = EProppertyToChange::Replic_condition_CompareType;
						SpeechVariablesParameter.VarTypePropperty = EProppertyToChange::Replic_condition_varType;
						SpeechVariablesParameter.VarNamePropperty = EProppertyToChange::Replic_condition_varName;
						SpeechVariablesParameter.VarValuePropperty = EProppertyToChange::Replic_condition_varValue;


						DrawConditionElement(CurrentPropertyIndex, SpeechVariablesParameter);


						//TSharedPtr<SVerticalBox>* RepConditionBlock = &DialogSection[CurrentPropertyIndex.iDialog].SpeechSection[CurrentPropertyIndex.iSpeech]
						//	.ReplicSection[CurrentPropertyIndex.iReplic].ReplicConditionBlock;  
						//TSharedPtr<SEditableTextBox>* TextBoxCondition_Type = &DialogSection[CurrentPropertyIndex.iDialog].SpeechSection[CurrentPropertyIndex.iSpeech]
						//	.ReplicSection[CurrentPropertyIndex.iReplic]
						//	.ReplicCondition[CurrentPropertyIndex.iReplicCondition].Condition_Type_Editable;
						//TSharedPtr<SEditableTextBox>* TextBoxVariable_Name = &DialogSection[CurrentPropertyIndex.iDialog].SpeechSection[CurrentPropertyIndex.iSpeech]
						//	.ReplicSection[CurrentPropertyIndex.iReplic]
						//	.ReplicCondition[CurrentPropertyIndex.iReplicCondition].ConditionVariable_Name_Editable;
						//TSharedPtr<SEditableTextBox>* TextBoxVariable_Value = &DialogSection[CurrentPropertyIndex.iDialog].SpeechSection[CurrentPropertyIndex.iSpeech]
						//	.ReplicSection[CurrentPropertyIndex.iReplic]
						//	.ReplicCondition[CurrentPropertyIndex.iReplicCondition].ConditionVariable_Value_Editable;
						//FName* Type_Text = &DialogSection[CurrentPropertyIndex.iDialog].SpeechSection[CurrentPropertyIndex.iSpeech]
						//	.ReplicSection[CurrentPropertyIndex.iReplic]
						//	.ReplicCondition[CurrentPropertyIndex.iReplicCondition].ConditionType;
						//FName* VariableName_Text = &DialogSection[CurrentPropertyIndex.iDialog].SpeechSection[CurrentPropertyIndex.iSpeech]
						//	.ReplicSection[CurrentPropertyIndex.iReplic]
						//	.ReplicCondition[CurrentPropertyIndex.iReplicCondition].VariableName;
						//FName* VariableValue_Text = &DialogSection[CurrentPropertyIndex.iDialog].SpeechSection[CurrentPropertyIndex.iSpeech]
						//	.ReplicSection[CurrentPropertyIndex.iReplic]
						//	.ReplicCondition[CurrentPropertyIndex.iReplicCondition].VariableValue;

						//EProppertyToChange AddButtonPropperty = EProppertyToChange::ButtonAddReplic_Condition;// ButtonAddRep_Condition;
						//EProppertyToChange RemoveButtonPropperty = EProppertyToChange::RemoveReplic_Condition;
						//EProppertyToChange ConditionTypePropperty = EProppertyToChange::Replic_condition_type;// rep_condition_type;
						//EProppertyToChange CompareType = EProppertyToChange::Replic_condition_CompareType;
						//EProppertyToChange VarTypePropperty = EProppertyToChange::Replic_condition_varType;// rep_condition_varType;
						//EProppertyToChange VarNamePropperty = EProppertyToChange::Replic_condition_varName;// rep_condition_varName;
						//EProppertyToChange VarValuePropperty = EProppertyToChange::Replic_condition_varValue;// rep_condition_varValue;




						//DrawConditionElement(*RepConditionBlock,
						//	CurrentPropertyIndex,
						//	AddButtonPropperty,
						//	
						//	RemoveButtonPropperty,

						//	*TextBoxCondition_Type,
						//	*Type_Text,
						//	ConditionTypePropperty,
						//	//CompareType,
						//	*TextBoxVariable_Name,
						//	*VariableName_Text,
						//	VarNamePropperty,
						//	*TextBoxVariable_Value,
						//	*VariableValue_Text,
						//	VarValuePropperty,

						//	VarTypePropperty);

					}

				//***************************************************************************************************************************************
				//****************************************************          REP          *********************************************************
				//*******************************************                                           *************************************************
				//***************************************************************************************************************************************

				for (int32 i_Rep = 0; i_Rep < DialogSection[i_Dlg].SpeechSection[i_Speech].ReplicSection[i_Replic].RepSection.Num(); i_Rep++)
				{

				
					CurrentPropertyIndex.iResponse = -1;
					CurrentPropertyIndex.iRep = i_Rep;

					 
					DialogSection[i_Dlg].SpeechSection[i_Speech].ReplicSection[i_Replic].RepBlock->AddSlot()
					.Padding(GetPadding(90.f, 0.f, 60.f, 0.f))
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.AutoHeight()
					[
						SNew(SVerticalBox)             ///////    -------------    FULL REP Zone   --------------

					
						+ SVerticalBox::Slot()            
						.Padding(GetPadding(3.f, 3.f, 3.f, 3.f))
						.AutoHeight()
						.HAlign(HAlign_Fill)
						.VAlign(VAlign_Fill)
						[
							SNew(SHorizontalBox)

							+ SHorizontalBox::Slot()
							.Padding(0.f, 0.f, 0.f, 0.f)        // L, Up, R, Dn
							.HAlign(HAlign_Right)
							.VAlign(VAlign_Center)
							.AutoWidth()
							[
								SNew(SVerticalBox)

								//   ====================      REP       (Remove Section)   ============================
								+ SVerticalBox::Slot()
								.HAlign(HAlign_Left)
								.VAlign(VAlign_Center)
								.FillHeight(1)
								[
									SNew(SBox)
									.Padding(0)
									.HAlign(HAlign_Left)
									.VAlign(VAlign_Top)
									.WidthOverride(this, &SDialogWindowWidget::GetButtonSize, RepButtonSmallSize)
									.HeightOverride(this, &SDialogWindowWidget::GetButtonSize, RepButtonSmallSize)
									
									[
										SNew(SButton)
										.ContentPadding(0)
										.ButtonColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 0.f))
										.OnClicked(this, &SDialogWindowWidget::OnButtonRemoveClick, EProppertyToChange::RemoveRep, CurrentPropertyIndex)
										[
											SNew(SImage)
											.Image(ImageDeleteElement)  
										]
									]
								]

								//   ======================       REP  ( Move )        ============================
								+ SVerticalBox::Slot()
								.Padding(0.f, 0.f, 0.f, 0.f)
								.AutoHeight()
								.HAlign(HAlign_Left)
								.VAlign(VAlign_Center)
								[
									SNew(SBox)
									.HAlign(HAlign_Fill)
									.VAlign(VAlign_Fill)
									.WidthOverride(this, &SDialogWindowWidget::GetButtonSize, RepButtonSmallSize)
									.HeightOverride(this, &SDialogWindowWidget::GetButtonSize, RepButtonSmallSize)
									[
										SNew(SButton)
										.ContentPadding(0)
										.ButtonColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 0.f))
										.OnClicked(this, &SDialogWindowWidget::OnHelperPanelClick, EProppertyToChange::MoveRep, CurrentPropertyIndex)
										[
											SNew(SImage)
											.Image(ImageMoveElement)
										]						
									]
								]
							]
						//  ---------- Title-RESPONSE    START  ----------------
							+SHorizontalBox::Slot()
							.Padding(GetPadding(2.f, 0.f, 0.f, 0.f))        // L, Up, R, Dn
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Fill)
							.AutoWidth()
							[
								SNew(SBox)
								.Padding(0)
								.HAlign(HAlign_Fill)
								.VAlign(VAlign_Fill)
								.WidthOverride(5.f * SizeKoef)   
								[
									SNew(SBorder)
									.Padding(0)
									.HAlign(HAlign_Fill)
									.VAlign(VAlign_Fill)
									.BorderImage(TitleDialogStart)                  //   Title-REPLICK    START
								]
							]


							//  ---------- Title-RESPONSE    BODY  ----------------
							+ SHorizontalBox::Slot()
							.Padding(0.f, 0.f, 0.f, 0.f)        // L, Up, R, Dn
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Fill)
							.FillWidth(1)
							[
								//  =====================  REP    (Condition Button),  (Speker-Text),  (Combob-box)   ========================
								SNew(SBorder)
								.HAlign(HAlign_Fill)/////
								.VAlign(VAlign_Fill)//////
								.BorderImage(TitleDialog)
								.OnMouseButtonDown(this, &SDialogWindowWidget::OnButtonMarkerUsual, EProppertyToChange::MarkerRep, CurrentPropertyIndex)
								[
									SNew(SHorizontalBox)


									+ SHorizontalBox::Slot()
									.Padding(0.f, 0.f, 0.f, 0.f)        // L, Up, R, Dn
									.HAlign(HAlign_Left)
									.VAlign(VAlign_Center)
									.AutoWidth()
									[
										SNew(SVerticalBox)

										// ---------------- Button      (Add_Down)  --------------------------
										+ SVerticalBox::Slot()
										.Padding(0.f, 0.f, 0.f, 0.f)
										.AutoHeight()
										.HAlign(HAlign_Left)
										.VAlign(VAlign_Center)
										[
											SNew(SBox)
											.WidthOverride(this, &SDialogWindowWidget::GetButtonSize, RepButtonSmallInsileSSize)
											.MaxDesiredHeight(this, &SDialogWindowWidget::GetButtonSize, RepButtonSmallInsileSSize)
											[
												// ---------------- Button      (Add_Down)  --------------------------
												SNew(SButton)
												.ContentPadding(0)
												.ButtonColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 0.f))
												.OnClicked(this, &SDialogWindowWidget::OnButtonClick, EProppertyToChange::ButtonAddRep, CurrentPropertyIndex)
												[
													SNew(SImage)
													.Image(ImageAddElement)
												]
											]
										]


										//   =====================  REP   "Condition button"  ===================
										+ SVerticalBox::Slot()
										.Padding(0.f, 0.f, 0.f, 0.f)
										.AutoHeight()
										.HAlign(HAlign_Left)
										.VAlign(VAlign_Center)
										[
											SNew(SBox)
											.HAlign(HAlign_Fill)
											.VAlign(VAlign_Center)
											.WidthOverride(this, &SDialogWindowWidget::GetButtonSize, RepButtonSmallInsileSSize)
											.HeightOverride(this, &SDialogWindowWidget::GetButtonSize, RepButtonSmallInsileSSize)
											[ 
												//   =====================  REP   "Condition button"  ===================
												SNew(SButton)
												.ContentPadding(0)
												.ButtonColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 0.f))
												.OnClicked(this, &SDialogWindowWidget::OnButtonClick, EProppertyToChange::CollapsedRep_Condition, CurrentPropertyIndex)
												[
													SNew(SImage)
													.Image(this, &SDialogWindowWidget::GetImageConditionButton, EProppertyToChange::CollapsedRep_Condition, CurrentPropertyIndex)
												]
											]
										]
									]
									
									//  =================    REP   ==========   "spiker"  propperty zone  ================================ 
									+ SHorizontalBox::Slot()
									.Padding(GetPadding(2, 1, 4, 1))
									.AutoWidth()
									.HAlign(HAlign_Left)
									.VAlign(VAlign_Center)
									[
										SNew(SBox)
										.Padding(GetPadding(2, 3, 4, 3))   
										.HAlign(HAlign_Left)
										.VAlign(VAlign_Center)
										.HeightOverride(RepSectionSize * SizeKoef)  // -----------   Heigh TITLE-Zone  ------------
										[
										
											SNew(SHorizontalBox)

											//   -------   REP   ImagePropertyZone     Start  -------------
											+SHorizontalBox::Slot()
											.Padding(GetPadding(2, 0, 0, 1))
											.HAlign(HAlign_Left)
											.VAlign(VAlign_Fill)
											.AutoWidth()
											[
												SNew(SBox)
									
												.Padding(0)
												.HAlign(HAlign_Fill)
												.VAlign(VAlign_Fill)
												.WidthOverride(4.f * SizeKoef)  
												[
													SNew(SBorder)
													.Padding(0)
													.HAlign(HAlign_Fill)
													.VAlign(VAlign_Fill)
													.BorderImage(PropertyResponseStart)       //   -------       ImagePropertyZone     Start  -------------
												]
											]

											//     -------   REP  Proprty Speker      ------------- 
											+SHorizontalBox::Slot()
											.Padding(GetPadding(0, 0, 0, 1))
											.HAlign(HAlign_Left)
											.VAlign(VAlign_Center)
											.AutoWidth()
											[
												SNew(SBorder)
												.Padding(0)
												.HAlign(HAlign_Fill)
												.VAlign(VAlign_Fill)
												.BorderImage(PropertyResponse)
												[

													SNew(SHorizontalBox)

													+ SHorizontalBox::Slot()
													.Padding(GetPadding(4, 1, 2, 1))
													.HAlign(HAlign_Left)
													.VAlign(VAlign_Center)
													.AutoWidth()
													[
														SNew(STextBlock)
														.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 12 * SizeKoef))
														.ColorAndOpacity(this, &SDialogWindowWidget::GetSectionTextColor, EProppertyToChange::speker, CurrentPropertyIndex)
														.Text(FText::FromString("speker:"))
													]


													+ SHorizontalBox::Slot() 
													.Padding(GetPadding(7, 4, 4, 3))
													.HAlign(HAlign_Left)
													.VAlign(VAlign_Center)
													.AutoWidth()
													[
														//  =============  Helper Panel ==============   (speker)
														SNew(SButton)
														.ContentPadding(0)
														.HAlign(HAlign_Left)
														.VAlign(VAlign_Center)
														.ButtonColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 0.f))    
														.OnClicked(this, &SDialogWindowWidget::OnHelperPanelClick, EProppertyToChange::speker, CurrentPropertyIndex)
														////////////////////.OnClicked(this, &SDialogWindowWidget::OnButtonClick, EProppertyToChange::DialogLink, CurrentPropertyIndex)
														[ 
															SNew(SOverlay)  

															+ SOverlay::Slot()           
															.HAlign(HAlign_Fill)
															.VAlign(VAlign_Center)
															[
																SNew(SBox)
																.Padding(GetPadding(0, 4, 0, 6))
																.HAlign(HAlign_Fill)
																.VAlign(VAlign_Fill)
																[
																	SNew(SImage)
																	.Image(ImageValueZone)      //       ImageValueZone
																]
															]

															+ SOverlay::Slot()
															.HAlign(HAlign_Center)
															.VAlign(VAlign_Center)
															[
																//  ===========================  REP-Spiker StaticText  ================================

																SNew(STextBlock)
																.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 12 * SizeKoef))
																.ColorAndOpacity(this, &SDialogWindowWidget::GetSectionTextColor, EProppertyToChange::speker, CurrentPropertyIndex)
																.Text(this, &SDialogWindowWidget::GetProppertyText, EProppertyToChange::speker, CurrentPropertyIndex)
															]
														]
													]
												]		
											]
											//   -------  REP  ImagePropertyZone     End  -------------
											+ SHorizontalBox::Slot()
											.Padding(GetPadding(0, 0, 5, 1))
											.HAlign(HAlign_Left)
											.VAlign(VAlign_Fill)
											.AutoWidth()
											[
												SNew(SBox)

												.Padding(0)
												.HAlign(HAlign_Fill)
												.VAlign(VAlign_Fill)
												.WidthOverride(4.f * SizeKoef)
												[
													SNew(SBorder)
													.Padding(0)
													.HAlign(HAlign_Fill)
													.VAlign(VAlign_Fill)
													.BorderImage(PropertyResponseEnd)       //   -------  REP  ImagePropertyZone     End  -------------
												]
											]
										]
									] //   REP   ==========   "sprker"  propperty zone       (END)





									
									//  =================    REP   ==========   "sound"  propperty zone     ================================
									+ SHorizontalBox::Slot()
									.Padding(GetPadding(2, 1, 4, 1))
									.AutoWidth()
									.HAlign(HAlign_Left)
									.VAlign(VAlign_Center)
									[
										SNew(SBox)
										.Padding(GetPadding(2, 3, 4, 3))
										.HAlign(HAlign_Left)
										.VAlign(VAlign_Center)
										.HeightOverride(40.f * SizeKoef)         // -----------   Heigh TITLE-Zone  ------------
										[
										
											SNew(SHorizontalBox)

											//   -------   REP   ImagePropertyZone     Start  -------------
											+SHorizontalBox::Slot()
											.Padding(GetPadding(2, 0, 0, 1))
											.HAlign(HAlign_Left)
											.VAlign(VAlign_Fill)
											.AutoWidth()
											[
												SNew(SBox)
									
												.Padding(0)
												.HAlign(HAlign_Fill)
												.VAlign(VAlign_Fill)
												.WidthOverride(4.f * SizeKoef)
												[
													SNew(SBorder)
													.Padding(0)
													.HAlign(HAlign_Fill)
													.VAlign(VAlign_Fill)
													.BorderImage(PropertyResponseStart)       //   -------   REP    ImagePropertyZone     Start  -------------
												]
											]

											//     -------   REP  Proprty  "Sound"     ------------- 
											+SHorizontalBox::Slot()
											.Padding(GetPadding(0, 0, 0, 1))
											.HAlign(HAlign_Left)
											.VAlign(VAlign_Center)
											.AutoWidth()
											[
												SNew(SBorder)
												.Padding(0)
												.HAlign(HAlign_Fill)
												.VAlign(VAlign_Fill)
												.BorderImage(PropertyResponse)
												[

													SNew(SHorizontalBox)

													+ SHorizontalBox::Slot()
													.Padding(GetPadding(4, 1, 2, 1))
													.HAlign(HAlign_Left)
													.VAlign(VAlign_Center)
													.AutoWidth()
													[
														SNew(STextBlock)
														.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 12 * SizeKoef))
														.ColorAndOpacity(this, &SDialogWindowWidget::GetSectionTextColor, EProppertyToChange::sound, CurrentPropertyIndex)
														.Text(FText::FromString("sound:"))
													]


													+ SHorizontalBox::Slot() 
													.Padding(GetPadding(7, 4, 4, 3))
													.HAlign(HAlign_Left)
													.VAlign(VAlign_Center)
													.AutoWidth()
													[										
														//  ===========  Helper Panel ===========  (Speker--Sound)
														SNew(SButton)
														.ContentPadding(0)
														.HAlign(HAlign_Left)
														.VAlign(VAlign_Center)
														.ButtonColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 0.f))    
														.OnClicked(this, &SDialogWindowWidget::OnHelperPanelClick, EProppertyToChange::sound, CurrentPropertyIndex)
														[ 
															SNew(SOverlay)  

															+ SOverlay::Slot()           
															.HAlign(HAlign_Fill)
															.VAlign(VAlign_Center)
															[
																SNew(SBox)
																.Padding(GetPadding(0, 4, 0, 6))
																.HAlign(HAlign_Fill)
																.VAlign(VAlign_Fill)
																[
																	SNew(SImage)
																	.Image(ImageValueZone)      //       ImageValueZone
																]
															]

															+ SOverlay::Slot()
															.HAlign(HAlign_Center)
															.VAlign(VAlign_Center)
															[
																//  ===========================  REP-Spiker StaticText  ================================

																SNew(STextBlock)
																.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 12 * SizeKoef))
																//.ColorAndOpacity(FLinearColor(0.7f, 0.77f, 1.f, 1))
																.ColorAndOpacity(this, &SDialogWindowWidget::GetSectionTextColor, EProppertyToChange::sound, CurrentPropertyIndex)
																.Text(this, &SDialogWindowWidget::GetProppertyText, EProppertyToChange::sound, CurrentPropertyIndex)
															]
														]
													]
												]		
											]
											//   -------  REP  ImagePropertyZone     End  -------------
											+ SHorizontalBox::Slot()
											.Padding(GetPadding(0, 0, 5, 1))
											.HAlign(HAlign_Left)
											.VAlign(VAlign_Fill)
											.AutoWidth()
											[
												SNew(SBox)

												.Padding(0)
												.HAlign(HAlign_Fill)
												.VAlign(VAlign_Fill)
												.WidthOverride(4.f * SizeKoef)
												[
													SNew(SBorder)
													.Padding(0)
													.HAlign(HAlign_Fill)
													.VAlign(VAlign_Fill)
													.BorderImage(PropertyResponseEnd)       //   -------  REP  ImagePropertyZone     End  -------------
												]
											]
										]
									] //    "sound"  propperty zone        (END)


									//****************************************
									//****************************************
									//****************************************
									//****************************************
									//  =================    REP   ==========   "EVENT"  propperty zone     ================================
									+SHorizontalBox::Slot()
									.Padding(GetPadding(2, 1, 4, 1))
									.FillWidth(1)
									.HAlign(HAlign_Left)
									.VAlign(VAlign_Center)
									[
										SNew(SBox)
										.Padding(GetPadding(2, 3, 4, 3))
										.HAlign(HAlign_Left)
										.VAlign(VAlign_Center)
										.HeightOverride(RepSectionSize * SizeKoef)  // -----------   Heigh TITLE-Zone  ------------
										[
			
											SNew(SHorizontalBox)

											//   -------   REP   ImagePropertyZone     Start  -------------
											+SHorizontalBox::Slot()
											.Padding(GetPadding(2, 0, 0, 1))
											.HAlign(HAlign_Left)
											.VAlign(VAlign_Fill)
											.AutoWidth()
											[
												SNew(SBox)
									
												.Padding(0)
												.HAlign(HAlign_Fill)
												.VAlign(VAlign_Fill)
												.WidthOverride(4.f * SizeKoef)
												[
													SNew(SBorder)
													.Padding(0)
													.HAlign(HAlign_Fill)
													.VAlign(VAlign_Fill)
													.BorderImage(PropertyResponseStart)       //   -------   REP    ImagePropertyZone     Start  -------------
												]
											] 

											//     -------   REP  Proprty       ------------- 
											+SHorizontalBox::Slot()
											.Padding(GetPadding(0, 0, 0, 1))
											.HAlign(HAlign_Left)
											.VAlign(VAlign_Center)
											.AutoWidth()
											[
												SNew(SBorder)
												.Padding(0)
												.HAlign(HAlign_Fill)
												.VAlign(VAlign_Fill)
												.BorderImage(PropertyResponse)
												[

													SNew(SHorizontalBox)

													+ SHorizontalBox::Slot()
													.Padding(GetPadding(4, 1, 2, 1))
													.HAlign(HAlign_Left)
													.VAlign(VAlign_Center)
													.AutoWidth()
													[
														SNew(STextBlock)
														.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 12 * SizeKoef))
													.ColorAndOpacity(this, &SDialogWindowWidget::GetSectionTextColor, EProppertyToChange::sound, CurrentPropertyIndex)
													.Text(FText::FromString("Event:"))
													]

													+ SHorizontalBox::Slot()
													.Padding(GetPadding(2, 0, 0, 1))
													.HAlign(HAlign_Right)
													.VAlign(VAlign_Center)
													.AutoWidth()
													[

														SNew(SButton)
														.ContentPadding(0)
														.HAlign(HAlign_Right)
														.VAlign(VAlign_Center)
														.ButtonColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 0.f))    
														.OnClicked(this, &SDialogWindowWidget::OnButtonClick, EProppertyToChange::RepEvent, CurrentPropertyIndex)
														[ 
															SNew(SOverlay)  

															+ SOverlay::Slot()           
															.HAlign(HAlign_Right)
															.VAlign(VAlign_Center)
															[
																SNew(SBox)
																.Padding(GetPadding(0, 0, 0, 0))
																.HAlign(HAlign_Fill)
																.VAlign(VAlign_Fill)
																[
																	SNew(SImage)
																	.Image(ImageValueZone)      //       ImageValueZone
																]
															]

															+ SOverlay::Slot()
															.HAlign(HAlign_Center)
															.VAlign(VAlign_Center)
															[
																//  ===========================  REP-EVENT StaticText  ================================
																SNew(SHorizontalBox)
														
																+ SHorizontalBox::Slot()
																.Padding(GetPadding(5, 0, 4, 0))
																.HAlign(HAlign_Center)
																.VAlign(VAlign_Center)
																.AutoWidth()
																[
																	//  ===========================  REP-EVENT StaticText  ================================
																	//SAssignNew(DialogSection[i_Dlg].SpeechSection[i_Speech].SpeechSectionName_Statick, STextBlock)   
																	SNew(STextBlock)   
																	.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 12 * SizeKoef))
															

																	.Visibility(this, &SDialogWindowWidget::GetVisibilityOfSectionPropperty_Static, EProppertyToChange::RepEvent, CurrentPropertyIndex)
																	.ColorAndOpacity(this, &SDialogWindowWidget::GetSectionTextColor, EProppertyToChange::RepEvent, CurrentPropertyIndex)
																	.Text(this, &SDialogWindowWidget::GetProppertyText, EProppertyToChange::RepEvent, CurrentPropertyIndex)
																]

																+ SHorizontalBox::Slot()
																.HAlign(HAlign_Center)
																.VAlign(VAlign_Center)
																[
																	SNew(SBox)
																	.MinDesiredWidth(70.f * SizeKoef)
																	.HAlign(HAlign_Fill)
																	.VAlign(VAlign_Fill)
																	[
																		//  ===========================  REP-EVENT EditableText  ================================
																		SAssignNew(DialogSection[i_Dlg].SpeechSection[i_Speech].ReplicSection[i_Replic]
																											.RepSection[i_Rep].RepEvent_EditableText, SEditableTextBox)
																		.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 14 * SizeKoef))
																		.Visibility(this, &SDialogWindowWidget::GetVisibilityOfSectionPropperty_Editable, EProppertyToChange::RepEvent, CurrentPropertyIndex)
																		.Text(FText::FromString(DialogSection[i_Dlg].SpeechSection[i_Speech].ReplicSection[i_Replic]
																																	.RepSection[i_Rep].RepEvent))
																		.OnTextCommitted(this, &SDialogWindowWidget::ConfirmEditableTextBox, EProppertyToChange::RepEvent, CurrentPropertyIndex)  // PRES_ENTER:   void ConfirmEditableTextBox(const FText& Text, ETextCommit::Type TextType);
																		.OnTextChanged_Raw(this, &SDialogWindowWidget::OnEditableTextChange)  // void OnButtonT(const FText& Text);
																	]
																]
															]
														]
													]


												]
											]



											//   -------  REP  ImagePropertyZone     End  -------------
											+ SHorizontalBox::Slot()
											.Padding(GetPadding(0, 0, 5, 1))
											.HAlign(HAlign_Left)
											.VAlign(VAlign_Fill)
											.AutoWidth()
											[
												SNew(SBox)

												.Padding(0)
												.HAlign(HAlign_Fill)
												.VAlign(VAlign_Fill)
												.WidthOverride(4.f * SizeKoef)
												[
													SNew(SBorder)
													.Padding(0)
													.HAlign(HAlign_Fill)
													.VAlign(VAlign_Fill)
													.BorderImage(PropertyResponseEnd)       //   -------  REP  ImagePropertyZone     End  -------------
												]
											]

										]
										
										
									]

									//  =================    REP   ==========   "Time"  propperty zone     ================================
									+ SHorizontalBox::Slot()
									.Padding(GetPadding(2, 1, 4, 1))
									.AutoWidth()
									.HAlign(HAlign_Right)
									.VAlign(VAlign_Center)
									[
										SNew(SBox)
										.Padding(GetPadding(2, 3, 4, 3))
										.HAlign(HAlign_Right)
										.VAlign(VAlign_Center)
										.HeightOverride(RepSectionSize * SizeKoef)  // -----------   Heigh TITLE-Zone  ------------
										[
										
											SNew(SHorizontalBox)

											//   -------   REP   ImagePropertyZone     Start  -------------
											+SHorizontalBox::Slot()
											.Padding(GetPadding(2, 0, 0, 1))
											.HAlign(HAlign_Right)
											.VAlign(VAlign_Fill)
											.AutoWidth()
											[
												SNew(SBox)
									
												.Padding(0)
												.HAlign(HAlign_Fill)
												.VAlign(VAlign_Fill)
												.WidthOverride(4.f * SizeKoef)
												[
													SNew(SBorder)
													.Padding(0)
													//.HAlign(HAlign_Left)
													.HAlign(HAlign_Fill)
													.VAlign(VAlign_Fill)
													.BorderImage(PropertyResponseStart)       //   -------   REP    ImagePropertyZone     Start  -------------
												]
											]

											//     -------   REP  Proprty       ------------- 
											+SHorizontalBox::Slot()
											.Padding(GetPadding(0, 0, 0, 1))
											.HAlign(HAlign_Left)
											.VAlign(VAlign_Center)
											.AutoWidth()
											[
												SNew(SBorder)
												.Padding(0)
												//.HAlign(HAlign_Left)
												.HAlign(HAlign_Fill)
												.VAlign(VAlign_Fill)
												.BorderImage(PropertyResponse)
												[

													SNew(SHorizontalBox)

													+ SHorizontalBox::Slot()
													.Padding(GetPadding(4, 1, 2, 1))
													.HAlign(HAlign_Left)
													.VAlign(VAlign_Center)
													.AutoWidth()
													[
														SNew(STextBlock)
														.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 12 * SizeKoef))
														//.ColorAndOpacity(FLinearColor(0.7f, 0.77f, 1.f, 1))
														.ColorAndOpacity(this, &SDialogWindowWidget::GetSectionTextColor, EProppertyToChange::time, CurrentPropertyIndex)
														.Text(FText::FromString("time:"))
													]



													+ SHorizontalBox::Slot() 
													.Padding(GetPadding(7, 4, 4, 3))
													.HAlign(HAlign_Left)
													.VAlign(VAlign_Center)
													.AutoWidth()
													[			
														//  ===============  Helper PAnel ================  (speker--Time)
														SNew(SButton)
														.ContentPadding(0)
														.HAlign(HAlign_Left)
														.VAlign(VAlign_Center)
														.ButtonColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 0.f))    
														.OnClicked(this, &SDialogWindowWidget::OnHelperPanelClick, EProppertyToChange::time, CurrentPropertyIndex) 
														[ 
															SNew(SOverlay)  

															+ SOverlay::Slot()           
															.HAlign(HAlign_Fill)
															.VAlign(VAlign_Center)
															//--.AutoWidth()
															[
																SNew(SBox)
																.Padding(GetPadding(0, 4, 0, 6))
																.HAlign(HAlign_Fill)
																.VAlign(VAlign_Fill)
																[
																	SNew(SImage)
																	.Image(ImageValueZone)      //       ImageValueZone
																]
															]

															+ SOverlay::Slot()
															.HAlign(HAlign_Center)
															.VAlign(VAlign_Center)
															[
																//  ===========================  REP-Time StaticText  ================================

																SNew(STextBlock)
																.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 12 * SizeKoef))
																//.ColorAndOpacity(FLinearColor(0.7f, 0.77f, 1.f, 1))
																.ColorAndOpacity(this, &SDialogWindowWidget::GetSectionTextColor, EProppertyToChange::time, CurrentPropertyIndex)
																.Text(this, &SDialogWindowWidget::GetProppertyText, EProppertyToChange::time, CurrentPropertyIndex)
															]
														]
													]
												]		
											]
											//   -------  REP  ImagePropertyZone     End  -------------
											+ SHorizontalBox::Slot()
											.Padding(GetPadding(0, 0, 5, 1))
											.HAlign(HAlign_Left)
											.VAlign(VAlign_Fill)
											.AutoWidth()
											[
												SNew(SBox)

												.Padding(0)
												.HAlign(HAlign_Fill)
												.VAlign(VAlign_Fill)
												.WidthOverride(4.f * SizeKoef)
												[
													SNew(SBorder)
													.Padding(0)
													//.HAlign(HAlign_Left)
													.HAlign(HAlign_Fill)
													.VAlign(VAlign_Fill)
													.BorderImage(PropertyResponseEnd)       //   -------  REP  ImagePropertyZone     End  -------------
												]
											]
										]
									] //    "Time"  propperty zone        (END)





									//  =================    REP   ==========   "Delay"  propperty zone     ================================
									+ SHorizontalBox::Slot()
									.Padding(GetPadding(2, 1, 4, 1))
									.AutoWidth()
									//.FillWidth(1)
									.HAlign(HAlign_Right)
									.VAlign(VAlign_Center)
									[
										SNew(SBox)
										.Padding(GetPadding(2, 3, 4, 3))
										//MaxDesiredWidth(FOptionalSize())
										.HAlign(HAlign_Right)
										.VAlign(VAlign_Center)
										//.WidthOverride(20.f)
										.HeightOverride(40.f * SizeKoef)         // -----------   Heigh TITLE-Zone  ------------
										[
										
											SNew(SHorizontalBox)

											//   -------   REP   ImagePropertyZone     Start  -------------
											+SHorizontalBox::Slot()
											.Padding(GetPadding(2, 0, 0, 1))
											.HAlign(HAlign_Right)
											.VAlign(VAlign_Fill)
											.AutoWidth()
											[
												SNew(SBox)
									
												.Padding(0)
												.HAlign(HAlign_Fill)
												.VAlign(VAlign_Fill)
												.WidthOverride(4.f * SizeKoef)
												[
													SNew(SBorder)
													.Padding(0)
													//.HAlign(HAlign_Left)
													.HAlign(HAlign_Fill)
													.VAlign(VAlign_Fill)
													.BorderImage(PropertyResponseStart)       //   -------   REP    ImagePropertyZone     Start  -------------
												]
											]

											//     -------   REP  Proprty       ------------- 
											+SHorizontalBox::Slot()
											.Padding(GetPadding(0, 0, 0, 1))
											.HAlign(HAlign_Left)
											.VAlign(VAlign_Center)
											.AutoWidth()
											[
												SNew(SBorder)
												.Padding(0)
												//.HAlign(HAlign_Left)
												.HAlign(HAlign_Fill)
												.VAlign(VAlign_Fill)
												.BorderImage(PropertyResponse)
												[

													SNew(SHorizontalBox)

													+ SHorizontalBox::Slot()
													.Padding(GetPadding(4, 1, 2, 1))
													.HAlign(HAlign_Left)
													.VAlign(VAlign_Center)
													.AutoWidth()
													[
														SNew(STextBlock)
														.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 12 * SizeKoef))
														//.ColorAndOpacity(FLinearColor(0.7f, 0.77f, 1.f, 1))
														.ColorAndOpacity(this, &SDialogWindowWidget::GetSectionTextColor, EProppertyToChange::delay, CurrentPropertyIndex)
														.Text(FText::FromString("delay:"))
													]



													+ SHorizontalBox::Slot() 
													.Padding(GetPadding(7, 4, 4, 3))
													.HAlign(HAlign_Left)
													.VAlign(VAlign_Center)
													.AutoWidth()
													[										
														//  ===========================  REP-Delay SpinBox  ================================
														SNew(SBox)
														.MinDesiredHeight(20.f * SizeKoef)
														//.MinDesiredWidth(70.f)
														.HAlign(HAlign_Fill)
														.VAlign(VAlign_Fill)
														[
															SNew(SSpinBox<float>)
															.MinValue(0.f)
															.MaxValue(100.f)
															//.Value(SDialogWindowWidget::GetDelayValue())  //, EProppertyToChange::Delay, CurrentPropertyIndex
															.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 12 * SizeKoef))
															.Value(FCString::Atof(*DialogSection[CurrentPropertyIndex.iDialog].SpeechSection[CurrentPropertyIndex.iSpeech]
																						.ReplicSection[CurrentPropertyIndex.iReplic]
																						.RepSection[CurrentPropertyIndex.iRep].Delay.ToString()))
															.OnValueCommitted(this, &SDialogWindowWidget::SetTimeValue, EProppertyToChange::delay, CurrentPropertyIndex)
														]
													]
												]		
											]
											//   -------  REP  ImagePropertyZone     End  -------------
											+ SHorizontalBox::Slot()
											.Padding(GetPadding(0, 0, 5, 1))
											.HAlign(HAlign_Left)
											.VAlign(VAlign_Fill)
											.AutoWidth()
											[
												SNew(SBox)

												.Padding(0)
												.HAlign(HAlign_Fill)
												.VAlign(VAlign_Fill)
												.WidthOverride(4.f * SizeKoef)
												[
													SNew(SBorder)
													.Padding(0)
													//.HAlign(HAlign_Left)
													.HAlign(HAlign_Fill)
													.VAlign(VAlign_Fill)
													.BorderImage(PropertyResponseEnd)       //   -------  REP  ImagePropertyZone     End  -------------
												]
											]
										]
									] //    "delay"  propperty zone        (END)
									
								]
							]
						]

						//  ================   REP CONDITION:      (Dynamick Add)   ================
						+ SVerticalBox::Slot()
						.Padding(GetPadding(3.f, 3.f, 3.f, 3.f))
						.AutoHeight()
						.HAlign(HAlign_Fill)
						.VAlign(VAlign_Top)
						[
							SAssignNew(DialogSection[i_Dlg].SpeechSection[i_Speech].ReplicSection[i_Replic].RepSection[i_Rep].RepConditionBlock, SVerticalBox)
							//.Visibility(this, &SDialogWindowWidget::GetIsSectionCollapsed, EButtonDialogType::CollapsedReplicSection, i_Dlg, i_Speech, i_Replic, i_Rep)
							.Visibility(this, &SDialogWindowWidget::IsSectionCollapsed, EProppertyToChange::CollapsedRep_Condition, CurrentPropertyIndex)

						]

						//  ================   REP CONTENT:      (Dynamick Add)   ================
						+ SVerticalBox::Slot()
						.Padding(GetPadding(90.f, 1.f, 10.f, 1.f))
						.AutoHeight()
						.HAlign(HAlign_Fill)
						.VAlign(VAlign_Fill)
						[
							SNew(SBox)
							.MaxDesiredHeight(RepMultiplyTextSize * SizeKoef)
							[
							//	SAssignNew(DialogSection[i_Dlg].SpeechSection[i_Speech].ReplicSection[i_Replic].ReplicComent_EditableMultiline, SMultiLineEditableTextBox) 	SMultiLineEditableTextBox)
								SNew(SMultiLineEditableTextBox)
								.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 12 * SizeKoef))
								.Text(FText::FromString(DialogSection[i_Dlg].SpeechSection[i_Speech].ReplicSection[i_Replic].RepSection[i_Rep].ComentText))
								.OnTextCommitted(this, &SDialogWindowWidget::ConfirmEditableMultilineTextBox, EProppertyToChange::repComent, CurrentPropertyIndex)
								.OnTextChanged_Raw(this, &SDialogWindowWidget::OnEditableTextChange)  // void OnButtonT(const FText& Text);
							]
						]
						//SNew(STextBlock).Text(FText::FromString("aaaaaaaaaa"))
					]; 





					//  =========================================================================================================
					//  =========================================================================================================
					//  ==============================               REP - CONDITION               ==============================
					//  =========================================================================================================
					//  =========================================================================================================

					for (int32 i_RepCondition = 0; i_RepCondition < DialogSection[i_Dlg].SpeechSection[i_Speech].ReplicSection[i_Replic].RepSection[i_Rep].RepCondition.Num(); i_RepCondition++)
					{

						CurrentPropertyIndex.iSpeechCondition = -1;
						CurrentPropertyIndex.iReplicCondition = -1;
						CurrentPropertyIndex.iResponse = -1;
						CurrentPropertyIndex.iResponseCondition = -1;
						CurrentPropertyIndex.iRepCondition = i_RepCondition; 



						FVariablesParameter SpeechVariablesParameter;
						SpeechVariablesParameter.ConditionBlock = &DialogSection[CurrentPropertyIndex.iDialog]
							.SpeechSection[CurrentPropertyIndex.iSpeech].ReplicSection[CurrentPropertyIndex.iReplic]
							.RepSection[CurrentPropertyIndex.iRep].RepConditionBlock;
						SpeechVariablesParameter.TextBoxCondition_Type = &DialogSection[CurrentPropertyIndex.iDialog]
							.SpeechSection[CurrentPropertyIndex.iSpeech]
							.ReplicSection[CurrentPropertyIndex.iReplic]
							.RepSection[CurrentPropertyIndex.iRep]
							.RepCondition[CurrentPropertyIndex.iRepCondition]
							.Condition_Type_Editable;
						SpeechVariablesParameter.TextBoxVariable_Name = &DialogSection[CurrentPropertyIndex.iDialog]
							.SpeechSection[CurrentPropertyIndex.iSpeech]
							.ReplicSection[CurrentPropertyIndex.iReplic]
							.RepSection[CurrentPropertyIndex.iRep]
							.RepCondition[CurrentPropertyIndex.iRepCondition]
							.ConditionVariable_Name_Editable;
						SpeechVariablesParameter.TextBoxVariable_Value = &DialogSection[CurrentPropertyIndex.iDialog]
							.SpeechSection[CurrentPropertyIndex.iSpeech]
							.ReplicSection[CurrentPropertyIndex.iReplic]
							.RepSection[CurrentPropertyIndex.iRep]
							.RepCondition[CurrentPropertyIndex.iRepCondition]
							.ConditionVariable_Value_Editable;
						SpeechVariablesParameter.Type_Text = &DialogSection[CurrentPropertyIndex.iDialog]
							.SpeechSection[CurrentPropertyIndex.iSpeech]
							.ReplicSection[CurrentPropertyIndex.iReplic]
							.RepSection[CurrentPropertyIndex.iRep]
							.RepCondition[CurrentPropertyIndex.iRepCondition].ConditionType;
						SpeechVariablesParameter.VariableName_Text = &DialogSection[CurrentPropertyIndex.iDialog]
							.SpeechSection[CurrentPropertyIndex.iSpeech]
							.ReplicSection[CurrentPropertyIndex.iReplic]
							.RepSection[CurrentPropertyIndex.iRep]
							.RepCondition[CurrentPropertyIndex.iRepCondition].VariableName;
						SpeechVariablesParameter.VariableValue_Text = &DialogSection[CurrentPropertyIndex.iDialog]
							.SpeechSection[CurrentPropertyIndex.iSpeech]
							.ReplicSection[CurrentPropertyIndex.iReplic]
							.RepSection[CurrentPropertyIndex.iRep]
							.RepCondition[CurrentPropertyIndex.iRepCondition].VariableValue;
						SpeechVariablesParameter.AddButtonPropperty = EProppertyToChange::ButtonAddRep_Condition;
						SpeechVariablesParameter.RemoveButtonPropperty = EProppertyToChange::RemoveRep_Condition;
						SpeechVariablesParameter.ConditionTypePropperty = EProppertyToChange::rep_condition_type;
						SpeechVariablesParameter.CompareType = EProppertyToChange::rep_condition_CompareType;
						SpeechVariablesParameter.VarTypePropperty = EProppertyToChange::rep_condition_varType;
						SpeechVariablesParameter.VarNamePropperty = EProppertyToChange::rep_condition_varName;
						SpeechVariablesParameter.VarValuePropperty = EProppertyToChange::rep_condition_varValue;


						DrawConditionElement(CurrentPropertyIndex, SpeechVariablesParameter);


						////TSharedPtr<SVerticalBox>* RepConditionBlock = &DialogSection[i_Dlg].SpeechSection[i_Speech].ReplicSection[i_Replic].RepSection[i_Rep].RepConditionBlock;
						//TSharedPtr<SVerticalBox>* RepConditionBlock = &DialogSection[CurrentPropertyIndex.iDialog]
						//	.SpeechSection[CurrentPropertyIndex.iSpeech].ReplicSection[CurrentPropertyIndex.iReplic]
						//	.RepSection[CurrentPropertyIndex.iRep].RepConditionBlock;       // i_Rep     XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
						//
						//TSharedPtr<SEditableTextBox>* TextBoxCondition_Type = &DialogSection[CurrentPropertyIndex.iDialog]
						//							.SpeechSection[CurrentPropertyIndex.iSpeech]
						//							.ReplicSection[CurrentPropertyIndex.iReplic]
						//							.RepSection[CurrentPropertyIndex.iRep]
						//							.RepCondition[CurrentPropertyIndex.iRepCondition].Condition_Type_Editable;

						//TSharedPtr<SEditableTextBox>* TextBoxVariable_Name = &DialogSection[CurrentPropertyIndex.iDialog]
						//							.SpeechSection[CurrentPropertyIndex.iSpeech]
						//							.ReplicSection[CurrentPropertyIndex.iReplic]
						//							.RepSection[CurrentPropertyIndex.iRep]
						//							.RepCondition[CurrentPropertyIndex.iRepCondition].ConditionVariable_Name_Editable;
						//TSharedPtr<SEditableTextBox>* TextBoxVariable_Value = &DialogSection[CurrentPropertyIndex.iDialog]
						//							.SpeechSection[CurrentPropertyIndex.iSpeech]
						//							.ReplicSection[CurrentPropertyIndex.iReplic]
						//							.RepSection[CurrentPropertyIndex.iRep]
						//							.RepCondition[CurrentPropertyIndex.iRepCondition].ConditionVariable_Value_Editable;
						//FName* Type_Text = &DialogSection[CurrentPropertyIndex.iDialog].SpeechSection[CurrentPropertyIndex.iSpeech]
						//							.ReplicSection[CurrentPropertyIndex.iReplic]
						//							.RepSection[CurrentPropertyIndex.iRep]
						//							.RepCondition[CurrentPropertyIndex.iRepCondition].ConditionType;

						//FName* VariableName_Text = &DialogSection[CurrentPropertyIndex.iDialog]
						//							.SpeechSection[CurrentPropertyIndex.iSpeech]
						//							.ReplicSection[CurrentPropertyIndex.iReplic]
						//							.RepSection[CurrentPropertyIndex.iRep]
						//							.RepCondition[CurrentPropertyIndex.iRepCondition].VariableName;


						//FName* VariableValue_Text = &DialogSection[CurrentPropertyIndex.iDialog].SpeechSection[CurrentPropertyIndex.iSpeech]
						//							.ReplicSection[CurrentPropertyIndex.iReplic]
						//							.RepSection[CurrentPropertyIndex.iRep]
						//							.RepCondition[CurrentPropertyIndex.iRepCondition].VariableValue;

						//EProppertyToChange AddButtonPropperty = EProppertyToChange::ButtonAddRep_Condition;
						////EProppertyToChange MoveButtonPropperty = EProppertyToChange::MoveRep_Condition;
						//EProppertyToChange RemoveButtonPropperty = EProppertyToChange::RemoveRep_Condition;
						//EProppertyToChange ConditionTypePropperty = EProppertyToChange::rep_condition_type;
						//EProppertyToChange CompareType = EProppertyToChange::rep_condition_CompareType;
						//EProppertyToChange VarTypePropperty = EProppertyToChange::rep_condition_varType;
						//EProppertyToChange VarNamePropperty = EProppertyToChange::rep_condition_varName;
						//EProppertyToChange VarValuePropperty = EProppertyToChange::rep_condition_varValue;

						//DrawConditionElement(*RepConditionBlock,
						//						CurrentPropertyIndex,
						//						AddButtonPropperty,
						//						//MoveButtonPropperty,
						//						RemoveButtonPropperty,

						//						*TextBoxCondition_Type,
						//						*Type_Text,
						//						ConditionTypePropperty,
						//						//CompareType,
						//						*TextBoxVariable_Name,
						//						*VariableName_Text,
						//						VarNamePropperty,
						//						*TextBoxVariable_Value,
						//						*VariableValue_Text,
						//						VarValuePropperty,

						//						VarTypePropperty);
					}

				}  // i_Rep
			}//   i_Replic




			//***************************************************************************************************************************************
			//*************************************************            RESPONSE            ******************************************************
			//*******************************************                                           *************************************************
			//***************************************************************************************************************************************
			for (int32 i_Response = 0; i_Response < DialogSection[i_Dlg].SpeechSection[i_Speech].ResponseSection.Num(); i_Response++)
			{


				//int32 aaa = DialogSection[i_Dlg].SpeechSection[i_Speech].ResponseSection.Num();
				CurrentPropertyIndex.iReplic = -1;
				CurrentPropertyIndex.iRep = -1;
				CurrentPropertyIndex.iResponse = i_Response;
				 

				DialogSection[i_Dlg].SpeechSection[i_Speech].ReplicAndResponseBlock->AddSlot()
				.Padding(GetPadding(50.f, 0.f, 10.f, 0.f))
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.AutoHeight()
				[
					SNew(SVerticalBox)

					//  All RESPONSE-Section
					+ SVerticalBox::Slot()            
					.Padding(GetPadding(3.f, 3.f, 3.f, 3.f))
					.AutoHeight()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					[
						SNew(SHorizontalBox)

						//  --------------   Buttons new RESPONSE-Section (Add_Down)  -----------------
        						
						+ SHorizontalBox::Slot()
						.Padding(0.f, 0.f, 0.f, 0.f)        // L, Up, R, Dn
						.HAlign(HAlign_Left)
						.VAlign(VAlign_Center)
						.AutoWidth()
						[


							SNew(SVerticalBox)

							//   ====================      RESPONSE       (Remove Section)   ============================
							+ SVerticalBox::Slot()
							.HAlign(HAlign_Left)
							.VAlign(VAlign_Center)
							//.AutoHeight()
							.FillHeight(1)
							[
								SNew(SBox)
								.Padding(0)
								.HAlign(HAlign_Left)
								.VAlign(VAlign_Top)
								.WidthOverride(24.f * SizeKoef)
								.HeightOverride(24.f * SizeKoef)
								//.HeightOverride(20.f)
								[
									SNew(SButton)
									.ContentPadding(0)
									.ButtonColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 0.f))
									.OnClicked(this, &SDialogWindowWidget::OnButtonRemoveClick, EProppertyToChange::RemoveResponse, CurrentPropertyIndex)
									[
										SNew(SImage)
										.Image(ImageDeleteElement)  
									]
								]
							]

							//   ======================       RESPONSE  ( Move )        ============================
							+ SVerticalBox::Slot()
							.Padding(0.f, 0.f, 0.f, 0.f)
							.AutoHeight()
							//.FillHeight(1)
							//.MaxWidth(30.f)
							.HAlign(HAlign_Left)
							.VAlign(VAlign_Center)
							[
								SNew(SBox)
								.HAlign(HAlign_Fill)
								.VAlign(VAlign_Fill)
								.WidthOverride(22.f * SizeKoef)
								.HeightOverride(22.f * SizeKoef)
								[
									SNew(SButton)
									.ContentPadding(0)
									.ButtonColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 0.f))
									.OnClicked(this, &SDialogWindowWidget::OnHelperPanelClick, EProppertyToChange::MoveResponse, CurrentPropertyIndex)
									[
										SNew(SImage)
										.Image(ImageMoveElement)
									]						
								]
							]							

						]


						//  ---------- Title-RESPONSE    START  ----------------
						+SHorizontalBox::Slot()
						.Padding(0.f, 0.f, 0.f, 0.f)        // L, Up, R, Dn
						.HAlign(HAlign_Fill)
						.VAlign(VAlign_Fill)
						//+++++++++.VAlign(VAlign_Center)
						.AutoWidth()
						[
							SNew(SBox)
							//MaxDesiredWidth(FOptionalSize())
							.Padding(0)
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Fill)
							.WidthOverride(5.f * SizeKoef)
							//.HeightOverride(20.f)
							[
								SNew(SBorder)
								.Padding(0)
								.HAlign(HAlign_Fill)
								.VAlign(VAlign_Fill)
								.BorderImage(TitleResponseStart)                  //   Title-REPLICK    START    //TitleDialogStart
							]
						]


						//  ---------- Title-RESPONSE    BODY  ----------------
						+ SHorizontalBox::Slot()
						.Padding(0.f, 0.f, 0.f, 0.f)        // L, Up, R, Dn
						.HAlign(HAlign_Fill)
						.VAlign(VAlign_Fill)
						.FillWidth(1)
						[
							//------------ALL RESPONSE-Section ----------
							SNew(SBorder)
							.HAlign(HAlign_Fill)/////
							.VAlign(VAlign_Fill)//////
							.BorderImage(TitleResponse)      //TitleDialog
							.OnMouseButtonDown(this, &SDialogWindowWidget::OnButtonMarkerUsual, EProppertyToChange::MarkerResponse, CurrentPropertyIndex)
							//.OnMouseDoubleClick(this, &SDialogWindowWidget::OnButtonMarkerLink, EProppertyToChange::MarkerResponse, CurrentPropertyIndex)
							[
								SNew(SHorizontalBox)


								+ SHorizontalBox::Slot()    // RESPONSE-Section title------COLLAPSED------Content Button
								.Padding(GetPadding(0, 3.f, 0, 3.f))
								.AutoWidth()
								//.FillWidth(1)
								.MaxWidth(30.f * SizeKoef)
								.HAlign(HAlign_Left)
								.VAlign(VAlign_Fill)
								[


									SNew(SVerticalBox)

									//  ------------------------------    RESPONSE    Add    BUTTON    ----------------------

									+ SVerticalBox::Slot()
									.Padding(0.f, 0.f, 0.f, 0.f)

									.AutoHeight()
									//.MaxWidth(30.f)
									.HAlign(HAlign_Center)
									.VAlign(VAlign_Center)
									[
										
										SNew(SBox)
										.WidthOverride(20.f * SizeKoef)
										.MaxDesiredHeight(20.f * SizeKoef)
										//.HeightOverride(20.f)
										[

											SNew(SButton)             //  Button new-RESPONSE-Section  (Add_Down)
											.ContentPadding(0)
											.ButtonColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 0.f))
											.OnClicked(this, &SDialogWindowWidget::OnButtonClick, EProppertyToChange::AddResponse, CurrentPropertyIndex)
											[
												SNew(SImage)
												.Image(ImageAddElement)
											]						
										]
										
									]


									//  ------------------------------    RESPONSE    CONDITION--COLLAPSED  BUTTON    ----------------------
									+ SVerticalBox::Slot()
									.Padding(0.f, 0.f, 0.f, 0.f)

									.AutoHeight()
									//.MaxWidth(30.f)
									.HAlign(HAlign_Center)
									.VAlign(VAlign_Center)
									[
										SNew(SBox)
										.HAlign(HAlign_Center)
										.VAlign(VAlign_Center)
										.WidthOverride(20.f * SizeKoef)
										.HeightOverride(20.f * SizeKoef)
										[
											//   =====================  RESPONSE   "Condition--COLLAPSED button"  ===================
											SNew(SButton)
											.ContentPadding(0)
											.ButtonColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 0.f))
											.OnClicked(this, &SDialogWindowWidget::OnButtonClick, EProppertyToChange::CollapsedResponse_Condition, CurrentPropertyIndex)
											[
												SNew(SImage)
												.Image(this, &SDialogWindowWidget::GetImageConditionButton, EProppertyToChange::CollapsedResponse_Condition, CurrentPropertyIndex)
											]
										]
									]
								]




								//    ======================       RESPONSE     COLLAPSED  "Variables"      Content Button      ==================
								+ SHorizontalBox::Slot()
								.Padding(GetPadding(4, 0, 0, 0))
								.AutoWidth()
								//.FillWidth(1)
								.HAlign(HAlign_Left)
								.VAlign(VAlign_Center)
								[
									SNew(SBox)
										//MaxDesiredWidth(FOptionalSize())
										.HAlign(HAlign_Center)
										.VAlign(VAlign_Center)
										.WidthOverride(30.f * SizeKoef)
										.HeightOverride(30.f * SizeKoef)
										[
											//  --------------------     RESPONSE-Section title----COLLAPSED-----Content Button
											SNew(SButton)
											.ContentPadding(0)
											.ButtonColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 0.f))
											.OnClicked(this, &SDialogWindowWidget::OnButtonClick, EProppertyToChange::CollapsedResponse_Variables, CurrentPropertyIndex)
											[
												SNew(SImage)
												.Image(this, &SDialogWindowWidget::GetImageConditionButton, EProppertyToChange::CollapsedResponse_Variables, CurrentPropertyIndex)
												//.Image(ImageVariableButtonOn)    
												//.BorderImage(this, &SDialogWindowWidget::GetImageButtonSectionCollapsed, EButtonDialogType::CollapsedDialogSection, i_Dlg, -1, -1)
											]

										]
								]	
									
								//  ==============================     PESPONSE--REPEAT--PROPERTY   =======================
								+ SHorizontalBox::Slot()
								.Padding(GetPadding(4, 1, 4, 1))
								.AutoWidth()
								//.FillWidth(1)
								.HAlign(HAlign_Left)
								.VAlign(VAlign_Center)
								[
									SNew(SBox)
									.Padding(GetPadding(4, 3, 4, 3))
									//MaxDesiredWidth(FOptionalSize())
									.HAlign(HAlign_Left)
									.VAlign(VAlign_Center)
									//.WidthOverride(20.f)
									.HeightOverride(40.f * SizeKoef)         // -----------   Heigh TITLE-Zone  ------------
									[
										
										SNew(SHorizontalBox)


										//   -------   RESPONSE   ImagePropertyZone     Start  -------------
										+SHorizontalBox::Slot()
										.Padding(GetPadding(2, 0, 0, 1))
										.HAlign(HAlign_Left)
										.VAlign(VAlign_Fill)
										.AutoWidth()
										[
											SNew(SBox)
									
											.Padding(0)
											.HAlign(HAlign_Fill)
											.VAlign(VAlign_Fill)
											.WidthOverride(4.f * SizeKoef)
											[
												SNew(SBorder)
												.Padding(0)
												//.HAlign(HAlign_Left)
												.HAlign(HAlign_Fill)
												.VAlign(VAlign_Fill)
												.BorderImage(PropertyReplicStart)       //   -------   RESPONSE    ImagePropertyZone     Start  -------------
											]
										]

										+SHorizontalBox::Slot()
										.Padding(GetPadding(0, 0, 0, 1))
										.HAlign(HAlign_Left)
										.VAlign(VAlign_Fill)
										.AutoWidth()
										[
											SNew(SBorder)
											.Padding(0)
											//.HAlign(HAlign_Left)
											.HAlign(HAlign_Fill)
											.VAlign(VAlign_Center)
											.BorderImage(PropertyReplic)
											[
													SNew(STextBlock)
													//.Padding(FMargin(4, 1, 2, 1))
													.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 14 * SizeKoef))
													//.ColorAndOpacity(FLinearColor(0.7f, 0.77f, 1.f, 1))
													.ColorAndOpacity(this, &SDialogWindowWidget::GetSectionTextColor, EProppertyToChange::repeatResponse, CurrentPropertyIndex)
													.Text(FText::FromString("RESPONSE:"))
											]
										]
										//   -------  RESPONSE  ImagePropertyZone     End  -------------
										+ SHorizontalBox::Slot()
										.Padding(GetPadding(0, 0, 0, 1))
										.HAlign(HAlign_Left)
										.VAlign(VAlign_Fill)
										.AutoWidth()
										[
											SNew(SBox)

											.Padding(0)
											.HAlign(HAlign_Fill)
											.VAlign(VAlign_Fill)
											.WidthOverride(4.f * SizeKoef)
											[
												SNew(SBorder)
												.Padding(0)
												//.HAlign(HAlign_Left)
												.HAlign(HAlign_Fill)
												.VAlign(VAlign_Fill)
												.BorderImage(PropertyReplicEnd)       //   -------  RESPONSE  ImagePropertyZone     End  -------------
											]
										]



										//   -------   RESPONSE   ImagePropertyZone     Start  -------------
										+SHorizontalBox::Slot()
										.Padding(GetPadding(15, 0, 0, 1))
										.HAlign(HAlign_Left)
										.VAlign(VAlign_Fill)
										.AutoWidth()
										[
											SNew(SBox)
									
											.Padding(0)
											.HAlign(HAlign_Fill)
											.VAlign(VAlign_Fill)
											.WidthOverride(4.f * SizeKoef)
											[
												SNew(SBorder)
												.Padding(0)
												//.HAlign(HAlign_Left)
												.HAlign(HAlign_Fill)
												.VAlign(VAlign_Fill)
												.BorderImage(PropertyResponseStart)       //   -------   RESPONSE    ImagePropertyZone     Start  -------------
											]
										]

										//     -------   RESPONSE  Proprty  "Repeat"     ------------- 
										+SHorizontalBox::Slot()
										.Padding(GetPadding(0, 0, 0, 1))
										.HAlign(HAlign_Left)
										.VAlign(VAlign_Center)
										.AutoWidth()
										[
											SNew(SBorder)
											.Padding(0)
											//.HAlign(HAlign_Left)
											.HAlign(HAlign_Fill)
											.VAlign(VAlign_Fill)
											.BorderImage(PropertyResponse) //ImagePropertyZoneStart
											[

												SNew(SHorizontalBox)

												+ SHorizontalBox::Slot()
												.Padding(GetPadding(4, 1, 2, 1))
												.HAlign(HAlign_Left)
												.VAlign(VAlign_Center)
												.AutoWidth()
												[ 
													SNew(STextBlock)
													.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 10 * SizeKoef))
													//.ColorAndOpacity(FLinearColor(0.7f, 0.77f, 1.f, 1))
													.ColorAndOpacity(this, &SDialogWindowWidget::GetSectionTextColor, EProppertyToChange::repeatResponse, CurrentPropertyIndex)
													.Text(FText::FromString("repeat:"))
												]


												+ SHorizontalBox::Slot() 
												.Padding(GetPadding(7, 4, 4, 3))
												.HAlign(HAlign_Left)
												.VAlign(VAlign_Center)
												.AutoWidth()
												[
													//  =============   ComboBox   ==============
													SAssignNew(DialogSection[i_Dlg].SpeechSection[i_Speech].ResponseSection[i_Response].CB_ResponseRepeat,
																																SComboBox<TSharedPtr<FString>>)
													.ContentPadding(GetPadding(4.0f, 0, 4.0f, 5.0f))
													.OptionsSource(&ResponseRepeatComboList)
													//.OnComboBoxOpening( this, &SDialogWindowWidget::OnSpekerComboBoxOpening, CurrentPropertyIndex)
													.OnGenerateWidget(this, &SDialogWindowWidget::HandleComboBoxGenerateWidget)
													.OnSelectionChanged(this, &SDialogWindowWidget::GetResponseRepeatComboList, CurrentPropertyIndex)
													//.InitiallySelectedItem(DialogSection[i_Dlg].SpeechSection[i_Speech].ReplicSection[i_Replic].RepSection[i_Rep].CurrentSpiker)
													[ 
														 
														SNew(STextBlock)
														.Margin(0)
														.Text(this, &SDialogWindowWidget::GetCurrentResponseRepeatLabel, CurrentPropertyIndex)
														.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 12 * SizeKoef))
														.ColorAndOpacity(FLinearColor(0.0f, 0.0f, 0.08f, 1))
													]//  ComboBox

												]
											]		
										]
										//   -------  RESPONSE  ImagePropertyZone     End  -------------
										+ SHorizontalBox::Slot()
										.Padding(GetPadding(0, 0, 5, 1))
										.HAlign(HAlign_Left)
										.VAlign(VAlign_Fill)
										.AutoWidth()
										[
											SNew(SBox)

											.Padding(0)
											.HAlign(HAlign_Fill)
											.VAlign(VAlign_Fill)
											.WidthOverride(4.f * SizeKoef)
											[
												SNew(SBorder)
												.Padding(0)
												//.HAlign(HAlign_Left)
												.HAlign(HAlign_Fill)
												.VAlign(VAlign_Fill)
												.BorderImage(PropertyResponseEnd)       //   -------  RESPONSE  ImagePropertyZone     End  -------------
											]
										]
									]
								]


								+ SHorizontalBox::Slot()
								
								.FillWidth(1)
								.HAlign(HAlign_Right)
								.VAlign(VAlign_Center)
								[
									SNew(SHorizontalBox)
								

									//  ==============================     PESPONSE--------LINK_TO_DIALOG_NAME-----PROPERTY   =======================
									+ SHorizontalBox::Slot()
									.Padding(GetPadding(2, 1, 4, 1))
									.AutoWidth()
									//.FillWidth(1)
									.HAlign(HAlign_Left)
									.VAlign(VAlign_Center)
									[
										SNew(SBox)
										.Padding(GetPadding(2, 3, 4, 3))
										//MaxDesiredWidth(FOptionalSize())
										.HAlign(HAlign_Left)
										.VAlign(VAlign_Center)
										//.WidthOverride(20.f)
										.HeightOverride(40.f * SizeKoef)         // -----------   Heigh TITLE-Zone  ------------
										[
										
											SNew(SHorizontalBox)

											//   -------   RESPONSE   ImagePropertyZone     Start  -------------
											+SHorizontalBox::Slot()
											.Padding(GetPadding(2, 0, 0, 1))
											.HAlign(HAlign_Left)
											.VAlign(VAlign_Fill)
											.AutoWidth()
											[
												SNew(SBox)
									
												.Padding(0)
												.HAlign(HAlign_Fill)
												.VAlign(VAlign_Fill)
												.WidthOverride(4.f * SizeKoef)
												[
													SNew(SBorder)
													.Padding(0)
													//.HAlign(HAlign_Left)
													.HAlign(HAlign_Fill)
													.VAlign(VAlign_Fill)
													.BorderImage(PropertyResponseStart)       //   -------   RESPONSE    ImagePropertyZone     Start  -------------
												]
											]

											//     -------   RESPONSE  Proprty       ------------- 
											+SHorizontalBox::Slot()
											.Padding(GetPadding(0, 0, 0, 1))
											.HAlign(HAlign_Left)
											.VAlign(VAlign_Center)
											.AutoWidth()
											[
												SNew(SBorder)
												.Padding(0)
												//.HAlign(HAlign_Left)
												.HAlign(HAlign_Fill)
												.VAlign(VAlign_Fill)
												.BorderImage(PropertyResponse)
												[

													SNew(SHorizontalBox)

													+ SHorizontalBox::Slot()
													.Padding(GetPadding(4, 1, 2, 1))
													.HAlign(HAlign_Left)
													.VAlign(VAlign_Center)
													.AutoWidth()
													[
														SNew(STextBlock)
														.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 12 * SizeKoef))
														//.ColorAndOpacity(FLinearColor(0.7f, 0.77f, 1.f, 1))
														.ColorAndOpacity(this, &SDialogWindowWidget::GetSectionTextColor, EProppertyToChange::DialogLink, CurrentPropertyIndex)
														.Text(FText::FromString("link dialog:"))
													]


													+ SHorizontalBox::Slot() 
													.Padding(GetPadding(7, 4, 4, 3))
													.HAlign(HAlign_Left)
													.VAlign(VAlign_Center)
													.AutoWidth()
													[										
														//]//  ComboBox
														SNew(SButton)
														.ContentPadding(0)
														.HAlign(HAlign_Left)
														.VAlign(VAlign_Center)
														.ButtonColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 0.f))    
														.OnClicked(this, &SDialogWindowWidget::OnHelperPanelClick, EProppertyToChange::DialogLink, CurrentPropertyIndex)
														[ 
															SNew(SOverlay)  

															+ SOverlay::Slot()           
															.HAlign(HAlign_Fill)
															.VAlign(VAlign_Center)
															//--.AutoWidth()
															[
																SNew(SBox)
																.Padding(GetPadding(0, 4, 0, 6))
																.HAlign(HAlign_Fill)
																.VAlign(VAlign_Fill)
																[
																	SNew(SImage)
																	.Image(ImageValueZone)      //       ImageValueZone
																]
															]

															+ SOverlay::Slot()
															.HAlign(HAlign_Center)
															.VAlign(VAlign_Center)
															[
																//  ===========================  RESPONSE        Link-Dialog      ================================
															
																SNew(STextBlock)
																.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 12 * SizeKoef))
																//.ColorAndOpacity(FLinearColor(0.7f, 0.77f, 1.f, 1))
																.ColorAndOpacity(this, &SDialogWindowWidget::GetSectionTextColor, EProppertyToChange::DialogLink, CurrentPropertyIndex)
																.Text(this, &SDialogWindowWidget::GetProppertyText, EProppertyToChange::DialogLink, CurrentPropertyIndex)

															]
														]
													]
												]		
											]
											//   -------  RESPONSE  ImagePropertyZone     End  -------------
											+ SHorizontalBox::Slot()
											.Padding(GetPadding(0, 0, 5, 1))
											.HAlign(HAlign_Left)
											.VAlign(VAlign_Fill)
											.AutoWidth()
											[
												SNew(SBox)

												.Padding(0)
												.HAlign(HAlign_Fill)
												.VAlign(VAlign_Fill)
												.WidthOverride(4.f * SizeKoef)
												[
													SNew(SBorder)
													.Padding(0)
													//.HAlign(HAlign_Left)
													.HAlign(HAlign_Fill)
													.VAlign(VAlign_Fill)
													.BorderImage(PropertyResponseEnd)       //   -------  RESPONSE  ImagePropertyZone     End  -------------
												]
											]
										]
									] //   DIALOG-LINK        (END)





									//  ==============================     PESPONSE--------LINK_TO_SPEECH_NAME-----PROPERTY   =======================
									+ SHorizontalBox::Slot()
									.Padding(GetPadding(2, 1, 4, 1))
									.AutoWidth()
									//.FillWidth(1)
									.HAlign(HAlign_Left)
									.VAlign(VAlign_Center)
									[
										SNew(SBox)
										.Padding(GetPadding(2, 3, 4, 3))
										//MaxDesiredWidth(FOptionalSize())
										.HAlign(HAlign_Left)
										.VAlign(VAlign_Center)
										//.WidthOverride(20.f)
										.HeightOverride(40.f * SizeKoef)         // -----------   Heigh TITLE-Zone  ------------
										[
										
											SNew(SHorizontalBox)

											//   -------   RESPONSE   ImagePropertyZone     Start  -------------
											+SHorizontalBox::Slot()
											.Padding(GetPadding(2, 0, 0, 1))
											.HAlign(HAlign_Left)
											.VAlign(VAlign_Fill)
											.AutoWidth()
											[
												SNew(SBox)
									
												.Padding(0)
												.HAlign(HAlign_Fill)
												.VAlign(VAlign_Fill)
												.WidthOverride(4.f * SizeKoef)
												[
													SNew(SBorder)
													.Padding(0)
													//.HAlign(HAlign_Left)
													.HAlign(HAlign_Fill)
													.VAlign(VAlign_Fill)
													.BorderImage(PropertyResponseStart)       //   -------   RESPONSE    ImagePropertyZone     Start  -------------
												]
											]

											//     -------   RESPONSE  Proprty       ------------- 
											+SHorizontalBox::Slot()
											.Padding(GetPadding(0, 0, 0, 1))
											.HAlign(HAlign_Left)
											.VAlign(VAlign_Center)
											.AutoWidth()
											[
												SNew(SBorder)
												.Padding(0)
												//.HAlign(HAlign_Left)
												.HAlign(HAlign_Fill)
												.VAlign(VAlign_Fill)
												.BorderImage(PropertyResponse)
												[

													SNew(SHorizontalBox)

													+ SHorizontalBox::Slot()
													.Padding(GetPadding(4, 1, 2, 1))
													.HAlign(HAlign_Left)
													.VAlign(VAlign_Center)
													.AutoWidth()
													[
														SNew(STextBlock)
														.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 12 * SizeKoef))
														//.ColorAndOpacity(FLinearColor(0.7f, 0.77f, 1.f, 1))
														.ColorAndOpacity(this, &SDialogWindowWidget::GetSectionTextColor, EProppertyToChange::SpeechLink, CurrentPropertyIndex)
														.Text(FText::FromString("link speech:"))
													]


													+ SHorizontalBox::Slot() 
													.Padding(GetPadding(7, 4, 4, 3))
													.HAlign(HAlign_Left)
													.VAlign(VAlign_Center)
													.AutoWidth()
													[
										
														//]//  ComboBox
														SNew(SButton)
														.ContentPadding(0)
														.HAlign(HAlign_Left)
														.VAlign(VAlign_Center)
														.ButtonColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 0.f))    
														.OnClicked(this, &SDialogWindowWidget::OnHelperPanelClick, EProppertyToChange::SpeechLink, CurrentPropertyIndex)
														[ 
															SNew(SOverlay)  

															+ SOverlay::Slot()           
															.HAlign(HAlign_Fill)
															.VAlign(VAlign_Center)
															//--.AutoWidth()
															[
																SNew(SBox)
																.Padding(GetPadding(0, 4, 0, 6))
																.HAlign(HAlign_Fill)
																.VAlign(VAlign_Fill)
																[
																	SNew(SImage)
																	.Image(ImageValueZone)      //       ImageValueZone
																]
															]

															+ SOverlay::Slot()
															.HAlign(HAlign_Center)
															.VAlign(VAlign_Center)
															[
																//  ===========================  RESPONSE     Speech  Link   ================================


																SNew(STextBlock)
																.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 12 * SizeKoef))
																.ColorAndOpacity(FLinearColor(0.7f, 0.77f, 1.f, 1))
																.ColorAndOpacity(this, &SDialogWindowWidget::GetSectionTextColor, EProppertyToChange::SpeechLink, CurrentPropertyIndex)
																.Text(this, &SDialogWindowWidget::GetProppertyText, EProppertyToChange::SpeechLink, CurrentPropertyIndex)
															]
														]
													]
												]		
											]
											//   -------  RESPONSE  ImagePropertyZone     End  -------------
											+ SHorizontalBox::Slot()
											.Padding(GetPadding(0, 0, 5, 1))
											.HAlign(HAlign_Left)
											.VAlign(VAlign_Fill)
											.AutoWidth()
											[
												SNew(SBox)

												.Padding(0)
												.HAlign(HAlign_Fill)
												.VAlign(VAlign_Fill)
												.WidthOverride(4.f * SizeKoef)
												[
													SNew(SBorder)
													.Padding(0)
													//.HAlign(HAlign_Left)
													.HAlign(HAlign_Fill)
													.VAlign(VAlign_Fill)
													.BorderImage(PropertyResponseEnd)       //   -------  RESPONSE  ImagePropertyZone     End  -------------
												]
											]
										]
									] //   SPEECH-LINK        (END)

									//  ==============================     PESPONSE--RETURN-PARAMETER--PROPERTY   =======================
									+ SHorizontalBox::Slot()
									.Padding(GetPadding(4, 1, 4, 1))
									.AutoWidth()
									//.FillWidth(1)
									.HAlign(HAlign_Left)
									.VAlign(VAlign_Center)
									[
										SNew(SBox)
										.Padding(GetPadding(4, 3, 4, 3))
										//MaxDesiredWidth(FOptionalSize())
										.HAlign(HAlign_Right)
										.VAlign(VAlign_Center)
										//.WidthOverride(20.f)
										.HeightOverride(ResponseSectionSize * SizeKoef) // -----------   Heigh TITLE-Zone  -----------
										[
										
											SNew(SHorizontalBox)

											//   -------   RESPONSE   ImagePropertyZone     Start  -------------
											+SHorizontalBox::Slot()
											.Padding(GetPadding(2, 0, 0, 1))
											.HAlign(HAlign_Right)
											.VAlign(VAlign_Fill)
											.AutoWidth()
											[
												SNew(SBox)
									
												.Padding(0)
												.HAlign(HAlign_Fill)
												.VAlign(VAlign_Fill)
												.WidthOverride(4.f * SizeKoef)
												[
													SNew(SBorder)
													.Padding(0)
													//.HAlign(HAlign_Left)
													.HAlign(HAlign_Fill)
													.VAlign(VAlign_Fill)
													.BorderImage(PropertyResponseStart)       //   -------   RESPONSE    ImagePropertyZone     Start  -------------
												]
											]

											//     -------   RESPONSE  Proprty  "Return type"     ------------- 
											+SHorizontalBox::Slot()
											.Padding(GetPadding(0, 0, 0, 1))
											.HAlign(HAlign_Right)
											.VAlign(VAlign_Center)
											.AutoWidth()
											[
												SNew(SBorder)
												.Padding(0)
												//.HAlign(HAlign_Left)
												.HAlign(HAlign_Fill)
												.VAlign(VAlign_Fill)
												.BorderImage(PropertyResponse)
												[

													SNew(SHorizontalBox)

													+ SHorizontalBox::Slot()
													.Padding(GetPadding(4, 1, 2, 1))
													.HAlign(HAlign_Left)
													.VAlign(VAlign_Center)
													.AutoWidth()
													[
														SNew(STextBlock)
														.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 12 * SizeKoef))
														//.ColorAndOpacity(FLinearColor(0.7f, 0.77f, 1.f, 1))
														.ColorAndOpacity(this, &SDialogWindowWidget::GetSectionTextColor, EProppertyToChange::repeatResponse, CurrentPropertyIndex)
														.Text(FText::FromString("Return type:"))
													]


													+ SHorizontalBox::Slot() 
													.Padding(GetPadding(7, 4, 4, 3))
													.HAlign(HAlign_Left)
													.VAlign(VAlign_Center)
													.AutoWidth()
													[
														//  ==========   ComboBox   ============
														SAssignNew(DialogSection[i_Dlg].SpeechSection[i_Speech].ResponseSection[i_Response].CB_ResponseReturnType,
																																	SComboBox<TSharedPtr<FString>>)
														.ContentPadding(GetPadding(4.0f, 0, 4.0f, 5.0f))
														.OptionsSource(&ResponseReturnTypeComboList)
														//.OnComboBoxOpening( this, &SDialogWindowWidget::OnSpekerComboBoxOpening, CurrentPropertyIndex)
														.OnGenerateWidget(this, &SDialogWindowWidget::HandleComboBoxGenerateWidget)
														.OnSelectionChanged(this, &SDialogWindowWidget::GetResponseReturnTypeComboList, CurrentPropertyIndex)
														//.InitiallySelectedItem(DialogSection[i_Dlg].SpeechSection[i_Speech].ReplicSection[i_Replic].RepSection[i_Rep].CurrentSpiker)
														[ 
														 
															SNew(STextBlock)
															.Margin(0)
															.Text(this, &SDialogWindowWidget::GetCurrentResponseReturnTypeLabel, CurrentPropertyIndex)
															.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 12 * SizeKoef))
															.ColorAndOpacity(FLinearColor(0.0f, 0.0f, 0.08f, 1))
														]//  ComboBox

													]
												]		
											]
											//   -------  RESPONSE  ImagePropertyZone     End  -------------
											+ SHorizontalBox::Slot()
											.Padding(GetPadding(0, 0, 5, 1))
											.HAlign(HAlign_Right)
											.VAlign(VAlign_Fill)
											.AutoWidth()
											[
												SNew(SBox)

												.Padding(0)
												.HAlign(HAlign_Fill)
												.VAlign(VAlign_Fill)
												.WidthOverride(4.f * SizeKoef)
												[
													SNew(SBorder)
													.Padding(0)
													//.HAlign(HAlign_Left)
													.HAlign(HAlign_Fill)
													.VAlign(VAlign_Fill)
													.BorderImage(PropertyResponseEnd)       //   -------  RESPONSE  ImagePropertyZone     End  -------------
												]
											]
										]
									] //   Combo-Box RETURN-PARRAMETER        (END)
								]


							]
						]
					//  ---------- Title-REPLICK    End  ----------------
						+SHorizontalBox::Slot()
						.Padding(GetPadding(0.f, 0.f, 2.f, 0.f))        // L, Up, R, Dn
						.HAlign(HAlign_Fill)
						.VAlign(VAlign_Fill)
						//+++++++++.VAlign(VAlign_Center)
						.AutoWidth()
						[
							SNew(SBox)
							//MaxDesiredWidth(FOptionalSize())
							.Padding(0)
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Fill)
							.WidthOverride(5.f * SizeKoef)
							//.HeightOverride(20.f)
							[
								SNew(SBorder)
								.Padding(0)
								.HAlign(HAlign_Fill)
								.VAlign(VAlign_Fill)
								.BorderImage(TitleResponseEnd)                  //   Title-REPLICK    End    //TitleDialogEnd    
							]
						]

						//  ============================   RESPONSE    Link-Marker      ============================

						+ SHorizontalBox::Slot()
						//.Padding(1.f, 0.f, 0.f, 0.f)        // L, Up, R, Dn
						.Padding(GetPadding(0.f, 5.f, 0.f, 0.f))
						.HAlign(HAlign_Left)
						.VAlign(VAlign_Top)
						//.FillWidth(1)
						.AutoWidth()
						[
							SNew(SButton)
							.ContentPadding(0)
							.HAlign(HAlign_Left)
							.VAlign(VAlign_Fill)
							.ButtonColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 0.f))
							.OnClicked(this, &SDialogWindowWidget::OnButtonMarkerLink, EProppertyToChange::MarkerResponse, CurrentPropertyIndex)
							[
								SNew(SBox)
								.Padding(0)
								.HAlign(HAlign_Left)
								.VAlign(VAlign_Fill)
								.HeightOverride((ResponseSectionSize * 0.45f) * SizeKoef)
								.WidthOverride((ResponseSectionSize * 0.4f) * SizeKoef)
								[
									SNew(SImage)
									.Image(MarkerLink)
								]
							]
						] //   RESPONSE    Link-Marker
					]


					//  ================   RESPONSE CONDITION:      (Dynamick Add)   ================
					+SVerticalBox::Slot()
					.Padding(GetPadding(100.f, 1.f, 67.f, 1.f))
					.AutoHeight()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Top)
					[
						SAssignNew(DialogSection[i_Dlg].SpeechSection[i_Speech].ResponseSection[i_Response].ResponseConditionBlock, SVerticalBox)
						//.Visibility(this, &SDialogWindowWidget::GetIsSectionCollapsed, EButtonDialogType::CollapsedReplicSection, i_Dlg, i_Speech, i_Replic, i_Rep)
						.Visibility(this, &SDialogWindowWidget::IsSectionCollapsed, EProppertyToChange::CollapsedResponse_Condition, CurrentPropertyIndex)

					]

					//  ================   RESPONSE VARIABLES:      (Dynamick Add)   ================
					+SVerticalBox::Slot()
					.Padding(GetPadding(100.f, 1.f, 67.f, 1.f))
					.AutoHeight()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Top)
					[
						///SNew(STextBlock)
						SAssignNew(DialogSection[i_Dlg].SpeechSection[i_Speech].ResponseSection[i_Response].VariableBlock, SVerticalBox)
						///.Visibility(this, &SDialogWindowWidget::GetIsSectionCollapsed, EButtonDialogType::CollapsedReplicSection, i_Dlg, i_Speech, i_Replic, i_Rep)
						.Visibility(this, &SDialogWindowWidget::IsSectionCollapsed, EProppertyToChange::CollapsedResponse_Variables, CurrentPropertyIndex)

					]
					 

					//  ================   RESPONSE CONTENT:         ================
					+ SVerticalBox::Slot()
					.Padding(GetPadding(60.f, 2.f, 10.f, 1.f))
					.AutoHeight()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					[
						SNew(SBox)

						.MaxDesiredHeight(ResponseMultiplyTextSize * SizeKoef)
						[
						//	SAssignNew(DialogSection[i_Dlg].SpeechSection[i_Speech].ReplicSection[i_Replic].ReplicComent_EditableMultiline, SMultiLineEditableTextBox) 	SMultiLineEditableTextBox)
							SNew(SMultiLineEditableTextBox)
							.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 12 * SizeKoef))
							.Text(FText::FromString(DialogSection[i_Dlg].SpeechSection[i_Speech].ResponseSection[i_Response].ComentText))
							.OnTextCommitted(this, &SDialogWindowWidget::ConfirmEditableMultilineTextBox, EProppertyToChange::responseComent, CurrentPropertyIndex)
							.OnTextChanged_Raw(this, &SDialogWindowWidget::OnEditableTextChange)  // void OnButtonT(const FText& Text);
						]
					]
				];


				//  =========================================================================================================
				//  =========================================================================================================
				//  ==============================               RESPONSE - CONDITION               ==============================
				//  =========================================================================================================
				//  =========================================================================================================


				for (int32 i_ResponseCondition = 0; i_ResponseCondition < DialogSection[i_Dlg].SpeechSection[i_Speech]
					.ResponseSection[i_Response].ResponseCondition.Num(); i_ResponseCondition++)
				{

					CurrentPropertyIndex.iSpeechCondition = -1;
					CurrentPropertyIndex.iReplic = -1;
					CurrentPropertyIndex.iReplicCondition = -1;
					CurrentPropertyIndex.iRep = -1;
					CurrentPropertyIndex.iRepCondition = -1;
					CurrentPropertyIndex.iResponseCondition = i_ResponseCondition;



					FVariablesParameter SpeechVariablesParameter;
					SpeechVariablesParameter.ConditionBlock = &DialogSection[CurrentPropertyIndex.iDialog]
						.SpeechSection[CurrentPropertyIndex.iSpeech]
						.ResponseSection[CurrentPropertyIndex.iResponse].ResponseConditionBlock;
					SpeechVariablesParameter.TextBoxCondition_Type = &DialogSection[CurrentPropertyIndex.iDialog]
						.SpeechSection[CurrentPropertyIndex.iSpeech]
						.ResponseSection[CurrentPropertyIndex.iResponse]
						.ResponseCondition[CurrentPropertyIndex.iResponseCondition].Condition_Type_Editable;
					SpeechVariablesParameter.TextBoxVariable_Name = &DialogSection[CurrentPropertyIndex.iDialog]
						.SpeechSection[CurrentPropertyIndex.iSpeech]
						.ResponseSection[CurrentPropertyIndex.iResponse]
						.ResponseCondition[CurrentPropertyIndex.iResponseCondition].ConditionVariable_Name_Editable;
					SpeechVariablesParameter.TextBoxVariable_Value = &DialogSection[CurrentPropertyIndex.iDialog]
						.SpeechSection[CurrentPropertyIndex.iSpeech]
						.ResponseSection[CurrentPropertyIndex.iResponse]
						.ResponseCondition[CurrentPropertyIndex.iResponseCondition].ConditionVariable_Value_Editable;
					SpeechVariablesParameter.Type_Text = &DialogSection[CurrentPropertyIndex.iDialog]
						.SpeechSection[CurrentPropertyIndex.iSpeech]
						.ResponseSection[CurrentPropertyIndex.iResponse]
						.ResponseCondition[CurrentPropertyIndex.iResponseCondition].ConditionType;
					SpeechVariablesParameter.VariableName_Text = &DialogSection[CurrentPropertyIndex.iDialog]
						.SpeechSection[CurrentPropertyIndex.iSpeech]
						.ResponseSection[CurrentPropertyIndex.iResponse]
						.ResponseCondition[CurrentPropertyIndex.iResponseCondition].VariableName;
					SpeechVariablesParameter.VariableValue_Text = &DialogSection[CurrentPropertyIndex.iDialog]
						.SpeechSection[CurrentPropertyIndex.iSpeech]
						.ResponseSection[CurrentPropertyIndex.iResponse]
						.ResponseCondition[CurrentPropertyIndex.iResponseCondition].VariableValue;
					SpeechVariablesParameter.AddButtonPropperty = EProppertyToChange::ButtonAddResponse_Condition;
					SpeechVariablesParameter.RemoveButtonPropperty = EProppertyToChange::RemoveResponse_Condition;
					SpeechVariablesParameter.ConditionTypePropperty = EProppertyToChange::Response_condition_type;
					SpeechVariablesParameter.CompareType = EProppertyToChange::Response_condition_CompareType;
					SpeechVariablesParameter.VarTypePropperty = EProppertyToChange::Response_condition_varType;
					SpeechVariablesParameter.VarNamePropperty = EProppertyToChange::Response_condition_varName;
					SpeechVariablesParameter.VarValuePropperty = EProppertyToChange::Response_condition_varValue;


					DrawConditionElement(CurrentPropertyIndex, SpeechVariablesParameter);





					////TSharedPtr<SVerticalBox>* RepConditionBlock = &DialogSection[i_Dlg].SpeechSection[i_Speech].ReplicSection[i_Replic].RepSection[i_Rep].RepConditionBlock;
					//TSharedPtr<SVerticalBox>* RepConditionBlock = &DialogSection[CurrentPropertyIndex.iDialog].SpeechSection[CurrentPropertyIndex.iSpeech]
					//							.ResponseSection[CurrentPropertyIndex.iResponse].ResponseConditionBlock;


					//TSharedPtr<SEditableTextBox>* TextBoxCondition_Type = &DialogSection[CurrentPropertyIndex.iDialog].SpeechSection[CurrentPropertyIndex.iSpeech]
					//							.ResponseSection[CurrentPropertyIndex.iResponse]
					//							.ResponseCondition[CurrentPropertyIndex.iResponseCondition].Condition_Type_Editable;
					//

					//TSharedPtr<SEditableTextBox>* TextBoxVariable_Name = &DialogSection[CurrentPropertyIndex.iDialog].SpeechSection[CurrentPropertyIndex.iSpeech]
					//							.ResponseSection[CurrentPropertyIndex.iResponse]
					//							.ResponseCondition[CurrentPropertyIndex.iResponseCondition].ConditionVariable_Name_Editable;


					//TSharedPtr<SEditableTextBox>* TextBoxVariable_Value = &DialogSection[CurrentPropertyIndex.iDialog].SpeechSection[CurrentPropertyIndex.iSpeech]
					//							.ResponseSection[CurrentPropertyIndex.iResponse]
					//							.ResponseCondition[CurrentPropertyIndex.iResponseCondition].ConditionVariable_Value_Editable;


					//FName* Type_Text = &DialogSection[CurrentPropertyIndex.iDialog].SpeechSection[CurrentPropertyIndex.iSpeech]
					//							.ResponseSection[CurrentPropertyIndex.iResponse]
					//							.ResponseCondition[CurrentPropertyIndex.iResponseCondition].ConditionType;


					//FName* VariableName_Text = &DialogSection[CurrentPropertyIndex.iDialog].SpeechSection[CurrentPropertyIndex.iSpeech]
					//							.ResponseSection[CurrentPropertyIndex.iResponse]
					//							.ResponseCondition[CurrentPropertyIndex.iResponseCondition].VariableName;

					//FName* VariableValue_Text = &DialogSection[CurrentPropertyIndex.iDialog].SpeechSection[CurrentPropertyIndex.iSpeech]
					//							.ResponseSection[CurrentPropertyIndex.iResponse]
					//							.ResponseCondition[CurrentPropertyIndex.iResponseCondition].VariableValue;

					//EProppertyToChange AddButtonPropperty = EProppertyToChange::ButtonAddResponse_Condition;   
					////EProppertyToChange MoveButtonPropperty = EProppertyToChange::MoveResponse_Condition;
					//EProppertyToChange RemoveButtonPropperty = EProppertyToChange::RemoveResponse_Condition;
					//EProppertyToChange ConditionTypePropperty = EProppertyToChange::Response_condition_type;  
					//EProppertyToChange CompareType = EProppertyToChange::Response_condition_CompareType;
					//EProppertyToChange VarTypePropperty = EProppertyToChange::Response_condition_varType;  
					//EProppertyToChange VarNamePropperty = EProppertyToChange::Response_condition_varName;
					//EProppertyToChange VarValuePropperty = EProppertyToChange::Response_condition_varValue;




					//DrawConditionElement(*RepConditionBlock,
					//						CurrentPropertyIndex,
					//						AddButtonPropperty,
					//						//MoveButtonPropperty,
					//						RemoveButtonPropperty,

					//						*TextBoxCondition_Type,
					//						*Type_Text,
					//						ConditionTypePropperty,
					//						//CompareType,
					//						*TextBoxVariable_Name,
					//						*VariableName_Text,
					//						VarNamePropperty,
					//						*TextBoxVariable_Value,
					//						*VariableValue_Text,
					//						VarValuePropperty,

					//						VarTypePropperty);
				}
				 

				//  =========================================================================================================
				//  =========================================================================================================
				//  ==============================             RESPONSE - Variables            ==============================
				//  =========================================================================================================
				//  =========================================================================================================

				for (int32 i_ResponseVariable = 0; i_ResponseVariable < DialogSection[i_Dlg].SpeechSection[i_Speech]
														.ResponseSection[i_Response].VariableSection.Num(); i_ResponseVariable++)
				{

					CurrentPropertyIndex.iSpeechCondition = -1;
					CurrentPropertyIndex.iReplic = -1;
					CurrentPropertyIndex.iReplicCondition = -1;
					CurrentPropertyIndex.iResponseCondition = -1;
					CurrentPropertyIndex.iRep = -1;
					CurrentPropertyIndex.iRepCondition = -1;
					CurrentPropertyIndex.iResponseVariable = i_ResponseVariable;

					DialogSection[i_Dlg].SpeechSection[i_Speech].ResponseSection[i_Response].VariableBlock->AddSlot()
					.Padding(GetPadding(200.f, 1.f, 40.f, 1.f))
					.HAlign(HAlign_Right)
					.VAlign(VAlign_Fill)
					//.AutoHeight()
					[
						SNew(SHorizontalBox)

						//    -------  Title-Condition    START   -------------
						+SHorizontalBox::Slot()
						.Padding(GetPadding(2.f, 1.f, 0.f, 1.f))        // L, Up, R, Dn
						.HAlign(HAlign_Right)
						.VAlign(VAlign_Fill)
						//+++++++++.VAlign(VAlign_Center)
						.AutoWidth()
						[
							SNew(SBox)
							//MaxDesiredWidth(FOptionalSize())
							.Padding(0)
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Fill)
							.WidthOverride(5.f * SizeKoef)
							//.HeightOverride(20.f)
							[
								SNew(SBorder)
								.Padding(0)
								.HAlign(HAlign_Fill)
								.VAlign(VAlign_Fill)
								.BorderImage(ConditionStart)                  //   Title-Condition    START
							]
						]
							
						
							//------------ALL CONDITION-title----------
						+ SHorizontalBox::Slot()
						.Padding(GetPadding(0.f, 1.f, 0.f, 1.f))        // L, Up, R, Dn
						.HAlign(HAlign_Fill)
						.VAlign(VAlign_Fill)
						.FillWidth(1)
						[ 
							SNew(SBox)
							.Padding(FMargin(0, 0, 0, 0))
							//MaxDesiredWidth(FOptionalSize())
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Fill)
							//.WidthOverride(20.f)
							.HeightOverride(RepsonseVariablesSectionSize)  //  Condition Panel "Height"  -----------   Heigh TITLE-Zone  ------------
							[
								//SNew(SButton)
								//  ==========================RESPONSE-VARIABLES     ALL CONDITION-title  ==============================
								SNew(SBorder)
								.HAlign(HAlign_Fill)
								.VAlign(VAlign_Fill)
								.BorderImage(Condition)
								[
							
									SNew(SHorizontalBox)


									// ---------------- Button      (Add_Down)      -------------------
									+ SHorizontalBox::Slot()
									.Padding(GetPadding(2.f, 1.f, 2.f, 1.f))        // L, Up, R, Dn
									.HAlign(HAlign_Fill)
									.VAlign(VAlign_Center)
									.AutoWidth()
									//.FillWidth(1)
									[
										SNew(SBox)
										.WidthOverride(20.f * SizeKoef)
										.MaxDesiredHeight(20.f * SizeKoef)
										//.HeightOverride(20.f)
										[
											SNew(SButton)
											.ContentPadding(0)
											.ButtonColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 0.f))
											.OnClicked(this, &SDialogWindowWidget::OnButtonClick, EProppertyToChange::ButtonAddResponse_Variable, CurrentPropertyIndex)  
											[
												SNew(SImage)
												.Image(ImageAddElement) 
											]						
										]

									]


									// ---------------- Button           (Remove) -------------------
									+ SHorizontalBox::Slot()
									.Padding(GetPadding(2.f, 1.f, 2.f, 1.f))        // L, Up, R, Dn
									.HAlign(HAlign_Fill)
									.VAlign(VAlign_Center)
									.AutoWidth()
									//.FillWidth(1)
									[
										SNew(SBox)
										.WidthOverride(20.f * SizeKoef)
										.MaxDesiredHeight(20.f)
										//.HeightOverride(20.f)
										[
											SNew(SButton)
											.ContentPadding(0)
											.ButtonColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 0.f))
											.OnClicked(this, &SDialogWindowWidget::OnButtonRemoveClick, EProppertyToChange::RemoveResponse_Variable, CurrentPropertyIndex)
											[
												SNew(SImage)
												.Image(ImageDeleteElement)
											]						
										]

									]

									// ---------------- Button          ( MOVE-Section)      -------------------
									+ SHorizontalBox::Slot()
									.Padding(GetPadding(2.f, 1.f, 2.f, 1.f))        // L, Up, R, Dn
									.HAlign(HAlign_Fill)
									.VAlign(VAlign_Center)
									.AutoWidth()
									//.FillWidth(1)
									[
										SNew(SBox)
										.WidthOverride(20.f * SizeKoef)
										.MaxDesiredHeight(20.f * SizeKoef)
										//.HeightOverride(20.f)
										[
											SNew(SButton)
											.ContentPadding(0)
											.ButtonColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 0.f))
											.OnClicked(this, &SDialogWindowWidget::OnHelperPanelClick, EProppertyToChange::MoveResponse_Variable, CurrentPropertyIndex)
											[
												SNew(SImage)
												.Image(ImageMoveElement)
											]						
										]

									]



									//     ======================= RESPONSE-VARIABLES       "VARIABLE-NAME"   +   "Local/Global"   =======================
									+ SHorizontalBox::Slot()
									[

										SNew(SHorizontalBox)


											//    -------  RESPONSE-VARIABLES   "VARIABLE-Value"  Start   -------------
										+SHorizontalBox::Slot()
										.Padding(GetPadding(2.f, 1.f, 0.f, 1.f))        // L, Up, R, Dn
										.HAlign(HAlign_Left)
										.VAlign(VAlign_Fill)
										//+++++++++.VAlign(VAlign_Center)
										.AutoWidth()
										[
											SNew(SBox)
											//MaxDesiredWidth(FOptionalSize())
											.Padding(0)
											.HAlign(HAlign_Fill)
											.VAlign(VAlign_Fill)
											.WidthOverride(4.f * SizeKoef)
											//.HeightOverride(20.f)
											[
												SNew(SBorder)
												.Padding(0)
												.HAlign(HAlign_Fill)
												.VAlign(VAlign_Fill)
												.BorderImage(PropertyResponseStart)                  //  image  Condition-Property   "Variable-Name"  Start
											]
										]

										+ SHorizontalBox::Slot()
										.Padding(GetPadding(0, 1, 0, 1))
										.HAlign(HAlign_Fill)
										.VAlign(VAlign_Fill)
										//.FillWidth(1)
										.AutoWidth()
										[

											SNew(SBorder)
											.Padding(FMargin(0, 0, 0, 0))
											.HAlign(HAlign_Fill)
											.VAlign(VAlign_Fill)
											.BorderImage(PropertyResponse)      //  image  Condition-Property   "Variable-Name"  
											[

												SNew(SHorizontalBox)

												+ SHorizontalBox::Slot()
												.Padding(GetPadding(2, 1, 2, 1))
												.HAlign(HAlign_Left)
												.VAlign(VAlign_Center)
												.AutoWidth()
												[		
														//  ------------------------RESPONSE-VARIABLES    VARIABLE- "Local/Global"    ---------------------------------
														SNew(SButton)
														.ContentPadding(0)
														.HAlign(HAlign_Fill)
														.VAlign(VAlign_Fill)
														.ButtonColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 0.3f))
														.OnClicked(this, &SDialogWindowWidget::OnButtonClick, EProppertyToChange::Response_variable_varType, CurrentPropertyIndex)  // VarTypePropperty // EProppertyToChange::rep_condition_varType
														[
															SNew(SHorizontalBox)

															+ SHorizontalBox::Slot()
															.Padding(GetPadding(3, 1, 3, 1))
															.HAlign(HAlign_Left)
															.VAlign(VAlign_Center)
															.AutoWidth()
															[
																SNew(STextBlock)
																.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 10 * SizeKoef))
																.ColorAndOpacity(FLinearColor(0.7f, 0.77f, 1.f, 1))
																//.ColorAndOpacity(FLinearColor(0.0f, 0.0f, 0.4f, 1))
																.Visibility(this, &SDialogWindowWidget::GetVisibility_LocalVarIndicator, EProppertyToChange::Response_variable_varType, CurrentPropertyIndex) // VarTypePropperty  // EProppertyToChange::rep_condition_varType
																.Text(FText::FromString("Local"))
															]

															+ SHorizontalBox::Slot()
															.Padding(GetPadding(3, 1, 3, 1))
															.HAlign(HAlign_Left)
															.VAlign(VAlign_Center)
															//	.AutoWidth()
															[
																SNew(STextBlock)
																.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 10 * SizeKoef))
																//.ColorAndOpacity(FLinearColor(0.0f, 0.0f, 0.4f, 1))
																.ColorAndOpacity(FLinearColor(0.7f, 0.77f, 1.f, 1))
																.Visibility(this, &SDialogWindowWidget::GetVisibility_GlobalVarIndicator, EProppertyToChange::Response_variable_varType, CurrentPropertyIndex) // VarTypePropperty // EProppertyToChange::rep_condition_varType
																.Text(FText::FromString("GLOBAL"))
															]
														]
													//]
												]


												//  --------------------------------RESPONSE-VARIABLES   Vatiable-Name  --------------------------------
												+ SHorizontalBox::Slot()
												.Padding(GetPadding(2, 1, 2, 1))
												.HAlign(HAlign_Left)
												.VAlign(VAlign_Center)
												.AutoWidth()
												[

													SNew(STextBlock)
													.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 10 * SizeKoef))
													//.ColorAndOpacity(FLinearColor(0.0f, 0.0f, 0.4f, 1))
													.ColorAndOpacity(FLinearColor(0.7f, 0.77f, 1.f, 1))
													.Text(FText::FromString("Var name:"))

												]
												//  -------------------------------- RESPONSE-VARIABLES  Vatiable-Name  (Button)--------------------------------
												+ SHorizontalBox::Slot()
												.Padding(GetPadding(2, 1, 2, 1))
												.HAlign(HAlign_Left)
												.VAlign(VAlign_Center)
												//777777777777.AutoWidth()
												[																			
													SNew(SButton)
													.ContentPadding(0)
													.HAlign(HAlign_Left)
													.VAlign(VAlign_Center)
													.ButtonColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 0.f))    
													.OnClicked(this, &SDialogWindowWidget::OnButtonClick, EProppertyToChange::Response_variable_varName, CurrentPropertyIndex)  //VarNamePropperty  //  EProppertyToChange::rep_condition_varName
													[ 
														SNew(SOverlay)  

														+ SOverlay::Slot()           
														.HAlign(HAlign_Fill)
														.VAlign(VAlign_Center)
														//--.AutoWidth()
														[
															SNew(SBox)
															.Padding(GetPadding(0, 4, 0, 6))
															.HAlign(HAlign_Fill)
															.VAlign(VAlign_Fill)
															[
																SNew(SImage)
																.Image(ImageValueZone)      //       ImageValueZone
															]
														]

														+ SOverlay::Slot()
														.HAlign(HAlign_Center)
														.VAlign(VAlign_Center)
														[
															//  ===========================RESPONSE-VARIABLES   Vatiable-Name StaticText  ================================
															SNew(SHorizontalBox)
														
															+ SHorizontalBox::Slot()
															.Padding(GetPadding(4, 0, 4, 1))
															//+++++.HAlign(HAlign_Fill)
															.HAlign(HAlign_Center)
															.VAlign(VAlign_Center)
															//.FillWidth(1)
															.AutoWidth()
															[
															     
																SNew(STextBlock)
																.Visibility(this, &SDialogWindowWidget::GetVisibilityOfSectionPropperty_Static, EProppertyToChange::Response_variable_varName, CurrentPropertyIndex)   //VarNamePropperty  //  EProppertyToChange::rep_condition_varName
																.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 12 * SizeKoef))
																.ColorAndOpacity(FLinearColor(0.7f, 0.77f, 1.f, 1))
																.Text(this, &SDialogWindowWidget::GetProppertyText, EProppertyToChange::Response_variable_varName, CurrentPropertyIndex)   //VarNamePropperty  //  EProppertyToChange::rep_condition_varName
															] 
													     
															+ SHorizontalBox::Slot()
															.HAlign(HAlign_Center)
															.VAlign(VAlign_Center)
															[
																SNew(SBox)
																.MinDesiredWidth(70.f * SizeKoef)
																.HAlign(HAlign_Fill)
																.VAlign(VAlign_Fill)                 
																[ 
																	//  ===========================   REsponse  Vatiable-Name EditableText  ================================
																	SAssignNew(DialogSection[i_Dlg].SpeechSection[i_Speech].ResponseSection[i_Response]
																							.VariableSection[i_ResponseVariable].ChangeVariable_Name_Editable, SEditableTextBox)
																	.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 12 * SizeKoef))
																	.Visibility(this, &SDialogWindowWidget::GetVisibilityOfSectionPropperty_Editable, EProppertyToChange::Response_variable_varName, CurrentPropertyIndex)   //VarNamePropperty  //  EProppertyToChange::rep_condition_varName
																	.Text(FText::FromString(DialogSection[i_Dlg].SpeechSection[i_Speech].ResponseSection[i_Response]
																								.VariableSection[i_ResponseVariable].VariableName.ToString()))
																	.OnTextCommitted(this, &SDialogWindowWidget::ConfirmEditableTextBox, EProppertyToChange::Response_variable_varName, CurrentPropertyIndex)  // PRES_ENTER:   void ConfirmEditableTextBox(const FText& Text, ETextCommit::Type TextType);
																	.OnTextChanged_Raw(this, &SDialogWindowWidget::OnEditableTextChange)  // void OnButtonT(const FText& Text);
																]
															]
														 
														]
													]
	
												]

											]
										]

										//    -------  RESPONSE-VARIABLES  "Variable-Name"  End   -------------
										+SHorizontalBox::Slot()
										.Padding(GetPadding(0.f, 1.f, 2.f, 1.f))        // L, Up, R, Dn
										.HAlign(HAlign_Left)
										.VAlign(VAlign_Fill)
										//+++++++++.VAlign(VAlign_Center)
										.AutoWidth()
										[
											SNew(SBox)
											//MaxDesiredWidth(FOptionalSize())
											.Padding(0)
											.HAlign(HAlign_Fill)
											.VAlign(VAlign_Fill)
											.WidthOverride(4.f * SizeKoef)
											//.HeightOverride(20.f)
											[
												SNew(SBorder)
												.Padding(0)
												.HAlign(HAlign_Fill)
												.VAlign(VAlign_Fill)
												.BorderImage(PropertyResponseEnd)                  //  image  Condition-Property   "Variable-Name"  End
											]
										]
											
									]

									//     =======================RESPONSE-VARIABLES    "VARIABLE-Value"    =======================
									+ SHorizontalBox::Slot()
									.HAlign(HAlign_Right)
									.VAlign(VAlign_Fill)
									[

										SNew(SHorizontalBox)


											//    -------  Condition-Property   "VARIABLE-Value"  Start   -------------
										+SHorizontalBox::Slot()
										.Padding(GetPadding(2.f, 1.f, 0.f, 1.f))        // L, Up, R, Dn
										.HAlign(HAlign_Right)
										.VAlign(VAlign_Fill)
										//+++++++++.VAlign(VAlign_Center)
										.AutoWidth()
										[
											SNew(SBox)
											//MaxDesiredWidth(FOptionalSize())
											.Padding(0)
											.HAlign(HAlign_Fill)
											.VAlign(VAlign_Fill)
											.WidthOverride(4.f * SizeKoef)
											//.HeightOverride(20.f)
											[
												SNew(SBorder)
												.Padding(0)
												.HAlign(HAlign_Fill)
												.VAlign(VAlign_Fill)
												.BorderImage(PropertyResponseStart)                  //  image  Condition-Property   "Variable-Value"  Start
											]
										]

										+ SHorizontalBox::Slot()
										.Padding(GetPadding(0, 1, 0, 1))
										.HAlign(HAlign_Right)
										.VAlign(VAlign_Fill)
										//.FillWidth(1)
										.AutoWidth()
										[

											SNew(SBorder)
											.Padding(GetPadding(0, 0, 0, 0))
											.HAlign(HAlign_Fill)
											.VAlign(VAlign_Fill)
											.BorderImage(PropertyResponse)      //  image  Condition-Property   "Variable-Value"  
											[

												SNew(SHorizontalBox)

												//  -------------------------------RESPONSE-VARIABLES-   Vatiable-Value  --------------------------------
												+ SHorizontalBox::Slot()
												.Padding(GetPadding(2, 1, 2, 1))
												.HAlign(HAlign_Left)
												.VAlign(VAlign_Center)
												.AutoWidth()
												[

													SNew(STextBlock)
													.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 10 * SizeKoef))
													//.ColorAndOpacity(FLinearColor(0.0f, 0.0f, 0.4f, 1))
													.ColorAndOpacity(FLinearColor(0.7f, 0.77f, 1.f, 1))
													.Text(FText::FromString("Var value:"))

												]
												//  --------------------------------RESPONSE-VARIABLES   Vatiable-Value  (Button)--------------------------------
												+ SHorizontalBox::Slot()
												.Padding(GetPadding(2, 1, 2, 1))
												.HAlign(HAlign_Left)
												.VAlign(VAlign_Center)
												//777777777777.AutoWidth()
												[																			
													SNew(SButton) 
													.ContentPadding(0)
													.HAlign(HAlign_Left)
													.VAlign(VAlign_Center)
													.ButtonColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 0.f))    
													.OnClicked(this, &SDialogWindowWidget::OnButtonClick, EProppertyToChange::Response_variable_varValue, CurrentPropertyIndex)  // VarValuePropperty  // EProppertyToChange::rep_condition_varValue
													[ 
														SNew(SOverlay)  

														+ SOverlay::Slot()           
														.HAlign(HAlign_Fill)
														.VAlign(VAlign_Center)
														//--.AutoWidth()
														[
															SNew(SBox)
															.Padding(GetPadding(0, 4, 0, 6))
															.HAlign(HAlign_Fill)
															.VAlign(VAlign_Fill)
															[
																SNew(SImage)
																.Image(ImageValueZone)      //       ImageValueZone
															]
														]

														+ SOverlay::Slot()
														.HAlign(HAlign_Center)
														.VAlign(VAlign_Center)
														[
															//  =========================== RESPONSE-VARIABLES   Vatiable-Value StaticText  ================================
															SNew(SHorizontalBox)
														
															+ SHorizontalBox::Slot()
															.Padding(GetPadding(4, 0, 4, 1))
															//+++++.HAlign(HAlign_Fill)
															.HAlign(HAlign_Center)
															.VAlign(VAlign_Center)
															//.FillWidth(1)
															.AutoWidth()
															[
															     
																SNew(STextBlock)
																.Visibility(this, &SDialogWindowWidget::GetVisibilityOfSectionPropperty_Static, EProppertyToChange::Response_variable_varValue, CurrentPropertyIndex)  // VarValuePropperty  // EProppertyToChange::rep_condition_varValue
																.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 12 * SizeKoef))
																.ColorAndOpacity(FLinearColor(0.7f, 0.77f, 1.f, 1))
																.Text(this, &SDialogWindowWidget::GetProppertyText, EProppertyToChange::Response_variable_varValue, CurrentPropertyIndex)  // VarValuePropperty  // EProppertyToChange::rep_condition_varValue
															] 
													     
															+ SHorizontalBox::Slot()
															.HAlign(HAlign_Center)
															.VAlign(VAlign_Center)
															[
																SNew(SBox)
																.MinDesiredWidth(70.f * SizeKoef)
																.HAlign(HAlign_Fill)
																.VAlign(VAlign_Fill)                 
																[ 
																	//  ===========================    Variable-Value EditableText  ================================
																	SAssignNew(DialogSection[i_Dlg].SpeechSection[i_Speech].ResponseSection[i_Response]
																			.VariableSection[i_ResponseVariable].ChangeVariable_Value_Editable, SEditableTextBox)
																	.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 12 * SizeKoef))
																	.Visibility(this, &SDialogWindowWidget::GetVisibilityOfSectionPropperty_Editable, EProppertyToChange::Response_variable_varValue, CurrentPropertyIndex)  // VarValuePropperty  // EProppertyToChange::rep_condition_varValue
																	.Text(FText::FromString(DialogSection[i_Dlg].SpeechSection[i_Speech].ResponseSection[i_Response]
																									.VariableSection[i_ResponseVariable].VariableValue.ToString()))
																	.OnTextCommitted(this, &SDialogWindowWidget::ConfirmEditableTextBox, EProppertyToChange::Response_variable_varValue, CurrentPropertyIndex)  // PRES_ENTER:   void ConfirmEditableTextBox(const FText& Text, ETextCommit::Type TextType);
																	.OnTextChanged_Raw(this, &SDialogWindowWidget::OnEditableTextChange)  // void OnButtonT(const FText& Text);
																]
															]
														 
														]
													]
	
												]

											]
										]
											
										//    -------  Condition-Property   "Variable-Value"  End   -------------
										+SHorizontalBox::Slot()
										.Padding(GetPadding(0.f, 1.f, 2.f, 1.f))        // L, Up, R, Dn
										.HAlign(HAlign_Right)
										.VAlign(VAlign_Fill)
										//+++++++++.VAlign(VAlign_Center)
										.AutoWidth()
										[
											SNew(SBox)
											//MaxDesiredWidth(FOptionalSize())
											.Padding(0)
											.HAlign(HAlign_Fill)
											.VAlign(VAlign_Fill)
											.WidthOverride(4.f * SizeKoef)
											//.HeightOverride(20.f)
											[
												SNew(SBorder)
												.Padding(0)
												.HAlign(HAlign_Fill)
												.VAlign(VAlign_Fill)
												.BorderImage(PropertyResponseEnd)          //  image  Condition-Property   "Variable-Value"  End
											]
										]
											
									]

								] // Border Title
							]
								
						]

						//    -------  Title-Condition    End   -------------
						+SHorizontalBox::Slot()
						.Padding(GetPadding(0.f, 1.f, 2.f, 1.f))        // L, Up, R, Dn
						.HAlign(HAlign_Fill)
						.VAlign(VAlign_Fill)
						//+++++++++.VAlign(VAlign_Center)
						.AutoWidth()
						[
							SNew(SBox)
							//MaxDesiredWidth(FOptionalSize())
							.Padding(0)
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Fill)
							.WidthOverride(5.f * SizeKoef)
							//.HeightOverride(20.f)
							[
								SNew(SBorder)
								.Padding(0)
								.HAlign(HAlign_Fill)
								.VAlign(VAlign_Fill)
								.BorderImage(ConditionEnd)                  //   Title-variable    End
							]
						]
					];
				} //   Response Variables Block
			}  //   Response 
		}  // i_Speech
	}  //i_Dlg

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXx
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXx
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXx
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXx
//XXXXXXXXXXXXXXXXXXXX  INDICATOR   ???????????????????????
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXx
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXx
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXx

	RedrawIndicator();


}   




/*void SDialogWindowWidget::DrawConditionElement(TSharedPtr<SVerticalBox> &ConditionBlock,
												FPropertyIndex& CurrentPropertyIndex,+
												EProppertyToChange AddButtonPropperty,+
												//EProppertyToChange MoweButtonPropperty,
												EProppertyToChange RemoveButtonPropperty,+

												TSharedPtr<SEditableTextBox>& TextBoxCondition_Type,+
												FName& Type_Text,+
												EProppertyToChange ConditionTypePropperty,+
												//EProppertyToChange CompareType,  +

												TSharedPtr<SEditableTextBox> *TextBoxVariable_Name,+

												FName& VariableName_Text,+
												EProppertyToChange VarNamePropperty,+
												TSharedPtr<SEditableTextBox>& TextBoxVariable_Value,+
												FName& VariableValue_Text,+
												EProppertyToChange VarValuePropperty,+

												EProppertyToChange VarTypePropperty+)*/
void SDialogWindowWidget::DrawConditionElement(FPropertyIndex& CurrentPropertyIndex, FVariablesParameter& VarParam)
{

	(*VarParam.ConditionBlock)->AddSlot()
	.Padding(GetPadding(150.f, 0.f, 40.f, 0.f))
	.HAlign(HAlign_Right)
	.VAlign(VAlign_Fill)
	//.AutoHeight()
	[
		SNew(SHorizontalBox)

		//    -------  Title-Condition    START   -------------
		+SHorizontalBox::Slot()
		.Padding(GetPadding(2.f, 1.f, 0.f, 1.f))        // L, Up, R, Dn
		.HAlign(HAlign_Right)
		.VAlign(VAlign_Fill)
		//+++++++++.VAlign(VAlign_Center)
		.AutoWidth()
		[
			SNew(SBox)
			//MaxDesiredWidth(FOptionalSize())
			.Padding(0)
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.WidthOverride(5.f * SizeKoef)
			//.HeightOverride(20.f)
			[
				SNew(SBorder)
				.Padding(0)
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.BorderImage(ConditionStart)                  //   Title-Condition    START
			]
		]

			//------------ALL CONDITION-title----------
		+ SHorizontalBox::Slot()
		.Padding(GetPadding(0.f, 1.f, 0.f, 1.f))        // L, Up, R, Dn
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.FillWidth(1)
		[ 
			SNew(SBox)
			.Padding(FMargin(0, 0, 0, 0))
			//MaxDesiredWidth(FOptionalSize())
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			//.WidthOverride(20.f)
			.HeightOverride(ConditionSectionSize * SizeKoef)  //     Condition Panel "Height"  -----------   Heigh TITLE-Zone  ------------
			[


				//SNew(SButton)
				//  ==========================  ALL CONDITION-title  ==============================
				SNew(SBorder)
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.BorderImage(Condition)
				[
							
					SNew(SHorizontalBox)

					// ---------------- Button      (Add_Down)      -------------------
					+ SHorizontalBox::Slot()
					.Padding(GetPadding(2.f, 1.f, 2.f, 1.f))        // L, Up, R, Dn
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Center)
					.AutoWidth()
					//.FillWidth(1)
					[
						SNew(SBox)
						.WidthOverride(20.f * SizeKoef)
						.MaxDesiredHeight(20.f * SizeKoef)
						//.HeightOverride(20.f)
						[
							SNew(SButton)
							.ContentPadding(0)
							.ButtonColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 0.f))
							.OnClicked(this, &SDialogWindowWidget::OnButtonClick, VarParam.AddButtonPropperty, CurrentPropertyIndex)
							[
								SNew(SImage)
								.Image(ImageAddElement) 
							]						
						]

					]


					// ---------------- Button           (Remove) -------------------
					+ SHorizontalBox::Slot()
					.Padding(GetPadding(2.f, 1.f, 2.f, 1.f))        // L, Up, R, Dn
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Center)
					.AutoWidth()
					//.FillWidth(1)
					[
						SNew(SBox)
						.WidthOverride(20.f * SizeKoef)
						.MaxDesiredHeight(20.f * SizeKoef)
						//.HeightOverride(20.f)
						[
							SNew(SButton)
							.ContentPadding(0)
							.ButtonColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 0.f))
							.OnClicked(this, &SDialogWindowWidget::OnButtonRemoveClick, VarParam.RemoveButtonPropperty, CurrentPropertyIndex)
							[
								SNew(SImage)
								.Image(ImageDeleteElement)
							]						
						]

					]

					// ---------------- Button          ( MOVE-Section)      -------------------
					+ SHorizontalBox::Slot()
					.Padding(GetPadding(2.f, 1.f, 2.f, 1.f))        // L, Up, R, Dn
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Center)
					.AutoWidth()
					//.FillWidth(1)
					[
						SNew(SBox)
						.WidthOverride(20.f * SizeKoef)
						.MaxDesiredHeight(20.f * SizeKoef)
						//.HeightOverride(20.f)
						[
							SNew(SButton)
							.ContentPadding(0)
							.ButtonColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 0.f))
							.OnClicked(this, &SDialogWindowWidget::OnHelperPanelClick, EProppertyToChange::Move_Condition, CurrentPropertyIndex)
							///////////.OnClicked(this, &SDialogWindowWidget::OnButtonClick, EProppertyToChange::XXXXXXXXXXXXXXXXXXXXXXXXXXXxxx, CurrentPropertyIndex)  
							[
								SNew(SImage)
								.Image(ImageMoveElement)
							]						
						]

					]

					//     =======================     CONDITION-Propprty       "TYPE"    =======================

						//    -------  Condition-Property   "Type"  START   -------------
					+SHorizontalBox::Slot()
					.Padding(GetPadding(2.f, 1.f, 0.f, 1.f))        // L, Up, R, Dn
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					//+++++++++.VAlign(VAlign_Center)
					.AutoWidth()
					[
						SNew(SBox)
						//MaxDesiredWidth(FOptionalSize())
						.Padding(0)
						.HAlign(HAlign_Fill)
						.VAlign(VAlign_Fill)
						.WidthOverride(4.f * SizeKoef)
						//.HeightOverride(20.f)
						[
							SNew(SBorder)
							.Padding(0)
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Fill)
							.BorderImage(PropertyResponseStart)                  //  image  Condition-Property   "Type"  START
						]
					]

					+ SHorizontalBox::Slot()
					.Padding(GetPadding(0, 2, 0, 2))
					.HAlign(HAlign_Left)
					.VAlign(VAlign_Fill)
					.AutoWidth()
					[
						SNew(SBorder)
						.Padding(GetPadding(2, 0, 0, 0))
						.HAlign(HAlign_Left)
						.VAlign(VAlign_Fill)
						.BorderImage(PropertyResponse)      //  image  Condition-Property   "Type"  
						[
							SNew(SHorizontalBox)

							+ SHorizontalBox::Slot()
							.Padding(GetPadding(0, 3, 0, 3))
							.HAlign(HAlign_Left)
							.VAlign(VAlign_Center)
							.AutoWidth()
							[
								SNew(STextBlock)
								.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 9 * SizeKoef))
								.ColorAndOpacity(FLinearColor(0.7f, 0.77f, 1.f, 1))
								.Text(FText::FromString("TYPE: "))
							]

							+ SHorizontalBox::Slot()
							.Padding(GetPadding(2, 1, 2, 1))
							.HAlign(HAlign_Center)
							.VAlign(VAlign_Center)
							//	.AutoWidth()
							[
														
								SNew(SButton)
								.ContentPadding(0)
								.HAlign(HAlign_Fill)
								.VAlign(VAlign_Fill)
								.ButtonColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 0.f))    
								.OnClicked(this, &SDialogWindowWidget::OnButtonClick, VarParam.ConditionTypePropperty, CurrentPropertyIndex)    //ConditionTypePropperty  //EProppertyToChange::rep_condition_type
								[
									SNew(SOverlay)  

									+ SOverlay::Slot()
									.Padding(GetPadding(3, 1, 6, 1))
									.HAlign(HAlign_Fill)
									.VAlign(VAlign_Center)
									[

										SNew(SHorizontalBox)
														
										+ SHorizontalBox::Slot()
										//+++++.HAlign(HAlign_Fill)
										.HAlign(HAlign_Center)
										.VAlign(VAlign_Center)
										.AutoWidth()
										[

											// XXXXXXXXXXXXXXXXXXXXXXXXXXXX      7777777777777777777      XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
											// XXXXXXXXXXXXX                     ERROR  TEXT_WIDTH_SIZE                      XXXXXXXXXXX
											// XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

											SNew(STextBlock)
											//.MinDesiredWidth(10.0f)
											.Visibility(this, &SDialogWindowWidget::GetVisibilityOfSectionPropperty_Static, VarParam.ConditionTypePropperty, CurrentPropertyIndex)  // ConditionTypePropperty  // EProppertyToChange::rep_condition_type
											.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 9 * SizeKoef))
											.ColorAndOpacity(FLinearColor(0.7f, 0.77f, 1.f, 1))
											.Text(this, &SDialogWindowWidget::GetProppertyText, VarParam.ConditionTypePropperty, CurrentPropertyIndex)  //ConditionTypePropperty // EProppertyToChange::rep_condition_type
										]
													    
										+ SHorizontalBox::Slot()
										.Padding(GetPadding(1, 0, 1, 0))
										.HAlign(HAlign_Center)
										.VAlign(VAlign_Center)
										[
											SNew(SBox)
											.MinDesiredWidth(30.f * SizeKoef)
											.HAlign(HAlign_Center)
											.VAlign(VAlign_Center)
											[ 
												//  ===========================  CONDITION-Propprty    EditableText  ================================
												SAssignNew((*VarParam.TextBoxCondition_Type), SEditableTextBox)
												//.BackgroundColor(FLinearColor((0.5f, 0.5f, 0.5f, 1.f))
												.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 9 * SizeKoef))
												.Visibility(this, &SDialogWindowWidget::GetVisibilityOfSectionPropperty_Editable, VarParam.ConditionTypePropperty, CurrentPropertyIndex)  // ConditionTypePropperty  // EProppertyToChange::rep_condition_type
												.Text(FText::FromString((*VarParam.Type_Text).ToString()))
																	
												.OnTextCommitted(this, &SDialogWindowWidget::ConfirmEditableTextBox, VarParam.ConditionTypePropperty, CurrentPropertyIndex)  // PRES_ENTER:   void ConfirmEditableTextBox(const FText& Text, ETextCommit::Type TextType);
												.OnTextChanged_Raw(this, &SDialogWindowWidget::OnEditableTextChange)  // void OnButtonT(const FText& Text);
											]
										]
														 
									]
								]
							]
						]
					]
						//    -------  CONDITION   "Type"  End   -------------
					+SHorizontalBox::Slot()
					.Padding(GetPadding(0.f, 1.f, 2.f, 1.f))        // L, Up, R, Dn
					.HAlign(HAlign_Left)
					.VAlign(VAlign_Fill)
					//+++++++++.VAlign(VAlign_Center)
					.AutoWidth()
					[
						SNew(SBox)
						//MaxDesiredWidth(FOptionalSize())
						.Padding(0)
						.HAlign(HAlign_Fill)
						.VAlign(VAlign_Fill)
						.WidthOverride(4.f * SizeKoef)
						//.HeightOverride(20.f)
						[
							SNew(SBorder)
							.Padding(0)
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Fill)
							.BorderImage(PropertyResponseEnd)                  //  image  Condition-Property   "Type"  End
						]
					]
									 



					//     =======================   CONDITION     "VARIABLE-NAME"   +   "Local/Global"   =======================
					+ SHorizontalBox::Slot()
					[

						SNew(SHorizontalBox)


							//    -------  CONDITION   "VARIABLE-Value"  Start   -------------
						+SHorizontalBox::Slot()
						.Padding(GetPadding(2.f, 1.f, 0.f, 1.f))        // L, Up, R, Dn
						.HAlign(HAlign_Left)
						.VAlign(VAlign_Fill)
						//+++++++++.VAlign(VAlign_Center)
						.AutoWidth()
						[
							SNew(SBox)
							//MaxDesiredWidth(FOptionalSize())
							.Padding(0)
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Fill)
							.WidthOverride(4.f * SizeKoef)
							//.HeightOverride(20.f)
							[
								SNew(SBorder)
								.Padding(0)
								.HAlign(HAlign_Fill)
								.VAlign(VAlign_Fill)
								.BorderImage(PropertyResponseStart)                  //  image  Condition-Property   "Variable-Name"  Start
							]
						]

						+ SHorizontalBox::Slot()
						.Padding(GetPadding(0, 1, 0, 1))
						.HAlign(HAlign_Fill)
						.VAlign(VAlign_Fill)
						//.FillWidth(1)
						.AutoWidth()
						[

							SNew(SBorder)
							.Padding(GetPadding(0, 0, 0, 0))
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Fill)
							.BorderImage(PropertyResponse)      //  image  Condition-Property   "Variable-Name"  
							[

								SNew(SHorizontalBox)

								+ SHorizontalBox::Slot()
								.Padding(GetPadding(2, 1, 2, 1))
								.HAlign(HAlign_Left)
								.VAlign(VAlign_Center)
								.AutoWidth()
								[		
										//  ------------------------ CONDITION   VARIABLE- "Local/Global"    ---------------------------------
									//SNew(SBox)
									//.MinDesiredWidth(60.f)
									//.HAlign(HAlign_Fill)
									//.VAlign(VAlign_Fill)
									//[
										SNew(SButton)
										.ContentPadding(0)
										.HAlign(HAlign_Fill)
										.VAlign(VAlign_Fill)
										.ButtonColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 0.3f))
										.OnClicked(this, &SDialogWindowWidget::OnButtonClick, VarParam.VarTypePropperty, CurrentPropertyIndex)  // VarTypePropperty // EProppertyToChange::rep_condition_varType
										[
											SNew(SHorizontalBox)

											+ SHorizontalBox::Slot()
											.Padding(GetPadding(3, 1, 3, 1))
											.HAlign(HAlign_Left)
											.VAlign(VAlign_Center)
											.AutoWidth()
											[
												SNew(STextBlock)
												.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 10 * SizeKoef))
												.ColorAndOpacity(FLinearColor(0.7f, 0.77f, 1.f, 1))
												//.ColorAndOpacity(FLinearColor(0.0f, 0.0f, 0.4f, 1))
												.Visibility(this, &SDialogWindowWidget::GetVisibility_LocalVarIndicator, VarParam.VarTypePropperty, CurrentPropertyIndex) // VarTypePropperty  // EProppertyToChange::rep_condition_varType
												.Text(FText::FromString("Local"))
											]

											+ SHorizontalBox::Slot()
											.Padding(GetPadding(3, 1, 3, 1))
											.HAlign(HAlign_Left)
											.VAlign(VAlign_Center)
											//	.AutoWidth()
											[
												SNew(STextBlock)
												.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 10 * SizeKoef))
												//.ColorAndOpacity(FLinearColor(0.0f, 0.0f, 0.4f, 1))
												.ColorAndOpacity(FLinearColor(0.7f, 0.77f, 1.f, 1))
												.Visibility(this, &SDialogWindowWidget::GetVisibility_GlobalVarIndicator, VarParam.VarTypePropperty, CurrentPropertyIndex) // VarTypePropperty // EProppertyToChange::rep_condition_varType
												.Text(FText::FromString("GLOBAL"))
											]
										]
									//]
								]


								//  -------------------------------- CONDITION  Vatiable-Name  --------------------------------
								+ SHorizontalBox::Slot()
								.Padding(GetPadding(2, 1, 2, 1))
								.HAlign(HAlign_Left)
								.VAlign(VAlign_Center)
								.AutoWidth()
								[

									SNew(STextBlock)
									.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 10 * SizeKoef))
									//.ColorAndOpacity(FLinearColor(0.0f, 0.0f, 0.4f, 1))
									.ColorAndOpacity(FLinearColor(0.7f, 0.77f, 1.f, 1))
									.Text(FText::FromString("Var name:"))

								]
								//  -------------------------------- CONDITION  Vatiable-Name  (Button)--------------------------------
								+ SHorizontalBox::Slot()
								.Padding(GetPadding(2, 1, 2, 1))
								.HAlign(HAlign_Left)
								.VAlign(VAlign_Center)
								//777777777777.AutoWidth()
								[																			
									SNew(SButton)
									.ContentPadding(0)
									.HAlign(HAlign_Left)
									.VAlign(VAlign_Center)
									.ButtonColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 0.f))    
									.OnClicked(this, &SDialogWindowWidget::OnButtonClick, VarParam.VarNamePropperty, CurrentPropertyIndex)  //VarNamePropperty  //  EProppertyToChange::rep_condition_varName
									[ 
										SNew(SOverlay)  

										+ SOverlay::Slot()           
										.HAlign(HAlign_Fill)
										.VAlign(VAlign_Center)
										//--.AutoWidth()
										[
											SNew(SBox)
											.Padding(GetPadding(0, 4, 0, 6))
											.HAlign(HAlign_Fill)
											.VAlign(VAlign_Fill)
											[
												SNew(SImage)
												.Image(ImageValueZone)      //       ImageValueZone
											]
										]

										+ SOverlay::Slot()
										.HAlign(HAlign_Center)
										.VAlign(VAlign_Center)
										[
											//  =========================== CONDITION  Vatiable-Name StaticText  ================================
											SNew(SHorizontalBox)
														
											+ SHorizontalBox::Slot()
											.Padding(GetPadding(4, 0, 4, 1))
											//+++++.HAlign(HAlign_Fill)
											.HAlign(HAlign_Center)
											.VAlign(VAlign_Center)
											//.FillWidth(1)
											.AutoWidth()
											[
												SNew(SBox)
												.MinDesiredWidth(70.f * SizeKoef)
												.MaxDesiredWidth(300.f * SizeKoef)
												.HAlign(HAlign_Center)
												.VAlign(VAlign_Center)
												[
													SNew(STextBlock)
													.Visibility(this, &SDialogWindowWidget::GetVisibilityOfSectionPropperty_Static, VarParam.VarNamePropperty, CurrentPropertyIndex)   //VarNamePropperty  //  EProppertyToChange::rep_condition_varName
													.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 12 * SizeKoef))
													.ColorAndOpacity(FLinearColor(0.7f, 0.77f, 1.f, 1))
													.Text(this, &SDialogWindowWidget::GetProppertyText, VarParam.VarNamePropperty, CurrentPropertyIndex)   //VarNamePropperty  //  EProppertyToChange::rep_condition_varName
												]
											] 
													     
											+ SHorizontalBox::Slot()
											.HAlign(HAlign_Center)
											.VAlign(VAlign_Center)
											[
												SNew(SBox)
												.MinDesiredWidth(70.f * SizeKoef)
												.MaxDesiredWidth(300.f * SizeKoef)
												.HAlign(HAlign_Center)
												.VAlign(VAlign_Center)
												[ 
													//  ===========================   CONDITION  Vatiable-Name EditableText  ================================
													SAssignNew((*VarParam.TextBoxVariable_Name), SEditableTextBox)
													.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 12 * SizeKoef))
													.Visibility(this, &SDialogWindowWidget::GetVisibilityOfSectionPropperty_Editable, VarParam.VarNamePropperty, CurrentPropertyIndex)   //VarNamePropperty  //  EProppertyToChange::rep_condition_varName
													.Text(FText::FromString((*VarParam.VariableName_Text).ToString()))
													.OnTextCommitted(this, &SDialogWindowWidget::ConfirmEditableTextBox, VarParam.VarNamePropperty, CurrentPropertyIndex)  // PRES_ENTER:   void ConfirmEditableTextBox(const FText& Text, ETextCommit::Type TextType);
													.OnTextChanged_Raw(this, &SDialogWindowWidget::OnEditableTextChange)  // void OnButtonT(const FText& Text);
												]
											]
														 
										]
									]
	
								]

							]
						]

						//    -------  CONDITION   "Variable-Name"  End   -------------
						+SHorizontalBox::Slot()
						.Padding(GetPadding(0.f, 1.f, 2.f, 1.f))        // L, Up, R, Dn
						.HAlign(HAlign_Left)
						.VAlign(VAlign_Fill)
						//+++++++++.VAlign(VAlign_Center)
						.AutoWidth()
						[
							SNew(SBox)
							//MaxDesiredWidth(FOptionalSize())
							.Padding(0)
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Fill)
							.WidthOverride(4.f * SizeKoef)
							//.HeightOverride(20.f)
							[
								SNew(SBorder)
								.Padding(0)
								.HAlign(HAlign_Fill)
								.VAlign(VAlign_Fill)
								.BorderImage(PropertyResponseEnd)                  //  image  Condition-Property   "Variable-Name"  End
							]
						]
											
					]
					
					//    ======================     CONDITION   "VARIABLE-Compare-Type"        =========================

					+SHorizontalBox::Slot()
					.HAlign(HAlign_Right)
					.VAlign(VAlign_Fill)
					[

						SNew(SHorizontalBox)

						//    -------  CONDITION   "VARIABLE-Compare-Type"  Start   -------------
						+SHorizontalBox::Slot()
						.Padding(GetPadding(50.f, 1.f, 0.f, 1.f))        // L, Up, R, Dn
						.HAlign(HAlign_Left)
						.VAlign(VAlign_Fill)
						//+++++++++.VAlign(VAlign_Center)
						.AutoWidth()
						[
							SNew(SBox)
							//MaxDesiredWidth(FOptionalSize())
							.Padding(0)
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Fill)
							.WidthOverride(4.f * SizeKoef)
							//.HeightOverride(20.f)
							[
								SNew(SBorder)
								.Padding(0)
								.HAlign(HAlign_Fill)
								.VAlign(VAlign_Fill)
								.BorderImage(PropertyResponseStart)                  //  image  Condition-Property   "Variable"  Start
							]
						]

						+ SHorizontalBox::Slot()
						.Padding(GetPadding(0, 1, 0, 1))
						.HAlign(HAlign_Fill)
						.VAlign(VAlign_Fill)
						//.FillWidth(1)
						.AutoWidth()
						[

							SNew(SBorder)
							.Padding(GetPadding(0, 0, 0, 0))
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Fill)
							.BorderImage(PropertyResponse)      //  image  Condition-Property   "Variable"  
							[

								SNew(SHorizontalBox)

								+ SHorizontalBox::Slot()
								.Padding(GetPadding(2, 1, 2, 1))
								.HAlign(HAlign_Left)
								.VAlign(VAlign_Center)
								.AutoWidth()
								[		
										//  ------------------------ CONDITION   VARIABLE- " = , != , < , < "    ---------------------------------
									SNew(SBox)
									//MaxDesiredWidth(FOptionalSize())
									.Padding(0)
									.HAlign(HAlign_Fill)
									.VAlign(VAlign_Fill)
									.WidthOverride(35.f * SizeKoef)
									[
										SNew(SButton)
										.ContentPadding(0)
										.HAlign(HAlign_Center)
										.VAlign(VAlign_Fill)
										.ButtonColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 0.3f))
										.OnClicked(this, &SDialogWindowWidget::OnHelperPanelClick, VarParam.CompareType, CurrentPropertyIndex)
										[
											
											SNew(STextBlock)
											.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 16 * SizeKoef))
											.ColorAndOpacity(FLinearColor(0.7f, 0.77f, 1.f, 1))
											//.ColorAndOpacity(FLinearColor(0.0f, 0.0f, 0.4f, 1))
											//.Visibility(this, &SDialogWindowWidget::GetVisibility_LocalVarIndicator, VarParam.VarTypePropperty, CurrentPropertyIndex) // VarTypePropperty  // EProppertyToChange::rep_condition_varType
											.Text(this, &SDialogWindowWidget::GetProppertyText, VarParam.CompareType, CurrentPropertyIndex)
										]
									]
								]
							]
						]

						//    -------  CONDITION   "Variable"  End   -------------
						+SHorizontalBox::Slot()
						.Padding(GetPadding(0.f, 1.f, 2.f, 1.f))        // L, Up, R, Dn
						.HAlign(HAlign_Left)
						.VAlign(VAlign_Fill)
						//+++++++++.VAlign(VAlign_Center)
						.AutoWidth()
						[
							SNew(SBox)
							//MaxDesiredWidth(FOptionalSize())
							.Padding(0)
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Fill)
							.WidthOverride(4.f * SizeKoef)
							//.HeightOverride(20.f)
							[
								SNew(SBorder)
								.Padding(0)
								.HAlign(HAlign_Fill)
								.VAlign(VAlign_Fill)
								.BorderImage(PropertyResponseEnd)                  //  image  Condition-Property   "Variable-Name"  End
							]
						]
					]

					//     ======================= CONDITION   "VARIABLE-Value"    =======================
					+ SHorizontalBox::Slot()
					.HAlign(HAlign_Right)
					.VAlign(VAlign_Fill)
					[

						SNew(SHorizontalBox)


							//    -------  CONDITION   "VARIABLE-Value"  Start   -------------
						+SHorizontalBox::Slot()
						.Padding(GetPadding(2.f, 1.f, 0.f, 1.f))        // L, Up, R, Dn
						.HAlign(HAlign_Right)
						.VAlign(VAlign_Fill)
						//+++++++++.VAlign(VAlign_Center)
						.AutoWidth()
						[
							SNew(SBox)
							//MaxDesiredWidth(FOptionalSize())
							.Padding(0)
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Fill)
							.WidthOverride(4.f * SizeKoef)
							//.HeightOverride(20.f)
							[
								SNew(SBorder)
								.Padding(0)
								.HAlign(HAlign_Fill)
								.VAlign(VAlign_Fill)
								.BorderImage(PropertyResponseStart)                  //  image  Condition-Property   "Variable-Value"  Start
							]
						]

						+ SHorizontalBox::Slot()
						.Padding(GetPadding(0, 1, 0, 1))
						.HAlign(HAlign_Right)
						.VAlign(VAlign_Fill)
						//.FillWidth(1)
						.AutoWidth()
						[

							SNew(SBorder)
							.Padding(GetPadding(0, 0, 0, 0))
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Fill)
							.BorderImage(PropertyResponse)      //  image  Condition-Property   "Variable-Value"  
							[

								SNew(SHorizontalBox)

								//  --------------------------------CONDITION   Vatiable-Value  --------------------------------
								+ SHorizontalBox::Slot()
								.Padding(GetPadding(2, 1, 2, 1))
								.HAlign(HAlign_Left)
								.VAlign(VAlign_Center)
								.AutoWidth()
								[

									SNew(STextBlock)
									.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 10 * SizeKoef))
									//.ColorAndOpacity(FLinearColor(0.0f, 0.0f, 0.4f, 1))
									.ColorAndOpacity(FLinearColor(0.7f, 0.77f, 1.f, 1))
									.Text(FText::FromString("Var value:"))

								]
								//  --------------------------------CONDITION   Vatiable-Value  (Button)--------------------------------
								+ SHorizontalBox::Slot()
								.Padding(GetPadding(2, 1, 2, 1))
								.HAlign(HAlign_Left)
								.VAlign(VAlign_Center)
								//777777777777.AutoWidth()
								[																			
									SNew(SButton) 
									.ContentPadding(0)
									.HAlign(HAlign_Left)
									.VAlign(VAlign_Center)
									.ButtonColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 0.f))    
									.OnClicked(this, &SDialogWindowWidget::OnButtonClick, VarParam.VarValuePropperty, CurrentPropertyIndex)  // VarValuePropperty  // EProppertyToChange::rep_condition_varValue
									[ 
										SNew(SOverlay)  

										+ SOverlay::Slot()           
										.HAlign(HAlign_Fill)
										.VAlign(VAlign_Center)
										//--.AutoWidth()
										[
											SNew(SBox)
											.Padding(GetPadding(0, 4, 0, 6))
											.HAlign(HAlign_Fill)
											.VAlign(VAlign_Fill)
											[
												SNew(SImage)
												.Image(ImageValueZone)      //       ImageValueZone
											]
										]

										+ SOverlay::Slot()
										.HAlign(HAlign_Center)
										.VAlign(VAlign_Center)
										[
											//  ===========================CONDITION   Vatiable-Value StaticText  ================================
											SNew(SHorizontalBox)
														
											+ SHorizontalBox::Slot()
											.Padding(GetPadding(4, 0, 4, 1))
											//+++++.HAlign(HAlign_Fill)
											.HAlign(HAlign_Center)
											.VAlign(VAlign_Center)
											//.FillWidth(1)
											.AutoWidth()
											[
												SNew(SBox)
												.MinDesiredWidth(70.f * SizeKoef)
												.MaxDesiredWidth(300.f * SizeKoef)
												.HAlign(HAlign_Center)
												.VAlign(VAlign_Center)
												[
													SNew(STextBlock)
													.Visibility(this, &SDialogWindowWidget::GetVisibilityOfSectionPropperty_Static, VarParam.VarValuePropperty, CurrentPropertyIndex)  // VarValuePropperty  // EProppertyToChange::rep_condition_varValue
													.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 12 * SizeKoef))
													.ColorAndOpacity(FLinearColor(0.7f, 0.77f, 1.f, 1))
													.Text(this, &SDialogWindowWidget::GetProppertyText, VarParam.VarValuePropperty, CurrentPropertyIndex)  // VarValuePropperty  // EProppertyToChange::rep_condition_varValue
												]
											]
													     
											+ SHorizontalBox::Slot()
											.HAlign(HAlign_Center)
											.VAlign(VAlign_Center)
											[
												SNew(SBox)
												.MinDesiredWidth(70.f * SizeKoef)
												.MaxDesiredWidth(300.f * SizeKoef)
												.HAlign(HAlign_Center)
												.VAlign(VAlign_Center)
												[ 
													//  ===========================CONDITION   Vatiable-Value EditableText  ================================
													SAssignNew((*VarParam.TextBoxVariable_Value), SEditableTextBox)
													.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 12 * SizeKoef))
													.Visibility(this, &SDialogWindowWidget::GetVisibilityOfSectionPropperty_Editable, VarParam.VarValuePropperty, CurrentPropertyIndex)  // VarValuePropperty  // EProppertyToChange::rep_condition_varValue
													.Text(FText::FromString((*VarParam.VariableValue_Text).ToString()))
													.OnTextCommitted(this, &SDialogWindowWidget::ConfirmEditableTextBox, VarParam.VarValuePropperty, CurrentPropertyIndex)  // PRES_ENTER:   void ConfirmEditableTextBox(const FText& Text, ETextCommit::Type TextType);
													.OnTextChanged_Raw(this, &SDialogWindowWidget::OnEditableTextChange)  // void OnButtonT(const FText& Text);
												]
											]
														 
										]
									]
	
								]

							]
						]
											
						//    -------  CONDITION   "Variable-Value"  End   -------------
						+SHorizontalBox::Slot()
						.Padding(GetPadding(0.f, 1.f, 2.f, 1.f))        // L, Up, R, Dn
						.HAlign(HAlign_Right)
						.VAlign(VAlign_Fill)
						//+++++++++.VAlign(VAlign_Center)
						.AutoWidth()
						[
							SNew(SBox)
							//MaxDesiredWidth(FOptionalSize())
							.Padding(0)
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Fill)
							.WidthOverride(4.f * SizeKoef)
							//.HeightOverride(20.f)
							[
								SNew(SBorder)
								.Padding(0)
								.HAlign(HAlign_Fill)
								.VAlign(VAlign_Fill)
								.BorderImage(PropertyResponseEnd)                  //  image  Condition-Property   "Variable-Value"  End
							]
						]
											
					]

				] // Border Title
			]
								
		]

		//    -------  Title-Condition    End   -------------
		+SHorizontalBox::Slot()
		.Padding(GetPadding(0.f, 1.f, 2.f, 1.f))        // L, Up, R, Dn
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		//+++++++++.VAlign(VAlign_Center)
		.AutoWidth()
		[
			SNew(SBox)
			//MaxDesiredWidth(FOptionalSize())
			.Padding(0)
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.WidthOverride(5.f * SizeKoef)
			//.HeightOverride(20.f)
			[
				SNew(SBorder)
				.Padding(0)
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.BorderImage(ConditionEnd)                  //   Title-Condition    End
			]
		]
	];
}





//   Set selected CONTENT-panel or  VARIABLES-panel
FReply SDialogWindowWidget::OnButtonSelectLayer(FName MainPanelType)
{
	iCurrentEditableSpeker = -1;
	iCurrentEditableSound = -1;
	vMainSpikersEditablePanel_FindImage = EVisibility::Collapsed;
	vMainSpikersEditablePanel_FindSound = EVisibility::Collapsed;
	MainSpikersEditablePanelBlock->ClearChildren();   //  CLear Speker-EditablePanel

	if (MainPanelType == FName("content"))
	{
		CurrentMainPanel = ECurrentMainPanel::Content;


		DialogContentVisibility = EVisibility::Visible;   //   Collapsed  Visible
		DialogVariablesVisibility = EVisibility::Collapsed;
		DialogSpikersVisibility = EVisibility::Collapsed;
	}
	else if (MainPanelType == FName("variables"))
	{
		CurrentMainPanel = ECurrentMainPanel::Variables;

		DialogContentVisibility = EVisibility::Collapsed;   //  // Collapsed  Visible  Hidden
		DialogVariablesVisibility = EVisibility::Visible;
		DialogSpikersVisibility = EVisibility::Collapsed;

		//RedrawVariablesBlock();
	}
	else if (MainPanelType == FName("spikers"))
	{
		
		CurrentMainPanel = ECurrentMainPanel::Spekers;

		DialogContentVisibility = EVisibility::Collapsed;   //  // Collapsed  Visible  Hidden
		DialogVariablesVisibility = EVisibility::Collapsed;
		DialogSpikersVisibility = EVisibility::Visible;

	}

	return FReply::Handled();
}   

FReply SDialogWindowWidget::AddNewElement()
{
	//   ----------------   Content   ----------------- 
	if (CurrentMainPanel == ECurrentMainPanel::Content)
	{
		*PathToCurrentXML = FString("none");
		DialogSection.Empty();
		FPropertyIndex PropertyIndex;
		PropertyIndex.iDialog = 0;
		AddDialogSection(PropertyIndex);
		UpdateDialogBlock();
	}

	//   ----------------   Variables   ----------------- 
	else if (CurrentMainPanel == ECurrentMainPanel::Variables)
	{
		FVariables DefaultVariables;
		DefaultVariables.VariableName = FName("default");
		DefaultVariables.VariableValue = FName("DEFAULT");
		DefaultVariables.isVariableGlobal = false;
		Variables.Add(DefaultVariables);

		RedrawVariablesBlock();
	}

	//   ----------------   Spekers   ----------------- 
	else if (CurrentMainPanel == ECurrentMainPanel::Spekers)
	{
		FSpekers SpekerTEMP;
		SpekerTEMP.SpekersImageBrush = *SpekersImageDefault;
		//SpekerTEMP.SpekersAssetPath = "/PugiXML_Plagin/icon/Man_avatar_0.Man_avatar_0";
		SpekerTEMP.SpekersAssetPath = SpekersImageDefault->GetResourceObject()->GetPathName();

		//SpekerTEMP.NeedRedraw = true;

		MainVariablesPanelBlock->ScrollToEnd();
		Speker.Add(SpekerTEMP);


		iCurrentEditableSpeker = -1;
		iCurrentEditableSound = -1;
		vMainSpikersEditablePanel_FindImage = EVisibility::Collapsed;
		vMainSpikersEditablePanel_FindSound = EVisibility::Collapsed;
		MainSpikersEditablePanelBlock->ClearChildren();   //  CLear Speker-EditablePanel

		MainSpikersPanelBlock->ScrollToEnd();
		RedrawSpekersBlock();
	}

	return FReply::Handled();
}


const FSlateBrush* SDialogWindowWidget::GetImageConditionButton(EProppertyToChange _ProppertyToChange, FPropertyIndex PropertyIndex)  const
{

	if (_ProppertyToChange == EProppertyToChange::CollapsedResponse_Variables)
	{
		if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
			.ResponseSection[PropertyIndex.iResponse].VariableSection.Num() > 0)			return ImageVariableButtonOn;
		else																				return ImageVariableButtonOff;
	}
	else if (_ProppertyToChange == EProppertyToChange::CollapsedResponse_Condition)
	{
		if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
			.ResponseSection[PropertyIndex.iResponse].ResponseCondition.Num() > 0)			return ImageConditionButtonOn;
		else																				return ImageConditionButtonOFF;
	}
	else if (_ProppertyToChange == EProppertyToChange::CollapsedReplic_Condition)
	{
		if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
			.ReplicSection[PropertyIndex.iReplic].ReplicCondition.Num() > 0)				return ImageConditionButtonOn;
		else																				return ImageConditionButtonOFF;
	}
	else if (_ProppertyToChange == EProppertyToChange::CollapsedRep_Condition)
	{
		if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic]
									.RepSection[PropertyIndex.iRep].RepCondition.Num() > 0)		return ImageConditionButtonOn;
		else																					return ImageConditionButtonOFF;
	}
	else if (_ProppertyToChange == EProppertyToChange::CollapsedSpeech_Condition)
	{
		if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].SpeechCondition.Num() > 0)	return ImageConditionButtonOn;
		else																										return ImageConditionButtonOFF;
	}

	return ImageConditionButtonOn;
}


//  Roll Up Section or expand it (Get picture)
const FSlateBrush* SDialogWindowWidget::GetImageButtonSectionCollapsed(EProppertyToChange _ProppertyToChange, FPropertyIndex PropertyIndex) const
{
	
	if (_ProppertyToChange == EProppertyToChange::CollapsedReplicSection)
	{
		if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
							.ReplicSection[PropertyIndex.iReplic].IsSectionOpen)		return ImageButtonSectionExpand;
		else																					return ImageButtonSectionRollUp;
	}

	else if (_ProppertyToChange == EProppertyToChange::CollapsedSpeechSection)
	{
		if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].IsSectionOpen)		return ImageButtonSectionExpand;
		else																								return ImageButtonSectionRollUp;
	}
	else if (_ProppertyToChange == EProppertyToChange::CollapsedDialogSection)
	{
		if (DialogSection[PropertyIndex.iDialog].IsSectionOpen)									return ImageButtonSectionExpand;
		else																					return ImageButtonSectionRollUp;
	}



	return ImageButtonSectionRollUp;


}


FSlateColor SDialogWindowWidget::GetSectionTextColor(EProppertyToChange ProppertyToChange, FPropertyIndex PropertyIndex) const
{

	if (ProppertyToChange == EProppertyToChange::DialogName)
	{
		if (DialogSection[PropertyIndex.iDialog].IsErrorMarker) return FSlateColor(ColorErrorMarked);
		else if (DialogSection[PropertyIndex.iDialog].IsDestinationMarker) return FSlateColor(ColorLinkMarked);
		else if (DialogSection[PropertyIndex.iDialog].IsLinkMarker) return FSlateColor(ColorDestinationLinkMarked);
		else if (DialogSection[PropertyIndex.iDialog].IsUsualMarker) return FSlateColor(ColorUsualMarked);
		else if (DialogSection[PropertyIndex.iDialog].IsFastFindMarker) return ColorFastFindMarked;
		else  return FSlateColor(ColorUsualText);
	}
	else if (ProppertyToChange == EProppertyToChange::SpeechName)
	{
		if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
			.IsErrorMarker) return FSlateColor(ColorErrorMarked);
		else if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
			.IsDestinationMarker) return FSlateColor(ColorLinkMarked);
		else if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
			.IsLinkMarker) return FSlateColor(ColorDestinationLinkMarked);
		else if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
			.IsUsualMarker) return FSlateColor(ColorUsualMarked);
		else if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
			.IsFastFindMarker) return ColorFastFindMarked;
		else  return FSlateColor(ColorUsualText);
	}


	else if (ProppertyToChange == EProppertyToChange::repeatReplic)
	{
		if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
			.ReplicSection[PropertyIndex.iReplic].IsErrorMarker) return FSlateColor(ColorErrorMarked);
		else if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
			.ReplicSection[PropertyIndex.iReplic].IsUsualMarker) return FSlateColor(ColorUsualMarked);
		else  return FSlateColor(ColorUsualText);
	}



	else if (ProppertyToChange == EProppertyToChange::MarkerRep ||
			 ProppertyToChange == EProppertyToChange::speker ||
			 ProppertyToChange == EProppertyToChange::sound || 
			 ProppertyToChange == EProppertyToChange::RepEvent ||
			 ProppertyToChange == EProppertyToChange::time ||
			 ProppertyToChange == EProppertyToChange::delay )
	{
		if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
			.ReplicSection[PropertyIndex.iReplic].RepSection[PropertyIndex.iRep]
			.IsErrorMarker) return FSlateColor(ColorErrorMarked);
		else if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
			.ReplicSection[PropertyIndex.iReplic].RepSection[PropertyIndex.iRep]
			.IsUsualMarker) return FSlateColor(ColorUsualMarked);
		else  return FSlateColor(ColorUsualText);
	}


	else if (ProppertyToChange == EProppertyToChange::repeatResponse || 
			 ProppertyToChange == EProppertyToChange::DialogLink ||
			 ProppertyToChange == EProppertyToChange::SpeechLink )
	{
		if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
			.ResponseSection[PropertyIndex.iResponse].IsErrorMarker) return FSlateColor(ColorErrorMarked);
		else if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
			.ResponseSection[PropertyIndex.iResponse].IsLinkMarker) return FSlateColor(ColorLinkMarked);
		else if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
			.ResponseSection[PropertyIndex.iResponse].IsUsualMarker) return FSlateColor(ColorUsualMarked);
		else  return FSlateColor(ColorUsualText);
	}


	return FSlateColor(ColorUsualText);
}

EVisibility SDialogWindowWidget::IsSectionCollapsed(EProppertyToChange _ProppertyToChange, FPropertyIndex PropertyIndex) const
{

	if (_ProppertyToChange == EProppertyToChange::CollapsedResponse_Variables)
	{
		if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ResponseSection[PropertyIndex.iResponse]
																										.IsVariableOpen)			return EVisibility::Visible;
		else																														return EVisibility::Collapsed;
	}
	else if (_ProppertyToChange == EProppertyToChange::CollapsedResponse_Condition)
	{
		if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ResponseSection[PropertyIndex.iResponse]
																										.IsConditionOpen)			return EVisibility::Visible;
		else																														return EVisibility::Collapsed;
	}
	else if (_ProppertyToChange == EProppertyToChange::CollapsedReplic_Condition)
	{
		if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
									.ReplicSection[PropertyIndex.iReplic].IsConditionOpen)								return EVisibility::Visible;
		else																														return EVisibility::Collapsed;
	}
	else if (_ProppertyToChange == EProppertyToChange::CollapsedSpeech_Condition)
	{
		if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].IsConditionOpen)								return EVisibility::Visible;
		else																														return EVisibility::Collapsed;
	}
	else if (_ProppertyToChange == EProppertyToChange::CollapsedRep_Condition)
	{
		if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
			.ReplicSection[PropertyIndex.iReplic].RepSection[PropertyIndex.iRep].IsConditionOpen)		return EVisibility::Visible;
		else																														return EVisibility::Collapsed;
	}   
	else if (_ProppertyToChange == EProppertyToChange::CollapsedReplicSection)
	{
		if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
									.ReplicSection[PropertyIndex.iReplic].IsSectionOpen)			return EVisibility::Visible;
		else																								return EVisibility::Collapsed;
	}

	else if (_ProppertyToChange == EProppertyToChange::CollapsedSpeechSection) 
	{
		if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].IsSectionOpen)		return EVisibility::Visible;
		else																								return EVisibility::Collapsed;
	}
	else if (_ProppertyToChange == EProppertyToChange::CollapsedDialogSection)
	{
		if (DialogSection[PropertyIndex.iDialog].IsSectionOpen)												 return EVisibility::Visible;
		else																								 return EVisibility::Collapsed;
	}


	

	return EVisibility::Collapsed;
}


void SDialogWindowWidget::ConfirmEditableMultilineTextBox(const FText& Text, ETextCommit::Type TextType, EProppertyToChange ProppertyToChange, FPropertyIndex PropertyIndex)
{
	//UE_LOG(LogTemp, Warning, TEXT("SEditableTextBox = '%i'"), a);  // EditableText1.GetText()

	float MultiplyEditableTextZoneSize = MultiplyTextSize;

	int32 StartPos = 0;
	int32 FindingN = EditableChangedText.Find("\n", ESearchCase::Type::IgnoreCase, ESearchDir::Type::FromStart, StartPos);
	while (FindingN != -1)
	{	
		MultiplyEditableTextZoneSize += MultiplyTextSize;
		StartPos = FindingN;
		if (FindingN == EditableChangedText.Len() - 1) break;
		FindingN = EditableChangedText.Find("\n", ESearchCase::Type::IgnoreCase, ESearchDir::Type::FromStart, StartPos + 1);		
	}

	if (MultiplyEditableTextZoneSize > MultiplyTextMaxSize) MultiplyEditableTextZoneSize = MultiplyTextMaxSize;

	if (ProppertyToChange == EProppertyToChange::replicComent)
	{
		if (EditableChangedText != FString(""))
		{
			DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
				.ReplicSection[PropertyIndex.iReplic].ComentText = EditableChangedText;
			DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
				.ReplicSection[PropertyIndex.iReplic].ComentTextZoneSizeY = MultiplyEditableTextZoneSize;
			EditableChangedText = FString("");

			//UE_LOG(LogTemp, Warning, TEXT("replic-------: = '%s'"), *DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic].ComentText);
		}
	}
	if (ProppertyToChange == EProppertyToChange::repComent)
	{
		if (EditableChangedText != FString(""))
		{
			DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
				.ReplicSection[PropertyIndex.iReplic].RepSection[PropertyIndex.iRep].ComentText = EditableChangedText;
			DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
				.ReplicSection[PropertyIndex.iReplic].RepSection[PropertyIndex.iRep].ComentTextZoneSizeY = MultiplyEditableTextZoneSize;
			EditableChangedText = FString("");
		}
	}
	if (ProppertyToChange == EProppertyToChange::responseComent)
	{
		if (EditableChangedText != FString(""))
		{
			DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
				.ResponseSection[PropertyIndex.iResponse].ComentText = EditableChangedText;
			DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
				.ResponseSection[PropertyIndex.iResponse].ComentTextZoneSizeY = MultiplyEditableTextZoneSize;
			EditableChangedText = FString("");
		}
	}	
	//ConfirmCurrentSelection(ProppertyToChange, PropertyIndex);
	RedrawIndicator();
}




FReply SDialogWindowWidget::OnButtonClick(EProppertyToChange ProppertyToChange, FPropertyIndex PropertyIndex)
{
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, FString::SanitizeFloat(_Param_DialodTag));
	ConfirmCurrentSelection(ProppertyToChange, PropertyIndex);
	
	if (ProppertyToChange == EProppertyToChange::ButtonAdd_Variable)
	{
		AddVariable(PropertyIndex);
	}
	if (ProppertyToChange == EProppertyToChange::ButtonRemove_Variable)
	{
		RemoveVariable(PropertyIndex);
	}
	else if (ProppertyToChange == EProppertyToChange::ButtonAddSpeech_Condition)
	{
		AddSpeechCondition(PropertyIndex);   
	}
	else if (ProppertyToChange == EProppertyToChange::ButtonAddResponse_Condition)
	{
		AddResponseCondition(PropertyIndex);
	}
	else if (ProppertyToChange == EProppertyToChange::ButtonAddResponse_Variable)
	{
		AddResponseVariable(PropertyIndex);   
	}
	else if (ProppertyToChange == EProppertyToChange::ButtonAddReplic_Condition)
	{
		AddReplicCondition(PropertyIndex);
	}
	else if (ProppertyToChange == EProppertyToChange::ButtonAddRep_Condition)
	{
		AddRepCondition(PropertyIndex);
	}
	else if (ProppertyToChange == EProppertyToChange::AddDialog)
	{
		AddDialogSection(PropertyIndex);
	}
	else if (ProppertyToChange == EProppertyToChange::AddSpeech)
	{
		AddSpeechSection(PropertyIndex);
	}
	else if (ProppertyToChange == EProppertyToChange::AddReplick)
	{
		AddReplicSection(PropertyIndex);
	}
	else if (ProppertyToChange == EProppertyToChange::AddResponse)
	{
		AddResponseSection(PropertyIndex);
	}
	else if (ProppertyToChange == EProppertyToChange::ButtonAddRep)
	{
		AddRepSection(PropertyIndex);
	}


	else if (ProppertyToChange == EProppertyToChange::CollapsedDialogSection ||
			ProppertyToChange == EProppertyToChange::CollapsedSpeechSection ||
			ProppertyToChange == EProppertyToChange::CollapsedReplicSection ||
			ProppertyToChange == EProppertyToChange::CollapsedRep_Condition ||
			ProppertyToChange == EProppertyToChange::CollapsedReplic_Condition ||
			ProppertyToChange == EProppertyToChange::CollapsedResponse_Condition ||
			ProppertyToChange == EProppertyToChange::CollapsedSpeech_Condition ||
			ProppertyToChange == EProppertyToChange::CollapsedResponse_Variables 
		)
	{
		SwitchCollapsedSection(ProppertyToChange, PropertyIndex);
	}




	else if (ProppertyToChange == EProppertyToChange::DialogName ||
			ProppertyToChange == EProppertyToChange::SpeechName ||
			ProppertyToChange == EProppertyToChange::rep_condition_type ||
			ProppertyToChange == EProppertyToChange::rep_condition_varName ||
			ProppertyToChange == EProppertyToChange::rep_condition_varValue ||
			ProppertyToChange == EProppertyToChange::Speech_condition_type ||
			ProppertyToChange == EProppertyToChange::Speech_condition_varName ||
			ProppertyToChange == EProppertyToChange::Speech_condition_varValue ||

			ProppertyToChange == EProppertyToChange::Response_condition_type ||
			ProppertyToChange == EProppertyToChange::Response_condition_varName ||
			ProppertyToChange == EProppertyToChange::Response_condition_varValue ||

			ProppertyToChange == EProppertyToChange::Replic_condition_type ||
			ProppertyToChange == EProppertyToChange::Replic_condition_varName ||
			ProppertyToChange == EProppertyToChange::Replic_condition_varValue ||
			ProppertyToChange == EProppertyToChange::DialogLink ||
			ProppertyToChange == EProppertyToChange::SpeechLink ||
			//ProppertyToChange == EProppertyToChange::Response_variable_type ||
			ProppertyToChange == EProppertyToChange::Response_variable_varName ||
			ProppertyToChange == EProppertyToChange::Response_variable_varValue ||
			ProppertyToChange == EProppertyToChange::Variable_varName ||
			ProppertyToChange == EProppertyToChange::Variable_varValue ||
			ProppertyToChange == EProppertyToChange::RepEvent)
	{
		EditProperty(ProppertyToChange, PropertyIndex);
	}


	else if (ProppertyToChange == EProppertyToChange::rep_condition_varType)
	{
		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic]
			.RepSection[PropertyIndex.iRep].RepCondition[PropertyIndex.iRepCondition].isVariableGlobal =
		!DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic]
			.RepSection[PropertyIndex.iRep].RepCondition[PropertyIndex.iRepCondition].isVariableGlobal;
	}
	else if (ProppertyToChange == EProppertyToChange::Replic_condition_varType)
	{
		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic]
																.ReplicCondition[PropertyIndex.iReplicCondition].isVariableGlobal =
			!DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic]
																.ReplicCondition[PropertyIndex.iReplicCondition].isVariableGlobal;
	}
	else if (ProppertyToChange == EProppertyToChange::Response_condition_varType)
	{
		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ResponseSection[PropertyIndex.iResponse]
																.ResponseCondition[PropertyIndex.iResponseCondition].isVariableGlobal =   //iRepOrResponsCondition
			!DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ResponseSection[PropertyIndex.iResponse]
																.ResponseCondition[PropertyIndex.iResponseCondition].isVariableGlobal;  //iRepOrResponsCondition
	}
	else if (ProppertyToChange == EProppertyToChange::Response_variable_varType)
	{
		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ResponseSection[PropertyIndex.iResponse]
																.VariableSection[PropertyIndex.iResponseVariable].isVariableGlobal =   //iRepOrResponsCondition
		!DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ResponseSection[PropertyIndex.iResponse]
																.VariableSection[PropertyIndex.iResponseVariable].isVariableGlobal;  //iRepOrResponsCondition
	}
	else if (ProppertyToChange == EProppertyToChange::Speech_condition_varType)
	{
		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].SpeechCondition[PropertyIndex.iSpeechCondition].isVariableGlobal =
			!DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].SpeechCondition[PropertyIndex.iSpeechCondition].isVariableGlobal;
	}

	

	return FReply::Handled();
}


FReply SDialogWindowWidget::OnButtonRemoveClick(EProppertyToChange ProppertyToChange, FPropertyIndex PropertyIndex)
{
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, FString::SanitizeFloat(_Param_DialodTag));
	ConfirmCurrentSelection(ProppertyToChange, PropertyIndex);

	if (ProppertyToChange == EProppertyToChange::RemoveDialog)
	{
		DialogSection.RemoveAt(PropertyIndex.iDialog);
	}
	else if (ProppertyToChange == EProppertyToChange::RemoveSpeech)
	{
		DialogSection[PropertyIndex.iDialog].SpeechSection.RemoveAt(PropertyIndex.iSpeech); 
	}
	else if (ProppertyToChange == EProppertyToChange::RemoveReplic)
	{
		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
									.ReplicSection.RemoveAt(PropertyIndex.iReplic);
	}
	else if (ProppertyToChange == EProppertyToChange::RemoveRep)
	{
		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
									.ReplicSection[PropertyIndex.iReplic]
									.RepSection.RemoveAt(PropertyIndex.iRep);
	}
	else if (ProppertyToChange == EProppertyToChange::RemoveResponse)
	{
		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
								.ResponseSection.RemoveAt(PropertyIndex.iReplic);
	}
	else if (ProppertyToChange == EProppertyToChange::RemoveSpeech_Condition)
	{
		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
								.SpeechCondition.RemoveAt(PropertyIndex.iSpeechCondition);
	}
	else if (ProppertyToChange == EProppertyToChange::RemoveReplic_Condition)
	{
		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
									.ReplicSection[PropertyIndex.iReplic]
									.ReplicCondition.RemoveAt(PropertyIndex.iReplicCondition);
	}
	else if (ProppertyToChange == EProppertyToChange::RemoveRep_Condition)
	{

		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
									.ReplicSection[PropertyIndex.iReplic]
									.RepSection[PropertyIndex.iRep]
									.RepCondition.RemoveAt(PropertyIndex.iRepCondition);
	}
	else if (ProppertyToChange == EProppertyToChange::RemoveResponse_Condition)
	{		
			DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
									.ResponseSection[PropertyIndex.iResponse]
									.ResponseCondition.RemoveAt(PropertyIndex.iResponseCondition);
	}
	else if (ProppertyToChange == EProppertyToChange::RemoveResponse_Variable)
	{		
		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
								.ResponseSection[PropertyIndex.iResponse]
								.VariableSection.RemoveAt(PropertyIndex.iResponseVariable);
	}

	UpdateDialogBlock();

	return FReply::Handled();
}

 
//  =====================     Change Section mame     ======================
//void SDialogWindowWidget::ChangeSectionProperty(EProppertyToChange ProppertyToChange, int32 _DialogIndex, int32 _SpeechIndex, int32 _ReplicOrResponseIndex)
void SDialogWindowWidget::EditProperty(EProppertyToChange _ProppertyToChange, FPropertyIndex PropertyIndex)
{

	ConfirmCurrentSelection(_ProppertyToChange, PropertyIndex);



	//  ---------------------------    Variables   Variable__Block  ----------------------------
	if (_ProppertyToChange == EProppertyToChange::Variable_varName)
	{

		Variables[PropertyIndex.iVariable].IsProperty_VariableName_EditNow = true;  

		FSlateApplication::Get().SetKeyboardFocus(Variables[PropertyIndex.iVariable].ChangeVariable_Name_Editable.ToSharedRef());  
	}

	else if (_ProppertyToChange == EProppertyToChange::Variable_varValue)
	{
		Variables[PropertyIndex.iVariable].IsProperty_VariableValue_EditNow = true;  

		FSlateApplication::Get().SetKeyboardFocus(Variables[PropertyIndex.iVariable].ChangeVariable_Value_Editable.ToSharedRef()); 
	}

	//  ---------------------------   Rsponse Variables   ----------------------------
	else if (_ProppertyToChange == EProppertyToChange::Response_variable_varName)
	{

		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ResponseSection[PropertyIndex.iResponse]
			.VariableSection[PropertyIndex.iResponseVariable].IsProperty_VariableName_EditNow = true;  // iRepOrResponsCondition

		FSlateApplication::Get().SetKeyboardFocus(DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
			.ResponseSection[PropertyIndex.iResponse].VariableSection[PropertyIndex.iResponseVariable].ChangeVariable_Name_Editable.ToSharedRef());  //iRepOrResponsCondition
	}

	else if (_ProppertyToChange == EProppertyToChange::Response_variable_varValue)
	{
		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ResponseSection[PropertyIndex.iResponse]
			.VariableSection[PropertyIndex.iResponseVariable].IsProperty_VariableValue_EditNow = true;  //iRepOrResponsCondition

		FSlateApplication::Get().SetKeyboardFocus(DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
			.ResponseSection[PropertyIndex.iResponse].VariableSection[PropertyIndex.iResponseVariable].ChangeVariable_Value_Editable.ToSharedRef()); // iRepOrResponsCondition
	}


	//  ---------------------------   Rep Condition   ----------------------------
	else if (_ProppertyToChange == EProppertyToChange::rep_condition_varName)
	{ 
	
		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic]
		.RepSection[PropertyIndex.iRep].RepCondition[PropertyIndex.iRepCondition].IsProperty_VariableName_EditNow = true;

		FSlateApplication::Get().SetKeyboardFocus(DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
			.ReplicSection[PropertyIndex.iReplic].RepSection[PropertyIndex.iRep]
			.RepCondition[PropertyIndex.iRepCondition].ConditionVariable_Name_Editable.ToSharedRef());
	}

	else if (_ProppertyToChange == EProppertyToChange::rep_condition_varValue)
	{		
		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic]
			.RepSection[PropertyIndex.iRep].RepCondition[PropertyIndex.iRepCondition].IsProperty_VariableValue_EditNow = true;

		FSlateApplication::Get().SetKeyboardFocus(DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
			.ReplicSection[PropertyIndex.iReplic].RepSection[PropertyIndex.iRep]
			.RepCondition[PropertyIndex.iRepCondition].ConditionVariable_Value_Editable.ToSharedRef());
	}
	else if (_ProppertyToChange == EProppertyToChange::rep_condition_type)
	{
		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic]
										.RepSection[PropertyIndex.iRep].RepCondition[PropertyIndex.iRepCondition].IsProperty_Type_EditNow = true;

		FSlateApplication::Get().SetKeyboardFocus(DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
											.ReplicSection[PropertyIndex.iReplic].RepSection[PropertyIndex.iRep]
											.RepCondition[PropertyIndex.iRepCondition].Condition_Type_Editable.ToSharedRef());
		
	}



	//  ---------------------------   Rsponse Condition   ----------------------------
	else if (_ProppertyToChange == EProppertyToChange::Response_condition_varName)
	{

		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ResponseSection[PropertyIndex.iResponse]
			.ResponseCondition[PropertyIndex.iResponseCondition].IsProperty_VariableName_EditNow = true;  // iRepOrResponsCondition

		FSlateApplication::Get().SetKeyboardFocus(DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
			.ResponseSection[PropertyIndex.iResponse].ResponseCondition[PropertyIndex.iResponseCondition].ConditionVariable_Name_Editable.ToSharedRef());  //iRepOrResponsCondition
	}

	else if (_ProppertyToChange == EProppertyToChange::Response_condition_varValue)
	{
		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ResponseSection[PropertyIndex.iResponse]
			.ResponseCondition[PropertyIndex.iResponseCondition].IsProperty_VariableValue_EditNow = true;  //iRepOrResponsCondition

		FSlateApplication::Get().SetKeyboardFocus(DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
			.ResponseSection[PropertyIndex.iResponse].ResponseCondition[PropertyIndex.iResponseCondition].ConditionVariable_Value_Editable.ToSharedRef()); // iRepOrResponsCondition
	}
	else if (_ProppertyToChange == EProppertyToChange::Response_condition_type)
	{
		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ResponseSection[PropertyIndex.iResponse]
																.ResponseCondition[PropertyIndex.iResponseCondition].IsProperty_Type_EditNow = true;  //iRepOrResponsCondition

		FSlateApplication::Get().SetKeyboardFocus(DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
						.ResponseSection[PropertyIndex.iResponse].ResponseCondition[PropertyIndex.iResponseCondition]  // iRepOrResponsCondition
																						.Condition_Type_Editable.ToSharedRef());		
	}



	//  ---------------------------   Replic Condition   ----------------------------
	else if (_ProppertyToChange == EProppertyToChange::Replic_condition_varName)
	{

		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic]
			.ReplicCondition[PropertyIndex.iReplicCondition].IsProperty_VariableName_EditNow = true;

		FSlateApplication::Get().SetKeyboardFocus(DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
			.ReplicSection[PropertyIndex.iReplic].ReplicCondition[PropertyIndex.iReplicCondition].ConditionVariable_Name_Editable.ToSharedRef());
	}

	else if (_ProppertyToChange == EProppertyToChange::Replic_condition_varValue)
	{
		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic]
			.ReplicCondition[PropertyIndex.iReplicCondition].IsProperty_VariableValue_EditNow = true;

		FSlateApplication::Get().SetKeyboardFocus(DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
			.ReplicSection[PropertyIndex.iReplic].ReplicCondition[PropertyIndex.iReplicCondition].ConditionVariable_Value_Editable.ToSharedRef());
	}
	else if (_ProppertyToChange == EProppertyToChange::Replic_condition_type)
	{
		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic]
						.ReplicCondition[PropertyIndex.iReplicCondition].IsProperty_Type_EditNow = true;

		FSlateApplication::Get().SetKeyboardFocus(DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
						.ReplicSection[PropertyIndex.iReplic].ReplicCondition[PropertyIndex.iReplicCondition]
																						.Condition_Type_Editable.ToSharedRef());
	}


	//  ---------------------------   Speech Condition   ----------------------------
	else if (_ProppertyToChange == EProppertyToChange::Speech_condition_varName)
	{

		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].SpeechCondition[PropertyIndex.iSpeechCondition].IsProperty_VariableName_EditNow = true;

		FSlateApplication::Get().SetKeyboardFocus(DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]			
			.SpeechCondition[PropertyIndex.iSpeechCondition].ConditionVariable_Name_Editable.ToSharedRef());
	}

	else if (_ProppertyToChange == EProppertyToChange::Speech_condition_varValue)
	{
		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].SpeechCondition[PropertyIndex.iSpeechCondition].IsProperty_VariableValue_EditNow = true;

		FSlateApplication::Get().SetKeyboardFocus(DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
			.SpeechCondition[PropertyIndex.iSpeechCondition].ConditionVariable_Value_Editable.ToSharedRef());
	}
	else if (_ProppertyToChange == EProppertyToChange::Speech_condition_type)
	{
		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
			.SpeechCondition[PropertyIndex.iSpeechCondition].IsProperty_Type_EditNow = true;

		FSlateApplication::Get().SetKeyboardFocus(DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
			.SpeechCondition[PropertyIndex.iSpeechCondition].Condition_Type_Editable.ToSharedRef());
	}
	
	else if (_ProppertyToChange == EProppertyToChange::RepEvent)
	{
	DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic]
																.RepSection[PropertyIndex.iRep].isEventPropertyEditNow = true;
	FSlateApplication::Get().SetKeyboardFocus(DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
		.ReplicSection[PropertyIndex.iReplic].RepSection[PropertyIndex.iRep].RepEvent_EditableText.ToSharedRef());
	}

	else if (_ProppertyToChange == EProppertyToChange::SpeechName)
	{

		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].IsSectionEditNow = true;
		
		FSlateApplication::Get().SetKeyboardFocus(DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
																							.SpeechSectionName_Editable.ToSharedRef());
		
	}


	else if (_ProppertyToChange == EProppertyToChange::DialogName)
	{

		if (PropertyIndex.iDialog == 0) return;

		//if (PropertyIndex.iDialog == -1) return;
		//   .........
		DialogSection[PropertyIndex.iDialog].IsSectionEditNow = true;
		////   .........
		//DialogSection[PropertyIndex.iDialog].ChangeDialodSectionName_Button->ButtonHitted = EVisibility::Hidden;
		////   .........
		FSlateApplication::Get().SetKeyboardFocus(DialogSection[PropertyIndex.iDialog].DialogSectionName_Editable.ToSharedRef());

		////   .........
		//changingDialod_Index = PropertyIndex.iDialog;
		//changingPropperty = EProppertyToChange::DialogName;
	}

	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, DialogSection[_DialogIndex].Name.ToString());
	
}


    
//  =====================  Add Mew DIALOG Section  =====================
void SDialogWindowWidget::AddDialogSection(FPropertyIndex PropertyIndex)
{
	// -----------   Get free name   --------------
	FName NewDialogSectionName = FName("DEFAULT");

	for (int32 i_dialog = 0; i_dialog < DialogSection.Num(); i_dialog++)
	{
		if (DialogSection[i_dialog].Name == NewDialogSectionName)
		{
			int32 random = FMath::RandRange(1, 100000);
			FString NewName = FString("NewDialogName_") + FString::FromInt(random);
			NewDialogSectionName = FName(*NewName);
			i_dialog = 0;
		}
	}


	//  ---------  form new Massive data  ----------
	FDialogSection NewDialogSection;
	NewDialogSection.Name = NewDialogSectionName;   

	

	ShouldUpdate = EShouldUpdate::inDialog;



	if (DialogSection.Num() == 0)   // no-one element
	{
		DialogSection.Add(FDialogSection());
		PropertyIndex.iSpeech = 0;
		AddSpeechSection(PropertyIndex);       //  -->> UpdateDialogBlock();
	}
	else if (PropertyIndex.iDialog == DialogSection.Num() - 1) // if it's last element
	{
		DialogSection.Add(NewDialogSection);
		PropertyIndex.iDialog += 1;
		PropertyIndex.iSpeech = 0;
		AddSpeechSection(PropertyIndex);   //  -->> UpdateDialogBlock();
	}
	else
	{
		DialogSection.Insert(NewDialogSection, PropertyIndex.iDialog + 1);
		PropertyIndex.iDialog += 1;
		PropertyIndex.iSpeech = 0;
		AddSpeechSection(PropertyIndex);   //  -->> UpdateDialogBlock();
	}

	
	UpdateDialogBlock();
	ShouldUpdate = EShouldUpdate::none;
}




//  =====================  Add Mew SPEECH Section  =====================
//void SDialogWindowWidget::AddSpeechSection(int32 _DialogIndex, int32 _SpeechIndex)
void SDialogWindowWidget::AddSpeechSection(FPropertyIndex PropertyIndex)
{ 

	// -----------   Get free name   --------------xxxxxxxxxxxxxx


	if (ShouldUpdate == EShouldUpdate::none) ShouldUpdate = EShouldUpdate::inSpeech;


	if (DialogSection[PropertyIndex.iDialog].SpeechSection.Num() == 0)   // no-one element
	{
		DialogSection[PropertyIndex.iDialog].SpeechSection.Add(FSpeechSection());
		PropertyIndex.iReplic = 0;
		PropertyIndex.iResponse = 0;
		AddReplicSection(PropertyIndex);
		AddResponseSection(PropertyIndex);
	}
	else if (PropertyIndex.iSpeech == DialogSection[PropertyIndex.iDialog].SpeechSection.Num() - 1)  // // if it's last element
	{
		DialogSection[PropertyIndex.iDialog].SpeechSection.Add(FSpeechSection());
		PropertyIndex.iSpeech += 1;
		PropertyIndex.iReplic = 0;
		PropertyIndex.iResponse = 0;
		AddReplicSection(PropertyIndex);
		AddResponseSection(PropertyIndex);
	}
	
	else
	{
		DialogSection[PropertyIndex.iDialog].SpeechSection.Insert(FSpeechSection(), PropertyIndex.iSpeech + 1);
		PropertyIndex.iSpeech += 1;
		PropertyIndex.iReplic = 0;
		PropertyIndex.iResponse = 0;
		AddReplicSection(PropertyIndex);
		AddResponseSection(PropertyIndex);
	}
		


	if (ShouldUpdate == EShouldUpdate::inSpeech)
	{
		UpdateDialogBlock();
		ShouldUpdate = EShouldUpdate::none;
	}

}


//  =====================  Add Mew REPLiC Section  =====================
//void SDialogWindowWidget::AddReplicSection(int32 _DialogIndex, int32 _SpeechIndex, int32 _ReplicIndex)
void SDialogWindowWidget::AddReplicSection(FPropertyIndex PropertyIndex)
{
	
	FReplicSection NewReplicSection;
	NewReplicSection.ComentTextZoneSizeY = MultiplyTextSize;


	if (ShouldUpdate == EShouldUpdate::none) ShouldUpdate = EShouldUpdate::inReplic;


	if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection.Num() == 0)   // no-one element
	{
		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection.Add(NewReplicSection);
		PropertyIndex.iRep = 0;
		AddRepSection(PropertyIndex);
		//Update = false;
	}
	else if (PropertyIndex.iReplic == DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection.Num() - 1)  // // if it's last element
	{
		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection.Add(NewReplicSection);
		PropertyIndex.iReplic += 1;
		PropertyIndex.iRep = 0;
		AddRepSection(PropertyIndex);
		//Update = false;
	}

	else
	{
		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection.Insert(NewReplicSection, PropertyIndex.iReplic + 1);
		PropertyIndex.iReplic += 1;
		PropertyIndex.iRep = 0;
		AddRepSection(PropertyIndex);
		//Update = false;
	}


	if (ShouldUpdate == EShouldUpdate::inReplic)
	{
		UpdateDialogBlock();
		ShouldUpdate = EShouldUpdate::none;
	}
}

//void SDialogWindowWidget::AddRepSection(int32 _DialogIndex, int32 _SpeechIndex, int32 _ReplicIndex, int32 _RepIndex)
void SDialogWindowWidget::AddRepSection(FPropertyIndex PropertyIndex)
{
	
	FRepSection NewRepSection;
	NewRepSection.ComentTextZoneSizeY = MultiplyTextSize;



	if (ShouldUpdate == EShouldUpdate::none) ShouldUpdate = EShouldUpdate::inRep;


	if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic].RepSection.Num() == 0)   // no-one element
	{
		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic].RepSection.Add(NewRepSection);
	}
	else if (PropertyIndex.iRep == DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic].RepSection.Num() - 1)  // // if it's last element
	{
		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic].RepSection.Add(NewRepSection);
	}

	else
	{
		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic].RepSection.Insert(NewRepSection, PropertyIndex.iRep + 1);
	}


	if (ShouldUpdate == EShouldUpdate::inRep)
	{
		UpdateDialogBlock();
		ShouldUpdate = EShouldUpdate::none;
	}
}


//  =====================  Add Mew RESPONSE Section  =====================
//void SDialogWindowWidget::AddResponseSection(int32 _DialogIndex, int32 _SpeechIndex, int32 _ResponseIndex)
void SDialogWindowWidget::AddResponseSection(FPropertyIndex PropertyIndex)
{
	
	FResponseSection NewResponseSection;
	NewResponseSection.ComentTextZoneSizeY = MultiplyTextSize;

	if (ShouldUpdate == EShouldUpdate::none) ShouldUpdate = EShouldUpdate::inResponse;


	if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ResponseSection.Num() == 0)   // no-one element
	{
		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ResponseSection.Add(NewResponseSection);
	}
	else if (PropertyIndex.iResponse == DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ResponseSection.Num() - 1)  // if it's last element
	{
		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ResponseSection.Add(NewResponseSection);
	}

	else
	{
		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ResponseSection.Insert(NewResponseSection, PropertyIndex.iResponse + 1);
	}

	if (ShouldUpdate == EShouldUpdate::inResponse)
	{
		UpdateDialogBlock();
		ShouldUpdate = EShouldUpdate::none;
	}
}


void SDialogWindowWidget::AddSpeechCondition(FPropertyIndex PropertyIndex)
{

	if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].SpeechCondition.Num() == 0)   // no-one element
	{
		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].SpeechCondition.Add(FCondition());
	}
	else if (PropertyIndex.iSpeechCondition == DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].SpeechCondition.Num() - 1)  // if it's last element
	{
		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].SpeechCondition.Add(FCondition());
	}
	else
	{
		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].SpeechCondition.Insert(FCondition(), PropertyIndex.iSpeechCondition + 1);
	}

	UpdateDialogBlock();
}

void SDialogWindowWidget::AddResponseCondition(FPropertyIndex PropertyIndex) 
{
	if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ResponseSection[PropertyIndex.iResponse]
																							.ResponseCondition.Num() == 0)   // no-one element
	{
		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ResponseSection[PropertyIndex.iResponse]
																								.ResponseCondition.Add(FCondition());
	}
	else if (PropertyIndex.iResponseCondition == DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]    //iRepOrResponsCondition
										.ResponseSection[PropertyIndex.iResponse].ResponseCondition.Num() - 1)  // if it's last element
	{
		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ResponseSection[PropertyIndex.iResponse]
			.ResponseCondition.Add(FCondition());
	}
	else
	{
		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ResponseSection[PropertyIndex.iResponse]
															.ResponseCondition.Insert(FCondition(), PropertyIndex.iResponseCondition + 1);  // iRepOrResponsCondition
	}

	UpdateDialogBlock();
}

void SDialogWindowWidget::AddResponseVariable(FPropertyIndex PropertyIndex)
{
	if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ResponseSection[PropertyIndex.iResponse]
		.VariableSection.Num() == 0)   // no-one element
	{
		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ResponseSection[PropertyIndex.iResponse]
			.VariableSection.Add(FVariables());
	}
	else if (PropertyIndex.iResponseVariable == DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]    //iRepOrResponsCondition
		.ResponseSection[PropertyIndex.iResponse].VariableSection.Num() - 1)  // if it's last element
	{
		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ResponseSection[PropertyIndex.iResponse]
			.VariableSection.Add(FVariables());
	}
	else
	{
		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ResponseSection[PropertyIndex.iResponse]
			.VariableSection.Insert(FVariables(), PropertyIndex.iResponseVariable + 1);  // iRepOrResponsCondition
	}

	UpdateDialogBlock();
}

void SDialogWindowWidget::AddReplicCondition(FPropertyIndex PropertyIndex)
{
	if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic]
																									.ReplicCondition.Num() == 0)   // no-one element
	{
		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic]
																									.ReplicCondition.Add(FCondition());
	}
	else if (PropertyIndex.iReplicCondition == DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
												.ReplicSection[PropertyIndex.iReplic].ReplicCondition.Num() - 1)  // if it's last element
	{
		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic]
			.ReplicCondition.Add(FCondition());
	}
	else
	{
		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic]
			.ReplicCondition.Insert(FCondition(), PropertyIndex.iReplicCondition + 1);
	}

	UpdateDialogBlock();
}

void SDialogWindowWidget::AddRepCondition(FPropertyIndex PropertyIndex)
{

	if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic]
		.RepSection[PropertyIndex.iRep].RepCondition.Num() == 0)   // no-one element
	{
		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic]
			.RepSection[PropertyIndex.iRep].RepCondition.Add(FCondition());
	}
	else if (PropertyIndex.iRepCondition == DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic]
		.RepSection[PropertyIndex.iRep].RepCondition.Num() - 1)  // if it's last element
	{
		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic]
			.RepSection[PropertyIndex.iRep].RepCondition.Add(FCondition());
	}
	else
	{
		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic]
			.RepSection[PropertyIndex.iRep].RepCondition.Insert(FCondition(), PropertyIndex.iRepCondition + 1);
	}

	UpdateDialogBlock();

}

void SDialogWindowWidget::SwitchCollapsedSection(EProppertyToChange _ProppertyToChange, FPropertyIndex PropertyIndex)
{
	
	



	if (_ProppertyToChange == EProppertyToChange::CollapsedResponse_Variables)   
	{
		//  if NoOne Variables ->> Add one and Open Condition-Block
		if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ResponseSection[PropertyIndex.iResponse]
																						.VariableSection.Num() == 0)
		{
			AddResponseVariable(PropertyIndex);

			DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ResponseSection[PropertyIndex.iResponse]
																						.IsVariableOpen = true;
		}
		else
		{
			//bool = !bool
			DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ResponseSection[PropertyIndex.iResponse]
																						.IsVariableOpen =
				!DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ResponseSection[PropertyIndex.iResponse]
																						.IsVariableOpen;

		}
	}
	else if (_ProppertyToChange == EProppertyToChange::CollapsedSpeech_Condition)
	{
		//  if NoOne condition ->> Add one and Open Condition-Block
		if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].SpeechCondition.Num() == 0)
		{
			AddSpeechCondition(PropertyIndex);

			DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].IsConditionOpen = true;
		}
		else
		{
			//bool = !bool
			DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].IsConditionOpen = 
				!DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].IsConditionOpen;

		}
	}
	else if (_ProppertyToChange == EProppertyToChange::CollapsedResponse_Condition)
	{
		//  if NoOne condition ->> Add one and Open Condition-Block
		if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ResponseSection[PropertyIndex.iResponse]
																						.ResponseCondition.Num() == 0)
		{
			AddResponseCondition(PropertyIndex);   

			DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ResponseSection[PropertyIndex.iResponse]
																													.IsConditionOpen = true;
		}
		else
		{
			//bool = !bool
			DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ResponseSection[PropertyIndex.iResponse]
										.IsConditionOpen = !DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
																	.ResponseSection[PropertyIndex.iResponse].IsConditionOpen;

		}
	}
	else if (_ProppertyToChange == EProppertyToChange::CollapsedReplic_Condition)
	{
		//  if NoOne condition ->> Add one and Open Condition-Block
		if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic]
																											.ReplicCondition.Num() == 0)
		{
			AddReplicCondition(PropertyIndex);   

			DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic]
																													.IsConditionOpen = true;
		}
		else
		{
			//bool = !bool
			DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic]
									.IsConditionOpen = !DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
																	.ReplicSection[PropertyIndex.iReplic].IsConditionOpen;
		}
	}
	else if (_ProppertyToChange == EProppertyToChange::CollapsedRep_Condition)
	{
		//  if NoOne condition ->> Add one and Open Condition-Block
		if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic].
												RepSection[PropertyIndex.iRep].RepCondition.Num() == 0)
		{
			AddRepCondition(PropertyIndex);

			DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic].
				RepSection[PropertyIndex.iRep].IsConditionOpen = true;
		}
		else 
		{
			//bool = !bool
			DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic]
			.RepSection[PropertyIndex.iRep].IsConditionOpen = !DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
			.ReplicSection[PropertyIndex.iReplic].RepSection[PropertyIndex.iRep].IsConditionOpen;

		}
	}

	else if (_ProppertyToChange == EProppertyToChange::CollapsedReplicSection)
	{
		//bool = !bool
		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic].IsSectionOpen = 
			!DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic].IsSectionOpen;

		// --------------   if Speech-Section has Markered-Child  =>> swetch on marker   -------------------
		// if open
		if (!DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
										.ReplicSection[PropertyIndex.iReplic].IsSectionOpen)
		{
			for (int32 i_Rep = 0; i_Rep < DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
				.ReplicSection[PropertyIndex.iReplic].RepSection.Num(); i_Rep++)
			{
				//   draw  "IsUsualMarker"
				if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
						.ReplicSection[PropertyIndex.iReplic].RepSection[i_Rep].IsUsualMarker)
				{
					DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
										.ReplicSection[PropertyIndex.iReplic].IsUsualMarker = true;
					break;
				}
			}
		}
		// if close  
		if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic].IsSectionOpen)
		{
			//   don't draw  "IsUsualMarker"
			if (!DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic].IsSelfUsualMarker)
			{
				DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic].IsUsualMarker = false;
			}
		}
		
	}
	else if (_ProppertyToChange == EProppertyToChange::CollapsedSpeechSection)
	{
		//bool = !bool
		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].IsSectionOpen = !DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].IsSectionOpen;

		// --------------   if Speech-Section has Markered-Child  =>> swetch on marker   -------------------
		// if open
		if (!DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].IsSectionOpen)
		{
			for (int32 i_Response = 0; i_Response < DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
				.ResponseSection.Num(); i_Response++)
			{
				//   draw "IsDestinationMarker"
				if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
																.ResponseSection[i_Response].IsLinkMarker)
					//!DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].IsSectionOpen)
				{
					DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].IsDestinationMarker = true;
					break;
				}
				//   draw  "IsUsualMarker"
				else if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
																.ResponseSection[i_Response].IsUsualMarker)
						//!DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].IsSectionOpen)
				{
					DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].IsUsualMarker = true;
					break;
				}
			}
			for (int32 i_Replic = 0; i_Replic < DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
																							.ReplicSection.Num(); i_Replic++)
			{
				//   draw  "IsUsualMarker"
				if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[i_Replic].IsUsualMarker)
					//!DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].IsSectionOpen)
				{
					DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].IsUsualMarker = true;
					break;
				}

				for (int32 i_Rep = 0; i_Rep < DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
																	.ReplicSection[i_Replic].RepSection.Num(); i_Rep++)
				{
					//   draw  "IsUsualMarker"
					if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
											.ReplicSection[i_Replic].RepSection[i_Rep].IsUsualMarker)
						//!DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].IsSectionOpen)
					{
						DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].IsUsualMarker = true;
						break;
					}
				}
			}
		}
		// if close  
		else //if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].IsSectionOpen)
		{
			//   don't draw  "IsDestinationMarker"
			if (!DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].IsSelfLinkMarker)
			{
				DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].IsDestinationMarker = false;
			}
			//   don't draw  "IsUsualMarker"
			if (!DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].IsSelfUsualMarker)
			{
				DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].IsUsualMarker = false;
			}
		}
	}
	else if (_ProppertyToChange == EProppertyToChange::CollapsedDialogSection)
	{
		//bool = !bool
		DialogSection[PropertyIndex.iDialog].IsSectionOpen = !DialogSection[PropertyIndex.iDialog].IsSectionOpen;

		// --------------   if Diagog-Section has Markered Child  =>> swetch on marker   -------------------
		// if open
		if (!DialogSection[PropertyIndex.iDialog].IsSectionOpen)
		{
			for (int32 i_Speech = 0; i_Speech < DialogSection[PropertyIndex.iDialog].SpeechSection.Num(); i_Speech++)
			{
				// if Speech "IsLinkMarker"
				if (DialogSection[PropertyIndex.iDialog].SpeechSection[i_Speech].IsLinkMarker)
				{
					DialogSection[PropertyIndex.iDialog].IsLinkMarker = true;
					break;
				}
				// if Speech->EACH_Response "IsDestinationMarker(IsLinkMarker)"
				for (int32 i_Response = 0; i_Response < DialogSection[PropertyIndex.iDialog].SpeechSection[i_Speech]
																				.ResponseSection.Num(); i_Response++)
				{
					if (DialogSection[PropertyIndex.iDialog].SpeechSection[i_Speech].ResponseSection[i_Response].IsLinkMarker)
					{
						DialogSection[PropertyIndex.iDialog].IsDestinationMarker = true;
						break;
					}
				}
			}

			for (int32 i_Speech = 0; i_Speech < DialogSection[PropertyIndex.iDialog].SpeechSection.Num(); i_Speech++)
			{

				//if (!DialogSection[PropertyIndex.iDialog].IsSectionOpen)
				//{
					//   draw "IsUsualMarker"
					if (DialogSection[PropertyIndex.iDialog].SpeechSection[i_Speech].IsUsualMarker)
						//!DialogSection[PropertyIndex.iDialog].IsSectionOpen)
					{
						DialogSection[PropertyIndex.iDialog].IsUsualMarker = true;
						break;
					}

					for (int32 i_Response = 0; i_Response < DialogSection[PropertyIndex.iDialog].SpeechSection[i_Speech]
																					.ResponseSection.Num(); i_Response++)
					{
						//   draw "IsUsualMarker"
						if (DialogSection[PropertyIndex.iDialog].SpeechSection[i_Speech].ResponseSection[i_Response].IsUsualMarker)
							//!DialogSection[PropertyIndex.iDialog].IsSectionOpen)
						{
							DialogSection[PropertyIndex.iDialog].IsUsualMarker = true;
							break;
						}
					}
					for (int32 i_Replic = 0; i_Replic < DialogSection[PropertyIndex.iDialog].SpeechSection[i_Speech]
						.ReplicSection.Num(); i_Replic++)
					{
						//   draw "IsUsualMarker"
						if (DialogSection[PropertyIndex.iDialog].SpeechSection[i_Speech].ReplicSection[i_Replic].IsUsualMarker)
							//!DialogSection[PropertyIndex.iDialog].IsSectionOpen)
						{
							DialogSection[PropertyIndex.iDialog].IsUsualMarker = true;
							break;
						}

						for (int32 i_Rep = 0; i_Rep < DialogSection[PropertyIndex.iDialog].SpeechSection[i_Speech]
							.ReplicSection[i_Replic].RepSection.Num(); i_Rep++)
						{
							//   draw "IsUsualMarker"
							if (DialogSection[PropertyIndex.iDialog].SpeechSection[i_Speech].ReplicSection[i_Replic]
																					.RepSection[i_Rep].IsUsualMarker)
								//!DialogSection[PropertyIndex.iDialog].IsSectionOpen)
							{
								DialogSection[PropertyIndex.iDialog].IsUsualMarker = true;
								break;
							}
						}
					}
				//}
			}
		}
		// if close
		else // if(DialogSection[PropertyIndex.iDialog].IsSectionOpen)
		{
			if (!DialogSection[PropertyIndex.iDialog].IsSelfLinkMarker)
			{
				DialogSection[PropertyIndex.iDialog].IsLinkMarker = false;
				DialogSection[PropertyIndex.iDialog].IsDestinationMarker = false;
			}
			if (!DialogSection[PropertyIndex.iDialog].IsSelfUsualMarker)
			{
				DialogSection[PropertyIndex.iDialog].IsUsualMarker = false;
			}
		}		
	}

	RedrawIndicator();
}



void SDialogWindowWidget::OnEditableTextChange(const FText& _Text)
{
	EditableChangedText = _Text.ToString();
}



void SDialogWindowWidget::ConfirmCurrentSelection(EProppertyToChange changingPropperty, FPropertyIndex PropertyIndex)
{
	
	//     ---------------      Variable    variavle-Block --------------------------------
	if (changingPropperty == EProppertyToChange::Variable_varName)
	{
		if (EditableChangedText != FString(""))
		{
			Variables[PropertyIndex.iVariable].VariableName = FName(*EditableChangedText);   //iRepOrResponsCondition
			EditableChangedText = FString("");
		}
		Variables[PropertyIndex.iVariable].IsProperty_VariableName_EditNow = false;  //iRepOrResponsCondition
	}

	if (changingPropperty == EProppertyToChange::Variable_varValue)
	{
		if (EditableChangedText != FString(""))
		{
			Variables[PropertyIndex.iVariable].VariableValue = FName(*EditableChangedText);  //iRepOrResponsCondition
			EditableChangedText = FString("");
		}
		Variables[PropertyIndex.iVariable].IsProperty_VariableValue_EditNow = false;   //iRepOrResponsCondition
	}


	//     ---------------      Response_Variable  section --------------------------------
	if (changingPropperty == EProppertyToChange::Response_variable_varName)
	{
		if (EditableChangedText != FString(""))
		{
			DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ResponseSection[PropertyIndex.iResponse]
				.VariableSection[PropertyIndex.iResponseVariable].VariableName = FName(*EditableChangedText);   //iRepOrResponsCondition
			EditableChangedText = FString("");
		}
		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ResponseSection[PropertyIndex.iResponse]
			.VariableSection[PropertyIndex.iResponseVariable].IsProperty_VariableName_EditNow = false;  //iRepOrResponsCondition
	}

	if (changingPropperty == EProppertyToChange::Response_variable_varValue)
	{
		if (EditableChangedText != FString(""))
		{
			DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ResponseSection[PropertyIndex.iResponse]
				.VariableSection[PropertyIndex.iResponseVariable].VariableValue = FName(*EditableChangedText);  //iRepOrResponsCondition
			EditableChangedText = FString("");
		}
		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ResponseSection[PropertyIndex.iResponse]
			.VariableSection[PropertyIndex.iResponseVariable].IsProperty_VariableValue_EditNow = false;   //iRepOrResponsCondition
	}

	
	//     ---------------      Response_condition  section --------------------------------
	if (changingPropperty == EProppertyToChange::Response_condition_varName)
	{
		if (EditableChangedText != FString(""))
		{
			DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ResponseSection[PropertyIndex.iResponse]
				.ResponseCondition[PropertyIndex.iResponseCondition].VariableName = FName(*EditableChangedText);   //iRepOrResponsCondition
			EditableChangedText = FString("");
		}
		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ResponseSection[PropertyIndex.iResponse]
			.ResponseCondition[PropertyIndex.iResponseCondition].IsProperty_VariableName_EditNow = false;  //iRepOrResponsCondition
	}

	if (changingPropperty == EProppertyToChange::Response_condition_varValue)
	{
		if (EditableChangedText != FString(""))
		{
			DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ResponseSection[PropertyIndex.iResponse]
				.ResponseCondition[PropertyIndex.iResponseCondition].VariableValue = FName(*EditableChangedText);  //iRepOrResponsCondition
			EditableChangedText = FString("");
		}
		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ResponseSection[PropertyIndex.iResponse]
			.ResponseCondition[PropertyIndex.iResponseCondition].IsProperty_VariableValue_EditNow = false;   //iRepOrResponsCondition
	}

	if (changingPropperty == EProppertyToChange::Response_condition_type)
	{
		if (EditableChangedText != FString(""))
		{
			DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ResponseSection[PropertyIndex.iResponse]
				.ResponseCondition[PropertyIndex.iResponseCondition].ConditionType = FName(*EditableChangedText);   //iRepOrResponsCondition
			EditableChangedText = FString("");
		}

		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ResponseSection[PropertyIndex.iResponse]
			.ResponseCondition[PropertyIndex.iResponseCondition].IsProperty_Type_EditNow = false;   //iRepOrResponsCondition
	}


	//     ---------------      replic_condition  section --------------------------------
	if (changingPropperty == EProppertyToChange::Replic_condition_varName)
	{
		if (EditableChangedText != FString(""))
		{
			DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic]
				.ReplicCondition[PropertyIndex.iReplicCondition].VariableName = FName(*EditableChangedText);
			EditableChangedText = FString("");
		}
		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic]
			.ReplicCondition[PropertyIndex.iReplicCondition].IsProperty_VariableName_EditNow = false;
	}

	if (changingPropperty == EProppertyToChange::Replic_condition_varValue)
	{
		if (EditableChangedText != FString(""))
		{
			DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic]
				.ReplicCondition[PropertyIndex.iReplicCondition].VariableValue = FName(*EditableChangedText);
			EditableChangedText = FString("");
		}
		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic]
			.ReplicCondition[PropertyIndex.iReplicCondition].IsProperty_VariableValue_EditNow = false;
	}

	if (changingPropperty == EProppertyToChange::Replic_condition_type)
	{
		if (EditableChangedText != FString(""))
		{
			DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic]
				.ReplicCondition[PropertyIndex.iReplicCondition].ConditionType = FName(*EditableChangedText);
			EditableChangedText = FString("");
		}

		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic]
			.ReplicCondition[PropertyIndex.iReplicCondition].IsProperty_Type_EditNow = false;
	}


	 //     ---------------      rep_condition  section --------------------------------
	if (changingPropperty == EProppertyToChange::rep_condition_varName)
	{
		if (EditableChangedText != FString(""))
		{
			DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic]
					.RepSection[PropertyIndex.iRep].RepCondition[PropertyIndex.iRepCondition].VariableName = FName(*EditableChangedText);
			EditableChangedText = FString("");
		}
		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic]
			.RepSection[PropertyIndex.iRep].RepCondition[PropertyIndex.iRepCondition].IsProperty_VariableName_EditNow = false;
	}

	if (changingPropperty == EProppertyToChange::rep_condition_varValue)
	{
		if (EditableChangedText != FString(""))
		{
			DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic]
				.RepSection[PropertyIndex.iRep].RepCondition[PropertyIndex.iRepCondition].VariableValue = FName(*EditableChangedText);
			EditableChangedText = FString("");
		}
		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic]
			.RepSection[PropertyIndex.iRep].RepCondition[PropertyIndex.iRepCondition].IsProperty_VariableValue_EditNow = false;
	}

	if (changingPropperty == EProppertyToChange::rep_condition_type)
	{
		if (EditableChangedText != FString(""))
		{
			DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic]
				.RepSection[PropertyIndex.iRep].RepCondition[PropertyIndex.iRepCondition].ConditionType = FName(*EditableChangedText);
			EditableChangedText = FString("");
		}

		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic]
			.RepSection[PropertyIndex.iRep].RepCondition[PropertyIndex.iRepCondition].IsProperty_Type_EditNow = false;
	}


	//     ---------------      Speech_condition  section --------------------------------
	if (changingPropperty == EProppertyToChange::Speech_condition_varName)
	{
		if (EditableChangedText != FString(""))
		{
			DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].SpeechCondition[PropertyIndex.iSpeechCondition].VariableName = FName(*EditableChangedText);
			EditableChangedText = FString("");
		}
		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].SpeechCondition[PropertyIndex.iSpeechCondition].IsProperty_VariableName_EditNow = false;
	}

	if (changingPropperty == EProppertyToChange::Speech_condition_varValue)
	{
		if (EditableChangedText != FString(""))
		{
			DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].SpeechCondition[PropertyIndex.iSpeechCondition]
																							.VariableValue = FName(*EditableChangedText);
			EditableChangedText = FString("");
		}
		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].SpeechCondition[PropertyIndex.iSpeechCondition].IsProperty_VariableValue_EditNow = false;
	}

	if (changingPropperty == EProppertyToChange::Speech_condition_type)
	{
		if (EditableChangedText != FString(""))
		{
			DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].SpeechCondition[PropertyIndex.iSpeechCondition]
																							.ConditionType = FName(*EditableChangedText);
			EditableChangedText = FString("");
		}

		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].SpeechCondition[PropertyIndex.iSpeechCondition]
																								.IsProperty_Type_EditNow = false;
	}




	//--------------------------------------------------------

	if (changingPropperty == EProppertyToChange::RepEvent) //PropertyIndex.iSpeech != -1)
	{
		//DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ChangeSpeechSectionName_Button->ButtonHitted = EVisibility::Visible;
		if (EditableChangedText != FString(""))
		{
			DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic]
														.RepSection[PropertyIndex.iRep].RepEvent = EditableChangedText;
			EditableChangedText = FString("");
		}
		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic]
												.RepSection[PropertyIndex.iRep].isEventPropertyEditNow = false;
	}
	

	if (changingPropperty == EProppertyToChange::SpeechName) //PropertyIndex.iSpeech != -1)
	{
		//DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ChangeSpeechSectionName_Button->ButtonHitted = EVisibility::Visible;
		if (EditableChangedText != FString(""))
		{
			DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].Name = FName(*EditableChangedText);
			EditableChangedText = FString("");
		}
		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].IsSectionEditNow = false;
	}
	if (changingPropperty == EProppertyToChange::DialogName) //PropertyIndex.iDialog != -1 )
	{
		//DialogSection[PropertyIndex.iDialog].ChangeDialodSectionName_Button->ButtonHitted = EVisibility::Visible;
		if (EditableChangedText != FString("") && EditableChangedText != FString("DEFAULT"))
		{
			DialogSection[PropertyIndex.iDialog].Name = FName(*EditableChangedText);			
		}
		EditableChangedText = FString("");

		DialogSection[PropertyIndex.iDialog].IsSectionEditNow = false;
	}


	if (changingPropperty == EProppertyToChange::SpekerinSpekerBlock)  //  Speaker Block
	{
		// XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX       APPEARS OR HIDDEN    EDITING_ZONE
		if (EditableChangedText != FString(""))
		{
			Speker[PropertyIndex.SpekerIndex].name = FName(*EditableChangedText);
			EditableChangedText = FString("");

			SaveSpekersToXML();
		}
		Speker[PropertyIndex.SpekerIndex].IsSectionEditNow = false;
	}


	iCurrentEditableSpeker = -1;   //  Saved SPEKER to aplay ASSET-IMAGE and when editable
}




EVisibility SDialogWindowWidget::GetVisibility_LocalVarIndicator(EProppertyToChange _ProppertyToChange, FPropertyIndex PropertyIndex) const
{

	if (_ProppertyToChange == EProppertyToChange::Response_variable_varType)
	{
		if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ResponseSection[PropertyIndex.iResponse]
			.VariableSection[PropertyIndex.iResponseVariable].isVariableGlobal) 	 return EVisibility::Collapsed; //iRepOrResponsCondition
		else																															 return EVisibility::Visible;
	}
	else if (_ProppertyToChange == EProppertyToChange::Response_variable_varType)
	{
		if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ResponseSection[PropertyIndex.iResponse]
																.VariableSection[PropertyIndex.iResponseVariable].isVariableGlobal) 	 return EVisibility::Collapsed;
		else																															 return EVisibility::Visible;
	}
	if (_ProppertyToChange == EProppertyToChange::rep_condition_varType)
	{
		if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic]
						.RepSection[PropertyIndex.iRep].RepCondition[PropertyIndex.iRepCondition].isVariableGlobal) 	 return EVisibility::Collapsed;
		else																															 return EVisibility::Visible;
	}
	else if (_ProppertyToChange == EProppertyToChange::Replic_condition_varType)
	{
		if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic]
																	.ReplicCondition[PropertyIndex.iReplicCondition].isVariableGlobal) 	 return EVisibility::Collapsed;
		else																															 return EVisibility::Visible;
	}
	else if (_ProppertyToChange == EProppertyToChange::Response_condition_varType)
	{
		if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ResponseSection[PropertyIndex.iResponse]
																.ResponseCondition[PropertyIndex.iResponseCondition].isVariableGlobal) 	 return EVisibility::Collapsed; //iRepOrResponsCondition
		else																															 return EVisibility::Visible;
	}
	else if (_ProppertyToChange == EProppertyToChange::Speech_condition_varType)
	{
		if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
																	.SpeechCondition[PropertyIndex.iSpeechCondition].isVariableGlobal) 	 return EVisibility::Collapsed;
		else																															 return EVisibility::Visible;
	}

	return EVisibility::Visible;
}


EVisibility SDialogWindowWidget::GetVisibility_GlobalVarIndicator(EProppertyToChange _ProppertyToChange, FPropertyIndex PropertyIndex) const
{

	
	if (_ProppertyToChange == EProppertyToChange::Response_variable_varType)
	{
		if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ResponseSection[PropertyIndex.iResponse]
																.VariableSection[PropertyIndex.iResponseVariable].isVariableGlobal) 	 return EVisibility::Visible; //iRepOrResponsCondition
		else																															 return EVisibility::Collapsed;
	}
	else if (_ProppertyToChange == EProppertyToChange::rep_condition_varType)
	{
		if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic]
						.RepSection[PropertyIndex.iRep].RepCondition[PropertyIndex.iRepCondition].isVariableGlobal) 	 return EVisibility::Visible;
		else																															 return EVisibility::Collapsed;
	}
	else if (_ProppertyToChange == EProppertyToChange::Replic_condition_varType)
	{
		if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic]
																	.ReplicCondition[PropertyIndex.iReplicCondition].isVariableGlobal) 	 return EVisibility::Visible;
		else																															 return EVisibility::Collapsed;
	}
	else if (_ProppertyToChange == EProppertyToChange::Response_condition_varType)
	{
		if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ResponseSection[PropertyIndex.iResponse]
															.ResponseCondition[PropertyIndex.iResponseCondition].isVariableGlobal) 	 return EVisibility::Visible; //iRepOrResponsCondition
		else																															 return EVisibility::Collapsed;
	}
	else if (_ProppertyToChange == EProppertyToChange::Speech_condition_varType)
	{
		if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
																	.SpeechCondition[PropertyIndex.iSpeechCondition].isVariableGlobal) 	 return EVisibility::Visible;
		else																															 return EVisibility::Collapsed;
	}
	return EVisibility::Visible;
}




EVisibility SDialogWindowWidget::GetVisibilityOfSectionPropperty_Static(EProppertyToChange _ProppertyToChange, FPropertyIndex PropertyIndex) const
{
	//    -----------------------  Variable      Variable--Block  -----------------------
	if (_ProppertyToChange == EProppertyToChange::Variable_varName)
	{
	if (Variables[PropertyIndex.iVariable].IsProperty_VariableName_EditNow)				return EVisibility::Collapsed;   
	else																				return EVisibility::Visible;
	}
	else if (_ProppertyToChange == EProppertyToChange::Variable_varValue)
	{
	if (Variables[PropertyIndex.iVariable].IsProperty_VariableValue_EditNow)			 return EVisibility::Collapsed;    
	else																				 return EVisibility::Visible;
	}


	//    -----------------------  Speech-Condition_Section  -----------------------
	if (_ProppertyToChange == EProppertyToChange::Speech_condition_type)
	{
		if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].SpeechCondition[PropertyIndex.iSpeechCondition]
																											.IsProperty_Type_EditNow)	return EVisibility::Collapsed;
		else																															return EVisibility::Visible;
	}
	else if (_ProppertyToChange == EProppertyToChange::Speech_condition_varName)
	{
		if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].SpeechCondition[PropertyIndex.iSpeechCondition]
																									.IsProperty_VariableName_EditNow)	return EVisibility::Collapsed;
		else																															return EVisibility::Visible;
	}
	else if (_ProppertyToChange == EProppertyToChange::Speech_condition_varValue)
	{
		if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].SpeechCondition[PropertyIndex.iSpeechCondition]
																									.IsProperty_VariableValue_EditNow)	return EVisibility::Collapsed;
		else																															return EVisibility::Visible;
	}

	//    -----------------------  Rep-Condition_Section  -----------------------
	if (_ProppertyToChange == EProppertyToChange::rep_condition_type)
	{
		if(DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic]
				.RepSection[PropertyIndex.iRep].RepCondition[PropertyIndex.iRepCondition].IsProperty_Type_EditNow)	return EVisibility::Collapsed;
		else																															return EVisibility::Visible;
	}
	else if (_ProppertyToChange == EProppertyToChange::rep_condition_varName)
	{
		if(DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic]
														.RepSection[PropertyIndex.iRep]
															.RepCondition[PropertyIndex.iRepCondition].IsProperty_VariableName_EditNow)	return EVisibility::Collapsed;
		else																															return EVisibility::Visible;
	}
	else if (_ProppertyToChange == EProppertyToChange::rep_condition_varValue)
	{
		if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic]
														.RepSection[PropertyIndex.iRep]
														.RepCondition[PropertyIndex.iRepCondition].IsProperty_VariableValue_EditNow)	return EVisibility::Collapsed;
		else																															return EVisibility::Visible;
	}

	//    -----------------------  Replic-Condition_Section  -----------------------
	if (_ProppertyToChange == EProppertyToChange::Replic_condition_type)
	{
		if(DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic]
																.ReplicCondition[PropertyIndex.iReplicCondition].IsProperty_Type_EditNow)	return EVisibility::Collapsed;
		else																															return EVisibility::Visible;
	}
	else if (_ProppertyToChange == EProppertyToChange::Replic_condition_varName)
	{
		if(DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic]
														.ReplicCondition[PropertyIndex.iReplicCondition].IsProperty_VariableName_EditNow)	return EVisibility::Collapsed;
		else																															return EVisibility::Visible;
	}
	else if (_ProppertyToChange == EProppertyToChange::Replic_condition_varValue)
	{
		if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic]
														.ReplicCondition[PropertyIndex.iReplicCondition].IsProperty_VariableValue_EditNow)	return EVisibility::Collapsed;
		else																															return EVisibility::Visible;
	}

	//    -----------------------  Response-Condition_Section  -----------------------
	if (_ProppertyToChange == EProppertyToChange::Response_condition_type)
	{
		if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ResponseSection[PropertyIndex.iResponse]
															.ResponseCondition[PropertyIndex.iResponseCondition].IsProperty_Type_EditNow)	return EVisibility::Collapsed;  //iRepOrResponsCondition
		else																															return EVisibility::Visible;
	}
	else if (_ProppertyToChange == EProppertyToChange::Response_condition_varName)
	{
		if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ResponseSection[PropertyIndex.iResponse]
												.ResponseCondition[PropertyIndex.iResponseCondition].IsProperty_VariableName_EditNow)	return EVisibility::Collapsed;  //iRepOrResponsCondition
		else																															return EVisibility::Visible;
	}
	else if (_ProppertyToChange == EProppertyToChange::Response_condition_varValue)
	{
		if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ResponseSection[PropertyIndex.iResponse]
												.ResponseCondition[PropertyIndex.iResponseCondition].IsProperty_VariableValue_EditNow)	return EVisibility::Collapsed; //iRepOrResponsCondition
		else																															return EVisibility::Visible;
	}

	//    -----------------------  Response-Condition_Section  -----------------------
	else if (_ProppertyToChange == EProppertyToChange::Response_variable_varName)
	{
		if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ResponseSection[PropertyIndex.iResponse]
			.VariableSection[PropertyIndex.iResponseVariable].IsProperty_VariableName_EditNow)											return EVisibility::Collapsed;   //iRepOrResponsCondition
		else																															return EVisibility::Visible;
	}
	else if (_ProppertyToChange == EProppertyToChange::Response_variable_varValue)
	{
		if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ResponseSection[PropertyIndex.iResponse]
			.VariableSection[PropertyIndex.iResponseVariable].IsProperty_VariableValue_EditNow)											 return EVisibility::Collapsed;    //iRepOrResponsCondition
		else																															return EVisibility::Visible;
	}




	else if (_ProppertyToChange == EProppertyToChange::repeatResponse)// && changingPropperty == EProppertyToChange::repeatResponse &&
							//_SpeechIndex != -1 && _DialogIndex != -1, _ReplicOrResponseIndex != -1)
	{
		if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
							.ResponseSection[PropertyIndex.iResponse].IsSectionEditNow)			return EVisibility::Collapsed;
		else																							return EVisibility::Visible;
	}




	else if (_ProppertyToChange == EProppertyToChange::RepEvent)
	{
		if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic]
												.RepSection[PropertyIndex.iRep].isEventPropertyEditNow)		return EVisibility::Collapsed;
		else																								return EVisibility::Visible;
	}

	else if (_ProppertyToChange == EProppertyToChange::SpeechName)
	{
		if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].IsSectionEditNow)		return EVisibility::Collapsed;
		else																								return EVisibility::Visible;
	}
	else if (_ProppertyToChange == EProppertyToChange::DialogName)
	{
		if (DialogSection[PropertyIndex.iDialog].IsSectionEditNow)											return EVisibility::Collapsed;
		else																								return EVisibility::Visible;
	}


	return EVisibility::Visible;
}

EVisibility SDialogWindowWidget::GetVisibilityOfSectionPropperty_Editable(EProppertyToChange _ProppertyToChange, FPropertyIndex PropertyIndex) const
{


	
	//    -----------------------  Variable      Variable--Block  -----------------------
	if (_ProppertyToChange == EProppertyToChange::Variable_varName)
	{
		if (Variables[PropertyIndex.iVariable].IsProperty_VariableName_EditNow)				return EVisibility::Visible;   //iRepOrResponsCondition
		else																				return EVisibility::Collapsed;
	}
	else if (_ProppertyToChange == EProppertyToChange::Variable_varValue)
	{
		if (Variables[PropertyIndex.iVariable].IsProperty_VariableValue_EditNow)			 return EVisibility::Visible;    //iRepOrResponsCondition
		else																				 return EVisibility::Collapsed;
	}

	 
	//    -----------------------  Speech-Condition_Section  -----------------------
	if (_ProppertyToChange == EProppertyToChange::Speech_condition_type)
	{
		if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].SpeechCondition[PropertyIndex.iSpeechCondition]
																										.IsProperty_Type_EditNow)		return EVisibility::Visible;
		else																															return EVisibility::Collapsed;
	}
	else if (_ProppertyToChange == EProppertyToChange::Speech_condition_varName)
	{
		if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].SpeechCondition[PropertyIndex.iSpeechCondition]
																									.IsProperty_VariableName_EditNow)	return EVisibility::Visible;
		else																															return EVisibility::Collapsed;
	}
	else if (_ProppertyToChange == EProppertyToChange::Speech_condition_varValue)
	{
		if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].SpeechCondition[PropertyIndex.iSpeechCondition]
																									.IsProperty_VariableValue_EditNow)	return EVisibility::Visible;
		else																															return EVisibility::Collapsed;
	}


	//    -----------------------  Rep-Condition_Section  -----------------------
	if (_ProppertyToChange == EProppertyToChange::rep_condition_type)
	{
		if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic]
			.RepSection[PropertyIndex.iRep].RepCondition[PropertyIndex.iRepCondition].IsProperty_Type_EditNow)		return EVisibility::Visible;
		else																															return EVisibility::Collapsed;
	}
	else if (_ProppertyToChange == EProppertyToChange::rep_condition_varName)
	{
		if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic]
														.RepSection[PropertyIndex.iRep].RepCondition[PropertyIndex
																					.iRepCondition].IsProperty_VariableName_EditNow)	return EVisibility::Visible;
		else																															return EVisibility::Collapsed;
	}
	else if (_ProppertyToChange == EProppertyToChange::rep_condition_varValue)
	{
		if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic]
														.RepSection[PropertyIndex.iRep].RepCondition[PropertyIndex
																					.iRepCondition].IsProperty_VariableValue_EditNow)	return EVisibility::Visible;
		else																															return EVisibility::Collapsed;
	}


	//    -----------------------  Replic-Condition_Section  -----------------------
	if (_ProppertyToChange == EProppertyToChange::Replic_condition_type)
	{
		if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic]
															.ReplicCondition[PropertyIndex.iReplicCondition].IsProperty_Type_EditNow)	return EVisibility::Visible;
		else																															return EVisibility::Collapsed;
	}
	else if (_ProppertyToChange == EProppertyToChange::Replic_condition_varName)
	{
		if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic]
													.ReplicCondition[PropertyIndex.iReplicCondition].IsProperty_VariableName_EditNow)	return EVisibility::Visible;
		else																															return EVisibility::Collapsed;
	}
	else if (_ProppertyToChange == EProppertyToChange::Replic_condition_varValue)
	{
		if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic]
													.ReplicCondition[PropertyIndex.iReplicCondition].IsProperty_VariableValue_EditNow)  return EVisibility::Visible;
		else																															return EVisibility::Collapsed;
	}

	//    -----------------------  Response-Condition_Section  -----------------------
	if (_ProppertyToChange == EProppertyToChange::Response_condition_type)
	{
		if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ResponseSection[PropertyIndex.iResponse]
														.ResponseCondition[PropertyIndex.iResponseCondition].IsProperty_Type_EditNow)	return EVisibility::Visible;  //iRepOrResponsCondition
		else																																return EVisibility::Collapsed;
	}
	else if (_ProppertyToChange == EProppertyToChange::Response_condition_varName)
	{
		if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ResponseSection[PropertyIndex.iResponse]
												.ResponseCondition[PropertyIndex.iResponseCondition].IsProperty_VariableName_EditNow)	return EVisibility::Visible;   //iRepOrResponsCondition
		else																																return EVisibility::Collapsed;
	}
	else if (_ProppertyToChange == EProppertyToChange::Response_condition_varValue)
	{
		if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ResponseSection[PropertyIndex.iResponse]
												.ResponseCondition[PropertyIndex.iResponseCondition].IsProperty_VariableValue_EditNow)  return EVisibility::Visible;    //iRepOrResponsCondition
		else																																return EVisibility::Collapsed;
	}


	//    -----------------------  Response-variable_Section  -----------------------
	else if (_ProppertyToChange == EProppertyToChange::Response_variable_varName)
	{
		if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ResponseSection[PropertyIndex.iResponse]
			.VariableSection[PropertyIndex.iResponseVariable].IsProperty_VariableName_EditNow)	return EVisibility::Visible;   //iRepOrResponsCondition
		else																															return EVisibility::Collapsed;
	}
	else if (_ProppertyToChange == EProppertyToChange::Response_variable_varValue)
	{
		if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ResponseSection[PropertyIndex.iResponse]
			.VariableSection[PropertyIndex.iResponseVariable].IsProperty_VariableValue_EditNow)  return EVisibility::Visible;    //iRepOrResponsCondition
		else																															return EVisibility::Collapsed;
	}




	else if (_ProppertyToChange == EProppertyToChange::repeatResponse)
	{
		if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
							.ResponseSection[PropertyIndex.iResponse].IsSectionEditNow)				return EVisibility::Visible;
		else																								return EVisibility::Collapsed;
	}
	
	else if (_ProppertyToChange == EProppertyToChange::RepEvent)
	{
		if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic]
												.RepSection[PropertyIndex.iRep].isEventPropertyEditNow)		return EVisibility::Visible;
		else																								return EVisibility::Collapsed;
	}

	else if (_ProppertyToChange == EProppertyToChange::SpeechName)
	{
		if (DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].IsSectionEditNow)		return EVisibility::Visible;
		else																								return EVisibility::Collapsed;
	}
	else if (_ProppertyToChange == EProppertyToChange::DialogName)
	{
		if (DialogSection[PropertyIndex.iDialog].IsSectionEditNow)											return EVisibility::Visible;
		else																								return EVisibility::Collapsed;
	}





	return EVisibility::Visible;
}


FText SDialogWindowWidget::GetProppertyText(EProppertyToChange _ProppertyToChange, FPropertyIndex PropertyIndex) const
{


	//    -----------------------    Variable     Variable--Block    -----------------------
	if (_ProppertyToChange == EProppertyToChange::Variable_varName)
	{
		return FText::FromString(Variables[PropertyIndex.iVariable].VariableName.ToString());
	}
	else if (_ProppertyToChange == EProppertyToChange::Variable_varValue)
	{
		return FText::FromString(Variables[PropertyIndex.iVariable].VariableValue.ToString());
	}



	if (_ProppertyToChange == EProppertyToChange::DialogLink)
	{
		return FText::FromString(DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
											.ResponseSection[PropertyIndex.iResponse].DialogLink.ToString());
	}
	else if (_ProppertyToChange == EProppertyToChange::SpeechLink)
	{
		return FText::FromString(DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
											.ResponseSection[PropertyIndex.iResponse].SpeechLink.ToString());
	}



	else if (_ProppertyToChange == EProppertyToChange::speker)
	{
		return FText::FromString(DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic]
			.RepSection[PropertyIndex.iRep].Speker.ToString());
	}
	else if (_ProppertyToChange == EProppertyToChange::sound)
	{
		return FText::FromString(DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic]
			.RepSection[PropertyIndex.iRep].Sound.ToString());
	}
	else if (_ProppertyToChange == EProppertyToChange::time)
	{
		return FText::FromString(DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic]
			.RepSection[PropertyIndex.iRep].Time.ToString());
	}


	//    -----------------------  Speech-Condition_Section  -----------------------
	else if (_ProppertyToChange == EProppertyToChange::Speech_condition_varName)
	{
		return FText::FromString(DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
								.SpeechCondition[PropertyIndex.iSpeechCondition].VariableName.ToString());
	}
	else if (_ProppertyToChange == EProppertyToChange::Speech_condition_varValue)
	{
		return FText::FromString(DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
			.SpeechCondition[PropertyIndex.iSpeechCondition].VariableValue.ToString());
	}

	else if (_ProppertyToChange == EProppertyToChange::Speech_condition_type) 
	{
		return FText::FromString(DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
			.SpeechCondition[PropertyIndex.iSpeechCondition].ConditionType.ToString());
	}
	else if (_ProppertyToChange == EProppertyToChange::Speech_condition_CompareType) 

	{
		return FText::FromString(DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
			.SpeechCondition[PropertyIndex.iSpeechCondition].VariableCompareType.ToString());
	}


	//    -----------------------  Rep-Condition_Section  -----------------------
	else if (_ProppertyToChange == EProppertyToChange::rep_condition_varName)
	{
		return FText::FromString(DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
			.ReplicSection[PropertyIndex.iReplic].RepSection[PropertyIndex.iRep].RepCondition[PropertyIndex.iRepCondition].VariableName.ToString());
	}
	else if (_ProppertyToChange == EProppertyToChange::rep_condition_varValue)
	{
		return FText::FromString(DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
			.ReplicSection[PropertyIndex.iReplic].RepSection[PropertyIndex.iRep].RepCondition[PropertyIndex.iRepCondition].VariableValue.ToString());
	}

	else if (_ProppertyToChange == EProppertyToChange::rep_condition_type)
	{
		return FText::FromString(DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
			.ReplicSection[PropertyIndex.iReplic].RepSection[PropertyIndex.iRep]
			.RepCondition[PropertyIndex.iRepCondition].ConditionType.ToString());
	}
	else if (_ProppertyToChange == EProppertyToChange::rep_condition_CompareType)
	{
		return FText::FromString(DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
			.ReplicSection[PropertyIndex.iReplic].RepSection[PropertyIndex.iRep]
			.RepCondition[PropertyIndex.iRepCondition].VariableCompareType.ToString());
	}

	//    -----------------------  Replic-Condition_Section  -----------------------
	else if (_ProppertyToChange == EProppertyToChange::Replic_condition_varName)
	{
		return FText::FromString(DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
			.ReplicSection[PropertyIndex.iReplic].ReplicCondition[PropertyIndex.iReplicCondition].VariableName.ToString());
	}
	else if (_ProppertyToChange == EProppertyToChange::Replic_condition_varValue)
	{
		return FText::FromString(DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
			.ReplicSection[PropertyIndex.iReplic].ReplicCondition[PropertyIndex.iReplicCondition].VariableValue.ToString());
	}
	else if (_ProppertyToChange == EProppertyToChange::Replic_condition_type) 
	{
		return FText::FromString(DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
			.ReplicSection[PropertyIndex.iReplic].ReplicCondition[PropertyIndex.iReplicCondition].ConditionType.ToString());
	}
	else if (_ProppertyToChange == EProppertyToChange::Replic_condition_CompareType)
	{
		return FText::FromString(DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
			.ReplicSection[PropertyIndex.iReplic].ReplicCondition[PropertyIndex.iReplicCondition].VariableCompareType.ToString());
	}


	//    -----------------------  Response-Condition_Section  -----------------------
	else if (_ProppertyToChange == EProppertyToChange::Response_condition_varName)
	{
		return FText::FromString(DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
			.ResponseSection[PropertyIndex.iResponse].ResponseCondition[PropertyIndex.iResponseCondition].VariableName.ToString());
	}
	else if (_ProppertyToChange == EProppertyToChange::Response_condition_varValue)
	{
		return FText::FromString(DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
			.ResponseSection[PropertyIndex.iResponse].ResponseCondition[PropertyIndex.iResponseCondition].VariableValue.ToString());
	}
	else if (_ProppertyToChange == EProppertyToChange::Response_condition_type)
	{
		return FText::FromString(DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
			.ResponseSection[PropertyIndex.iResponse].ResponseCondition[PropertyIndex.iResponseCondition].ConditionType.ToString());
	}
	else if (_ProppertyToChange == EProppertyToChange::Response_condition_CompareType)
	{
	return FText::FromString(DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
		.ResponseSection[PropertyIndex.iResponse].ResponseCondition[PropertyIndex.iResponseCondition].VariableCompareType.ToString());
	}

	//    -----------------------  Response_ Variable to change _Section  -----------------------
	else if (_ProppertyToChange == EProppertyToChange::Response_variable_varName)
	{
	return FText::FromString(DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ResponseSection[PropertyIndex.iResponse]
		.VariableSection[PropertyIndex.iResponseVariable].VariableName.ToString());
	}
	else if (_ProppertyToChange == EProppertyToChange::Response_variable_varValue)
	{
	return FText::FromString(DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ResponseSection[PropertyIndex.iResponse]
		.VariableSection[PropertyIndex.iResponseVariable].VariableValue.ToString());
	}


	else if (_ProppertyToChange == EProppertyToChange::RepEvent)
	{
		return FText::FromString(DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
										.ReplicSection[PropertyIndex.iReplic].RepSection[PropertyIndex.iRep].RepEvent);
	}

	else if (_ProppertyToChange == EProppertyToChange::SpeechName)
	{
		return FText::FromString(DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].Name.ToString());
	}
	else if (_ProppertyToChange == EProppertyToChange::DialogName)
	{
		return FText::FromString(DialogSection[PropertyIndex.iDialog].Name.ToString());
	}

	return FText::FromString("ERROR");
}




//        ========================================================================================
//        ========================================================================================

//        ============================   Marker,  Indicator   ================================

//        ========================================================================================
//        ========================================================================================

void SDialogWindowWidget::RedrawIndicator()
{
	
	FPropertyIndex CurrentIndicatorIndex;




	auto IndicatorElement = [&](float VerticalSize, FLinearColor color)
	{
		RightIndicator->AddSlot()
		.Padding(0.f)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.FillHeight(0.01f * VerticalSize)
		[
			SNew(SBox)
			.Padding(0)
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SButton)
				.ButtonColorAndOpacity(color)
			]
		];
	};

	//  ======================      Return current block-Collor     =======================

	auto GetMarkerColor = [&](EProppertyToChange ProppertyToChange, FPropertyIndex IndicatorIndex)
	{
		if (ProppertyToChange == EProppertyToChange::MarkerDialog)
		{
			if (DialogSection[IndicatorIndex.iDialog].IsErrorMarker) return ColorErrorMarked;
			else if (DialogSection[IndicatorIndex.iDialog].IsDestinationMarker) return ColorLinkMarked; // ColorLinkMarked
			else if (DialogSection[IndicatorIndex.iDialog].IsLinkMarker) return ColorDestinationLinkMarked; // ColorLinkMarked
			else if (DialogSection[IndicatorIndex.iDialog].IsUsualMarker) return ColorUsualMarked;
			else if (DialogSection[IndicatorIndex.iDialog].IsFastFindMarker) return ColorFastFindMarked;
			else  return ColorInvisible;
		}
		else if (ProppertyToChange == EProppertyToChange::MarkerSpeech)
		{
			if (DialogSection[IndicatorIndex.iDialog].SpeechSection[IndicatorIndex.iSpeech]
				.IsErrorMarker) return ColorErrorMarked;
			else if (DialogSection[IndicatorIndex.iDialog].SpeechSection[IndicatorIndex.iSpeech]   // ColorLinkMarked
				.IsDestinationMarker) return ColorLinkMarked;
			else if (DialogSection[IndicatorIndex.iDialog].SpeechSection[IndicatorIndex.iSpeech]   // ColorLinkMarked
				.IsLinkMarker) return ColorDestinationLinkMarked;
			else if (DialogSection[IndicatorIndex.iDialog].SpeechSection[IndicatorIndex.iSpeech]
				.IsUsualMarker) return ColorUsualMarked;
			else if (DialogSection[IndicatorIndex.iDialog].SpeechSection[IndicatorIndex.iSpeech]
				.IsFastFindMarker) return ColorFastFindMarked;
			else  return ColorInvisible;
		}

		else if (ProppertyToChange == EProppertyToChange::MarkerReplic)
		{
			if (DialogSection[IndicatorIndex.iDialog].SpeechSection[IndicatorIndex.iSpeech]
				.ReplicSection[IndicatorIndex.iReplic].IsErrorMarker) return ColorErrorMarked;
			else if (DialogSection[IndicatorIndex.iDialog].SpeechSection[IndicatorIndex.iSpeech]
				.ReplicSection[IndicatorIndex.iReplic].IsUsualMarker) return ColorUsualMarked;
			else  return ColorInvisible;
		}

		else if (ProppertyToChange == EProppertyToChange::MarkerRep)
		{
			if (DialogSection[IndicatorIndex.iDialog].SpeechSection[IndicatorIndex.iSpeech]
				.ReplicSection[IndicatorIndex.iReplic].RepSection[IndicatorIndex.iRep]
				.IsErrorMarker) return ColorErrorMarked;
			else if (DialogSection[IndicatorIndex.iDialog].SpeechSection[IndicatorIndex.iSpeech]
				.ReplicSection[IndicatorIndex.iReplic].RepSection[IndicatorIndex.iRep]
				.IsUsualMarker) return ColorUsualMarked;
			else  return ColorInvisible;
		}

		else if (ProppertyToChange == EProppertyToChange::MarkerResponse)
		{
			if (DialogSection[IndicatorIndex.iDialog].SpeechSection[IndicatorIndex.iSpeech]
				.ResponseSection[IndicatorIndex.iResponse].IsErrorMarker) return ColorErrorMarked;
			else if (DialogSection[IndicatorIndex.iDialog].SpeechSection[IndicatorIndex.iSpeech]
				.ResponseSection[IndicatorIndex.iResponse].IsLinkMarker) return ColorLinkMarked;
			else if (DialogSection[IndicatorIndex.iDialog].SpeechSection[IndicatorIndex.iSpeech]
				.ResponseSection[IndicatorIndex.iResponse].IsUsualMarker) return ColorUsualMarked;
			else  return ColorInvisible;
		}

		return ColorInvisible;
	};


	//  ==================  Draw Indicator field   ====================

	RightIndicator->ClearChildren();
	FLinearColor colorTMP;

	//  =======  Dialog  =======
	for (int32 i_Dlg = 0; i_Dlg < DialogSection.Num(); i_Dlg++)
	{
		CurrentIndicatorIndex.iDialog = i_Dlg;

		colorTMP = GetMarkerColor(EProppertyToChange::MarkerDialog, CurrentIndicatorIndex);
		IndicatorElement(DialogSectionSize, colorTMP);

		//  =======  Speech  =======
		if (DialogSection[i_Dlg].IsSectionOpen)
		{
			for (int32 i_Speech = 0; i_Speech < DialogSection[i_Dlg].SpeechSection.Num(); i_Speech++)
			{

				CurrentIndicatorIndex.iSpeech = i_Speech;

				colorTMP = GetMarkerColor(EProppertyToChange::MarkerSpeech, CurrentIndicatorIndex);
				IndicatorElement(SpeechSectionSize, colorTMP);
				 
				//  =======  Speech Condition  =======
				if (DialogSection[i_Dlg].SpeechSection[i_Speech].IsConditionOpen)
				{
					for (int32 i_SpeechCondition = 0; i_SpeechCondition < DialogSection[i_Dlg].SpeechSection[i_Speech].SpeechCondition.Num(); i_SpeechCondition++)
					{
						CurrentIndicatorIndex.iSpeechCondition = i_SpeechCondition;
						
						//colorTMP = GetMarkerColor(EProppertyToChange::MarkerSpeech, CurrentIndicatorIndex);
						IndicatorElement(ConditionSectionSize, ColorInvisible);
					}
				}

				//  =======  Speech CONTENT  =======
				if (DialogSection[i_Dlg].SpeechSection[i_Speech].IsSectionOpen)
				{

					//  =======  Replic  =======
					for (int32 i_Replic = 0; i_Replic < DialogSection[i_Dlg].SpeechSection[i_Speech].ReplicSection.Num(); i_Replic++)
					{
						CurrentIndicatorIndex.iReplic = i_Replic; 

						colorTMP = GetMarkerColor(EProppertyToChange::MarkerReplic, CurrentIndicatorIndex);
						IndicatorElement(ReplicSectionSize, colorTMP);

						//  =======  Replic Condition  =======
						if (DialogSection[i_Dlg].SpeechSection[i_Speech].ReplicSection[i_Replic].IsConditionOpen)
						{
							for (int32 i_ReplicCondition = 0; i_ReplicCondition < DialogSection[i_Dlg].SpeechSection[i_Speech].
															ReplicSection[i_Replic].ReplicCondition.Num(); i_ReplicCondition++)
							{
								CurrentIndicatorIndex.iReplicCondition = i_ReplicCondition;

								//colorTMP = GetMarkerColor(EProppertyToChange::MarkerReplic, CurrentIndicatorIndex);
								IndicatorElement(ConditionSectionSize, ColorInvisible);
							}
						}

						//   -----------   EditabeText ---------
						IndicatorElement(DialogSection[CurrentIndicatorIndex.iDialog].SpeechSection[CurrentIndicatorIndex.iSpeech]
							.ReplicSection[CurrentIndicatorIndex.iReplic].ComentTextZoneSizeY, ColorInvisible);  //-----------editabeText


						//  =======  Rep  =======
						if (DialogSection[i_Dlg].SpeechSection[i_Speech].ReplicSection[i_Replic].IsSectionOpen)
						{
							for (int32 i_Rep = 0; i_Rep < DialogSection[i_Dlg].SpeechSection[i_Speech].ReplicSection[i_Replic]
								.RepSection.Num(); i_Rep++)
							{
								CurrentIndicatorIndex.iRep = i_Rep;

								colorTMP = GetMarkerColor(EProppertyToChange::MarkerRep, CurrentIndicatorIndex);
								IndicatorElement(RepSectionSize, colorTMP);

								//  =======  Rep Condition  =======
								if (DialogSection[i_Dlg].SpeechSection[i_Speech].ReplicSection[i_Replic].RepSection[i_Rep].IsConditionOpen)
								{
									for (int32 i_RepCondition = 0; i_RepCondition < DialogSection[i_Dlg].SpeechSection[i_Speech].ReplicSection[i_Replic].RepSection[i_Rep].RepCondition.Num(); i_RepCondition++)
									{
										CurrentIndicatorIndex.iRepCondition = i_RepCondition;

										//colorTMP = GetMarkerColor(EProppertyToChange::MarkerRep, CurrentIndicatorIndex);
										IndicatorElement(ConditionSectionSize, ColorInvisible);
									}
								}

								//   -----------   EditabeText ---------
								IndicatorElement(DialogSection[CurrentIndicatorIndex.iDialog].SpeechSection[CurrentIndicatorIndex.iSpeech]
									.ReplicSection[CurrentIndicatorIndex.iReplic]
									.RepSection[CurrentIndicatorIndex.iRep].ComentTextZoneSizeY, ColorInvisible);   //-----------editabeText
							}
						}
					}

					//  =======  Response  =======
					for (int32 i_Response = 0; i_Response < DialogSection[i_Dlg].SpeechSection[i_Speech].ResponseSection.Num(); i_Response++)
					{
						CurrentIndicatorIndex.iResponse = i_Response;

						colorTMP = GetMarkerColor(EProppertyToChange::MarkerResponse, CurrentIndicatorIndex);
						IndicatorElement(ResponseSectionSize, colorTMP);

						//  =======  Response Condition  =======
						if (DialogSection[i_Dlg].SpeechSection[i_Speech].ResponseSection[i_Response].IsConditionOpen)
						{
							for (int32 i_ResponseCondition = 0; i_ResponseCondition < DialogSection[i_Dlg].SpeechSection[i_Speech]
													.ResponseSection[i_Response].ResponseCondition.Num(); i_ResponseCondition++)
							{
								CurrentIndicatorIndex.iResponseCondition = i_ResponseCondition;

								//colorTMP = GetMarkerColor(EProppertyToChange::MarkerResponse, CurrentIndicatorIndex);
								IndicatorElement(ConditionSectionSize, ColorInvisible);
							}
						}

						//  =======  Response Variables  =======
						for (int32 i_ResponseVariable = 0; i_ResponseVariable < DialogSection[i_Dlg].SpeechSection[i_Speech]
							.ResponseSection[i_Response].VariableSection.Num(); i_ResponseVariable++)
						{
							CurrentIndicatorIndex.iResponseVariable = i_ResponseVariable;

							//colorTMP = GetMarkerColor(EProppertyToChange::MarkerResponse, CurrentIndicatorIndex);
							IndicatorElement(RepsonseVariablesSectionSize, ColorInvisible);
						}

						//   -----------   EditabeText ---------
						IndicatorElement(DialogSection[CurrentIndicatorIndex.iDialog].SpeechSection[CurrentIndicatorIndex.iSpeech]
								.ResponseSection[CurrentIndicatorIndex.iResponse].ComentTextZoneSizeY, ColorInvisible); //-----------editabeText
					}

				}				
			}
		}
	}

}     

//   =============================    Pess Link Button     ========================

FReply SDialogWindowWidget::OnButtonMarkerLink(EProppertyToChange ProppertyToChange, FPropertyIndex PropertyIndex)
{

	//  -------------   Change and store lick button-Marker click   ---------------
	//  -------------   save lest Clicked-Button-index
	if (LastClickedSectionDialogIndex == PropertyIndex.iDialog	&&
		LastClickedSectionSpeechIndex == PropertyIndex.iSpeech	&&
		LastClickedSectionResponseIndex == PropertyIndex.iResponse)	IsLinkMarkerDrawn = false;
	else															IsLinkMarkerDrawn = true;
	LastClickedSectionDialogIndex = PropertyIndex.iDialog;  
	LastClickedSectionSpeechIndex = PropertyIndex.iSpeech;  
	LastClickedSectionResponseIndex = PropertyIndex.iResponse;  


	//  ===============   Deselect All Markers  ===============

	for (int32 i_Dlg = 0; i_Dlg < DialogSection.Num(); i_Dlg++)
	{
		DialogSection[i_Dlg].IsSelfLinkMarker = false;
		DialogSection[i_Dlg].IsLinkMarker = false;
		DialogSection[i_Dlg].IsDestinationMarker = false;

		for (int32 i_Speech = 0; i_Speech < DialogSection[i_Dlg].SpeechSection.Num(); i_Speech++)
		{
			DialogSection[i_Dlg].SpeechSection[i_Speech].IsSelfLinkMarker = false;
			DialogSection[i_Dlg].SpeechSection[i_Speech].IsLinkMarker = false;			
			DialogSection[i_Dlg].SpeechSection[i_Speech].IsDestinationMarker = false;

			for (int32 i_Response = 0; i_Response < DialogSection[i_Dlg].SpeechSection[i_Speech]
															.ResponseSection.Num(); i_Response++)
			{
				DialogSection[i_Dlg].SpeechSection[i_Speech].ResponseSection[i_Response].IsLinkMarker = false;
			}
		}
	}


	//  ====================   Select all Referenses Blocks ===================
	FName DialogLinkStr = FName("DEFAULT");
	FName SpeechLinkStr = FName("DEFAULT");

	if (PropertyIndex.iResponse != -1)
	{
		SpeechLinkStr = DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
												.ResponseSection[PropertyIndex.iResponse].SpeechLink;
		DialogLinkStr = DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
												.ResponseSection[PropertyIndex.iResponse].DialogLink;
	
		for (int32 i_Dlg = 0; i_Dlg < DialogSection.Num(); i_Dlg++)
		{
			if (DialogSection[i_Dlg].Name == DialogLinkStr)
			{
				for (int32 i_Speech = 0; i_Speech < DialogSection[i_Dlg].SpeechSection.Num(); i_Speech++)
				{
					if (DialogSection[i_Dlg].SpeechSection[i_Speech].Name == SpeechLinkStr)
					{
						if (!DialogSection[i_Dlg].IsSectionOpen) DialogSection[i_Dlg].IsLinkMarker = IsLinkMarkerDrawn;
						DialogSection[i_Dlg].SpeechSection[i_Speech].IsLinkMarker = IsLinkMarkerDrawn;
					}
				}
			}
		}
	}
	else //  if( Dialog  or Speech )
	{
		if (PropertyIndex.iSpeech != -1)
			SpeechLinkStr = DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].Name;
		else
			SpeechLinkStr = FName("none");

		DialogLinkStr = DialogSection[PropertyIndex.iDialog].Name;

		for (int32 i_Dlg = 0; i_Dlg < DialogSection.Num(); i_Dlg++)
		{			
			for (int32 i_Speech = 0; i_Speech < DialogSection[i_Dlg].SpeechSection.Num(); i_Speech++)
			{
				for (int32 i_Response = 0; i_Response < DialogSection[i_Dlg].SpeechSection[i_Speech]
																.ResponseSection.Num(); i_Response++)
				{
					if (DialogSection[i_Dlg].SpeechSection[i_Speech].ResponseSection[i_Response].DialogLink == DialogLinkStr)
					{						
						if (DialogSection[i_Dlg].SpeechSection[i_Speech].ResponseSection[i_Response].SpeechLink == SpeechLinkStr ||
							SpeechLinkStr == FName("none"))
						{
							if (!DialogSection[i_Dlg].IsSectionOpen)
								DialogSection[i_Dlg].IsDestinationMarker = IsLinkMarkerDrawn;
							if(!DialogSection[i_Dlg].SpeechSection[i_Speech].IsSectionOpen)
								DialogSection[i_Dlg].SpeechSection[i_Speech].IsDestinationMarker = IsLinkMarkerDrawn;
							DialogSection[i_Dlg].SpeechSection[i_Speech].ResponseSection[i_Response].IsLinkMarker = IsLinkMarkerDrawn;
						}
					}
					
				}
			}
			
		}
	}


	//  ===========   Set Self marker  ============

	if (ProppertyToChange == EProppertyToChange::MarkerDialog)
	{
		if (IsLinkMarkerDrawn)
		{
			//  ------------  Real draw color ---------------
			DialogSection[PropertyIndex.iDialog].IsLinkMarker = true;
			//  ------------  Self Marker---------------
			DialogSection[PropertyIndex.iDialog].IsSelfLinkMarker = true;
		}
		else
		{	//  ------------  Self Marker---------------
			DialogSection[PropertyIndex.iDialog].IsSelfLinkMarker = false;
		}

	}
	else if (ProppertyToChange == EProppertyToChange::MarkerSpeech)
	{
		if (IsLinkMarkerDrawn)
		{
			//  ------------  consider Children's Markers  ---------------
			if (!DialogSection[PropertyIndex.iDialog].IsSectionOpen)
				DialogSection[PropertyIndex.iDialog].IsLinkMarker = true;
			//  ------------  Self Marker---------------
			DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].IsSelfLinkMarker = true;
			//  ------------  Real draw color ---------------
			DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].IsLinkMarker = true;
		}
		else
		{	//  ------------  consider Children's Markers ---------------
			DialogSection[PropertyIndex.iDialog].IsLinkMarker = false;
			//  ------------  Self Marker---------------
			DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].IsSelfLinkMarker = false;
		}
	}
	else if (ProppertyToChange == EProppertyToChange::MarkerResponse)
	{

		if (IsLinkMarkerDrawn)
		{
			//  ------------  consider Children's Markers ---------------
			if (!DialogSection[PropertyIndex.iDialog].IsSectionOpen)
				DialogSection[PropertyIndex.iDialog].IsLinkMarker = true;
			if (!DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].IsSectionOpen)
				DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].IsLinkMarker = true;
			//  ------------  Self Marker---------------
			DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
						.ResponseSection[PropertyIndex.iResponse].IsLinkMarker = true;
		}
		else
		{
			////  ------------  consider Children's Markers ---------------
			DialogSection[PropertyIndex.iDialog].IsLinkMarker = false;
			DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].IsLinkMarker = false;
			//  ------------  Self Marker---------------
			DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
						.ResponseSection[PropertyIndex.iResponse].IsLinkMarker = false;
		}

	}


	RedrawIndicator();


	if (!IsLinkMarkerDrawn)  // Children Markers kontrol
	{
		LastClickedSectionDialogIndex = -1;
		LastClickedSectionSpeechIndex = -1;
		LastClickedSectionResponseIndex = -1;
	}

	return FReply::Handled();
}


FReply SDialogWindowWidget::OnButtonMarkerUsual(const FGeometry& Geomet, const FPointerEvent& PEvent, EProppertyToChange ProppertyToChange, FPropertyIndex PropertyIndex)
{

	
	if (ProppertyToChange == EProppertyToChange::MarkerDialog)
	{

			DialogSection[PropertyIndex.iDialog].IsSelfUsualMarker = !DialogSection[PropertyIndex.iDialog].IsSelfUsualMarker;
			DialogSection[PropertyIndex.iDialog].IsUsualMarker = !DialogSection[PropertyIndex.iDialog].IsUsualMarker;
		//}
	}
	else if (ProppertyToChange == EProppertyToChange::MarkerSpeech)
	{
			DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].IsSelfUsualMarker =
				!DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].IsSelfUsualMarker;
			DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].IsUsualMarker =
				!DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].IsUsualMarker;
	}
	else if (ProppertyToChange == EProppertyToChange::MarkerReplic)
	{
		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
			.ReplicSection[PropertyIndex.iReplic].IsSelfUsualMarker =
		!DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
			.ReplicSection[PropertyIndex.iReplic].IsSelfUsualMarker;
		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
			.ReplicSection[PropertyIndex.iReplic].IsUsualMarker =
		!DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
			.ReplicSection[PropertyIndex.iReplic].IsUsualMarker;
	}
	else if (ProppertyToChange == EProppertyToChange::MarkerRep)
	{
		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic]
			.RepSection[PropertyIndex.iRep].IsUsualMarker =
		!DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic]
			.RepSection[PropertyIndex.iRep].IsUsualMarker;
	}
	else if (ProppertyToChange == EProppertyToChange::MarkerResponse)
	{

			DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
				.ResponseSection[PropertyIndex.iResponse].IsUsualMarker =
				!DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
				.ResponseSection[PropertyIndex.iResponse].IsUsualMarker;
	}

	RedrawIndicator();

	return FReply::Handled();

}

//        ============================   Marker   END   ================================




//        ========================================================================================
//        ========================================================================================

//                                    Marker,  Indicator   ================================

//        ========================================================================================
//        ========================================================================================


void SDialogWindowWidget::SelectFindingContentBlock(bool Select, FString DialogName, FString SpeechName)
{
	for (int32 i_Dlg = 0; i_Dlg < DialogSection.Num(); i_Dlg++)
	{
		DialogSection[i_Dlg].IsFastFindMarker = false;

		for (int32 i_Speech = 0; i_Speech < DialogSection[i_Dlg].SpeechSection.Num(); i_Speech++)
		{			
			if (Select)
			{
				if (DialogSection[i_Dlg].Name.ToString().Contains(DialogName) &&
					DialogSection[i_Dlg].SpeechSection[i_Speech].Name.ToString().Contains(SpeechName))
				{
					//DialogSection[i_Dlg].SpeechSection[i_Speech].IsFastFindMarker = true;
					DialogSection[i_Dlg].IsFastFindMarker = true;
					DialogSection[i_Dlg].SpeechSection[i_Speech].IsFastFindMarker = true;
					//DialogSection[i_Dlg].SpeechSection[i_Speech].IsUsualMarker = true;
				}
				else
				{					
					DialogSection[i_Dlg].SpeechSection[i_Speech].IsFastFindMarker = false;
				}
			}
			else
			{
				//DialogSection[i_Dlg].IsUsualMarker = false;
				DialogSection[i_Dlg].SpeechSection[i_Speech].IsFastFindMarker = false;
			}

		}
	}
	RedrawIndicator();
}


FReply SDialogWindowWidget::FindNextContentBlock()
{
	
	int32 iDialog;
	int32 iSpeech;
	float sizeTo = GetContentBlockIndex(iDialog, iSpeech);

	if (sizeTo == 0 || sizeTo == -1) return FReply::Handled();;

	while (sizeTo < MainContentPanelBlock->GetScrollOffset())
	{
		sizeTo = GetContentBlockIndex(iDialog, iSpeech);
	}

	MainContentPanelBlock->SetScrollOffset(sizeTo);

	return FReply::Handled();
}
 

float SDialogWindowWidget::GetContentBlockIndex(int32& _iDialodSection, int32& _iSpeechSection)  
{
	float CurrScrollOffset = MainContentPanelBlock->GetScrollOffset();
	
	float newScrollOffset = 0;


	auto GetCurrContentsSize = [&](int32 iDlg, int32 iSpeech )
	{

		if (iDlg > DialogSection.Num() - 1)
		{
			return -1.f;   //  ERROR
		}

		float Size = 0;

		for (int32 i_Dlg = 0; i_Dlg < DialogSection.Num(); i_Dlg++)
		{
			
			if (iSpeech > DialogSection[i_Dlg].SpeechSection.Num() - 1)
			{
				continue;
			}

			
			
			
			//  --------------   Speech  -------------
			float _SpeechSectionSize = 0;  //  if it's finding section but it closed
			
			for (int32 i_Speech = 0; i_Speech < DialogSection[i_Dlg].SpeechSection.Num(); i_Speech++)
			{


				//  ========  if finded destinate section  =========
				if (i_Dlg == iDlg && i_Speech == iSpeech)
				{
					Size += _SpeechSectionSize * SizeKoef;
					return Size;
				}

				_SpeechSectionSize += SpeechSectionSize * SizeKoef;

				//  --------------   Speech Condition  -------------
				if (DialogSection[i_Dlg].SpeechSection[i_Speech].IsConditionOpen)
				{
					for (int32 i_SpeechCondition = 0; i_SpeechCondition < DialogSection[i_Dlg].SpeechSection[i_Speech]
						.SpeechCondition.Num(); i_SpeechCondition++)
					{
						_SpeechSectionSize += ConditionSectionSize * SizeKoef;
					}
				}

				//  --------------   Replic  -------------
				
				if (DialogSection[i_Dlg].SpeechSection[i_Speech].IsSectionOpen)
				{
					for (int32 i_Replic = 0; i_Replic < DialogSection[i_Dlg].SpeechSection[i_Speech]
																		.ReplicSection.Num(); i_Replic++)
					{
						//  --------------   Replic Condition  -------------
						if (DialogSection[i_Dlg].SpeechSection[i_Speech].ReplicSection[i_Replic].IsConditionOpen)
						{
							for (int32 i_ReplicCondition = 0; i_ReplicCondition < DialogSection[i_Dlg].SpeechSection[i_Speech]
													.ReplicSection[i_Replic].ReplicCondition.Num(); i_ReplicCondition++)
							{
								_SpeechSectionSize += ConditionSectionSize * SizeKoef;
							}
						}

						//  --------------   Rep  -------------
						_SpeechSectionSize += ReplicSectionSize * SizeKoef;
						if (DialogSection[i_Dlg].SpeechSection[i_Speech].ReplicSection[i_Replic].IsSectionOpen)
						{
							for (int32 i_Rep = 0; i_Rep < DialogSection[i_Dlg].SpeechSection[i_Speech]
														.ReplicSection[i_Replic].RepSection.Num(); i_Rep++)
							{

								//  --------------   Rep Condition  -------------
								if (DialogSection[i_Dlg].SpeechSection[i_Speech].ReplicSection[i_Replic]
																		.RepSection[i_Rep].IsConditionOpen)
								{
									for (int32 i_RepCondition = 0; i_RepCondition < DialogSection[i_Dlg].SpeechSection[i_Speech].ReplicSection[i_Replic].RepSection[i_Rep].RepCondition.Num(); i_RepCondition++)
									{
										_SpeechSectionSize += ConditionSectionSize * SizeKoef;
									}
								}
										
								//  --------------   Rep EditableField   -------------
								_SpeechSectionSize += DialogSection[i_Dlg].SpeechSection[i_Speech]
									.ReplicSection[i_Replic].RepSection[i_Rep].ComentTextZoneSizeY * SizeKoef;
							}
						}

						//  --------------   Replic EditableField   -------------
						_SpeechSectionSize += DialogSection[i_Dlg].SpeechSection[i_Speech]
												.ReplicSection[i_Replic].ComentTextZoneSizeY * SizeKoef;
					}

					for (int32 i_Response = 0; i_Response < DialogSection[i_Dlg].SpeechSection[i_Speech]
																	.ResponseSection.Num(); i_Response++)
					{
						//  --------------   Response Condition  -------------
						_SpeechSectionSize += ResponseSectionSize * SizeKoef;
						if (DialogSection[i_Dlg].SpeechSection[i_Speech].ResponseSection[i_Response].IsConditionOpen)
						{
							for (int32 i_ResponseCondition = 0; i_ResponseCondition < DialogSection[i_Dlg].SpeechSection[i_Speech]
													.ResponseSection[i_Response].ResponseCondition.Num(); i_ResponseCondition++)
							{
								_SpeechSectionSize += ConditionSectionSize * SizeKoef;
							}
						}
						//  --------------   Response Variables  -------------
						if (DialogSection[i_Dlg].SpeechSection[i_Speech].ResponseSection[i_Response].IsVariableOpen)
						{
							for (int32 i_SpeechCondition = 0; i_SpeechCondition < DialogSection[i_Dlg].SpeechSection[i_Speech]
													.ResponseSection[i_Response].VariableSection.Num(); i_SpeechCondition++)
							{
								_SpeechSectionSize += RepsonseVariablesSectionSize * SizeKoef;
							}
						}

						//  --------------   Response EditableField   -------------
						_SpeechSectionSize += DialogSection[i_Dlg].SpeechSection[i_Speech]
											.ResponseSection[i_Response].ComentTextZoneSizeY * SizeKoef;
					}
				}
			}
			if (DialogSection[i_Dlg].IsSectionOpen)
			{
				Size += DialogSectionSize * SizeKoef + _SpeechSectionSize;    //  Scroll  //  add full open Dialog-Section-Size
				Size += 32 * SizeKoef;    //  Scroll  //  if dialog-section open
			}
			else
			{
				Size += DialogSectionSize * SizeKoef + 16 * SizeKoef;    //  Scroll  //  add only Dialog-Title-Size
			}

		}

		return Size;
	};


	for (int32 i_Dlg = 0; i_Dlg < DialogSection.Num(); i_Dlg++)
	{
		if (DialogSection[i_Dlg].Name.ToString().Contains(sContentDialogFinder))
		{
			for (int32 i_Speech = 0; i_Speech < DialogSection[i_Dlg].SpeechSection.Num(); i_Speech++)
			{
				if (DialogSection[i_Dlg].SpeechSection[i_Speech].Name.ToString().Contains(sContentSpeechFinder))

				{
					float CurrContentsSize = GetCurrContentsSize(i_Dlg, i_Speech);

					//UE_LOG(LogTemp, Warning, TEXT("SSSSSSSSSSSSSSSSSSSSSSSSS    %f"), CurrContentsSize);

					return CurrContentsSize;
				}
			}
		}

	}

	return -1;
}



void SDialogWindowWidget::OnEditableTextChange_ContentFinding(const FText& _Text, FName Type)  // "dialog"  ,   "speech"
{
	if(Type == FName("dialog"))	sContentDialogFinder = _Text.ToString();
	if(Type == FName("speech"))	sContentSpeechFinder = _Text.ToString();

	SelectFindingContentBlock(true, sContentDialogFinder, sContentSpeechFinder);
}

//        ============================   Marker,  Indicator      END   ================================









//  =====================   Exequte after printString in 'EditableTextBox'   =====================
void SDialogWindowWidget::ConfirmEditableTextBox(const FText& Text, ETextCommit::Type TextType, EProppertyToChange ProppertyToChange, FPropertyIndex PropertyIndex)
{
	//UE_LOG(LogTemp, Warning, TEXT("SEditableTextBox = '%i'"), a);  // EditableText1.GetText()

	ConfirmCurrentSelection(ProppertyToChange, PropertyIndex);


}






//   ================================================================================================================================================================
//   ================================================================================================================================================================
//   ===============================               COMBO-Box Using        "SPEKER"        ==========================================================================
//   ================================================================================================================================================================
//   ================================================================================================================================================================



//   ================================================================================================================================================================
//   ===============================               COMBO-Box Using        "ReplicRepeat"   "ResponseRepeat"      ======================================================
//   ================================================================================================================================================================
void SDialogWindowWidget::GetReplicRepeatComboList(TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo, FPropertyIndex PropertyIndex)
{	
	DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic].ReplicRepeatPropperty = NewSelection;
}


void SDialogWindowWidget::GetResponseRepeatComboList(TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo, FPropertyIndex PropertyIndex)
{
	DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ResponseSection[PropertyIndex.iResponse].ResponseRepeatPropperty = NewSelection;
}

void SDialogWindowWidget::GetResponseReturnTypeComboList(TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo, FPropertyIndex PropertyIndex)
{
	DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ResponseSection[PropertyIndex.iResponse].ResponseReturnTypePropperty = NewSelection;
}

FText SDialogWindowWidget::GetCurrentReplicRepeatLabel(FPropertyIndex PropertyIndex) const
{
	return DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic].ReplicRepeatPropperty.IsValid() ?
		FText::FromString(*DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic].ReplicRepeatPropperty) :
		FText::GetEmpty();
}

FText SDialogWindowWidget::GetCurrentResponseRepeatLabel(FPropertyIndex PropertyIndex) const
{
	return DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ResponseSection[PropertyIndex.iResponse].ResponseRepeatPropperty.IsValid() ?
		FText::FromString(*DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ResponseSection[PropertyIndex.iResponse].ResponseRepeatPropperty) :
		FText::GetEmpty();
}

FText SDialogWindowWidget::GetCurrentResponseReturnTypeLabel(FPropertyIndex PropertyIndex) const
{
	return DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ResponseSection[PropertyIndex.iResponse].ResponseReturnTypePropperty.IsValid() ?
		FText::FromString(*DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ResponseSection[PropertyIndex.iResponse].ResponseReturnTypePropperty) :
		FText::GetEmpty();
}
//  ===========================================================================================  
//  ================================     Shared   COMBO-BOX    ================================
//  ===========================================================================================
TSharedRef<SWidget> SDialogWindowWidget::HandleComboBoxGenerateWidget(TSharedPtr<FString> InItem)
{
	return SNew(STextBlock)
		.Text(FText::FromString(*InItem))
		.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 18 * SizeKoef))
		.ColorAndOpacity(FLinearColor(0.7f, 0.77f, 1.f, 1));
}


void SDialogWindowWidget::InitComboBox_StaticList()
{
	// ComboBox initial
	//ReplicRepeatComboList.Add(MakeShareable(new FString(FString::Printf(TEXT("Item A %3d"), 0))));
	ReplicRepeatComboList.Add(MakeShareable(new FString(TEXT("once"))));
	ReplicRepeatComboList.Add(MakeShareable(new FString(TEXT("after_once"))));
	ReplicRepeatComboList.Add(MakeShareable(new FString(TEXT("back"))));
	ReplicRepeatComboList.Add(MakeShareable(new FString(TEXT("always"))));

	ResponseRepeatComboList.Add(MakeShareable(new FString(TEXT("once"))));
	ResponseRepeatComboList.Add(MakeShareable(new FString(TEXT("always"))));

	ResponseReturnTypeComboList.Add(MakeShareable(new FString(TEXT("click"))));
	ResponseReturnTypeComboList.Add(MakeShareable(new FString(TEXT("click_back"))));
	ResponseReturnTypeComboList.Add(MakeShareable(new FString(TEXT("click_noreplic"))));

	ResponseReturnTypeComboList.Add(MakeShareable(new FString(TEXT("pass"))));
	ResponseReturnTypeComboList.Add(MakeShareable(new FString(TEXT("pass_back"))));
	ResponseReturnTypeComboList.Add(MakeShareable(new FString(TEXT("pass_noreplic"))));

	ResponseReturnTypeComboList.Add(MakeShareable(new FString(TEXT("EXT (exit)"))));
 
}


//   ---------------------------------------------------------------------------------------------------------------
//   ---------------------------------------------------------------------------------------------------------------
//   ------------------------------          COMBO-Box Using        (END)             ------------------------------
//   ---------------------------------------------------------------------------------------------------------------
//   ---------------------------------------------------------------------------------------------------------------





//  ===========================================================================================
//  ================================       SSpinBox    ================================
//  ===========================================================================================

void SDialogWindowWidget::SetTimeValue(float value, ETextCommit::Type _Type, EProppertyToChange ProppertyToChange, FPropertyIndex PropertyIndex)
{

	if (ProppertyToChange == EProppertyToChange::time)
	{
		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
			.ReplicSection[PropertyIndex.iReplic]
			.RepSection[PropertyIndex.iRep].Time = FName(*FString::SanitizeFloat(value));

		isHelperMenuOpen = false;
	}
	else if (ProppertyToChange == EProppertyToChange::delay)
	{
		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
			.ReplicSection[PropertyIndex.iReplic]
			.RepSection[PropertyIndex.iRep].Delay = FName(*FString::SanitizeFloat(value));
	}
}


void SDialogWindowWidget::SaveDialogToXML()
{
	

	TArray<FString> OutFileNames;
	if (GEngine)  // && GEngine->GameViewport -- In Runtime
	{
		
		void* ParentWindowHandle = FSlateApplication::Get().GetActiveTopLevelWindow()->GetNativeWindow()->GetOSWindowHandle(); // In Editor
		//void* ParentWindowHandle = GEngine->GameViewport->GetWindow()->GetNativeWindow()->GetOSWindowHandle();				// In Runtime
		IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
		if (DesktopPlatform)
		{

			//    ===============  Get Path thrue DielogWindow  ====================
			FString Path = FPaths::ProjectContentDir();  //FString("C:\\Program Files\\7-Zip");//
			FString FileName = FString("Dialog_New.xml");  //FString("C:\\Program Files\\7-Zip");//
			TArray<FString> str;
			if (Path.Find(FString("/"), ESearchCase::Type::CaseSensitive, ESearchDir::Type::FromStart, 0) != -1)
			{				
				Path.ParseIntoArray(str, TEXT("/"), true);			
			}
			else if (Path.Find(FString("\\"), ESearchCase::Type::CaseSensitive, ESearchDir::Type::FromStart, 0) != -1)
			{
				Path.ParseIntoArray(str, TEXT("\\"), true);
			}
			Path = FString("");
			for (int32 i_str = 0; i_str < str.Num(); i_str++)
			{
				Path += str[i_str] + FString("\\");
			}
			Path += "Dialog";

			// open DialogWindow to Save
			uint32 SelectionFlag = 0; // if one or few files has chosen
			DesktopPlatform->SaveFileDialog(ParentWindowHandle, FString("Save file (.xml)"), Path, FileName, FString(".xml"), SelectionFlag, OutFileNames);
			///GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Orange, OutFileNames[0]);


			if (OutFileNames.Num() > 0)
			{
				if (OutFileNames[0].Find(FString(".xml"), ESearchCase::Type::IgnoreCase, ESearchDir::Type::FromStart, 0) == -1)
				{
					OutFileNames[0] += FString(".xml");
				}
				//--------------  Get fileName  ----------------
				if (OutFileNames[0].Find(FString("/"), ESearchCase::Type::CaseSensitive, ESearchDir::Type::FromStart, 0) != -1)
				{
					OutFileNames[0].ParseIntoArray(str, TEXT("/"), true);
				}
				else if (OutFileNames[0].Find(FString("\\"), ESearchCase::Type::CaseSensitive, ESearchDir::Type::FromStart, 0) != -1)
				{
					OutFileNames[0].ParseIntoArray(str, TEXT("\\"), true);
				}
				FileName = str.Last();
				FileName.RemoveFromEnd(".xml", ESearchCase::Type::IgnoreCase);
				Path = OutFileNames[0];     //    ==========   PATH TO SAVE   ===========
			}




			//  XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXxxx
			//  XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXxxx
			//  XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXxxx
			//  XXXXXXXX       Check on ERROR
					FString IsStrError = FString("ok");   //         not jet
			//  XXXXXXXX
			//  XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXxxx
			//  XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXxxx
			//  XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXxxx





			//  ==================   DIALOG   ==================

			// Create .XML,  save "Dialog"
			FString ContentToSave = FString("<name name=\"") + FileName + FString("\" ") + FString("redy=\"") + IsStrError + FString("\">\n");
			for (int32 i_Dlg = 0; i_Dlg < DialogSection.Num(); i_Dlg++)
			{
				
				//  ==================   SPEECH   ==================

				//<dialog DlgName="##############" >
				ContentToSave += FString("\t<dialog dialog_name=\"") + DialogSection[i_Dlg].Name.ToString() + FString("\">\n");
				for (int32 i_Speech = 0; i_Speech < DialogSection[i_Dlg].SpeechSection.Num(); i_Speech++)
				{

					//  ==================   SPEECH CONDITION   ==================

					//<speech marker = "############">
					ContentToSave += FString("\t\t<speech speech_name=\"") + DialogSection[i_Dlg].SpeechSection[i_Speech].Name.ToString() + FString("\">\n");
					for (int32 i_speech_condition = 0; i_speech_condition < DialogSection[i_Dlg].SpeechSection[i_Speech]
																					.SpeechCondition.Num(); i_speech_condition++)
					{	
							//<speech_condition type = "and"  var_local = "GameMapVar_1">val_1</speech_condition>
							ContentToSave += FString("\t\t\t<speech_condition type=\"") +
								DialogSection[i_Dlg].SpeechSection[i_Speech].SpeechCondition[i_speech_condition].ConditionType.ToString();
								ContentToSave += FString("\" var_type=\"");
								if (DialogSection[i_Dlg].SpeechSection[i_Speech]
										.SpeechCondition[i_speech_condition].isVariableGlobal == true)		ContentToSave += FString("global\" ");
								else																		ContentToSave += FString("local\" ");
								ContentToSave += FString("compare_type=\"");
								ContentToSave += DialogSection[i_Dlg].SpeechSection[i_Speech]
									.SpeechCondition[i_speech_condition].VariableCompareType.ToString() +
									FString("\" ");
								ContentToSave += FString("var_name=\"") +
								DialogSection[i_Dlg].SpeechSection[i_Speech].SpeechCondition[i_speech_condition].VariableName.ToString() +
								FString("\">") +
								DialogSection[i_Dlg].SpeechSection[i_Speech].SpeechCondition[i_speech_condition].VariableValue.ToString();
							//FString("\">\n");
						//for (int32 i_speech_condition = 0; i_speech_condition < DialogSection[i_Dlg].SpeechSection[].SpeechCondition.Num(); speech_condition++)
							ContentToSave += FString("</speech_condition>\n");

					}
					//ContentToSave += FString("\n");


					//  ==================   REPLIC  ==================

					for (int32 i_replic = 0; i_replic < DialogSection[i_Dlg].SpeechSection[i_Speech].ReplicSection.Num(); i_replic++)
					{
						//<replic repeat = "once">
						ContentToSave += FString("\t\t\t<replic repeat=\"") +
							*DialogSection[i_Dlg].SpeechSection[i_Speech].ReplicSection[i_replic].ReplicRepeatPropperty +
							FString("\">\n\t\t\t\t ") +
							DialogSection[i_Dlg].SpeechSection[i_Speech].ReplicSection[i_replic].ComentText +
							FString("\n ");


						//  ==================   REPLIC CONDITION   ==================

						for (int32 i_replic_condition = 0; i_replic_condition < DialogSection[i_Dlg].SpeechSection[i_Speech]
							.ReplicSection[i_replic].ReplicCondition.Num(); i_replic_condition++)
						{
								//<response_condition type = "and"  var_local = "GameMapVar_1">val_1</speech_condition>
								ContentToSave += FString("\t\t\t\t<replic_condition type=\"") +
									DialogSection[i_Dlg].SpeechSection[i_Speech].ReplicSection[i_replic]
									.ReplicCondition[i_replic_condition].ConditionType.ToString();
									ContentToSave += FString("\" var_type=\"");
									if (DialogSection[i_Dlg].SpeechSection[i_Speech].ReplicSection[i_replic]
											.ReplicCondition[i_replic_condition].isVariableGlobal == true)		ContentToSave += FString("global\" ");
									else																		ContentToSave += FString("local\" ");
									ContentToSave += FString("compare_type=\"");
									ContentToSave += DialogSection[i_Dlg].SpeechSection[i_Speech]
										.ReplicSection[i_replic].ReplicCondition[i_replic_condition]
										.VariableCompareType.ToString() +
										FString("\" ");
									ContentToSave += FString("var_name=\"") +
									DialogSection[i_Dlg].SpeechSection[i_Speech].ReplicSection[i_replic]
												.ReplicCondition[i_replic_condition].VariableName.ToString() +
									FString("\">") +
									DialogSection[i_Dlg].SpeechSection[i_Speech].ReplicSection[i_replic]
												.ReplicCondition[i_replic_condition].VariableValue.ToString();
								//FString("\">\n");
								ContentToSave += FString("</replic_condition>\n");
						}

						//  =====================    REP   =====================

						for (int32 i_rep = 0; i_rep < DialogSection[i_Dlg].SpeechSection[i_Speech].ReplicSection[i_replic]
																					.RepSection.Num(); i_rep++)
						{
							ContentToSave += FString("\t\t\t\t<rep speker=\"") +
								DialogSection[i_Dlg].SpeechSection[i_Speech].ReplicSection[i_replic].RepSection[i_rep].Speker.ToString() +
								FString("\" sound=\"") +
								DialogSection[i_Dlg].SpeechSection[i_Speech].ReplicSection[i_replic].RepSection[i_rep].Sound.ToString() +
								FString("\" event=\"") +
								DialogSection[i_Dlg].SpeechSection[i_Speech].ReplicSection[i_replic].RepSection[i_rep].RepEvent +
								FString("\" time=\"") +
								DialogSection[i_Dlg].SpeechSection[i_Speech].ReplicSection[i_replic].RepSection[i_rep].Time.ToString() +
								FString("\" delay=\"") +
								DialogSection[i_Dlg].SpeechSection[i_Speech].ReplicSection[i_replic].RepSection[i_rep].Delay.ToString() +
								FString("\">\n\t\t\t\t\t ") +
								DialogSection[i_Dlg].SpeechSection[i_Speech].ReplicSection[i_replic].RepSection[i_rep].ComentText +
								FString("\n ");



							//  ==================   REP CONDITION   ==================

							for (int32 i_rep_condition = 0; i_rep_condition < DialogSection[i_Dlg].SpeechSection[i_Speech]
								.ReplicSection[i_replic].RepSection[i_rep].RepCondition.Num(); i_rep_condition++)
							{
									//<response_condition type = "and"  var_local = "GameMapVar_1">val_1</speech_condition>
									ContentToSave += FString("\t\t\t\t\t<rep_condition type=\"") +
										DialogSection[i_Dlg].SpeechSection[i_Speech].ReplicSection[i_replic]
										.RepSection[i_rep].RepCondition[i_rep_condition].ConditionType.ToString();
										ContentToSave += FString("\" var_type=\"");
										if (DialogSection[i_Dlg].SpeechSection[i_Speech].ReplicSection[i_replic].RepSection[i_rep]
											.RepCondition[i_rep_condition].isVariableGlobal == true)				ContentToSave += FString("global\" ");
										else																		ContentToSave += FString("local\" ");
										ContentToSave += FString("compare_type=\"");
										ContentToSave += DialogSection[i_Dlg].SpeechSection[i_Speech]
											.ReplicSection[i_replic].RepSection[i_rep]
											.RepCondition[i_rep_condition].VariableCompareType.ToString() +
											FString("\" ");
										ContentToSave += FString("var_name=\"") +
										DialogSection[i_Dlg].SpeechSection[i_Speech].ReplicSection[i_replic]
										.RepSection[i_rep].RepCondition[i_rep_condition].VariableName.ToString() +
										FString("\">") +
										DialogSection[i_Dlg].SpeechSection[i_Speech].ReplicSection[i_replic]
										.RepSection[i_rep].RepCondition[i_rep_condition].VariableValue.ToString();
									//FString("\">\n");
									ContentToSave += FString("</rep_condition>\n");
							}
							ContentToSave += FString("\t\t\t\t</rep>\n");
						}
						ContentToSave += FString("\t\t\t</replic>\n");
						
					}


					//  ==================   RESPONSE  ==================

					for (int32 i_response = 0; i_response < DialogSection[i_Dlg].SpeechSection[i_Speech].ResponseSection.Num(); i_response++)
					{
						//<response repeat="once" dialog="" marker="" type="BACK" color="-----------">
						ContentToSave += FString("\t\t\t<response repeat=\"") +
							*DialogSection[i_Dlg].SpeechSection[i_Speech].ResponseSection[i_response].ResponseRepeatPropperty +
							FString("\" dialog_link=\"") +
							DialogSection[i_Dlg].SpeechSection[i_Speech].ResponseSection[i_response].DialogLink.ToString() +
							FString("\" speech_link=\"") +
							DialogSection[i_Dlg].SpeechSection[i_Speech].ResponseSection[i_response].SpeechLink.ToString() +
							FString("\" return_type=\"") +
							*DialogSection[i_Dlg].SpeechSection[i_Speech].ResponseSection[i_response].ResponseReturnTypePropperty +
							FString("\">\n\t\t\t\t ") +
							DialogSection[i_Dlg].SpeechSection[i_Speech].ResponseSection[i_response].ComentText +
							FString("\n ");


							//  ==================   RESPONSE CONDITION   ==================

							for (int32 i_response_condition = 0; i_response_condition < DialogSection[i_Dlg].SpeechSection[i_Speech]
														.ResponseSection[i_response].ResponseCondition.Num(); i_response_condition++)
							{
									//<response_condition type = "and"  var_local = "GameMapVar_1">val_1</speech_condition>
									ContentToSave += FString("\t\t\t\t<response_condition type=\"") +
										DialogSection[i_Dlg].SpeechSection[i_Speech].ResponseSection[i_response]
														.ResponseCondition[i_response_condition].ConditionType.ToString();
										ContentToSave += FString("\" var_type=\"");
										if (DialogSection[i_Dlg].SpeechSection[i_Speech].ResponseSection[i_response]
											.ResponseCondition[i_response_condition].isVariableGlobal == true)		ContentToSave += FString("global\" ");
										else																		ContentToSave += FString("local\" ");
										ContentToSave += FString("compare_type=\"");
										ContentToSave += DialogSection[i_Dlg].SpeechSection[i_Speech]
											.ResponseSection[i_response].ResponseCondition[i_response_condition]
											.VariableCompareType.ToString() +
											FString("\" ");
										ContentToSave += FString("var_name=\"") +
										DialogSection[i_Dlg].SpeechSection[i_Speech].ResponseSection[i_response]
														.ResponseCondition[i_response_condition].VariableName.ToString() +
										FString("\">") +
										DialogSection[i_Dlg].SpeechSection[i_Speech].ResponseSection[i_response]
														.ResponseCondition[i_response_condition].VariableValue.ToString();
									//FString("\">\n");
									ContentToSave += FString("</response_condition>\n");
							}

							//  ==================   RESPONSE VARIABLES   ==================

							for (int32 i_response_variables = 0; i_response_variables < DialogSection[i_Dlg].SpeechSection[i_Speech]
																.ResponseSection[i_response].VariableSection.Num(); i_response_variables++)
							{
								//<response_condition type = "and"  var_local = "GameMapVar_1">val_1</speech_condition>
								ContentToSave += FString("\t\t\t\t<change_variable var_type=\"");
								if(DialogSection[i_Dlg].SpeechSection[i_Speech].ResponseSection[i_response]
									.VariableSection[i_response_variables].isVariableGlobal == true)		ContentToSave += FString("global\" ");
								else																		ContentToSave += FString("local\" ");
								ContentToSave += FString("var_name=\"") +
								DialogSection[i_Dlg].SpeechSection[i_Speech].ResponseSection[i_response]
												.VariableSection[i_response_variables].VariableName.ToString() +
								FString("\">") +
								DialogSection[i_Dlg].SpeechSection[i_Speech].ResponseSection[i_response]
								.VariableSection[i_response_variables].VariableValue.ToString();
								//FString("\">\n");
								ContentToSave += FString("</change_variable>\n");

							}
							ContentToSave += FString("\t\t\t</response>\n");

					}
					

					ContentToSave += FString("\t\t</speech>\n");
				}
				ContentToSave += FString("\t</dialog>\n");
			}
			ContentToSave += FString("</name>");



			//  ===============   Save string to file   ================
			FFileHelper::SaveStringToFile(ContentToSave, *Path);

		}
	} 
}


void SDialogWindowWidget::ChoiseLoadingXmlFile()
{
	TArray<FString> OutFileNames;
	if (GEngine)  // && GEngine->GameViewport -- In Runtime
	{

		void* ParentWindowHandle = FSlateApplication::Get().GetActiveTopLevelWindow()->GetNativeWindow()->GetOSWindowHandle(); // In Editor
		//void* ParentWindowHandle = GEngine->GameViewport->GetWindow()->GetNativeWindow()->GetOSWindowHandle();				// In Runtime
		IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
		if (DesktopPlatform)
		{

			//    ===============  Get Path thrue DielogWindow  ====================
			FString Path = FPaths::ProjectContentDir();  //FString("C:\\Program Files\\7-Zip");//
			FString FileName = FString("Dialog_New.xml");  //FString("C:\\Program Files\\7-Zip");//
			TArray<FString> str;
			if (Path.Find(FString("/"), ESearchCase::Type::CaseSensitive, ESearchDir::Type::FromStart, 0) != -1)
			{
				Path.ParseIntoArray(str, TEXT("/"), true);
			}
			else if (Path.Find(FString("\\"), ESearchCase::Type::CaseSensitive, ESearchDir::Type::FromStart, 0) != -1)
			{
				Path.ParseIntoArray(str, TEXT("\\"), true);
			}
			Path = FString("");
			for (int32 i_str = 0; i_str < str.Num(); i_str++)
			{
				Path += str[i_str] + FString("\\");
			}
			Path += "Dialog";

			// open DialogWindow to Save
			uint32 SelectionFlag = 0; // if one or few files has chosen
			DesktopPlatform->OpenFileDialog(ParentWindowHandle, FString("Save file (.xml)"), Path, FileName, FString(".xml"), SelectionFlag, OutFileNames);
			///GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Orange, OutFileNames[0]);


			if (OutFileNames.Num() > 0 && OutFileNames[0].Find(FString(".xml"), ESearchCase::Type::IgnoreCase, ESearchDir::Type::FromStart, 0) != -1)
			{
				*PathToCurrentXML = OutFileNames[0];
			}
		}
	}	
}

void SDialogWindowWidget::LoadDialogFromXML()
{

	////////#####################################################################################
	//std::string text = "ПРМЛД";
	//std::wstring text_wstring11 = pugi::as_wide(text.c_str());
	//FString aaaa(text_wstring11.c_str());
	//UE_LOG(LogTemp, Warning, TEXT("YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY '%s'"), *aaaa);
	////////#####################################################################################


	//UE_LOG(LogTemp, Warning, TEXT("PathToCurrentXML = '%s'"), *(*PathToCurrentXML));
	if (*PathToCurrentXML == FString("none"))
	{
		return;
	}


	//FString XmlFileContent;



	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();


	

	// ------  FileLoadingContent  -----------
	pugi::xml_document xmlDoc;
	
	pugi::xml_parse_result parse_Res = xmlDoc.load_file(StringCast<ANSICHAR>(**PathToCurrentXML).Get());  //+++++

	pugi::xml_node RootNode = xmlDoc.child("name");



	DialogSection.Empty();
	//  1111   ========================  Run over all <dialog>  =================
	pugi::xpath_node_set DLG_DialogNode = RootNode.select_nodes("dialog");
	for (int32 i_Dialog = 0; i_Dialog < DLG_DialogNode.size(); i_Dialog++)
	{
		FDialogSection DialogTmp;
		  
		std::string STD_dlgStr(DLG_DialogNode[i_Dialog].node().attribute("dialog_name").as_string());  //   get attribute("dialog_name")
		std::wstring STD_W_DlgStr = pugi::as_wide(STD_dlgStr.c_str());
		FString DlgStr(STD_W_DlgStr.c_str());

		DialogTmp.Name = FName(*DlgStr);

		//   2222  ================  Run over all <speech>  =================		
		pugi::xpath_node_set DLG_SpeechNode = DLG_DialogNode[i_Dialog].node().select_nodes("speech");
		for (int32 i_Speech = 0; i_Speech < DLG_SpeechNode.size(); i_Speech++)
		{
			FSpeechSection SpeechTmp;

			std::string STD_SpeechStr(DLG_SpeechNode[i_Speech].node().attribute("speech_name").as_string());  //   get attribute("speech_name")
			std::wstring STD_W_SpeechStr = pugi::as_wide(STD_SpeechStr.c_str());
			FString SpeechStr(STD_W_SpeechStr.c_str());

			SpeechTmp.Name = FName(*SpeechStr);
			

			//   3333   SPEECH_CONDITION   ================  Run over all <speech_condition>  =================		
			pugi::xpath_node_set DLG_SpeechConditionNode = DLG_SpeechNode[i_Speech].node().select_nodes("speech_condition");
			for (int32 i_SpeechCondition = 0; i_SpeechCondition < DLG_SpeechConditionNode.size(); i_SpeechCondition++)
			{
				FCondition SpeechConditionTmp;

				std::string STD_SpeechConditionStr(DLG_SpeechConditionNode[i_SpeechCondition].node().attribute("type").as_string());  //   get attribute("type")
				std::wstring STD_W_SpeechConditionStr = pugi::as_wide(STD_SpeechConditionStr.c_str());
				FString SpeechConditionStr(STD_W_SpeechConditionStr.c_str());

				SpeechConditionTmp.ConditionType = FName(*SpeechConditionStr);

				std::string STD_SpeechVarTypeStr(DLG_SpeechConditionNode[i_SpeechCondition].node().attribute("var_type").as_string());  //   get attribute("var_type")
				//std::wstring STD_W_SpeechVarTypeStr = pugi::as_wide(STD_SpeechVarTypeStr.c_str());
				//FString SpeechVarTypeStr(STD_W_SpeechVarTypeStr.c_str());
				SpeechConditionTmp.isVariableGlobal = (STD_SpeechVarTypeStr == "global") ? true : false;

				std::string STD_SpeechCompareTypeStr(DLG_SpeechConditionNode[i_SpeechCondition].node().attribute("compare_type").as_string());  //   get attribute("compare_type")
				FString SpeechCompareTypeStr(STD_SpeechCompareTypeStr.c_str());

				SpeechConditionTmp.VariableCompareType = FName(*SpeechCompareTypeStr);

				std::string STD_SpeechVarNameStr(DLG_SpeechConditionNode[i_SpeechCondition].node().attribute("var_name").as_string());  //   get attribute("var_name")
				std::wstring STD_W_SpeechVarNameStr = pugi::as_wide(STD_SpeechVarNameStr.c_str());
				FString SpeechVarNameStr(STD_W_SpeechVarNameStr.c_str());

				SpeechConditionTmp.VariableName = FName(*SpeechVarNameStr);

				std::string STD_SpeechVarValueStr(DLG_SpeechConditionNode[i_SpeechCondition].node().text().as_string());   //       get Value
				std::wstring STD_W_SpeechVarValueStr = pugi::as_wide(STD_SpeechVarValueStr.c_str());
				FString SpeechVarValueStr(STD_W_SpeechVarValueStr.c_str());

				SpeechConditionTmp.VariableValue = FName(*SpeechVarValueStr);


				SpeechTmp.SpeechCondition.Add(SpeechConditionTmp);
			}

			//   3333 REPLIC  ================  Run over all <replic>  =================		
			pugi::xpath_node_set DLG_ReplicNode = DLG_SpeechNode[i_Speech].node().select_nodes("replic");
			for (int32 i_Replic = 0; i_Replic < DLG_ReplicNode.size(); i_Replic++)
			{
				FReplicSection ReplicTmp;

					std::string STD_ReplicRepeatStr(DLG_ReplicNode[i_Replic].node().attribute("repeat").as_string());  //   get attribute("repeat")
					std::wstring STD_W_ReplicStr = pugi::as_wide(STD_ReplicRepeatStr.c_str());
					FString ReplicRepeatStr(STD_W_ReplicStr.c_str());

				*ReplicTmp.ReplicRepeatPropperty = ReplicRepeatStr;
				 
					std::string STD_ReplicContentStr(DLG_ReplicNode[i_Replic].node().text().as_string());           //   get Value
					std::wstring STD_W_ReplicContentStr = pugi::as_wide(STD_ReplicContentStr.c_str());
					FString ReplicContentStr(STD_W_ReplicContentStr.c_str());
					ReplicContentStr.TrimStartAndEndInline();               //  remove \t \n

				ReplicTmp.ComentText = ReplicContentStr;


				
				//   4444   REPLIC_CONDITION   ================  Run over all <replic_condition>  =================		
				pugi::xpath_node_set DLG_ReplicConditionNode = DLG_ReplicNode[i_Replic].node().select_nodes("replic_condition");
				for (int32 i_ReplicCondition = 0; i_ReplicCondition < DLG_ReplicConditionNode.size(); i_ReplicCondition++)
				{
					FCondition ReplicConditionTmp;

					std::string STD_ReplicConditionStr(DLG_ReplicConditionNode[i_ReplicCondition].node().attribute("type").as_string());  //   get attribute("type")
					std::wstring STD_W_ReplicConditionStr = pugi::as_wide(STD_ReplicConditionStr.c_str());
					FString ReplicConditionStr(STD_W_ReplicConditionStr.c_str());

					ReplicConditionTmp.ConditionType = FName(*ReplicConditionStr);

					std::string STD_ReplicVarTypeStr(DLG_ReplicConditionNode[i_ReplicCondition].node().attribute("var_type").as_string());  //   get attribute("var_type")
					//std::wstring STD_W_ReplicVarTypeStr = pugi::as_wide(STD_ReplicVarTypeStr.c_str());
					//FString ReplicVarTypeStr(STD_W_ReplicVarTypeStr.c_str());
					ReplicConditionTmp.isVariableGlobal = (STD_ReplicVarTypeStr == "global") ? true : false;

					std::string STD_ReplicCompareTypeStr(DLG_ReplicConditionNode[i_ReplicCondition].node().attribute("compare_type").as_string());  //   get attribute("compare_type")
					FString ReplicCompareTypeStr(STD_ReplicCompareTypeStr.c_str());

					ReplicConditionTmp.VariableCompareType = FName(*ReplicCompareTypeStr);

					std::string STD_ReplicVarNameStr(DLG_ReplicConditionNode[i_ReplicCondition].node().attribute("var_name").as_string());  //   get attribute("var_name")
					std::wstring STD_W_ReplicVarNameStr = pugi::as_wide(STD_ReplicVarNameStr.c_str());
					FString ReplicVarNameStr(STD_W_ReplicVarNameStr.c_str());

					ReplicConditionTmp.VariableName = FName(*ReplicVarNameStr);

					std::string STD_ReplicVarValueStr(DLG_ReplicConditionNode[i_ReplicCondition].node().text().as_string());   //       get Value
					std::wstring STD_W_ReplicVarValueStr = pugi::as_wide(STD_ReplicVarValueStr.c_str());
					FString ReplicVarValueStr(STD_W_ReplicVarValueStr.c_str());

					ReplicConditionTmp.VariableValue = FName(*ReplicVarValueStr);


					ReplicTmp.ReplicCondition.Add(ReplicConditionTmp);
				}


				//   4444   REP   ================  Run over all <rep>  =================		
				pugi::xpath_node_set DLG_RepNode = DLG_ReplicNode[i_Replic].node().select_nodes("rep");
				for (int32 i_Rep = 0; i_Rep < DLG_RepNode.size(); i_Rep++)
				{
					FRepSection RepTmp;
					
						std::string STD_RepSrekerStr(DLG_RepNode[i_Rep].node().attribute("speker").as_string());  //   get attribute("speker")
						std::wstring STD_W_RepSrekerStr = pugi::as_wide(STD_RepSrekerStr.c_str());
						FString RepSrekerStr(STD_W_RepSrekerStr.c_str());

					RepTmp.Speker = FName(*RepSrekerStr);

						std::string STD_RepSoundStr(DLG_RepNode[i_Rep].node().attribute("sound").as_string());  //   get attribute("sound")
						std::wstring STD_W_RepSoundStr = pugi::as_wide(STD_RepSoundStr.c_str());
						FString RepSoundStr(STD_W_RepSoundStr.c_str());

					RepTmp.Sound = FName(*RepSoundStr);

						std::string STD_RepEventStr(DLG_RepNode[i_Rep].node().attribute("event").as_string());  //   get attribute("event")
						std::wstring STD_W_RepEventStr = pugi::as_wide(STD_RepEventStr.c_str());
						FString RepEventStr(STD_W_RepEventStr.c_str());

					RepTmp.RepEvent = RepEventStr;

						std::string STD_RepTimeStr(DLG_RepNode[i_Rep].node().attribute("time").as_string());  //   get attribute("time")
						std::wstring STD_W_RepTimeStr = pugi::as_wide(STD_RepTimeStr.c_str());
						FString RepTimeStr(STD_W_RepTimeStr.c_str());

					RepTmp.Time = FName(*RepTimeStr);

						std::string STD_RepDelayStr(DLG_RepNode[i_Rep].node().attribute("delay").as_string());  //   get attribute("delay")
						std::wstring STD_W_RepDelayStr = pugi::as_wide(STD_RepDelayStr.c_str());
						FString RepDelayStr(STD_W_RepDelayStr.c_str());

					RepTmp.Delay = FName(*RepDelayStr);

						std::string STD_RepContentStr(DLG_RepNode[i_Rep].node().text().as_string());   //       get Value
						std::wstring STD_W_RepContentStr = pugi::as_wide(STD_RepContentStr.c_str());
						FString RepContentStr(STD_W_RepContentStr.c_str());           
						RepContentStr.TrimStartAndEndInline();               //  remove \t \n

					RepTmp.ComentText = RepContentStr;


					//   5555  	================  Run over all <rep_condition>  =================		
					pugi::xpath_node_set DLG_RepConditionNode = DLG_RepNode[i_Rep].node().select_nodes("rep_condition");
					for (int32 i_RepCondition = 0; i_RepCondition < DLG_RepConditionNode.size(); i_RepCondition++)
					{
						FCondition RepConditionTmp;

							std::string STD_RepConditionStr(DLG_RepConditionNode[i_RepCondition].node().attribute("type").as_string());  //   get attribute("type")
							std::wstring STD_W_RepConditionStr = pugi::as_wide(STD_RepConditionStr.c_str());
							FString RepConditionStr(STD_W_RepConditionStr.c_str());
							 
						RepConditionTmp.ConditionType = FName(*RepConditionStr);

							std::string STD_RepVarTypeStr(DLG_RepConditionNode[i_RepCondition].node().attribute("var_type").as_string());  //   get attribute("var_type")
							//std::wstring STD_W_RepVarTypeStr = pugi::as_wide(STD_RepVarTypeStr.c_str());
							//FString RepVarTypeStr(STD_W_RepVarTypeStr.c_str());
						RepConditionTmp.isVariableGlobal = (STD_RepVarTypeStr == "global") ? true : false;

						std::string STD_RepCompareTypeStr(DLG_RepConditionNode[i_RepCondition].node().attribute("compare_type").as_string());  //   get attribute("compare_type")
						FString RepCompareTypeStr(STD_RepCompareTypeStr.c_str());

						RepConditionTmp.VariableCompareType = FName(*RepCompareTypeStr);

							std::string STD_RepVarNameStr(DLG_RepConditionNode[i_RepCondition].node().attribute("var_name").as_string());  //   get attribute("var_name")
							std::wstring STD_W_RepVarNameStr = pugi::as_wide(STD_RepVarNameStr.c_str());
							FString RepVarNameStr(STD_W_RepVarNameStr.c_str());

						RepConditionTmp.VariableName = FName(*RepVarNameStr);

							std::string STD_RepVarValueStr(DLG_RepConditionNode[i_RepCondition].node().text().as_string());   //       get Value
							std::wstring STD_W_RepVarValueStr = pugi::as_wide(STD_RepVarValueStr.c_str());
							FString RepVarValueStr(STD_W_RepVarValueStr.c_str());

						RepConditionTmp.VariableValue = FName(*RepVarValueStr);


						RepTmp.RepCondition.Add(RepConditionTmp);
					}

					ReplicTmp.RepSection.Add(RepTmp);
				}
				 
				SpeechTmp.ReplicSection.Add(ReplicTmp);
			}

			//   3333   RESPONSE   ================  Run over all <response>  =================		
			pugi::xpath_node_set DLG_ResponseNode = DLG_SpeechNode[i_Speech].node().select_nodes("response");
			for (int32 i_Response = 0; i_Response < DLG_ResponseNode.size(); i_Response++)
			{
				FResponseSection ResponseTmp;

					std::string STD_ResponseRepeatStr(DLG_ResponseNode[i_Response].node().attribute("repeat").as_string());  //   get attribute("repeat")
					std::wstring STD_W_ResponseRepeatStr = pugi::as_wide(STD_ResponseRepeatStr.c_str());
					FString ResponseRepeatStr(STD_W_ResponseRepeatStr.c_str());

				*ResponseTmp.ResponseRepeatPropperty = ResponseRepeatStr;

					std::string STD_ResponseLinkDlgStr(DLG_ResponseNode[i_Response].node().attribute("dialog_link").as_string());  //   get attribute("dialog_link")
					std::wstring STD_W_ResponseLinkDlgStr = pugi::as_wide(STD_ResponseLinkDlgStr.c_str());
					FString ResponseLinkDlgStr(STD_W_ResponseLinkDlgStr.c_str());

				ResponseTmp.DialogLink = FName(*ResponseLinkDlgStr);

					std::string STD_ResponseLincSpeechStr(DLG_ResponseNode[i_Response].node().attribute("speech_link").as_string());  //   get attribute("speech_link")
					std::wstring STD_W_ResponseLincSpeechStr = pugi::as_wide(STD_ResponseLincSpeechStr.c_str());
					FString ResponseLincSpeechStr(STD_W_ResponseLincSpeechStr.c_str());

				ResponseTmp.SpeechLink = FName(*ResponseLincSpeechStr);

					std::string STD_ResponseReturnTypeStr(DLG_ResponseNode[i_Response].node().attribute("return_type").as_string());  //   get attribute("return_type")
					std::wstring STD_W_ResponseReturnTypeStr = pugi::as_wide(STD_ResponseReturnTypeStr.c_str());
					FString ResponseReturnTypeStr(STD_W_ResponseReturnTypeStr.c_str());

				*ResponseTmp.ResponseReturnTypePropperty = ResponseReturnTypeStr;

					std::string STD_ResponseContentStr(DLG_ResponseNode[i_Response].node().text().as_string());  //   get Value
					std::wstring STD_W_ResponseContentStr = pugi::as_wide(STD_ResponseContentStr.c_str());
					FString ResponseContentStr(STD_W_ResponseContentStr.c_str());
					ResponseContentStr.TrimStartAndEndInline();               //  remove \t \n

				ResponseTmp.ComentText = ResponseContentStr;


				//   4444   RESPONSE_CONDITION   ================  Run over all <response_condition>  =================		
				pugi::xpath_node_set DLG_ResponseConditionNode = DLG_ResponseNode[i_Response].node().select_nodes("response_condition");
				for (int32 i_ResponseCondition = 0; i_ResponseCondition < DLG_ResponseConditionNode.size(); i_ResponseCondition++)
				{
					FCondition ResponseConditionTmp;

					std::string STD_ResponseConditionStr(DLG_ResponseConditionNode[i_ResponseCondition].node().attribute("type").as_string());  //   get attribute("type")
					std::wstring STD_W_ResponseConditionStr = pugi::as_wide(STD_ResponseConditionStr.c_str());
					FString ResponseConditionStr(STD_W_ResponseConditionStr.c_str());

					ResponseConditionTmp.ConditionType = FName(*ResponseConditionStr);

					std::string STD_ResponseVarTypeStr(DLG_ResponseConditionNode[i_ResponseCondition].node().attribute("var_type").as_string());  //   get attribute("var_type")
					//std::wstring STD_W_ResponseVarTypeStr = pugi::as_wide(STD_ResponseVarTypeStr.c_str());
					//FString ResponseVarTypeStr(STD_W_ResponseVarTypeStr.c_str());
					ResponseConditionTmp.isVariableGlobal = (STD_ResponseVarTypeStr == "global") ? true : false;

					std::string STD_ResponseCompareTypeStr(DLG_ResponseConditionNode[i_ResponseCondition].node().attribute("compare_type").as_string());  //   get attribute("compare_type")
					FString ResponseCompareTypeStr(STD_ResponseCompareTypeStr.c_str());

					ResponseConditionTmp.VariableCompareType = FName(*ResponseCompareTypeStr);

					std::string STD_ResponseVarNameStr(DLG_ResponseConditionNode[i_ResponseCondition].node().attribute("var_name").as_string());  //   get attribute("var_name")
					std::wstring STD_W_ResponseVarNameStr = pugi::as_wide(STD_ResponseVarNameStr.c_str());
					FString ResponseVarNameStr(STD_W_ResponseVarNameStr.c_str());

					ResponseConditionTmp.VariableName = FName(*ResponseVarNameStr);

					std::string STD_ResponseVarValueStr(DLG_ResponseConditionNode[i_ResponseCondition].node().text().as_string());   //       get Value
					std::wstring STD_W_ResponseVarValueStr = pugi::as_wide(STD_ResponseVarValueStr.c_str());
					FString ResponseVarValueStr(STD_W_ResponseVarValueStr.c_str());

					ResponseConditionTmp.VariableValue = FName(*ResponseVarValueStr);


					ResponseTmp.ResponseCondition.Add(ResponseConditionTmp);
				}

				//   4444   RESPONSE_VARIABLES   ================  Run over all <change_variable>  =================		
				pugi::xpath_node_set DLG_ResponseVariableNode = DLG_ResponseNode[i_Response].node().select_nodes("change_variable");
				for (int32 i_ResponseVariable = 0; i_ResponseVariable < DLG_ResponseVariableNode.size(); i_ResponseVariable++)
				{
					FVariables ResponseVariableTmp;

					std::string STD_ResponseVarTypeStr(DLG_ResponseVariableNode[i_ResponseVariable].node().attribute("var_type").as_string());  //   get attribute("var_type")
					//std::wstring STD_W_ResponseVarTypeStr = pugi::as_wide(STD_ResponseVarTypeStr.c_str());
					//FString ResponseVarTypeStr(STD_W_ResponseVarTypeStr.c_str());

					ResponseVariableTmp.isVariableGlobal = (STD_ResponseVarTypeStr == "global") ? true : false;

					std::string STD_ResponseVarNameStr(DLG_ResponseVariableNode[i_ResponseVariable].node().attribute("var_name").as_string());  //   get attribute("var_name")
					std::wstring STD_W_ResponseVarNameStr = pugi::as_wide(STD_ResponseVarNameStr.c_str());
					FString ResponseVarNameStr(STD_W_ResponseVarNameStr.c_str());

					ResponseVariableTmp.VariableName = FName(*ResponseVarNameStr);

					std::string STD_ResponseVarValueStr(DLG_ResponseVariableNode[i_ResponseVariable].node().text().as_string());   //       get Value
					std::wstring STD_W_ResponseVarValueStr = pugi::as_wide(STD_ResponseVarValueStr.c_str());
					FString ResponseVarValueStr(STD_W_ResponseVarValueStr.c_str());

					ResponseVariableTmp.VariableValue = FName(*ResponseVarValueStr);


					ResponseTmp.VariableSection.Add(ResponseVariableTmp);
				}

				SpeechTmp.ResponseSection.Add(ResponseTmp);
			}

			DialogTmp.SpeechSection.Add(SpeechTmp);
		}

		DialogSection.Add(DialogTmp);
	}

	UpdateDialogBlock();
}




//  ===============================================================================================================================
//  ===============================================================================================================================
//  ===============================================================================================================================
//  =================================                 Variables BLOCK                      =================================
//  ===============================================================================================================================
//  ===============================================================================================================================
//  ===============================================================================================================================
void SDialogWindowWidget::SaveVariablesToXML()
{
	//FString XmlContentPath = IPluginManager::Get().FindPlugin(TEXT("PugiXML_Plagin"))->GetContentDir();
	FString DialogXmlContentPath = FPaths::ProjectContentDir();
	DialogXmlContentPath += "/Dialog";
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, XmlContentPath);


	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	if (!PlatformFile.DirectoryExists(*DialogXmlContentPath))
	{
		PlatformFile.CreateDirectory(*DialogXmlContentPath);
		if (!PlatformFile.DirectoryExists(*DialogXmlContentPath))
		{
			return;
		}
	}

	// Create .XML,  save "Speker"
	FString ContentToSave = FString("<local_variables>\n");

	for (int32 i = 0; i < Variables.Num(); i++)
	{

		ContentToSave += FString("\t<variable name=\"") + Variables[i].VariableName.ToString() + 
			FString("\" value=\"") + 
			Variables[i].VariableValue.ToString() +
			FString("\"/>") +
			FString("\n");

	}

	ContentToSave += FString("</local_variables>");

	// Get file path
	FString FilePath = DialogXmlContentPath + "/LVariables.xml";

		// save string to file
	FFileHelper::SaveStringToFile(ContentToSave, *FilePath);

}

void SDialogWindowWidget::LoadVariablesFromXML()
{
	
	FString DialogXmlContentPath = FPaths::ProjectContentDir() + FString("Dialog/") + FString("LVariables.xml");
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	if (!PlatformFile.FileExists(*DialogXmlContentPath))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, DialogXmlContentPath);
		return;
	}

	//  Get xmlFile Content
	pugi::xml_document xmlDoc;
	//pugi::xml_parse_result parse_Res = xmlDoc.load_file(TCHAR_TO_ANSI(*PathToFile));   //++++++
	pugi::xml_parse_result parse_Res = xmlDoc.load_file(StringCast<ANSICHAR>(*DialogXmlContentPath).Get());  //+++++
	if (!parse_Res)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, FString("XML-File Parse ERROR"));
		return;
	}


	Variables.Empty();

	//  Get Root Node
	pugi::xml_node RootNode = xmlDoc.child("local_variables");
	//std::string RootNodeStr(RootNode.attribute("name").as_string());

	//  Go throu all root
	pugi::xpath_node_set VariablesNodes = RootNode.select_nodes("variable");
	for (int32 i = 0; i < VariablesNodes.size(); i++)
	{
		FVariables Variables_tmp;

		std::string STD_AttributName_str(VariablesNodes[i].node().attribute("name").as_string());
		//std::wstring AtributName_STD_wchar_t = pugi::as_wide(AttributName_STD.c_str());
		FString VariablesName_str(STD_AttributName_str.c_str());

		Variables_tmp.VariableName = FName(*VariablesName_str);


		std::string STD_VariablesValue_str(VariablesNodes[i].node().attribute("value").as_string());
		//std::wstring AtributName_STD_wchar_t = pugi::as_wide(AttributName_STD.c_str());
		FString VariablesValue_str(STD_VariablesValue_str.c_str());

		Variables_tmp.VariableValue = FName(*VariablesValue_str);

	

		Variables_tmp.isVariableGlobal = false;
		Variables.Add(Variables_tmp);


		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, Variables_tmp.VariableName.ToString());
		//UE_LOG(LogTemp, Warning, TEXT("replic-------: =     '%s',       %s"), *Variables_tmp.VariableName.ToString(), *Variables_tmp.VariableValue.ToString());

	}

	RedrawVariablesBlock();
}



void SDialogWindowWidget::AddVariable(FPropertyIndex PropertyIndex)
{

	if (PropertyIndex.iVariable == Variables.Num() - 1)  // if it's last element
	{
		Variables.Add(FVariables());
	}
	else
	{
		Variables.Insert(FVariables(), PropertyIndex.iVariable + 1);
	}

	RedrawVariablesBlock();
}
void SDialogWindowWidget::RemoveVariable(FPropertyIndex PropertyIndex)
{

	if (Variables.Num() == 1) return;

	Variables.RemoveAt(PropertyIndex.iVariable);

	RedrawVariablesBlock();
}

void SDialogWindowWidget::RedrawVariablesBlock()
{
	MainVariablesPanelBlock->ClearChildren();

	FPropertyIndex CurrentPropertyIndex;


	for (int32 i_Var = 0; i_Var < Variables.Num(); i_Var++)
	{
		CurrentPropertyIndex.iVariable = i_Var;

		MainVariablesPanelBlock->AddSlot()
		.Padding(0.f)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		//--.AutoHeight()



		[
			SNew(SHorizontalBox)

			//    -------  Title-Condition    START   -------------
			+SHorizontalBox::Slot()
			.Padding(GetPadding(2.f, 1.f, 0.f, 1.f))        // L, Up, R, Dn
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			//+++++++++.VAlign(VAlign_Center)
			.AutoWidth()
			[
				SNew(SBox)
				//MaxDesiredWidth(FOptionalSize())
				.Padding(0)
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.WidthOverride(5.f * SizeKoef)
				//.HeightOverride(20.f)
				[
					SNew(SBorder)
					.Padding(0)
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.BorderImage(ConditionStart)                  //   Title-Condition    START
				]
			]
							
						
				//   =============   ALL title   =================
			+ SHorizontalBox::Slot()
			.Padding(GetPadding(0.f, 2.f, 0.f, 2.f))        // L, Up, R, Dn
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.FillWidth(1)
			[ 
				SNew(SBox)
				.Padding(GetPadding(0, 0, 0, 0))
				//MaxDesiredWidth(FOptionalSize())
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				//.WidthOverride(20.f)
				.HeightOverride(35.f * SizeKoef)                //     Condition Panel "Height"  -----------   Heigh TITLE-Zone  ------------
				[


					//SNew(SButton)
					//  ==========================  ALL title  ==============================
					SNew(SBorder)
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.BorderImage(Condition)
					[
							
						SNew(SHorizontalBox)


						// ---------------- Button      (Add_Down)      -------------------
						+ SHorizontalBox::Slot()
						.Padding(GetPadding(2.f, 2.f, 2.f, 2.f))        // L, Up, R, Dn
						.HAlign(HAlign_Fill)
						.VAlign(VAlign_Center)
						.AutoWidth()
						//.FillWidth(1)
						[
							SNew(SBox)
							.WidthOverride(20.f * SizeKoef)
							.MaxDesiredHeight(20.f * SizeKoef)
							//.HeightOverride(20.f)
							[
								SNew(SButton)
								.ContentPadding(0)
								.ButtonColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 0.f))
								.OnClicked(this, &SDialogWindowWidget::OnButtonClick, EProppertyToChange::ButtonAdd_Variable, CurrentPropertyIndex)  
								[
									SNew(SImage)
									.Image(ImageAddElement) 
								]						
							]

						]


						// ---------------- Button           (Remove) -------------------
						+ SHorizontalBox::Slot()
						.Padding(GetPadding(2.f, 2.f, 2.f, 2.f))        // L, Up, R, Dn
						.HAlign(HAlign_Fill)
						.VAlign(VAlign_Center)
						.AutoWidth()
						//.FillWidth(1)
						[
							SNew(SBox)
							.WidthOverride(20.f * SizeKoef)
							.MaxDesiredHeight(20.f * SizeKoef)
							//.HeightOverride(20.f)
							[
								SNew(SButton)
								.ContentPadding(0)
								.ButtonColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 0.f))
								.OnClicked(this, &SDialogWindowWidget::OnButtonClick, EProppertyToChange::ButtonRemove_Variable, CurrentPropertyIndex)
							[
									SNew(SImage)
									.Image(ImageDeleteElement)
								]						
							]

						]

						// ---------------- Button          (MOVE-Section)      -------------------
						+ SHorizontalBox::Slot()
						.Padding(GetPadding(2.f, 2.f, 2.f, 2.f))        // L, Up, R, Dn
						.HAlign(HAlign_Fill)
						.VAlign(VAlign_Center)
						.AutoWidth()
						//.FillWidth(1)
						[
							SNew(SBox)
							.WidthOverride(20.f * SizeKoef)
							.MaxDesiredHeight(20.f * SizeKoef)
							//.HeightOverride(20.f)
							[
								SNew(SButton)
								.ContentPadding(0)
								.ButtonColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 0.f))
								///////////.OnClicked(this, &SDialogWindowWidget::OnButtonClick, EProppertyToChange::XXXXXXXXXXXXXXXXXXXXXXXXXXXxxx, CurrentPropertyIndex)  
								[
									SNew(SImage)
									.Image(ImageMoveElement)
								]						
							]

						]



						//     =======================        "VARIABLE-NAME"  +  "VARIABLE-VALUE"   =======================
						+ SHorizontalBox::Slot()
						[

							SNew(SHorizontalBox)


							//    -------  Variables BLOCK       "VARIABLE"  Start   -------------
							+SHorizontalBox::Slot()
							.Padding(GetPadding(2.f, 1.f, 0.f, 1.f))        // L, Up, R, Dn
							.HAlign(HAlign_Left)
							.VAlign(VAlign_Fill)
							//+++++++++.VAlign(VAlign_Center)
							.AutoWidth()
							[
								SNew(SBox)
								//MaxDesiredWidth(FOptionalSize())
								.Padding(0)
								.HAlign(HAlign_Fill)
								.VAlign(VAlign_Fill)
								.WidthOverride(4.f * SizeKoef)
								//.HeightOverride(20.f)
								[
									SNew(SBorder)
									.Padding(0)
									.HAlign(HAlign_Fill)
									.VAlign(VAlign_Fill)
									.BorderImage(PropertyResponseStart)                  //  image  VARIAVLE_BLOCK    Property   "Variable-Name"  Start
								]
							]

							+ SHorizontalBox::Slot()
							.Padding(GetPadding(0, 1, 0, 1))
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Fill)
							//.FillWidth(1)
							.AutoWidth()
							[

								SNew(SBorder)
								.Padding(GetPadding(0, 0, 0, 0))
								.HAlign(HAlign_Fill)
								.VAlign(VAlign_Fill)
								.BorderImage(PropertyResponse)      //  image  VARIAVLE_BLOCK     Property   "Variable-Name"  
								[

									SNew(SHorizontalBox)
									
									//  --------------------------------   Vatiable-Name  --------------------------------
									+ SHorizontalBox::Slot()
									.Padding(GetPadding(2, 1, 2, 1))
									.HAlign(HAlign_Left)
									.VAlign(VAlign_Center)
									.AutoWidth()
									[

										SNew(STextBlock)
										.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 10 * SizeKoef))
										//.ColorAndOpacity(FLinearColor(0.0f, 0.0f, 0.4f, 1))
										.ColorAndOpacity(FLinearColor(0.7f, 0.77f, 1.f, 1))
										.Text(FText::FromString("Var name:"))

									]
									//  --------------------------------   Vatiable-Name  (Button)--------------------------------
									+ SHorizontalBox::Slot()
									.Padding(GetPadding(2, 1, 2, 1))
									.HAlign(HAlign_Left)
									.VAlign(VAlign_Center)
									//777777777777.AutoWidth()
									[																			
										SNew(SButton)
										.ContentPadding(0)
										.HAlign(HAlign_Left)
										.VAlign(VAlign_Center)
										.ButtonColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 0.f))    
										.OnClicked(this, &SDialogWindowWidget::OnButtonClick, EProppertyToChange::Variable_varName, CurrentPropertyIndex)  //VarNamePropperty  //  EProppertyToChange::rep_condition_varName
										[ 
											SNew(SOverlay)  

											+ SOverlay::Slot()           
											.HAlign(HAlign_Fill)
											.VAlign(VAlign_Center)
											//--.AutoWidth()
											[
												SNew(SBox)
												.Padding(GetPadding(0, 4, 0, 6))
												.HAlign(HAlign_Fill)
												.VAlign(VAlign_Fill)
												[
													SNew(SImage)
													.Image(ImageValueZone)      //       ImageValueZone
												]
											]

											+ SOverlay::Slot()
											.HAlign(HAlign_Center)
											.VAlign(VAlign_Center)
											[
												//  ===========================  VARIAVLE_BLOCK   Vatiable-Name StaticText  ================================
												SNew(SHorizontalBox)
														
												+ SHorizontalBox::Slot()
												.Padding(GetPadding(4, 0, 4, 1))
												//+++++.HAlign(HAlign_Fill)
												.HAlign(HAlign_Center)
												.VAlign(VAlign_Center)
												//.FillWidth(1)
												.AutoWidth()
												[
															     
													SNew(STextBlock)
													.Visibility(this, &SDialogWindowWidget::GetVisibilityOfSectionPropperty_Static, EProppertyToChange::Variable_varName, CurrentPropertyIndex)   //VarNamePropperty  //  EProppertyToChange::rep_condition_varName
													.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 12 * SizeKoef))
													.ColorAndOpacity(FLinearColor(0.7f, 0.77f, 1.f, 1))
													.Text(this, &SDialogWindowWidget::GetProppertyText, EProppertyToChange::Variable_varName, CurrentPropertyIndex)   //VarNamePropperty  //  EProppertyToChange::rep_condition_varName
												] 
													     
												+ SHorizontalBox::Slot()
												.HAlign(HAlign_Center)
												.VAlign(VAlign_Center)
												[
													SNew(SBox)
													.MinDesiredWidth(70.f * SizeKoef)
													.HAlign(HAlign_Fill)
													.VAlign(VAlign_Fill)                 
													[ 
														//  ===========================   VARIAVLE_BLOCK  Vatiable-Name EditableText  ================================
														SAssignNew(Variables[i_Var].ChangeVariable_Name_Editable, SEditableTextBox)
														.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 12 * SizeKoef))
														.Visibility(this, &SDialogWindowWidget::GetVisibilityOfSectionPropperty_Editable, EProppertyToChange::Variable_varName, CurrentPropertyIndex)   //VarNamePropperty  //  EProppertyToChange::rep_condition_varName
														.Text(FText::FromString(Variables[i_Var].VariableName.ToString()))
														
														.OnTextCommitted(this, &SDialogWindowWidget::ConfirmEditableTextBox, EProppertyToChange::Variable_varName, CurrentPropertyIndex)  // PRES_ENTER:   void ConfirmEditableTextBox(const FText& Text, ETextCommit::Type TextType);
														.OnTextChanged_Raw(this, &SDialogWindowWidget::OnEditableTextChange)  // void OnButtonT(const FText& Text);
													]
												]
														 
											]
										]
	
									]

								]
							]

							//    -------   VARIAVLE_BLOCK       "Variable-Name"  End   -------------
							+SHorizontalBox::Slot()
							.Padding(GetPadding(0.f, 1.f, 2.f, 1.f))        // L, Up, R, Dn
							.HAlign(HAlign_Left)
							.VAlign(VAlign_Fill)
							//+++++++++.VAlign(VAlign_Center)
							.AutoWidth()
							[
								SNew(SBox)
								//MaxDesiredWidth(FOptionalSize())
								.Padding(0)
								.HAlign(HAlign_Fill)
								.VAlign(VAlign_Fill)
								.WidthOverride(4.f * SizeKoef)
								//.HeightOverride(20.f)
								[
									SNew(SBorder)
									.Padding(0)
									.HAlign(HAlign_Fill)
									.VAlign(VAlign_Fill)
									.BorderImage(PropertyResponseEnd)                  //  image  Condition-Property   "Variable-Name"  End
								]
							]
											
						]

						//     =======================    VARIAVLE_BLOCK      "VARIABLE-Value"    =======================
						+ SHorizontalBox::Slot()
						.HAlign(HAlign_Right)
						.VAlign(VAlign_Fill)
						[

							SNew(SHorizontalBox)


								//    -------  VARIAVLE_BLOCK   "VARIABLE-Value"  Start   -------------
							+SHorizontalBox::Slot()
							.Padding(GetPadding(2.f, 1.f, 0.f, 1.f))        // L, Up, R, Dn
							.HAlign(HAlign_Right)
							.VAlign(VAlign_Fill)
							//+++++++++.VAlign(VAlign_Center)
							.AutoWidth()
							[
								SNew(SBox)
								//MaxDesiredWidth(FOptionalSize())
								.Padding(0)
								.HAlign(HAlign_Fill)
								.VAlign(VAlign_Fill)
								.WidthOverride(4.f * SizeKoef)
								//.HeightOverride(20.f)
								[
									SNew(SBorder)
									.Padding(0)
									.HAlign(HAlign_Fill)
									.VAlign(VAlign_Fill)
									.BorderImage(PropertyResponseStart)                  //  image  Condition-Property   "Variable-Value"  Start
								]
							]

							+ SHorizontalBox::Slot()
							.Padding(GetPadding(0, 1, 0, 1))
							.HAlign(HAlign_Right)
							.VAlign(VAlign_Fill)
							//.FillWidth(1)
							.AutoWidth()
							[

								SNew(SBorder)
								.Padding(GetPadding(0, 0, 0, 0))
								.HAlign(HAlign_Fill)
								.VAlign(VAlign_Fill)
								.BorderImage(PropertyResponse)      //  image  VARIAVLE_BLOCK   "Variable-Value"  
								[

									SNew(SHorizontalBox)

									//  --------------------------------  VARIAVLE_BLOCK    Vatiable-Value  --------------------------------
									+ SHorizontalBox::Slot()
									.Padding(GetPadding(2, 1, 2, 1))
									.HAlign(HAlign_Left)
									.VAlign(VAlign_Center)
									.AutoWidth()
									[

										SNew(STextBlock)
										.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 10 * SizeKoef))
										//.ColorAndOpacity(FLinearColor(0.0f, 0.0f, 0.4f, 1))
										.ColorAndOpacity(FLinearColor(0.7f, 0.77f, 1.f, 1))
										.Text(FText::FromString("Var value:"))

									]
									//  --------------------------------VARIAVLE_BLOCK     Vatiable-Value  (Button)--------------------------------
									+ SHorizontalBox::Slot()
									.Padding(GetPadding(2, 1, 2, 1))
									.HAlign(HAlign_Left)
									.VAlign(VAlign_Center)
									//777777777777.AutoWidth()
									[																			
										SNew(SButton) 
										.ContentPadding(0)
										.HAlign(HAlign_Left)
										.VAlign(VAlign_Center)
										.ButtonColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 0.f))    
										.OnClicked(this, &SDialogWindowWidget::OnButtonClick, EProppertyToChange::Variable_varValue, CurrentPropertyIndex)  
										[ 
											SNew(SOverlay)  

											+ SOverlay::Slot()           
											.HAlign(HAlign_Fill)
											.VAlign(VAlign_Center)
											//--.AutoWidth()
											[
												SNew(SBox)
												.Padding(GetPadding(0, 4, 0, 6))
												.HAlign(HAlign_Fill)
												.VAlign(VAlign_Fill)
												[
													SNew(SImage)
													.Image(ImageValueZone)      //       ImageValueZone
												]
											]

											+ SOverlay::Slot()
											.HAlign(HAlign_Center)
											.VAlign(VAlign_Center)
											[
												//  ======================   VARIAVLE_BLOCK    Vatiable-Value StaticText  =========================
												SNew(SHorizontalBox)
														
												+ SHorizontalBox::Slot()
												.Padding(GetPadding(4, 0, 4, 1))
												//+++++.HAlign(HAlign_Fill)
												.HAlign(HAlign_Center)
												.VAlign(VAlign_Center)
												//.FillWidth(1)
												.AutoWidth()
												[
															     
													SNew(STextBlock)
													.Visibility(this, &SDialogWindowWidget::GetVisibilityOfSectionPropperty_Static, EProppertyToChange::Variable_varValue, CurrentPropertyIndex)
													.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 12 * SizeKoef))
													.ColorAndOpacity(FLinearColor(0.7f, 0.77f, 1.f, 1))
													.Text(this, &SDialogWindowWidget::GetProppertyText, EProppertyToChange::Variable_varValue, CurrentPropertyIndex)
												] 
													     
												+ SHorizontalBox::Slot()
												.HAlign(HAlign_Center)
												.VAlign(VAlign_Center)
												[
													SNew(SBox)
													.MinDesiredWidth(70.f * SizeKoef)
													.HAlign(HAlign_Fill)
													.VAlign(VAlign_Fill)                 
													[ 
														//  ===========================    Vatiable-Value EditableText  ================================
														SAssignNew(Variables[i_Var].ChangeVariable_Value_Editable, SEditableTextBox)
														.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 12 * SizeKoef))
														.Visibility(this, &SDialogWindowWidget::GetVisibilityOfSectionPropperty_Editable, EProppertyToChange::Variable_varValue, CurrentPropertyIndex)  // VarValuePropperty  // EProppertyToChange::rep_condition_varValue
														.Text(FText::FromString(Variables[i_Var].VariableValue.ToString()))
														//.Text(FText::FromString(DialogSection[i_Dlg].SpeechSection[i_Speech]
														//	.ReplicSection[i_Replic].RepSection[i_Rep].RepCondition[i_RepCondition].VariableValue.ToString()))
														.OnTextCommitted(this, &SDialogWindowWidget::ConfirmEditableTextBox, EProppertyToChange::Variable_varValue, CurrentPropertyIndex)  // PRES_ENTER:   void ConfirmEditableTextBox(const FText& Text, ETextCommit::Type TextType);
														.OnTextChanged_Raw(this, &SDialogWindowWidget::OnEditableTextChange)  // void OnButtonT(const FText& Text);
													]
												]
														 
											]
										]
	
									]

								]
							]
											
							//    -------  VARIAVLE_BLOCK   "Variable-Value"  End   -------------
							+SHorizontalBox::Slot()
							.Padding(GetPadding(0.f, 1.f, 2.f, 1.f))        // L, Up, R, Dn
							.HAlign(HAlign_Right)
							.VAlign(VAlign_Fill)
							//+++++++++.VAlign(VAlign_Center)
							.AutoWidth()
							[
								SNew(SBox)
								//MaxDesiredWidth(FOptionalSize())
								.Padding(0)
								.HAlign(HAlign_Fill)
								.VAlign(VAlign_Fill)
								.WidthOverride(4.f * SizeKoef)
								//.HeightOverride(20.f)
								[
									SNew(SBorder)
									.Padding(0)
									.HAlign(HAlign_Fill)
									.VAlign(VAlign_Fill)
									.BorderImage(PropertyResponseEnd)                  //  image  Condition-Property   "Variable-Value"  End
								]
							]
											
						]

					] // Border Title
				]
								
			]

			//    -------  Title-Condition    End   -------------
			+SHorizontalBox::Slot()
			.Padding(GetPadding(0.f, 2.f, 2.f, 2.f))        // L, Up, R, Dn
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			//+++++++++.VAlign(VAlign_Center)
			.AutoWidth()
			[
				SNew(SBox)
				//MaxDesiredWidth(FOptionalSize())
				.Padding(0)
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.WidthOverride(5.f * SizeKoef)
				//.HeightOverride(20.f)
				[
					SNew(SBorder)
					.Padding(0)
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.BorderImage(ConditionEnd)                  //   Title-variable    End
				]
			]
		];
	} //    Variables Block
}

//  -------------------------------------------------------------------------------------------------------------------------------
//  ----------------------------------                   Variables BLOCK      End                 ----------------------------------
//  -------------------------------------------------------------------------------------------------------------------------------




//  ===============================================================================================================================
//  ===============================================================================================================================
//  ==================================                SOUND BLOCK                      ==================================
//  ===============================================================================================================================
//  ===============================================================================================================================
FReply SDialogWindowWidget::AddSpekerSound(int32 iSpeker)
{
	iCurrentEditableSpeker = -1;
	iCurrentEditableSound = -1;
	vMainSpikersEditablePanel_FindImage = EVisibility::Collapsed;
	vMainSpikersEditablePanel_FindSound = EVisibility::Collapsed;
	MainSpikersEditablePanelBlock->ClearChildren();   //  CLear Speker-EditablePanel

	FString NewName = FString("NewSoundName");
	for (int32 i_Speker = 0; i_Speker < Speker.Num(); i_Speker++)
	{
		for (int32 i_Sound = 0; i_Sound < Speker[i_Speker].Sound.Num(); i_Sound++)
		{
			//FName nnnnnnnnnnnnn = Speker[i_Speker].Sound[i_Sound].name;
			if (Speker[i_Speker].Sound[i_Sound].name == FName(*NewName))
			{
				int32 rnd = FMath::RandRange(0, 100);
				NewName += FString("_") + FString::FromInt(rnd);
				i_Speker = 0;
				i_Sound = 0;
			}
		}
	}

	FSound SoundTMP;
	SoundTMP.SoundComment = FString("It's a comments of your sound-phrase");
	SoundTMP.SoundAssetPath = FString("/PugiXML_Plagin/res/ItIsADialog.ItIsADialog");
	SoundTMP.name = FName(*NewName);

	Speker[iSpeker].Sound.Add(SoundTMP);

	RedrawSoundsBlock(iSpeker);

	return FReply::Handled();
}


void SDialogWindowWidget::RedrawSoundsBlock(int32 iSpeker)
{
	Speker[iSpeker].SounsScroll->ClearChildren();

	//MainSpikersEditablePanelBlock->ClearChildren();   //  CLear Speker-EditablePanel
	//FPropertyIndex PropertyIndex;

	for (int32 i_Sound = 0; i_Sound < Speker[iSpeker].Sound.Num(); i_Sound++)
	{
		//PropertyIndex.SpekerIndex = i;

		//if(Speker[i].SpekersImageBrush)
		//{
		Speker[iSpeker].SounsScroll->AddSlot()
			.Padding(0.f)
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			
			//.AutoHeight()
			[
				SNew(SBorder)
				.Clipping(EWidgetClipping::ClipToBounds)
				[
					SNew(SButton)
					.ContentPadding(0)
					//.ButtonColorAndOpacity(FLinearColor(0.5f, 0, 1, 0.2f))
					.ButtonColorAndOpacity(this, &SDialogWindowWidget::GetSelectedSoundItem_Color, iSpeker, i_Sound)
					//.ButtonColorAndOpacity_Lambda([this]()-> FSlateColor { return SelectedSoundItemColor; })
					.OnClicked(this, &SDialogWindowWidget::ShowSpekerSoundItem, iSpeker, i_Sound)  
					
					[
						SNew(SHorizontalBox)

						+ SHorizontalBox::Slot()
						.Padding(1, 0, 0, 0)
						.AutoWidth()
						.HAlign(HAlign_Left)
						.VAlign(VAlign_Fill)
						[
							SNew(SButton)
							.ContentPadding(0)
							.ButtonColorAndOpacity(FLinearColor(1, 1, 1, 0))
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Fill)
							.OnClicked(this, &SDialogWindowWidget::PlaySoundItem, iSpeker, i_Sound)
							[
								SNew(SBox)
								.HeightOverride(25.f * SizeKoef)
								.WidthOverride(25.f * SizeKoef)
								//.MaxDesiredWidth(64.f)
								//.MaxDesiredHeight(64.f)
								[								
									SNew(SImage)
									.Image(PlaySound)
									//SNew(STextBlock).Text(FText::FromString("11111111111111111111111111111222222222222222222222222222223333333333333333333333333333333333333333333344444444444444444444444444444444444444555555555555555555555555555555555555566666666666666666666666666667777777777777777777777777777777777888888888888888888888888888888888889999999999999999999999999999999999wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww"))
								]
							]
						]
						+ SHorizontalBox::Slot()
						.Padding(GetPadding(1, 0, 0, 0))
						.AutoWidth()
						//.FillWidth(1)
						.HAlign(HAlign_Left)
						.VAlign(VAlign_Fill)
						[ 
							SNew(SButton)
							.OnClicked(this, &SDialogWindowWidget::ChangeSpekerSoundItem, iSpeker, i_Sound)
							[
								SNew(STextBlock).Text(FText::FromString("Audio"))
							]
						] 
						+ SHorizontalBox::Slot()
						.Padding(GetPadding(4, 0, 0, 0))
						.FillWidth(1)
						.HAlign(HAlign_Left)
						.VAlign(VAlign_Center)
						[
							SNew(SBox)
							.Padding(FMargin(0,0,0,0))
							.HAlign(HAlign_Left)
							.VAlign(VAlign_Center)
							[
								//SNew(STextBlock).Text(FText::FromString("dd"))
								SNew(STextBlock)
								.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 12 * SizeKoef))
								.ColorAndOpacity(FLinearColor(0.7f, 0.77f, 1.f, 1))
								.Text(this, &SDialogWindowWidget::GetSoundNameText, iSpeker, i_Sound)
								//.Text(GetSoundNameText(iSpeker, i_Sound))
							] 
						]
					]
				]
			];

	}
}

FReply SDialogWindowWidget::PlaySoundItem(int32 iSpeker, int32 iSound)
{
	iCurrentEditableSpeker = iSpeker;
	iCurrentEditableSound = iSound;
	//USoundBase* MySoundWave = LoadObject<USoundBase>(this, TEXT("/Game/VoiceSound/Dialog_Test.Dialog_Test"));

	if (iSpeker != -1 && iSound != -1)
	{
		UObject* EditorWorld = GEditor->GetEditorWorldContext().World();
		if (EditorWorld)
		{
			USoundBase* MySoundWave = LoadObject<USoundBase>(EditorWorld, *Speker[iCurrentEditableSpeker].Sound[iCurrentEditableSound].SoundAssetPath);

			if (MySoundWave)
			{
				UGameplayStatics::PlaySound2D(EditorWorld, MySoundWave);
			}
		}
	}
	return FReply::Handled();
}

FSlateColor SDialogWindowWidget::GetSelectedSoundItem_Color(int32 iSpeker, int32 iSound) const
{
	if (iCurrentEditableSpeker == -1 ||	iCurrentEditableSound == -1) return FSlateColor(UnSelectedSoundItemColor);

	if (iCurrentEditableSpeker == iSpeker && iCurrentEditableSound == iSound) return FSlateColor(SelectedSoundItemColor);

	return FSlateColor(UnSelectedSoundItemColor);
}


FReply SDialogWindowWidget::ShowSpekerSoundItem(int32 iSpeker, int32 iSound)
{
	iCurrentEditableSpeker = iSpeker;
	iCurrentEditableSound = iSound;
	vMainSpikersEditablePanel_FindImage = EVisibility::Collapsed;
	vMainSpikersEditablePanel_FindSound = EVisibility::Collapsed;
	MainSpikersEditablePanelBlock->ClearChildren();   //  CLear Speker-EditablePanel

	MainSpikersEditablePanelBlock->AddSlot()
		.Padding(GetPadding(3.f, 3.f, 3.f, 3.f))
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		//--.AutoHeight()
		[
				SNew(SVerticalBox)

				+ SVerticalBox::Slot()
				.Padding(GetPadding(3, 3, 0, 0))
				.HAlign(HAlign_Left)
				.VAlign(VAlign_Top)
				.AutoHeight()
				[
					SNew(STextBlock)
					.AutoWrapText(true)
					.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 11 * SizeKoef))
					.ColorAndOpacity(FLinearColor(0.7f, 0.77f, 1.f, 1))
					.Text(FText::FromString("Name:"))
				]
				+ SVerticalBox::Slot()
				.Padding(GetPadding(3, 3, 0, 0))
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Top)
				.AutoHeight()
				[
					SNew(SEditableTextBox)
					.BackgroundColor(FLinearColor(1, 1, 1, 0))
					.ForegroundColor(FLinearColor(0.7f, 0.77f, 1.f, 1))
					.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 16 * SizeKoef))
					.Text(this, &SDialogWindowWidget::GetSoundNameText, iSpeker, iSound)
					.OnTextCommitted(this, &SDialogWindowWidget::SpekerSoundNameEditableTextBox, iSpeker, iSound)
					//.OnTextChanged_Raw(this, &SDialogWindowWidget::OnEditableTextChange)  // void OnButtonT(const FText& Text);
				]

				+ SVerticalBox::Slot()
				.Padding(GetPadding(3, 5, 0, 0))
				.HAlign(HAlign_Left)
				.VAlign(VAlign_Top)
				.AutoHeight()
				[
					SNew(STextBlock)
					.AutoWrapText(true)
					.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 11 * SizeKoef))
					.ColorAndOpacity(FLinearColor(0.7f, 0.77f, 1.f, 1))
					.Text(FText::FromString("Comment:"))
				]
				+ SVerticalBox::Slot()
				.Padding(GetPadding(3, 3, 0, 0))
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Top)
				.AutoHeight()
				[
					SNew(SMultiLineEditableTextBox)
					.BackgroundColor(FLinearColor(1, 1, 1, 0))
					.ForegroundColor(FLinearColor(0.7f, 0.77f, 1.f, 1))
					.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 16 * SizeKoef))
					.Text(this, &SDialogWindowWidget::GetSoundCommentText, iSpeker, iSound)
					.OnTextCommitted(this, &SDialogWindowWidget::SpekerSoundCommentEditableTextBox, iSpeker, iSound)
					//.OnTextChanged_Raw(this, &SDialogWindowWidget::OnEditableTextChange)  // void OnButtonT(const FText& Text);
				]

				+ SVerticalBox::Slot()
				.Padding(GetPadding(3, 5, 0, 0))
				.HAlign(HAlign_Left)
				.VAlign(VAlign_Top)
				.AutoHeight()
				[
					SNew(STextBlock)
					.AutoWrapText(true)
					.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 11 * SizeKoef))
					.ColorAndOpacity(FLinearColor(0.7f, 0.77f, 1.f, 1))
					.Text(FText::FromString("Audio data:"))
				]

				+ SVerticalBox::Slot()
				.Padding(GetPadding(3, 5, 0, 0))
				.HAlign(HAlign_Left)
				.VAlign(VAlign_Top)
				.AutoHeight()
				[
					SNew(STextBlock)
					.AutoWrapText(true)
					.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 14 * SizeKoef))
					.ColorAndOpacity(FLinearColor(0.7f, 0.77f, 1.f, 0.5))
					.Text(this, &SDialogWindowWidget::GetSoundPathText, iSpeker, iSound)
				]

				+ SVerticalBox::Slot()
				.Padding(GetPadding(3, 8, 0, 0))
				.HAlign(HAlign_Left)
				.VAlign(VAlign_Top)
				.AutoHeight()
				[
					SNew(SHorizontalBox)

					+ SHorizontalBox::Slot()
					.HAlign(HAlign_Left)
					.VAlign(VAlign_Top)
					.AutoWidth()
					[
						SNew(SButton)
						.ContentPadding(0)
						.ButtonColorAndOpacity(FLinearColor(1, 1, 1, 0))
						.HAlign(HAlign_Left)
						.VAlign(VAlign_Fill)
						.OnClicked(this, &SDialogWindowWidget::PlaySoundItem, iSpeker, iSound)
						[
							SNew(SBox)
							.HeightOverride(25.f * SizeKoef)
							.WidthOverride(25.f * SizeKoef)
							//.MaxDesiredWidth(64.f)
							//.MaxDesiredHeight(64.f)
							[								
								SNew(SImage)
								.Image(PlaySound)
							]
						]
					]
				 
					+ SHorizontalBox::Slot()
					.Padding(GetPadding(4, 0, 0, 0))
					.AutoWidth()
					//.FillWidth(1)
					.HAlign(HAlign_Left)
					.VAlign(VAlign_Fill)
					[ 
						SNew(SButton)
						.OnClicked(this, &SDialogWindowWidget::ChangeSpekerSoundItem, iSpeker, iSound)
						[
							SNew(STextBlock).Text(FText::FromString("Audio"))
						]
					] 
				]


		];

	return FReply::Handled();
}




//  =======  Get EngineSoundResource and Draw in "MainSpikersEditablePanelBlock" ========
FReply SDialogWindowWidget::ChangeSpekerSoundItem(int32 iSpeker, int32 iSound)
{	
	vMainSpikersEditablePanel_FindImage = EVisibility::Collapsed;
	vMainSpikersEditablePanel_FindSound = EVisibility::Visible;
	iCurrentEditableSpeker = iSpeker;
	iCurrentEditableSound = iSound;
	    
	AssetSoundPath.Empty();
	AssetPathName.Empty();
	AssetPathSortByName.Empty();
	FindedText_InMainSpikerEditablePanel = FString("");
	//AssetImageBrush.Empty();

	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	TArray<FAssetData> AssetData;
	//AssetRegistryModule.Get().GetAssetsByClass(FName("MediaTexture"), AssetData);
	AssetRegistryModule.Get().GetAssetsByClass(FName("SoundWave"), AssetData);
	for (int i = 0; i < AssetData.Num(); i++)
	{
		//UMediaTexture* FoundMedia = Cast<UMediaTexture>(AssetData[i].GetAsset());
		USoundBase* FoundSoundBaseItem = Cast<USoundBase>(AssetData[i].GetAsset());
		if (FoundSoundBaseItem != NULL)
		{
			AssetSoundPath.Add(AssetData[i].GetFullName());
			
			// ----- get only Name in FullPathStr  -----
			int32 CutStartTMP = AssetSoundPath.Last().Find(FString("/"), ESearchCase::Type::CaseSensitive, ESearchDir::Type::FromEnd);
			int32 NumTMP = AssetSoundPath.Last().Len() - CutStartTMP;
			FString StrPathNameTmp = AssetSoundPath.Last().Mid(CutStartTMP + NumTMP/2 + 1, NumTMP);
			AssetPathName.Add(StrPathNameTmp);
			AssetPathSortByName.Add(i);

		}
	}

	//  ------  Draw faunded Item in FindingBlock  -------- 
	RedrawSpekerSoundFindingItem(iSpeker, iSound);


	return FReply::Handled();
}

//  ----- Fast Find ------
void SDialogWindowWidget::MainSpikersEditablePanel_FindExtBlock(const FText& _Text, int32 type)  // type: 1=Sound, 2=Image
{
	FindedText_InMainSpikerEditablePanel = _Text.ToString();
	AssetPathSortByName.Empty();
	for (int32 i = 0; i < AssetPathName.Num(); i++)
	{
		if (FindedText_InMainSpikerEditablePanel != _Text.ToString()) return;
		if (AssetPathName[i].Contains(_Text.ToString(), ESearchCase::Type::IgnoreCase, ESearchDir::Type::FromStart))
		{

			AssetPathSortByName.Add(i);
		}
	}
	//IsStartFinding = false;  //++++++++++++++
	if(type == 1) RedrawSpekerSoundFindingItem(iCurrentEditableSpeker, iCurrentEditableSound);  // 1=Sound
	else if (type == 2) RedrawSpekerImageFindingItem(0, 0);  // // 2=Image

	//UE_LOG(LogTemp, Warning, TEXT("-------------  %s"), *_Text.ToString());
}

void SDialogWindowWidget::RedrawSpekerSoundFindingItem(int32 iSpeker, int32 iSound)
{ 

	//IsStartFinding = true;  //++++++++++++++++

	MainSpikersEditablePanelBlock->ClearChildren();


	for (int32 i = 0; i < AssetPathSortByName.Num(); i++)
	{
		if (AssetPathSortByName[i] < 0 || AssetPathSortByName[i] > AssetPathName.Num() - 1) continue;
		//if (!IsStartFinding) return;  //+++++++++++++

		MainSpikersEditablePanelBlock->AddSlot()
		.Padding(GetPadding(3.f, 3.f, 3.f, 3.f))
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		//--.AutoHeight()
		[
			SNew(SButton)
			.ContentPadding(0)
			.ButtonColorAndOpacity(FLinearColor(1, 1, 1, 0))
			.OnClicked(this, &SDialogWindowWidget::ApplaySaundToSpekerSound, iSpeker, iSound, AssetPathSortByName[i])
			[
					SNew(STextBlock)
					.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 12 * SizeKoef))
					.ColorAndOpacity(FLinearColor(0.7f, 0.77f, 1.f, 1))
					.Text(FText::FromString(AssetPathName[AssetPathSortByName[i]]))
			]

		];
	}
}

FReply SDialogWindowWidget::ApplaySaundToSpekerSound(int32 iSpeker, int32 iSpekerSound, int32 iSound)
{
	Speker[iSpeker].Sound[iSpekerSound].SoundAssetPath = AssetSoundPath[iSound];
	Speker[iSpeker].Sound[iSpekerSound].SoundAssetPath.RemoveFromStart("SoundWave ");


	//changingSpeker_Index = -1;
	iCurrentEditableSpeker = -1;
	iCurrentEditableSound = -1;
	vMainSpikersEditablePanel_FindImage = EVisibility::Collapsed;
	vMainSpikersEditablePanel_FindSound = EVisibility::Collapsed;
	MainSpikersEditablePanelBlock->ClearChildren();   //  CLear Speker-EditablePanel


	ShowSpekerSoundItem(iSpeker, iSpekerSound);

	SaveSpekersToXML();

	return FReply::Handled();
}


FText SDialogWindowWidget::GetSoundNameText(int32 _iSpeker, int32 _iSound) const
{
	return FText::FromString(Speker[_iSpeker].Sound[_iSound].name.ToString());
}

FText SDialogWindowWidget::GetSoundCommentText(int32 _iSpeker, int32 _iSound) const
{
	return FText::FromString(Speker[_iSpeker].Sound[_iSound].SoundComment);
}

FText SDialogWindowWidget::GetSoundPathText(int32 _iSpeker, int32 _iSound) const
{
	return FText::FromString(Speker[_iSpeker].Sound[_iSound].SoundAssetPath);
}

void SDialogWindowWidget::SpekerSoundNameEditableTextBox(const FText& Text, ETextCommit::Type TextType, int32 iSpeker, int32 iSpekerSound)
{
	Speker[iSpeker].Sound[iSpekerSound].name = FName(*Text.ToString());
}

void SDialogWindowWidget::SpekerSoundCommentEditableTextBox(const FText& Text, ETextCommit::Type TextType, int32 iSpeker, int32 iSpekerSound)
{
	Speker[iSpeker].Sound[iSpekerSound].SoundComment = Text.ToString();
}
  
  
//  ===========================================================================================================================================================
//  ===========================================================================================================================================================
//  ===========================================================================================================================================================
//  ==================================================                   SPEKER BLOCK                      ===================================================
//  ===========================================================================================================================================================
//  ===========================================================================================================================================================
//  ===========================================================================================================================================================






FReply SDialogWindowWidget::StoredSpekerIndex(EProppertyToChange _ProppertyToChange, int32 _index)
{
	 
	FPropertyIndex PropertyIndex;
	PropertyIndex.SpekerIndex = _index;
	ConfirmCurrentSelection(_ProppertyToChange, PropertyIndex);

	//changingSpeker_Index = _index;
	//changingPropperty = EProppertyToChange::none;

	Speker[_index].IsSectionEditNow = true;


	FSlateApplication::Get().SetKeyboardFocus(Speker[_index].SpekerName_Editable.ToSharedRef());


	return FReply::Handled();
}


const FSlateBrush* SDialogWindowWidget::GetSpekerImage(int32 _index) const
{
	if (Speker[_index].SpekersImageBrush.HasUObject())
		return &Speker[_index].SpekersImageBrush;
	else
		return SpekersImageDefault;
}


FReply SDialogWindowWidget::ApplayImageAssetToSpeker(int32 _index)
{
	vMainSpikersEditablePanel_FindImage = EVisibility::Collapsed;

	Speker[iCurrentEditableSpeker].SpekersAssetPath = AssetImagePath[_index];
	//Speker[changingSpeker_Index].SpekersAssetPath = AssetImagePath[_index];
	Speker[iCurrentEditableSpeker].SpekersImageBrush = AssetImageBrush[_index];
	//Speker[changingSpeker_Index].SpekersImageBrush = AssetImageBrush[_index];
	Speker[iCurrentEditableSpeker].SpekersAssetPath.RemoveFromStart("Texture2D ");
	//Speker[changingSpeker_Index].SpekersAssetPath.RemoveFromStart("Texture2D ");

	iCurrentEditableSpeker = -1;
	iCurrentEditableSound = -1;
	//changingSpeker_Index = -1;
	vMainSpikersEditablePanel_FindImage = EVisibility::Collapsed;
	vMainSpikersEditablePanel_FindSound = EVisibility::Collapsed;
	MainSpikersEditablePanelBlock->ClearChildren();   //  CLear Speker-EditablePanel


	SaveSpekersToXML();

	return FReply::Handled();
}


FReply SDialogWindowWidget::RemoveSpekerElenemt(int32 _index)
{
	Speker.RemoveAt(_index);

	iCurrentEditableSpeker = -1;
	iCurrentEditableSound = -1;
	vMainSpikersEditablePanel_FindImage = EVisibility::Collapsed;
	vMainSpikersEditablePanel_FindSound = EVisibility::Collapsed;
	MainSpikersEditablePanelBlock->ClearChildren();   //  CLear Speker-EditablePanel


	RedrawSpekersBlock();

	return FReply::Handled();
}






EVisibility SDialogWindowWidget::GetVisibilitySpekerNameText_Static(int32 _Index) const
{
	if (Speker[_Index].IsSectionEditNow)										return EVisibility::Collapsed;
	else																		return EVisibility::Visible;
}

EVisibility SDialogWindowWidget::GetVisibilitySpekerNameText_Editable(int32 _Index) const
{
	if (Speker[_Index].IsSectionEditNow)										return EVisibility::Visible;
	else																		return EVisibility::Collapsed;
}




FText SDialogWindowWidget::GetSpikerNameText(int32 _Index) const
{
	return FText::FromString(Speker[_Index].name.ToString());
}
 


void SDialogWindowWidget::LoadSoundFromXMLSpeker(FName FoundingSpeker)
{

	FString DialogXmlContentPath = FPaths::ProjectContentDir() + FString("Dialog/") + FString("Spekers.xml");
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	if (!PlatformFile.FileExists(*DialogXmlContentPath))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, DialogXmlContentPath);
		//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, FString("Not EXIST"));
		return;
	}

	//  Get xmlFile Content
	pugi::xml_document xmlDoc;
	//pugi::xml_parse_result parse_Res = xmlDoc.load_file(TCHAR_TO_ANSI(*PathToFile));   //++++++
	pugi::xml_parse_result parse_Res = xmlDoc.load_file(StringCast<ANSICHAR>(*DialogXmlContentPath).Get());  //+++++
	if (!parse_Res)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, FString("XML-File Parse ERROR"));
		return;
	}

	Sound.Empty();
	
	//  Get Root Node
	pugi::xml_node RootNode = xmlDoc.child("game_spekers");
	//std::string RootNodeStr(RootNode.attribute("name").as_string());

	//  Go throu all root
	pugi::xpath_node_set SpekerNode = RootNode.select_nodes("speker");
	for (int32 i = 0; i < SpekerNode.size(); i++)
	{
		std::string AttributName_STD(SpekerNode[i].node().attribute("name").as_string());
		FString SpekerNameStr(AttributName_STD.c_str());
		if (FName(SpekerNameStr) == FoundingSpeker)
		{
			//FSound Sound_tmp;

			pugi::xpath_node_set SoundNode = SpekerNode[i].node().select_nodes("sound");
			for (int32 i_Sound = 0; i_Sound < SoundNode.size(); i_Sound++)
			{
				FSound Sound_tmp;

				std::string STD_SoundNameString(SoundNode[i_Sound].node().attribute("name").as_string());
				FString SoundNameString(STD_SoundNameString.c_str());
				Sound_tmp.name = FName(*SoundNameString);

				std::string STD_SoundPanhString(SoundNode[i_Sound].node().text().as_string());
				FString SoundPanhString(STD_SoundPanhString.c_str());
				SoundPanhString.TrimStartAndEndInline();               //  remove \t \n
				Sound_tmp.SoundAssetPath = SoundPanhString;

				std::string STD_SoundCommentString(SoundNode[i_Sound].node().child("sound_comment").text().as_string());
				FString SoundCommentString(STD_SoundCommentString.c_str());
				SoundCommentString.TrimStartAndEndInline();               //  remove \t \n
				Sound_tmp.SoundComment = SoundCommentString;

				Sound.Add(Sound_tmp);
			}
		}
	}
}
	
void SDialogWindowWidget::LoadSpekersfromXML()
{
	
	FString DialogXmlContentPath = FPaths::ProjectContentDir() + FString("Dialog/") + FString("Spekers.xml");
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	if (!PlatformFile.FileExists(*DialogXmlContentPath))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, DialogXmlContentPath);
		//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, FString("Not EXIST"));
		return;
	}

	//  Get xmlFile Content
	pugi::xml_document xmlDoc;
	//pugi::xml_parse_result parse_Res = xmlDoc.load_file(TCHAR_TO_ANSI(*PathToFile));   //++++++
	pugi::xml_parse_result parse_Res = xmlDoc.load_file(StringCast<ANSICHAR>(*DialogXmlContentPath).Get());  //+++++
	if (!parse_Res)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, FString("XML-File Parse ERROR"));
		return;
	}


	Speker.Empty();

	//  Get Root Node
	pugi::xml_node RootNode = xmlDoc.child("game_spekers");
	//std::string RootNodeStr(RootNode.attribute("name").as_string());

	//  Go throu all root
	pugi::xpath_node_set SpekerNode = RootNode.select_nodes("speker");
	for (int32 i = 0; i < SpekerNode.size(); i++)
	{
		FSpekers Speker_tmp;

		std::string STD_SpekerNameStr(SpekerNode[i].node().attribute("name").as_string());
		std::wstring STD_SpekerName_wchar_t = pugi::as_wide(STD_SpekerNameStr.c_str());
		FString SpekerNameStr(STD_SpekerName_wchar_t.c_str());

		Speker_tmp.name = FName(*SpekerNameStr);



		STD_SpekerNameStr = SpekerNode[i].node().text().as_string();
		SpekerNameStr = FString(STD_SpekerNameStr.c_str());
		SpekerNameStr.TrimStartAndEndInline();               //  remove \t \n
		//SpekerNameStr.TrimStartAndEnd();
		Speker_tmp.SpekersAssetPath = SpekerNameStr;
		

		UTexture2D * tmpTexture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *(Speker_tmp.SpekersAssetPath)));
		if (tmpTexture)	Speker_tmp.SpekersImageBrush = UWidgetBlueprintLibrary::MakeBrushFromTexture(tmpTexture, 64, 64);

		//  -------  sound --------
		pugi::xpath_node_set SoundNode = SpekerNode[i].node().select_nodes("sound");
		for (int32 i_Sound = 0; i_Sound < SoundNode.size(); i_Sound++)
		{
			FSound Sound_tmp;

			std::string STD_SoundNameString(SoundNode[i_Sound].node().attribute("name").as_string());
			FString SoundNameString(STD_SoundNameString.c_str());
			Sound_tmp.name = FName(*SoundNameString);

			std::string STD_SoundPanhString(SoundNode[i_Sound].node().text().as_string());
			FString SoundPanhString(STD_SoundPanhString.c_str());
			SoundPanhString.TrimStartAndEndInline();               //  remove \t \n
			Sound_tmp.SoundAssetPath = SoundPanhString;

			std::string STD_SoundCommentString(SoundNode[i_Sound].node().child("sound_comment").text().as_string());
			FString SoundCommentString(STD_SoundCommentString.c_str());
			SoundCommentString.TrimStartAndEndInline();               //  remove \t \n
			Sound_tmp.SoundComment = SoundCommentString;

			Speker_tmp.Sound.Add(Sound_tmp);
		}

	

		Speker.Add(Speker_tmp);

		RedrawSpekersBlock();

		//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FoundedString);
		//UE_LOG(LogTemp, Warning, TEXT("replic-------: = '%s'"), *FoundedString);

	}
}




void SDialogWindowWidget::SaveSpekersToXML()
{

	//FString XmlContentPath = IPluginManager::Get().FindPlugin(TEXT("PugiXML_Plagin"))->GetContentDir();
	FString DialogXmlContentPath = FPaths::ProjectContentDir();
	DialogXmlContentPath += "/Dialog";
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, XmlContentPath);


	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	if (!PlatformFile.DirectoryExists(*DialogXmlContentPath))
	{ 
		PlatformFile.CreateDirectory(*DialogXmlContentPath);
		if(!PlatformFile.DirectoryExists(*DialogXmlContentPath))
		{
			return;
		}
	}

	

	// -------- Create .XML,  save "Speker" ---------
	FString ContentToSave = FString("<game_spekers>\n");

	for (int32 i_Speker = 0; i_Speker < Speker.Num(); i_Speker++)
	{

		ContentToSave += FString("\t<speker name=\"") + Speker[i_Speker].name.ToString() + FString("\">") + Speker[i_Speker].SpekersAssetPath + FString("\n");

		//  --------------  audio  --------------
		for (int32 i_Sound = 0; i_Sound < Speker[i_Speker].Sound.Num(); i_Sound++)
		{
			ContentToSave += FString("\t\t<sound name=\"") + Speker[i_Speker].Sound[i_Sound].name.ToString() + FString("\">") + Speker[i_Speker].Sound[i_Sound].SoundAssetPath + FString("\n");
			ContentToSave += FString("\t\t\t<sound_comment>\n");
			ContentToSave += FString("\t\t\t\t") + Speker[i_Speker].Sound[i_Sound].SoundComment + FString("\n");
			ContentToSave += FString("\t\t\t</sound_comment>\n");
			ContentToSave += FString("\t\t</sound>\n");
		}

		ContentToSave += FString("\t</speker>") + FString("\n");
	}

	ContentToSave += FString("</game_spekers>");

	// Get file path
	FString FilePath = DialogXmlContentPath + "/Spekers.xml";

		FFileHelper::SaveStringToFile(ContentToSave, *FilePath);

}
 

   
FReply SDialogWindowWidget::ChangeSpekerImage(int32 _index)
{

	iCurrentEditableSpeker = -1;
	iCurrentEditableSound = -1;
	vMainSpikersEditablePanel_FindImage = EVisibility::Visible;
	vMainSpikersEditablePanel_FindSound = EVisibility::Collapsed;
	MainSpikersEditablePanelBlock->ClearChildren();   //  CLear Speker-EditablePanel
	iCurrentEditableSpeker = _index;
	//changingSpeker_Index = _index;

	AssetImagePath.Empty();
	AssetImageBrush.Empty();

	AssetPathName.Empty();
	AssetPathSortByName.Empty();
	FindedText_InMainSpikerEditablePanel = FString("");


	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	TArray<FAssetData> AssetData;
	//AssetRegistryModule.Get().GetAssetsByClass(FName("MediaTexture"), AssetData);
	AssetRegistryModule.Get().GetAssetsByClass(FName("Texture2D"), AssetData);
	for (int i = 0; i < AssetData.Num(); i++)
	{
		//UMediaTexture* FoundMedia = Cast<UMediaTexture>(AssetData[i].GetAsset());
		UTexture2D* FoundTexture2D = Cast<UTexture2D>(AssetData[i].GetAsset());
		if (FoundTexture2D != NULL)
		{
			AssetImagePath.Add(AssetData[i].GetFullName());
			AssetImageBrush.Add(UWidgetBlueprintLibrary::MakeBrushFromTexture(FoundTexture2D, 64, 64));

			// ----- get only Name in FullPathStr  -----
			int32 CutStartTMP = AssetImagePath.Last().Find(FString("/"), ESearchCase::Type::CaseSensitive, ESearchDir::Type::FromEnd);
			int32 NumTMP = AssetImagePath.Last().Len() - CutStartTMP;
			FString StrPathNameTmp = AssetImagePath.Last().Mid(CutStartTMP + NumTMP / 2 + 1, NumTMP);
			AssetPathName.Add(StrPathNameTmp);
			AssetPathSortByName.Add(i);

			//Textures.Add(FoundMedia);
		}
	}


	RedrawSpekerImageFindingItem(0, 0);

	return FReply::Handled();
}

void SDialogWindowWidget::RedrawSpekerImageFindingItem(int32 iSpeker, int32 iSound)
{
	MainSpikersEditablePanelBlock->ClearChildren();

	for (int32 i = 0; i < AssetPathSortByName.Num(); i++)
	{
		if (AssetPathSortByName[i] < 0 || AssetPathSortByName[i] > AssetPathName.Num() - 1) continue;

		MainSpikersEditablePanelBlock->AddSlot()
			.Padding(GetPadding(6.f, 6.f, 6.f, 6.f))
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			//--.AutoHeight()
			[
				SNew(SButton)
				.ContentPadding(0)
				.ButtonColorAndOpacity(FLinearColor(1, 1, 1, 0))
				.OnClicked(this, &SDialogWindowWidget::ApplayImageAssetToSpeker, AssetPathSortByName[i])
				[
					SNew(SHorizontalBox)

					+ SHorizontalBox::Slot()
					.AutoWidth()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					[
						SNew(SBox)
						.Padding(3)
						.HeightOverride(64.f * SizeKoef)
						.WidthOverride(64.f * SizeKoef)
						//.MaxDesiredWidth(64.f)
						//.MaxDesiredHeight(64.f)
						[
							SNew(SImage)
							.Image(&AssetImageBrush[AssetPathSortByName[i]])
						]
					]

					+ SHorizontalBox::Slot()
					[
						SNew(STextBlock).Text(FText::FromString(AssetImagePath[AssetPathSortByName[i]]))
					]
				]

			];
	}
}


void SDialogWindowWidget::RedrawSpekersBlock()
{

	MainSpikersPanelBlock->ClearChildren();

	FPropertyIndex PropertyIndex;

	for (int32 i = 0; i < Speker.Num(); i++)     
	{
		PropertyIndex.SpekerIndex = i;

		//if(Speker[i].SpekersImageBrush)
		//{
			MainSpikersPanelBlock->AddSlot()
				.Padding(GetPadding(6.f, 6.f, 6.f, 6.f))
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				//--.AutoHeight()
				[
					SNew(SVerticalBox)


						//   -------  name:  Button + text + editText
					+SVerticalBox::Slot()
					.Padding(GetPadding(3.f, 3.f, 3.f, 3.f))
					.HAlign(HAlign_Left)
					.VAlign(VAlign_Fill)
					//--.AutoWidth()
					.AutoHeight()
					//--.MaxHeigth(30.f)
					[

						SNew(SHorizontalBox)

						+ SHorizontalBox::Slot()               //         Remove Speker
						//.Padding(FMargin(6, 1, 2, 1))
						.Padding(GetPadding(2, 0, 2, 0))
						.HAlign(HAlign_Left)
						.VAlign(VAlign_Center)
						.AutoWidth()
						[
							SNew(SBox)
							.HeightOverride(32.f * SizeKoef)
							.MaxDesiredHeight(32.f * SizeKoef)
							.WidthOverride(32.f * SizeKoef)
							.MaxDesiredWidth(32.f * SizeKoef)
							[
								SNew(SButton)					 //         Remove Speker
								.ContentPadding(0)
								.ButtonColorAndOpacity(FLinearColor(1, 1, 1, 0))
								.OnClicked(this, &SDialogWindowWidget::RemoveSpekerElenemt, i)
								[
									SNew(SImage).Image(ImageDeleteElement)
								]
							]
						]

						+ SHorizontalBox::Slot()               //         Change Image
						//.Padding(FMargin(6, 1, 2, 1))
						.Padding(GetPadding(2, 0, 2, 0))
						.HAlign(HAlign_Left)
						.VAlign(VAlign_Center)
						.AutoWidth()
						[
							SNew(SBox)
							.HeightOverride(32.f * SizeKoef)
							.MaxDesiredHeight(32.f * SizeKoef)
							.WidthOverride(32.f * SizeKoef)
							.MaxDesiredWidth(32.f * SizeKoef)
							[
								SNew(SButton)					 //         Change Image
								.ContentPadding(0)
								.ButtonColorAndOpacity(FLinearColor(1, 1, 1, 0))
								.OnClicked(this, &SDialogWindowWidget::ChangeSpekerImage, i)
								[
									SNew(SImage).Image(this, &SDialogWindowWidget::GetSpekerImage, i)  // Speker[i].SpekersImageBrush
									//SNew(SImage).Image(GetSpekerImage(i))  // Speker[i].SpekersImageBrush
									//SNew(SImage).Image(&SpekersImageBrushTmp[0])  //--------------------
								]
							]
						]

						+ SHorizontalBox::Slot()               //         Change Sound
						//.Padding(FMargin(6, 1, 2, 1))
						.Padding(GetPadding(2, 0, 4, 0))
						.HAlign(HAlign_Left)
						.VAlign(VAlign_Center)
						.AutoWidth()
						[
							SNew(SBox)
							.HeightOverride(32.f * SizeKoef)
							.MaxDesiredHeight(32.f * SizeKoef)
							.WidthOverride(32.f * SizeKoef)
							.MaxDesiredWidth(32.f * SizeKoef)
							[
								SNew(SButton)					 //         Change Sound
								.ContentPadding(0)
								.ButtonColorAndOpacity(FLinearColor(1, 1, 1, 0))
								.OnClicked(this, &SDialogWindowWidget::AddSpekerSound, i)
								[
									SNew(SImage).Image(ImageAddSoundElement)
								]
							]
						]

						+ SHorizontalBox::Slot()               //   -------  name:  Button + text + editText       
						//.Padding(FMargin(6, 1, 2, 1))
						.Padding(GetPadding(2, 0, 2, 0))
						.HAlign(HAlign_Left)
						.VAlign(VAlign_Center)
						.AutoWidth()
						[
							SNew(SBox)
							.MinDesiredWidth(150.f * SizeKoef)
							.HeightOverride(30.f * SizeKoef)
							//.WidthOverride(100.f)
							[
								SNew(SButton)  //   -------  name:  Button + text + editText
								.ContentPadding(0)
								.ButtonColorAndOpacity(FLinearColor(1, 1, 1, 0))
								.OnClicked(this, &SDialogWindowWidget::StoredSpekerIndex, EProppertyToChange::SpekerinSpekerBlock, i)
								[
									SNew(SOverlay)
									+ SOverlay::Slot()
									.HAlign(HAlign_Fill)
									.VAlign(VAlign_Fill)
									[
										SNew(SImage)
										.Image(PropertyResponseStart)
									]

									+ SOverlay::Slot()
									[
										SNew(SHorizontalBox)

										+ SHorizontalBox::Slot()
										.Padding(GetPadding(6, 1, 2, 1))
										.HAlign(HAlign_Left)
										.VAlign(VAlign_Center)
										.AutoWidth()
										[
											SNew(STextBlock)
											.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 8 * SizeKoef))
											.ColorAndOpacity(FLinearColor(0.7f, 0.77f, 1.f, 1))
											.Text(FText::FromString("Name:"))
										]

										+ SHorizontalBox::Slot()
										.Padding(GetPadding(6, 1, 6, 1))
										.HAlign(HAlign_Left)
										.VAlign(VAlign_Center)
										.AutoWidth()
										//.FillWidth(1)
										[
											//  ===========================  SPEKER-Name StaticText  ================================
											SAssignNew(Speker[i].SpekerName_Statick, STextBlock)
											.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 10 * SizeKoef))
											.ColorAndOpacity(FLinearColor(0.7f, 0.77f, 1.f, 1))
											.Visibility(this, &SDialogWindowWidget::GetVisibilitySpekerNameText_Static, i)
											//.Visibility(GetVisibilitySpekerNameText_Static(i))
											.Text(this, &SDialogWindowWidget::GetSpikerNameText, i)
											//.Text(GetSpikerNameText(i))
										]

										+ SHorizontalBox::Slot()
										.Padding(GetPadding(6, 1, 6, 1))
										//.FillWidth(1)
										.AutoWidth()
										//--.MaxHeigth(30.f)
										.HAlign(HAlign_Center)
										.VAlign(VAlign_Center)
										[
											SNew(SBox)
											//+++++++.MinDesiredWidth(100.f)
											.HAlign(HAlign_Left)

											[
												//  ===========================  SPEKER-Name EditableText  ================================
												SAssignNew(Speker[i].SpekerName_Editable, SEditableTextBox)
												.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 10 * SizeKoef))
											.Visibility(this, &SDialogWindowWidget::GetVisibilitySpekerNameText_Editable, i)
											//.Visibility(GetVisibilitySpekerNameText_Editable(i))
											.Text(FText::FromString(Speker[i].name.ToString()))
											.OnTextCommitted(this, &SDialogWindowWidget::ConfirmEditableTextBox, EProppertyToChange::SpekerinSpekerBlock, PropertyIndex)  // PRES_ENTER:   void ConfirmEditableTextBox(const FText& Text, ETextCommit::Type TextType);
											//.OnTextCommitted(this, &SDialogWindowWidget::ConfirmEditableTextBox, EProppertyToChange::SpekerinSpekerBlock, PropertyIndex)  // PRES_ENTER:   void ConfirmEditableTextBox(const FText& Text, ETextCommit::Type TextType);
											.OnTextChanged_Raw(this, &SDialogWindowWidget::OnEditableTextChange) // change every KEY    // void OnButtonT(const FText& Text);
											//.OnTextChanged_Raw(this, &SDialogWindowWidget::OnEditableTextChange) // change every KEY    // void OnButtonT(const FText& Text);
											]
										]
									]
								]
							]
						]
					]

					+ SVerticalBox::Slot()
					.Padding(GetPadding(3.f, 3.f, 3.f, 3.f))
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					//--.AutoWidth()
					.AutoHeight()
					//--.MaxHeigth(30.f)
					[
						SNew(SHorizontalBox)

						+ SHorizontalBox::Slot()
						.HAlign(HAlign_Fill)
						.VAlign(VAlign_Fill)
						.AutoWidth()
						[
							SNew(SBox)
							.HeightOverride(128.f * SizeKoef)
							.MaxDesiredHeight(128.f * SizeKoef)
							.WidthOverride(128.f * SizeKoef)
							.MaxDesiredWidth(128.f * SizeKoef)
							[
								// SPEKER IMAGE
								SNew(SImage).Image(GetSpekerImage(i))
							]
						]


						+ SHorizontalBox::Slot()
						.Padding(GetPadding(6.f, 3.f, 3.f, 3.f))
						.HAlign(HAlign_Fill)
						.VAlign(VAlign_Fill)
						.FillWidth(1)
						[
							SNew(SBox)
							.HeightOverride(128.f * SizeKoef)
							//.WidthOverride(64.f)
							//.MaxDesiredWidth(64.f)
							.MaxDesiredHeight(64.f * SizeKoef)
							[
								// // SPEKER SOUND
								SAssignNew(Speker[i].SounsScroll, SScrollBox)
							]
						]
					]
				];
		RedrawSoundsBlock(i);
	}

}
//  --------------------------------------------------------------------------------------------------------
//  ----------------------------------     Spekers Block     (Finish)     ----------------------------------
//  --------------------------------------------------------------------------------------------------------











//  =========================================================================================================
//  =========================================================================================================
//  ==================================            Helper Panel          =====================================
//  =========================================================================================================
//  =========================================================================================================



FOptionalSize SDialogWindowWidget::GetHelperMenu_Height() const
{
	return FOptionalSize(HelperMenu_Height);
}


EVisibility SDialogWindowWidget::GetHelperPanelVisibility() const
{
	if(isHelperMenuOpen) return EVisibility::Visible;
	else				return EVisibility::Collapsed;

}

FMargin SDialogWindowWidget::GetHelperPanelPosition() const
{
	return HelperPanelPosition;
}

FReply SDialogWindowWidget::CancelHelperPanel()
{
	//StacklessAnchorPanel.ToSharedRef()->SetIsOpen(false);
	isHelperMenuOpen = false;
	return FReply::Handled();
}


FReply SDialogWindowWidget::OnHelperPanelClick(EProppertyToChange ProppertyToChange, FPropertyIndex PropertyIndex)
{

	CurrProppertyToChange = ProppertyToChange;
	CurrPropertyIndex = PropertyIndex;

	HelperMenulList->ClearChildren();


	//TArray<FString> ListElement;
	HelperPanel_FastFindingListIndexes.Empty();
	ListElementTmp.Empty();
	HelperMenu_Height = 0;

	FastFindingHelperString.TrimStartAndEndInline();               //  remove \t \n (" ")


	if (ProppertyToChange == EProppertyToChange::speker)
	{
		OnHelperPanel_FindingEditableText->SetVisibility(EVisibility::Visible);

		LoadSpekersfromXML();
		
		for (int32 i_Speker = 0; i_Speker < Speker.Num(); i_Speker++)
		{
			ListElementTmp.Add(Speker[i_Speker].name.ToString());

			//  Fast Finding Indexes
			if(FastFindingHelperString == FString(""))	HelperPanel_FastFindingListIndexes.Add(i_Speker);
			else if (Speker[i_Speker].name.ToString().Contains(FastFindingHelperString, ESearchCase::Type::IgnoreCase))
			{
				HelperPanel_FastFindingListIndexes.Add(i_Speker);   
			}
			
		}

	}

	else if (ProppertyToChange == EProppertyToChange::sound)
	{

		OnHelperPanel_FindingEditableText->SetVisibility(EVisibility::Visible);

		LoadSoundFromXMLSpeker(DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
								.ReplicSection[PropertyIndex.iReplic]
								.RepSection[PropertyIndex.iRep].Speker);

		for (int32 i_Sound = 0; i_Sound < Sound.Num(); i_Sound++)
		{
			ListElementTmp.Add(Sound[i_Sound].name.ToString());

			//  Fast Finding Indexes
			if (FastFindingHelperString == FString(""))	HelperPanel_FastFindingListIndexes.Add(i_Sound);
			else if (Sound[i_Sound].name.ToString().Contains(FastFindingHelperString, ESearchCase::Type::IgnoreCase))
			{
				HelperPanel_FastFindingListIndexes.Add(i_Sound);
			}
			
		}

	}

	else if (ProppertyToChange == EProppertyToChange::time)
	{
		OnHelperPanel_FindingEditableText->SetVisibility(EVisibility::Collapsed);

		HelperMenu_Height = 30.f * SizeKoef; 
		

		HelperMenulList->AddSlot()
			.Padding(0.f)
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			//--.AutoHeight()
			[
				SNew(SBox)
				.MinDesiredHeight(HelperMenu_Height)
				.MaxDesiredHeight(HelperMenu_Height)
				//.MinDesiredWidth(70.f)
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
					//  ===========================   SPinBox        ================================
					SNew(SSpinBox<float>)
					.MinValue(0.f)
					.MaxValue(100.f)
					//.Value(SDialogWindowWidget::GetDelayValue())  //, EProppertyToChange::Delay, CurrentPropertyIndex
					.Value(FCString::Atof(*DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
											.ReplicSection[PropertyIndex.iReplic]
											.RepSection[PropertyIndex.iRep].Time.ToString()))  
					.OnValueCommitted(this, &SDialogWindowWidget::SetTimeValue, ProppertyToChange, PropertyIndex)
				]
			];
		
		ListElementTmp.Add(FString("sound_length"));
		HelperPanel_FastFindingListIndexes.Add(0);
		ListElementTmp.Add(FString("while_press"));
		HelperPanel_FastFindingListIndexes.Add(1);

	}
	else if (ProppertyToChange == EProppertyToChange::DialogLink)
	{
		OnHelperPanel_FindingEditableText->SetVisibility(EVisibility::Visible);

		for (int32 i_dialog = 0; i_dialog < DialogSection.Num(); i_dialog++)
		{
			ListElementTmp.Add(DialogSection[i_dialog].Name.ToString());

			//  Fast Finding Indexes
			if (FastFindingHelperString == FString(""))	 HelperPanel_FastFindingListIndexes.Add(i_dialog);
			else if (DialogSection[i_dialog].Name.ToString().Contains(FastFindingHelperString, ESearchCase::Type::IgnoreCase))
			{
				HelperPanel_FastFindingListIndexes.Add(i_dialog);
			}			
		}
		
	}
	else if (ProppertyToChange == EProppertyToChange::SpeechLink)
	{
	
		OnHelperPanel_FindingEditableText->SetVisibility(EVisibility::Visible);


		//  Get current chois "dialog"
		FName CurrDialogLink = DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
												.ResponseSection[PropertyIndex.iResponse].DialogLink;

		int32 CurrDialogIndex = -1;
		for (int32 i_dialog = 0; i_dialog < DialogSection.Num(); i_dialog++)
		{
			if (DialogSection[i_dialog].Name == CurrDialogLink)
			{
				CurrDialogIndex = i_dialog;
				break;
			}
		}

		//  make massive of availability Speech names
		if (CurrDialogIndex != -1)
		{
			int32 iTmp = -1; // ------ index. of witch element of HelperPanel_FastFindingListIndexes[] is referens on ListElementTmp[]


			// ---------   Add "Speech DEFAULT" on TOP if this Dialog has any   ---------
			for (int32 i_speech = 0; i_speech < DialogSection[CurrDialogIndex].SpeechSection.Num(); i_speech++)
			{
				if (DialogSection[CurrDialogIndex].SpeechSection[i_speech].Name == FName("DEFAULT"))
				{
					ListElementTmp.Add(FString("DEFAULT"));
					HelperPanel_FastFindingListIndexes.Add(0);  //  "DEFAULT"  in Top
					iTmp = 0;  //  if Dialog-Block has any_Speech-DEFAULT =>> start increasing from "0" else start from "-1"
					break;
				}
			}


			//  --------   form list to draw  from all Speech in current dialog   ------------
			for (int32 i_speech = 0; i_speech < DialogSection[CurrDialogIndex].SpeechSection.Num(); i_speech++)
			{
				
				if (DialogSection[CurrDialogIndex].SpeechSection[i_speech].Name != FName("DEFAULT"))
				{
					iTmp++;

					//  form list to draw // add all Speech
					ListElementTmp.Add(DialogSection[CurrDialogIndex].SpeechSection[i_speech].Name.ToString());

					//  ---------   Fast Finding Indexes   ----------
					// add all suitable element to FastFinding
					if (FastFindingHelperString == FString("")) HelperPanel_FastFindingListIndexes.Add(iTmp);
					else if(DialogSection[CurrDialogIndex].SpeechSection[i_speech].Name.ToString()
									.Contains(FastFindingHelperString, ESearchCase::Type::IgnoreCase))
					{
						//  stored suitable indexes of  "ListElementTmp[]" in HelperPanel_FastFindingListIndexes[]
						HelperPanel_FastFindingListIndexes.Add(iTmp);
						iTmp++;
					}					
				}
			}

		}		
	}
	else if (ProppertyToChange == EProppertyToChange::Speech_condition_CompareType ||
			ProppertyToChange == EProppertyToChange::Replic_condition_CompareType ||
			ProppertyToChange == EProppertyToChange::rep_condition_CompareType ||
			ProppertyToChange == EProppertyToChange::Response_condition_CompareType)
	{
			OnHelperPanel_FindingEditableText->SetVisibility(EVisibility::Collapsed);
			ListElementTmp.Add(FString("="));
			HelperPanel_FastFindingListIndexes.Add(0);
			ListElementTmp.Add(FString("!="));
			HelperPanel_FastFindingListIndexes.Add(1);
			ListElementTmp.Add(FString(">"));
			HelperPanel_FastFindingListIndexes.Add(2);
			ListElementTmp.Add(FString(">="));
			HelperPanel_FastFindingListIndexes.Add(3);
			ListElementTmp.Add(FString("<"));
			HelperPanel_FastFindingListIndexes.Add(4);
			ListElementTmp.Add(FString("<="));
			HelperPanel_FastFindingListIndexes.Add(5);
	}
	else if (ProppertyToChange == EProppertyToChange::MoveDialog ||
			ProppertyToChange == EProppertyToChange::MoveSpeech ||
			ProppertyToChange == EProppertyToChange::MoveReplic ||
			ProppertyToChange == EProppertyToChange::MoveRep ||
			ProppertyToChange == EProppertyToChange::MoveResponse ||
			ProppertyToChange == EProppertyToChange::Move_Condition ||
			ProppertyToChange == EProppertyToChange::MoveResponse_Variable)
	{
		OnHelperPanel_FindingEditableText->SetVisibility(EVisibility::Collapsed);
		ListElementTmp.Add(FString("Copy"));
		HelperPanel_FastFindingListIndexes.Add(0);
		ListElementTmp.Add(FString("Cut"));
		HelperPanel_FastFindingListIndexes.Add(1);
		ListElementTmp.Add(FString("Paste"));
		HelperPanel_FastFindingListIndexes.Add(2);
	}


	//  *******************************************************************************************
	//  *******************************************************************************************
	//  *******************************************************************************************
	//                        (calculate HelperMenuSizeY)     Not Correct Work       
	//  ********************************************************************************************
	//  ********************************************************************************************
	//  ********************************************************************************************
	HelperMenu_Height = ListElementTmp.Num() * 25.f + 30.f;   //   element Height + EditableBoxHigh
	FVector2D _ViewportSize = FSlateApplication::Get().GetActiveTopLevelWindow()->GetViewportSize();	
	if (HelperMenu_Height > _ViewportSize.Y)  HelperMenu_Height = _ViewportSize.Y;   //  HelperMenu Height
	else if (HelperMenu_Height > 800) HelperMenu_Height = 800;


	//for (int32 i_list = 0; i_list < ListElementTmp.Num(); i_list++)
	for (int32 i_list = 0; i_list < HelperPanel_FastFindingListIndexes.Num(); i_list++)
	{
		
		//GetChildren()->GetChildAt()
		//RemoveSlot()
		//ClearChildren()
		HelperMenulList->AddSlot()
			.Padding(0.f)
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			//--.AutoHeight()
			[
					SNew(SBox)
					.Padding(GetPadding(1, 0, 1, 0))
					.MaxDesiredWidth(300.f * SizeKoef)
					//.MinDesiredHeight(30.f)
					//.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					//.WidthOverride(20.f)
					.HeightOverride(25.f * SizeKoef)
					[
						SNew(SButton)
						.ContentPadding(0)
						.HAlign(HAlign_Fill)
						.VAlign(VAlign_Center)
						.ButtonColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 0.15f))
						.OnClicked(this, &SDialogWindowWidget::OnHelperPanelElementClick, ProppertyToChange, PropertyIndex, HelperPanel_FastFindingListIndexes[i_list])
						[
							SNew(STextBlock)
							.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 14 * SizeKoef))
							.ColorAndOpacity(FLinearColor(0.7f, 0.77f, 1.f, 1))
							.Text(FText::FromString(ListElementTmp[HelperPanel_FastFindingListIndexes[i_list]]))
						]
					]
			];
		
	}
	

	CalculateHelperMenuPosition = true;
	return FReply::Handled();
}

void SDialogWindowWidget::OnHelperPanel_FindingTextChange(const FText& _Text)
{
	FastFindingHelperString = _Text.ToString();
	OnHelperPanelClick(CurrProppertyToChange, CurrPropertyIndex);
}

FReply SDialogWindowWidget::OnHelperPanelElementClick(EProppertyToChange ProppertyToChange, FPropertyIndex PropertyIndex, int32 index)
{
	FastFindingHelperString = FString("");

	if (ProppertyToChange == EProppertyToChange::speker)
	{
		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic]
														.RepSection[PropertyIndex.iRep].Speker = Speker[index].name;

		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic]
														.RepSection[PropertyIndex.iRep].Sound = FName("none");
	}
	  
	else if (ProppertyToChange == EProppertyToChange::sound)
	{
		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic]
														.RepSection[PropertyIndex.iRep].Sound = Sound[index].name;
	}

	else if (ProppertyToChange == EProppertyToChange::time)
	{
	
		if (index == 0)   //   sound_length
		{
			DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
				.ReplicSection[PropertyIndex.iReplic]
				.RepSection[PropertyIndex.iRep].Time = FName("sound_length");
		}
		else //  if (index = 0)   /   while_press
		{
			DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
				.ReplicSection[PropertyIndex.iReplic]
				.RepSection[PropertyIndex.iRep].Time = FName("while_press");
		}		
	}


	else if (ProppertyToChange == EProppertyToChange::DialogLink)
	{
		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
								.ResponseSection[PropertyIndex.iResponse].DialogLink = FName(*ListElementTmp[index]);

		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
			.ResponseSection[PropertyIndex.iResponse].SpeechLink = FName("DEFAULT");
	}
	else if (ProppertyToChange == EProppertyToChange::SpeechLink)
	{
		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
			.ResponseSection[PropertyIndex.iResponse].SpeechLink = FName(*ListElementTmp[index]);
	}

	//  Condition type (=. !=, <, >, >=, <=)
	else if (ProppertyToChange == EProppertyToChange::Speech_condition_CompareType)
	{
		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
			.SpeechCondition[PropertyIndex.iSpeechCondition].VariableCompareType = FName(*ListElementTmp[index]);
	}
	else if (ProppertyToChange == EProppertyToChange::Replic_condition_CompareType)
	{
		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
			.ReplicSection[PropertyIndex.iReplic].ReplicCondition[PropertyIndex.iReplicCondition]
			.VariableCompareType = FName(*ListElementTmp[index]);
	}
	else if (ProppertyToChange == EProppertyToChange::rep_condition_CompareType)
	{
		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
			.ReplicSection[PropertyIndex.iReplic].RepSection[PropertyIndex.iRep]
			.RepCondition[PropertyIndex.iRepCondition].VariableCompareType = FName(*ListElementTmp[index]);
	}
	else if (ProppertyToChange == EProppertyToChange::Response_condition_CompareType)
	{
		DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
			.ResponseSection[PropertyIndex.iResponse].ResponseCondition[PropertyIndex.iResponseCondition]
			.VariableCompareType = FName(*ListElementTmp[index]);
	}

		
	//    =========================================================================================
	//    =======                         Copy or move Section                             ========
	//    =========================================================================================
	if (ProppertyToChange == EProppertyToChange::MoveDialog ||
		ProppertyToChange == EProppertyToChange::MoveSpeech ||
		ProppertyToChange == EProppertyToChange::MoveReplic ||
		ProppertyToChange == EProppertyToChange::MoveRep ||
		ProppertyToChange == EProppertyToChange::MoveResponse ||
		ProppertyToChange == EProppertyToChange::Move_Condition ||
		ProppertyToChange == EProppertyToChange::MoveResponse_Variable)
	{
		// ------   Copy or Cut  (not paste)  ---------
		if (index != 2)
		{
			SectionToMove_Propperty = ProppertyToChange;
			iSectionToMove = PropertyIndex;

			if (index == 0) isCurrSectionToMove_Cut = false;  // ------   Copy Section  ---------	
			//------  if (index == 1)  ---------
			else isCurrSectionToMove_Cut = true;			  // ------   Cut  Section   ---------

			//  =================  if it's condition =>> save it   =================
			if (ProppertyToChange == EProppertyToChange::Move_Condition)
			{
				//    -----------------------   response Condition Section   -----------------------
				if (PropertyIndex.iResponseCondition != -1)
				{
					MovingCondition = DialogSection[iSectionToMove.iDialog]
						.SpeechSection[iSectionToMove.iSpeech].ResponseSection[iSectionToMove.iResponse]
						.ResponseCondition[iSectionToMove.iResponseCondition];
				}
				//    -----------------------   rep Condition Section   -----------------------
				else if (PropertyIndex.iRepCondition != -1)
				{
					MovingCondition = DialogSection[iSectionToMove.iDialog]
						.SpeechSection[iSectionToMove.iSpeech].ReplicSection[iSectionToMove.iReplic]
						.RepSection[iSectionToMove.iRep].RepCondition[iSectionToMove.iRepCondition];
				}
				//    -----------------------   replic Condition Section   -----------------------
				else if (PropertyIndex.iReplicCondition != -1)
				{
					MovingCondition = DialogSection[iSectionToMove.iDialog]
						.SpeechSection[iSectionToMove.iSpeech].ReplicSection[iSectionToMove.iReplic]
						.ReplicCondition[iSectionToMove.iReplicCondition];
				}
				//    -----------------------   Speesh Condition Section   -----------------------
				else if (PropertyIndex.iSpeechCondition != -1)
				{
					MovingCondition = DialogSection[iSectionToMove.iDialog]
						.SpeechSection[iSectionToMove.iSpeech].SpeechCondition[iSectionToMove.iSpeechCondition];					
				}
			}
		}
		else //----if (index == 2)  // ================   Paste Section   ====================
		{
			//    -----------------------   Dialog Section   -----------------------

			if (ProppertyToChange == EProppertyToChange::MoveDialog &&       //click now
				SectionToMove_Propperty == EProppertyToChange::MoveDialog)   //click last(copyred)
			{
				FDialogSection DialogSectionToMove = DialogSection[iSectionToMove.iDialog];
				DialogSection.Insert(DialogSectionToMove, PropertyIndex.iDialog + 1);

				// if "Cut" =>> remove last
				if (isCurrSectionToMove_Cut)
				{
					if (iSectionToMove.iDialog < PropertyIndex.iDialog) DialogSection.RemoveAt(iSectionToMove.iDialog);
					else DialogSection.RemoveAt(iSectionToMove.iDialog + 1);
				}
				SectionToMove_Propperty = EProppertyToChange::none;
				UpdateDialogBlock();

			}
			else if (ProppertyToChange == EProppertyToChange::MoveSpeech &&     //click now
				SectionToMove_Propperty == EProppertyToChange::MoveSpeech)  //click last(copyred)
			{
				//    -----------------------   Speech Section   -----------------------

				FSpeechSection SpeechSectionToMove = DialogSection[iSectionToMove.iDialog].SpeechSection[iSectionToMove.iSpeech];
				DialogSection[PropertyIndex.iDialog].SpeechSection.Insert(SpeechSectionToMove, PropertyIndex.iSpeech + 1);

				// if "Cut" =>> remove last
				if (isCurrSectionToMove_Cut)
				{
					if (iSectionToMove.iSpeech < PropertyIndex.iSpeech || iSectionToMove.iDialog != PropertyIndex.iDialog)
						DialogSection[iSectionToMove.iDialog].SpeechSection.RemoveAt(iSectionToMove.iSpeech);
					else DialogSection[iSectionToMove.iDialog].SpeechSection.RemoveAt(iSectionToMove.iSpeech + 1);
				}
				SectionToMove_Propperty = EProppertyToChange::none;
				UpdateDialogBlock();
			}
			else if (ProppertyToChange == EProppertyToChange::MoveReplic &&     //click now
				SectionToMove_Propperty == EProppertyToChange::MoveReplic)  //click last(copyred)
			{
				//    -----------------------   Replic Section   -----------------------

				FReplicSection ReplicSectionToMove = DialogSection[iSectionToMove.iDialog]
								.SpeechSection[iSectionToMove.iSpeech].ReplicSection[iSectionToMove.iReplic];
				DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
										.ReplicSection.Insert(ReplicSectionToMove, PropertyIndex.iReplic + 1);

				// if "Cut" =>> remove last
				if (isCurrSectionToMove_Cut)
				{
					if (iSectionToMove.iReplic < PropertyIndex.iReplic || 
						iSectionToMove.iDialog != PropertyIndex.iDialog ||
						iSectionToMove.iSpeech != PropertyIndex.iSpeech)
						DialogSection[iSectionToMove.iDialog].SpeechSection[iSectionToMove.iSpeech]
														.ReplicSection.RemoveAt(iSectionToMove.iReplic);
					else DialogSection[iSectionToMove.iDialog].SpeechSection[iSectionToMove.iSpeech]
														.ReplicSection.RemoveAt(iSectionToMove.iReplic + 1);
				}
				SectionToMove_Propperty = EProppertyToChange::none;
				UpdateDialogBlock();
			}
			else if (ProppertyToChange == EProppertyToChange::MoveRep &&     //click now
					SectionToMove_Propperty == EProppertyToChange::MoveRep)  //click last(copyred)
			{
				//    -----------------------   Rep Section   -----------------------

				FRepSection RepSectionToMove = DialogSection[iSectionToMove.iDialog]
					.SpeechSection[iSectionToMove.iSpeech].ReplicSection[iSectionToMove.iReplic].RepSection[iSectionToMove.iRep];
				DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
					.ReplicSection[PropertyIndex.iReplic].RepSection.Insert(RepSectionToMove, PropertyIndex.iRep + 1);

				// if "Cut" =>> remove last
				if (isCurrSectionToMove_Cut)
				{
					if (iSectionToMove.iRep < PropertyIndex.iRep ||
						iSectionToMove.iDialog != PropertyIndex.iDialog ||
						iSectionToMove.iSpeech != PropertyIndex.iSpeech ||
						iSectionToMove.iReplic != PropertyIndex.iReplic )
						DialogSection[iSectionToMove.iDialog].SpeechSection[iSectionToMove.iSpeech]
								.ReplicSection[iSectionToMove.iReplic].RepSection.RemoveAt(iSectionToMove.iRep);
					else DialogSection[iSectionToMove.iDialog].SpeechSection[iSectionToMove.iSpeech]
							.ReplicSection[iSectionToMove.iReplic].RepSection.RemoveAt(iSectionToMove.iRep + 1);
				}
				SectionToMove_Propperty = EProppertyToChange::none;
				UpdateDialogBlock();
			}

			else if (ProppertyToChange == EProppertyToChange::MoveResponse &&     //click now
				SectionToMove_Propperty == EProppertyToChange::MoveResponse)  //click last(copyred)
			{
				//    -----------------------   Response Section   -----------------------

				FResponseSection ResponseSectionToMove = DialogSection[iSectionToMove.iDialog]
					.SpeechSection[iSectionToMove.iSpeech].ResponseSection[iSectionToMove.iResponse];
				DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
					.ResponseSection.Insert(ResponseSectionToMove, PropertyIndex.iResponse + 1);

				// if "Cut" =>> remove last
				if (isCurrSectionToMove_Cut)
				{
					if (iSectionToMove.iResponse < PropertyIndex.iResponse ||
						iSectionToMove.iDialog != PropertyIndex.iDialog ||
						iSectionToMove.iSpeech != PropertyIndex.iSpeech)
						DialogSection[iSectionToMove.iDialog].SpeechSection[iSectionToMove.iSpeech]
						.ResponseSection.RemoveAt(iSectionToMove.iResponse);
					else DialogSection[iSectionToMove.iDialog].SpeechSection[iSectionToMove.iSpeech]
						.ResponseSection.RemoveAt(iSectionToMove.iResponse + 1);
				}
				SectionToMove_Propperty = EProppertyToChange::none;
				UpdateDialogBlock();
			}
			else if (ProppertyToChange == EProppertyToChange::MoveResponse_Variable &&     //click now
				SectionToMove_Propperty == EProppertyToChange::MoveResponse_Variable)  //click last(copyred)
			{
				//    -----------------------   Response Variables Section   -----------------------

				FVariables ResponseVariablesSectionToMove = DialogSection[iSectionToMove.iDialog].SpeechSection[iSectionToMove.iSpeech]
					.ResponseSection[iSectionToMove.iResponse].VariableSection[iSectionToMove.iResponseVariable];
				DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ResponseSection[PropertyIndex.iResponse]
					.VariableSection.Insert(ResponseVariablesSectionToMove, PropertyIndex.iResponseVariable + 1);

				// if "Cut" =>> remove last
				if (isCurrSectionToMove_Cut)
				{
					if (iSectionToMove.iResponseVariable < PropertyIndex.iResponseVariable ||
						iSectionToMove.iDialog != PropertyIndex.iDialog ||
						iSectionToMove.iSpeech != PropertyIndex.iSpeech ||
						iSectionToMove.iResponse != PropertyIndex.iResponse)
						DialogSection[iSectionToMove.iDialog].SpeechSection[iSectionToMove.iSpeech]
							.ResponseSection[iSectionToMove.iResponse].VariableSection.RemoveAt(iSectionToMove.iResponseVariable);
					else DialogSection[iSectionToMove.iDialog].SpeechSection[iSectionToMove.iSpeech]
							.ResponseSection[iSectionToMove.iResponse].VariableSection.RemoveAt(iSectionToMove.iResponseVariable + 1);
				}
				SectionToMove_Propperty = EProppertyToChange::none;
				UpdateDialogBlock();
			}
			//    ========================   Condition Section   -----------------------
			else if (ProppertyToChange == EProppertyToChange::Move_Condition &&     //click now
					SectionToMove_Propperty == EProppertyToChange::Move_Condition)  //click last(copyred)
			{
				//    -----------------------   Response Condition Section   -----------------------
				if (PropertyIndex.iResponseCondition != -1)
				{
					DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ResponseSection[PropertyIndex.iResponse]
						.ResponseCondition.Insert(MovingCondition, PropertyIndex.iResponseCondition + 1);
				}
				//    -----------------------   rep Condition Section   -----------------------
				else if (PropertyIndex.iRepCondition != -1)
				{
					DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
						.ReplicSection[PropertyIndex.iReplic].RepSection[PropertyIndex.iRep].RepCondition
						.Insert(MovingCondition, PropertyIndex.iRepCondition + 1);
				}
				//    -----------------------   replic Condition Section   -----------------------
				else if (PropertyIndex.iReplicCondition != -1)
				{
					DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech].ReplicSection[PropertyIndex.iReplic]
						.ReplicCondition.Insert(MovingCondition, PropertyIndex.iReplicCondition + 1);
				}
				//    -----------------------   Speesh Condition Section   -----------------------
				else if (PropertyIndex.iSpeechCondition != -1)
				{
					DialogSection[PropertyIndex.iDialog].SpeechSection[PropertyIndex.iSpeech]
						.SpeechCondition.Insert(MovingCondition, PropertyIndex.iSpeechCondition + 1);
				}

				//  =================     Remove Old condition object    ==================
				//    -----------------------   Response Condition Section   -----------------------
				if (iSectionToMove.iResponseCondition != -1)
				{
					//// if "Cut" =>> remove last
					if (isCurrSectionToMove_Cut)
					{
						if (iSectionToMove.iResponseCondition < PropertyIndex.iResponseCondition ||
							iSectionToMove.iDialog != PropertyIndex.iDialog ||
							iSectionToMove.iSpeech != PropertyIndex.iSpeech ||
							iSectionToMove.iResponse != PropertyIndex.iResponse ||
							PropertyIndex.iResponseCondition == -1)
							DialogSection[iSectionToMove.iDialog].SpeechSection[iSectionToMove.iSpeech]
							.ResponseSection[iSectionToMove.iResponse].ResponseCondition.RemoveAt(iSectionToMove.iResponseCondition);
						else DialogSection[iSectionToMove.iDialog].SpeechSection[iSectionToMove.iSpeech]
							.ResponseSection[iSectionToMove.iResponse].ResponseCondition.RemoveAt(iSectionToMove.iResponseCondition + 1);
					}
					SectionToMove_Propperty = EProppertyToChange::none;
					UpdateDialogBlock();
				}
				//    -----------------------   rep Condition Section   -----------------------
				else if (iSectionToMove.iRepCondition != -1)
				{
					//// if "Cut" =>> remove last
					if (isCurrSectionToMove_Cut)
					{
						if (iSectionToMove.iRepCondition < PropertyIndex.iRepCondition ||
							iSectionToMove.iDialog != PropertyIndex.iDialog ||
							iSectionToMove.iSpeech != PropertyIndex.iSpeech ||
							iSectionToMove.iReplic != PropertyIndex.iReplic ||
							iSectionToMove.iRep != PropertyIndex.iRep ||
							PropertyIndex.iRepCondition == -1)
							DialogSection[iSectionToMove.iDialog].SpeechSection[iSectionToMove.iSpeech]
							.ReplicSection[iSectionToMove.iReplic].RepSection[iSectionToMove.iRep]
															.RepCondition.RemoveAt(iSectionToMove.iRepCondition);
						else DialogSection[iSectionToMove.iDialog].SpeechSection[iSectionToMove.iSpeech]
							.ReplicSection[iSectionToMove.iReplic].RepSection[iSectionToMove.iRep]
														.RepCondition.RemoveAt(iSectionToMove.iRepCondition + 1);
					}
					SectionToMove_Propperty = EProppertyToChange::none;
					UpdateDialogBlock();
				}
				//    -----------------------   replic Condition Section   -----------------------
				else if (iSectionToMove.iReplicCondition != -1)
				{
					// if "Cut" =>> remove last
					if (isCurrSectionToMove_Cut)
					{
						if (iSectionToMove.iReplicCondition < PropertyIndex.iReplicCondition ||
							iSectionToMove.iDialog != PropertyIndex.iDialog ||
							iSectionToMove.iSpeech != PropertyIndex.iSpeech ||
							iSectionToMove.iReplic != PropertyIndex.iReplic ||
							PropertyIndex.iReplicCondition == -1)
							DialogSection[iSectionToMove.iDialog].SpeechSection[iSectionToMove.iSpeech]
								.ReplicSection[iSectionToMove.iReplic].ReplicCondition.RemoveAt(iSectionToMove.iReplicCondition);
						else DialogSection[iSectionToMove.iDialog].SpeechSection[iSectionToMove.iSpeech]
								.ReplicSection[iSectionToMove.iReplic].ReplicCondition.RemoveAt(iSectionToMove.iReplicCondition + 1);
					}
					SectionToMove_Propperty = EProppertyToChange::none;
					UpdateDialogBlock();
				}
				//    -----------------------   Speesh Condition Section   -----------------------
				else if (iSectionToMove.iSpeechCondition != -1)
				{
					//// if "Cut" =>> remove last
					if (isCurrSectionToMove_Cut)
					{
						if (iSectionToMove.iSpeechCondition < PropertyIndex.iSpeechCondition ||
							iSectionToMove.iDialog != PropertyIndex.iDialog ||
							iSectionToMove.iSpeech != PropertyIndex.iSpeech ||
							PropertyIndex.iSpeechCondition == -1)
							DialogSection[iSectionToMove.iDialog].SpeechSection[iSectionToMove.iSpeech]
								.SpeechCondition.RemoveAt(iSectionToMove.iSpeechCondition);
						//else if(iSectionToMove.iSpeechCondition != )
						else DialogSection[iSectionToMove.iDialog].SpeechSection[iSectionToMove.iSpeech]
								.SpeechCondition.RemoveAt(iSectionToMove.iSpeechCondition + 1);
					}
					SectionToMove_Propperty = EProppertyToChange::none;
					UpdateDialogBlock();
				}
			}
		}
	}
	
	CalculateHelperMenuPosition = false;
	isHelperMenuOpen = false;
	return FReply::Handled();
}








//  =========================================================================================================
//  =========================================================================================================
//  ==================================             Element SIZE          =====================================
//  =========================================================================================================
//  =========================================================================================================


FOptionalSize SDialogWindowWidget::GetButtonSize(float size) const
{
	return FOptionalSize(size * SizeKoef);
}

FMargin SDialogWindowWidget::GetPadding(float left, float Up, float Right, float Bottom)
{
	return FMargin(left * SizeKoef, Up * SizeKoef, Right * SizeKoef, Bottom * SizeKoef);
}







//  =========================================================================================================
//  =========================================================================================================
//  ==================================    Helper Panel     (Finish)    =====================================
//  =========================================================================================================
//  =========================================================================================================






