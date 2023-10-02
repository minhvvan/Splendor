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
	void SetPlayerTurn(APlayerController* Player, bool bFirst);

	virtual void StartPlay() override;

	virtual void StartMatch() override;

	TArray<FVector> GetTokenSpawnLoc(const TArray<class AToken*>& Tokens);

	UFUNCTION()
	void TokenClicked(class AToken* ClickedToken);


private:
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class ATileManager* TileManager;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class ATokenManager* TokenManager;
};
