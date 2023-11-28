// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDColorItem.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/ListViewBase.h"
#include "HUDAnyColor.h"
#include "CostData.h"
#include "Blueprint/WidgetBlueprintLibrary.h"


void UHUDColorItem::NativeOnInitialized()
{
	BtnColor->OnClicked.AddDynamic(this, &UHUDColorItem::OnClicked);
}

void UHUDColorItem::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	auto Data = Cast<UCostData>(ListItemObject);
	if (Data)
	{
		Color = Data->GetColor();
		BtnColor->WidgetStyle.SetNormal(UWidgetBlueprintLibrary::MakeBrushFromTexture(TokenImg[Color]));
		BtnColor->WidgetStyle.Normal.TintColor = FSlateColor(FColor(200, 200, 200));

		BtnColor->WidgetStyle.SetHovered(UWidgetBlueprintLibrary::MakeBrushFromTexture(TokenImg[Color]));
		BtnColor->WidgetStyle.Hovered.TintColor = FSlateColor(FColor(255, 255, 255));

		BtnColor->WidgetStyle.SetPressed(UWidgetBlueprintLibrary::MakeBrushFromTexture(TokenImg[Color]));
		BtnColor->WidgetStyle.Pressed.TintColor = FSlateColor(FColor(127, 127, 127));

		BtnColor->WidgetStyle.SetDisabled(UWidgetBlueprintLibrary::MakeBrushFromTexture(TokenImg[Color]));
		BtnColor->WidgetStyle.Disabled.TintColor = FSlateColor(FColor(77, 77, 77));
	}
}

void UHUDColorItem::OnClicked()
{
	auto OwnList = GetOwningListView();
	auto Parent = OwnList->GetParent();
	auto Outer1 = Parent->GetOuter();
	auto Outer2 = Outer1->GetOuter();

	auto AnyColor = Cast<UHUDAnyColor>(Outer2);
	AnyColor->CallUpdate(Color);
}