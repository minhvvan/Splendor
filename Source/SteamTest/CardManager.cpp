

#include "CardManager.h"
#include "Card.h"
#include "GSPlay.h"
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

void ACardManager::InitCards()
{
	UWorld* world = GetWorld();
	if (world)
	{
		FVector offset(0, 180, 0);
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		FRotator rotator;

		auto GS = GetWorld()->GetGameState<AGSPlay>();
		check(IsValid(GS));

		{
			FVector SpawnLoc = StartOneTier;
			for (int i = 0; i < 5; i++)
			{
				auto Card = Cast<ACard>(world->SpawnActor<AActor>(CardClass, SpawnLoc, rotator, SpawnParams));

				SpawnLoc += offset;
				auto info = GS->GetInfoByTier(ECardTier::C_One);
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
				auto info = GS->GetInfoByTier(ECardTier::C_Two);
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
				auto info = GS->GetInfoByTier(ECardTier::C_Three);
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

		auto GS = GetWorld()->GetGameState<AGSPlay>();
		check(IsValid(GS));

		{
			FVector SpawnLoc = DummyOneTier;
			auto CardDumy = Cast<ACardDummy>(world->SpawnActor<AActor>(DummyClass, SpawnLoc, rotator, SpawnParams));
			if (CardDumy)
			{
				CardDumy->SetTier(ECardTier::C_One);
				CardDumy->SetNum(GS->GetInfoNumByTier(ECardTier::C_One));
				CardDummies.Add(CardDumy);
			}
		}
		{
			FVector SpawnLoc = DummyTwoTier;
			auto CardDumy = Cast<ACardDummy>(world->SpawnActor<AActor>(DummyClass, SpawnLoc, rotator, SpawnParams));
			if (CardDumy)
			{
				CardDumy->SetTier(ECardTier::C_Two);
				CardDumy->SetNum(GS->GetInfoNumByTier(ECardTier::C_Two));
				CardDummies.Add(CardDumy);
			}
		} 
		{
			FVector SpawnLoc = DummyThreeTier;
			auto CardDumy = Cast<ACardDummy>(world->SpawnActor<AActor>(DummyClass, SpawnLoc, rotator, SpawnParams));
			if (CardDumy)
			{
				CardDumy->SetTier(ECardTier::C_Three);
				CardDumy->SetNum(GS->GetInfoNumByTier(ECardTier::C_Three));
				CardDummies.Add(CardDumy);
			}
		}
	}

}

void ACardManager::DestoryCard(FVector loc, ECardTier tier, ACard* card)
{
	auto& CurrentTokenList = GetCardListByTier(tier);

	auto GS = GetWorld()->GetGameState<AGSPlay>();
	check(IsValid(GS));

	UWorld* world = GetWorld();
	if (world)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		FRotator rotator;

		if (GS->GetInfoNumByTier(tier) > 0)
		{
			auto SpawnedCard = Cast<ACard>(world->SpawnActor<AActor>(CardClass, loc, rotator, SpawnParams));
			auto info = GS->GetInfoByTier(tier);
			SpawnedCard->SetInfo(info);

			CurrentTokenList.Add(SpawnedCard);
		}
	}

	//!TODO: GS로 업데이트하게 변경 필요
	for (auto dummy : CardDummies)
	{
		if (dummy->GetTier() == tier)
		{
			dummy->AddNum(-1);
		}
	}
}

void ACardManager::ChangeCard(FCardInfo cardInfo)
{
	auto GS = GetWorld()->GetGameState<AGSPlay>();
	check(IsValid(GS));

	auto& CardList = GetCardListByTier(cardInfo.tier);

	for (auto card : CardList)
	{
		//key 값 비교
		auto info = card->GetInfo();
		if (info == cardInfo)
		{
			auto loc = card->GetActorLocation();
			CardList.Remove(card);
			DestoryCard(loc, cardInfo.tier, card);
			card->Destroy();
			break;
		}
	}

	GS->RemoveCurrentCardInfo(cardInfo);
}

TArray<ACard*>& ACardManager::GetCardListByTier(ECardTier tier)
{
	switch (tier)
	{
	case ECardTier::C_One:
		return TierOne;
		break;
	case ECardTier::C_Two:
		return TierTwo;
		break;
	}

	return TierThree;
}