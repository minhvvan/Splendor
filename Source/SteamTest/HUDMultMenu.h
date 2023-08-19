// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDMultMenu.generated.h"

/**
 * 
 */
UCLASS()
class STEAMTEST_API UHUDMultMenu : public UUserWidget
{
	GENERATED_BODY()
		
protected:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UButton* BtnHostGame;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UButton* BtnSearchGame;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UButton* BtnConnection;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* TxtConnection;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UButton* BtnBack;
protected:
	virtual void NativeOnInitialized();

private:
	UFUNCTION(BlueprintCallable)
	void HostGameClicked();

	UFUNCTION(BlueprintCallable)
	void SearchGameClicked();

	UFUNCTION(BlueprintCallable)
	void ConnectionClicked();

	UFUNCTION(BlueprintCallable)
	void BackClicked();

	UFUNCTION(BlueprintCallable)
	void SetConnectionText();
	
public:
	
};
