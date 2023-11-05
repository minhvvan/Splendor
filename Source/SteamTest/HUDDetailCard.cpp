// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDDetailCard.h"
#include "GlobalStruct.h"
#include "HUDCard.h"
#include "PCPlay.h"
#include "PSPlayerInfo.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "GlobalEnum.h"

void UHUDDetailCard::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UHUDDetailCard::SetCardInfo(FCardInfo& info)
{
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
		CardInfo->SetInfo(info);
	}
}
