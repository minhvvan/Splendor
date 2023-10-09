// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PCPlay.generated.h"

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

	virtual void SeamlessTravelFrom(class APlayerController* OldPC) override;

	UFUNCTION(Server, Reliable)
	void SRSetTurn();

	UFUNCTION(Server, Reliable)
	void SRClickToken(class AToken* ClickedToken, int cnt, bool bAble);

	UFUNCTION()
	void ShowDesk();

	void Click();

	bool IsNear(int a, int b);

	TArray<class AToken*> GetSelectedTokens() const { return SelectedToken; };

protected:
	virtual void SetupInputComponent() override;

private:
	TArray<class ATile*> Tiles;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> DeskClass;

	UPROPERTY(VisibleAnywhere)
	class UHUDDesk* WidgetDesk;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ATile> TileClass;

	const FString CAM_TAG = TEXT("GameCam");

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ClickAction;

	TArray<class AToken*> SelectedToken;
};
