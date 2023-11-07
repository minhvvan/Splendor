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
	void InitData();

	UFUNCTION()
	void InitCards();	
	
	UFUNCTION()
	void InitDummy();


	//!-------------Card----------
	UFUNCTION()
	void DestoryCard(FVector loc, ECardTier tier, ACard* card);

	UFUNCTION()
	void SetCurrentSelectedCard(ACard* Card);

	UFUNCTION()
	void ChangeCard();
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

	UPROPERTY()
	TArray<FCardInfo> TierOneInfos;

	UPROPERTY()
	TArray<FCardInfo> TierTwoInfos;

	UPROPERTY()
	TArray<FCardInfo> TierThreeInfos;	

	UPROPERTY()
	TWeakObjectPtr<ACard> CurrentClickCard;
	
	//!------Dummy--------
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ACardDummy> DummyClass;

	UPROPERTY()
	TArray<class ACardDummy*> CardDummies;

	//!-------------Data--------
	UPROPERTY()
	class UDataTable* CardData;

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
