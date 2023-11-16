// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUDCard.h"
#include "HUDHandCard.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FDeleOnHover, UHUDHandCard*);
DECLARE_MULTICAST_DELEGATE_OneParam(FDeleOnLeave, UHUDHandCard*);
DECLARE_MULTICAST_DELEGATE_OneParam(FDeleOnCardClick, FCardInfo);

UCLASS()
class STEAMTEST_API UHUDHandCard : public UHUDCard
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void StartRePostion(FWidgetTransform Pos, float Speed);
	
	FDeleOnHover OnHover;
	FDeleOnLeave OnLeave;
	FDeleOnCardClick OnCardClicked;

protected:
	virtual void NativeOnInitialized();

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);

	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent);

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
