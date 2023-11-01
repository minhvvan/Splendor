// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "STGameModePlay.generated.h"

/**
 * 
 */
UCLASS()
class STEAMTEST_API ASTGameModePlay : public AGameMode
{
	GENERATED_BODY()
	
public:
	ASTGameModePlay();

	UFUNCTION()
	void SwapPlayerControllers(APlayerController* OldPC, APlayerController* NewPC) override;

	UFUNCTION()
	void InitPlayerTurn(APlayerController* Player, bool bFirst);

	virtual void StartPlay() override;

	virtual void StartMatch() override;

	//!-----------Token-----------------------
	UFUNCTION()
	void SetTokenSpawnLoc(TArray<class AToken*>& Tokens);

	UFUNCTION()
	void TokenClicked(class AToken* ClickedToken, int cnt, bool bAble);

	UFUNCTION()
	void PossessTokens(APlayerController* PC, bool bFirst);

	UFUNCTION()
	void RestoreTokens(FRestroeTokens Restore, bool bFirst);

	//!-----------------Scroll---------------------
	UFUNCTION()
	void GiveScroll(APlayerController* player);

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
