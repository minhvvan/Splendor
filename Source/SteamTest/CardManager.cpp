// Fill out your copyright notice in the Description page of Project Settings.


#include "CardManager.h"

// Sets default values
ACardManager::ACardManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UDataTable> CARD(TEXT("/Script/Engine.DataTable'/Game/Data/DT_CardInfo.DT_CardInfo'"));
	if (CARD.Succeeded())
	{
		CardData = CARD.Object;
	}
}

// Called when the game starts or when spawned
void ACardManager::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, FString::Printf(TEXT("BeginPlay")));

	InitData();
	SpawnCards();
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
	}
}

void ACardManager::SpawnCards()
{
	for (auto one : TierOneInfos)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, FString::Printf(TEXT("score: %d"), one.score));
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, FString::Printf(TEXT("bonus: %d"), one.bonus));
		for (auto c : one.cost)
		{
			FString color;
			switch (c.Key)
			{
			case EColor::E_Red:
				color = TEXT("Red");
			case EColor::E_Green:
				color = TEXT("Green");
			case EColor::E_Blue:
				color = TEXT("Blue");
			case EColor::E_White:
				color = TEXT("White");
			case EColor::E_Black:
				color = TEXT("Black");
			}
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, FString::Printf(TEXT("cost: %s, %d"), color, c.Value));
		}
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, FString::Printf(TEXT("crown: %d"), one.crown));

		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, FString::Printf(TEXT("----------------")));
	}
}

