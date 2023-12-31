// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDCardHolder.h"
#include "GlobalStruct.h"
#include "HUDDesk.generated.h"

UENUM(BlueprintType)
enum class EFailWidget : uint8
{
	E_GetToken = 0		UMETA(DisplayName = "GetToken"),
	E_FillToken			UMETA(DisplayName = "FillToken"),
	E_UseScroll			UMETA(DisplayName = "UseScroll"),
	E_TwiceUseScroll	UMETA(DisplayName = "TwiceUseScroll"),

	E_End,
};


UCLASS()
class STEAMTEST_API UHUDDesk : public UUserWidget
{
	GENERATED_BODY()
	

protected:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UButton* BtnGetToken;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UButton* BtnFillToken;	
	
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UButton* BtnUseScroll;
	
	UPROPERTY(VisibleAnywhere, meta = (BindWidgetOptional))
	class UHUDPopUpPannel* PUPannel;

	UPROPERTY(VisibleAnywhere, meta = (BindWidgetOptional))
	class UHUDCardHolder* CDHRed;	
	
	UPROPERTY(VisibleAnywhere, meta = (BindWidgetOptional))
	class UHUDCardHolder* CDHGreen;

	UPROPERTY(VisibleAnywhere, meta = (BindWidgetOptional))
	class UHUDCardHolder* CDHBlue;

	UPROPERTY(VisibleAnywhere, meta = (BindWidgetOptional))
	class UHUDCardHolder* CDHWhite;

	UPROPERTY(VisibleAnywhere, meta = (BindWidgetOptional))
	class UHUDCardHolder* CDHBlack;

	UPROPERTY(VisibleAnywhere, meta = (BindWidgetOptional))
	class UHUDTokenHolder* TokenHolder;	
	
	UPROPERTY(VisibleAnywhere, meta = (BindWidgetOptional))
	class UHUDHand* Hand;

	UPROPERTY(VisibleAnywhere, meta = (BindWidgetOptional))
	class UHUDTurnAlert* TurnAlert;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* TxtScore;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* TxtCrown;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* TxtScroll;	
	
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* TxtTurn;	
	
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* TxtMessage;

	UPROPERTY(BlueprintReadOnly, Transient, meta = (BindWidgetAnim))
	class UWidgetAnimation* FailedGetAnim;	
	
	UPROPERTY(BlueprintReadOnly, Transient, meta = (BindWidgetAnim))
	class UWidgetAnimation* FailedFillAnim;

	UPROPERTY(BlueprintReadOnly, Transient, meta = (BindWidgetAnim))
	class UWidgetAnimation* FailedUseScrollAnim;

	UPROPERTY(BlueprintReadOnly, Transient, meta = (BindWidgetAnim))
	class UWidgetAnimation* MessageAnim;

	virtual void NativeOnInitialized();

public:
	void InitSetTurnBegin(const FString& turn);

	UFUNCTION()
	void BindState(class APSPlayerInfo* ps);

	UFUNCTION()
	void ChangedScroll();

	UFUNCTION()
	void ChangedToken();

	UFUNCTION()
	void ChangedBonus();

	UFUNCTION()
	void ChangedScore();

	UFUNCTION()
	void ChangedColorScore();

	UFUNCTION()
	void ChangedCrown();	
	
	UFUNCTION()
	void RenderMessage(FString message);

	//!---------Hand--------------
	UFUNCTION()
	void AddCardToHand(FCardInfo cardInfo);	
	
	UFUNCTION()
	void OnHandCardClicked(FCardInfo cardInfo);

	UFUNCTION()
	void OnBuyCard(int key);

	//!---------PopUp--------------
	UFUNCTION()
	void CrownEvent();

	UFUNCTION()
	void NotifyOverToken();

	UFUNCTION()
	void PopUpDetailCard(const FCardInfo& cardInfo);

	UFUNCTION()
	void PopUpItemGetToken(const TArray<ETokenColor>& colors, bool bEndturn);

	UFUNCTION()
	void PopUpItemTakeToken();

	UFUNCTION()
	void PopUpItemAnyColor(const FCardInfo& cardInfo);

	UFUNCTION()
	void PopUpSelectCard();

	UFUNCTION()
	void PopUpRivalInfo();

	UFUNCTION()
	void PopUpEndPage(const FString& winnerName, bool bWin);

	UFUNCTION()
	UHUDCardHolder* GetBonusWidget(ETokenColor color);

	UFUNCTION()
	void CloseItemWidget(EItem itemType);

	UFUNCTION()
	void CloseCrownWidget();

	UFUNCTION()
	void CloseCardWidget();

	UFUNCTION()
	void CloseRivalInfo();

	//!---------Util--------------
	UFUNCTION()
	void FailAnimPlay(EFailWidget failWidget);

private:
	UFUNCTION(BlueprintCallable)
	void GetTokenClicked();

	UFUNCTION(BlueprintCallable)
	void FilTokenClicked();		
	
	UFUNCTION(BlueprintCallable)
	void UseScrollClicked();


	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	USoundBase* FailSound;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> OverTokenClass;

	UPROPERTY()
	TWeakObjectPtr<APSPlayerInfo> CurrentState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> DetailCardClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> GetTokenWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> TakeTokenWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> AnyColorWidgetClass;	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> RoyalWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> SelectCardWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> RivalInfoClass;	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> EndGameClass;

	UPROPERTY()
	TWeakObjectPtr<class UHUDTakeToken> TakeWidget;

	UPROPERTY()
	TWeakObjectPtr<class UHUDGetToken> GetWidget;

	UPROPERTY()
	TWeakObjectPtr<class UHUDSelectRoyal> CrownWidget;

	UPROPERTY()
	TWeakObjectPtr<class UHUDSelectCard> CardWidget;

	UPROPERTY()
	TWeakObjectPtr<class UHudRivalInfo> RivalInfoWidget;	

	UPROPERTY()
	TWeakObjectPtr<class UHUDDetailCard> DetailCardWidget;
	
	//!---------Data--------------
	UPROPERTY()
	bool bUsedScroll = false;
};
