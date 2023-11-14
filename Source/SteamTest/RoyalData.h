// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GlobalEnum.h"
#include "RoyalData.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class STEAMTEST_API URoyalData : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	int GetScore() { return Score; };

	UFUNCTION()
	void SetScore(int score) { Score = score; };

	UFUNCTION(BlueprintCallable)
	EItem GetItem() { return Item; };

	UFUNCTION()
	void SetItem(EItem item) { Item = item; };

	UFUNCTION(BlueprintCallable)
	int GetOwner() { return Owner; };

	UFUNCTION()
	void SetOwner(int owner) { Owner = owner; };	
	
	UFUNCTION(BlueprintCallable)
	int GetKey() { return Key; };

	UFUNCTION()
	void SetKey(int key) { Key = key; };

private:
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	int Key;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	int Score;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	EItem Item;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	int Owner;
};
