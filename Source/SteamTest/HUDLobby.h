// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDLobby.generated.h"

/**
 * 
 */
UCLASS()
class STEAMTEST_API UHUDLobby : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UButton* BtnFirstPlayer;	
	
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* TxtFirstPlayer;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UButton* BtnSecondPlayer;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* TxtSecondPlayer;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UButton* BtnStartGame;	
	
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UButton* BtnSubmit;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UMultiLineEditableText* EdtChat;
protected:
	virtual void NativeOnInitialized();

private:
	UFUNCTION(BlueprintCallable)
	void FirstPlayerClicked();

	UFUNCTION(BlueprintCallable)
	void SecondPlayerClicked();

	UFUNCTION(BlueprintCallable)
	void StartGameClicked();

	UFUNCTION(BlueprintCallable)
	void OnChatTextCommitted(const FText& Text, ETextCommit::Type CommitMethod);

	//이렇게 하는게 맞나 모르겠다
	class APCLobby* MainPC;

public:
	void SetPC(APlayerController* PC);

	void SetFirstText(FString text);
	void SetSecondText(FString text);
};
