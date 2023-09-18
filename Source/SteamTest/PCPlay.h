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

	UFUNCTION()
	void ShowDesk();

	//UFUNCTION(Client, Reliable)
	//void SpawnPlayer();

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> DeskClass;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<APawn> PawnClass;

	UPROPERTY(VisibleAnywhere)
	class UHUDDesk* WidgetDesk;

	const FString CAM_TAG = TEXT("GameCam");
};
