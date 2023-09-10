// Fill out your copyright notice in the Description page of Project Settings.


#include "PCPlay.h"
#include "PSPlayerInfo.h"
#include "Kismet/GameplayStatics.h"
#include "STGameModePlay.h"

APCPlay::APCPlay()
{
}

void APCPlay::BeginPlay()
{
	GEngine->AddOnScreenDebugMessage(-1, 15, FColor::Red, FString::Printf(TEXT("PCPlay: BeginPlay")));
}

void APCPlay::SeamlessTravelFrom(APlayerController* OldPC)
{
	Super::SeamlessTravelFrom(OldPC);

	SRSetTurn();
}


void APCPlay::SRSetTurn_Implementation()
{
	auto PS = GetPlayerState<APSPlayerInfo>();
	
	if (PS)
	{
		auto GM = Cast<ASTGameModePlay>(UGameplayStatics::GetGameMode(GetWorld()));

		//GS Update
		if (GM)
		{
			GM->SetPlayerTurn(this, PS->GetMyTurn());
		}
	}
}
