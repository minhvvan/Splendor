// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDMainMenu.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "SteamTestGameInstance.h"
#include "Types/SlateEnums.h"
#include "PCMenu.h"
#include "PSPlayerInfo.h"

void UHUDMainMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	BtnPlay->OnClicked.AddDynamic(this, &UHUDMainMenu::PlayGameClicked);
	BtnQuitGame->OnClicked.AddDynamic(this, &UHUDMainMenu::QuitGameClicked);
	EdtPlayerName->OnTextCommitted.AddDynamic(this, &UHUDMainMenu::ChangedPlayerName);
}

void UHUDMainMenu::PlayGameClicked()
{
	Cast<APCMenu>(GetOwningPlayer())->ShowMultMenu();

	RemoveFromParent();
}

void UHUDMainMenu::QuitGameClicked()
{
	UKismetSystemLibrary::QuitGame(this, 0, EQuitPreference::Quit, false);
}

void UHUDMainMenu::ChangedPlayerName(const FText& Text, ETextCommit::Type CommitMethod)
{
	auto GI = Cast<USteamTestGameInstance>(GetGameInstance());
	APCMenu* PC = Cast<APCMenu>(GetOwningPlayer());
	auto PS = PC->GetPlayerState<APSPlayerInfo>();
	if (PS)
	{
		PS->SetPName(Text.ToString());
		GI->SaveGame();
	}
}

void UHUDMainMenu::SetPlayerName(FString& name)
{
	EdtPlayerName->SetText(FText::FromString(name));
}
