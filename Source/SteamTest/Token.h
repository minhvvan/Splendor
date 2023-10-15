// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Token.generated.h"

UENUM(BlueprintType)	
enum class ETokenType : uint8
{
	T_Red = 0   UMETA(DisplayName = "Red"),
	T_Green		UMETA(DisplayName = "Green"),
	T_Blue		UMETA(DisplayName = "Blue"),
	T_White		UMETA(DisplayName = "White"),
	T_Black		UMETA(DisplayName = "Black"),
	T_Gold		UMETA(DisplayName = "Gold"),
	T_Pearl		UMETA(DisplayName = "Pearl"),

	E_End,
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSelected);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUnSelected);
UCLASS()
class STEAMTEST_API AToken : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AToken();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void PostInitializeComponents();

	UAudioComponent* GetAudio() const { return AudioComp; };

	bool GetSelected() const { return bSelected; };
	void SetSelected(bool flag) { bSelected = flag; };

	UFUNCTION(NetMulticast, Reliable)
	void Clicked();

	FSelected OnSelected;
	FUnSelected OnUnSelected;

	UFUNCTION()
	int GetIndex() const { return Index; };

	UFUNCTION()
	void SetIndex(int idx) { Index = idx; };

	UFUNCTION()
	ETokenType GetTokenType() const { return TokenType; };

	UFUNCTION()
	void SetTokenType(ETokenType color) { TokenType = color; };

protected:


private:
	UPROPERTY(BlueprintReadWrite, EditAnyWhere, meta = (AllowPrivateAccess = "true"))
	class UClickableMesh* Mesh;

	UPROPERTY(BlueprintReadWrite, EditAnyWhere, meta = (AllowPrivateAccess = "true"))
	class UAudioComponent* AudioComp;

	UPROPERTY(BlueprintReadWrite, EditAnyWhere, meta = (AllowPrivateAccess = "true"))
	class USoundCue* HoverSound;

	UPROPERTY(replicated)
	bool bSelected;

	UPROPERTY()
	int Index;

	UPROPERTY()
	ETokenType TokenType;
};
