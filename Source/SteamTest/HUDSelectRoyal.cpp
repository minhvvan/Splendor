// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDSelectRoyal.h"
#include "Components/TextBlock.h"
#include "Components/TileView.h"
#include "Kismet/GameplayStatics.h"
#include "GSPlay.h"
#include "RoyalData.h"

void UHUDSelectRoyal::SetScore(int score)
{
	TxtScore->SetText(FText::AsNumber(score));
}

void UHUDSelectRoyal::SetCrown(int crown)
{
	TxtCrown->SetText(FText::AsNumber(crown));
}

void UHUDSelectRoyal::SetScroll(int scroll)
{
	TxtScroll->SetText(FText::AsNumber(scroll));
}

void UHUDSelectRoyal::SetRoyal()
{
	auto GS = GetWorld()->GetGameState<AGSPlay>();
	check(RoyalDataClass);

	auto royals = GS->GertRoylas();

	for (auto royal : royals)
	{
		auto RoyalData = NewObject<URoyalData>(this, RoyalDataClass);
		RoyalData->SetKey(royal.Key);
		RoyalData->SetScore(royal.Score);
		RoyalData->SetItem(royal.Item);
		RoyalData->SetOwner(royal.Owner);

		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, FString::Printf(TEXT("Owner: %d"), royal.Owner));

		TileRoyal->AddItem(RoyalData);
	}
}