// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDSelectRoyal.generated.h"

/**
 * 
 */
UCLASS()
class STEAMTEST_API UHUDSelectRoyal : public UUserWidget
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
	class UTileView* TileRoyal;

protected:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class URoyalData> RoyalDataClass;

public:
	UFUNCTION()
	void SetScore(int score);

	UFUNCTION()
	void SetCrown(int crown);

	UFUNCTION()
	void SetScroll(int scroll);

	UFUNCTION()
	void SetRoyal();
};
