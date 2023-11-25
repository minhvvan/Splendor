// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDEndGame.generated.h"

/**
 * 
 */
UCLASS()
class STEAMTEST_API UHUDEndGame : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnInitialized();

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UButton* BtnExit;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* TxtWin;

	//!---------First--------------------------
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* TxtFirstPName;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* TxtFirstScore;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* TxtFirstCrown;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* TxtFirstScroll;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTileView* TVFirstColorScore;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTileView* TVFirstBonus;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTileView* TVFirstToken;

	//!---------Second--------------------------
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* TxtSecondPName;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* TxtSecondScore;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* TxtSecondCrown;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* TxtSecondScroll;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTileView* TVSecondColorScore;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTileView* TVSecondBonus;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTileView* TVSecondToken;

	//!---------Second--------------------------
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UCostData> CostDataClass;

	UFUNCTION()
	void SetColorScore(APSPlayerInfo* PS);

	UFUNCTION()
	void SetBonus(APSPlayerInfo* PS);

	UFUNCTION()
	void SetToken(APSPlayerInfo* PS);

	//!---------Second--------------------------
	UFUNCTION()
	void ExitGame();
};
