// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GlobalEnum.h"
#include "TileData.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class STEAMTEST_API UTileData : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	ETokenColor GetColor() { return color; };

	UFUNCTION()
	void SetColor(ETokenColor c) { color = c; };

	UFUNCTION(BlueprintCallable)
	int GetIdx() { return idx; };

	UFUNCTION()
	void SetIdx(int n) { idx = n; };

	UFUNCTION(BlueprintCallable)
	bool GetEnable() { return enable; };

	UFUNCTION()
	void SetEnable(bool b) { enable = b; };

private: 	
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	ETokenColor color;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	int idx;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	bool enable;
};
