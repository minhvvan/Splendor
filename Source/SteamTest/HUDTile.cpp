// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDTile.h"
#include "Components/Button.h"
#include "PCPlay.h"
#include "TileData.h"
#include "GlobalEnum.h"
#include "Blueprint/WidgetBlueprintLibrary.h"


void UHUDTile::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	BtnToken->OnClicked.AddDynamic(this, &UHUDTile::OnClicked);
}

void UHUDTile::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	TileData = Cast<UTileData>(ListItemObject);

	if(!TileData) GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, FString::Printf(TEXT("No data")));

	auto Normal = UWidgetBlueprintLibrary::MakeBrushFromTexture(TokenImg[TileData->GetColor()]);

	BtnToken->WidgetStyle.SetNormal(UWidgetBlueprintLibrary::MakeBrushFromTexture(TokenImg[TileData->GetColor()]));
	BtnToken->WidgetStyle.Normal.TintColor = FSlateColor(FColor(200, 200, 200));

	BtnToken->WidgetStyle.SetHovered(UWidgetBlueprintLibrary::MakeBrushFromTexture(TokenImg[TileData->GetColor()]));
	BtnToken->WidgetStyle.Hovered.TintColor = FSlateColor(FColor(255, 255, 255));

	BtnToken->WidgetStyle.SetPressed(UWidgetBlueprintLibrary::MakeBrushFromTexture(TokenImg[TileData->GetColor()]));
	BtnToken->WidgetStyle.Pressed.TintColor = FSlateColor(FColor(127, 127, 127));

	BtnToken->WidgetStyle.SetDisabled(UWidgetBlueprintLibrary::MakeBrushFromTexture(TokenImg[TileData->GetColor()]));
	BtnToken->WidgetStyle.Disabled.TintColor = FSlateColor(FColor(77, 77, 77));

	if (!TileData->GetEnable()) BtnToken->SetIsEnabled(false);
}


void UHUDTile::OnClicked()
{
	check(TileData);

	auto idx = TileData->GetIdx();
	auto PC = Cast<APCPlay>(GetOwningPlayer());
	if (PC)
	{
		//PC¿¡°Ô È¹µæ ¿äÃ»
		PC->GetTokenByIdx(idx);
	}
}