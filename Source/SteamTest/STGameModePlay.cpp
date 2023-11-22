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

	//client
	Cast<APCPlay>(C)->SRSetTurn();
}

void ASTGameModePlay::StartPlay()
{
	Super::StartPlay();
}

void ASTGameModePlay::StartMatch()
{
	Super::StartMatch();

	TurnManager = GetWorld()->SpawnActor<ATurnManager>();
	CardManager = GetWorld()->SpawnActor<ACardManager>();
}

void ASTGameModePlay::InitGameState()
{
	Super::InitGameState();

	auto GS = GetGameState<AGSPlay>();
	if (IsValid(GS))
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

void ASTGameModePlay::PossessTokens(APlayerController* PC, const TArray<FTokenIdxColor>& SelectedTokens)
{
	//PS Update
	auto PS = PC->GetPlayerState<APSPlayerInfo>();
	auto GS = GetGameState<AGSPlay>();
	bool bFrist = PS->GetBFirst();

	check(IsValid(PS) && IsValid(GS));
	
	bool bGiveScroll = CheckGiveScroll(SelectedTokens);
	bool bGold = false;
	if (bGiveScroll) GiveScroll(PC);

	TArray<int> DestroyTokenIdx;
	for (auto token : SelectedTokens)
	{
		if (token.Color == ETokenColor::E_Gold) bGold = true;
		PS->AddToken(token.Color, 1);
	}

	//gold check
	if (bGold)
	{
		Cast<APCPlay>(PS->GetPlayerController())->AddCardToHand();
	}

	//GS Update
	for (auto token : SelectedTokens)
	{
		GS->RemoveTokenIdx(token.Idx);
	}

	for (auto token : SelectedTokens)
	{
		DestroyTokenIdx.Add(token.Idx);
	}

	for (auto ps : GS->PlayerArray)
	{
		auto Controller = Cast<APCPlay>(ps->GetPlayerController());
		Controller->RemoveTokens(DestroyTokenIdx, PC == Controller);
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
	auto GS = GetGameState<AGSPlay>();
	auto PS = PC->GetPlayerState<APSPlayerInfo>();
	check(IsValid(GS) && IsValid(PS));

	auto CurrentState = GS->GetCurrentTileState();
	auto color = CurrentState[idx];

	TArray<int> temp;
	temp.Add(idx);

	for (auto ps : GS->PlayerArray)
	{
		auto Controller = Cast<APCPlay>(ps->GetPlayerController());
		Controller->RemoveTokens(temp, PC == Controller);
	}

	//ps update
	PS->AddToken(color, 1);
}

void ASTGameModePlay::FillToken(APlayerController* PC)
{
	//GS에서 pouch받아서 다시 스폰
	auto GS = GetGameState<AGSPlay>();
	check(IsValid(GS));

	auto pouch = GS->GetPouch();
	if (pouch.Num() == 0) return;

	GS->ClearPouch();

	TArray<FTokenIdxColor> Tokens;

	//GS에 Add
	for (auto token : pouch)
	{
		for (int i = 0; i < token.Value; i++)
		{
			int idx = GS->AddToken(token.Key);
			Tokens.Add({ idx, token.Key });
		}
	}

	//All PC Spawn
	for (auto ps : GS->PlayerArray)
	{
		auto PC = Cast<APCPlay>(ps->GetPlayerController());
		PC->SpawnToken(Tokens);
	}

	//상대에게 특권하나
	GiveScroll(PC);
}

bool ASTGameModePlay::CheckGiveScroll(const TArray<FTokenIdxColor>& SelectedTokens)
{
	bool bGiveScroll = SelectedTokens.Num() == 3 ? true : false;
	int pearlCnt = 0;
	ETokenColor current = ETokenColor::E_End;
	for (auto selected : SelectedTokens)
	{
		auto tType = selected.Color;
		if (tType == ETokenColor::E_Pearl) pearlCnt++;

		if (current == ETokenColor::E_End)
		{
			current = tType;
		}
		else
		{
			if (current != tType) bGiveScroll = false;
		}
	}

	if (bGiveScroll || pearlCnt >= 2)
	{
		return true;
	}

	return false;
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