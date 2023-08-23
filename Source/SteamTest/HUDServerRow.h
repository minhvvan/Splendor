// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDServerRow.generated.h"

/**
 * 
 */
UCLASS()
class STEAMTEST_API UHUDServerRow : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnInitialized();

private:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UButton* BtnServerRow;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* TxtServerName;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* TxtNumPlayer;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* TxtPing;


public:
	void SetServerName(FString name);
	void SetNumPlayer(int NumPlayer, int maxPlayer);
	void SetPing(int ping);

	UFUNCTION(BlueprintCallable)
	void ClickedRow();
};
