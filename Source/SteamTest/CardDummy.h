// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CardDummy.generated.h"

UCLASS()
class STEAMTEST_API ACardDummy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACardDummy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void SetTier(ECardTier tier) { Tier = tier; };

	UFUNCTION()
	ECardTier GetTier() { return Tier; };

	UFUNCTION()
	void SetNum(int cardNum);

	UFUNCTION()
	UAudioComponent* GetAudio() const { return AudioComp; };	
	
	UFUNCTION()
	void ShowNum();	
	
	UFUNCTION()
	void hideNum();

private:
	UPROPERTY()
	ECardTier Tier;

	UPROPERTY(BlueprintReadWrite, EditAnyWhere, meta = (AllowPrivateAccess = "true"))
	class UClickableMesh* Mesh;

	UPROPERTY(BlueprintReadWrite, EditAnyWhere, meta = (AllowPrivateAccess = "true"))
	class UAudioComponent* AudioComp;

	UPROPERTY(BlueprintReadWrite, EditAnyWhere, meta = (AllowPrivateAccess = "true"))
	class USoundCue* HoverSound;

	UPROPERTY(BlueprintReadWrite, EditAnyWhere, meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* NumWidgetComp;
};
