// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDDetailCard.h"
#include "GlobalStruct.h"
#include "HUDCard.h"
#include "PCPlay.h"
#include "PSPlayerInfo.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "GlobalEnum.h"
#include "GlobalConst.h"

void UHUDDetailCard::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	BtnBuy->OnClicked.AddDynamic(this, &UHUDDetailCard::BuyClicked);
	BtnBack->OnClicked.AddDynamic(this, &UHUDDetailCard::BackClicked);
}

void UHUDDetailCard::SetCardInfo(FCardInfo& info)
{
	Info = info;

	if (IsValid(CardInfo))
	{
		auto PC = Cast<APCPlay>(GetOwningPlayer());
		if (IsValid(PC))
		{
			auto PS = PC->GetPlayerState<APSPlayerInfo>();
			if (IsValid(PS))
			{
				int red =	PS->GetTokenNum(ETokenColor::E_Red);
				int green = PS->GetTokenNum(ETokenColor::E_Green);
				int blue =	PS->GetTokenNum(ETokenColor::E_Blue);
				int white = PS->GetTokenNum(ETokenColor::E_White);
				int black = PS->GetTokenNum(ETokenColor::E_Black);
				int gold =	PS->GetTokenNum(ETokenColor::E_Gold);
				int pearl = PS->GetTokenNum(ETokenColor::E_Pearl);

				TxtOwnRed->SetText(FText::AsNumber(red));
				TxtOwnGreen->SetText(FText::AsNumber(green));
				TxtOwnBlue->SetText(FText::AsNumber(blue));
				TxtOwnWhite->SetText(FText::AsNumber(white));
				TxtOwnBlack->SetText(FText::AsNumber(black));
				TxtOwnGold->SetText(FText::AsNumber(gold));
				TxtOwnPearl->SetText(FText::AsNumber(pearl));
			}
		}

		//!TODO: info 조정(전체에서 bonus 빼기)
		auto PS = GetOwningPlayer()->GetPlayerState<APSPlayerInfo>();
		if (PS)
		{
			auto costs = Info.cost;
			for (auto& cost : costs)
			{
				int ownBonus = PS->GetBonusNum(cost.Key);
				cost.Value -= ownBonus;
			}
		}
		
		CardInfo->SetInfo(info);
	}
}

void UHUDDetailCard::BuyClicked()
{
	if (!CheckCanBuy() && FailedBuy)
	{
		PlayAnimation(FailedBuy);
		RenderMessage(UGlobalConst::MsgUnableBuy);
		return;
	}

	//구매성공
	//token 사용 & bonus, score, crown update
	//item 사용
	//try1: 여기서 직접 업데이트
	auto PS = GetOwningPlayer()->GetPlayerState<APSPlayerInfo>();
	if (PS)
	{
		PS->AddBonus(Info.color);
		PS->AddScore(Info.color, Info.score);
		PS->AddCrown(Info.crown);
	}

	RemoveFromParent();
}

void UHUDDetailCard::BackClicked()
{
	RemoveFromParent();
}

bool UHUDDetailCard::CheckCanBuy()
{
	auto PS = GetOwningPlayer()->GetPlayerState<APSPlayerInfo>();
	if (PS)
	{
		bool flag = true;
		auto costs = Info.cost;
		for (auto cost : costs)
		{
			int ownToken = PS->GetTokenNum(cost.Key);
			int ownBonus = PS->GetBonusNum(cost.Key);

			if (cost.Value > ownToken + ownBonus)
			{
				flag = false;
				break;
			}
		}

		return flag;
	}

	return false;
}


void UHUDDetailCard::RenderMessage(FString message)
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