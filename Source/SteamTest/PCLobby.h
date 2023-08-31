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

	UFUNCTION()
	void FirstPlayerClicked();

	UFUNCTION(Server, Reliable)
	void SRFirstPlayerClicked();

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> LobbyClass;

	UPROPERTY(VisibleAnywhere)
	class UHUDLobby* WidgetLobby;
};
