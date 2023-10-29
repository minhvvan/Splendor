// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PCPlay.generated.h"

class AToken;
class ATile;

/**
 * 
 */
UCLASS()
class STEAMTEST_API APCPlay : public APlayerController
{
	GENERATED_BODY()
	
public:
	APCPlay();

	UFUNCTION()
	void BeginPlay() override;

	UFUNCTION(Server, Reliable)
	void SRSetTurn();

	UFUNCTION(Server, Reliable)
	void SRClickToken(AToken* ClickedToken, int cnt, bool bAble);

	UFUNCTION()
	void ShowDesk();

	void Click();

	bool IsNear(int a, int b);

	TArray<AToken*>& GetSelectedTokens() { return SelectedToken; };

	UFUNCTION()
	void SetTurn(bool flag);

	UFUNCTION()
	bool GetTurn() { return IsTurn; };

	UFUNCTION(Server, Reliable)
	void SRPossessTokens();

	UFUNCTION(Client, Reliable)
	void ClearSelectedTokens();

	UFUNCTION()
	void PopUpOverToken();

	UFUNCTION()
	void BindState();

	//!------------Desk-------


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
};
