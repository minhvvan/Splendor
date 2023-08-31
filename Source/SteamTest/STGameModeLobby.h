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

	void BeginPlay();

	void PostLogin(APlayerController* NewPlayer) override;

	void SwapPlayerControllers(APlayerController* OldPC, APlayerController* NewPC) override;
	
	void Logout(AController* Exiting) override;

	void SpawnPlayer(APlayerController* PlayerController);

private:
	TArray<class APlayerController*> PlayerControllers;

	UPROPERTY()
	TSubclassOf<AActor> SpawnToActor;
};
