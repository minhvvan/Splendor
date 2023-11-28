// Fill out your copyright notice in the Description page of Project Settings.


#include "GSLobby.h"
#include "Net/UnrealNetwork.h"
#include "PCLobby.h"
#include "PSPlayerInfo.h"

bool AGSLobby::SetFirstPlayer(APCLobby* pc)
{
	if (SecondPlayer == pc)
	{
		SecondPlayer = nullptr;
		FirstPlayer = pc;

		for (auto PS : PlayerArray)
		{
			Cast<APCLobby>(PS->GetPlayerController())->MarkSecond(FString(""));
		}
		return true;
	}

	if (FirstPlayer)
	{
		if (FirstPlayer == pc)
		{
			FirstPlayer = nullptr;
		}
	}
	else
	{
		FirstPlayer = pc;
	}

	checkCanStart();
	return FirstPlayer ? true : false;
}

bool AGSLobby::SetSecondPlayer(APCLobby* pc)
{
	if (FirstPlayer == pc)
	{
		FirstPlayer = nullptr;
		SecondPlayer = pc;

		for (auto PS : PlayerArray)
		{
			Cast<APCLobby>(PS->GetPlayerController())->MarkFirst(FString(""));
		}
		return true;
	}

	if (SecondPlayer)
	{
		if (SecondPlayer == pc)
		{
			SecondPlayer = nullptr;
		}
	}
	else
	{
		SecondPlayer = pc;
	}

	checkCanStart();
	return SecondPlayer ? true : false;
}

void AGSLobby::checkCanStart()
{
	if (FirstPlayer && SecondPlayer)
	{
		bCanStart = true;
	}
	else
	{
		bCanStart = false;
	}
}
