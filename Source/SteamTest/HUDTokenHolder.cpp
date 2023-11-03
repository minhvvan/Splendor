// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDTokenHolder.h"
#include "Components/TextBlock.h"
#include "PCPlay.h"
#include "PSPlayerInfo.h"
#include "Token.h"

void UHUDTokenHolder::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	//auto player = GetOwningPlayer<APCPlay>();
	//if (player)
	//{
	//	PS = player->GetPlayerState<APSPlayerInfo>();
	//	if (PS)
	//	{
	//		SetTokenNum(ETokenType::T_Red, PS->GetTokenRed());
	//		SetTokenNum(ETokenType::T_Red, PS->GetTokenGreen());
	//		SetTokenNum(ETokenType::T_Red, PS->GetTokenBlue());
	//		SetTokenNum(ETokenType::T_Red, PS->GetTokenWhite());
	//		SetTokenNum(ETokenType::T_Red, PS->GetTokenBlack());
	//		SetTokenNum(ETokenType::T_Red, PS->GetTokenGold());
	//		SetTokenNum(ETokenType::T_Red, PS->GetTokenPearl());
	//	}
	//}
}

void UHUDTokenHolder::SetTokenNum(ETokenType type, int score)
{
	switch (type)
	{
	case ETokenType::T_Red:
		TxtTokenRed->SetText(FText::AsNumber(score));
		break;
	case ETokenType::T_Green:
		TxtTokenGreen->SetText(FText::AsNumber(score));
		break;
	case ETokenType::T_Blue:
		TxtTokenBlue->SetText(FText::AsNumber(score));
		break;
	case ETokenType::T_White:
		TxtTokenWhite->SetText(FText::AsNumber(score));
		break;
	case ETokenType::T_Black:
		TxtTokenBlack->SetText(FText::AsNumber(score));
		break;
	case ETokenType::T_Gold:
		TxtTokenGold->SetText(FText::AsNumber(score));
		break;
	case ETokenType::T_Pearl:
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

	for (ETokenType type : TEnumRange<ETokenType>())
	{
		SetTokenNum(type, PS->GetTokenNum(type));
	}
}
