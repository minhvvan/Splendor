// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "CardManager.generated.h"

class ACard;

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
enum class EColor : uint8
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
ENUM_RANGE_BY_COUNT(EColor, EColor::E_End);


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


USTRUCT()
struct FCardInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Info")
	ECardTier tier;

	UPROPERTY(EditAnywhere, Category = "Info")
	int score;

	UPROPERTY(EditAnywhere, Category = "Info")
	int bonus;

	UPROPERTY(EditAnywhere, Category = "Info")
	int crown;

	UPROPERTY(EditAnywhere, Category = "Info")
	EColor color;

	UPROPERTY(EditAnywhere, Category = "Info")
	TMap<EColor, int> cost;

	UPROPERTY(EditAnywhere, Category = "Info")
	TArray<EItem> item;
};


UCLASS()
class STEAMTEST_API ACardManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACardManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	ACard* GetCardByTier(ECardTier tier);

	//!------------Init-----------------
	UFUNCTION()
	void InitData();

	UFUNCTION()
	void SpawnCards();
	
private:
	//!----------------Card--------------
	UPROPERTY()
	TArray<ACard*> TierOne;
	
	UPROPERTY()
	TArray<ACard*> TierTwo;
	
	UPROPERTY()
	TArray<ACard*> TierThree;

	UPROPERTY()
	TArray<FCardInfo> TierOneInfos;

	UPROPERTY()
	TArray<FCardInfo> TierTwoInfos;

	UPROPERTY()
	TArray<FCardInfo> TierThreeInfos;

	//!-------------Data--------
	UPROPERTY()
	class UDataTable* CardData;
};
