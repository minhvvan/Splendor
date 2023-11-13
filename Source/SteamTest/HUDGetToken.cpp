// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDGetToken.h"
#include "TileData.h"
#include "Components/TileView.h"

void UHUDGetToken::SetTiles(TArray<FTokenIdxColor> tokens, const FCardInfo& cardInfo)
{
	check(IsValid(TileDataClass));

	TArray<bool> checked;
	checked.Init(false, 25);

	for (auto token : tokens)
	{
		checked[token.Idx] = true;
	}

	for (int i = 0; i < 25; i++)
	{
		if (!checked[i])
		{
			tokens.Add({ i, ETokenColor::E_End });
		}
	}

	tokens.Sort();
	for (auto token : tokens)
	{
		auto TileData = NewObject<UTileData>(this, TileDataClass);
		TileData->SetColor(token.Color);
		TileData->SetIdx(token.Idx);
		TileData->SetEnable(token.Color == cardInfo.color);

		if (token.Idx < 5)
		{
			TileRowOne->AddItem(TileData);
		}
		else if (token.Idx < 10)
		{
			TileRowTwo->AddItem(TileData);
		}
		else if (token.Idx < 15)
		{
			TileRowThree->AddItem(TileData);
		}
		else if (token.Idx < 20)
		{
			TileRowFour->AddItem(TileData);
		}
		else
		{
			TileRowFive->AddItem(TileData);
		}
	}
}
