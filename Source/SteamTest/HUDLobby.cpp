// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDLobby.h"
#include "Components/Button.h"
#include "Components/MultiLineEditableText.h"
#include "PCLobby.h"

void UHUDLobby::NativeOnInitialized()
{
	BtnFirstPlayer->OnClicked.AddDynamic(this, &UHUDLobby::FirstPlayerClicked);
	BtnSecondPlayer->OnClicked.AddDynamic(this, &UHUDLobby::SecondPlayerClicked);
	BtnStartGame->OnClicked.AddDynamic(this, &UHUDLobby::StartGameClicked);
	//BtnSubmit->OnClicked.AddDynamic(this, &UHUDLobby::BackClicked);

	EdtChat->OnTextCommitted.AddDynamic(this, &UHUDLobby::OnChatTextCommitted);
}

void UHUDLobby::FirstPlayerClicked()
{
	auto PC = Cast<APCLobby>(GetOwningPlayer());
	if (IsValid(PC))
	{
		PC->FirstPlayerClicked();
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
