// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDTokenHolder.h"
#include "Components/TextBlock.h"
#include "PCPlay.h"
#include "PSPlayerInfo.h"
#include "Token.h"
#include "GlobalEnum.h"

void UHUDTokenHolder::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UHUDTokenHolder::SetTokenNum(ETokenColor type, int score)
{
	switch (type)
	{
	case ETokenColor::E_Red:
		TxtTokenRed->SetText(FText::AsNumber(score));
		break;
	case ETokenColor::E_Green:
		TxtTokenGreen->SetText(FText::AsNumber(score));
		break;
	case ETokenColor::E_Blue:
		TxtTokenBlue->SetText(FText::AsNumber(score));
		break;
	case ETokenColor::E_White:
		TxtTokenWhite->SetText(FText::AsNumber(score));
		break;
	case ETokenColor::E_Black:
		TxtTokenBlack->SetText(FText::AsNumber(score));
		break;
	case ETokenColor::E_Gold:
		TxtTokenGold->SetText(FText::AsNumber(score));
		break;
	case ETokenColor::E_Pearl:
		TxtTokenPearl->SetText(FText::AsNumber(score));
		break;
	}
}

void UHUDTokenHolder::UpdateTokenNum(APSPlayerInfo* ps)
{
	if (PS == nullptr || !IsValid(PS))
	{
		PS = ps;
	}

	for (ETokenColor type : TEnumRange<ETokenColor>())
	{
		SetTokenNum(type, PS->GetTokenNum(type));
	}
}
