// Fill out your copyright notice in the Description page of Project Settings.


#include "STGameModePlay.h"
#include "PSPlayerInfo.h"
#include "GSPlay.h"
#include "TileManager.h"
#include "TokenManager.h"
#include "CardManager.h"
#include "Kismet/GameplayStatics.h"
#include "TurnManager.h"
#include "PCPlay.h"
#include "GlobalStruct.h"

ASTGameModePlay::ASTGameModePlay()
{
	bUseSeamlessTravel = true;
}

void ASTGameModePlay::SwapPlayerControllers(APlayerController* OldPC, APlayerController* NewPC)
{
	Super::SwapPlayerControllers(OldPC, NewPC);
}

void ASTGameModePlay::HandleSeamlessTravelPlayer(AController*& C)
{
	Super::HandleSeamlessTravelPlayer(C);

	Cast<APCPlay>(C)->SRSetTurn();
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
	CardManager = GetWorld()->SpawnActor<ACardManager>();

	if (TokenManager)
	{
		TokenManager->AddScroll.AddUObject(this, &ASTGameModePlay::GiveScroll);
	}

	auto GS = GetGameState<AGSPlay>();
	if (GS && IsValid(GS))
	{
		GS->InitState();
	}
}

//!-------------Turn-------------------
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

//!-------------Token-------------------
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

void ASTGameModePlay::PossessTokens(APlayerController* PC, bool bFirst)
{
	if (TokenManager)
	{
		TokenManager->PossessTokens(PC, bFirst);
	}

	if (TileManager)
	{
		TileManager->ClearSeletedTiles();
	}

	//턴 변경
	if (TurnManager)
	{
		TurnManager->EndCurrentTurn();
	}
}

void ASTGameModePlay::RestoreTokens(const FTokenCountList& Restore, APlayerController* player)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, FString::Printf(TEXT("RestoreTokens")));

	//PS Update
	auto PS = player->GetPlayerState<APSPlayerInfo>();
	if (PS)
	{
		for (auto color : TEnumRange<ETokenColor>())
		{
			PS->AddToken(color, -Restore[color]);
		}
	}

	if (TokenManager)
	{
		TokenManager->UseTokens(Restore, PS->GetBFirst());
	}
}

//!-------------Card-------------------
void ASTGameModePlay::BuyCard(APlayerController* player, FCardInfo cardInfo, const FTokenCountList& UseTokens)
{
	auto PS = player->GetPlayerState<APSPlayerInfo>();
	if (PS)
	{
		PS->AddBonus(cardInfo.color);
		PS->AddScore(cardInfo.color, cardInfo.score);
		PS->AddCrown(cardInfo.crown);
		
		//토큰 소비
		RestoreTokens(UseTokens, player);
	}

	//아이템, crown 처리
	bool bPassTurn = true;
	bPassTurn = UseItem(cardInfo, player);

	//카드 교체
	if (CardManager)
	{
		CardManager->ChangeCard();
	}

	//턴변경
	if (TurnManager && bPassTurn)
	{
		TurnManager->EndCurrentTurn();
	}
}

void ASTGameModePlay::CardClicked(ACard* ClickedCard)
{
	if (CardManager)
	{
		CardManager->SetCurrentSelectedCard(ClickedCard);
	}
}

//!-------------Scroll-------------------
void ASTGameModePlay::GiveScroll(APlayerController* player)
{
	int minus = 0;

	auto GS = GetGameState<AGSPlay>();
	if (GS && IsValid(GS))
	{
		int scroll = GS->GetGlobalScroll();

		if (scroll == 0)
		{
			minus = -1;
		}
		else
		{
			GS->AddGlobalScroll(-1);
		}
	}

	if (TurnManager)
	{
		if (TurnManager->IsFirstPlayer(player))
		{
			//second
			APCPlay* Second = TurnManager->GetScondPlayer();
			if (Second)
			{
				Second->GetPlayerState<APSPlayerInfo>()->AddScroll(1);
			}
		}
		else
		{
			//first
			APCPlay* First = TurnManager->GetFirstPlayer();
			if (First)
			{
				First->GetPlayerState<APSPlayerInfo>()->AddScroll(1);
			}
		}

		if (minus < 0)
		{
			player->GetPlayerState<APSPlayerInfo>()->AddScroll(minus);
		}
	}
}

//!-------------Item-------------------
bool ASTGameModePlay::UseItem(FCardInfo cardInfo, APlayerController* player)
{
	for (auto i : cardInfo.item)
	{
		switch (i)
		{
			case EItem::I_AnyColor:
				//widget
				Cast<APCPlay>(player)->ShowItemWidget(EItem::I_AnyColor, cardInfo);
				break;
			case EItem::I_GetScroll:
				GiveScroll(player);
				break;			
			case EItem::I_GetToken:
				//widget
				Cast<APCPlay>(player)->ShowItemWidget(EItem::I_GetToken, cardInfo);
				break;
			case EItem::I_RePlay:
				return false;
				break;			
			case EItem::I_TakeToken:
				//widget
				Cast<APCPlay>(player)->ShowItemWidget(EItem::I_TakeToken, cardInfo);
				break;
		}
	}

	return true;
}

void ASTGameModePlay::AddBonus(ETokenColor color, APlayerController* player)
{
	auto PS = player->GetPlayerState<APSPlayerInfo>();
	if (PS)
	{
		PS->AddBonus(color);
	}
}

void ASTGameModePlay::AddScore(ETokenColor color, int score, APlayerController* player)
{
	auto PS = player->GetPlayerState<APSPlayerInfo>();
	if (PS)
	{
		PS->AddColorScore(color, score);
	}
}


void ASTGameModePlay::PrintBonus()
{
	auto GS = GetGameState<AGSPlay>();

	if (GS)
	{
		for (auto PS : GS->PlayerArray)
		{
			for (auto color : TEnumRange<ETokenColor>())
			{
				GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, FString::Printf(TEXT("bonus: %d"), Cast<APSPlayerInfo>(PS)->GetBonusNum(color)));
			}
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, FString::Printf(TEXT("-------------------------")));
		}
	}
}

void ASTGameModePlay::PrintToken()
{
	auto GS = GetGameState<AGSPlay>();

	if (GS)
	{
		for (auto PS : GS->PlayerArray)
		{
			Cast<APSPlayerInfo>(PS)->PrintToken();
		}
	}
}