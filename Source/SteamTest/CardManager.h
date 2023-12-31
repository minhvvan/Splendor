// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CardManager.generated.h"

class ACard;
class ACardDummy;
struct FCardInfo;

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
	void InitCards();	
	
	UFUNCTION()
	void InitDummy();


	//!-------------Card----------
	UFUNCTION()
	void DestoryCard(FVector loc, ECardTier tier, ACard* card);

	UFUNCTION()
	void ChangeCard(FCardInfo cardInfo);

	UFUNCTION()
	TArray<ACard*>& GetCardListByTier(ECardTier tier);

private:
	//!----------------Card--------------
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ACard> CardClass;

	UPROPERTY()
	TArray<ACard*> TierOne;
	
	UPROPERTY()
	TArray<ACard*> TierTwo;
	
	UPROPERTY()
	TArray<ACard*> TierThree;
	
	//!------Dummy--------
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ACardDummy> DummyClass;

	UPROPERTY()
	TArray<class ACardDummy*> CardDummies;

	//!-----------Position--------
	UPROPERTY()
	FVector StartOneTier;

	UPROPERTY()
	FVector StartTwoTier;

	UPROPERTY()
	FVector StartThreeTier;

	UPROPERTY()
	FVector DummyOneTier;

	UPROPERTY()
	FVector DummyTwoTier;

	UPROPERTY()
	FVector DummyThreeTier;
};
