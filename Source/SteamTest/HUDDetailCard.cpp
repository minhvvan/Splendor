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

	UseTokens.Init();

	BtnBuy->OnClicked.AddDynamic(this, &UHUDDetailCard::BuyClicked);
	BtnBuy->OnHovered.AddDynamic(this, &UHUDDetailCard::BuyHovered);
	BtnBuy->OnUnhovered.AddDynamic(this, &UHUDDetailCard::BuyLeaved);

	BtnBack->OnHovered.AddDynamic(this, &UHUDDetailCard::BackHovered);
	BtnBack->OnUnhovered.AddDynamic(this, &UHUDDetailCard::BackLeaved);
	BtnBack->OnClicked.AddDynamic(this, &UHUDDetailCard::BackClicked);
}

void UHUDDetailCard::SetCardInfo(const FCardInfo& info_)
{
	Info = info_;

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

		auto PS = GetOwningPlayer()->GetPlayerState<APSPlayerInfo>();
		if (PS)
		{
			auto& costs = Info.cost;
			for (auto& cost : costs)
			{
				int ownBonus = PS->GetBonusNum(cost.Key);
				cost.Value -= ownBonus;
			}
		}
		
		CardInfo->SetInfo(Info);
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

	auto PC = Cast<APCPlay>(GetOwningPlayer());
	if (PC)
	{
		PC->SRBuyCard(Info, UseTokens);
	}

	GetOwningPlayer()->SetInputMode(FInputModeGameAndUI());
	RemoveFromParent();
}

void UHUDDetailCard::BackClicked()
{
	GetOwningPlayer()->SetInputMode(FInputModeGameAndUI());
	RemoveFromParent();
}

void UHUDDetailCard::BackHovered()
{
	if (HoverBacKBtnAnim)
	{
		PlayAnimation(HoverBacKBtnAnim);
	}
}

void UHUDDetailCard::BackLeaved()
{
	if (HoverBacKBtnAnim)
	{
		PlayAnimationReverse(HoverBacKBtnAnim);
	}
}

void UHUDDetailCard::BuyHovered()
{
	if (HoverBuyBtnAnim)
	{
		PlayAnimation(HoverBuyBtnAnim);
	}
}

void UHUDDetailCard::BuyLeaved()
{
	if (HoverBuyBtnAnim)
	{
		PlayAnimationReverse(HoverBuyBtnAnim);
	}
}

bool UHUDDetailCard::CheckCanBuy()
{
	auto PS = GetOwningPlayer()->GetPlayerState<APSPlayerInfo>();
	if (PS)
	{
		bool flag = true;
		auto costs = Info.cost;

		//AnyColor Check
		auto item = Info.item;
		if (item.Find(EItem::I_AnyColor) != INDEX_NONE)
		{
			int totalBonus = 0;

			for (auto color : TEnumRange<ETokenColor>())
			{
				totalBonus += PS->GetBonusNum(color);
			}

			if (totalBonus == 0) flag = false;
		}

		//Cost Check
		FTokenCountList OwnTokens;
		OwnTokens.Init();

		OwnTokens[ETokenColor::E_Red] = PS->GetTokenNum(ETokenColor::E_Red);
		OwnTokens[ETokenColor::E_Green] = PS->GetTokenNum(ETokenColor::E_Green);
		OwnTokens[ETokenColor::E_Blue] = PS->GetTokenNum(ETokenColor::E_Blue);
		OwnTokens[ETokenColor::E_White] = PS->GetTokenNum(ETokenColor::E_White);
		OwnTokens[ETokenColor::E_Black] = PS->GetTokenNum(ETokenColor::E_Black);
		OwnTokens[ETokenColor::E_Gold] = PS->GetTokenNum(ETokenColor::E_Gold);
		OwnTokens[ETokenColor::E_Pearl] = PS->GetTokenNum(ETokenColor::E_Pearl);

		for (auto cost : costs)
		{
			int ownToken = OwnTokens[cost.Key];
			int ownBonus = PS->GetBonusNum(cost.Key);

			int diff = cost.Value - (ownToken + ownBonus);
			if (diff > 0)
			{
				//gold »ç¿ë
				if (OwnTokens[ETokenColor::E_Gold] >= diff)
				{
					OwnTokens[ETokenColor::E_Gold] -= diff;
					UseTokens[ETokenColor::E_Gold] += diff;
					continue;
				}

				flag = false;
				break;
			}
			else
			{
				UseTokens[cost.Key] += (cost.Value - ownBonus);
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