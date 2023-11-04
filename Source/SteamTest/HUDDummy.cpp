// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDDummy.h"
#include "Components/TextBlock.h"

void UHUDDummy::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UHUDDummy::SetRemainNumText(int num)
{
	if (TxtNum && IsValid(TxtNum))
	{
		TxtNum->SetText(FText::AsNumber(num));
	}
}
