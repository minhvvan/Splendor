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
}

void UHUDDesk::SetTurnTxt(FString turn)
{
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
	switch (itemType)
	{
	case EItem::I_GetToken:
		check(GetWidget.IsValid());
		GetWidget->RemoveFromParent();
		GetWidget.Reset();
		break;
	case EItem::I_TakeToken:
		check(TakeWidget.IsValid());
		TakeWidget->RemoveFromParent();
		TakeWidget.Reset();
		break;
	}
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
		auto widget = Cast<UHUDSelectRoyal>(CreateWidget(GetWorld(), RoyalWidgetClass));
		if (widget)
		{
			auto PS = GetOwningPlayer()->GetPlayerState<APSPlayerInfo>();
			widget->SetScore(PS->GetScore());
			widget->SetCrown(PS->GetCrown());
			widget->SetScroll(PS->GetScroll());

			widget->SetRoyal();
			widget->AddToViewport();
		}
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

void UHUDDesk::GetTokenClicked()
{
	auto PC = Cast<APCPlay>(GetOwningPlayer());

	if (PC)
	{
		auto Tokens = PC->GetSelectedTokens();

		if (Tokens.Num() == 0)
		{
			if (FailedGetAnim)
			{
				PlayAnimation(FailedGetAnim);
				
				RenderMessage(UGlobalConst::MsgNotSelect);

				if (FailSound)
				{
					PlaySound(FailSound);
				}
			}

			return;
		}

		Tokens.Sort([](const AToken& A, const AToken& B) {
			return A.GetIndex() < B.GetIndex();
		});

		bool flag = true;

		int diff = -1;
		int prev = -1;
		for (auto token : Tokens)
		{
			if (prev == -1)
			{
				prev = token->GetIndex(); 
				continue;
			}

			if (diff == -1)
			{
				diff = token->GetIndex() - prev;
			}
			else
			{
				if (diff != token->GetIndex() - prev)
				{
					flag = false;
					break;
				}
			}

			prev = token->GetIndex();
		}
		
		if (flag)
		{
			auto PS = Cast<APSPlayerInfo>(PC->PlayerState);
			PC->SRPossessTokens(PS->GetBFirst());

			return;
		}
	}
}

void UHUDDesk::FilTokenClicked()
{
	Cast<APCPlay>(GetOwningPlayer())->SRFillToken();
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

void UHUDDesk::PopUpDetailCard(ACard* card)
{
	if (DetailCardClass)
	{
		auto widget = Cast<UHUDDetailCard>(CreateWidget(GetWorld(), DetailCardClass));
		if (widget)
		{
			auto info = card->GetInfo();
			widget->SetCardInfo(info);
			widget->AddToViewport();
		}
	}
}

void UHUDDesk::PopUpItemWidget(EItem itemType, const FCardInfo& cardInfo)
{
	switch (itemType)
	{
	case EItem::I_GetToken:
		{
			GetWidget = Cast<UHUDGetToken>(CreateWidget(GetWorld(), GetTokenWidgetClass));
			auto TileIdxs = GetWorld()->GetGameState<AGSPlay>()->GetRemainTokenIdx();
			GetWidget->SetTiles(TileIdxs, cardInfo);
			GetWidget->AddToViewport();
		}
		break;
	case EItem::I_TakeToken:
		{
			TakeWidget = Cast<UHUDTakeToken>(CreateWidget(GetWorld(), TakeTokenWidgetClass));
			auto TokenList = Cast<APCPlay>(GetOwningPlayer())->GetOppTokens();
			TakeWidget->SetTokens(TokenList);
			TakeWidget->AddToViewport();
		}
		break;
	case EItem::I_AnyColor:
		{
			auto widget = Cast<UHUDAnyColor>(CreateWidget(GetWorld(), AnyColorWidgetClass));
			widget->SetInfo(cardInfo);
			widget->AddToViewport();
		}
		break;
	}
}
