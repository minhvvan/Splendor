// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDDummy.generated.h"

/**
 * 
 */
UCLASS()
class STEAMTEST_API UHUDDummy : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnInitialized();

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* TxtNum;

public:
	UFUNCTION()
	void SetRemainNum(int num);
};
