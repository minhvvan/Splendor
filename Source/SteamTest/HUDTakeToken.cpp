// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDTakeToken.h"
#include "GlobalStruct.h"
#include "Components/TileView.h"
#include "CostData.h"

void UHUDTakeToken::SetTokens(TArray<FTokenCount> tokens)
{
	if (TokenDataClass && IsValid(TokenDataClass))
	{
		for (auto cost : tokens)
		{
			if (cost.Value == 0 || cost.Key == ETokenColor::E_Gold) continue;
			auto CostData = NewObject<UCostData>(this, TokenDataClass);
			CostData->SetColor(cost.Key);
			CostData->SetNum(cost.Value);

			TileToken->AddItem(CostData);
		}
	}
}