// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDAnyColor.generated.h"

/**
 * 
 */
UCLASS()
class STEAMTEST_API UHUDAnyColor : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTileView* TVColor;

protected:
	virtual void NativeOnInitialized();


public:
	UFUNCTION()
	void SetInfo(const FCardInfo& cardInfo);

	UFUNCTION()
	void CallUpdate(ETokenColor color);

private:
	UPROPERTY()
	int score;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UCostData> DataClass;
};
