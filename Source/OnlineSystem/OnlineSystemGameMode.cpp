// Copyright Epic Games, Inc. All Rights Reserved.

#include "OnlineSystemGameMode.h"
#include "OnlineSystemCharacter.h"
#include "UObject/ConstructorHelpers.h"

AOnlineSystemGameMode::AOnlineSystemGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
