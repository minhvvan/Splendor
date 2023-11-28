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
	class UBorder* BorderMenuBtn;
	
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UButton* BtnHostGame;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UButton* BtnSearchGame;	
	
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* TxtSearchGame;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UButton* BtnBack;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UBorder* BorderServerList;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UScrollBox* SclServerList;

protected:
	virtual void NativeOnInitialized();

	//!----------Anim----------------
	UPROPERTY(BlueprintReadOnly, Transient, meta = (BindWidgetAnim))
	class UWidgetAnimation* BtnHostHover;

	UPROPERTY(BlueprintReadOnly, Transient, meta = (BindWidgetAnim))
	class UWidgetAnimation* BtnSearchHover;

	UPROPERTY(BlueprintReadOnly, Transient, meta = (BindWidgetAnim))
	class UWidgetAnimation* BtnBackHover;

	UPROPERTY(BlueprintReadOnly, Transient, meta = (BindWidgetAnim))
	class UWidgetAnimation* MessageAnim;

	//!----------SFX----------------
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class USoundBase* FailedSound;

private:
	//!----------Host----------------
	UFUNCTION(BlueprintCallable)
	void HostGameClicked();	
	
	UFUNCTION()
	void HostGameHovered();

	UFUNCTION()
	void HostGameLeaved();

	//!----------Search----------------
	UFUNCTION(BlueprintCallable)
	void SearchGameClicked();

	UFUNCTION()
	void SearchGameHovered();

	UFUNCTION()
	void SearchGameLeaved();


	//!----------Back----------------
	UFUNCTION(BlueprintCallable)
	void BackClicked();

	UFUNCTION(BlueprintCallable)
	void BackHovered();

	UFUNCTION(BlueprintCallable)
	void BackLeaved();


	//!----------ETC----------------
	UFUNCTION()
	void PreSessionSearch();

	UFUNCTION()
	void RenderMessage();

public:
	UFUNCTION()
	void AddSessionRow(class UHUDServerRow* row);

	UFUNCTION()
	void FailedSessionSearch();
};
