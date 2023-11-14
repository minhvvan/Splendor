// Fill out your copyright notice in the Description page of Project Settings.


#include "GSPlay.h"
#include "Net/UnrealNetwork.h"
#include "UObject/CoreNet.h"
#include "PSPlayerInfo.h"
#include "PCPlay.h"

void AGSPlay::InitState()
{
	GlobalScroll = 3;
	Pouch.Init();

	check(IsValid(RoyalData));

	auto Names = RoyalData->GetRowNames();
	FString ContextString;
	for (auto name : Names)
	{
		auto data = RoyalData->FindRow<FRoyalInfo>(name, ContextString);
		Royals.Add(*data);
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

void AGSPlay::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AGSPlay, RemainTokenIdx);
	DOREPLIFETIME(AGSPlay, Pouch);
	DOREPLIFETIME(AGSPlay, Royals);
}
