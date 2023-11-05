// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Token.generated.h"


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
	ETokenColor GetTokenType() const { return TokenType; };

	UFUNCTION()
	void SetTokenType(ETokenColor color) { TokenType = color; };

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
	ETokenColor TokenType;
};
