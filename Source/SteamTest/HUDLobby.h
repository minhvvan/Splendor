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
	class UTextBlock* TxtMessage;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UButton* BtnStartGame;	
	
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UButton* BtnSubmit;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UMultiLineEditableText* EdtChat;

	//!--------------SFX-----------
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class USoundBase* ClickSound;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class USoundBase* CancelSound;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class USoundBase* FailSound;

	//!--------------Anim-----------
	UPROPERTY(BlueprintReadOnly, Transient, meta = (BindWidgetAnim))
	class UWidgetAnimation* ShakeFirstBtn;

	UPROPERTY(BlueprintReadOnly, Transient, meta = (BindWidgetAnim))
	class UWidgetAnimation* FirstHoverAnim;

	UPROPERTY(BlueprintReadOnly, Transient, meta = (BindWidgetAnim))
	class UWidgetAnimation* ShakeSecondBtn;

	UPROPERTY(BlueprintReadOnly, Transient, meta = (BindWidgetAnim))
	class UWidgetAnimation* SecondHoverAnim;

	UPROPERTY(BlueprintReadOnly, Transient, meta = (BindWidgetAnim))
	class UWidgetAnimation* StartGameAnim;

	UPROPERTY(BlueprintReadOnly, Transient, meta = (BindWidgetAnim))
	class UWidgetAnimation* MessageAnim;

protected:
	virtual void NativeOnInitialized();

private:
	//!--------------First-----------
	UFUNCTION(BlueprintCallable)
	void FirstPlayerClicked();

	UFUNCTION()
	void OnHoveredFirst();

	UFUNCTION()
	void OnLeavedFirst();

	//!--------------Second-----------
	UFUNCTION(BlueprintCallable)
	void SecondPlayerClicked();

	UFUNCTION()
	void OnHoveredSecond();

	UFUNCTION()
	void OnLeavedSecond();

	//!--------------Game-----------
	UFUNCTION(BlueprintCallable)
	void StartGameClicked();	
	
	UFUNCTION()
	void StartGameHovered();	
	
	UFUNCTION()
	void StartGameLeaved();

	UFUNCTION(BlueprintCallable)
	void OnChatTextCommitted(const FText& Text, ETextCommit::Type CommitMethod);

public:
	UFUNCTION()
	void SetFirstText(FString text);

	UFUNCTION()
	void SetSecondText(FString text);

	UFUNCTION()
	void SetCanStart(bool bCanStart);

	UFUNCTION()
	void SuccessSelect();

	UFUNCTION()
	void CancelSelect();

	UFUNCTION()
	void FailSelect();
};
