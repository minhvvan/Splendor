// Fill out your copyright notice in the Description page of Project Settings.


#include "PCMenu.h"
#include "Blueprint/UserWidget.h"
#include "HUDMainMenu.h"
#include "HUDMultMenu.h"
#include "HUDLobby.h"
#include "HUDServerRow.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ScrollBox.h"


APCMenu::APCMenu()
{
	ConstructorHelpers::FClassFinder<UUserWidget> MULT(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Widget/WBP_MultMenu.WBP_MultMenu_C'"));
	if (MULT.Succeeded())
	{
		MultMenuClass = MULT.Class;
	}

	ConstructorHelpers::FClassFinder<UUserWidget> LOBBY(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Widget/WBP_Lobby.WBP_Lobby_C'"));
	if (LOBBY.Succeeded())
	{
		LobbyClass = LOBBY.Class;
	}
}


void APCMenu::ShowMultMenu()
{
	if (!WidgetMultMenu)
	{
		WidgetMultMenu = Cast<UHUDMultMenu>(CreateWidget(GetWorld(), MultMenuClass));
	}

	WidgetMultMenu->AddToViewport();
	SetInputMode(FInputModeUIOnly());
	SetShowMouseCursor(true);
}

void APCMenu::ShowLobby()
{
	if (!WidgetLobby)
	{
		WidgetLobby = Cast<UHUDLobby>(CreateWidget(GetWorld(), LobbyClass));
	}

	WidgetLobby->AddToViewport();
	SetInputMode(FInputModeUIOnly());
	SetShowMouseCursor(true);
}

void APCMenu::PreSessionSearch()
{
	if (WidgetMultMenu)
	{
		auto Scroll = WidgetMultMenu->GetScrollServer();
		WidgetMultMenu->PreSessionSearch();
	}
}

void APCMenu::AddSessionRow(UHUDServerRow* row)
{
	if (WidgetMultMenu)
	{
		auto Scroll = WidgetMultMenu->GetScrollServer();
		Scroll->AddChild(row);
	}
}
