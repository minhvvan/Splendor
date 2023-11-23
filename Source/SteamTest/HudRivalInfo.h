// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HudRivalInfo.generated.h"

/**
 * 
 */
UCLASS()
class STEAMTEST_API UHudRivalInfo : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* TxtScore;	
	
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* TxtCrown;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* TxtScroll;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTileView* TVScore;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTileView* TVBonus;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTileView* TVToken;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UCostData> ColorDataClass;

public:
	UFUNCTION(BlueprintCallable)
	void SetScore(int score);	
	
	UFUNCTION(BlueprintCallable)
	void SetScroll(int scroll);	
	
	UFUNCTION(BlueprintCallable)
	void SetCrown(int crown);


	UFUNCTION(BlueprintCallable)
	void AddScroeList(ETokenColor color, int cnt);

	UFUNCTION(BlueprintCallable)
	void AddBonusList(ETokenColor color, int cnt);

	UFUNCTION(BlueprintCallable)
	void AddTokenList(ETokenColor color, int cnt);

protected:
	virtual void NativeOnInitialized();
};
