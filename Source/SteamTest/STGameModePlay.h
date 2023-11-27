// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "STGameModePlay.generated.h"

/**
 * 
 */
class APSPlayerInfo;

UCLASS()
class STEAMTEST_API ASTGameModePlay : public AGameMode
{
	GENERATED_BODY()
	
public:
	ASTGameModePlay();

	UFUNCTION()
	void SwapPlayerControllers(APlayerController* OldPC, APlayerController* NewPC) override;
	
	virtual void PostLogin(APlayerController* NewPlayer) override;

	virtual void PostSeamlessTravel() override;

	virtual void StartPlay() override;

	virtual void StartMatch() override;

	virtual void InitGameState() override;

	virtual void HandleMatchHasEnded() override;

	UFUNCTION()
	void PrintBonus();

	UFUNCTION()
	void PrintToken();	

	//!-----------Turn-----------------------
	UFUNCTION()
	void InitPlayerTurn(APlayerController* Player);

	UFUNCTION()
	void EndCurrentTurn();

	UFUNCTION()
	void EndGame(APSPlayerInfo* winner);

	//!-----------Token-----------------------
	UFUNCTION()
	void SetTokenSpawnLoc(TArray<class AToken*>& Tokens);

	UFUNCTION()
	void PossessTokens(APlayerController* PC, const TArray<FTokenIdxColor>& SelectedTokens);

	UFUNCTION()
	void RestoreTokens(const FTokenCountList& Restore, APlayerController* PC);

	UFUNCTION()
	void TakeToken(APlayerController* PC, ETokenColor color);	
	
	UFUNCTION()
	void GetTokenByIdx(APlayerController* PC, int idx);	
	
	UFUNCTION()
	void FillToken(APlayerController* PC);

	UFUNCTION()
	bool CheckGiveScroll(const TArray<FTokenIdxColor>& SelectedTokens);

	//!-----------------Scroll---------------------
	UFUNCTION()
	void GiveScroll(APlayerController* player);	
	
	UFUNCTION()
	void GetScroll(APlayerController* player);

	//!-----------------Card---------------------
	UFUNCTION()
	void BuyCard(APlayerController* player, FCardInfo cardInfo, const FTokenCountList& UseTokens);
	
	UFUNCTION()
	void ChangeCard(FCardInfo cardInfo);

	//!-----------Item----------------------
	UFUNCTION()
	void UseItem(FCardInfo cardInfo, APlayerController* player);


	//!-----------Bonus----------------------
	UFUNCTION()
	void AddBonus(ETokenColor color, APlayerController* player);


	//!-----------Score----------------------
	UFUNCTION()
	void AddScore(ETokenColor color, int score, APlayerController* player);

	//!-----------Crown----------------------
	void UpdateRoyal(int key, APlayerController* player);


protected:
	virtual void HandleSeamlessTravelPlayer(AController*& C) override;

private:
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class ATileManager* TileManager;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class ATokenManager* TokenManager;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class ATurnManager* TurnManager;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class ACardManager* CardManager;
};
