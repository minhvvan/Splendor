// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PCMenu.generated.h"

/**
 * 
 */
UCLASS()
class STEAMTEST_API APCMenu : public APlayerController
{
	GENERATED_BODY()
	
public:
	APCMenu();

	UFUNCTION()
	void ShowMultMenu();

	UFUNCTION()
	void ShowLobby();

	UFUNCTION()
	void PreSessionSearch();

	UFUNCTION()
	void AddSessionRow(class UHUDServerRow* row);

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> MultMenuClass;

	UPROPERTY(VisibleAnywhere)
	class UHUDMultMenu* WidgetMultMenu;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> LobbyClass;

	UPROPERTY(VisibleAnywhere)
	class UHUDLobby* WidgetLobby;
};
