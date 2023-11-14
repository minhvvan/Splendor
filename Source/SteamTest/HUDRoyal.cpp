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
	Item = item;
	
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
		BorderFrame->SetIsEnabled(true);
		return;
	}

	//!TODO : player name으로 가져오면 best
	TxtOwner->SetVisibility(ESlateVisibility::Visible);
	if (owner == UGlobalConst::FirstPlayer)
	{
		TxtOwner->SetText(FText::FromString("P1"));
	}
	else
	{
		TxtOwner->SetText(FText::FromString("P2"));
	}

	BorderFrame->SetIsEnabled(false);
}

void UHUDRoyal::OnClicked(const FGeometry& Geometry, const FPointerEvent& MouseEvent)
{
	auto PC = Cast<APCPlay>(GetOwningPlayer());
	check(IsValid(PC));

	//점수 추가
	PC->SRAddScore(ETokenColor::E_End, Score);

	//소유 설정
	PC->SRPossessRoyal(Key);

	switch (Item)
	{
	case EItem::I_RePlay:
		PC->CloseCrownWidget(true);
		break;
	case EItem::I_GetScroll:
		PC->SRAddScroll();
		PC->CloseCrownWidget(false);
		break;
	case EItem::I_TakeToken:
		PC->UseItemTakeToken();
		PC->CloseCrownWidget(true);
		break;
	case EItem::E_End:
		PC->CloseCrownWidget(false);
		break;
	}
}