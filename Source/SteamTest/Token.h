// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GlobalEnum.h"
#include "Token.generated.h"


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

	UFUNCTION()
	int GetIndex() const { return Index; };

	UFUNCTION()
	void SetIndex(int idx) { Index = idx; };

	UFUNCTION()
	ETokenColor GetTokenType() const { return TokenType; };

	UFUNCTION()
	void SetTokenType(ETokenColor color);	
	
	UFUNCTION()
	void OnHover(UPrimitiveComponent* Target);

	UFUNCTION()
	void OnLeave(UPrimitiveComponent* Target);
	
	UFUNCTION()
	void MoveAndDestory(FVector dest);

private:
	UPROPERTY(BlueprintReadWrite, EditAnyWhere, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Mesh;

	UPROPERTY(BlueprintReadWrite, EditAnyWhere, meta = (AllowPrivateAccess = "true"))
	class UAudioComponent* AudioComp;

	UPROPERTY(BlueprintReadWrite, EditAnyWhere, meta = (AllowPrivateAccess = "true"))
	class USoundCue* HoverSound;

	UPROPERTY(BlueprintReadWrite, EditAnyWhere, meta = (AllowPrivateAccess = "true"))
	TMap<ETokenColor, UStaticMesh*> TokenMesh;

	UPROPERTY(replicated)
	int Index;

	UPROPERTY(replicated)
	ETokenColor TokenType;

	UPROPERTY()
	FVector Destination;

	UPROPERTY()
	bool bMoveComplete;

	UFUNCTION()
	FVector InterpolatePos(float delta);

	UFUNCTION()
	FRotator InterpolateRot(float delta);

	UPROPERTY(BlueprintReadWrite, EditAnyWhere, meta = (AllowPrivateAccess = "true"))
	float LerpSpeed;

	UPROPERTY()
	float PitchValue;
};
