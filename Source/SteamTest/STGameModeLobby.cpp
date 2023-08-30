// Fill out your copyright notice in the Description page of Project Settings.


#include "STGameModeLobby.h"
#include "SteamTestCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "SteamTestGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "PCMenu.h"

ASTGameModeLobby::ASTGameModeLobby()
{
	bUseSeamlessTravel = true;

	static ConstructorHelpers::FClassFinder<APlayerController> PlayerController(TEXT("/Script/Engine.Blueprint'/Game/Framework/BP_PCMenu.BP_PCMenu_C'"));
	if (PlayerController.Class != NULL)
	{
		PlayerControllerClass = PlayerController.Class;
	}
}

void ASTGameModeLobby::BeginPlay()
{
}

void ASTGameModeLobby::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	PlayerControllers.Add(NewPlayer);
}

void ASTGameModeLobby::SwapPlayerControllers(APlayerController* OldPC, APlayerController* NewPC)
{
	PlayerControllers.Add(NewPC);
}

void ASTGameModeLobby::Logout(AController* Exiting)
{
	auto PCtarget = Cast<APCMenu>(Exiting);

	PlayerControllers.Remove(PCtarget);
}

