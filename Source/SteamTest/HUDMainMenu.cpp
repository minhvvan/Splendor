// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDMainMenu.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "SteamTestGameInstance.h"
#include "Types/SlateEnums.h"


void UHUDMainMenu::NativeOnInitialized()
{
	BtnSoloGame->OnClicked.AddDynamic(this, &UHUDMainMenu::SoloGameClicked);
	BtnMult->OnClicked.AddDynamic(this, &UHUDMainMenu::MultGameClicked);
	BtnQuitGame->OnClicked.AddDynamic(this, &UHUDMainMenu::QuitGameClicked);
	EdtPlayerName->OnTextCommitted.AddDynamic(this, &UHUDMainMenu::OnChatTextCommitted);
}

void UHUDMainMenu::SoloGameClicked()
{
	if (auto GameInstance = Cast<USteamTestGameInstance>(GetGameInstance()))
	{
		GameInstance->StartSoloGame();
	}

	RemoveFromParent();
}

void UHUDMainMenu::MultGameClicked()
{
	if (auto GameInstance = Cast<USteamTestGameInstance>(GetGameInstance()))
	{
		GameInstance->ShowMultMenu();
	}

	RemoveFromParent();
}

void UHUDMainMenu::QuitGameClicked()
{
	UKismetSystemLibrary::QuitGame(this, 0, EQuitPreference::Quit, false);
}

void UHUDMainMenu::ChangedPlayerName(const FText& Text)
{
	if (auto GameInstance = Cast<USteamTestGameInstance>(GetGameInstance()))
	{
		GameInstance->MakePlayerInfo(Text.ToString());
	}
}

void UHUDMainMenu::OnChatTextCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	UE_LOG(LogTemp, Warning, TEXT("commit"));
	if (auto GameInstance = Cast<USteamTestGameInstance>(GetGameInstance()))
	{
		GameInstance->MakePlayerInfo(Text.ToString());
	}
}

void UHUDMainMenu::SetPlayerName(FString& name)
{
	EdtPlayerName->SetText(FText::FromString(name));
}
