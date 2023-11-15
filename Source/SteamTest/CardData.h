// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GlobalEnum.h"
#include "GlobalStruct.h"
#include "CardData.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class STEAMTEST_API UCardData : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	FCardInfo GetData() { return Info; };

	UFUNCTION(BlueprintCallable)
	void SetData(FCardInfo info) { Info = info; };

private:
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	FCardInfo Info;
};