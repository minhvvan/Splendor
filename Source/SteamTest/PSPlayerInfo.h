// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PSPlayerInfo.generated.h"

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
	void SetMyTrun(bool flag) { MyTurn = flag; };

	UFUNCTION()
	bool GetMyTurn() { return MyTurn; };


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

protected:
	UFUNCTION()
	void CopyProperties(class APlayerState* PlayerState) override;

	UFUNCTION()
	void OverrideWith(class APlayerState* PlayerState) override;

private:
	UPROPERTY(Replicated)
	FString PName;

	UPROPERTY(Replicated)
	bool MyTurn;

	UPROPERTY(Replicated)
	int TokenNumRed;

	UPROPERTY(Replicated)
	int TokenNumGreen;

	UPROPERTY(Replicated)
	int TokenNumBlue;

	UPROPERTY(Replicated)
	int TokenNumWhite;

	UPROPERTY(Replicated)
	int TokenNumBlack;

	UPROPERTY(Replicated)
	int TokenNumGold;

	UPROPERTY(Replicated)
	int TokenNumPearl;
};
