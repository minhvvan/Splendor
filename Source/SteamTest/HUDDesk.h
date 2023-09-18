// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDCardHolder.h"
#include "HUDDesk.generated.h"

/**
 * 
 */
UCLASS()
class STEAMTEST_API UHUDDesk : public UUserWidget
{
	GENERATED_BODY()
	

protected:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UButton* BtnGetToken;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UButton* BtnFillToken;


	UPROPERTY(VisibleAnywhere, meta = (BindWidgetOptional))
	class UHUDCardHolder* CDHRed;

	//UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	//class UHUDCardHolder* CDHGreen;

	//UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	//class UHUDCardHolder* CDHBlue;

	//UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	//class UHUDCardHolder* CDHWhite;

	//UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	//class UHUDCardHolder* CDHBlack;


	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* TxtScore;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* TxtCrown;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* TxtScroll;	
	
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* TxtTurn;
	
	virtual void NativeOnInitialized();

public:
	void SetScoreTxt(int score);
	void SetCrownTxt(int crown);
	void SetScrollTxt(int scroll);
	void SetTurnTxt(FString turn);

private:
	UFUNCTION(BlueprintCallable)
	void GetTokenClicked();

	UFUNCTION(BlueprintCallable)
	void FilTokenClicked();
};
