// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDDummy.h"
#include "Components/TextBlock.h"

void UHUDDummy::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UHUDDummy::SetRemainNum(int num)
{
	TxtNum->SetText(FText::AsNumber(num));
}
