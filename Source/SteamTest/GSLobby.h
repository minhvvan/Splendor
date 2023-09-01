// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "GSLobby.generated.h"

/**
 * 
 */
UCLASS()
class STEAMTEST_API AGSLobby : public AGameState
{
	GENERATED_BODY()
	
public:
	void UpdatePlayerList();

private:

	
};
