// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDCardHolder.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Engine/Texture2D.h"
#include "GlobalEnum.h"

void UHUDCardHolder::NativeOnInitialized()
{
	Super::NativeOnInitialized();

}

void UHUDCardHolder::SetScoreTxt(int score)
{
	TxtScore->SetText(FText::AsNumber(score));
}

void UHUDCardHolder::SetBonusTxt(int bonus)
{
	TxtBonus->SetText(FText::AsNumber(bonus));
}

void UHUDCardHolder::SetImage(ETokenColor color)
{
	auto tex = TokenTexture.Find(color);
	if (tex)
	{
		ImgToken->SetBrushFromTexture(*tex);
	}
}
