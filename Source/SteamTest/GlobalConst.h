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
};
