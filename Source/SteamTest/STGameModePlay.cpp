// Fill out your copyright notice in the Description page of Project Settings.


#include "STGameModePlay.h"
#include "PSPlayerInfo.h"
#include "GSPlay.h"
#include "TileManager.h"
#include "Kismet/GameplayStatics.h"
#include "PCPlay.h"

ASTGameModePlay::ASTGameModePlay()
{
	bUseSeamlessTravel = true;

	TileManager = CreateDefaultSubobject<ATileManager>(TEXT("TileManager"));
}

void ASTGameModePlay::SwapPlayerControllers(APlayerController* OldPC, APlayerController* NewPC)
{
	Super::SwapPlayerControllers(OldPC, NewPC);
	//SpawnPlayer(NewPC);
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

void ASTGameModePlay::SpawnPlayer(APlayerController* PlayerController)
{
	if (IsValid(PlayerController))
	{
		auto Pawn = PlayerController->GetPawn();
		if (Pawn)
		{
			Pawn->Destroy();
		}
	}

	//Cast<APCPlay>(PlayerController)->SpawnPlayer();
}

void ASTGameModePlay::RestartPlayer(AController* NewPlayer)
{
	Super::RestartPlayer(NewPlayer);
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("RestartPlayer")));
}
