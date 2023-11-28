// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDTurnAlert.h"
#include "Components/TextBlock.h"
#include "GlobalConst.h"

void UHUDTurnAlert::NativeOnInitialized()
{

}

void UHUDTurnAlert::SetTurnText(FString PlayerName)
{
	PlayerName.Append(UGlobalConst::SuffixTurnText);
	TxtTurn->SetText(FText::FromString(PlayerName));
}

void UHUDTurnAlert::AlertChangedTurn(FString PlayerName)
{
	SetTurnText(PlayerName);
	if (TextAppear) PlayAnimation(TextAppear);
	if (ChangeSound) PlaySound(ChangeSound);
}
