// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDDesk.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Sound/SoundCue.h"
#include "HUDCardHolder.h"
#include "HUDTokenHolder.h"
#include "HUDOverToken.h"
#include "HUDDetailCard.h"
#include "HUDGetToken.h"
#include "HUDSelectRoyal.h"
#include "HUDSelectCard.h"
#include "HUDHand.h"
#include "HudRivalInfo.h"
#include "HUDEndGame.h"
#include "PCPlay.h"
#include "PSPlayerInfo.h"
#include "GSPlay.h"
#include "Token.h"
#include "Card.h"
#include "CardManager.h"
#include "GlobalEnum.h"
#include "GlobalConst.h"
#include "HUDTakeToken.h"
#include "HUDAnyColor.h"
#include "STGameModePlay.h"


void UHUDDesk::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	CDHRed->SetImage(ETokenColor::E_Red);
	CDHGreen->SetImage(ETokenColor::E_Green);
	CDHBlue->SetImage(ETokenColor::E_Blue);
	CDHWhite->SetImage(ETokenColor::E_White);
	CDHBlack->SetImage(ETokenColor::E_Black);

	BtnGetToken->OnClicked.AddDynamic(this, &UHUDDesk::GetTokenClicked);
	BtnFillToken->OnClicked.AddDynamic(this, &UHUDDesk::FilTokenClicked);
	BtnUseScroll->OnClicked.AddDynamic(this, &UHUDDesk::UseScrollClicked);

	Hand->OnCard.AddUObject(this, &UHUDDesk::OnHandCardClicked);
}

void UHUDDesk::IntSetTurnBegin(const FString& turn)
{
	FString newText = turn;
	newText.Append(UGlobalConst::SuffixTurnText);

	TxtTurn->SetText(FText::FromString(newText));
	bUsedScroll = false;

	//anim도 있으면 좋을듯
}

void UHUDDesk::BindState(APSPlayerInfo* ps)
{
	if (IsValid(ps))
	{
		CurrentState = ps;
		ps->OnScrollChanged.AddUObject(this, &UHUDDesk::ChangedScroll);
		ps->OnOverToken.AddUObject(this, &UHUDDesk::NotifyOverToken);
		ps->OnChangeToken.AddUObject(this, &UHUDDesk::ChangedToken);
		ps->OnChangeBonus.AddUObject(this, &UHUDDesk::ChangedBonus);
		ps->OnChangeScore.AddUObject(this, &UHUDDesk::ChangedScore);
		ps->OnChangeColorScore.AddUObject(this, &UHUDDesk::ChangedColorScore);
		ps->OnChangeCrown.AddUObject(this, &UHUDDesk::ChangedCrown);
		ps->OnCrownEvent.AddUObject(this, &UHUDDesk::CrownEvent);
	}
}

void UHUDDesk::ChangedScroll()
{
	if (CurrentState.IsValid())
	{
		TxtScroll->SetText(FText::AsNumber(CurrentState->GetScroll()));
	}
}

void UHUDDesk::ChangedToken()
{
	if (CurrentState.IsValid() && TokenHolder)
	{
		TokenHolder->UpdateTokenNum(CurrentState.Get());
	}
}

UHUDCardHolder* UHUDDesk::GetBonusWidget(ETokenColor color)
{
	switch (color)
	{
	case ETokenColor::E_Red:
		return CDHRed;
		break;
	case ETokenColor::E_Green:
		return CDHGreen;
		break;
	case ETokenColor::E_Blue:
		return CDHBlue;
		break;
	case ETokenColor::E_White:
		return CDHWhite;
		break;
	case ETokenColor::E_Black:
		return CDHBlack;
		break;
	}

	return nullptr;
}

void UHUDDesk::CloseItemWidget(EItem itemType)
{
	bool bEndTurn = true;

	switch (itemType)
	{
	case EItem::I_GetToken:
		check(GetWidget.IsValid());
		bEndTurn = GetWidget->GetBEndTurn();
		GetWidget->RemoveFromParent();
		GetWidget.Reset();
		break;
	case EItem::I_TakeToken:
		check(TakeWidget.IsValid());
		TakeWidget->RemoveFromParent();
		TakeWidget.Reset();
		break;
	}

	if(bEndTurn) Cast<APCPlay>(GetOwningPlayer())->SREndTurn();
}

