// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GlobalConst.generated.h"

/**
 * 
 */
UCLASS()
class STEAMTEST_API UGlobalConst : public UObject
{
	GENERATED_BODY()
	
public:
	static const FVector4 RedColor;
	static const FVector4 GreenColor;
	static const FVector4 BlueColor;
	static const FVector4 WhiteColor;
	static const FVector4 BlackColor;
	static const FVector4 PearlColor;

	static const FVector4 StrongRedColor;
	static const FVector4 StrongGreenColor;
	static const FVector4 StrongBlueColor;
	static const FVector4 StrongWhiteColor;
	static const FVector4 StrongBlackColor;
	static const FVector4 StrongPearlColor;

	//!------------------Msg----------------------
	static const FString MsgNotTurn;
	static const FString MsgThreeToken;
	static const FString MsgUnableGold;
	static const FString MsgOneGold;
	static const FString MsgNotContiue;
	static const FString MsgNotSelect;
	static const FString MsgUnableBuy;
	static const FString MsgCanNotTake;
	static const FString MsgNoPouch;

	//!------------------util----------------------
	static const int FirstPlayer;
	static const int SecondPlayer;
	static const FString SuffixTurnText;

	//!------------------Position----------------------
	static const FVector RivalTokenPos;
	static const FVector OwnTokenPos;
};
