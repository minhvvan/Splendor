// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDDesk.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "HUDCardHolder.h"
#include "PCPlay.h"
#include "Kismet/GameplayStatics.h"

void UHUDDesk::NativeOnInitialized()
{
	BtnGetToken->OnClicked.AddDynamic(this, &UHUDDesk::GetTokenClicked);
	BtnFillToken->OnClicked.AddDynamic(this, &UHUDDesk::FilTokenClicked);
}

void UHUDDesk::SetScoreTxt(int score)
{
}

void UHUDDesk::SetCrownTxt(int crown)
{
}

void UHUDDesk::SetScrollTxt(int scroll)
{
}

void UHUDDesk::SetTurnTxt(FString turn)
{
}

void UHUDDesk::SetBtnGetTokenState(bool bEnable)
{
	if (bEnable)
	{
		BtnGetToken->SetIsEnabled(true);
	}
	else
	{
		BtnGetToken->SetIsEnabled(false);
	}
}

void UHUDDesk::GetTokenClicked()
{
	auto PC = Cast<APCPlay>(GetOwningPlayer());

	if (PC)
	{
		// token 받아와서 가능 여부 판단
		// 가능하면 받아오기
	}
}

void UHUDDesk::FilTokenClicked()
{
}
