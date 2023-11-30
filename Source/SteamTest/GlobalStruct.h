// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "GlobalEnum.h"
#include "GlobalConst.h"
#include "GlobalStruct.generated.h"

USTRUCT(Atomic, BlueprintType)
struct FTokenCount
{
	GENERATED_USTRUCT_BODY()

public:
	FTokenCount() : Key(ETokenColor::E_End), Value(0) {};

	FTokenCount(ETokenColor key, int value) : Key(key), Value(value) {};

	UPROPERTY(EditAnywhere)
	ETokenColor Key;

	UPROPERTY(EditAnywhere)
	int Value;
};

USTRUCT(Atomic, BlueprintType)
struct FTokenCountList
{
	GENERATED_USTRUCT_BODY()
	
public:
	void Init()
	{
		for (ETokenColor color : TEnumRange<ETokenColor>())
		{
			TokenCnt.Add({ color, 0 });
		}
	}

	int& operator[] (ETokenColor color)
	{
		for (int i = 0; i < TokenCnt.Num(); i++)
		{
			if(this->TokenCnt[i].Key == color) return this->TokenCnt[i].Value;
		}

		return temp;
	}

	const int& operator[] (ETokenColor color) const
	{
		for (int i = 0; i < TokenCnt.Num(); i++)
		{
			if (this->TokenCnt[i].Key == color) return this->TokenCnt[i].Value;
		}

		return temp;
	}

	int Num()
	{
		int total = 0;
		for (auto token : TokenCnt)
		{
			total += token.Value;
		}

		return total;
	}

	const TArray<FTokenCount>& Get()
	{
		return TokenCnt;
	}

	void Clear()
	{
		for (int i = 0; i < TokenCnt.Num(); i++)
		{
			this->TokenCnt[i].Value = 0;
		}
	}

private:
	UPROPERTY()
	TArray<FTokenCount> TokenCnt;

	int temp;
};

USTRUCT(BlueprintType)
struct FCardInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Info")
	int key;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Info")
	ECardTier tier;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Info")
	int score;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Info")
	int bonus;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Info")
	int crown;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Info")
	ETokenColor color;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Info")
	TArray<FTokenCount> cost;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Info")
	TArray<EItem> item;

	bool operator== (FCardInfo info)
	{
		return this->key == info.key;
	}
};

USTRUCT(BlueprintType)
struct FTokenIdxColor
{
	GENERATED_USTRUCT_BODY()

public:
	FTokenIdxColor() : Idx(0), Color(ETokenColor::E_End) {};

	FTokenIdxColor(int idx, ETokenColor color) : Idx(idx), Color(color) {};

	UPROPERTY(EditAnywhere)
	int Idx;
	
	UPROPERTY(EditAnywhere)
	ETokenColor Color;

	bool operator== (const FTokenIdxColor& rhs)
	{
		return this->Idx == rhs.Idx && this->Color == rhs.Color;
	}

	bool operator== (const FTokenIdxColor& rhs) const
	{
		return this->Idx == rhs.Idx && this->Color == rhs.Color;
	}

	bool operator< (const FTokenIdxColor& rhs) const
	{
		return this->Idx < rhs.Idx;
	}
};

USTRUCT(BlueprintType)
struct FRoyalInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	FRoyalInfo() : Key(0), Score(0), Item(EItem::E_End), Owner(0) {};

	FRoyalInfo(int score, EItem item, int owner) : Score(score), Item(item), Owner(owner) {};

	UPROPERTY(EditAnywhere)
	int Key;

	UPROPERTY(EditAnywhere)
	int Score;
	
	UPROPERTY(EditAnywhere)
	EItem Item;

	UPROPERTY(EditAnywhere)
	int Owner;
};


UCLASS()
class STEAMTEST_API UGlobalStruct : public UObject
{
	GENERATED_BODY()
	
};
