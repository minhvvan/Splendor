// Fill out your copyright notice in the Description page of Project Settings.


#include "PSPlayerInfo.h"
#include "Net/UnrealNetwork.h"
#include "UObject/CoreNet.h"
#include "Token.h"
#include "PCPlay.h"

APSPlayerInfo::APSPlayerInfo(): PName(""), bFirst(false)
{
}

void APSPlayerInfo::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(APSPlayerInfo, PName);
	DOREPLIFETIME(APSPlayerInfo, bFirst);

	DOREPLIFETIME(APSPlayerInfo, TokenNumRed);
	DOREPLIFETIME(APSPlayerInfo, TokenNumGreen);
	DOREPLIFETIME(APSPlayerInfo, TokenNumBlue);
	DOREPLIFETIME(APSPlayerInfo, TokenNumWhite);
	DOREPLIFETIME(APSPlayerInfo, TokenNumBlack);
	DOREPLIFETIME(APSPlayerInfo, TokenNumGold);
	DOREPLIFETIME(APSPlayerInfo, TokenNumPearl);

	DOREPLIFETIME(APSPlayerInfo, ScrollNum);
}

void APSPlayerInfo::AddToken(ETokenType type)
{
	switch (type)
	{
	case ETokenType::T_Red:
		TokenNumRed++;
		break;

	case ETokenType::T_Green:
		TokenNumGreen++;
		break;

	case ETokenType::T_Blue:
		TokenNumBlue++;
		break;

	case ETokenType::T_White:
		TokenNumWhite++;
		break;

	case ETokenType::T_Black:
		TokenNumBlack++;
		break;

	case ETokenType::T_Gold:
		TokenNumGold++;
		break;

	case ETokenType::T_Pearl:
		TokenNumPearl++;
		break;
	}
}


void APSPlayerInfo::SetToken(ETokenType type, int num)
{
	switch (type)
	{
	case ETokenType::T_Red:
		TokenNumRed = num;
		break;

	case ETokenType::T_Green:
		TokenNumGreen = num;
		break;

	case ETokenType::T_Blue:
		TokenNumBlue = num;
		break;

	case ETokenType::T_White:
		TokenNumWhite = num;
		break;

	case ETokenType::T_Black:
		TokenNumBlack = num;
		break;

	case ETokenType::T_Gold:
		TokenNumGold = num;
		break;

	case ETokenType::T_Pearl:
		TokenNumPearl = num;
		break;
	}
}

void APSPlayerInfo::AddScroll(int num)
{
	ScrollNum += num;
	OnScrollChanged.Broadcast();
}

void APSPlayerInfo::OnRep_Scroll()
{
	//~왜 서버쪽 PS변경시 클라에서 동작?
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, FString::Printf(TEXT("scroll: %d"), ScrollNum));
	OnScrollChanged.Broadcast();
}

void APSPlayerInfo::CopyProperties(APlayerState* PlayerState)
{
	Super::CopyProperties(PlayerState);

	if (PlayerState)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, FString::Printf(TEXT("CopyProperties")));

		APSPlayerInfo* NewPlayerState = Cast<APSPlayerInfo>(PlayerState);
		if (NewPlayerState)
		{
			NewPlayerState->PName = PName;
			NewPlayerState->bFirst = bFirst;
		}
	}
}

void APSPlayerInfo::OverrideWith(APlayerState* PlayerState)
{
	Super::OverrideWith(PlayerState);
	if (PlayerState)
	{
		APSPlayerInfo* OldPlayerState = Cast<APSPlayerInfo>(PlayerState);
		if (OldPlayerState)
		{
			PName = OldPlayerState->PName;
			bFirst = OldPlayerState->bFirst;
		}
	}
}

void APSPlayerInfo::ClientInitialize(AController* C)
{
	Super::ClientInitialize(C);

	Cast<APCPlay>(GetOwningController())->BindState();
}
