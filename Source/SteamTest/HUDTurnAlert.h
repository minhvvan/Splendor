// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDTurnAlert.generated.h"

/**
 * 
 */
UCLASS()
class STEAMTEST_API UHUDTurnAlert : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnInitialized();

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* TxtTurn;

	UPROPERTY(VisibleAnywhere, Transient, meta = (BindWidgetAnim))
	class UWidgetAnimation* TextAppear;

	UFUNCTION()
	void SetTurnText(FString PlayerName);

	UPROPERTY(EditAnywhere)
	class USoundBase* ChangeSound;
	
public:
	UFUNCTION()
	void AlertChangedTurn(FString PlayerName);
};
