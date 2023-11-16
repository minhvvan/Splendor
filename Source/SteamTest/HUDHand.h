// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GlobalStruct.h"
#include "HUDHand.generated.h"

/**
 * 
 */
UCLASS()
class STEAMTEST_API UHUDHand : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void AddCard(FCardInfo cardInfo);
	
protected:
	virtual void NativeOnInitialized();

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
	class UOverlay* OverlayHand;

	UPROPERTY()
	TArray<class UHUDHandCard*> Hands;

	UFUNCTION()
	void UpdateCardPosition();

	UFUNCTION()
	FWidgetTransform CalculatePosition(int idx);

	UFUNCTION()
	float CalculateAngle(int idx);

	UFUNCTION()
	float CalculateXpos(int idx);

	UFUNCTION()
	float CalculateYpos(int idx);

	UFUNCTION()
	int ConvertIdx(int idx);

	UFUNCTION()
	void OnHovered(UHUDHandCard* HoverdCard);

	UFUNCTION()
	void OnLeaved(UHUDHandCard* HoverdCard);

	UFUNCTION()
	float GetHoverYOffset(int idx);

	UFUNCTION()
	float GetHoverXOffset(int idx);

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> CardClass;

	UPROPERTY()
	float AnimSpeed;

	UPROPERTY()
	float CardAngle;

	UPROPERTY()
	float CardSpacing;

	UPROPERTY()
	float ArcHeight;

	UPROPERTY()
	float DefaultYOffset;	
	
	UPROPERTY()
	float DefaultXOffset;

	UPROPERTY()
	float HoverYOffset;

	UPROPERTY()
	float HoverXOffset;

	UPROPERTY()
	int HoveredCardIdx;

	const int NONVALIDIDX = -100;
};
