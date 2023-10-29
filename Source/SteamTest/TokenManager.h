// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Token.h"
#include "TokenManager.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FDeleAddScroll, APlayerController*);

UCLASS()
class STEAMTEST_API ATokenManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATokenManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SpawnTokens();
	void PlaceTokens(TArray<AToken*>& Tokens);

	UFUNCTION()
	void SelectedToken(AToken* token, bool bSelected);

	UFUNCTION()
	void FillTokens();

	UFUNCTION()
	void PossessTokens(APlayerController* PC, bool bFirst);
	
	UFUNCTION()
	void UseTokens(TArray<AToken*>& Tokens, bool b1Player);

	FDeleAddScroll AddScroll;

private:
	TArray<AToken*> RemainTokens;
	TArray<AToken*> Pouch;

	TArray<AToken*> SelectedTokens;

	TMap<ETokenType, AToken*> P1Tokens;
	TMap<ETokenType, AToken*> P2Tokens;

	TArray<TArray<AToken*>> Board;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AToken> RedTokenClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AToken> GreenTokenClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AToken> BlueTokenClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AToken> BlackTokenClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AToken> WhileTokenClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AToken> GoldTokenClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AToken> PearlTokenClass;

};
