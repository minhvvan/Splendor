// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDNotifyRow.generated.h"

/**
 * 
 */
UCLASS()
class STEAMTEST_API UHUDNotifyRow : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* TxtName;

public:
	UFUNCTION()
	void SetText(const FString& Chat);
};
