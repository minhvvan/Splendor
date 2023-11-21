// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GlobalStruct.h"
#include "HUDGetToken.generated.h"

/**
 * 
 */
UCLASS()
class STEAMTEST_API UHUDGetToken : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void SetTiles(const TArray<ETokenColor>& tokens, const FCardInfo& cardInfo);

protected:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTileView* TileRowOne;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTileView* TileRowTwo;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTileView* TileRowThree;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTileView* TileRowFour;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTileView* TileRowFive;

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UTileData> TileDataClass;
};
