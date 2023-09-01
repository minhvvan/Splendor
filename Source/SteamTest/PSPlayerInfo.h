// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PSPlayerInfo.generated.h"

/**
 * 
 */
UCLASS()
class STEAMTEST_API APSPlayerInfo : public APlayerState
{
	GENERATED_BODY()
	
public:
	APSPlayerInfo();

	FString GetPlayerName() const { return PlayerName; };
	void SetPlayerName(FString name) { PlayerName = name; };

private:
	UPROPERTY()
	FString PlayerName;
};
