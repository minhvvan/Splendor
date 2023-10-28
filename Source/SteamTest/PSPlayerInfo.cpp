// Fill out your copyright notice in the Description page of Project Settings.


#include "PSPlayerInfo.h"
#include "Net/UnrealNetwork.h"
#include "UObject/CoreNet.h"
#include "Token.h"

APSPlayerInfo::APSPlayerInfo(): PName(""), MyTurn(false)
{
}

void APSPlayerInfo::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(APSPlayerInfo, PName);
	DOREPLIFETIME(APSPlayerInfo, MyTurn);
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


void APSPlayerInfo::CopyProperties(APlayerState* PlayerState)
{
	Super::CopyProperties(PlayerState);

	if (PlayerState)
	{
		APSPlayerInfo* NewPlayerState = Cast<APSPlayerInfo>(PlayerState);
		if (NewPlayerState)
		{
			NewPlayerState->PName = PName;
			NewPlayerState->MyTurn = MyTurn;
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
			MyTurn = OldPlayerState->MyTurn;
		}
	}
}