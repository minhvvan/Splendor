// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "STGameModeLobby.generated.h"

/**
 * 
 */
UCLASS()
class STEAMTEST_API ASTGameModeLobby : public AGameMode
{
	GENERATED_BODY()
	
public:
	ASTGameModeLobby();

	UFUNCTION()
	void BeginPlay();

	UFUNCTION()
	void PostLogin(APlayerController* NewPlayer) override;

	UFUNCTION()
	void SwapPlayerControllers(APlayerController* OldPC, APlayerController* NewPC) override;

	UFUNCTION()
	void Logout(AController* Exiting) override;

	UFUNCTION()
	void SpawnPlayer(APlayerController* PlayerController);

	UFUNCTION()
	void FirstPlayerMark(FString name);

private:
	UPROPERTY()
	TArray<class APlayerController*> PlayerControllers;

	UPROPERTY()
	TArray<class APlayerState*> PlayerStates;

	UPROPERTY()
	TSubclassOf<AActor> SpawnToActor;
};
