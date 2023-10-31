// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Token.h"
#include "TokenManager.generated.h"

USTRUCT()
struct FTokens
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY()
	TArray<AToken*> RedTokens;

	UPROPERTY()
	TArray<AToken*> GreenTokens;

	UPROPERTY()
	TArray<AToken*> BlueTokens;

	UPROPERTY()
	TArray<AToken*> WhiteTokens;

	UPROPERTY()
	TArray<AToken*> BlackTokens;

	UPROPERTY()
	TArray<AToken*> GoldTokens;

	UPROPERTY()
	TArray<AToken*> PearlTokens;

	UPROPERTY()
	TArray<AToken*> Default;

	TArray<AToken*>& GetTokenList(ETokenType type)
	{
		switch (type)
		{
		case ETokenType::T_Red:
			return RedTokens;
		case ETokenType::T_Green:
			return GreenTokens;
		case ETokenType::T_Blue:
			return BlueTokens;
		case ETokenType::T_White:
			return WhiteTokens;
		case ETokenType::T_Black:
			return BlackTokens;
		case ETokenType::T_Gold:
			return GoldTokens;
		case ETokenType::T_Pearl:
			return PearlTokens;
		}

		return Default;
	}

	AToken* Remove(ETokenType type)
	{
		auto& TokenArray = GetTokenList(type);
		return TokenArray.Pop();
	}

	void Add(ETokenType type, AToken* token)
	{
		auto& TokenArray = GetTokenList(type);
		TokenArray.Add(token);
	}

	int Num()
	{
		return RedTokens.Num() + GreenTokens.Num() + BlueTokens.Num() + WhiteTokens.Num() + BlackTokens.Num() + GoldTokens.Num() + PearlTokens.Num();
	}
};


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
	void UseTokens(FRestroeTokens Tokens, bool bFirst);

	FDeleAddScroll AddScroll;

private:
	TArray<AToken*> RemainTokens;
	TArray<AToken*> Pouch;

	TArray<AToken*> SelectedTokens;

	FTokens P1Tokens;
	FTokens P2Tokens;

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
