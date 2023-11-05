// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDTokenHolder.generated.h"

/**
 * 
 */
UCLASS()
class STEAMTEST_API UHUDTokenHolder : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnInitialized() override;
	
public:
	UFUNCTION()
	void SetTokenNum(enum ETokenColor type, int score);
	
	UFUNCTION()
	void UpdateTokenNum(class APSPlayerInfo* ps);

protected:
	//!------------Token--------------
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* TxtTokenRed;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* TxtTokenGreen;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* TxtTokenBlue;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* TxtTokenWhite;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* TxtTokenBlack;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* TxtTokenGold;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* TxtTokenPearl;

private:
	UPROPERTY()
	class APSPlayerInfo* PS;
};
