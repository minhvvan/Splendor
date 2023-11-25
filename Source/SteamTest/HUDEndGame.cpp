// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDEndGame.h"
#include "Components/TileView.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "GSPlay.h"
#include "PSPlayerInfo.h"
#include "CostData.h"
#include "SteamTestGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"

void UHUDEndGame::NativeOnInitialized()
{
	BtnExit->OnClicked.AddDynamic(this, &UHUDEndGame::ExitGame);

	auto GS = GetWorld()->GetGameState<AGSPlay>();

	for (auto PS : GS->PlayerArray)
	{
		auto casted = Cast<APSPlayerInfo>(PS);

		if (casted->GetBFirst())
		{
			TxtFirstPName->SetText(FText::FromString(casted->GetPName()));
			TxtFirstCrown->SetText(FText::AsNumber(casted->GetCrown()));
			TxtFirstScroll->SetText(FText::AsNumber(casted->GetScroll()));
			TxtFirstScore->SetText(FText::AsNumber(casted->GetTotalScore()));
		}
		else
		{
			TxtSecondPName->SetText(FText::FromString(casted->GetPName()));
			TxtSecondCrown->SetText(FText::AsNumber(casted->GetCrown()));
			TxtSecondScroll->SetText(FText::AsNumber(casted->GetScroll()));
			TxtSecondScore->SetText(FText::AsNumber(casted->GetTotalScore()));
		}

		SetColorScore(casted);
		SetBonus(casted);
		SetToken(casted);
	}
}

void UHUDEndGame::SetColorScore(APSPlayerInfo* PS)
{
	UTileView* Current;

	if (PS->GetBFirst()) Current = TVFirstColorScore;
	else Current = TVSecondColorScore;

	for (auto color : TEnumRange<ETokenColor>())
	{
		auto score = PS->GetScoreByColor(color);
		if (score == 0) continue;

		auto CostData = NewObject<UCostData>(this, CostDataClass);
		CostData->SetColor(color);
		CostData->SetNum(score);

		Current->AddItem(CostData);
	}
}

void UHUDEndGame::SetBonus(APSPlayerInfo* PS)
{
	UTileView* Current;

	if (PS->GetBFirst()) Current = TVFirstBonus;
	else Current = TVSecondBonus;

	for (auto color : TEnumRange<ETokenColor>())
	{
		auto bonus = PS->GetBonusNum(color);
		if (bonus == 0) continue;

		auto CostData = NewObject<UCostData>(this, CostDataClass);
		CostData->SetColor(color);
		CostData->SetNum(bonus);

		Current->AddItem(CostData);
	}
}

void UHUDEndGame::SetToken(APSPlayerInfo* PS)
{
	UTileView* Current;

	if (PS->GetBFirst()) Current = TVFirstToken;
	else Current = TVSecondToken;

	for (auto cost : PS->GetOwnTokens())
	{
		if (cost.Value == 0) continue;

		auto CostData = NewObject<UCostData>(this, CostDataClass);
		CostData->SetColor(cost.Key);
		CostData->SetNum(cost.Value);

		Current->AddItem(CostData);
	}
}

void UHUDEndGame::ExitGame()
{
	//게임 끝: 로비로 이동
	//UKismetSystemLibrary::QuitGame(GetWorld(), GetOwningPlayer(), EQuitPreference::Quit, false);

	Cast<USteamTestGameInstance>(GetGameInstance())->LeaveSession();
	RemoveFromParent();
}
