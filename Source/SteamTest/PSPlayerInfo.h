// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "GlobalStruct.h"
#include "PSPlayerInfo.generated.h"

DECLARE_MULTICAST_DELEGATE(FDeleChangeScroll)
DECLARE_MULTICAST_DELEGATE(FDeleOverToken)
DECLARE_MULTICAST_DELEGATE(FDeleChangeToken)
DECLARE_MULTICAST_DELEGATE(FDeleChangeBonus)
DECLARE_MULTICAST_DELEGATE(FDeleChangeScore)
DECLARE_MULTICAST_DELEGATE(FDeleChangeColorScore)
DECLARE_MULTICAST_DELEGATE(FDeleChangeCrown)

UCLASS()
class STEAMTEST_API APSPlayerInfo : public APlayerState
{
	GENERATED_BODY()
	
public:
	APSPlayerInfo();

	UFUNCTION()
	FString GetPName() const { return PName; };

	UFUNCTION()
	void SetPName(FString name) { PName = name; };

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	UFUNCTION()
	void SetBFirst(bool flag) { bFirst = flag; };

	UFUNCTION()
	bool GetBFirst() { return bFirst; };

	//!------------------------token--------------------------------
	UFUNCTION()
	void AddToken(enum ETokenColor type, int cnt);

	UFUNCTION()
	void SetToken(enum ETokenColor type, int num);

	UFUNCTION()
	int GetTokenNum(ETokenColor type);

	UFUNCTION(Server, Reliable)
	void NotifyUpdateToken();

	UFUNCTION()
	void PrintToken();

	UFUNCTION()
	void OnRep_TokenUpdated();

	//!---------------Scroll---------------
	UFUNCTION()
	void AddScroll(int num);

	UFUNCTION()
	int GetScroll() { return ScrollNum; };

	UFUNCTION()
	void OnRep_Scroll();

	//!---------------Bonus---------------
	UFUNCTION()
	void AddBonus(enum ETokenColor color);

	UFUNCTION()
	int GetBonusNum(ETokenColor type);

	UFUNCTION()
	void OnRep_Bonus();

	//!---------------Score---------------
	UFUNCTION()
	void AddScore(ETokenColor color, int s);

	UFUNCTION()
	int GetTotalScore() { return TotalScore; };	
	
	UFUNCTION()
	int GetScoreByColor(ETokenColor color) { return ColorScore[color]; };

	UFUNCTION()
	void OnRep_TotalScore();

	UFUNCTION()
	void OnRep_ColorScore();

	//!---------------Crown---------------
	UFUNCTION()
	void AddCrown(int crown);

	UFUNCTION()
	const int GetCrown() const { return Crown; };

	UFUNCTION()
	void OnRep_Crown();

	//!-------------Delegate-----------
	FDeleChangeScroll OnScrollChanged;
	FDeleOverToken OnOverToken;
	FDeleChangeToken OnChangeToken;
	FDeleChangeBonus OnChangeBonus;
	FDeleChangeScore OnChangeScore;
	FDeleChangeColorScore OnChangeColorScore;
	FDeleChangeCrown OnChangeCrown;

protected:
	UFUNCTION()
	virtual void CopyProperties(class APlayerState* PlayerState) override;

	UFUNCTION()
	virtual void OverrideWith(class APlayerState* PlayerState) override;

	UFUNCTION()
	virtual void ClientInitialize(class AController* C) override;

private:
	UPROPERTY(replicated)
	FString PName;

	UPROPERTY(replicated)
	bool bFirst;

	UPROPERTY(replicated)
	FTokenCountList OwnTokens;

	UPROPERTY(ReplicatedUsing = OnRep_Bonus)
	FTokenCountList OwnBonus;

	UPROPERTY(ReplicatedUsing = OnRep_ColorScore)
	FTokenCountList ColorScore;

	UPROPERTY(ReplicatedUsing = OnRep_TokenUpdated)
	bool bTokenUpdated;

	UPROPERTY(ReplicatedUsing = OnRep_TotalScore)
	int TotalScore;

	UPROPERTY(ReplicatedUsing = OnRep_Scroll)
	int ScrollNum;

	UPROPERTY(ReplicatedUsing = OnRep_Crown)
	int Crown;
};
