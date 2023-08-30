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
	BtnConnection->OnClicked.AddDynamic(this, &UHUDMultMenu::ConnectionClicked);
	BtnBack->OnClicked.AddDynamic(this, &UHUDMultMenu::BackClicked);

	SetConnectionText();
}

void UHUDMultMenu::HostGameClicked()
{
	if (auto GameInstance = Cast<USteamTestGameInstance>(GetGameInstance()))
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("click")));

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

void UHUDMultMenu::ConnectionClicked()
{
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
	if (auto GameInstance = Cast<USteamTestGameInstance>(GetGameInstance()))
	{
		if (GameInstance->GetIsLanConnect())
		{
			TxtConnection->SetText(FText::FromString("LAN"));
		}
		else
		{
			TxtConnection->SetText(FText::FromString("Online"));
		}
	}
}

void UHUDMultMenu::PreSessionSearch()
{
	BorderServerList->SetVisibility(ESlateVisibility::Visible);
	BorderMenuBtn->SetIsEnabled(false);

	TxtSearchGame->SetText(FText::FromString("Searching...."));

	SclServerList->ClearChildren();
}
