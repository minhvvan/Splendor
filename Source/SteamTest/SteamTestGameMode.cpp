// Copyright Epic Games, Inc. All Rights Reserved.

#include "SteamTestGameMode.h"
#include "SteamTestCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "SteamTestGameInstance.h"

ASteamTestGameMode::ASteamTestGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ASteamTestGameMode::BeginPlay()
{
	Cast<USteamTestGameInstance>(GetGameInstance())->ShowMainMenu();
}
