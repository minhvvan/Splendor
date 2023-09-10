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
	void SetFirstPlayer(APlayerController* Player);
	void SetSecondPlayer(APlayerController* Player);

private:
	UPROPERTY()
	class APCPlay* FirstPlayer;

	UPROPERTY()
	class APCPlay* SecondPlayer;
};
