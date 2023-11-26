// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDCost.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "PCPlay.h"
#include "CostData.h"
#include "GlobalEnum.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void UHUDCost::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	//BorderColor->OnMouseButtonDownEvent.BindUFunction(this, "OnClicked");

	BtnColor->OnClicked.AddDynamic(this, &UHUDCost::OnClicked);
}

void UHUDCost::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	auto Data = Cast<UCostData>(ListItemObject);

	CostData = Data;
	TxtCost->SetText(FText::AsNumber(CostData->GetNum()));

	BtnColor->WidgetStyle.SetNormal(UWidgetBlueprintLibrary::MakeBrushFromTexture(TokenImg[CostData->GetColor()]));
	BtnColor->WidgetStyle.Normal.TintColor = FSlateColor(FColor(230, 230, 230));

	BtnColor->WidgetStyle.SetHovered(UWidgetBlueprintLibrary::MakeBrushFromTexture(TokenImg[CostData->GetColor()]));
	BtnColor->WidgetStyle.Hovered.TintColor = FSlateColor(FColor(255, 255, 255));

	BtnColor->WidgetStyle.SetPressed(UWidgetBlueprintLibrary::MakeBrushFromTexture(TokenImg[CostData->GetColor()]));
	BtnColor->WidgetStyle.Pressed.TintColor = FSlateColor(FColor(127, 127, 127));

	BtnColor->WidgetStyle.SetDisabled(UWidgetBlueprintLibrary::MakeBrushFromTexture(TokenImg[CostData->GetColor()]));
	BtnColor->WidgetStyle.Disabled.TintColor = FSlateColor(FColor(77, 77, 77));
}


void UHUDCost::OnClicked()
{
	if (CostData)
	{
		auto color = CostData->GetColor();

		auto PC = Cast<APCPlay>(GetOwningPlayer());
		if (PC)
		{
			PC->TakeTokenFromOpp(color);
		}
	}
}