

#include "HUDLobby.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/EditableText.h"
#include "Components/ScrollBox.h"
#include "Components/ScrollBoxSlot.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "STGameModeLobby.h"
#include "PCLobby.h"
#include "PSPlayerInfo.h"
#include "GSLobby.h"
#include "HUDChatRow.h"
#include "HUDNotifyRow.h"

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
	BtnSubmit->OnClicked.AddDynamic(this, &UHUDLobby::SendChat);

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


//!--------------StartGame-----------
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


//!--------------Chat-----------
void UHUDLobby::OnChatTextCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	//String 최신화
	ChatMsg = Text.ToString();

	if (CommitMethod == ETextCommit::OnEnter)
	{
		EdtChat->SetFocus();

		//전송
		SendChat();
	}
}

void UHUDLobby::SendChat()
{
	if (ChatMsg.Len() == 0) return;

	auto Row = Cast<UHUDChatRow>(CreateWidget(GetWorld(), ChatRowClass));
	Row->SetText(ChatMsg);

	auto AddedSlot = ScrollChat->AddChild(Row);
	Cast<UScrollBoxSlot>(AddedSlot)->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Right);

	auto PC = Cast<APCLobby>(GetOwningPlayer());
	PC->SRSendChat(ChatMsg);

	EdtChat->SetText(FText::FromString(""));
	ChatMsg.Empty();

	if (SendChatSound) PlaySound(SendChatSound);
}

void UHUDLobby::RecvChat(const FString& msg)
{
	auto Row = Cast<UHUDChatRow>(CreateWidget(GetWorld(), ChatRowClass));
	Row->SetText(msg);

	auto AddedSlot = ScrollChat->AddChild(Row);
	Cast<UScrollBoxSlot>(AddedSlot)->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Left);

	if (RecvChatSound) PlaySound(RecvChatSound);
}

void UHUDLobby::RecvNoti(const FString& msg)
{
	auto Row = Cast<UHUDNotifyRow>(CreateWidget(GetWorld(), NotiRowClass));
	Row->SetText(msg);

	auto AddedSlot = ScrollChat->AddChild(Row);
	Cast<UScrollBoxSlot>(AddedSlot)->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);

	if (RecvChatSound) PlaySound(RecvChatSound);
}

//!--------------Util-----------
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
