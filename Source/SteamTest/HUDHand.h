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

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> CardClass;

	UPROPERTY()
	float AnimSpeed;
};
