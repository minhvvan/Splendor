// Fill out your copyright notice in the Description page of Project Settings.


#include "HudRivalInfo.h"
#include "Components/TileView.h"
#include "Components/TextBlock.h"
#include "PSPlayerInfo.h"
#include "GSPlay.h"
#include "CostData.h"


void UHudRivalInfo::NativeOnInitialized()
{
	auto GS = GetWorld()->GetGameState<AGSPlay>();
	auto PlayerName = GetOwningPlayer()->GetPlayerState<APSPlayerInfo>()->GetPName();

	for (auto PS : GS->PlayerArray)
	{
		auto castedPS = Cast<APSPlayerInfo>(PS);
		if (!PlayerName.Equals(castedPS->GetPName()))
		{
			SetScore(castedPS->GetTotalScore());
			SetScroll(castedPS->GetScroll());
			SetCrown(castedPS->GetCrown());

			for (auto color : TEnumRange<ETokenColor>())
			{
				int score = castedPS->GetScoreByColor(color);
				if (score != 0) AddScroeList(color, score);

				int bonus = castedPS->GetBonusNum(color);
				if (bonus != 0) AddBonusList(color, bonus);

				int token = castedPS->GetTokenNum(color);
				if (token != 0) AddTokenLst(color, token);
			}

			break;
		}
	}
}

void UHudRivalInfo::SetScore(int score)
{
	TxtScore->SetText(FText::AsNumber(score));
}

void UHudRivalInfo::SetScroll(int scroll)
{
	TxtScroll->SetText(FText::AsNumber(scroll));
}

void UHudRivalInfo::SetCrown(int crown)
{
	TxtCrown->SetText(FText::AsNumber(crown));
}

void UHudRivalInfo::AddScroeList(ETokenColor color, int cnt)
{
	auto ScoreData = NewObject<UCostData>(this, ColorDataClass);
	ScoreData->SetColor(color);
	ScoreData->SetNum(cnt);

	TVScore->AddItem(ScoreData);
}

void UHudRivalInfo::AddBonusList(ETokenColor color, int cnt)
{
	auto ScoreData = NewObject<UCostData>(this, ColorDataClass);
	ScoreData->SetColor(color);
	ScoreData->SetNum(cnt);

	TVBonus->AddItem(ScoreData);
}

void UHudRivalInfo::AddTokenList(ETokenColor color, int cnt)
{
	auto ScoreData = NewObject<UCostData>(this, ColorDataClass);
	ScoreData->SetColor(color);
	ScoreData->SetNum(cnt);

	TVToken->AddItem(ScoreData);
}

