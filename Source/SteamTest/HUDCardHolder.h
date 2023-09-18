// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDCardHolder.generated.h"

/**
 * 
 */
UCLASS()
class STEAMTEST_API UHUDCardHolder : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	class UImage* ImgToken;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UButton* BtnBonus;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UButton* BtnScore;


	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* TxtBonus;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* TxtColorScore;

	virtual void NativeOnInitialized();

public:
	void SetScoreTxt(int score);
	void SetBonusTxt(int bonus);

	void SetImage();

	UPROPERTY(EditAnywhere)
	UTexture2D* IconImg;
};
