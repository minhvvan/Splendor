// Fill out your copyright notice in the Description page of Project Settings.


#include "TurnManager.h"
#include "PCPlay.h"

// Sets default values
ATurnManager::ATurnManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATurnManager::BeginPlay()
{
	Super::BeginPlay();

	Players.SetNum(2);
	PlayerTurn = 0;
}

// Called every frame
void ATurnManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATurnManager::InitPlayerTurn(APlayerController* Player, bool bFirst)
{
	if (bFirst)
	{
		auto FirstPlayer = Cast<APCPlay>(Player);
		FirstPlayer->SetTurn(true);
		Players[0] = FirstPlayer;

		CurrentPlayer = FirstPlayer;
	}
	else
	{
		auto SecondPlayer = Cast<APCPlay>(Player);
		SecondPlayer->SetTurn(false);
		Players[1] = SecondPlayer;
	}
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
	}
}

bool ATurnManager::IsFirstPlayer(APlayerController* PC)
{
	auto CurrentPC = Cast<APCPlay>(PC);

	return Players[0] == CurrentPC;
}
