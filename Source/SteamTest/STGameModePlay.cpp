// Fill out your copyright notice in the Description page of Project Settings.


#include "STGameModePlay.h"

ASTGameModePlay::ASTGameModePlay()
{
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerController(TEXT("/Script/Engine.Blueprint'/Game/Framework/BP_PlayerContoller.BP_PlayerContoller_C'"));
	if (PlayerController.Class != NULL)
	{
		PlayerControllerClass = PlayerController.Class;
	}

	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
