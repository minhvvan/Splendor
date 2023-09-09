// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDMainMenu.generated.h"

/**
 * 
 */
UCLASS()
class STEAMTEST_API UHUDMainMenu : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UButton* BtnPlay;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UButton* BtnQuitGame;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UEditableText* EdtPlayerName;
protected:
	virtual void NativeOnInitialized();

private:
	UFUNCTION(BlueprintCallable)
	void PlayGameClicked();

	UFUNCTION(BlueprintCallable)
	void QuitGameClicked();

	UFUNCTION(BlueprintCallable)
	void ChangedPlayerName(const FText& Text, ETextCommit::Type CommitMethod);

public:
	void SetPlayerName(FString& name);
};
