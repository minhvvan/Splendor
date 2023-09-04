// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "Net/UnrealNetwork.h"
#include "GSLobby.generated.h"


UCLASS()
class STEAMTEST_API AGSLobby : public AGameState
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	bool SetFirstPlayer(APCLobby* pc);

	UFUNCTION()
	bool SetSecondPlayer(APCLobby* pc);

	UFUNCTION()
	APCLobby* GetFirstPlayer() { return FirstPlayer; };

	UFUNCTION()
	APCLobby* GetSecondPlayer() { return SecondPlayer; };

	UFUNCTION()
	bool GetCanStart() { return bCanStart; };

private:
	UPROPERTY()
	class APCLobby* FirstPlayer;

	UPROPERTY()
	class APCLobby* SecondPlayer;

	UPROPERTY()
	bool bCanStart;

	void checkCanStart();
};
