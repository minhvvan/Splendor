// Fill out your copyright notice in the Description page of Project Settings.


#include "CardManager.h"
#include "Card.h"
#include "Algo/RandomShuffle.h"

// Sets default values
ACardManager::ACardManager() : StartOneTier(FVector(-15, -670, 0)), StartTwoTier(FVector(215, -580, 0)), StartThreeTier(FVector(455, -490, 0))
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UDataTable> DATA(TEXT("/Script/Engine.DataTable'/Game/Data/DT_CardInfo.DT_CardInfo'"));
	if (DATA.Succeeded())
	{
		CardData = DATA.Object;
	}

	ConstructorHelpers::FClassFinder<ACard> CARD(TEXT("/Script/Engine.Blueprint'/Game/Splendor/BP/BP_Card.BP_Card_C'"));
	if (CARD.Succeeded())
	{
		CardClass = CARD.Class;
	}
}

// Called when the game starts or when spawned
void ACardManager::BeginPlay()
{
	Super::BeginPlay();

	InitData();
	InitCards();
}

// Called every frame
void ACardManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

ACard* ACardManager::GetCardByTier(ECardTier tier)
{
	switch (tier)
	{
	case ECardTier::C_One:
		if (!TierOne.IsEmpty()) return TierOne.Pop();
	case ECardTier::C_Two:
		if (!TierTwo.IsEmpty()) return TierTwo.Pop();
	case ECardTier::C_Three:
		if (!TierThree.IsEmpty()) return TierThree.Pop();
	}

	return nullptr;
}

void ACardManager::InitData()
{
	//테이블에서 받아와서 array에 넣기
	if(CardData && IsValid(CardData))
	{
		auto Names = CardData->GetRowNames();
		FString ContextString;
		for (auto name : Names)
		{
			auto data = CardData->FindRow<FCardInfo>(name, ContextString);
			switch (data->tier)
			{
			case ECardTier::C_One:
				TierOneInfos.Add(*data);
				break;
			case ECardTier::C_Two:
				TierTwoInfos.Add(*data);
				break;
			case ECardTier::C_Three:
				TierThreeInfos.Add(*data);
				break;
			}
		}
		Algo::RandomShuffle(TierOneInfos);
		Algo::RandomShuffle(TierTwoInfos);
		Algo::RandomShuffle(TierThreeInfos);
	}
}

void ACardManager::InitCards()
{
	UWorld* world = GetWorld();
	if (world)
	{
		FVector offset(0, 180, 0);
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		FRotator rotator;

		{
			FVector SpawnLoc = StartOneTier;
			for (int i = 0; i < 5; i++)
			{
				auto Card = Cast<ACard>(world->SpawnActor<AActor>(CardClass, SpawnLoc, rotator, SpawnParams));

				SpawnLoc += offset;
				auto info = TierOneInfos.Pop();
				Card->SetInfo(info);
				TierOne.Add(Card);
			}
		}

		{
			FVector SpawnLoc = StartTwoTier;
			for (int i = 0; i < 4; i++)
			{
				auto Card = Cast<ACard>(world->SpawnActor<AActor>(CardClass, SpawnLoc, rotator, SpawnParams));

				SpawnLoc += offset;
				auto info = TierTwoInfos.Pop();
				Card->SetInfo(info);
				TierTwo.Add(Card);
			}
		}

		{
			FVector SpawnLoc = StartThreeTier;
			for (int i = 0; i < 3; i++)
			{
				auto Card = Cast<ACard>(world->SpawnActor<AActor>(CardClass, SpawnLoc, rotator, SpawnParams));

				SpawnLoc += offset;
				auto info = TierThreeInfos.Pop();
				Card->SetInfo(info);
				TierThree.Add(Card);
			}
		}
	}
}

