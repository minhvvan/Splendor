// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDCardHolder.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Engine/Texture2D.h"

void UHUDCardHolder::NativeOnInitialized()
{
	//~error
	//SetImage();
}

void UHUDCardHolder::SetScoreTxt(int score)
{
}

void UHUDCardHolder::SetBonusTxt(int bonus)
{
}

void UHUDCardHolder::SetImage()
{
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("SetImage")));


	//if (IsValid(IconImg))
	//{
	//	ImgToken->SetBrushFromTexture(IconImg);
	//}
}
