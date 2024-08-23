// Copyright Epic Games, Inc. All Rights Reserved.

#include "Game_PrototypeGameMode.h"
#include "Game_PrototypeCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGame_PrototypeGameMode::AGame_PrototypeGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
