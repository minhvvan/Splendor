// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDGetToken.h"
#include "TileData.h"
#include "Components/TileView.h"

void UHUDGetToken::SetTiles(const TArray<ETokenColor>& tokens, const TArray<ETokenColor>& colors)
{
	check(IsValid(TileDataClass));

	for (int i = 0 ; i < 25; i ++)
	{
		auto TileData = NewObject<UTileData>(this, TileDataClass);
		TileData->SetColor(tokens[i]);
		TileData->SetIdx(i);
		TileData->SetEnable(colors.Find(tokens[i]) != INDEX_NONE);

		if (i < 5)
		{
			TileRowOne->AddItem(TileData);
		}
		else if (i < 10)
		{
			TileRowTwo->AddItem(TileData);
		}
		else if (i < 15)
		{
			TileRowThree->AddItem(TileData);
		}
		else if (i < 20)
		{
			TileRowFour->AddItem(TileData);
		}
		else
		{
			TileRowFive->AddItem(TileData);
		}
	}
}
