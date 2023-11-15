// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GlobalStruct.h"
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
	class UTileView* TileItem;

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
	//!-----------Setter--------------
	UFUNCTION(BlueprintCallable)
	void SetInfo(FCardInfo info);

	UFUNCTION(BlueprintCallable)
	void SetBonus(ETokenColor color, int bonus);

	UFUNCTION(BlueprintCallable)
	void SetCost(TArray<FTokenCount> costs);
	
	UFUNCTION(BlueprintCallable)
	void SetCrown(int crown);	
	
	UFUNCTION(BlueprintCallable)
	void SetScore(int score);

	UFUNCTION(BlueprintCallable)
	void SetItem(TArray<EItem> items);

	UFUNCTION()
	void Onclicked(const FGeometry& Geometry, const FPointerEvent& MouseEvent);

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UCostData> CostDataClass;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UItemData> ItemDataClass;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TMap<ETokenColor, UTexture2D*> TokenTexture;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	FCardInfo Info;
};
