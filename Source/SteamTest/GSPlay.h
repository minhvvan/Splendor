// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "GlobalStruct.h"
#include "GSPlay.generated.h"


UCLASS()
class STEAMTEST_API AGSPlay : public AGameState
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void InitState();

	UFUNCTION()
	int GetGlobalScroll() { return GlobalScroll; };

	UFUNCTION()
	void AddGlobalScroll(int num) { GlobalScroll += num; };

	UFUNCTION()
	void RemoveTokenIdx(int idx);

	UFUNCTION()
	int AddToken(ETokenColor color);

	UFUNCTION()
	void AddPouch(ETokenColor color, int cnt);

	UFUNCTION()
	FTokenCountList& GetPouch() { return Pouch; };
	
	UFUNCTION()
	void ClearPouch();

	UFUNCTION()
	TArray<FRoyalInfo>& GertRoylas() { return Royals; };

	UFUNCTION()
	void UpdateRoyalOwner(int key, bool bFirst);
	
	UFUNCTION()
	int GetInfoNumByTier(ECardTier tier);

	UFUNCTION()
	FCardInfo GetInfoByTier(ECardTier tier);

	UFUNCTION()
	void RemoveCurrentCardInfo(FCardInfo info);

	UFUNCTION()
	const TArray<FCardInfo>& GetCurrentInfoByTier(ECardTier tier);

	UFUNCTION()
	const TArray<ETokenColor>& GetCurrentTileState() { return TileState; };

protected:
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const;

	UPROPERTY()
	int GlobalScroll;

	UPROPERTY(Replicated)
	FTokenCountList Pouch;

	UPROPERTY(Replicated)
	TArray<FRoyalInfo> Royals;

	UPROPERTY(EditAnywhere)
	class UDataTable* RoyalData;	
	
	//!----------Card-------------
	UPROPERTY(EditAnywhere)
	class UDataTable* CardData;

	UPROPERTY(Replicated)
	TArray<FCardInfo> TierOneCurrentInfos;

	UPROPERTY(Replicated)
	TArray<FCardInfo> TierTwoCurrentInfos;

	UPROPERTY(Replicated)
	TArray<FCardInfo> TierThreeCurrentInfos;

	UPROPERTY(Replicated)
	TArray<FCardInfo> TierOneInfos;

	UPROPERTY(Replicated)
	TArray<FCardInfo> TierTwoInfos;

	UPROPERTY(Replicated)
	TArray<FCardInfo> TierThreeInfos;

	//!----------Tile-------------
	UPROPERTY(Replicated)
	TArray<ETokenColor> TileState;	
	
	UPROPERTY(Replicated)
	TArray<int> FillIdx;
};
