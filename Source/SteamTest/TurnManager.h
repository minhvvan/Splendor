// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TurnManager.generated.h"

UCLASS()
class STEAMTEST_API ATurnManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATurnManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void InitPlayerTurn(APlayerController* Player, bool bFirst);
	void EndCurrentTurn();

	bool IsFirstPlayer(APlayerController* PC);

	UFUNCTION()
	APCPlay* GetFirstPlayer() { return Players[0]; };

	UFUNCTION()
	APCPlay* GetScondPlayer() { return Players[1]; };

private:
	int PlayerTurn = 0;

	TArray<class APCPlay*> Players;

	UPROPERTY()
	class APCPlay* CurrentPlayer;
};
