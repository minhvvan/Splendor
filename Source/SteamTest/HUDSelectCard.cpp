// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDSelectCard.h"
#include "GSPlay.h"
#include "Components/TileView.h"
#include "CardData.h"
#include "GlobalEnum.h"

void UHUDSelectCard::NativeOnInitialized()
{
	auto GS = GetWorld()->GetGameState<AGSPlay>();
	check(IsValid(GS));

	auto One = GS->GetCurrentInfoByTier(ECardTier::C_One);
	auto Two = GS->GetCurrentInfoByTier(ECardTier::C_Two);
	auto Three = GS->GetCurrentInfoByTier(ECardTier::C_Three);

	check(IsValid(CardDataClass));

	for (auto card : One)
	{
		auto CardData = NewObject<UCardData>(this, CardDataClass);
		CardData->SetData(card);

		TVOne->AddItem(CardData);
	}

	for (auto card : Two)
	{
		auto CardData = NewObject<UCardData>(this, CardDataClass);
		CardData->SetData(card);

		TVTwo->AddItem(CardData);
	}


	for (auto card : Three)
	{
		auto CardData = NewObject<UCardData>(this, CardDataClass);
		CardData->SetData(card);

		TVThree->AddItem(CardData);
	}
}
