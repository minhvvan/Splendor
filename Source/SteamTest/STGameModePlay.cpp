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

TArray<FVector> ASTGameModePlay::GetTokenSpawnLoc(const TArray<class AToken*>& Tokens)
{
	if (TileManager)
	{
		auto Locs = TileManager->GetTokenLocs(Tokens);

		return Locs;
	}

	return TArray<FVector>();
}
