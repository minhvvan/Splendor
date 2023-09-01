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

	//playerstate정보를 받아서 화면에 표시
	UFUNCTION(NetMulticast, Reliable)
	void MarkFirst(const FString& name);

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> LobbyClass;

	UPROPERTY(VisibleAnywhere)
	class UHUDLobby* WidgetLobby;
};
