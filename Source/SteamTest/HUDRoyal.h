// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GlobalEnum.h"
#include "HUDRoyal.generated.h"

/**
 * 
 */
UCLASS()
class STEAMTEST_API UHUDRoyal : public UUserWidget
{
	GENERATED_BODY()
	
	
protected:
	virtual void NativeOnInitialized();

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTileView* TileItem;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* TxtScore;	
	
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* TxtOwner;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UBorder* BorderFrame;
	
public:
	//!-----------Setter--------------
	UFUNCTION(BlueprintCallable)
	void SetScore(int score);

	UFUNCTION(BlueprintCallable)
	void SetItem(EItem item);

	UFUNCTION(BlueprintCallable)
	void SetOwner(int owner);

	UFUNCTION(BlueprintCallable)
	void OnClicked(const FGeometry& Geometry, const FPointerEvent& MouseEvent);

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UItemData> ItemDataClass;

	UPROPERTY()
	int Score;

	UPROPERTY()
	EItem Item;
};
