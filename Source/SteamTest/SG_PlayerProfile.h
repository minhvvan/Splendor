// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SteamTestGameInstance.h"
#include "SG_PlayerProfile.generated.h"

/**
 * 
 */
UCLASS()
class STEAMTEST_API USG_PlayerProfile : public USaveGame
{
	GENERATED_BODY()
	
public:	
	UPROPERTY()
	FPlayerProfile PlayPfofile;

	void SetPlayerName(FString name);

	UPROPERTY()
	int score;

	void Print();
};
