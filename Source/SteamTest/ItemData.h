// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CardManager.h"
#include "ItemData.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class STEAMTEST_API UItemData : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	EItem GetItem() { return item; };

	UFUNCTION()
	void SetItem(EItem i) { item = i; };

private:
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	EItem item;
};
