// Fill out your copyright notice in the Description page of Project Settings.


#include "STGameModePlay.h"
#include "PSPlayerInfo.h"
#include "GSPlay.h"

ASTGameModePlay::ASTGameModePlay()
{
	bUseSeamlessTravel = true;
}

void ASTGameModePlay::SwapPlayerControllers(APlayerController* OldPC, APlayerController* NewPC)
{
	Super::SwapPlayerControllers(OldPC, NewPC);
}

//void ASTGameModePlay::InitGameState()
//{
//	auto GS = GetGameState<AGSPlay>();
//
//	for (auto ps : GS->PlayerArray)
//	{
//		auto name = Cast<APSPlayerInfo>(ps)->GetPName();
//	}
//}

void ASTGameModePlay::SetPlayerTurn(APlayerController* Player, bool bFirst)
{
	auto GS = GetGameState<AGSPlay>();
	
	if (GS)
	{
		if (bFirst)
		{
			GS->SetFirstPlayer(Player);
		}
		else
		{
			GS->SetSecondPlayer(Player);
		}
	}
}
