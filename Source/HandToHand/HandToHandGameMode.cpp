// Copyright Epic Games, Inc. All Rights Reserved.

#include "HandToHandGameMode.h"
#include "HandToHandCharacter.h"
#include "UObject/ConstructorHelpers.h"

AHandToHandGameMode::AHandToHandGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