void UHUDDesk::CloseCrownWidget()
{
	check(CrownWidget.IsValid());

	CrownWidget->RemoveFromParent();
	CrownWidget.Reset();
}

void UHUDDesk::CloseCardWidget()
{
	check(CardWidget.IsValid());

	CardWidget->RemoveFromParent();
	CardWidget.Reset();
}

void UHUDDesk::CloseRivalInfo()
{
	if (!RivalInfoWidget.Get()) return;

	RivalInfoWidget->RemoveFromParent();
	RivalInfoWidget.Reset();
}

void UHUDDesk::ChangedBonus()
{
	if (CurrentState.IsValid())
	{
		for (auto color : TEnumRange<ETokenColor>())
		{
			auto widget = GetBonusWidget(color);

			if (widget)
			{
				widget->SetBonusTxt(CurrentState->GetBonusNum(color));
			}
		}
	}
}

void UHUDDesk::ChangedScore()
{
	if (CurrentState.IsValid())
	{
		TxtScore->SetText(FText::AsNumber(CurrentState->GetTotalScore()));
	}
}

void UHUDDesk::ChangedColorScore()
{
	if (CurrentState.IsValid())
	{
		for (auto color : TEnumRange<ETokenColor>())
		{
			auto widget = GetBonusWidget(color);

			if (widget)
			{
				widget->SetScoreTxt(CurrentState->GetScoreByColor(color));
			}
		}
	}
}

void UHUDDesk::ChangedCrown()
{
	if (CurrentState.IsValid())
	{
		TxtCrown->SetText(FText::AsNumber(CurrentState->GetCrown()));
	}
}

void UHUDDesk::CrownEvent()
{
	if (RoyalWidgetClass)
	{
		CrownWidget = Cast<UHUDSelectRoyal>(CreateWidget(GetWorld(), RoyalWidgetClass));
		check(CrownWidget.IsValid());

		auto PS = GetOwningPlayer()->GetPlayerState<APSPlayerInfo>();
		CrownWidget->SetScore(PS->GetScore());
		CrownWidget->SetCrown(PS->GetCrown());
		CrownWidget->SetScroll(PS->GetScroll());

		CrownWidget->SetRoyal();
		CrownWidget->AddToViewport();
	}
}

void UHUDDesk::RenderMessage(FString message)
{
	if (TxtMessage)
	{
		TxtMessage->SetText(FText::FromString(message));
	}

	if (MessageAnim)
	{
		PlayAnimation(MessageAnim);
	}
}

void UHUDDesk::AddCardToHand(FCardInfo cardInfo)
{
	check(IsValid(Hand));

	Hand->AddCard(cardInfo);
}

void UHUDDesk::OnHandCardClicked(FCardInfo cardInfo)
{
	PopUpDetailCard(cardInfo);
}

void UHUDDesk::GetTokenClicked()
{
	auto PC = Cast<APCPlay>(GetOwningPlayer());

	if (PC)
	{
		auto Tokens = PC->GetSelectedTokens();

		if (Tokens.Num() == 0)
		{
			FailAnimPlay(EFailWidget::E_GetToken);
			return;
		}

		PC->PossessTokens();
	}
}

void UHUDDesk::FilTokenClicked()
{
	Cast<APCPlay>(GetOwningPlayer())->SRFillToken();
}

void UHUDDesk::UseScrollClicked()
{
	if (bUsedScroll)
	{
		FailAnimPlay(EFailWidget::E_TwiceUseScroll);
		return;
	}

	auto PS = GetOwningPlayer()->GetPlayerState<APSPlayerInfo>();
	if (PS)
	{
		auto ScrollNum = PS->GetScroll();
		
		if (ScrollNum == 0)
		{
			FailAnimPlay(EFailWidget::E_UseScroll);
			return;
		}
	}

	TArray<ETokenColor> colors;
	for (ETokenColor color : TEnumRange<ETokenColor>())
	{
		if (color == ETokenColor::E_End || color == ETokenColor::E_Gold) continue;
		colors.Add(color);
	}

	PopUpItemGetToken(colors, false);
	Cast<APCPlay>(GetOwningPlayer())->SRUseScroll();
	bUsedScroll = true;
}

