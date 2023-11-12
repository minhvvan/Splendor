// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Token.h"
#include "GlobalStruct.h"
#include "PCPlay.generated.h"

class ATile;

UCLASS()
class STEAMTEST_API APCPlay : public APlayerController
{
	GENERATED_BODY()
	
public:
	APCPlay();

	UFUNCTION()
	void BeginPlay() override;

	UFUNCTION()
	void Click();

	UFUNCTION()
	void BindState();

	//!----------Turn--------
	UFUNCTION(Server, Reliable)
	void SRSetTurn();

	UFUNCTION()
	void SetTurn(bool flag);

	UFUNCTION()
	bool GetTurn() { return IsTurn; };

	//!--------------Token-----------
	TArray<AToken*>& GetSelectedTokens() { return SelectedToken; };
	
	UFUNCTION(Server, Reliable)
	void SRPossessTokens(bool bFirst);

	UFUNCTION(Client, Reliable)
	void ClearSelectedTokens();

	UFUNCTION(Client, Reliable)
	void PopUpOverToken();

	bool IsNear(int a, int b);

	UFUNCTION(Server, Reliable)
	void SRClickToken(AToken* ClickedToken, int cnt, bool bAble);

	UFUNCTION()
	void TokenClicked(AToken* ClickedToken);

	UFUNCTION()
	void TakeTokenFromOpp(ETokenColor color);	
	
	UFUNCTION(Server, Reliable)
	void SRTakeToken(ETokenColor color);

	UFUNCTION()
	TArray<FTokenCount> GetOppTokens();

	//!--------------Card-----------
	UFUNCTION()
	void CardClicked(ACard* ClickedCard);

	UFUNCTION(Server, Reliable)
	void SRBuyCard(FCardInfo cardInfo,const FTokenCountList& UseTokens);
	
	UFUNCTION(Server, Reliable)
	void SRCardClicked(ACard* ClickedCard);

	//!------------DESK-------
	UFUNCTION()
	void ShowDesk();

	UFUNCTION(Server, Reliable)
	void SRRestoreToken(const FTokenCountList& Restore);

	UFUNCTION()
	void SendMessage(FString msg);

	UFUNCTION(Client, Reliable)
	void ShowItemWidget(EItem itemType, const FCardInfo& cardInfo);

	UFUNCTION(Server, Reliable)
	void SRAddBonus(ETokenColor color);

	UFUNCTION(Server, Reliable)
	void SRAddScore(ETokenColor color, int score);



protected:
	virtual void SetupInputComponent() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
	TArray<ATile*> Tiles;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> DeskClass;

	UPROPERTY(VisibleAnywhere)
	class UHUDDesk* WidgetDesk;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ATile> TileClass;

	const FString CAM_TAG = TEXT("GameCam");

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ClickAction;

	UPROPERTY()
	TArray<AToken*> SelectedToken;

	UPROPERTY(replicated)
	bool IsTurn = false;

	UPROPERTY(replicated)
	int GoldCnt = 0;
};
