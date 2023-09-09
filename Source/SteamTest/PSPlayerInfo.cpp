// Fill out your copyright notice in the Description page of Project Settings.


#include "PSPlayerInfo.h"
#include "Net/UnrealNetwork.h"
#include "UObject/CoreNet.h"

APSPlayerInfo::APSPlayerInfo()
{
}

void APSPlayerInfo::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(APSPlayerInfo, PName);
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
		}
	}
}