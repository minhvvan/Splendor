// Fill out your copyright notice in the Description page of Project Settings.


#include "CardManager.h"
#include "Card.h"
#include "CardDummy.h"
#include "Algo/RandomShuffle.h"
#include "GlobalEnum.h"
#include "GlobalStruct.h"

// Sets default values
ACardManager::ACardManager() : StartOneTier(FVector(-15, -670, 0)), StartTwoTier(FVector(215, -580, 0)), StartThreeTier(FVector(445, -490, 0))
, DummyOneTier(FVector(-15, -870.0, 0)), DummyTwoTier(FVector(215, -870.0, 0)), DummyThreeTier(FVector(445, -870.0, 0))
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

	ConstructorHelpers::FClassFinder<ACardDummy> DUMMY(TEXT("/Script/Engine.Blueprint'/Game/Splendor/BP/BP_CardDummy.BP_CardDummy_C'"));
	if (DUMMY.Succeeded())
	{
		DummyClass = DUMMY.Class;
	}
}

// Called when the game starts or when spawned
void ACardManager::BeginPlay()
{
	Super::BeginPlay();

	InitData();
	InitCards();
	InitDummy();
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

void ACardManager::InitDummy()
{
	UWorld* world = GetWorld();
	if (world)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		FRotator rotator;

		{
			FVector SpawnLoc = DummyOneTier;
			auto CardDumy = Cast<ACardDummy>(world->SpawnActor<AActor>(DummyClass, SpawnLoc, rotator, SpawnParams));
			if (CardDumy)
			{
				CardDumy->SetTier(ECardTier::C_One);
				CardDumy->SetNum(TierOneInfos.Num());
				CardDummies.Add(CardDumy);
			}
		}
		{
			FVector SpawnLoc = DummyTwoTier;
			auto CardDumy = Cast<ACardDummy>(world->SpawnActor<AActor>(DummyClass, SpawnLoc, rotator, SpawnParams));
			if (CardDumy)
			{
				CardDumy->SetTier(ECardTier::C_Two);
				CardDumy->SetNum(TierTwoInfos.Num());
				CardDummies.Add(CardDumy);
			}
		} 
		{
			FVector SpawnLoc = DummyThreeTier;
			auto CardDumy = Cast<ACardDummy>(world->SpawnActor<AActor>(DummyClass, SpawnLoc, rotator, SpawnParams));
			if (CardDumy)
			{
				CardDumy->SetTier(ECardTier::C_Three);
				CardDumy->SetNum(TierThreeInfos.Num());
				CardDummies.Add(CardDumy);
			}
		}
	}

}