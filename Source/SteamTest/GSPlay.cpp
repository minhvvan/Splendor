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
}

void AGSPlay::RemoveTokenIdx(int idx, ETokenColor color)
{
	RemainTokenIdx.Remove({ idx, color });
}

void AGSPlay::AddTokenIdx(int idx, ETokenColor color)
{
	RemainTokenIdx.Add({ idx, color });
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
	if (bFirst)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, FString::Printf(TEXT("First UpdateRoyalOwner: %d"), key));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, FString::Printf(TEXT("Second UpdateRoyalOwner: %d"), key));
	}

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
	DOREPLIFETIME(AGSPlay, RemainTokenIdx);
	DOREPLIFETIME(AGSPlay, Pouch);
	DOREPLIFETIME(AGSPlay, Royals);
	DOREPLIFETIME(AGSPlay, TierOneInfos);
	DOREPLIFETIME(AGSPlay, TierTwoInfos);
	DOREPLIFETIME(AGSPlay, TierThreeInfos);	
	DOREPLIFETIME(AGSPlay, TierOneCurrentInfos);
	DOREPLIFETIME(AGSPlay, TierTwoCurrentInfos);
	DOREPLIFETIME(AGSPlay, TierThreeCurrentInfos);
}
