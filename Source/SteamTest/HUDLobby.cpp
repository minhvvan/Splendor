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
#include "PSPlayerInfo.h"
#include "GSLobby.h"

void UHUDLobby::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	BtnFirstPlayer->OnClicked.AddDynamic(this, &UHUDLobby::FirstPlayerClicked);
	BtnFirstPlayer->OnHovered.AddDynamic(this, &UHUDLobby::OnHoveredFirst);
	BtnFirstPlayer->OnUnhovered.AddDynamic(this, &UHUDLobby::OnLeavedFirst);

	BtnSecondPlayer->OnClicked.AddDynamic(this, &UHUDLobby::SecondPlayerClicked);
	BtnSecondPlayer->OnHovered.AddDynamic(this, &UHUDLobby::OnHoveredSecond);
	BtnSecondPlayer->OnUnhovered.AddDynamic(this, &UHUDLobby::OnLeavedSecond);

	BtnStartGame->OnClicked.AddDynamic(this, &UHUDLobby::StartGameClicked);
	BtnStartGame->OnHovered.AddDynamic(this, &UHUDLobby::StartGameHovered);
	BtnStartGame->OnUnhovered.AddDynamic(this, &UHUDLobby::StartGameLeaved);
	//BtnSubmit->OnClicked.AddDynamic(this, &UHUDLobby::BackClicked);

	EdtChat->OnTextCommitted.AddDynamic(this, &UHUDLobby::OnChatTextCommitted);
}

//!--------------First-----------
void UHUDLobby::FirstPlayerClicked()
{
	Cast<APCLobby>(GetOwningPlayer())->SRFirstPlayerClicked();
}

void UHUDLobby::OnHoveredFirst()
{
	if (FirstHoverAnim) PlayAnimation(FirstHoverAnim);
}

void UHUDLobby::OnLeavedFirst()
{
	if (FirstHoverAnim) PlayAnimationReverse(FirstHoverAnim);
}


//!--------------Second-----------
void UHUDLobby::SecondPlayerClicked()
{
	Cast<APCLobby>(GetOwningPlayer())->SRSecondPlayerClicked();
}

void UHUDLobby::OnHoveredSecond()
{
	if (SecondHoverAnim) PlayAnimation(SecondHoverAnim);
}

void UHUDLobby::OnLeavedSecond()
{
	if (SecondHoverAnim) PlayAnimationReverse(SecondHoverAnim);
}

void UHUDLobby::StartGameClicked()
{
	//GM에게 Widget 떼라고 말해야 함
	auto PC = Cast<APCLobby>(GetOwningPlayer());
	if (PC) PC->SRStartGame();
}

void UHUDLobby::StartGameHovered()
{
	if (StartGameAnim) PlayAnimation(StartGameAnim);
}

void UHUDLobby::StartGameLeaved()
{
	if (StartGameAnim) PlayAnimationReverse(StartGameAnim);
}

void UHUDLobby::OnChatTextCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	//String 최신화
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

void UHUDLobby::SuccessSelect()
{
	if (ClickSound) PlaySound(ClickSound);
}

void UHUDLobby::CancelSelect()
{
	if (CancelSound) PlaySound(CancelSound);
}

void UHUDLobby::FailSelect()
{
	if (MessageAnim) PlayAnimation(MessageAnim);
	if (FailSound) PlaySound(FailSound);
}
