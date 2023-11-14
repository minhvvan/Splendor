// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDRoyal.h"
#include "Components/TileView.h"
#include "Components/TextBlock.h"
#include "GlobalConst.h"
#include "ItemData.h"

void UHUDRoyal::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UHUDRoyal::SetScore(int score)
{
	TxtScore->SetText(FText::AsNumber(score));
}

void UHUDRoyal::SetItem(EItem item)
{
	if (item == EItem::E_End)
	{
		TileItem->SetVisibility(ESlateVisibility::Hidden);
		return;
	}

	check(IsValid(ItemDataClass));

	auto ItemData = NewObject<UItemData>(this, ItemDataClass);
	ItemData->SetItem(item);

	TileItem->AddItem(ItemData);
}


void UHUDRoyal::SetOwner(int owner)
{
	if (owner == 0)
	{
		TxtOwner->SetVisibility(ESlateVisibility::Hidden);
		return;
	}

	//!TODO : player name으로 가져오면 best
	if (owner == UGlobalConst::FirstPlayer)
	{
		TxtOwner->SetText(FText::FromString("P1"));
	}
	else
	{
		TxtOwner->SetText(FText::FromString("P2"));
	}
}

