// Fill out your copyright notice in the Description page of Project Settings.


#include "STGameModePlay.h"
#include "PSPlayerInfo.h"
#include "GSPlay.h"
#include "TileManager.h"
#include "TokenManager.h"
#include "Kismet/GameplayStatics.h"
#include "TurnManager.h"
#include "PCPlay.h"

ASTGameModePlay::ASTGameModePlay()
{
	bUseSeamlessTravel = true;
}

void ASTGameModePlay::SwapPlayerControllers(APlayerController* OldPC, APlayerController* NewPC)
{
	Super::SwapPlayerControllers(OldPC, NewPC);
}

void ASTGameModePlay::InitPlayerTurn(APlayerController* Player, bool bFirst)
{
	if (TurnManager)
	{
		auto GS = GetGameState<AGSPlay>();
		
		if (GS)
		{
			for (auto PS : GS->PlayerArray)
			{
				TurnManager->InitPlayerTurn(PS->GetPlayerController(), Cast<APSPlayerInfo>(PS)->GetBFirst());
			}
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
	TurnManager = GetWorld()->SpawnActor<ATurnManager>();

	if (TokenManager)
	{
		TokenManager->AddScroll.AddUObject(this, &ASTGameModePlay::GiveScroll);
	}
}

void ASTGameModePlay::SetTokenSpawnLoc(TArray<class AToken*>& Tokens)
{
	if (TileManager)
	{
		TileManager->SetTokenLocs(Tokens);
	}
}

void ASTGameModePlay::TokenClicked(AToken* ClickedToken, int cnt, bool bAble)
{
	if (ClickedToken)
	{
		int boardIdx = ClickedToken->GetIndex();

		if (TileManager)
		{
			TileManager->Clicked(boardIdx, cnt, bAble);
		}

		if (TokenManager)
		{
			TokenManager->SelectedToken(ClickedToken, bAble);
		}

		ClickedToken->Clicked();
	}
}

void ASTGameModePlay::PossessTokens(APlayerController* PC)
{
	if (TokenManager)
	{
		TokenManager->PossessTokens(PC);
	}

	if (TileManager)
	{
		TileManager->ClearSeletedTiles();
	}

	//ÅÏ º¯°æ
	if (TurnManager)
	{
		TurnManager->EndCurrentTurn();
	}
}

void ASTGameModePlay::GiveScroll(APlayerController* player)
{
	if (TurnManager)
	{
		if (TurnManager->IsFirstPlayer(player))
		{
			//second
			APCPlay* Second = TurnManager->GetScondPlayer();
			if (Second)
			{
				GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, FString::Printf(TEXT("Give Second")));
				Second->GetPlayerState<APSPlayerInfo>()->AddScroll(1);
			}
		}
		else
		{
			//first
			APCPlay* First = TurnManager->GetFirstPlayer();
			if (First)
			{
				GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, FString::Printf(TEXT("Give First")));
				First->GetPlayerState<APSPlayerInfo>()->AddScroll(1);
			}
		}
	}
}

void ASTGameModePlay::HandleSeamlessTravelPlayer(AController*& C)
{
	Super::HandleSeamlessTravelPlayer(C);

	Cast<APCPlay>(C)->SRSetTurn();
}