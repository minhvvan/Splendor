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
	//Server 인지 check -> 맞으면 start game
	GEngine->AddOnScreenDebugMessage(-1, 15, FColor::Red, FString::Printf(TEXT("Start")));

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
	if(bCanStart)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15, FColor::Blue, FString::Printf(TEXT("SetCanStart")));
	}

	BtnStartGame->SetIsEnabled(bCanStart);
}