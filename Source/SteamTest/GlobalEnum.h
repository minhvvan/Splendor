// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GlobalEnum.generated.h"


UENUM(BlueprintType)
enum class ECardTier : uint8
{
	C_One = 0   UMETA(DisplayName = "One"),
	C_Two		UMETA(DisplayName = "Two"),
	C_Three		UMETA(DisplayName = "Three"),

	E_End,
};
ENUM_RANGE_BY_COUNT(ECardTier, ECardTier::E_End);


UENUM(BlueprintType)
enum class ETokenColor : uint8
{
	E_Red = 0   UMETA(DisplayName = "Red"),
	E_Green		UMETA(DisplayName = "Green"),
	E_Blue		UMETA(DisplayName = "Blue"),
	E_White		UMETA(DisplayName = "White"),
	E_Black		UMETA(DisplayName = "Black"),
	E_Gold		UMETA(DisplayName = "Gold"),
	E_Pearl		UMETA(DisplayName = "Pearl"),

	E_End,
};
ENUM_RANGE_BY_COUNT(ETokenColor, ETokenColor::E_End);


UENUM(BlueprintType)
enum class EItem : uint8
{
	I_RePlay = 0   UMETA(DisplayName = "RePlay"),
	I_GetToken		UMETA(DisplayName = "GetToken"),
	I_GetScroll		UMETA(DisplayName = "GetScroll"),
	I_TakeToken		UMETA(DisplayName = "TakeToken"),
	I_AnyColor		UMETA(DisplayName = "AnyColor"),

	E_End,
};
ENUM_RANGE_BY_COUNT(EItem, EItem::E_End);

UCLASS()
class STEAMTEST_API UGlobalEnum : public UObject
{
	GENERATED_BODY()
	
};
