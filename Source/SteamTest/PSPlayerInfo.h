// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PSPlayerInfo.generated.h"

DECLARE_MULTICAST_DELEGATE(FDeleChangeScroll)
DECLARE_MULTICAST_DELEGATE(FDeleOverToken)
DECLARE_MULTICAST_DELEGATE(FDeleChangeToken)

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
	void AddToken(enum ETokenType type);

	UFUNCTION()
	void SetToken(enum ETokenType type, int num);

	UFUNCTION()
	int GetTokenRed() { return TokenNumRed; };

	UFUNCTION()
	int GetTokenGreen() { return TokenNumGreen; };

	UFUNCTION()
	int GetTokenBlue() { return TokenNumBlue; };

	UFUNCTION()
	int GetTokenWhite() { return TokenNumWhite; };

	UFUNCTION()
	int GetTokenBlack() { return TokenNumBlack; };

	UFUNCTION()
	int GetTokenGold() { return TokenNumGold; };

	UFUNCTION()
	int GetTokenPearl() { return TokenNumPearl; };

	UFUNCTION()
	int GetTokenNum(ETokenType type);

	UFUNCTION()
	void UpdateTotalToken(int num) { TotalTokenNum += num; };

	UFUNCTION()
	void PrintToken();

	//!---------------Scroll---------------
	UFUNCTION()
	void AddScroll(int num);

	UFUNCTION()
	int GetScroll() { return ScrollNum; };

	UFUNCTION()
	void OnRep_Scroll();

	UFUNCTION()
	void OnRep_TotalTokenNum();

	//!-------------Delegate-----------
	FDeleChangeScroll OnScrollChanged;
	FDeleOverToken OnOverToken;
	FDeleChangeToken OnChangeToken;

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
	int TokenNumRed;

	UPROPERTY(replicated)
	int TokenNumGreen;

	UPROPERTY(replicated)
	int TokenNumBlue;

	UPROPERTY(replicated)
	int TokenNumWhite;

	UPROPERTY(replicated)
	int TokenNumBlack;

	UPROPERTY(replicated)
	int TokenNumGold;

	UPROPERTY(replicated)
	int TokenNumPearl;

	UPROPERTY(ReplicatedUsing = OnRep_TotalTokenNum)
	int TotalTokenNum;

	UPROPERTY(ReplicatedUsing = OnRep_Scroll)
	int ScrollNum;
};
