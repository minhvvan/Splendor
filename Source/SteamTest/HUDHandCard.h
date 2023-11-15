// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUDCard.h"
#include "HUDHandCard.generated.h"

/**
 * 
 */
UCLASS()
class STEAMTEST_API UHUDHandCard : public UHUDCard
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void StartRePostion(FWidgetTransform Pos, float Speed);
	
protected:
	virtual void Onclicked(const FGeometry& Geometry, const FPointerEvent& MouseEvent);

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

	UFUNCTION()
	bool IsCompletedMove();

	UFUNCTION()
	FWidgetTransform IterpolateWidgetPos(float Delta);


	UPROPERTY()
	FWidgetTransform DestPos;

	UPROPERTY()
	float InterpolationSpeed;

	UPROPERTY()
	bool bCompletedMove; 
};
