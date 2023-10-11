// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

UCLASS()
class STEAMTEST_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FVector GetTokenLoc() { return GetActorLocation() + FVector(0, 0, 15); };

	class AToken* GetOnToken() { return OnToken; };

	UFUNCTION()
	void SetOnToken(class AToken* token);

	UFUNCTION(NetMulticast, Reliable)
	void OnSelected();

	UFUNCTION(NetMulticast, Reliable)
	void OnUnSelected();

	UFUNCTION(NetMulticast, Reliable)
	void SetIsAble(bool bAlbe);
private:
	UPROPERTY(BlueprintReadWrite, EditAnyWhere, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;

	UPROPERTY()
	AToken* OnToken;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class UMaterial* UnSelectedMat;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class UMaterial* SelectedMat;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class UMaterial* DisabledMat;
};
