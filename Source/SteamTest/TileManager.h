// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.h"
#include "TileManager.generated.h"

UCLASS()
class STEAMTEST_API ATileManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATileManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void SpawnTiles();
	
	UFUNCTION()
	void SetTokenLocs(const TArray<class AToken*>& Tokens);

	UFUNCTION()
	void Clicked(int selectedIdx, bool bAble);

	UFUNCTION()
	void UpdateBoardState();

	UFUNCTION()
	void ClearSeletedTiles(const TArray<int>& DestroyTokenIdx);

private:
	TArray<ATile*> Tiles;
	TArray<int> FillIdx;
	TArray<int> SelectedTiles;
	TArray<TArray<TArray<int>>> Distance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	TSubclassOf<ATile> TileClass;
};
