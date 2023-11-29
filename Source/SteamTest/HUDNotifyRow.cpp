// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDNotifyRow.h"
#include "Components/TextBlock.h"

FORCEINLINE void UHUDNotifyRow::SetText(const FString& Chat)
{
	TxtName->SetText(FText::FromString(Chat));
}