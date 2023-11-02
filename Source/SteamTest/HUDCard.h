// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CardManager.h"
#include "HUDCard.generated.h"

/**
 * 
 */
UCLASS()
class STEAMTEST_API UHUDCard : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnInitialized();

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UBorder* BorderFrame;
	
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UBorder* BorderColor;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UBorder* BorderFlag;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTileView* TileCost;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* TxtScore;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* TxtCrown;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* TxtBonus;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UImage* ImgCrown;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UImage* ImgToken;
public:
	UFUNCTION()
	void SetInfo(struct FCardInfo& info);

	UFUNCTION()
	void SetBonus(ETokenColor color, int bonus);

	UFUNCTION()
	void SetCost(TMap<ETokenColor, int> cost);	
	
	UFUNCTION()
	void SetCrown(int crown);	
	
	UFUNCTION()
	void SetScore(int score);

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UHUDCost> CostClass;
	
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UCardData> CostDataClass;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TMap<ETokenColor, UTexture2D*> TokenTexture;
};