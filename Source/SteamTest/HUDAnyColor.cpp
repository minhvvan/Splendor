// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDAnyColor.h"
#include "Components/Button.h"
#include "Components/TileView.h"
#include "PCPlay.h"
#include "PSPlayerInfo.h"
#include "GlobalStruct.h"
#include "CostData.h"


void UHUDAnyColor::NativeOnInitialized()
{
	//PS에서 Bonus 받아서 data create
	auto PS = GetOwningPlayer()->GetPlayerState<APSPlayerInfo>();

	if (PS)
	{
		for (auto color : TEnumRange<ETokenColor>())
		{
			if (PS->GetBonusNum(color) > 0)
			{
				auto Data = NewObject<UCostData>(this, DataClass);
				Data->SetColor(color);

				TVColor->AddItem(Data);
			}
		}
	}

}

void UHUDAnyColor::SetInfo(const FCardInfo& cardInfo)
{
	score = cardInfo.score;
}

void UHUDAnyColor::CallUpdate(ETokenColor color)
{
	auto PC = Cast<APCPlay>(GetOwningPlayer());
	if (PC)
	{
		PC->SRAddBonus(color);
		PC->SRAddScore(color, score);
	}

	RemoveFromParent();
}
