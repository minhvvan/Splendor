// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void HighlightOn(UPrimitiveComponent* TouchComp);

	UFUNCTION()
	void HighlightOff(UPrimitiveComponent* TouchComp);

	virtual void PostInitializeComponents();
private:
	UPROPERTY(BlueprintReadWrite, EditAnyWhere, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;

	UPROPERTY(BlueprintReadWrite, EditAnyWhere, meta = (AllowPrivateAccess = "true"))
	class UAudioComponent* AudioComponent;

	UPROPERTY(BlueprintReadWrite, EditAnyWhere, meta = (AllowPrivateAccess = "true"))
	class USoundCue* HoverSound;
};
