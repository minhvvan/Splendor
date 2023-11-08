// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDAnyColor.generated.h"

/**
 * 
 */
UCLASS()
class STEAMTEST_API UHUDAnyColor : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UButton* BtnRed;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UButton* BtnGreen;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UButton* BtnBlue;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UButton* BtnWhite;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UButton* BtnBlack;

protected:
	virtual void NativeOnInitialized();


public:
	UFUNCTION()
	void RedClicked();

	UFUNCTION()
	void GreenClicked();

	UFUNCTION()
	void BlueClicked();

	UFUNCTION()
	void WhiteClicked();

	UFUNCTION()
	void BlackClicked();

	UFUNCTION()
	void SetInfo(const FCardInfo& cardInfo);

	UFUNCTION()
	void CallUpdate(ETokenColor color);

private:
	UPROPERTY()
	int score;
};
