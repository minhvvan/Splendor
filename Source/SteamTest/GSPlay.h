// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "GlobalStruct.h"
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
	void InitState();

	UFUNCTION()
	int GetGlobalScroll() { return GlobalScroll; };

	UFUNCTION()
	void AddGlobalScroll(int num) { GlobalScroll += num; };

	UFUNCTION()
	TArray<FTokenIdxColor>& GetRemainTokenIdx() { return RemainTokenIdx; };

	UFUNCTION()
	void RemoveTokenIdx(int idx, ETokenColor color);

	UFUNCTION()
	void AddTokenIdx(int idx, ETokenColor color);

protected:
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const;

	UPROPERTY()
	int GlobalScroll;

	UPROPERTY(Replicated)
	TArray<FTokenIdxColor> RemainTokenIdx;
};
