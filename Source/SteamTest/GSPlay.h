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
	UPROPERTY()
	int GlobalScroll;

	UFUNCTION()
	void InitState();

	UFUNCTION()
	int GetGlobalScroll() { return GlobalScroll; };

	UFUNCTION()
	void AddGlobalScroll(int num) { GlobalScroll += num; };

protected:
};
