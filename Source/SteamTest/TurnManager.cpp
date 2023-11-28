// Fill out your copyright notice in the Description page of Project Settings.


#include "TurnManager.h"
#include "PCPlay.h"
#include "PSPlayerInfo.h"
#include "STGameModePlay.h"
#include "Kismet/GameplayStatics.h"
#include "GSPlay.h"

// Sets default values
ATurnManager::ATurnManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Players.SetNum(2);
	PlayerTurn = 0;
}

// Called when the game starts or when spawned
void ATurnManager::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATurnManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATurnManager::InitPlayerTurn(APlayerController* Player, bool bFirst, const FString& playerName)
{
	auto CastedPC = Cast<APCPlay>(Player);
	if (CastedPC == nullptr) return;

	CastedPC->SetTurn(bFirst);

	if (bFirst) CurrentPlayer = CastedPC;

	if (Players.Num() == 2)
	{
		if(bFirst) Players[0] = CastedPC;
		else Players[1] = CastedPC;
	}

	CastedPC->SetTurnText(playerName);
}


void ATurnManager::EndCurrentTurn()
{
	if (CurrentPlayer)
	{
		CurrentPlayer->SetTurn(false);

		PlayerTurn = (PlayerTurn + 1) % 2;
		CurrentPlayer = Players[PlayerTurn];
		if (CurrentPlayer)
		{
			CurrentPlayer->SetTurn(true);
		}

		auto CurrentPlayerName = CurrentPlayer->GetPlayerState<APSPlayerInfo>()->GetPName();
		auto GM = Cast<ASTGameModePlay>(UGameplayStatics::GetGameMode(GetWorld()));
		if (GM)
		{
			auto GS = GM->GetGameState<AGSPlay>();

			for (auto PS : GS->PlayerArray)
			{
				Cast<APCPlay>(PS->GetPlayerController())->SetTurnText(CurrentPlayerName);
			}
		}
	}
}

bool ATurnManager::IsFirstPlayer(APlayerController* PC)
{
	auto CurrentPC = Cast<APCPlay>(PC);

	return Players[0] == CurrentPC;
}
