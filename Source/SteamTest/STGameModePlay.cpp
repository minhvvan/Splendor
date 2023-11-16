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

	auto GS = GetGameState<AGSPlay>();
	if (GS && IsValid(GS))
	{
		GS->InitState();
	}

	TileManager = GetWorld()->SpawnActor<ATileManager>();
	TokenManager = GetWorld()->SpawnActor<ATokenManager>();
	TurnManager = GetWorld()->SpawnActor<ATurnManager>();
	CardManager = GetWorld()->SpawnActor<ACardManager>();

	if (TokenManager)
	{
		TokenManager->AddScroll.AddUObject(this, &ASTGameModePlay::GiveScroll);
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

void ASTGameModePlay::EndCurrentTurn()
{
	check(IsValid(TurnManager));

	TurnManager->EndCurrentTurn();
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
	//PS Update
	auto PS = player->GetPlayerState<APSPlayerInfo>();
	auto GS = GetGameState<AGSPlay>();
	check(IsValid(GS) && IsValid(PS));

	for (auto color : TEnumRange<ETokenColor>())
	{
		PS->AddToken(color, -Restore[color]);
		GS->AddPouch(color, Restore[color]);
	}
}

void ASTGameModePlay::TakeToken(APlayerController* PC, ETokenColor color)
{
	if (TokenManager)
	{
		//PS update
		bool bFirst = PC->GetPlayerState<APSPlayerInfo>()->GetBFirst();
		for (auto ps : GetGameState<AGSPlay>()->PlayerArray)
		{
			auto casted = Cast<APSPlayerInfo>(ps);
			if (casted->GetBFirst() == bFirst)
			{
				casted->AddToken(color, 1);
			}
			else
			{
				casted->AddToken(color, -1);
			}
		}
	}
}

void ASTGameModePlay::GetTokenByIdx(APlayerController* PC, int idx)
{
	check(IsValid(TokenManager));

	TokenManager->GetTokenByIdx(PC, idx);
}

void ASTGameModePlay::FillToken(APlayerController* PC)
{
	//GS에서 pouch받아서 다시 스폰
	auto GS = GetGameState<AGSPlay>();
	check(IsValid(TokenManager) && IsValid(GS));
	auto pouch = GS->GetPouch();

	TokenManager->SpawnTokensByList(pouch);
	GS->ClearPouch();

	//상대에게 특권하나
	GiveScroll(PC);
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
	UseItem(cardInfo, player);

	//카드 교체
	if (CardManager)
	{ 
		CardManager->ChangeCard(cardInfo);
	}

	if(PS->GetCrown() != 3 && PS->GetCrown() != 6 && cardInfo.item.Num() == 0)
	{
		EndCurrentTurn();
	}
}

void ASTGameModePlay::ChangeCard(FCardInfo cardInfo)
{
	check(IsValid(CardManager));

	CardManager->ChangeCard(cardInfo);
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

void ASTGameModePlay::GetScroll(APlayerController* player)
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
	
	check(IsValid(TurnManager));

	player->GetPlayerState<APSPlayerInfo>()->AddScroll(1);

	if (minus < 0)
	{
		if (TurnManager->IsFirstPlayer(player))
		{
			//second
			APCPlay* Second = TurnManager->GetScondPlayer();
			if (Second)
			{
				Second->GetPlayerState<APSPlayerInfo>()->AddScroll(minus);
			}
		}
		else
		{
			//first
			APCPlay* First = TurnManager->GetFirstPlayer();
			if (First)
			{
				First->GetPlayerState<APSPlayerInfo>()->AddScroll(minus);
			}
		}
	}
}

//!-------------Item-------------------
void ASTGameModePlay::UseItem(FCardInfo cardInfo, APlayerController* player)
{
	for (auto i : cardInfo.item)
	{
		switch (i)
		{
			case EItem::I_AnyColor:
				Cast<APCPlay>(player)->UseItemAnyColor(cardInfo);
				break;
			case EItem::I_GetScroll:
				GetScroll(player);
				break;			
			case EItem::I_GetToken:
				Cast<APCPlay>(player)->UseItemGetToken(cardInfo);
				break;
			case EItem::I_TakeToken:
				Cast<APCPlay>(player)->UseItemTakeToken();
				break;
		}
	}
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
		PS->AddScore(color, score);
	}
}

//!-----------Crown----------------------
void ASTGameModePlay::UpdateRoyal(int key, bool bFirst)
{
	auto GS = GetGameState<AGSPlay>();
	check(IsValid(GS));

	GS->UpdateRoyalOwner(key, bFirst);
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