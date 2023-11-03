// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDLobby.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/MultiLineEditableText.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "STGameModeLobby.h"
#include "PCLobby.h"
#include "GSLobby.h"

void UHUDLobby::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	BtnFirstPlayer->OnClicked.AddDynamic(this, &UHUDLobby::FirstPlayerClicked);
	BtnSecondPlayer->OnClicked.AddDynamic(this, &UHUDLobby::SecondPlayerClicked);
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
	if (MainPC)
	{
		MainPC->SecondPlayerClicked();
	}
}

void UHUDLobby::StartGameClicked()
{
	//GM에게 Widget 떼라고 말해야 함
	auto PC = Cast<APCLobby>(GetOwningPlayer());
	if (PC)
	{
		PC->SRStartGame();
	}
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

void UHUDLobby::SetCanStart(bool bCanStart)
{
	BtnStartGame->SetIsEnabled(bCanStart);
}