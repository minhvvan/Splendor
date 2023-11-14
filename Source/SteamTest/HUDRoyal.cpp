// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDRoyal.h"
#include "Components/Border.h"
#include "Components/TileView.h"
#include "Components/TextBlock.h"
#include "GlobalConst.h"
#include "GlobalEnum.h"
#include "PCPlay.h"
#include "ItemData.h"

void UHUDRoyal::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	BorderFrame->OnMouseButtonDownEvent.BindUFunction(this, "OnClicked");
}

void UHUDRoyal::SetScore(int score)
{
	Score = score;
	TxtScore->SetText(FText::AsNumber(score));
}

void UHUDRoyal::SetItem(EItem item)
{
	if (item == EItem::E_End)
	{
		TileItem->SetVisibility(ESlateVisibility::Hidden);
		return;
	}

	Item = item;

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

void UHUDRoyal::OnClicked(const FGeometry& Geometry, const FPointerEvent& MouseEvent)
{
	auto PC = Cast<APCPlay>(GetOwningPlayer());
	check(IsValid(PC));

	//점수 추가
	PC->SRAddScore(ETokenColor::E_End, Score);

	//아이템 사용
	switch (Item)
	{
	case EItem::I_GetScroll:
		PC->SRAddScroll();
		PC->CloseCrownWidget(false);
		return;
		break;
	case EItem::I_TakeToken:
		PC->UseItemTakeToken();
		break;
	}

	PC->CloseCrownWidget(true);
}