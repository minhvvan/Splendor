// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDLobby.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/MultiLineEditableText.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PCLobby.h"
#include "GSLobby.h"


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
	auto GS = GetWorld()->GetGameState<AGSLobby>();
	if (!GS->SetFirstPlayer(MainPC))
	{
		SetFirstText("");
	}

	//!TODO: 여기가 이상함 -> pram이 없고 넘어가서 info를 따서 세팅하게됨
	if (MainPC)
	{
		MainPC->FirstPlayerClicked(/*param*/);
	}
}

void UHUDLobby::SecondPlayerClicked()
{
	auto GS = GetWorld()->GetGameState<AGSLobby>();
	auto SecondPlayer = GS->GetSecondPlayer();

	if (SecondPlayer)
	{
		if (MainPC == SecondPlayer)
		{
			//해제
			GS->SetSecondPlayer(nullptr);
			SetSecondText("");
		}
		else
		{
			//선택 불가
		}
	}
	else
	{
		if (MainPC)
		{
			GS->SetSecondPlayer(MainPC);
			MainPC->SecondPlayerClicked();
		}
	}
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

void UHUDLobby::SetSecondText(FString text)
{
	TxtSecondPlayer->SetText(FText::FromString(text));
}
