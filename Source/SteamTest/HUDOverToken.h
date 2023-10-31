// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDOverToken.generated.h"

/**
 * 
 */
UCLASS()
class STEAMTEST_API UHUDOverToken : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnInitialized();
	
public:
	UFUNCTION()
	void UpRed();
	UFUNCTION()
	void DownRed();
	
	UFUNCTION()
	void UpGreen();
	UFUNCTION()
	void DownGreen();

	UFUNCTION()
	void UpBlue();
	UFUNCTION()
	void DownBlue();

	UFUNCTION()
	void UpWhite();
	UFUNCTION()
	void DownWhite();

	UFUNCTION()
	void UpBlack();
	UFUNCTION()
	void DownBlack();

	UFUNCTION()
	void UpGold();
	UFUNCTION()
	void DownGold();

	UFUNCTION()
	void UpPearl();
	UFUNCTION()
	void DownPearl();

	UFUNCTION()
	void CommitTokens();

	UFUNCTION()
	void UpdateTotalToken();

	UFUNCTION()
	int GetTokenNumByType(ETokenType type);

private:
	UFUNCTION()
	void FailClick(ETokenType type, bool bUp);

	void RenderMessage();

private:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* TxtCurrentToken;

	//!-------------Red------------
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UButton* BtnRedUp;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* TxtRed;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UButton* BtnRedDown;

	//!----------Green-------------
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UButton* BtnGreenUp;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* TxtGreen;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UButton* BtnGreenDown;

	//!----------Blue-------------
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UButton* BtnBlueUp;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* TxtBlue;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UButton* BtnBlueDown;

	//!----------White-------------
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UButton* BtnWhiteUp;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* TxtWhite;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UButton* BtnWhiteDown;

	//!----------Black-------------
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UButton* BtnBlackUp;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* TxtBlack;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UButton* BtnBlackDown;

	//!----------Gold-------------
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UButton* BtnGoldUp;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* TxtGold;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UButton* BtnGoldDown;

	//!----------Pearl-------------
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UButton* BtnPearlUp;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* TxtPearl;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UButton* BtnPearlDown;

	//!------------Data---------------
	int RedNum;
	int GreenNum;
	int BlueNum;
	int WhiteNum;
	int BlackNum;
	int GoldNum;
	int PearlNum;

	int TotalNum;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UButton* BtnCommit;	
	
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* TxtMessage;

	UPROPERTY()
	class APSPlayerInfo* PS;

	//!---------------Anim------------
	UPROPERTY(BlueprintReadOnly, Transient, meta = (BindWidgetAnim, AllowPrivateAccess = "true"))
	class UWidgetAnimation* FailRedUp;
	
	UPROPERTY(BlueprintReadOnly, Transient, meta = (BindWidgetAnim, AllowPrivateAccess = "true"))
	class UWidgetAnimation* FailRedDown;

	UPROPERTY(BlueprintReadOnly, Transient, meta = (BindWidgetAnim, AllowPrivateAccess = "true"))
	class UWidgetAnimation* FailGreenUp;

	UPROPERTY(BlueprintReadOnly, Transient, meta = (BindWidgetAnim, AllowPrivateAccess = "true"))
	class UWidgetAnimation* FailGreenDown;

	UPROPERTY(BlueprintReadOnly, Transient, meta = (BindWidgetAnim, AllowPrivateAccess = "true"))
	class UWidgetAnimation* FailBlueUp;

	UPROPERTY(BlueprintReadOnly, Transient, meta = (BindWidgetAnim, AllowPrivateAccess = "true"))
	class UWidgetAnimation* FailBlueDown;

	UPROPERTY(BlueprintReadOnly, Transient, meta = (BindWidgetAnim, AllowPrivateAccess = "true"))
	class UWidgetAnimation* FailWhiteUp;

	UPROPERTY(BlueprintReadOnly, Transient, meta = (BindWidgetAnim, AllowPrivateAccess = "true"))
	class UWidgetAnimation* FailWhiteDown;

	UPROPERTY(BlueprintReadOnly, Transient, meta = (BindWidgetAnim, AllowPrivateAccess = "true"))
	class UWidgetAnimation* FailBlackUp;

	UPROPERTY(BlueprintReadOnly, Transient, meta = (BindWidgetAnim, AllowPrivateAccess = "true"))
	class UWidgetAnimation* FailBlackDown;

	UPROPERTY(BlueprintReadOnly, Transient, meta = (BindWidgetAnim, AllowPrivateAccess = "true"))
	class UWidgetAnimation* FailGoldUp;

	UPROPERTY(BlueprintReadOnly, Transient, meta = (BindWidgetAnim, AllowPrivateAccess = "true"))
	class UWidgetAnimation* FailGoldDown;

	UPROPERTY(BlueprintReadOnly, Transient, meta = (BindWidgetAnim, AllowPrivateAccess = "true"))
	class UWidgetAnimation* FailPearlUp;

	UPROPERTY(BlueprintReadOnly, Transient, meta = (BindWidgetAnim, AllowPrivateAccess = "true"))
	class UWidgetAnimation* FailPearlDown;

	UPROPERTY(BlueprintReadOnly, Transient, meta = (BindWidgetAnim, AllowPrivateAccess = "true"))
	class UWidgetAnimation* FailCommit;

	UPROPERTY(BlueprintReadOnly, Transient, meta = (BindWidgetAnim, AllowPrivateAccess = "true"))
	class UWidgetAnimation* MessageAnim;

	//!---------------Sound---------
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	USoundBase* FailSound;
};