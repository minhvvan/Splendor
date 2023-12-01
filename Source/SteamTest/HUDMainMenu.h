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
	class UTextBlock* TxtMessage;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UButton* BtnPlay;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UButton* BtnQuitGame;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UEditableText* EdtPlayerName;

	UPROPERTY(VisibleAnywhere, Transient, meta = (BindWidgetAnim))
	class UWidgetAnimation* MessageAnim;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class USoundBase* FailedSound;

protected:
	virtual void NativeOnInitialized();

private:
	UFUNCTION(BlueprintCallable)
	void PlayGameClicked();

	UFUNCTION(BlueprintCallable)
	void QuitGameClicked();

	UFUNCTION(BlueprintCallable)
	void ChangedPlayerName(const FText& Text, ETextCommit::Type CommitMethod);

	UFUNCTION(BlueprintCallable)
	void RenderMessage();

public:
	void SetPlayerName(FString& name);
};
