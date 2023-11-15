// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GlobalEnum.h"
#include "CostData.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class STEAMTEST_API UCostData : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	ETokenColor GetColor() { return color; };

	UFUNCTION()
	void SetColor(ETokenColor c) { color = c; };

	UFUNCTION(BlueprintCallable)
	int GetNum() { return num; };

	UFUNCTION()
	void SetNum(int n) { num = n; };

private:
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	ETokenColor color;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	int num;
};
