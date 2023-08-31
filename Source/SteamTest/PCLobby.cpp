// Fill out your copyright notice in the Description page of Project Settings.


#include "PCLobby.h"
#include "Blueprint/UserWidget.h"
#include "HUDMainMenu.h"
#include "HUDMultMenu.h"
#include "HUDLobby.h"
#include "HUDServerRow.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ScrollBox.h"
#include "STGameModeLobby.h"


APCLobby::APCLobby()
{
	ConstructorHelpers::FClassFinder<UUserWidget> LOBBY(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Widget/WBP_Lobby.WBP_Lobby_C'"));
	if (LOBBY.Succeeded())
	{
		LobbyClass = LOBBY.Class;
	}
}

void APCLobby::BeginPlay()
{
	if (IsLocalController())
	{
		//SRSpawnPlayer();
		ShowLobby();
	}
}

void APCLobby::SRSpawnPlayer_Implementation()
{
	//gamemode ¹Þ±â
	ASTGameModeLobby* GMLobby = Cast< ASTGameModeLobby>(UGameplayStatics::GetGameMode(GetWorld()));
	GMLobby->SpawnPlayer(this);
}


void APCLobby::ShowLobby()
{
	if (!WidgetLobby)
	{
		WidgetLobby = Cast<UHUDLobby>(CreateWidget(GetWorld(), LobbyClass));
	}

	WidgetLobby->AddToViewport();
	SetInputMode(FInputModeUIOnly());
	SetShowMouseCursor(true);
}

void APCLobby::FirstPlayerClicked()
{
	if (IsLocalController())
	{
		SRFirstPlayerClicked();
	}
}

void APCLobby::SRFirstPlayerClicked_Implementation()
{
	ASTGameModeLobby* GMLobby = Cast< ASTGameModeLobby>(UGameplayStatics::GetGameMode(GetWorld()));
	GEngine->AddOnScreenDebugMessage(-1, 15, FColor::Red, FString::Printf(TEXT("fist")));
}