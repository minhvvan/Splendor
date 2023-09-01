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
#include "PSPlayerInfo.h"


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
		ShowLobby();
	}
}

void APCLobby::SRSpawnPlayer_Implementation()
{
	//gamemode 받기
	ASTGameModeLobby* GMLobby = Cast< ASTGameModeLobby>(UGameplayStatics::GetGameMode(GetWorld()));
	GMLobby->SpawnPlayer(this);
}


void APCLobby::ShowLobby()
{
	if (!WidgetLobby)
	{
		WidgetLobby = Cast<UHUDLobby>(CreateWidget(GetWorld(), LobbyClass));
		WidgetLobby->SetPC(this);
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

void APCLobby::MarkFirst_Implementation(const FString& name)
{
	if (IsLocalController())
	{
		GEngine->AddOnScreenDebugMessage(-1, 15, FColor::Red, FString::Printf(TEXT("MarkFirst")));

		if (WidgetLobby)
		{
			WidgetLobby->SetFirstText(name);
		}
	}
}

void APCLobby::SRFirstPlayerClicked_Implementation()
{
	ASTGameModeLobby* GMLobby = Cast< ASTGameModeLobby>(UGameplayStatics::GetGameMode(GetWorld()));
	//main에서 입력한 name 전달(지금은 hard)
	//auto PS = GetPlayerState<APSPlayerInfo>();
	//auto PlayerName = PS->GetPlayerName();
	FString PlayerName = "minhwan";

	GMLobby->FirstPlayerMark(PlayerName);
}