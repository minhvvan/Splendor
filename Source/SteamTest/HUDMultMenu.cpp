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
	Super::NativeOnInitialized();
	
	BtnHostGame->OnClicked.AddDynamic(this, &UHUDMultMenu::HostGameClicked);
	BtnHostGame->OnHovered.AddDynamic(this, &UHUDMultMenu::HostGameHovered);
	BtnHostGame->OnUnhovered.AddDynamic(this, &UHUDMultMenu::HostGameLeaved);

	BtnSearchGame->OnClicked.AddDynamic(this, &UHUDMultMenu::SearchGameClicked);
	BtnSearchGame->OnHovered.AddDynamic(this, &UHUDMultMenu::SearchGameHovered);
	BtnSearchGame->OnUnhovered.AddDynamic(this, &UHUDMultMenu::SearchGameLeaved);

	BtnBack->OnClicked.AddDynamic(this, &UHUDMultMenu::BackClicked);
	BtnBack->OnHovered.AddDynamic(this, &UHUDMultMenu::BackHovered);
	BtnBack->OnUnhovered.AddDynamic(this, &UHUDMultMenu::BackLeaved);
}

void UHUDMultMenu::HostGameClicked()
{
	if (auto GameInstance = Cast<USteamTestGameInstance>(GetGameInstance()))
	{
		GameInstance->CreateSession();
	}
}

void UHUDMultMenu::HostGameHovered()
{
	if (BtnHostHover) PlayAnimation(BtnHostHover);
}

void UHUDMultMenu::HostGameLeaved()
{
	if (BtnHostHover) PlayAnimationReverse(BtnHostHover);
}

void UHUDMultMenu::SearchGameClicked()
{
	PreSessionSearch();

	if (auto GameInstance = Cast<USteamTestGameInstance>(GetGameInstance()))
	{
		GameInstance->FindSession();
	}
}

void UHUDMultMenu::SearchGameHovered()
{
	if (BtnSearchHover) PlayAnimation(BtnSearchHover);
}

void UHUDMultMenu::SearchGameLeaved()
{
	if (BtnSearchHover) PlayAnimationReverse(BtnSearchHover);
}

void UHUDMultMenu::BackClicked()
{
	if (auto GameInstance = Cast<USteamTestGameInstance>(GetGameInstance()))
	{
		GameInstance->ShowMainMenu();
	}

	RemoveFromParent();
}

void UHUDMultMenu::BackHovered()
{
	if (BtnBackHover) PlayAnimation(BtnBackHover);
}

void UHUDMultMenu::BackLeaved()
{
	if (BtnBackHover) PlayAnimationReverse(BtnBackHover);
}

void UHUDMultMenu::PreSessionSearch()
{
	BorderServerList->SetVisibility(ESlateVisibility::Visible);
	BorderMenuBtn->SetIsEnabled(false);

	TxtSearchGame->SetText(FText::FromString("Searching...."));

	SclServerList->ClearChildren();
}

void UHUDMultMenu::RenderMessage()
{
	if (MessageAnim) PlayAnimation(MessageAnim);
	if (FailedSound) PlaySound(FailedSound);
}

void UHUDMultMenu::AddSessionRow(UHUDServerRow* row)
{
	if(SclServerList) SclServerList->AddChild(row);
}

void UHUDMultMenu::FailedSessionSearch()
{
	RenderMessage();

	BorderServerList->SetVisibility(ESlateVisibility::Hidden);
	BorderMenuBtn->SetIsEnabled(true);

	TxtSearchGame->SetText(FText::FromString("Search Game"));
}
