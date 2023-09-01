// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDLobby.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/MultiLineEditableText.h"
#include "Kismet/GameplayStatics.h"
#include "PCLobby.h"
#include "Components/AudioComponent.h"


void UHUDLobby::NativeOnInitialized()
{
	BtnFirstPlayer->OnClicked.AddDynamic(this, &UHUDLobby::FirstPlayerClicked);
	BtnStartGame->OnClicked.AddDynamic(this, &UHUDLobby::StartGameClicked);
	//BtnSubmit->OnClicked.AddDynamic(this, &UHUDLobby::BackClicked);

	EdtChat->OnTextCommitted.AddDynamic(this, &UHUDLobby::OnChatTextCommitted);
}

void UHUDLobby::FirstPlayerClicked()
{
	if (MainPC)
	{
		MainPC->FirstPlayerClicked();
	}
}

void UHUDLobby::SecondPlayerClicked()
{
}

void UHUDLobby::StartGameClicked()
{
	//Server 인지 check -> 맞으면 start game
}

void UHUDLobby::OnChatTextCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
}

void UHUDLobby::SetPC(APlayerController* PC)
{
	if (PC)
	{
		MainPC = Cast<APCLobby>(PC);
	}
}

void UHUDLobby::SetFirstText(FString text)
{
	TxtFirstPlayer->SetText(FText::FromString(text));
}
