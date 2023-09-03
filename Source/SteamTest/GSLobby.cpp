// Fill out your copyright notice in the Description page of Project Settings.


#include "GSLobby.h"

bool AGSLobby::SetFirstPlayer(APCLobby* pc)
{
	if (FirstPlayer)
	{
		if (FirstPlayer == pc)
		{
			FirstPlayer = nullptr;
			return false;
		}
	}
	else
	{
		FirstPlayer = pc;
		return true;
	}

	return true;
}

bool AGSLobby::SetSecondPlayer(APCLobby* pc)
{
	SecondPlayer = pc;
	return true;
}
