// Fill out your copyright notice in the Description page of Project Settings.


#include "GSPlay.h"
#include "PSPlayerInfo.h"
#include "PCPlay.h"

void AGSPlay::SetFirstPlayer(APlayerController* Player)
{
	if (!FirstPlayer)
	{
		FirstPlayer = Cast<APCPlay>(Player);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("already set firstPlayer")));
	}
}

void AGSPlay::SetSecondPlayer(APlayerController* Player)
{
	if (!SecondPlayer)
	{
		SecondPlayer = Cast<APCPlay>(Player);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("already set firstPlayer")));
	}
}
