// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PCLobby.generated.h"

/**
 * 
 */
UCLASS()
class STEAMTEST_API APCLobby : public APlayerController
{
	GENERATED_BODY()
	
public:
	APCLobby();

	UFUNCTION()
	void BeginPlay() override;

	UFUNCTION(Server, Reliable)
	void SRSpawnPlayer();

	UFUNCTION()
	void ShowLobby();

	UFUNCTION(Server, Reliable)
	void SRFirstPlayerClicked();

	UFUNCTION(Server, Reliable)
	void SRSecondPlayerClicked();

	UFUNCTION(Client, Reliable)
	void MarkFirst(const FString& name);

	UFUNCTION(Client, Reliable)
	void MarkSecond(const FString& name);

	UFUNCTION(Client, Reliable)
	void SuccessSelect();

	UFUNCTION(Client, Reliable)
	void CancelSelect();

	UFUNCTION(Client, Reliable)
	void FailSelect();

	UFUNCTION(Client, Reliable)
	void Init();

	UFUNCTION(Server, Reliable)
	void SRUpdatePlayerState(const FString& name);

	void OnRep_PlayerState() override;

	UFUNCTION(Server, Reliable)
	void SRStartGame();

	UFUNCTION(NetMulticast, Reliable)
	void DetachLobbyWidget();

	UFUNCTION()
	void CheckCanStart();

	UFUNCTION()
	void EnableCanStart(bool bStart);

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> LobbyClass;

	UPROPERTY(VisibleAnywhere)
	class UHUDLobby* WidgetLobby;
};
