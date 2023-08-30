// Fill out your copyright notice in the Description page of Project Settings.


#include "STGameModeDefault.h"
#include "SteamTestCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "SteamTestGameInstance.h"


ASTGameModeDefault::ASTGameModeDefault()
{
	bUseSeamlessTravel = true;

	static ConstructorHelpers::FClassFinder<APlayerController> PlayerController(TEXT("/Script/Engine.Blueprint'/Game/Framework/BP_PCMenu.BP_PCMenu_C'"));
	if (PlayerController.Class != NULL)
	{
		PlayerControllerClass = PlayerController.Class;
	}

	DefaultPawnClass = nullptr;
}

void ASTGameModeDefault::BeginPlay()
{
	Cast<USteamTestGameInstance>(GetGameInstance())->ShowMainMenu();
}