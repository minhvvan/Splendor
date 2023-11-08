// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDAnyColor.h"
#include "Components/Button.h"
#include "PCPlay.h"
#include "PSPlayerInfo.h"
#include "GlobalStruct.h"

void UHUDAnyColor::NativeOnInitialized()
{
	BtnRed->OnClicked.AddDynamic(this,   &UHUDAnyColor::RedClicked);
	BtnGreen->OnClicked.AddDynamic(this, &UHUDAnyColor::GreenClicked);
	BtnBlue->OnClicked.AddDynamic(this,  &UHUDAnyColor::BlueClicked);
	BtnWhite->OnClicked.AddDynamic(this, &UHUDAnyColor::WhiteClicked);
	BtnBlack->OnClicked.AddDynamic(this, &UHUDAnyColor::BlackClicked);
}

void UHUDAnyColor::RedClicked()
{
	CallUpdate(ETokenColor::E_Red);
	RemoveFromParent();
}

void UHUDAnyColor::GreenClicked()
{
	CallUpdate(ETokenColor::E_Green);
	RemoveFromParent();
}

void UHUDAnyColor::BlueClicked()
{
	CallUpdate(ETokenColor::E_Blue);
	RemoveFromParent();
}

void UHUDAnyColor::WhiteClicked()
{
	CallUpdate(ETokenColor::E_White);
	RemoveFromParent();
}

void UHUDAnyColor::BlackClicked()
{
	CallUpdate(ETokenColor::E_Black);
	RemoveFromParent();
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
}
