// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Card.generated.h"

UCLASS()
class STEAMTEST_API ACard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	UAudioComponent* GetAudio() const { return AudioComp; };

	UFUNCTION()
	void SetInfo(struct FCardInfo& info);	
	
	UFUNCTION()
	void ChangedCardInfo();

private:
	UPROPERTY(BlueprintReadWrite, EditAnyWhere, meta = (AllowPrivateAccess = "true"))
	class UClickableMesh* Mesh;

	UPROPERTY(BlueprintReadWrite, EditAnyWhere, meta = (AllowPrivateAccess = "true"))
	class UAudioComponent* AudioComp;

	UPROPERTY(BlueprintReadWrite, EditAnyWhere, meta = (AllowPrivateAccess = "true"))
	class USoundCue* HoverSound;

	UPROPERTY(BlueprintReadWrite, replicated, EditAnyWhere, meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* CardWidgetComp;

	UPROPERTY(ReplicatedUsing = ChangedCardInfo)
	FCardInfo* CardInfo;

};
