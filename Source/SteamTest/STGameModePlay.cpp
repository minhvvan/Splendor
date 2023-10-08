// Fill out your copyright notice in the Description page of Project Settings.


#include "STGameModePlay.h"
#include "PSPlayerInfo.h"
#include "GSPlay.h"
#include "TileManager.h"
#include "TokenManager.h"
#include "Kismet/GameplayStatics.h"
#include "PCPlay.h"

ASTGameModePlay::ASTGameModePlay()
{
	bUseSeamlessTravel = true;
}

void ASTGameModePlay::SwapPlayerControllers(APlayerController* OldPC, APlayerController* NewPC)
{
	Super::SwapPlayerControllers(OldPC, NewPC);
}

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

void ASTGameModePlay::StartPlay()
{
	Super::StartPlay();
}

void ASTGameModePlay::StartMatch()
{
	Super::StartMatch();

	TileManager = GetWorld()->SpawnActor<ATileManager>();
	TokenManager = GetWorld()->SpawnActor<ATokenManager>();
}

TPair<TArray<FVector>, TArray<int>> ASTGameModePlay::GetTokenSpawnLoc(const TArray<class AToken*>& Tokens)
{
	if (TileManager)
	{
		auto LocAndIdx = TileManager->GetTokenLocs(Tokens);

		return LocAndIdx;
	}

	return TPair<TArray<FVector>, TArray<int>>();
}

void ASTGameModePlay::TokenClicked(AToken* ClickedToken, int cnt, bool bAble)
{
	if (ClickedToken)
	{
		int boardIdx = ClickedToken->GetBoardIndex();

		if (TileManager)
		{
			TileManager->Clicked(boardIdx, cnt, bAble);
		}

		ClickedToken->Clicked();
	}
}