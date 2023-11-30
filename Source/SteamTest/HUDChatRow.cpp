// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDChatRow.h"
#include "Components/TextBlock.h"

void UHUDChatRow::SetText(const FString& Chat)
{
	TxtChat->SetText(FText::FromString(Chat));
}