void UHUDDesk::FailAnimPlay(EFailWidget failWidget)
{
	switch (failWidget)
	{
	case EFailWidget::E_GetToken:
		if (FailedGetAnim)
		{
			PlayAnimation(FailedGetAnim);
			RenderMessage(UGlobalConst::MsgNotSelect);
		}
		break;
	case EFailWidget::E_FillToken:
		if (FailedFillAnim)
		{
			PlayAnimation(FailedFillAnim);
			RenderMessage(UGlobalConst::MsgNoPouch);
		}
		break;
	case EFailWidget::E_UseScroll:
		if (FailedUseScrollAnim)
		{
			PlayAnimation(FailedUseScrollAnim);
			RenderMessage(UGlobalConst::MsgCanNotUseScroll);
		}	
	case EFailWidget::E_TwiceUseScroll:
		if (FailedUseScrollAnim)
		{
			PlayAnimation(FailedUseScrollAnim);
			RenderMessage(UGlobalConst::MsgUsedScroll);
		}
		break;
	}

	if (FailSound)
	{
		PlaySound(FailSound);
	}
}

void UHUDDesk::NotifyOverToken()
{
	if (OverTokenClass)
	{
		auto widget = Cast<UHUDOverToken>(CreateWidget(GetWorld(), OverTokenClass));
		if (widget)
		{
			widget->AddToViewport();
		}
	}
}

void UHUDDesk::PopUpDetailCard(const FCardInfo& cardInfo)
{
	check(IsValid(DetailCardClass));

	auto widget = Cast<UHUDDetailCard>(CreateWidget(GetWorld(), DetailCardClass));
	if (widget)
	{
		widget->SetCardInfo(cardInfo);
		widget->AddToViewport();
	}
}

void UHUDDesk::PopUpItemGetToken(const TArray<ETokenColor>& colors, bool bEndturn)
{
	GetWidget = Cast<UHUDGetToken>(CreateWidget(GetWorld(), GetTokenWidgetClass));
	auto& TileIdxs = GetWorld()->GetGameState<AGSPlay>()->GetCurrentTileState();
	GetWidget->SetTiles(TileIdxs, colors);
	GetWidget->SetBEndTurn(bEndturn);
	GetWidget->AddToViewport();
}

void UHUDDesk::PopUpItemTakeToken()
{
	auto TokenList = Cast<APCPlay>(GetOwningPlayer())->GetOppTokens();

	int total = 0;
	for (auto token : TokenList)
	{
		if (token.Key == ETokenColor::E_Gold) continue;
		total += token.Value;
	}

	if (total == 0)
	{
		RenderMessage(UGlobalConst::MsgCanNotTake);
		return;
	}

	TakeWidget = Cast<UHUDTakeToken>(CreateWidget(GetWorld(), TakeTokenWidgetClass));
	TakeWidget->SetTokens(TokenList);
	TakeWidget->AddToViewport();
}

void UHUDDesk::PopUpItemAnyColor(const FCardInfo& cardInfo)
{
	auto widget = Cast<UHUDAnyColor>(CreateWidget(GetWorld(), AnyColorWidgetClass));
	widget->SetInfo(cardInfo);
	widget->AddToViewport();
}

void UHUDDesk::PopUpSelectCard()
{
	CardWidget = Cast<UHUDSelectCard>(CreateWidget(GetWorld(), SelectCardWidgetClass));
	CardWidget->AddToViewport();
}

void UHUDDesk::PopUpRivalInfo()
{
	RivalInfoWidget = Cast<UHudRivalInfo>(CreateWidget(GetWorld(), RivalInfoClass));
	RivalInfoWidget->AddToViewport();
}

void UHUDDesk::PopUpEndPage(const FString& winnerName, bool bWin)
{
	auto Widget = Cast<UHUDEndGame>(CreateWidget(GetWorld(), EndGameClass));
	
	if (Widget)
	{
		Widget->AddToViewport();
	}
}
