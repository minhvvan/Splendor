// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDMultMenu.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/ScrollBox.h"
#include "Components/Border.h"
#include "SteamTestGameInstance.h"
#include "Components/SlateWrapperTypes.h"
#include "OnlineSessionSettings.h"
#include "HUDServerRow.h"


void UHUDMultMenu::NativeOnInitialized()
{
	BtnHostGame->OnClicked.AddDynamic(this, &UHUDMultMenu::HostGameClicked);
	BtnSearchGame->OnClicked.AddDynamic(this, &UHUDMultMenu::SearchGameClicked);
	BtnBack->OnClicked.AddDynamic(this, &UHUDMultMenu::BackClicked);

	SetConnectionText();
}

void UHUDMultMenu::HostGameClicked()
{
	if (auto GameInstance = Cast<USteamTestGameInstance>(GetGameInstance()))
	{
		GameInstance->CreateSession();
	}
}

void UHUDMultMenu::SearchGameClicked()
{
	if (auto GameInstance = Cast<USteamTestGameInstance>(GetGameInstance()))
	{
		GameInstance->FindSession();
	}
}

void UHUDMultMenu::BackClicked()
{
	if (auto GameInstance = Cast<USteamTestGameInstance>(GetGameInstance()))
	{
		GameInstance->ShowMainMenu();
	}

	RemoveFromParent();
}

void UHUDMultMenu::SetConnectionText()
{
	TxtConnection->SetText(FText::FromString("Online"));
}

void UHUDMultMenu::PreSessionSearch()
{
	BorderServerList->SetVisibility(ESlateVisibility::Visible);
	BorderMenuBtn->SetIsEnabled(false);

	TxtSearchGame->SetText(FText::FromString("Searching...."));

	SclServerList->ClearChildren();
}
