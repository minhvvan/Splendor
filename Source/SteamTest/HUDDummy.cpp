// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDDummy.h"
#include "Components/TextBlock.h"

void UHUDDummy::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, FString::Printf(TEXT("NativeOnInitialized")));
}

void UHUDDummy::SetRemainNumText(int num)
{
	if (TxtNum && IsValid(TxtNum))
	{
		TxtNum->SetText(FText::AsNumber(num));
	}
}
