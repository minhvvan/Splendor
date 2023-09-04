// Fill out your copyright notice in the Description page of Project Settings.


#include "GSLobby.h"
#include "Net/UnrealNetwork.h"

bool AGSLobby::SetFirstPlayer(APCLobby* pc)
{
	if (FirstPlayer)
	{
		if (FirstPlayer == pc)
		{
			FirstPlayer = nullptr;
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 15, FColor::Blue, FString::Printf(TEXT("First: other player clicked")));
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
	if (SecondPlayer)
	{
		if (SecondPlayer == pc)
		{
			SecondPlayer = nullptr;
		}
		else
		{
			// �ٸ� player�� �̹� ������ ��Ȳ
			//pop up ���� ���� ��
			GEngine->AddOnScreenDebugMessage(-1, 15, FColor::Blue, FString::Printf(TEXT("Second: other player clicked")));
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
	GEngine->AddOnScreenDebugMessage(-1, 15, FColor::Blue, FString::Printf(TEXT("checkCanStart")));

	if (FirstPlayer && SecondPlayer)
	{
		bCanStart = true;
	}
	else
	{
		bCanStart = false;
	}
}
