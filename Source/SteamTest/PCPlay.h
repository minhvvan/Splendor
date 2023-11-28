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

	//!----------Base--------
	UFUNCTION()
	void Click();	
	
	UFUNCTION()
	void BindState();	
	
	UFUNCTION()
	void PopupRivalInfo();	

	UFUNCTION()
	void CloseRivalInfo();

	UFUNCTION(Client, Reliable)
	void EndGame(const FString& winnerName, bool bWin);

	//!----------Turn--------
	UFUNCTION(Server, Reliable)
	void SRSetTurn();

	UFUNCTION()
	void SetTurn(bool flag);

	UFUNCTION()
	bool GetTurn() { return IsTurn; };

	UFUNCTION(Server, Reliable)
	void SREndTurn();

	//!--------------Token-----------
	UFUNCTION()
	void InitGameBase();
	
	UFUNCTION()
	const TArray<FTokenIdxColor>& GetSelectedTokens() { return SelectedTokenIdx; };
	
	UFUNCTION(Client, Reliable)
	void SpawnToken(const TArray<FTokenIdxColor>& Tokens);
	
	UFUNCTION()
	void PossessTokens();

	UFUNCTION(Server, Reliable)
	void SRPossessTokens(const TArray<FTokenIdxColor>& selcted);

	UFUNCTION(Client, Reliable)
	void RemoveTokens(const TArray<int>& DestroyTokenIdx, bool bOwn);

	UFUNCTION(Client, Reliable)
	void ClearSelectedTokens();

	UFUNCTION(Client, Reliable)
	void PopUpOverToken();

	UFUNCTION()
	bool IsNear(int a, int b);

	UFUNCTION()
	void TokenClicked(AToken* ClickedToken);

	UFUNCTION()
	void TakeTokenFromOpp(ETokenColor color);	
	
	UFUNCTION(Server, Reliable)
	void SRTakeToken(ETokenColor color);

	UFUNCTION()
	void GetTokenByIdx(int idx);

	UFUNCTION(Server, Reliable)
	void SRGetToken(int idx);	
	
	UFUNCTION(Server, Reliable)
	void SRFillToken();

	UFUNCTION()
	TArray<FTokenCount> GetOppTokens();

	UFUNCTION(Client, Reliable)
	void AddCardToHand();	
	
	//!--------------Card-----------
	UFUNCTION()
	void CardClicked(ACard* ClickedCard);

	UFUNCTION(Server, Reliable)
	void SRBuyCard(FCardInfo cardInfo,const FTokenCountList& UseTokens);
	
	UFUNCTION(Server, Reliable)
	void SRChangeCard(FCardInfo cardInfo);

	//!------------DESK-------
	UFUNCTION()
	void ShowDesk();

	UFUNCTION(Server, Reliable)
	void SRRestoreToken(const FTokenCountList& Restore);

	UFUNCTION(Client, Reliable)
	void SendMessage(const FString& msg);

	UFUNCTION(Server, Reliable)
	void SRAddBonus(ETokenColor color);

	UFUNCTION(Server, Reliable)
	void SRAddScore(ETokenColor color, int score);	
	
	UFUNCTION(Server, Reliable)
	void SRAddScroll();

	UFUNCTION(Server, Reliable)
	void SRUseScroll();

	UFUNCTION()
	void GetCardToHand(FCardInfo Info);

	UFUNCTION(Client, Reliable)
	void SetTurnText(const FString& playerName);

	UFUNCTION(Client, Reliable)
	void FailFillToken();

	//!-----------------Item-------------
	UFUNCTION(Client, Reliable)
	void UseItemGetToken(const FCardInfo& cardInfo);

	UFUNCTION(Client, Reliable)
	void UseItemTakeToken();

	UFUNCTION(Client, Reliable)
	void UseItemAnyColor(const FCardInfo& cardInfo);

	//!-----------------Crown-------------
	UFUNCTION()
	void CloseCrownWidget(bool bReplay);	
	
	UFUNCTION(Server, Reliable)
	void SRPossessRoyal(int key);

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* TabAction;

	UPROPERTY(replicated)
	TArray<FTokenIdxColor> SelectedTokenIdx;

	UPROPERTY(replicated)
	bool IsTurn = false;

	UPROPERTY(replicated)
	int GoldCnt = 0;

	//!-----------------Manager-------------
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class ATileManager* TileManager;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class ATokenManager* TokenManager;
};
