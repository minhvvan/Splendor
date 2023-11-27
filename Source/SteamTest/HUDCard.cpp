// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDCard.h"
#include "HUDCost.h"
#include "HUDItem.h"
#include "Components/Border.h"
#include "Components/TileView.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "CardManager.h"
#include "CostData.h"
#include "CardData.h"
#include "ItemData.h"
#include "GlobalConst.h"
#include "GlobalEnum.h"
#include "PCPlay.h"
#include "Engine/Texture2D.h"


void UHUDCard::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

FReply UHUDCard::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Cast<APCPlay>(GetOwningPlayer())->GetCardToHand(Info);

	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	return OnMouseButtonDown(InGeometry, InMouseEvent).NativeReply;
}

void UHUDCard::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{

	if (HoverSound) PlaySound(HoverSound);
	if (HoverCardAnim) PlayAnimation(HoverCardAnim);

	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
}

void UHUDCard::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	if (HoverCardAnim) PlayAnimationReverse(HoverCardAnim);

	Super::NativeOnMouseLeave(InMouseEvent);
}

void UHUDCard::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	auto Data = Cast<UCardData>(ListItemObject);

	if (Data)
	{
		Info = Data->GetData();
		SetInfo(Info);
	}
}


void UHUDCard::SetInfo(FCardInfo info)
{
	Info = info;

	auto color = info.color;
	auto bonus = info.bonus;
	auto score = info.score;
	auto crown = info.crown;
	auto costs = info.cost;
	auto item = info.item;

	//!--------Set--------

	SetCrown(crown);
	SetBonus(color, bonus);
	SetCost(costs);
	SetScore(score);
	SetItem(item);
}

void UHUDCard::SetBonus(ETokenColor color, int bonus)
{
	if (bonus == 0)
	{
		ImgToken->SetVisibility(ESlateVisibility::Hidden);
		TxtBonus->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		ImgToken->SetVisibility(ESlateVisibility::Visible);
		TxtBonus->SetVisibility(ESlateVisibility::Visible);
		TxtBonus->SetText(FText::AsNumber(bonus));

		switch (color)
		{
		case ETokenColor::E_Red:
			BorderColor->SetBrushColor(FLinearColor(UGlobalConst::RedColor));
			BorderFlag->SetBrushColor(FLinearColor(UGlobalConst::StrongRedColor));
			BorderFrame->SetBrushColor(FLinearColor(UGlobalConst::RedColor));
			break;
		case ETokenColor::E_Green:
			BorderColor->SetBrushColor(FLinearColor(UGlobalConst::GreenColor));
			BorderFlag->SetBrushColor(FLinearColor(UGlobalConst::StrongGreenColor));
			BorderFrame->SetBrushColor(FLinearColor(UGlobalConst::GreenColor));
			break;
		case ETokenColor::E_Blue:
			BorderColor->SetBrushColor(FLinearColor(UGlobalConst::BlueColor));
			BorderFlag->SetBrushColor(FLinearColor(UGlobalConst::StrongBlueColor));
			BorderFrame->SetBrushColor(FLinearColor(UGlobalConst::BlueColor));
			break;
		case ETokenColor::E_White:
			BorderColor->SetBrushColor(FLinearColor(UGlobalConst::WhiteColor));
			BorderFlag->SetBrushColor(FLinearColor(UGlobalConst::StrongWhiteColor));
			BorderFrame->SetBrushColor(FLinearColor(UGlobalConst::WhiteColor));
			break;
		case ETokenColor::E_Black:
			BorderColor->SetBrushColor(FLinearColor(UGlobalConst::BlackColor));
			BorderFlag->SetBrushColor(FLinearColor(UGlobalConst::StrongBlackColor));
			BorderFrame->SetBrushColor(FLinearColor(UGlobalConst::BlackColor));
			break;
		case ETokenColor::E_End:
			BorderColor->SetBrushColor(FLinearColor(UGlobalConst::WhiteColor));
			BorderFlag->SetBrushColor(FLinearColor(UGlobalConst::StrongWhiteColor));
			BorderFrame->SetBrushColor(FLinearColor(UGlobalConst::WhiteColor));
		}

		auto tex = TokenTexture.Find(color);
		if (tex)
		{
			ImgToken->SetBrushFromTexture(*tex);
		}
	}
}

void UHUDCard::SetCost(TArray<FTokenCount> costs)
{
	if (CostDataClass && IsValid(CostDataClass))
	{
		for (auto cost : costs)
		{
			auto CostData = NewObject<UCostData>(this, CostDataClass);
			CostData->SetColor(cost.Key);
			CostData->SetNum(cost.Value);

			TileCost->AddItem(CostData);
		}
	}
}

void UHUDCard::SetCrown(int crown)
{
	if (crown == 0)
	{
		ImgCrown->SetVisibility(ESlateVisibility::Hidden);
		TxtCrown->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		ImgCrown->SetVisibility(ESlateVisibility::Visible);
		TxtCrown->SetVisibility(ESlateVisibility::Visible);
		TxtCrown->SetText(FText::AsNumber(crown));
	}
}

void UHUDCard::SetScore(int score)
{
	if (score == 0)
	{
		TxtScore->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		TxtScore->SetText(FText::AsNumber(score));
		TxtScore->SetVisibility(ESlateVisibility::Visible);
	}
}

void UHUDCard::SetItem(TArray<EItem> items)
{
	check(IsValid(ItemDataClass));

	for (auto item : items)
	{
		auto ItemData = NewObject<UItemData>(this, ItemDataClass);
		ItemData->SetItem(item);

		TileItem->AddItem(ItemData);
	}
}