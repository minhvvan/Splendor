// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ping.generated.h"

UCLASS()
class STEAMTEST_API APing : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APing();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAcess = "true"))
	class UBillboardComponent* Billboard;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
