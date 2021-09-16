// Copyright Epic Games, Inc. All Rights Reserved.

#include "DialogSystem_TestGameMode.h"
#include "DialogSystem_TestCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADialogSystem_TestGameMode::ADialogSystem_TestGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
