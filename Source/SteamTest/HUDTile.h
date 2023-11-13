// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDTile.generated.h"

/**
 * 
 */
UCLASS()
class STEAMTEST_API UHUDTile : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
	class UBorder* BorderInner;

public:
	UFUNCTION()
	void OnClicked(const FGeometry& Geometry, const FPointerEvent& MouseEvent);

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	class UTileData* TileData;

protected:
	virtual void NativeOnInitialized();
};
