// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDSelectCard.h"
#include "GSPlay.h"
#include "GlobalEnum.h"

void UHUDSelectCard::NativeOnInitialized()
{
	auto GS = GetWorld()->GetGameState<AGSPlay>();
	check(IsValid(GS));

	auto One = GS->GetCurrentInfoByTier(ECardTier::C_One);
	auto Two = GS->GetCurrentInfoByTier(ECardTier::C_Two);
	auto Three = GS->GetCurrentInfoByTier(ECardTier::C_Three);

	for (auto card : One)
	{

	}
}
