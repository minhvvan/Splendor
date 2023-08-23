// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDServerRow.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "SteamTestGameInstance.h"

void UHUDServerRow::NativeOnInitialized()
{
	BtnServerRow->OnClicked.AddDynamic(this, &UHUDServerRow::ClickedRow);
}

void UHUDServerRow::SetServerName(FString name)
{
	TxtServerName->SetText(FText::FromString(name));
}

void UHUDServerRow::SetNumPlayer(int NumPlayer, int maxPlayer)
{
	auto text = FText::FromString(FString::FromInt(NumPlayer) + TEXT(" / ") + FString::FromInt(maxPlayer));
	TxtNumPlayer->SetText(text);
}

void UHUDServerRow::SetPing(int ping)
{
	auto text = FText::FromString(FString::FromInt(ping) + TEXT(" ms"));
	TxtPing->SetText(text);
}

void UHUDServerRow::ClickedRow()
{
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("clicked")));

	if (auto GameInstance = Cast<USteamTestGameInstance>(GetGameInstance()))
	{
		auto idx = GetParent()->GetChildIndex(this);
		GameInstance->JoinSession(idx);
	}
}
