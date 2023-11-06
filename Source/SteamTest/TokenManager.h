// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Token.h"
#include "GlobalEnum.h"
#include "TokenManager.generated.h"

USTRUCT(BlueprintType)
struct FTokenList
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
	TArray<AToken*> Dummy;

	TArray<AToken*>& GetTokenList(ETokenColor type)
	{
		switch (type)
		{
		case ETokenColor::E_Red:
			return RedTokens;
		case ETokenColor::E_Green:
			return GreenTokens;
		case ETokenColor::E_Blue:
			return BlueTokens;
		case ETokenColor::E_White:
			return WhiteTokens;
		case ETokenColor::E_Black:
			return BlackTokens;
		case ETokenColor::E_Gold:
			return GoldTokens;
		case ETokenColor::E_Pearl:
			return PearlTokens;
		}

		return Dummy;
	}

	AToken* Remove(ETokenColor type)
	{
		auto& TokenArray = GetTokenList(type);
		return TokenArray.Pop();
	}

	void Add(ETokenColor type, AToken* token)
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
	void UseTokens(FTokenCountList Restore, bool bFirst);

	FDeleAddScroll AddScroll;

private:
	TArray<AToken*> RemainTokens;
	TArray<AToken*> Pouch;

	TArray<AToken*> SelectedTokens;

	FTokenList P1Tokens;
	FTokenList P2Tokens;

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
