// Fill out your copyright notice in the Description page of Project Settings.


#include "GSPlay.h"
#include "Net/UnrealNetwork.h"
#include "UObject/CoreNet.h"
#include "Algo/RandomShuffle.h"
#include "PSPlayerInfo.h"
#include "PCPlay.h"

void AGSPlay::InitState()
{
	GlobalScroll = 3;
	Pouch.Init();

	check(IsValid(RoyalData));
	{
		auto Names = RoyalData->GetRowNames();
		FString ContextString;
		for (auto name : Names)
		{
			auto data = RoyalData->FindRow<FRoyalInfo>(name, ContextString);
			Royals.Add(*data);
		}
	}

	check(IsValid(CardData));
	{
		auto Names = CardData->GetRowNames();
		FString ContextString;
		for (auto name : Names)
		{
			auto data = CardData->FindRow<FCardInfo>(name, ContextString);
			switch (data->tier)
			{
			case ECardTier::C_One:
				TierOneInfos.Add(*data);
				break;
			case ECardTier::C_Two:
				TierTwoInfos.Add(*data);
				break;
			case ECardTier::C_Three:
				TierThreeInfos.Add(*data);
				break;
			}
		}

		Algo::RandomShuffle(TierOneInfos);
		Algo::RandomShuffle(TierTwoInfos);
		Algo::RandomShuffle(TierThreeInfos);
	}

	//!------------Tile State Init-----------
	for (auto color : TEnumRange<ETokenColor>())
	{
		if (color == ETokenColor::E_End) break;

		int count = 4;
		if (color == ETokenColor::E_Pearl) count = 2;
		if (color == ETokenColor::E_Gold) count = 3;

		for (int i = 0; i < count; i++)
		{
			TileState.Add(color);
		}
	}

	Algo::RandomShuffle(TileState);

	//!------------Tile Idx Init-----------
	{
		FillIdx.Add(12);
		FillIdx.Add(17);
		FillIdx.Add(16);
		FillIdx.Add(11);
		FillIdx.Add(6);
		FillIdx.Add(7);
		FillIdx.Add(8);
		FillIdx.Add(13);
		FillIdx.Add(18);
		FillIdx.Add(23);
		FillIdx.Add(22);
		FillIdx.Add(21);
		FillIdx.Add(20);
		FillIdx.Add(15);
		FillIdx.Add(10);
		FillIdx.Add(5);
		FillIdx.Add(0);
		FillIdx.Add(1);
		FillIdx.Add(2);
		FillIdx.Add(3);
		FillIdx.Add(4);
		FillIdx.Add(9);
		FillIdx.Add(14);
		FillIdx.Add(19);
		FillIdx.Add(24);
	}
}

void AGSPlay::RemoveTokenIdx(int idx)
{
	TileState[idx] = ETokenColor::E_End;
}

int AGSPlay::AddToken(ETokenColor color)
{
	int result = -1;
	for (int i = 0; i < FillIdx.Num(); i++)
	{
		if (TileState[FillIdx[i]] == ETokenColor::E_End)
		{
			TileState[FillIdx[i]] = color;
			result = FillIdx[i];
			break;
		}
	}

	return result;
}

void AGSPlay::AddPouch(ETokenColor color, int cnt)
{
	Pouch[color] += cnt;
}

void AGSPlay::ClearPouch()
{
	Pouch.Clear();
}

void AGSPlay::UpdateRoyalOwner(int key, bool bFirst)
{
	for (auto& royal : Royals)
	{
		if (royal.Key == key)
		{
			royal.Owner = bFirst ? UGlobalConst::FirstPlayer : UGlobalConst::SecondPlayer;
			break;
		}
	}
}

int AGSPlay::GetInfoNumByTier(ECardTier tier)
{
	int num = 0;

	switch (tier)
	{
	case ECardTier::C_One:
		num = TierOneInfos.Num();
		break;
	case ECardTier::C_Two:
		num = TierTwoInfos.Num();
		break;
	case ECardTier::C_Three:
		num= TierThreeInfos.Num();
		break;
	}

	return num;
}

FCardInfo AGSPlay::GetInfoByTier(ECardTier tier)
{
	FCardInfo card;

	switch (tier)
	{
	case ECardTier::C_One:
		if (TierOneInfos.Num() > 0)
		{
			card = TierOneInfos.Pop();
			TierOneCurrentInfos.Add(card);
		}
		break;
	case ECardTier::C_Two:
		if (TierTwoInfos.Num() > 0)
		{
			card = TierTwoInfos.Pop();
			TierTwoCurrentInfos.Add(card);
		}
		break;
	case ECardTier::C_Three:
		if (TierThreeInfos.Num() > 0)
		{
			card = TierThreeInfos.Pop();
			TierThreeCurrentInfos.Add(card);
		}
		break;
	}

	return card;
}

void AGSPlay::RemoveCurrentCardInfo(FCardInfo info)
{
	switch (info.tier)
	{
	case ECardTier::C_One:
		TierOneCurrentInfos.Remove(info);
		break;
	case ECardTier::C_Two:
		TierTwoCurrentInfos.Remove(info);
		break;
	case ECardTier::C_Three:
		TierThreeCurrentInfos.Remove(info);
		break;
	}
}

const TArray<FCardInfo>& AGSPlay::GetCurrentInfoByTier(ECardTier tier)
{
	if (tier == ECardTier::C_One)
	{
		return TierOneCurrentInfos;
	}

	if (tier == ECardTier::C_Two)
	{
		return TierTwoCurrentInfos;
	}

	return TierThreeCurrentInfos;
}

void AGSPlay::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AGSPlay, Pouch);
	DOREPLIFETIME(AGSPlay, Royals);
	DOREPLIFETIME(AGSPlay, TierOneInfos);
	DOREPLIFETIME(AGSPlay, TierTwoInfos);
	DOREPLIFETIME(AGSPlay, TierThreeInfos);	
	DOREPLIFETIME(AGSPlay, TierOneCurrentInfos);
	DOREPLIFETIME(AGSPlay, TierTwoCurrentInfos);
	DOREPLIFETIME(AGSPlay, TierThreeCurrentInfos);
	DOREPLIFETIME(AGSPlay, TileState);
}
