// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "GSPlay.generated.h"

/**
 * 
 */
UCLASS()
class STEAMTEST_API AGSPlay : public AGameState
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void SetFirstPlayer(APlayerController* Player);

	UFUNCTION()
	void SetSecondPlayer(APlayerController* Player);

	UFUNCTION()
	bool IsFirstPlayer(class APCPlay* Player) { return FirstPlayer == Player; };

private:
	UPROPERTY()
	class APCPlay* FirstPlayer;

	UPROPERTY()
	class APCPlay* SecondPlayer;
};
