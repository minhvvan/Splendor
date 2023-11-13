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

void AGSPlay::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AGSPlay, RemainTokenIdx);
	DOREPLIFETIME(AGSPlay, Pouch);
}
