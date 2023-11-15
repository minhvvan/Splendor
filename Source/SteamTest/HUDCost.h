// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDCost.generated.h"

UCLASS()
class STEAMTEST_API UHUDCost : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
	class UBorder* BorderColor;

public:
	UFUNCTION()
	void OnClicked(const FGeometry& Geometry, const FPointerEvent& MouseEvent);

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	class UCostData* CostData;
protected:
	virtual void NativeOnInitialized();
};
